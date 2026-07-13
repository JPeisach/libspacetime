#include "mars_time_impl.h"
#include <stdlib.h>
#include <wchar.h>

size_t __wcsfmarstime(wchar_t *restrict s, size_t count, const wchar_t* restrict format, const struct mars_tm* restrict tm, locale_t locale)
{
    // Based off of musl's implementation of wcsftime.
    int padding, plus;
    char buf[100];
    wchar_t wbuf[100];
    wchar_t *p; // used in wcstoul
    unsigned long width; // musl uses unsigned long for this
    size_t i, outlen;
    size_t widechars;
    const char* item_nonwide; // musl calls this "t_mb"
    const wchar_t *item;

    // format++ moves to next character
    for(i = 0; i < count; format++) {
        // NULL check
        if(!*format) {
            s[i] = 0;
            return i;
        }

        // non-format character - copy over and move on
        if(*format != '%') {
            s[i++] = *format;
            continue;
        }

        // We have a %
        format++;

        // Reset padding
        padding = 0;

        // Padding specifier characters
        if(*format == '-' || *format == '_' || *format == '0') padding = *format++;

        // Zero padding character
        if((plus = (*format == '+'))) format++;

        // TODO: strfmarstime checks for digit before calling strtoul - why not check for digit before calling wcstoul?
        width = wcstoul(format, &p, 10);

        // only need two chars for these formats
        if(*p == 'C' || *p == 'F' || *p == 'G' || *p == 'Y') {
            // not sure what this is for tbh
            if(!width && p != format) width = 1;
        } else {
            width = 0;
        }

        // Also not sure why
        format = p;

        // "Two characters" (comment from strfmarstime)
        if(*format == 'E' || *format == 'O') format++;

        // Our item!
        item_nonwide = __strfmarstime_fmt_item(&buf, &outlen, *format, tm, locale, padding);
        if(!item_nonwide) break;

        // Convert to wide char
        outlen = mbstowcs(wbuf, item_nonwide, sizeof wbuf / sizeof *wbuf); // TODO: wrap in parens so the math is clear
        if(outlen == (size_t) -1) return 0; // If nothing, move on
        item = wbuf;

        if(width) {
            // More padding specifiers
            for(; *item == '+' || *item == '-' || (*item == '0' && item[1]); item++, outlen--);

            width--; // Not sure why we do this.

            // Specify + or -
            // Interestingly, in strfmarstime, we decrease width amounts
            // in the if statement. musl's wcsftime just does it by default.
            // Probably behaves the same way?
            if(plus && tm->mars_tm_year >= 0) {
                s[i++] = '+';
            } else if(tm->mars_tm_year < 0) {
                s[i++] = '-';
            } else {
                width++;
            }

            // Adding zeroes?
            for(; width > outlen && i < count; width--) {
                s[i++] = '0';
            }
        }

        // length fix?
        if(outlen >= count - i) outlen = count - i;

        // Copy item to string - but it's a  w i d e  memcpy
        wmemcpy(s + i, item, outlen);

        // Update position
        i += outlen;
    }

    if(count) {
        if(i == count) i = count - 1;

        // Terminating
        s[i] = 0;
    }

    return 0;
}

size_t wcsfmarstime(wchar_t *restrict wcs, size_t count, const wchar_t* restrict format, const struct mars_tm* restrict tm)
{
    // Just like strfmarstime, try to get the locale
    locale_t locale = newlocale(LC_ALL, setlocale(LC_ALL, ""), NULL);

    size_t ret = __wcsfmarstime(wcs, count, format, tm, locale);
    freelocale(locale);

    return ret;
}
