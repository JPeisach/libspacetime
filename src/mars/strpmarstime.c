#include "mars.h"
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
char* __strpmarstime(const char *restrict str, const char *restrict format, struct mars_tm *restrict tm, locale_t locale);

// Using musl's implementation, while also commenting what is happening for learning purposes.
char* __strpmarstime(const char *restrict str, const char *restrict format, struct mars_tm *restrict tm, locale_t locale)
{
    // Values we will need later.
    int w, adj, neg, min, dummy, iteration_range, extracted_string_len, *tm_destination;
    const char* extracted_string;
    const char** iteration_array;  // We have to double up as we are pointing to an array of char

    // musl's handling of century: give its own vars
    int want_century = 0, century = 0, relyear = 0;

    size_t i;

    // This goes through each character of the string
    while (*format) {
        // This isn't a formatter character
        if (*format != '%') {
            if(isspace(*format)) {
                // Keep going along until we are not at a space character
                for(; *str && isspace(*str); str++);
            } else if(*str != *format) return 0; // TODO: Not sure what the purpose is here. Are we checking that we are done? This isn't a space character.
            else str++; // This is basically the equivalent of str.substring(1) - basically, proceed to the next character.
            format++; // Again, proceed to next character
            continue; // Check on loop again
        }

        format++;  // We are now at a % character
        if(*format == '+') format++;  // + operator, most likely for padding

        if(isdigit(*format)) {
            // Get the number - we need to read to a temp variable
            char *new_format;
            w = strtoul(format, &new_format, 10);
            format = new_format;
        } else {
            w = -1;  // Unused?
        }

        adj = 0; // TODO: ???

        // Start parsing items
        switch(*format++) {
            // Name of day of week, abbreviated
            case 'a':
                tm_destination = &tm->mars_tm_wsol;
                iteration_range = 7;
                iteration_array = abbreviated_day_names;

                goto symbolic_range;

            // Name of day of week
            case 'A':
                tm_destination = &tm->mars_tm_wsol;
                iteration_range = 7;
                iteration_array = day_names;

                goto symbolic_range;


            // Name of month, abbreviated
            case 'h':
            case 'b':
                tm_destination = &tm->mars_tm_mon;
                iteration_range = 24;
                iteration_array = abbreviated_month_names;

                goto symbolic_range;

            // Name of month
            case 'B':
                tm_destination = &tm->mars_tm_mon;
                iteration_range = 24;
                iteration_array = month_names;

                goto symbolic_range;

            // Preferred date and time from locale
            // musl does something clever: in strftime, it calls itself since this is really just a combination of formats
            // so we can o the same here
            case 'c':
                str = __strpmarstime(str, nl_langinfo_l(D_T_FMT, locale), tm, locale);
                if (!*str) return 0;
                break;

            // Current century as 2-digit integers
            case 'C':
                tm_destination = &century;
                if(w < 0) w = 2;
                want_century |= 2; // Signal we want 2 digit century

            // Sol of month
            case 'd':
            case 'e':
                tm_destination = &tm->mars_tm_msol;
                min = 1;
                iteration_range = 28;
                goto numeric_range;

            // %m/%d/%y
            case 'D':
                str = __strpmarstime(str, "%m/%d/%y", tm, locale);
                if(!str) return 0;
                break;

            // attempt to match with %Y-%m-%d
            case 'F':
                // From musl code:
                // "Use temp buffer to implement the odd requirement that entire field be width-limited but the year subfield not itself be limited"
                i = 0;
                char tmp[20];
                if(*str == '-' || *str == '+') tmp[i++] = *str++; // Move past +/- sign

                while(*str == '0' && isdigit(str[1])) str++; // keep moving until digit (zero padding?)
                for(; *str && i < (size_t)w && i + 1 < sizeof tmp; i++) {
                    tmp[i] = *str++;  // copying to buffer
                }
                tmp[i] = 0; // null terminate

                // TODO: Moved from %12Y to %24Y - see if still works
                char *p = __strpmarstime(tmp, "%24Y-%m-%d", tm, locale);
                if(!p) return 0;
                str -= tmp + i - p; // remove what we found already(?)
                break;

            // Hour (24hr)
            case 'H':
                tm_destination = &tm->mars_tm_hour;
                min = 0;
                iteration_range = 24;
                goto numeric_range;

            // Expressed as 12hr
            case 'I':
                tm_destination = &tm->mars_tm_hour;
                min = 1;
                iteration_range = 12;
                goto numeric_range;

            // Sol
            case 'j':
                tm_destination = &tm->mars_tm_ysol;
                min = 1;
                iteration_range = 668; // TODO: check leap year
                adj = 1;
                goto numeric_range;

            // Month
            case 'm':
                tm_destination = &tm->mars_tm_mon;
                min = 1;
                iteration_range = 24;
                adj = 1;
                goto numeric_range;

            // Minute
            case 'M':
                tm_destination = &tm->mars_tm_min;
                min = 0;
                iteration_range = 60;
                goto numeric_range;

            // Newline and tab characters; do nothing, just move past it
            case 'n':
            case 't':
                for(; *str && isspace(*str); str++);
                break;

            // AM or PM
            case 'p':
                extracted_string = nl_langinfo_l(AM_STR, locale);
                extracted_string_len = strlen(extracted_string);

                // See if we got this
                if(!strncasecmp(str, extracted_string, extracted_string_len)) {
                    tm->mars_tm_hour %= 12;
                    str += extracted_string_len;
                    break;
                }

                extracted_string = nl_langinfo_l(PM_STR, locale);
                extracted_string_len = strlen(extracted_string);

                // Also the modulus
                if(!strncasecmp(str, extracted_string, extracted_string_len)) {
                    tm->mars_tm_hour %= 12;
                    tm->mars_tm_hour += 12;
                    str += extracted_string_len;
                    break;
                }
                return 0;

            // AM or PM
            case 'r':
                str = __strpmarstime(str, nl_langinfo_l(T_FMT_AMPM, locale), tm, locale);
                if(!str) return 0;
                break;

            case 'R':
                str = __strpmarstime(str, "%H:%M", tm, locale);
                if(!str) return 0;
                break;

            // Parse only - musl says "effect on tm is unspecified"
            case 's':
                if(*str == '-') str++;
                if(!isdigit(*str)) return 0;
                while(!isdigit(*str)) str++;
                break;

            // Seconds
            case 'S':
                tm_destination = &tm->mars_tm_sec;
                min = 0;
                iteration_range = 60;
                goto numeric_range;

            // H:M:S
            case 'T':
                str = __strpmarstime(str, "%H:%M:%S", tm, locale);
                if(!str) return 0;
                break;

            // Week number shenanigans..
            // TODO: Come back to this and test because there are different standards on counting week numbers
            // Heck, even in musl it says "Throw away result of %U, %V, %W, %g and %G" due to "No clear right choice"
            case 'U':
            case 'W':
                tm_destination = &dummy;
                min = 0;
                iteration_range = 86;
                goto numeric_range;
            case 'V':
                tm_destination = &dummy;
                min = 1;
                iteration_range = 85;
                goto numeric_range;
            case 'g':
                tm_destination = &dummy;
                w = 2;
                goto numeric_digits;
            case 'G':
                tm_destination = &dummy;
                if(w < 0) w = 4; // not sure how this is possible but sure
                goto numeric_digits;

            // Weeksol but counted at 1
            case 'u':
                tm_destination = &tm->mars_tm_wsol;
                min = 1;
                iteration_range = 7;
                goto numeric_range;

            // Weeksol but count starts at 0. Again, TODO for checking this.
            case 'w':
                tm_destination = &tm->mars_tm_wsol;
                min = 0;
                iteration_range = 7;
                goto numeric_range;

            // Date format
            case 'x':
                str = __strpmarstime(str, nl_langinfo_l(D_FMT, locale), tm, locale);
                if(!str) return 0;
                break;

            // Time format
            case 'X':
                str = __strpmarstime(str, nl_langinfo_l(T_FMT, locale), tm, locale);
                if(!str) return 0;
                break;

            // Year
            case 'y':
                tm_destination = &relyear; // Relative year - TODO: may not be needed since we just store since year 0
                w = 2;
                want_century |= 1;
                goto numeric_digits;

            case 'Y':
                tm_destination = &tm->mars_tm_year;
                if(w < 0) w = 4;
                adj = 0; // TODO: Maybe we can remove things if we are just counting years since 0 instead of 1900
                want_century = 0; // TODO: check
                goto numeric_digits;

            // Timezones. Unimplemented for now:
            case 'z':
                // Calculate the offset

                // Negative or positive, nothing crazy
                if(*str == '+') neg = 0;
                else if(*str == '-') neg = 1;
                else return 0; // I believe it would have to be +00:00 if none

                // Number validation checks. I assume the extra 1 is after for the + or - character.
                for(i = 0; i < 4; i++) {
                    if(!isdigit(str[1 + i])) return 0;
                }

                // actual math
                // Notes:
                // Not sure what the - '0' is for
                // Anyways: Math appears to be matching by tens digit of hour -> then hour -> tens digit of minutes -> minutes
                tm->mars_tm_amtoff = (str[1] - '0') * 36000 + (str[2] - '0') * 3600 + (str[3] - '0') * 600 + (str[4] - '0') * 60;

                // If negative, account for that
                if(neg) tm->mars_tm_amtoff = -tm->mars_tm_amtoff;

                // Next characters afterwards
                str += 5;
                break;

            // Timezone name.
            // FIXME: Check on what to do here.
            case 'Z':
                // glibc does no action
                // musl checks to see if DST
                // for now, no-op.
                break;

            // % character
            case '%':
                if(*str++ != '%') return 0;
                break;
            default:
                return 0;
            numeric_range:
                // i'm skeptical this will work
                if(!isdigit(*str)) return 0;
                *tm_destination = 0;
                for(i = 1; i <= min + iteration_range && isdigit(*str); i *= 10) {
                    *tm_destination = *tm_destination * 10 + *str++ - '0';
                }
                // unsigned?
                if (*tm_destination - min >= (unsigned)iteration_range) return 0; // another bound check
                *tm_destination -= adj;
                // ????????
                // switch((char*)tm_destination - (char*)tm) {
                //     case offsetof(struct mars_tm, tm_ysol):
                //         ;
                // }
                goto cont;
            numeric_digits:
                neg = 0;
                if(*str == '+') str++; // + op -> move on
                else if(*str == '-') neg = 1, str++;

                if(!isdigit(*str)) return 0; // We shouldn't get here anyway

                for(*tm_destination = i = 0; i < w && isdigit(*str); i++) {
                    *tm_destination = *tm_destination * 10 + *str++ - '0'; // I guess just the multiply by ten? Not sure how it will help with other values
                }
                if (neg) *tm_destination = -*tm_destination;
                *tm_destination -= adj;
                goto cont;
            symbolic_range:
                // musl uses a goto statement, which uses nl_langinfo to look through the possible entries and see if the string we are looking for fits
                // however I don't think we have "domain addresses" like the ABDAY_1 constant. We might, but until then, manually assign an array to iter
                // TODO: See if we can have an nl_item lookup equivalent for this.
                // Another interesting note: I think musl does the lookup.. in reverse order? Is there a benefit to this?
                for(i = 0; i < iteration_range; i++) {
                    extracted_string = iteration_array[i];
                    extracted_string_len = strlen(extracted_string);
                    if(strncasecmp(str, extracted_string, extracted_string_len)) continue; // If this is a mismatch, check the next item.

                    // At this point we found it:
                    str += extracted_string_len;
                    *tm_destination = i;
                    break;
                }
            cont:
                // musl has a FIXME here
                ;
        }
    }
    if(want_century) {
        tm->mars_tm_year = relyear;
        if(want_century & 2) {
            tm->mars_tm_year += century * 100;
        }
        // musl then has handling to bump year by 100 for if before 2038, probably unneeded here.
    }
    return (char*)str;
}


char* strpmarstime(const char *restrict str, const char *restrict format, struct mars_tm *restrict tm)
{
    // Use this to get the locale
    locale_t locale = newlocale(LC_ALL, setlocale(LC_ALL, ""), NULL);

    char* ret = __strpmarstime(str, format, tm, locale);
    freelocale(locale);
    return ret;
}
