#include "mars.h"

#include "earth.h"
#include <stdio.h>

mars_time_t mars_time() {
    time_t et = earth_time();

    double msd = ((et + (37.0)) / 88775.244147) + 34127.2954262;

    // martian seconds
    return (mars_time_t) (msd * 86400);
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
