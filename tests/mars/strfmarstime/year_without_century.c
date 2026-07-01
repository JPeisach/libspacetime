#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    char str[10];
    struct mars_tm singledigit;
    singledigit.mars_tm_year = 3;
    strfmarstime(str, sizeof(str), "%y", &singledigit);
    printf("%s ", str);

    struct mars_tm doubledigit;
    doubledigit.mars_tm_year = 34;
    strfmarstime(str, sizeof(str), "%y", &doubledigit);
    printf("%s ", str);

    struct mars_tm tripledigit;
    tripledigit.mars_tm_year = 345;
    strfmarstime(str, sizeof(str), "%y", &tripledigit);
    printf("%s", str);
}
