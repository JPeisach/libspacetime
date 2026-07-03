#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;
    strpmarstime("02", "%H", &tm);
    printf("%d ", tm.mars_tm_hour);

    strpmarstime("14", "%H", &tm);
    printf("%d", tm.mars_tm_hour);
    return 0;
}
