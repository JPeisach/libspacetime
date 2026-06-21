#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>

// Verify we can make Y2038, just after - 1/1/38, 03:14:08 UTC
int main() {
    struct mars_tm mt;
    mt.mars_tm_sec = 10;
    mt.mars_tm_min = 56;
    mt.mars_tm_hour = 9;
    mt.mars_tm_msol = 8;
    mt.mars_tm_mon = 0;
    mt.mars_tm_year = 228;

    mars_time_t converted = mkmarstime(&mt);
    time_t y2038_post = mars_time_to_earth_time(converted);

    printf("Post Y2038: %ld", y2038_post);
    return 0;
}
