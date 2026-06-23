#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>

// Verify we can make MSD 0.
// This test may fail because the expected date may be calculated wrong
// This was before unix epoch so we just check value
int main() {
    struct mars_tm mt1;
    mt1.mars_tm_sec = 0;
    mt1.mars_tm_min = 0;
    mt1.mars_tm_hour = 1;
    mt1.mars_tm_msol = 2;
    mt1.mars_tm_mon = 1;
    mt1.mars_tm_year = 200;

    struct mars_tm mt2;
    mt2.mars_tm_sec = 0;
    mt2.mars_tm_min = 0;
    mt2.mars_tm_hour = 1;
    mt2.mars_tm_msol = 1;
    mt2.mars_tm_mon = 1;
    mt2.mars_tm_year = 200;

    mars_time_t converted1 = mkmarstime(&mt1);
    mars_time_t converted2 = mkmarstime(&mt2);

    double diff = diffmarstime(converted1, converted2);

    printf("Length of one sol: %lf", diff);

    return 0;
}
