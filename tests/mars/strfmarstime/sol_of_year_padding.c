#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm_day1;
    tm_day1.mars_tm_msol = 0;

    struct mars_tm tm_day10;
    tm_day10.mars_tm_msol = 9;

    struct mars_tm tm_day100;
    tm_day100.mars_tm_msol = 99;

    char str[10];
    strfmarstime(str, sizeof(str), "%j", &tm_day1);
    printf("%s ", str);

    strfmarstime(str, sizeof(str), "%j", &tm_day10);
    printf("%s ", str);

    strfmarstime(str, sizeof(str), "%j", &tm_day100);
    printf("%s", str);
    return 0;
}
