#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;
    tm.mars_tm_year = 1000;

    char str[10];
    strfmarstime(str, sizeof(str), "%C", &tm);

    printf("%s", str);
    return 0;
}
