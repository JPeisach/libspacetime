#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    wchar_t str[10];
    struct mars_tm tm;


    tm.mars_tm_year = 0;
    wcsfmarstime(str, sizeof(str), L"%C", &tm);
    printf("%ls ", str);

    tm.mars_tm_year = 100;
    wcsfmarstime(str, sizeof(str), L"%C", &tm);
    printf("%ls ", str);

    tm.mars_tm_year = 1000;
    wcsfmarstime(str, sizeof(str), L"%C", &tm);
    printf("%ls", str);

    return 0;
}
