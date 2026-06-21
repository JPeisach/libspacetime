#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>

// Verify we can make the Unix Epoch - 1/1/1970 00:00:00 UTC
int main() {
    struct mars_tm mt;
    mt.mars_tm_sec = 57;
    mt.mars_tm_min = 5;
    mt.mars_tm_hour = 7;
    mt.mars_tm_msol = 26;
    mt.mars_tm_mon = 19;
    mt.mars_tm_year = 191;

    mars_time_t converted = mkmarstime(&mt);
    time_t epoch = mars_time_to_earth_time(converted);

    if(epoch == 0) return 0;

    printf("Epoch is not equivalent");
    return -1;
}
