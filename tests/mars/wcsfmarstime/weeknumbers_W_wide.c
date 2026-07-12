#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    wchar_t str[16];

    struct mars_tm week0;
    week0.mars_tm_ysol = 0;
    week0.mars_tm_wsol = 0;

    wcsfmarstime(str, sizeof(str), L"%W", &week0);
    printf("%ls ", str);

    struct mars_tm firstMonday;
    firstMonday.mars_tm_ysol = 1;
    firstMonday.mars_tm_wsol = 1;

    wcsfmarstime(str, sizeof(str), L"%W", &firstMonday);
    printf("%ls ", str);

    struct mars_tm week1;
    week1.mars_tm_ysol = 7;
    week1.mars_tm_wsol = 0;

    wcsfmarstime(str, sizeof(str), L"%W", &week1);
    printf("%ls ", str);

    struct mars_tm secondMonday;
    secondMonday.mars_tm_ysol = 8;
    secondMonday.mars_tm_wsol = 1;

    wcsfmarstime(str, sizeof(str), L"%W", &secondMonday);
    printf("%ls ", str);

    // Season end alignment checks
    // Ensure last day of week is still 24
    struct mars_tm lastDayOfSeason;
    lastDayOfSeason.mars_tm_ysol = 166;
    lastDayOfSeason.mars_tm_wsol = 0;

    wcsfmarstime(str, sizeof(str), L"%W", &lastDayOfSeason);
    printf("%ls ", str);

    // Ensure we can modulate once...
    // For %W we are still in the 24th week
    struct mars_tm firstPisces;
    firstPisces.mars_tm_ysol = 167;
    firstPisces.mars_tm_wsol = 0;

    wcsfmarstime(str, sizeof(str), L"%W", &firstPisces);
    printf("%ls ", str);

    // One more time for good measure
    struct mars_tm firstGemini;
    firstGemini.mars_tm_ysol = 334;
    firstGemini.mars_tm_wsol = 0;

    wcsfmarstime(str, sizeof(str), L"%W", &firstGemini);
    printf("%ls ", str);

    // Leap year
    struct mars_tm leapDay;
    leapDay.mars_tm_ysol = 668;
    leapDay.mars_tm_wsol = 6;

    wcsfmarstime(str, sizeof(str), L"%W", &leapDay);
    printf("%ls", str);
}
