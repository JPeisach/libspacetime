#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[16];

    struct mars_tm week0;
    week0.mars_tm_ysol = 0;
    week0.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%W", &week0);
    printf("%s ", str);

    struct mars_tm firstMonday;
    firstMonday.mars_tm_ysol = 1;
    firstMonday.mars_tm_wsol = 1;

    strfmarstime(str, sizeof(str), "%W", &firstMonday);
    printf("%s ", str);

    struct mars_tm week1;
    week1.mars_tm_ysol = 7;
    week1.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%W", &week1);
    printf("%s ", str);

    struct mars_tm secondMonday;
    secondMonday.mars_tm_ysol = 8;
    secondMonday.mars_tm_wsol = 1;

    strfmarstime(str, sizeof(str), "%W", &secondMonday);
    printf("%s ", str);

    // Season end alignment checks
    // Ensure last day of week is still 24
    struct mars_tm lastDayOfSeason;
    lastDayOfSeason.mars_tm_ysol = 166;
    lastDayOfSeason.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%W", &lastDayOfSeason);
    printf("%s ", str);

    // Ensure we can modulate once...
    // For %W we are still in the 24th week
    struct mars_tm firstPisces;
    firstPisces.mars_tm_ysol = 167;
    firstPisces.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%W", &firstPisces);
    printf("%s ", str);

    // One more time for good measure
    struct mars_tm firstGemini;
    firstGemini.mars_tm_ysol = 334;
    firstGemini.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%W", &firstGemini);
    printf("%s ", str);

    // Leap year
    struct mars_tm leapDay;
    leapDay.mars_tm_ysol = 668;
    leapDay.mars_tm_wsol = 6;

    strfmarstime(str, sizeof(str), "%W", &leapDay);
    printf("%s", str);
}
