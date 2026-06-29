#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;
    tm.mars_tm_mon = 3;
    tm.mars_tm_msol = 4;
    tm.mars_tm_hour = 9;
    tm.mars_tm_min = 6;
    tm.mars_tm_sec = 7;
    tm.mars_tm_wsol = 3;
    tm.mars_tm_year = 205;

    char str[128];
    strfmarstime(str, sizeof(str), "%c", &tm);
    printf("%s", str);

    return 0;
}
