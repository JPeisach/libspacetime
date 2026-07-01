#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    struct mars_tm tm;
    char str[10];
    strfmarstime(str, sizeof(str), "%t", &tm);
    printf("%s", str);
}
