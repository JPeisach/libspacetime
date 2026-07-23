#include "mars.h"

#include "../const.h"
#include <math.h>

#define SOLS_PER_100Y (66859) // Try to keep this, otherwise MSD 0 will be in the wrong place
// TODO: support 1000Y+

inline int is_leap_year(int year)
{
    if(year % 2 == 1) {
        return 1;
    }

    if(year % 10 == 0) {
        if(year % 100 == 0) {
            return 0;
        }
        return 1;
    }

    return 0;
}

// Space vs. time tradeoff for leap years.
static const int __sols_in_month[2][24] = {
    {28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 27},
    {28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 28},
};

// This is basically written based off of musl's secs_to_tm function.
// TODO: Testcases for this
struct mars_tm* ammarstime(const mars_time_t* timer)
{
    static struct mars_tm ret;
    int months;

    // First, get MSD (days)
    double msd = *timer / 86400.0;

    // seconds into day:
    // Hey kids, this is why you DON'T always trust AI!
    // If MSD is a fraction, we can literally use the remainder to determine how
    // much of the day is left in seconds.
    // After all, it's a whole out of 1.
    // I managed to reduce a whole second of error because of this. After I don't know how long of manual debugging.
    // int secs_into_day = *timer % SECONDS_PER_DAY;
    int secs_into_day = fmod(msd, 1) * 86400;

    // When we refer to Darian Calendar days, MSD 0 will be offset.
    // Make sure we start at the right epoch
    int days = ((int)msd + (8132745597 / SECONDS_PER_DAY));


    // Going based off how musl calculates secs to tm via "cycles"
    // Instead of 4Y -> 100Y -> 400Y, will do 2Y -> 10Y -> 100Y
    int c_cycles = days / SOLS_PER_100Y;
    int remdays = days;
    remdays -= c_cycles * SOLS_PER_100Y;

    // We can find the base year, and determine if the year after that is a leap or not.
    int years = (c_cycles * 100L);


    // ---------
    // The ammarstime story
    //
    // When I created the function, I did what I was doing for other
    // functions: basically recreate based off musl or glibc's
    // implementation.
    //
    // musl, for it's calculations, uses a "cycle" system, where
    // it takes the amount of seconds that have passed per 400 years,
    // then 100 years, then 4 years. This is consistent with Gregorian
    // Calendar leap year rules.
    //
    // For the Darian Calendar, this system does not quite work,
    // because the only constant cycles are decades and centuries.
    // Because the start of a decade year is a leap year (unless
    // divisible by 100), there could be three back-to-back leap years.
    // To confuse things even more, the handling of the "days per decade"
    // would lead to situations where an extra day would be added (such
    // as a false "25-01" day) or because of modulus boundaries, multiple
    // dates would share the same "24-28" or "01-01" day, and sometimes
    // days would be missing entirely.
    //
    // I've probably spent about 10 hours trying to debug this without
    // AI. I eventually folded and asked for what was wrong, and the
    // LLM suggested removing the "optimization" and calculating years
    // manually.
    //
    // This does in fact fix everything. It makes the current date
    // consistent. The only issue is that I thought MSD 0 started on
    // 140 Virgo 25, but it may actually be the 26. I'll need to check that.
    //
    // I spent a lot of time just trying to fix the issue and document
    // what the code was doing (because I didn't want to just plainly
    // copy and paste), but didn't really understand *why* I was doing
    // it this way. I was thinking too close minded. It's kind of a
    // shame an AI had to tell me.
    //
    // The "why" for the cycles, is really because you can prevent
    // loops (and probably save runtime) by trying to position the
    // offset by a cycle-system instead of manually looping through
    // everything.
    //
    // I will try to revisit this, but I want to get this library
    // released.
    // -July 23 2026
    //
    // Oh: And MSD 0 actually starts 3 minutes before 140 Virgo 26.
    // So that explains the confusion. Probably MSD offset above is
    // slightly off.
    //
    // TODO: Optimize.
    while(remdays >= 668) {
        int year_len = is_leap_year(years) ? 669 : 668;

        if (remdays < year_len)
            break;

        remdays -= year_len;
        years++;
    }

    int is_leap = is_leap_year(years);

    // Store this for later!
    int ysol = remdays; // TODO: Handle leap day in leap years if needed

    // Stolen from musl
    int wsol = (3 + remdays) % 7;
	if (wsol < 0) wsol += 7;


    // Now we go backwards
    for(months = 0; __sols_in_month[is_leap][months] <= remdays; months++) {
        remdays -= __sols_in_month[is_leap][months];
    }

    ret.mars_tm_year = years;
    ret.mars_tm_mon = months;
    ret.mars_tm_msol = remdays + 1;
    ret.mars_tm_wsol = wsol;
    ret.mars_tm_ysol = ysol;

    ret.mars_tm_hour = (int) (24 * msd) % 24;     // from marsclock.com
    ret.mars_tm_min = (secs_into_day % 3600) / 60;
    ret.mars_tm_sec = (secs_into_day % 60); // why are we off by a second

    ret.mars_tm_amtoff = 0;
    ret.mars_tm_zone = "MTC";
    return &ret;
}
