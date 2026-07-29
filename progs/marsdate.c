#include "mars/mars.h"
#include <getopt.h>
#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <unistd.h>

// TODO: All the features the "date" command in coreutils provides...
int main(int argc, char** argv)
{
    mars_time_t time = mars_time(NULL);
    struct mars_tm* tm = ammarstime(&time);
    char* format = nl_langinfo(_DATE_FMT);

    // FIXME: Get appropriate size, don't guess
    char buf[128];

    setlocale(LC_ALL, "");

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

    // If there are other stuff left to parse its either info to set
    // date (or use as a base for formatting?), or define format.
    // (util-linux seems to check this, and this is my first time using
    // optind)
    if(argc > optind) {
        // Rule of the date command that I learned (feels weird to be
        // making a program based off one I don't know how to use) -
        // a + must be the only choice
        // Learning by example proves to be useful once again.
        if(argc > optind + 1) {
            printf("marsdate: extra operand '%s'", argv[optind + 1]);
            return 1;
        }

        if(argv[optind][0] == '+') {
            // got a %, let rest of input be the format
            // util-linux does this.
            // the optind++ makes sense, I guess, to ensure the index is kept accurate
            // the +1 is to get to the character after the +
            format = argv[optind++] + 1;
        }
    }

    if(!format) {
        // done in util-linux for a case when LC_ALL is unset and LANG
        // is Korean
        // https://github.com/coreutils/coreutils/blob/04befb136a7f1c50b18be322995f3a2906d41e74/src/date.c#L715
        format = "%a %b %e %H:%M:%S %Z %Y";
    }

    strfmarstime(buf, sizeof(buf), format, tm);
    printf("%s\n", buf);

    return 0;
}
