#include <libspacetime/mars.h>
#include <stdio.h>

// TODO: All the features the "date" command in coreutils provides...
int main()
{
    mars_time_t time = mars_time(NULL);
    struct mars_tm* tm = ammarstime(&time);

    // FIXME: Get appropriate size, don't guess
    char buf[50];

    // Seems to be a default?
    strfmarstime(buf, sizeof(buf), "%a %b %e %H:%M:%S %Z %Y", tm);
    printf("%s", buf);

    return 0;
}
