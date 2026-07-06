#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>
#include <time.h>

// August 6, 2012 at 05:17:57
const time_t CURIOSITY_LANDING = (time_t) 1344230277;

int main() {
    mars_time_t mt = earth_time_to_mars_time(CURIOSITY_LANDING);

    int msd = (mt / 86400);
    printf("Curiosity landed - MSD %d", msd);

    return 0;
}
