#pragma once

#include <dts/Types.hpp>

namespace dts {

u32  strlen(char *str);
void strcpy(char *dst, char *src);

char *itoa(u64 integer, u8 base = 10);

} // namespace dts
