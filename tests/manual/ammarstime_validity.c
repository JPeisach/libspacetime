// This test will print every day since MSD 0.
// Using this, you can check to see if any dates are invalid.
#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>
#include <time.h>

int main()
{
    time_t a;
    time(&a);
    mars_time_t now = earth_time_to_mars_time(a);
    printf("%ld", now);

    for(mars_time_t marstime = 0; marstime < now; marstime += 86400)
    {
        struct mars_tm *tm = ammarstime(&marstime);
        char str[60];
        strfmarstime(str, 60, "%F %T", tm);
        printf("%s\n", str);
    }
    return 0;
}
