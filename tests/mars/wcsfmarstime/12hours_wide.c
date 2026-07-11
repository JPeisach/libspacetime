#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    wchar_t str[10];
    struct mars_tm tm_lz;
    tm_lz.mars_tm_hour = 0; // Should show as 12

    wcsfmarstime(str, sizeof(str), L"%I", &tm_lz);
    printf("%ls ", str);

    struct mars_tm tm;
    tm.mars_tm_hour = 13; // Should show as 1
    wcsfmarstime(str, sizeof(str), L"%I", &tm);
    printf("%ls", str);
}
