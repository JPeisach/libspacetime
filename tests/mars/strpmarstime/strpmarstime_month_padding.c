#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;

    strpmarstime("01", "%m", &tm);
    printf("%d ", tm.mars_tm_mon);

    strpmarstime("10", "%m", &tm);
    printf("%d", tm.mars_tm_mon);

    return 0;
}
