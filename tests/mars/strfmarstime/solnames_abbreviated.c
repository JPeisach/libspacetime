#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[4];

    struct mars_tm solis;
    solis.mars_tm_wsol = 0;
    strfmarstime(str, 4, "%a ", &solis);
    printf("%s", str);

    struct mars_tm lunae;
    lunae.mars_tm_wsol = 1;
    strfmarstime(str, 4, "%a ", &lunae);
    printf("%s", str);

    struct mars_tm martis;
    martis.mars_tm_wsol = 2;
    strfmarstime(str, 4, "%a ", &martis);
    printf("%s", str);

    struct mars_tm mercurii;
    mercurii.mars_tm_wsol = 3;
    strfmarstime(str, 4, "%a ", &mercurii);
    printf("%s", str);

    struct mars_tm jovis;
    jovis.mars_tm_wsol = 4;
    strfmarstime(str, 4, "%a ", &jovis);
    printf("%s", str);

    struct mars_tm veneris;
    veneris.mars_tm_wsol = 5;
    strfmarstime(str, 4, "%a ", &veneris);
    printf("%s", str);

    struct mars_tm saturnis;
    saturnis.mars_tm_wsol = 6;
    strfmarstime(str, 4, "%a ", &saturnis);
    printf("%s", str);

    return 0;
}
