#include <libspacetime/mars.h>
#include <stdio.h>
#include <wchar.h>

int main()
{
    struct mars_tm tm;
    wchar_t str[10];
    wcsfmarstime(str, sizeof(str), L"%t", &tm);
    printf("%ls", str);
}
