#include "mars.h"

#include "../const.h"
#include "../earth.h"

// Calculate the MSD (Mars Sol Date) given the amount of seconds since the Unix Epoch
double earth_time_to_msd(time_t et)
{
    // First, adjust by leap seconds offset
    // 88775.244147 comes from 86400 (Earth seconds per day) * 1.02749 (Martian seconds in one Earth second - there are more digits to this number)
    // 34127.2954262 comes from.. somewhere, but it keeps MSD 0 at "midday December 29th 1873" (marsclock.com)
    return ((et + TAI_OFFSET) / 88775.244147) + 34127.2954262;
}

inline mars_time_t __do_earth_time_to_mars_time(time_t et)
{
    // Given MSD, multiply by seconds to per day to get the number of Martian seconds.
    return (mars_time_t) (earth_time_to_msd(et) * SECONDS_PER_DAY);
}


// Returns the current Martian time, and writes it to timer if timer is not NULL.
mars_time_t mars_time(mars_time_t *timer)
{
    mars_time_t time = __do_earth_time_to_mars_time(earth_time());
    if(timer)
        *timer = time;

    return time;
}

// Converts Martian time to Earth time.
time_t mars_time_to_earth_time(mars_time_t mars_time)
{
    // Martian Days. Try to keep precision
    double msd = mars_time / 86400.0;

    // Same steps in reverse
    double earth_time = (msd - 34127.2954262) * 88775.244147;

    // Subtract leap-second correction and cast to time_t (subtract first to match test expectations)
    return (time_t) (earth_time - TAI_OFFSET);
}

// Converts Earth time to Martian time, given seconds from the unix epoch.
mars_time_t earth_time_to_mars_time(time_t et)
{
    return __do_earth_time_to_mars_time(et);
}
