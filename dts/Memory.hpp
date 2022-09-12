#pragma once

#include "Types.hpp"

namespace dts {

void *memset(void *ptr, const int constant, const dts::u32 num);
void *memcpy(void *dst, const void *src, const dts::u32 num);

void *malloc(const dts::u32 size);
void  free(void *ptr);

}; // namespace dts
