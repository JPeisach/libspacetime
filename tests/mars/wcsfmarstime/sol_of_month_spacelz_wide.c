#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    struct mars_tm tm_singledigit;
    tm_singledigit.mars_tm_msol = 3;
    tm_singledigit.mars_tm_mon = 2;

    struct mars_tm tm_doubledigit;
    tm_doubledigit.mars_tm_msol = 20;
    tm_doubledigit.mars_tm_mon = 2;

    wchar_t str[10];
    wcsfmarstime(str, sizeof(str), L"%e", &tm_singledigit);
    printf("%ls ", str);

    wcsfmarstime(str, sizeof(str), L"%e", &tm_doubledigit);
    printf("%ls", str);
    return 0;
}
