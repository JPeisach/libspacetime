#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;
    strpmarstime("00", "%C", &tm);
    printf("%d ", tm.mars_tm_year);

    strpmarstime("01", "%C", &tm);
    printf("%d ", tm.mars_tm_year);

    strpmarstime("10", "%C", &tm);
    printf("%d", tm.mars_tm_year);
    return 0;
}
