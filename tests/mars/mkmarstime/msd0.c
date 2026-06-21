#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>

// Verify we can make MSD 0.
// This test may fail because the expected date may be calculated wrong
int main() {
    struct mars_tm mt;
    mt.mars_tm_sec = 57;
    mt.mars_tm_min = 59;
    mt.mars_tm_hour = 23;
    mt.mars_tm_msol = 25;
    mt.mars_tm_mon = 18;
    mt.mars_tm_year = 140;

    mars_time_t converted = mkmarstime(&mt);
    printf("MSD 0: %ld", converted);

    if(converted == 0) return 0;

    return -1;
}
