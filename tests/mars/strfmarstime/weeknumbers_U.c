#include <libspacetime/mars.h>
#include <stdio.h>

// %U = %V
int main()
{
    char str[16];

    struct mars_tm week0;
    week0.mars_tm_ysol = 0;
    week0.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%U", &week0);
    printf("%s ", str);

    struct mars_tm firstMonday;
    firstMonday.mars_tm_ysol = 1;
    firstMonday.mars_tm_wsol = 1;

    strfmarstime(str, sizeof(str), "%U", &firstMonday);
    printf("%s ", str);

    struct mars_tm week1;
    week1.mars_tm_ysol = 7;
    week1.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%U", &week1);
    printf("%s ", str);

    struct mars_tm secondMonday;
    secondMonday.mars_tm_ysol = 8;
    secondMonday.mars_tm_wsol = 1;

    strfmarstime(str, sizeof(str), "%U", &secondMonday);
    printf("%s ", str);

    // Season end alignment checks
    // Ensure last day of week is still 24
    struct mars_tm lastDayOfSeason;
    lastDayOfSeason.mars_tm_ysol = 166;
    lastDayOfSeason.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%U", &lastDayOfSeason);
    printf("%s ", str);

    // Ensure we can modulate once...
    struct mars_tm firstPisces;
    firstPisces.mars_tm_ysol = 167;
    firstPisces.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%U", &firstPisces);
    printf("%s ", str);

    // One more time for good measure
    struct mars_tm firstGemini;
    firstGemini.mars_tm_ysol = 334;
    firstGemini.mars_tm_wsol = 0;

    strfmarstime(str, sizeof(str), "%U", &firstGemini);
    printf("%s ", str);

    // Leap year
    struct mars_tm leapDay;
    leapDay.mars_tm_ysol = 668;
    leapDay.mars_tm_wsol = 6;

    strfmarstime(str, sizeof(str), "%U", &leapDay);
    printf("%s", str);
}
