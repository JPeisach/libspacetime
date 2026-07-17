#include <time.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef time_t mars_time_t;

// Broken down time structure for Martian time using the Darian calendar system.
//
// It is the same as struct tm, but with a few changes:
//  - Ranges are determined by the Darian Calendar (24 months in a year, max 28 sols in a month, max 668 sols in a year)
//  - No timezones at the moment
//  - "GMT offset" variable is "AMT offset" (Airy Mean Time)
//  - The variable names "day" have been replaced with "sol"
//  - The year starts at Year 0 of the Darian Calendar, unlike struct tm which starts counting from Gregorian Year 1900
//
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

    long int mars_tm_amtoff; /* Seconds east of MTC. */
    const char* mars_tm_zone; /* Timezone abbreviation. */
};

#ifdef MARS_TIMESPEC

// Time base value for a future mars_timespec_get, should be nothing too crazy.
#define TIME_MTC 101

struct mars_timespec
{
    // TODO: glibc actually switches the order of this for big endian platforms. consider doing the same?
    mars_time_t tv_mars_sec;

    // TODO: put in padding here??
    long int tv_mars_nsec;
};
#endif

mars_time_t mars_time(mars_time_t*);
time_t mars_time_to_earth_time(mars_time_t);

double earth_time_to_msd(time_t);
mars_time_t earth_time_to_mars_time(time_t);

double diffmarstime(mars_time_t, mars_time_t);

// (airy mean time instead of GMT)
struct mars_tm* ammarstime(const mars_time_t*);
struct mars_tm* localmarstime(const mars_time_t*);

mars_time_t mkmarstime(struct mars_tm*);

// C++ does not have the restrict keyword, but rather "__restrict", so handle it specially.
#ifdef __cplusplus
size_t strfmarstime(char* __restrict, size_t, const char* __restrict, const struct mars_tm* __restrict);
char* strpmarstime(const char *__restrict, const char *__restrict, struct mars_tm *__restrict);
size_t wcsfmarstime(wchar_t *__restrict, size_t, const wchar_t* __restrict, const struct mars_tm* __restrict);
#else
size_t strfmarstime(char* restrict, size_t, const char* restrict, const struct mars_tm* restrict);
char* strpmarstime(const char *restrict, const char *restrict, struct mars_tm *restrict);
size_t wcsfmarstime(wchar_t *restrict, size_t, const wchar_t* restrict, const struct mars_tm* restrict);
#endif

#ifdef __cplusplus
}
#endif
