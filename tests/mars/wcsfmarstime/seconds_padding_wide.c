#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    struct mars_tm tm_sec0;
    tm_sec0.mars_tm_sec = 0;

    struct mars_tm tm_sec10;
    tm_sec10.mars_tm_sec = 10;


    wchar_t str[10];
    wcsfmarstime(str, sizeof(str), L"%S", &tm_sec0);
    printf("%ls ", str);

    wcsfmarstime(str, sizeof(str), L"%S", &tm_sec10);
    printf("%ls", str);
    return 0;
}
