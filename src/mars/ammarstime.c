#include "mars.h"

#include "../const.h"

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

    // First, get MSD (days)
    double msd = *timer / 86400.0;

    // asked google and used its AI results for equations
    // seconds into day:
    int secs_into_day = *timer % SECONDS_PER_DAY;


    // When we refer to Darian Calendar days, MSD 0 will be offset.
    // Make sure we start at the right epoch
    int days = ((int)msd + (8132745597 / SECONDS_PER_DAY));


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

    ret.mars_tm_hour = (int) (24.0 * msd) % 24;     // from marsclock.com
    ret.mars_tm_min = (secs_into_day % 3600) / 60;
    ret.mars_tm_sec = (*timer % 60); // why are we off by a second

    ret.mars_tm_amtoff = 0;
    ret.mars_tm_zone = "MTC";
    return &ret;
}
