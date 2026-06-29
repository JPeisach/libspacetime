#include "mars_time_impl.h"
#include <ctype.h>
#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ENABLE_NLS
#include "../gettext.h"
#include <libintl.h>
#include <locale.h>

#define N_(STRING) gettext_noop(STRING)
#else
#define N_(STRING) STRING
#endif

// TODO: Gettext strings will have this as an array for accessing the different locales, maybe?
static const char* month_names[24] = {
    N_("Sagittarius"), N_("Dhanus"), N_("Capricornus"), N_("Makara"), N_("Aquarius"), N_("Kumbha"), N_("Pisces"), N_("Mina"), N_("Aries"), N_("Mesha"), N_("Taurus"), N_("Rishabha"), N_("Gemini"), N_("Mithuna"), N_("Cancer"), N_("Karka"), N_("Leo"), N_("Simha"), N_("Virgo"), N_("Kanya"), N_("Libra"), N_("Tula"), N_("Scorpius"), N_("Vrishika")
};

static const char* abbreviated_month_names[24] = {
    N_("Sag"), N_("Dha"), N_("Cap"), N_("Mak"), N_("Aqu"), N_("Kum"), N_("Pis"), N_("Min"), N_("Ari"), N_("Mes"), N_("Tau"), N_("Ris"), N_("Gem"), N_("Mit"), N_("Can"), N_("Kar"), N_("Leo"), N_("Sim"), N_("Vir"), N_("Kan"), N_("Lib"), N_("Tul"), N_("Sco"), N_("Vri")
};

static const char* day_names[7] = {
    N_("Solis"), N_("Lunae"), N_("Martis"), N_("Mercurii"), N_("Jovis"), N_("Veneris"), N_("Saturni")
};

static const char* abbreviated_day_names[7] = {
    N_("So"), N_("Lu"), N_("Ma"), N_("Me"), N_("Jo"), N_("Ve"), N_("Sa")
};

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

        case 'e': // same but with space instead of leading 0
            def_pad = '_';
        case 'd': // Day of month
            val = tm->mars_tm_msol;
            goto number;

        // %m/%d/%y
        case 'D':
            fmt = "%m/%d/%y";
            goto to_strfmarstime;

        // TODO: %E
        // %Y-%m-%d
        case 'F':
            fmt = "%Y-%m-%d";
            goto to_strfmarstime;

        // ISO 8601 week-based year with century as a decimal number ("g" -> 2 digits).
        case 'g':
        case 'G':
            // TODO: Unimplemented for now.
            goto stringlen;

        // Hour using a 24 hr clock
        // TODO: %k
        case 'H':
            val = tm->mars_tm_hour;
            goto number;

        // Hour using 12 hr clock
        // TODO: %l
        case 'I':
            // AI suggested using modulus.. would be fine except 12:00 would go to 0
            val = tm->mars_tm_hour;
            if(val == 0) val = 12;
            else if(val > 12) val -= 12;
            goto number;

        // Sol of year
        case 'j':
            // TODO: musl adds +1 to this counter. Figure out if we need to do the same.
            val = tm->mars_tm_ysol;
            goto number;

        // Month
        case 'm':
            val = tm->mars_tm_mon;
            goto number;

        // Minute
        case 'M':
            val = tm->mars_tm_min;
            goto number;

        // Newline
        case 'n':
            // musl sets the length to 1 and just returns "\n". After all, we are done formatting.
            *len = 1;
            return "\n";

        // TODO: %O modifier

        // %p - AM or PM
        // TODO: %P, which is the same but in lowercase (need to find a way to do it with const char*)
        case 'p':
            fmt = nl_langinfo_l(tm->mars_tm_hour >= 12 ? PM_STR : AM_STR, locale);
            goto stringlen;

        // %r - "a.m. or p.m. notation"
        case 'r':
            // Also goes to strfmarstime call
            fmt = nl_langinfo_l(T_FMT_AMPM, locale);
            goto to_strfmarstime;

        // Time in 24hr notation (%H:%M)
        case 'R':
            fmt = "%H:%M";
            goto to_strfmarstime;

        // Martian Seconds since the Unix epoch.
        // FIXME: For now, will do time since the 1970-01-01 epoch, but in the future.. who knows. MSD 0 may be more relevant?
        case 's':
            // Says internally calculated from mk(mars)time.. do this for now
            // TODO: Timezones
            val = __mars_tm_to_secs(tm) - 2948598360;
            // Set width
            width = 1;
            goto number;

        // Martian seconds as decimal number
        case 'S':
            val = tm->mars_tm_sec;
            goto number;

        // Tab character
        case 't':
            // Same idea as \n
            *len = 1;
            return "\t";

        // Hour:Minute:Seconds format!
        case 'T':
            fmt = "%H:%M:%S";
            goto to_strfmarstime;

        // Day of week as decimal - Monday (Lunae) being 1
        case 'u':
            // Range from 1 to 7, not 0 to 6
            // Monday (Lunae) is 1, Sunday (Solis) is 7
            // Taking musl's strategy
            val = tm->mars_tm_wsol ? tm->mars_tm_wsol : 7;
            width = 1;
            goto number;

        // FIXME: Testing needed. These all have similar specifiers.
        // TODO: Meet these weird implementations
        // U: Week number of current year as a decimal - Sunday (in this case, Solis) is first day
        // V: ISO 8601 week number, where week 1 is first week of year with at least 4 days? (TODO: Find this edge case)
        // W: Week number of current year as a decimal - where Monday is first day (Sol Lunae)
        case 'U':
        case 'V':
        case 'W':
            val = tm->mars_tm_ysol / 7;
            goto number;

        // Day of week, with Sunday (Solis) being 0 (see %u)
        case 'w':
            val = tm->mars_tm_wsol;
            width = 1;
            goto number;

        // Preferred date for current locale without time
        case 'x':
            fmt = nl_langinfo_l(D_FMT, locale);
            goto to_strfmarstime;

        // Preferred time for current locale without date
        case 'X':
            fmt = nl_langinfo_l(T_FMT, locale);
            goto to_strfmarstime;

        // Year as decimal without century
        case 'y':
            val = tm->mars_tm_year % 100;
            goto number;

        // Year as decimal including century
        case 'Y':
            // FIXME: handle years above 999
            val = tm->mars_tm_year;
            width = 3; // for now.. :)
            goto number;

        // TODO: %z, %Z modifier (timezones)

        // Your good old % character.
        case '%':
            *len = 1;
            return "%";
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
    locale_t locale = newlocale(LC_ALL, setlocale(LC_ALL, ""), NULL);

    size_t ret = __strfmarstime(s, count, format, tm, locale);
    freelocale(locale);
    return ret;
}
