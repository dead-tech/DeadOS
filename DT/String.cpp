#include "String.hpp"

namespace dt {

u32 strlen(const char *str)
{
    u32 len = 0;
    while (str[len] != 0) { len++; }

    return len;
}

void strcpy(char *dst, const char *src)
{
    u32 len = 0;

    for (u32 i = 0; src[len] != 0; ++i) { dst[len] = src[len]; }

    dst[len] = '\0';
}

} // namespace dt
