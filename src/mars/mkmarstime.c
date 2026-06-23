#include "mars.h"

#include "../const.h"

// sols before the current month
// You can actually calculate this by doing (28*0, 28*1, 28*2...) and then adding 27*(m/4) for months
// but I just took values from first day of https://ops-alaska.com/time/gangale_converter/calendar_clock.htm
// sols before months 0..23 for a normal (non-leap) year
const int __mon_ysol[24] =
        {0, 28, 56, 84, 112, 140, 167, 195,
         223, 251, 279, 307, 334, 362, 390,
         418, 446, 474, 501, 529, 557, 585,
         613, 641};

mars_time_t mkmarstime(struct mars_tm* tm)
{
    mars_time_t ret = 0;

    // find number of leap years
    // Leap years: every odd number year OR if the year is divisible by 10 - unless its divisible by 100
    // intercalation:
    // ((y - 1) / 2) + (y/10) - (y/100) + (y/1000)

    // verified manually:
    //
    // 10 was a leap year, 20, etc. but not 100 - count the amount of times divisible by 10 and subtract by times divisible by 100
    // int decade_leap_years = (tm->mars_tm_year / 10) - (tm->mars_tm_year / 100);
    //
    // only even years are leap, and its only half of it - then add together for 1000
    // int odd_num_years = (tm->mars_tm_year - 1)
    //
    // This was later revised by review with AI - we are doing years since, not current year, so we need Y-1
    //
    // Count leap years before the given year using Darian intercalation rules.
    //
    // Closed-form equivalent: odd years + decades - centuries (all counts are for 1..Y-1)
    // L(Y) = floor(Y/2) + floor((Y-1)/10) - floor((Y-1)/100)
    mars_time_t leap_years = (mars_time_t) ((tm->mars_tm_year / 2) + ((tm->mars_tm_year - 1) / 10) - ((tm->mars_tm_year - 1) / 100) + ((tm->mars_tm_year - 1) / 1000));

    // 669 sols in a leap year, each sol has 86400 seconds
    ret += (leap_years * 669 * SECONDS_PER_DAY);

    // and the non-leap years
    ret += (tm->mars_tm_year - leap_years) * 668 * SECONDS_PER_DAY;

    // Months
    // So glibc has this thing where it looks up the amount of days before a month
    // and that is probably the strat.
    ret += (__mon_ysol[tm->mars_tm_mon] * SECONDS_PER_DAY);

    // leap days are just the last day of the year if its a leap year which is actually convenient
    // so we don't have to worry about it here
    ret += (tm->mars_tm_msol * SECONDS_PER_DAY);

    // Hours: 1hr*60min*60sec
    ret += (tm->mars_tm_hour * 3600);
    ret += (tm->mars_tm_min * 60);
    ret += (tm->mars_tm_sec);

    // Finally, subtract from the epoch
    // Darian calendar starts at gregorian date March 11 1609 18:40:34 UTC
    // This translates to being a difference of 11,385,983,966 seconds from when unix time started
    // If we take this martian seconds (8135164797) equivalent, you get time of 5329151639,
    // which is Nov 15 2138. Time between 1/1/1970 and 11/15/2138 is 168 years... so no correlation there (as far as I can tell)
    //
    // MSD 0 = "Midday Dec 29 1873" (marsclock.com)
    // Translates to 23:57:00, 25th of Virgo 140 but is behind by 177 martian seconds
    // Bumping forward brings you to:
    //
    // MSD 0:
    // Gregorian Date: 12:03:01 UTC, December 29 1873
    // Darian Date: 23:59:56 Airy, Virgo 25 140
    // It's possible this calculation could be incorrect due to conversion error
    // but it seems to match.
    // Epoch calibrated so MSD0 maps to 0
    return ret - 8132745597;
}
