#include <libspacetime/mars.h>
#include <stdio.h>

// 212 was not a leap year.
// Make sure that we go into 213 and not a fake leap day of 212
int main()
{
    // This is actually of 1 Sagittarius 213. If it is correct, it would show so.
    // But if ammarstime thinks it's a leap year, it would show "28 Vrishka"
    mars_time_t time = 4171478402;
    struct mars_tm* tm = ammarstime(&time);

    char str[100];
    strfmarstime(str, sizeof(str), "%F %T", tm);
    printf("%s", str);

    return 0;
}
