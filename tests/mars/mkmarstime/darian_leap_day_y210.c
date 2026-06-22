#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>

// Verify we can make Darian leap day conversion - 210 is a leap year
int main() {
    struct mars_tm mt;
    mt.mars_tm_sec = 0;
    mt.mars_tm_min = 0;
    mt.mars_tm_hour = 9;
    mt.mars_tm_msol = 28;
    mt.mars_tm_mon = 23;
    mt.mars_tm_year = 210;

    mars_time_t converted = mkmarstime(&mt);
    time_t darian_leap_day = mars_time_to_earth_time(converted);

    printf("darian_leap_day on Earth: %ld", darian_leap_day);
    return 0;
}
