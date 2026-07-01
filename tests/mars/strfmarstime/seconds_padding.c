#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm_sec0;
    tm_sec0.mars_tm_sec = 0;

    struct mars_tm tm_sec10;
    tm_sec10.mars_tm_sec = 10;


    char str[10];
    strfmarstime(str, sizeof(str), "%S", &tm_sec0);
    printf("%s ", str);

    strfmarstime(str, sizeof(str), "%S", &tm_sec10);
    printf("%s", str);
    return 0;
}
