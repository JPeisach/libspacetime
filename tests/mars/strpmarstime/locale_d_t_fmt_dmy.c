#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    // This test expects you are using French locale
    char str[128];
    struct mars_tm tm;
    strpmarstime("Me 04 Mak 205 09:06:07", "%c", &tm);

    // Test equivalence
    strfmarstime(str, sizeof(str), "%c", &tm);
    printf("%s", str);

    return 0;
}
