#include <math.h>
#include <stdlib.h>
#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>
#include <time.h>

int main() {
    time_t time = earth_time();
	printf("current earth epoch: %ld\n", time);

	mars_time_t mt = mars_time();
	printf("current mars epoch: %ld\n", mt);

    time_t mt_reconv = mars_time_to_earth_time(mt);
    printf("converted mars time to earth time: %ld\n", mt_reconv);
    return 0;
}
