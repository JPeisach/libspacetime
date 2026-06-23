#include "mars.h"

#include "../const.h"
#include "../earth.h"

inline double __do_earth_time_to_msd(time_t et)
{
    return ((et + TAI_OFFSET) / 88775.244147) + 34127.2954262;
}

inline mars_time_t __do_earth_time_to_mars_time(time_t et)
{
    // martian seconds
    return (mars_time_t) (__do_earth_time_to_msd(et) * SECONDS_PER_DAY);
}



mars_time_t mars_time(mars_time_t *timer)
{
    mars_time_t time = __do_earth_time_to_mars_time(earth_time());
    if(timer)
        *timer = time;

    return time;
}

time_t mars_time_to_earth_time(mars_time_t mars_time)
{
    // Martian Days. Try to keep precision
    double msd = mars_time / 86400.0;

    // Same steps in reverse
    double earth_time = (msd - 34127.2954262) * 88775.244147;

    // Subtract leap-second correction and cast to time_t (subtract first to match test expectations)
    return (time_t) (earth_time - TAI_OFFSET);
}

mars_time_t earth_time_to_mars_time(time_t et)
{
    return __do_earth_time_to_mars_time(et);
}
