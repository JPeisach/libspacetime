#include "mars.h"

#include "../const.h"
#include "../earth.h"

#ifdef HAVE_MPFR
#include <mpfr.h>
#endif

inline double __do_earth_time_to_msd(time_t et)
{
    return ((et + TAI_OFFSET) / 88775.244147) + 34127.2954262;
}

inline mars_time_t __do_earth_time_to_mars_time(time_t et)
{
#ifdef HAVE_MPFR
    // mpf_set_default_prec(50);
    mpfr_t num, denom, base, msd, offset, ret, seconds_per_day;
    mpfr_init(num);
    mpfr_init(denom);
    mpfr_init(base);
    mpfr_init(msd);
    mpfr_init(seconds_per_day);
    mpfr_init(offset);
    mpfr_init(ret);

    mpfr_set_d(num, ((double)et + TAI_OFFSET), MPFR_RNDN);
    mpfr_set_d(denom, (double)88775.244147, MPFR_RNDN);

    mpfr_div(base, num, denom, MPFR_RNDN);

    mpfr_set_d(offset, (double)34127.2954262, MPFR_RNDN);

    mpfr_add(msd, base, offset, MPFR_RNDN);

    mpfr_set_d(seconds_per_day, (double)86400.0, MPFR_RNDN);

    mpfr_mul(ret, msd, seconds_per_day, MPFR_RNDN);

    return mpfr_get_d(ret, MPFR_RNDN);

#endif
    // martian seconds
    return (mars_time_t) (__do_earth_time_to_msd(et) * SECONDS_PER_DAY);
}



mars_time_t mars_time(mars_time_t *timer)
{
    mars_time_t time = __do_earth_time_to_mars_time(earth_time());
    if(timer)
        *timer = time;

    return time;
}

time_t mars_time_to_earth_time(mars_time_t mars_time)
{
    // Martian Days. Try to keep precision
    double msd = mars_time / 86400.0;

    // Same steps in reverse
    double earth_time = (msd - 34127.2954262) * 88775.244147;

    // Subtract leap-second correction and cast to time_t (subtract first to match test expectations)
    return (time_t) (earth_time - TAI_OFFSET);
}

mars_time_t earth_time_to_mars_time(time_t et)
{
    return __do_earth_time_to_mars_time(et);
}
