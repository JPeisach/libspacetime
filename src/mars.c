#include "mars.h"

#include "earth.h"
#include <stdio.h>

inline mars_time_t __do_earth_time_to_mars_time(time_t et)
{
    double msd = ((et + (37.0)) / 88775.244147) + 34127.2954262;

    // martian seconds
    return (mars_time_t) (msd * 86400);
}

mars_time_t mars_time() {
    return __do_earth_time_to_mars_time(earth_time());
}

time_t mars_time_to_earth_time(mars_time_t mars_time)
{
    // Martian Days. Try to keep precision
    double msd = mars_time / 86400.0;

    // Same steps in reverse
    double earth_time = (msd - 34127.2954262) * 88775.244147;

    // FIXME: we appear to lose about one second of earth time
    return (time_t) earth_time - 37.0;
}

mars_time_t earth_time_to_mars_time(time_t et)
{
    return __do_earth_time_to_mars_time(et);
}
