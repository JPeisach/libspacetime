#include "mars_time_impl.h"

#include "../const.h"

mars_time_t mkmarstime(struct mars_tm* tm)
{
    // TODO: Timezones
    mars_time_t base = __mars_tm_to_secs(tm);

    return base;
}
