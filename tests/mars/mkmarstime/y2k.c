#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>

// Verify we can make Y2K - 1/1/00, 2000
int main() {
    struct mars_tm mt;
    mt.mars_tm_sec = 20;
    mt.mars_tm_min = 12;
    mt.mars_tm_hour = 3;
    mt.mars_tm_msol = 22;
    mt.mars_tm_mon = 18;
    mt.mars_tm_year = 207;

    mars_time_t converted = mkmarstime(&mt);
    time_t y2k = mars_time_to_earth_time(converted);

    printf("Y2K: %ld", y2k);
    return 0;
}
