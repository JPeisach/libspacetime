#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm_singledigit;
    tm_singledigit.mars_tm_msol = 3;
    tm_singledigit.mars_tm_mon = 2;

    struct mars_tm tm_doubledigit;
    tm_doubledigit.mars_tm_msol = 20;
    tm_doubledigit.mars_tm_mon = 2;

    char str[10];
    strfmarstime(str, sizeof(str), "%d", &tm_singledigit);
    printf("%s ", str);

    strfmarstime(str, sizeof(str), "%d", &tm_doubledigit);
    printf("%s", str);
    return 0;
}
