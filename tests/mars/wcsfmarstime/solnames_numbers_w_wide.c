#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    wchar_t str[16];

    struct mars_tm solis;
    solis.mars_tm_wsol = 0;
    wcsfmarstime(str, 16, L"%w ", &solis);
    printf("%ls", str);

    struct mars_tm lunae;
    lunae.mars_tm_wsol = 1;
    wcsfmarstime(str, 16, L"%w ", &lunae);
    printf("%ls", str);

    struct mars_tm martis;
    martis.mars_tm_wsol = 2;
    wcsfmarstime(str, 16, L"%w ", &martis);
    printf("%ls", str);

    struct mars_tm mercurii;
    mercurii.mars_tm_wsol = 3;
    wcsfmarstime(str, 16, L"%w ", &mercurii);
    printf("%ls", str);

    struct mars_tm jovis;
    jovis.mars_tm_wsol = 4;
    wcsfmarstime(str, 16, L"%w ", &jovis);
    printf("%ls", str);

    struct mars_tm veneris;
    veneris.mars_tm_wsol = 5;
    wcsfmarstime(str, 16, L"%w ", &veneris);
    printf("%ls", str);

    struct mars_tm saturni;
    saturni.mars_tm_wsol = 6;
    wcsfmarstime(str, 16, L"%w ", &saturni);
    printf("%ls", str);

    return 0;
}
