#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    struct mars_tm tm_mon1;
    tm_mon1.mars_tm_mon = 0;

    struct mars_tm tm_mon_10;
    tm_mon_10.mars_tm_mon = 9;

    wchar_t str[10];
    wcsfmarstime(str, sizeof(str), L"%m", &tm_mon1);
    printf("%ls ", str);

    wcsfmarstime(str, sizeof(str), L"%m", &tm_mon_10);
    printf("%ls", str);

    return 0;
}
