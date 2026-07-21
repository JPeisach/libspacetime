#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    // 210 is a leap year because it is divisible by 10.
    // Let's check before for "decade" cycle
    mars_time_t time = 3998116802;
    struct mars_tm* tm = ammarstime(&time);

    char str[100];
    strfmarstime(str, sizeof(str), "%F %T", tm);
    printf("%s", str);

    return 0;
}
