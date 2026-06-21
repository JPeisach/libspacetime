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

mars_time_t mars_time();
time_t mars_time_to_earth_time(mars_time_t);
mars_time_t earth_time_to_mars_time(time_t);

mars_time_t mkmarstime(struct mars_tm*);
