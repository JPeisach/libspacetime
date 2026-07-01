#include <libspacetime/mars.h>
#include <stdio.h>

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

    char str[60];
    strfmarstime(str, 60, "%r", &midnight);
    printf("%s ", str);
    strfmarstime(str, 60, "%r", &noon);
    printf("%s", str);

    return 0;
}
