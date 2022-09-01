#pragma once

#include "Types.hpp"

namespace dts {

extern "C" dts::u32 kernel_end;


void *memset(void *ptr, const int constant, const dts::u32 num);

void *kmalloc(const dts::u32 size);
void *kmalloc_aligned(const dts::u32 size);
void *kmalloc_physical_address(const dts::u32 size, dts::u32 *physical_address);
void *kmalloc_aligned_physical_address(const dts::u32 size, dts::u32 *physicalAddress);

}; // namespace dts
