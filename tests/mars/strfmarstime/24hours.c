#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[10];
    struct mars_tm tm_lz;
    tm_lz.mars_tm_hour = 2;
    strfmarstime(str, sizeof(str), "%H", &tm_lz);
    printf("%s ", str);

    struct mars_tm tm;
    tm.mars_tm_hour = 14;
    strfmarstime(str, sizeof(str), "%H", &tm);
    printf("%s", str);
    return 0;
}
