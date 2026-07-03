#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm mt;

    strpmarstime("191-21-04", "%F", &mt);

    printf("Year %d Month %d Day %d", mt.mars_tm_year, mt.mars_tm_mon, mt.mars_tm_msol);

    return 0;
}
