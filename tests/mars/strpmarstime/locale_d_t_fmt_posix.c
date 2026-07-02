#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    // This test expects you are using POSIX locale
    char str[128];
    struct mars_tm tm;
    strpmarstime("Me Mak  4 09:06:07 205", "%c", &tm);

    // Test equivalence
    strfmarstime(str, sizeof(str), "%c", &tm);
    printf("%s", str);

    return 0;
}
