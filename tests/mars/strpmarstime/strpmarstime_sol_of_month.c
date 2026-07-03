#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;
    strpmarstime("03", "%d", &tm);
    printf("%d ", tm.mars_tm_msol);

    strpmarstime("21", "%d", &tm);
    printf("%d", tm.mars_tm_msol);

    return 0;
}
