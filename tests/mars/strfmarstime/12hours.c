#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[10];
    struct mars_tm tm_lz;
    tm_lz.mars_tm_hour = 0; // Should show up as 12
    strfmarstime(str, sizeof(str), "%I", &tm_lz);
    printf("%s ", str);

    struct mars_tm tm;
    tm.mars_tm_hour = 13; // Should show up as 1
    strfmarstime(str, sizeof(str), "%I", &tm);
    printf("%s", str);
    return 0;
}
