#include "mars.h"

#include <locale.h>

#ifdef MACOS
#include <xlocale.h>
#endif

// Hidden
mars_time_t __mars_tm_to_secs(const struct mars_tm* tm);
const char* __strfmarstime_fmt_item(char (*str)[100], size_t *len, int op, const struct mars_tm *tm, locale_t locale, int pad);
