#include "mars.h"

// Glibc and Musl return double.. not sure how it would help us in this situation since difference is in seconds
double diffmarstime(mars_time_t time_end, mars_time_t time_start)
{
    return (double) (time_end - time_start);
}
