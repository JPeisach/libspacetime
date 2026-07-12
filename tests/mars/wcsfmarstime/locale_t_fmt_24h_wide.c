#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    struct mars_tm tm;
    tm.mars_tm_mon = 2;
    tm.mars_tm_msol = 4;
    tm.mars_tm_hour = (12+9);
    tm.mars_tm_min = 6;
    tm.mars_tm_sec = 7;
    tm.mars_tm_wsol = 3;
    tm.mars_tm_year = 205;

    wchar_t str[128];
    wcsfmarstime(str, sizeof(str), L"%X", &tm);
    printf("%ls", str);

    return 0;
}
