#include "kmalloc.hpp"

namespace Mem {

static dts::u32 free_memory = reinterpret_cast<dts::u32>(&kernel_end);

void *kmalloc(const dts::u32 size)
{
    void *mem = reinterpret_cast<void *>(free_memory);
    free_memory += size;
    return mem;
}

void *kmalloc_aligned(const dts::u32 size)
{
    if (free_memory & 0xFFFFF000) {
        free_memory &= 0xFFFFF000;
        free_memory += 0x1000;
    }
    return kmalloc(size);
}

void *kmalloc_physical_address(const dts::u32 size, dts::u32 *physical_address)
{
    if (physical_address) { *physical_address = free_memory; }

    return kmalloc(size);
}

void *kmalloc_aligned_physical_address(const dts::u32 size, dts::u32 *phyiscal_address)
{
    if (free_memory & 0xFFFFF000) {
        free_memory &= 0xFFFFF000;
        free_memory += 0x1000;
    }
    return kmalloc_physical_address(size, phyiscal_address);
}

} // namespace Mem
