#include "mars.h"

// At the moment, we have no timezones.
// So just run on airy.
struct mars_tm* localmarstime(const mars_time_t* timer)
{
    return ammarstime(timer);
}
