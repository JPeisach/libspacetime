#include "mars_time_impl.h"

#include "../const.h"

// Returns the number of Martian Seconds since MSD 0 that equate to the broken down martian time structure (tm).
mars_time_t mkmarstime(struct mars_tm* tm)
{
    // TODO: Timezones
    mars_time_t base = __mars_tm_to_secs(tm);

    return base;
}
