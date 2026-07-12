#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    struct mars_tm tm_day1;
    tm_day1.mars_tm_ysol = 0;

    struct mars_tm tm_day10;
    tm_day10.mars_tm_ysol = 9;

    struct mars_tm tm_day100;
    tm_day100.mars_tm_ysol = 99;

    wchar_t str[10];
    wcsfmarstime(str, sizeof(str), L"%j", &tm_day1);
    printf("%ls ", str);

    wcsfmarstime(str, sizeof(str), L"%j", &tm_day10);
    printf("%ls ", str);

    wcsfmarstime(str, sizeof(str), L"%j", &tm_day100);
    printf("%ls", str);
    return 0;
}
