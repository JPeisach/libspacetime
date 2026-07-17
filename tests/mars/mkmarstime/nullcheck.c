#include <libspacetime/mars.h>
#include <stdio.h>

int main()
{
    mars_time_t out = mkmarstime(NULL);
    printf("%ld", out);

    return 0;
}
