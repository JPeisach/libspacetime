#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{

    struct mars_tm solis;
    strpmarstime("Solis", "%a ", &solis);
    printf("%d ", solis.mars_tm_wsol);

    struct mars_tm lunae;
    strpmarstime("Lunae", "%a ", &lunae);
    printf("%d ", lunae.mars_tm_wsol);

    struct mars_tm martis;
    strpmarstime("Martis", "%a ", &martis);
    printf("%d ", martis.mars_tm_wsol);

    struct mars_tm mercurii;
    strpmarstime("Mercurii", "%a ", &mercurii);
    printf("%d ", mercurii.mars_tm_wsol);

    struct mars_tm jovis;
    strpmarstime("Jovis", "%a ", &jovis);
    printf("%d ", jovis.mars_tm_wsol);

    struct mars_tm veneris;
    strpmarstime("Veneris", "%a ", &veneris);
    printf("%d ", veneris.mars_tm_wsol);

    struct mars_tm saturni;
    strpmarstime("Saturni", "%a ", &saturni);
    printf("%d", saturni.mars_tm_wsol);

    return 0;
}
