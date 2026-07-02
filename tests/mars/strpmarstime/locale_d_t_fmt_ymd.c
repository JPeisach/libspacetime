#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    // This test expects you are using Hungarian locale
    char str[128];
    struct mars_tm tm;
    strpmarstime("205. Mak. 4., Mercurii, 09:06:07 MTC", "%c", &tm);

    // Test equivalence
    strfmarstime(str, sizeof(str), "%c", &tm);
    printf("%s", str);

    return 0;
}
