#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    wchar_t str[10];
    struct mars_tm tm_lz;
    tm_lz.mars_tm_hour = 2;
    wcsfmarstime(str, sizeof(str), L"%H", &tm_lz);
    printf("%ls ", str);

    struct mars_tm tm;
    tm.mars_tm_hour = 14;
    wcsfmarstime(str, sizeof(str), L"%H", &tm);
    printf("%ls", str);

    return 0;
}
