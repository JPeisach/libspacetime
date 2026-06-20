#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>
#include <time.h>

// November 13, 1971, 18:00 UTC
const time_t MARINER_9_ENTER_ORBIT = (time_t) 58903200;

int main() {
    mars_time_t mt = earth_time_to_mars_time(MARINER_9_ENTER_ORBIT);

    int msd = (mt / 86400);
    printf("Mariner 9 entered orbit - MSD %d", msd);

    return 0;
}
