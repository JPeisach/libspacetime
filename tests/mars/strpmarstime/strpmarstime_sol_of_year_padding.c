#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;

    strpmarstime("001", "%j", &tm);
    printf("%d ", tm.mars_tm_ysol);

    strpmarstime("010", "%j", &tm);
    printf("%d ", tm.mars_tm_ysol);

    strpmarstime("100", "%j", &tm);
    printf("%d", tm.mars_tm_ysol);

    return 0;
}
