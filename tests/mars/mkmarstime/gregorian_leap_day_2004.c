#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>

// Verify we can make equivalence with a Gregorian Leap Day - 2004, midnight UTC
int main() {
    struct mars_tm mt;
    mt.mars_tm_sec = 27;
    mt.mars_tm_min = 9;
    mt.mars_tm_hour = 11;
    mt.mars_tm_msol = 24;
    mt.mars_tm_mon = 23;
    mt.mars_tm_year = 209;

    mars_time_t converted = mkmarstime(&mt);
    time_t leap_day = mars_time_to_earth_time(converted);

    printf("leap_day: %ld", leap_day);
    return 0;
}
