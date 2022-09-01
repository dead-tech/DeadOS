#include "Memory.hpp"

namespace dts {

static dts::u32 free_memory = reinterpret_cast<dts::u32>(&kernel_end);

void *memset(void *address, const int constant, const dts::u32 num)
{
    dts::u8 *ptr = reinterpret_cast<dts::u8 *>(address);
    for (dts::u32 i = 0; i < num; ++i) { ptr[i] = static_cast<dts::u8>(constant); }

    return ptr;
}

void *kmalloc(const dts::u32 size)
{
    void *mem = reinterpret_cast<void *>(free_memory);
    free_memory += size;
    return mem;
}

void *kmalloc_aligned(const dts::u32 size)
{
    if ((free_memory & 0xFFFFF000) != 0U) {
        free_memory &= 0xFFFFF000;
        free_memory += 0x1000;
    }
    return kmalloc(size);
}

void *kmalloc_physical_address(const dts::u32 size, dts::u32 *physical_address)
{
    if (physical_address != nullptr) { *physical_address = free_memory; }

    return kmalloc(size);
}

void *kmalloc_aligned_physical_address(const dts::u32 size, dts::u32 *physical_address)
{
    if ((free_memory & 0xFFFFF000) != 0U) {
        free_memory &= 0xFFFFF000;
        free_memory += 0x1000;
    }
    return kmalloc_physical_address(size, physical_address);
}
} // namespace dts
