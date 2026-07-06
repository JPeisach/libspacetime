#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    mars_time_t time = 4229236802;
    struct mars_tm* tm = ammarstime(&time);

    char str[100];
    strfmarstime(str, sizeof(str), "%F %T", tm);
    printf("%s", str);

    return 0;
}
