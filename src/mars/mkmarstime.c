#include "mars_time_impl.h"

#include "../const.h"

mars_time_t mkmarstime(struct mars_tm* tm)
{
    return __mars_tm_to_secs(tm);
}
