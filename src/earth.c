#include "earth.h"

#include <stdlib.h>

time_t earth_time() {
  time_t t;
  return time(&t);
}
