#pragma once

#include <dts/Types.hpp>

namespace Mem {

extern "C" dts::u32 kernel_end;

// Aligned -> Page aligned
void *kmalloc(const dts::u32 size);
void *kmalloc_aligned(const dts::u32 size);
void *kmalloc_physical_address(const dts::u32 size, dts::u32 *physical_address);
void *kmalloc_aligned_physical_address(const dts::u32 size, dts::u32 *physicalAddress);

} // namespace Mem
