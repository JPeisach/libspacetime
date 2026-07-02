#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{

    struct mars_tm solis;
    strpmarstime("Solis", "%A ", &solis);
    printf("%d ", solis.mars_tm_wsol);

    struct mars_tm lunae;
    strpmarstime("Lunae", "%A ", &lunae);
    printf("%d ", lunae.mars_tm_wsol);

    struct mars_tm martis;
    strpmarstime("Martis", "%A ", &martis);
    printf("%d ", martis.mars_tm_wsol);

    struct mars_tm mercurii;
    strpmarstime("Mercurii", "%A ", &mercurii);
    printf("%d ", mercurii.mars_tm_wsol);

    struct mars_tm jovis;
    strpmarstime("Jovis", "%A ", &jovis);
    printf("%d ", jovis.mars_tm_wsol);

    struct mars_tm veneris;
    strpmarstime("Veneris", "%A ", &veneris);
    printf("%d ", veneris.mars_tm_wsol);

    struct mars_tm saturni;
    strpmarstime("Saturni", "%A ", &saturni);
    printf("%d", saturni.mars_tm_wsol);

    return 0;
}
