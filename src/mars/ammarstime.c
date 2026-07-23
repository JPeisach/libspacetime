#include "mars.h"

#include "../const.h"
#include <math.h>

#define SOLS_PER_2Y (668 + 669)
#define SOLS_PER_10Y (668*10 + 6)
#define SOLS_PER_100Y (66859) // Keep this, otherwise MSD 0 will be in the wrong place
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

    // TODO: when decade year 0 is not a leap year
    int d_cycles = remdays / (SOLS_PER_10Y);
    if(remdays <= 6686) {
        // in the entire century, we are not past the
        // first decade, which has one less sol per 10y
        d_cycles = remdays / (SOLS_PER_10Y - 1);
        remdays -= d_cycles * (SOLS_PER_10Y - 1);
    } else {
        remdays -= d_cycles * SOLS_PER_10Y;
    }

    // unfortunately from here we are going to have to go by one
    // You see, in the Gregorian Calendar, every leap year is 4 years apart (2020-2016)
    // And for the years that aren't, it is divisible by 4 anyway (2104-2096) = 8
    // With the Darian Calendar, you can't guarantee this.
    // The distance between leap years can be 1 or 2.
    // So... closest place of normalcy is the decades.
    int single_years = 0;

    // We can find the base year, and determine if the year after that is a leap or not.
    int base_year = (c_cycles * 100L) + (d_cycles * 10L);
    int done_itering = 0;

    int can_leap_on_base_year = is_leap_year(base_year);

    // TODO: try to clean this up, I did try using a "base_leap_delta" but I think I still had weird things going on
    // Two cases
    // First, we are on a decade that does start with a leap year

    // FIXME: Still an extra day added.. (220-01-01)
    if(can_leap_on_base_year) {
        if(remdays >= 6685) {
            single_years += 10;
            remdays -= 6685;
        } else if(remdays >= 6017) {
            single_years += 9;
            remdays -= 6017;
        } else if(remdays >= 5349) {
            single_years += 8;
            remdays -= 5349;
        } else if(remdays >= 4680) {
            single_years += 7;
            remdays -= 4680;
        } else if(remdays >= 4012) {
            single_years += 6;
            remdays -= 4012;
        } else if(remdays >= 3343) {
            single_years += 5;
            remdays -= 3343;
        } else if(remdays >= 2675) {
            single_years += 4;
            remdays -= 2675;
        } else if(remdays >= 2006) {
            single_years += 3;
            remdays -= 2006;
        } else if(remdays >= 1338) {
            single_years += 2;
            remdays -= 1338;
        } else if (remdays >= 669) {
            single_years += 1;
            remdays -= 669;
        }
    } else {
        if(remdays >= 6685) {
            single_years += 10;
            remdays -= 6685;
        } else if(remdays >= 6016) {
            single_years += 9;
            remdays -= 6016;
        } else if(remdays >= 5348) {
            single_years += 8;
            remdays -= 5348;
        } else if(remdays >= 4679) {
            single_years += 7;
            remdays -= 4679;
        } else if(remdays >= 4011) {
            single_years += 6;
            remdays -= 4011;
        } else if(remdays >= 3342) {
            single_years += 5;
            remdays -= 3342;
        } else if(remdays >= 2674) {
            single_years += 4;
            remdays -= 2674;
        } else if(remdays >= 2005) {
            single_years += 3;
            remdays -= 2005;
        } else if(remdays >= 1337) {
            single_years += 2;
            remdays -= 1337;
        } else if (remdays >= 668) {
            single_years += 1;
            remdays -= 668;
        }
    }


    int years = single_years + base_year;
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
    // TODO: Test on other months, especially first and last
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
