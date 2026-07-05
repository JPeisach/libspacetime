#include "mars.h"

#include "../const.h"
#include <math.h>

#ifdef HAVE_MPFR
#include <mpfr.h>
#endif

#define SOLS_PER_2Y (668 + 669)
#define SOLS_PER_10Y (668*4 + 669*6) // would be even, but skip if divisible by 10
#define SOLS_PER_100Y ((10 * SOLS_PER_10Y) - 1) // skip if divisible by 100, so subtract 1
// TODO: support 1000Y+

static const int __sols_in_month[24] = {
    28, 28, 28, 28, 28, 27,
    28, 28, 28, 28, 28, 27,
    28, 28, 28, 28, 28, 27,
    28, 28, 28, 28, 28, 27,
};

// This is basically written based off of musl's secs_to_tm function.
// TODO: Testcases for this
struct mars_tm* ammarstime(const mars_time_t* timer)
{
    static struct mars_tm ret;
    int months;

#ifdef HAVE_MPFR
    mpf_set_default_prec(50);
    mpfr_t msd, new_timer;
    mpfr_init(msd);
    mpfr_init(new_timer);
    mpfr_set_d(new_timer, *timer, MPFR_RNDZ);
    mpfr_div_ui(msd, new_timer, 86400.0, MPFR_RNDN);

    int days = ((int)mpfr_get_d(msd, MPFR_RNDN) + (8132745597 / SECONDS_PER_DAY));
#else
    // First, get MSD (days)
    double msd = *timer / 86400.0;

    // When we refer to Darian Calendar days, MSD 0 will be offset.
    // Make sure we start at the right epoch
    int days = ((int)msd + (8132745597 / SECONDS_PER_DAY));
#endif
    // asked google and used its AI results for equations
    // seconds into day:
    int secs_into_day = *timer % SECONDS_PER_DAY;

    // Going based off how musl calculates secs to tm via "cycles"
    // Instead of 4Y -> 100Y -> 400Y, will do 2Y -> 10Y -> 100Y
    int c_cycles = days / SOLS_PER_100Y;
    int remdays = days % SOLS_PER_100Y;
    if (remdays < 0) {
        remdays += SOLS_PER_100Y;
        c_cycles--;
    }

    int d_cycles = remdays / SOLS_PER_10Y;
    if(d_cycles == 10) d_cycles--;
    remdays -= d_cycles * SOLS_PER_10Y;

    int ty_cycles = remdays / SOLS_PER_2Y;
    if(ty_cycles == 2) ty_cycles--;
    remdays -= ty_cycles * SOLS_PER_2Y;

    int remyears = remdays / 668;
    if (remyears == 2) remyears--;
    remdays -= remyears * 668;

    // Store this for later!
    int ysol = remdays; // TODO: Handle leap day in leap years

    // Stolen from musl
    int wsol = (3 + remdays) % 7;
	if (wsol < 0) wsol += 7;

    int years = remyears + (c_cycles * 100L) + (d_cycles * 10) + (ty_cycles * 2);

    // Now we go backwards
    for(months = 0; __sols_in_month[months] <= remdays; months++) {
        remdays -= __sols_in_month[months];
    }

    ret.mars_tm_year = years;
    // TODO: Test on other months, especially first and last
    ret.mars_tm_mon = months;
    ret.mars_tm_msol = remdays + 1;
    ret.mars_tm_wsol = wsol;
    ret.mars_tm_ysol = ysol;

    ret.mars_tm_min = (secs_into_day % 3600) / 60;
#ifdef HAVE_MPFR
    // define what we need according to the non-mpfr version below
    mpfr_t mtc, top, a, b, multwofourmsd, x, y, sixty, fin;
    mpfr_init(mtc);
    mpfr_init(top);
    mpfr_init(multwofourmsd);
    mpfr_init(x);
    mpfr_init(y);
    mpfr_init(fin);

    mpfr_init_set_d(a, (double)3600.0, MPFR_RNDN);
    mpfr_init_set_d(b, (double)24.0, MPFR_RNDN);
    mpfr_init_set_d(sixty, (double)60.0, MPFR_RNDN);
    mpfr_mul(multwofourmsd, msd, b, MPFR_RNDN);
    mpfr_fmod(mtc, multwofourmsd, b, MPFR_RNDN);

    mpfr_mul(x, mtc, a, MPFR_RNDN);
    mpfr_fmod(y, x, a, MPFR_RNDN);

    ret.mars_tm_hour = (int) mpfr_get_d(multwofourmsd, MPFR_RNDN) % 24;

    mpfr_fmod(fin, y, sixty, MPFR_RNDN);
    ret.mars_tm_sec = mpfr_get_d(fin, MPFR_RNDN); // why are we off by a second

#else
    // The source of marsclock.com does these calculations for MSD -> MTC.
    // For more precision, use fmod.
    // Whether to round these numbers or not.. still undecided.
    double mtc = fmod(24 * msd, 24);
    double x = mtc * 3600;

    ret.mars_tm_hour = (int) (24 * msd) % 24;     // from marsclock.com
    double y = fmod(x, 3600);
    ret.mars_tm_min = (secs_into_day % 3600) / 60;
    ret.mars_tm_sec = fmod(y, 60); // why are we off by a second
#endif


    ret.mars_tm_amtoff = 0;
    ret.mars_tm_zone = "MTC";
    return &ret;
}
