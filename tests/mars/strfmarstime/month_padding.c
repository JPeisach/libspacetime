#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm_mon1;
    tm_mon1.mars_tm_mon = 0;

    struct mars_tm tm_mon_10;
    tm_mon_10.mars_tm_mon = 9;

    char str[10];
    strfmarstime(str, sizeof(str), "%m", &tm_mon1);
    printf("%s ", str);

    strfmarstime(str, sizeof(str), "%m", &tm_mon_10);
    printf("%s", str);

    return 0;
}
