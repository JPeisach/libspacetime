#include "mars.h"

#include "earth.h"
#include <stdio.h>

mars_time_t mars_time() {
    time_t et = earth_time();

    double msd = ((et + (37.0)) / 88775.244147) + 34127.2954262;

    return (mars_time_t) (msd * 86400);
}
