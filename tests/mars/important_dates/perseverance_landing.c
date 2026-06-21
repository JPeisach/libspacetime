#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>
#include <time.h>

// February 18, 2021 20:55 UTC (TODO: Get more specific)
const time_t PERSEVERANCE_LANDING = (time_t) 1613681700;

int main() {
    mars_time_t mt = earth_time_to_mars_time(PERSEVERANCE_LANDING);

    int msd = (mt / 86400);
    printf("Perseverance landed - MSD %d", msd);

    return 0;
}
