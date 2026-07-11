#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    wchar_t str[10];
    struct mars_tm singledigit;
    singledigit.mars_tm_year = 3;
    wcsfmarstime(str, sizeof(str), L"%Y", &singledigit);
    printf("%ls ", str);

    struct mars_tm doubledigit;
    doubledigit.mars_tm_year = 34;
    wcsfmarstime(str, sizeof(str), L"%Y", &doubledigit);
    printf("%ls ", str);

    struct mars_tm tripledigit;
    tripledigit.mars_tm_year = 345;
    wcsfmarstime(str, sizeof(str), L"%Y", &tripledigit);
    printf("%ls", str);
}
