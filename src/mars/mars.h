#include <time.h>

typedef time_t mars_time_t;

// Same as struct tm, but without timezones at the moment, and day is renamed to sol
// Of course, the range of values will depend on Darian calendar
struct mars_tm
{
    int mars_tm_sec; /* Seconds, 0-59 (TODO: leap seconds?) */
    int mars_tm_min; /* Minutes, 0-59 */
    int mars_tm_hour; /* Hours, 0-23 */
    int mars_tm_msol; /* Sol of month, 1-28 */
    int mars_tm_mon; /* Month, 0-23 (TODO: Why start at 0 instead of 1 like for day?) */
    int mars_tm_year; /* Year, should be decent to just throw it in, as of writing the year is only 221. */
    int mars_tm_wsol; /* Sol of week, 0-6 */
    int mars_tm_ysol; /* Sol of year, 0-668 */
};

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


mars_time_t mars_time(mars_time_t*);
time_t mars_time_to_earth_time(mars_time_t);
mars_time_t earth_time_to_mars_time(time_t);

double diffmarstime(mars_time_t, mars_time_t);

// (airy mean time instead of GMT)
struct mars_tm* ammarstime(const mars_time_t*);

mars_time_t mkmarstime(struct mars_tm*);

size_t strfmarstime(char* restrict, size_t, const char* restrict, const struct mars_tm* restrict);
