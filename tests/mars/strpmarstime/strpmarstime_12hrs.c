#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;
    strpmarstime("0", "%I", &tm);
    printf("%d ", tm.mars_tm_hour);


    strpmarstime("12", "%I", &tm);
    printf("%d", tm.mars_tm_hour);

    // There's really no way to check AM vs PM..
    // strpmarstime("13", "%I", &tm);
    // printf("%d", tm.mars_tm_hour);
    return 0;
}
