#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[16];

    struct mars_tm solis;
    solis.mars_tm_wsol = 0;
    strfmarstime(str, 16, "%u ", &solis);
    printf("%s", str);

    struct mars_tm lunae;
    lunae.mars_tm_wsol = 1;
    strfmarstime(str, 16, "%u ", &lunae);
    printf("%s", str);

    struct mars_tm martis;
    martis.mars_tm_wsol = 2;
    strfmarstime(str, 16, "%u ", &martis);
    printf("%s", str);

    struct mars_tm mercurii;
    mercurii.mars_tm_wsol = 3;
    strfmarstime(str, 16, "%u ", &mercurii);
    printf("%s", str);

    struct mars_tm jovis;
    jovis.mars_tm_wsol = 4;
    strfmarstime(str, 16, "%u ", &jovis);
    printf("%s", str);

    struct mars_tm veneris;
    veneris.mars_tm_wsol = 5;
    strfmarstime(str, 16, "%u ", &veneris);
    printf("%s", str);

    struct mars_tm saturni;
    saturni.mars_tm_wsol = 6;
    strfmarstime(str, 16, "%u ", &saturni);
    printf("%s", str);

    return 0;
}
