#include "mars.h"
#include <ctype.h>
#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implicit function declaration fix
size_t __strfmarstime(char* restrict s, size_t count, const char* restrict format, const struct mars_tm* restrict tm, locale_t locale);

// This will use musl's strftime, but with commented explanations so I can learn about what is happening.


// Format an individual item
// musl uses 100 for first argument length.
// TODO: do we need to call nl_langinfo for each?
const char* __strfmarstime_fmt_item(char (*str)[100], size_t *len, int op, const struct mars_tm *tm, locale_t locale, int pad)
{
    int item;
    long long val;
    const char *fmt = "-"; // musl defines this here.
    int width = 2, def_pad = '0';

    // TODO: Continue
    switch(op) {
        // Abbreviated name of day
        case 'a':
            if (tm->mars_tm_wsol > 6) goto stringlen; // validity check?
            fmt = abbreviated_day_names[tm->mars_tm_wsol];
            goto stringlen;

        // Full name of day
        case 'A':
            if (tm->mars_tm_wsol > 6) goto stringlen;
            fmt = day_names[tm->mars_tm_wsol];
            goto stringlen;


        // Abbreviated month name
        case 'h': // Equal to b
        case 'b':
            if(tm->mars_tm_mon > 23) goto stringlen;
            fmt = abbreviated_month_names[tm->mars_tm_mon];
            goto stringlen;

        // Full name of month
        case 'B':
            if(tm->mars_tm_mon > 23) goto stringlen;
            fmt = month_names[tm->mars_tm_mon];
            goto stringlen;

        // Preferred date and time from locale
        case 'c':
            // fmt will go a strfmarstime call (think of c as an alias for other formats)
            fmt = nl_langinfo_l(D_T_FMT, locale);
            goto to_strfmarstime;

        // Current century as 2-digit integers
        case 'C':
            val = (tm->mars_tm_year / 100);
            goto number;
    }

number:
    // Handle padding
    switch(pad ? pad : def_pad) {
        case '-':
            *len = snprintf(*str, sizeof *str, "%lld", val); break;
        case '_':
            *len = snprintf(*str, sizeof *str, "%*lld", width, val); break;  // Padding by the width variable
        case '0':
        default:
            *len = snprintf(*str, sizeof *str, "%0*lld", width, val); break;  // Zero padding
    }
    return *str;

stringlen:
    *len = strlen(fmt);
    return fmt;

to_strfmarstime:
    *len = __strfmarstime(*str, sizeof(*str), fmt, tm, locale);
    if(!*len) return 0;
    return *str;
}

size_t __strfmarstime(char* restrict s, size_t count, const char* restrict format, const struct mars_tm* restrict tm, locale_t locale)
{
    int padding, plus;
    char buf[100]; // we have our own buffer for some reason
    char *p; // used as an "endpointer" in strtoul
    unsigned long width; // musl uses an unsigned long for this type.
    const char *item;
    size_t outlen;
    size_t i; // ???

    // TODO: If count is too high (like, much higher than end length of str), we are SIGABRT'ing
    // count -> Length of string object
    // format++ -> goes to the next character of the string object (I learned this!) - in other language terms, its .substring(1, format.length())
    for(i = 0; i < count; format++) {
        // NULL check (format != NULL)
        if(!*format) {
            s[i] = 0;
            return i; // number of bytes
        }

        if(*format != '%') {
            // Non-operator character, copy it over.
            s[i++] = *format;
            continue;
        }

        // Move to next character (we have a %)
        format++;

        // Reset padding
        padding = 0;

        // Take the length of the separator character and add to padding?
        if (*format == '-' || *format == '_' || *format == '0') padding = *format++;

        // Zero padding (+) character
        if ((plus = (*format == '+'))) format++;

        // If given digit, determine how long the string will need to be (I'm assuming this is with the +)
        if (isdigit(*format)) {
            width = strtoul(format, &p, 10);
        } else {
            width = 0;
            p = (void*)format; // this will be *some* character
        }

        // We only need two chars for these formats
        if(*p == 'C' || *p == 'F' || *p == 'G' || *p == 'Y') {
            // I'm guessing !width checks we don't already have something waiting (e.g. %GG)
            if(!width && p != format) width = 1;
        } else {
            width = 0;
        }

        // Not sure what purpose of this is..
        format = p;

        // Two characters
        if(*format == 'E' || *format == 'O') format++;

        // Format an item
        item = __strfmarstime_fmt_item(&buf, &outlen, *format, tm, locale, padding);
        if(!item) break; // if nothing, move on.

        if(width) {
            // From comment in musl code: "Trim off any sign and leading zeroes, then count remaining digits to determine behavior fot the + flag."

            // Go through next characters of item - remove it from final len
            if(*item == '+' || *item == '-') item++, outlen--;

            // Count zeroes?
            for(; *item == '0' && item[1] - '0' < 10U; item++, outlen--);

            if(width < outlen) width = outlen;

            // Count digits
            size_t d;
            for(d = 0; item[d] - '0' < 10U; d++);
            if(tm->mars_tm_year < 0) {
                // TODO: Is this needed? In musl this checks if < -1900 (should always be false.)
                // My guess is that this inserts negative year values
                s[i++] = '-';
                width--;
            } else if(plus && d + (width - outlen) >= (*p == 'C' ? 3 : 5)) {  // Century number is a two digit number, if that's what this is?
                s[i++] = '+';
                width--;
            }
            for(; width > outlen && i < count; width--) {
                // Add zeroes?
                s[i++] = '0';
            }
        }

        // i'm guessing another length fix?
        if(outlen > count - i) outlen = count - i;

        // Copy the item to the string
        memcpy(s + i, item, outlen);

        // Increase char index?
        i += outlen;
    }

    if(count) {
        // Determine final str length
        if(i == count) i = count - 1;

        // Terminating char
        s[i] = 0;
    }

    return 0;
}

size_t strfmarstime(char* restrict s, size_t count, const char* restrict format, const struct mars_tm* restrict tm)
{
    // Use this to get the locale
    // TODO: Is there a better way to do this?
    locale_t locale = newlocale(LC_ALL, setlocale(LC_ALL, NULL), NULL);
    size_t ret = __strfmarstime(s, count, format, tm, locale);
    freelocale(locale);
    return ret;
}
