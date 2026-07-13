#include <libspacetime/mars.h>
#include <stdio.h>
#include <unistd.h>

// TODO: All the features the "date" command in coreutils provides...
int main(int argc, char** argv)
{
    mars_time_t time = mars_time(NULL);
    struct mars_tm* tm = ammarstime(&time);
    char* format = "%a %b %e %H:%M:%S %Z %Y";  // Seems to be a default?

    // FIXME: Get appropriate size, don't guess
    char buf[50];

    int optc;
    while((optc = getopt(argc, argv, "IR")) != -1) {
        switch(optc) {
            case 'I':
                // ISO 8601 format
                format = "%Y-%m-%d";
                break;
            case 'R':
                // RFC 5322 format
                format = "%a, %d %b %Y %H:%M:%S %z";
                break;
        }
    }

    strfmarstime(buf, sizeof(buf), format, tm);
    printf("%s", buf);

    return 0;
}
