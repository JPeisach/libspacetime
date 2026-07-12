#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    struct mars_tm midnight;
    midnight.mars_tm_hour = 0;
    midnight.mars_tm_min = 0;
    midnight.mars_tm_sec = 0;

    struct mars_tm noon;
    noon.mars_tm_hour = 12;
    noon.mars_tm_min = 0;
    noon.mars_tm_sec = 0;

    wchar_t str[60];
    wcsfmarstime(str, 60, L"%r", &midnight);
    printf("%ls ", str);
    wcsfmarstime(str, 60, L"%r", &noon);
    printf("%ls", str);

    return 0;
}
