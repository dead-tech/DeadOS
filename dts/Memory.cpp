#include "Memory.hpp"

namespace dts {

static dts::u32 free_memory = reinterpret_cast<dts::u32>(&kernel_end);

void *memset(void *address, const int constant, const dts::u32 num)
{
    auto *ptr = reinterpret_cast<dts::u8 *>(address);
    for (dts::u32 i = 0; i < num; ++i) { ptr[i] = static_cast<dts::u8>(constant); }

    return ptr;
}

void *memcpy(void *dst, const void *src, const dts::u32 num)
{
    auto       *dest_byte_ptr = reinterpret_cast<dts::u8 *>(dst);
    const auto *src_byte_ptr  = reinterpret_cast<const dts::u8 *>(src);
    for (dts::u32 i = 0; i < num; ++i) { dest_byte_ptr[i] = src_byte_ptr[i]; }

    return dest_byte_ptr;
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

void *malloc(const dts::u32 size)
{
    void *ptr = nullptr;

    asm volatile("int $0x80" : : "a"(0), "b"(size));
    asm volatile("mov %%eax, %0" : "=r"(ptr));

    return ptr;
}

void free(void *ptr) { asm volatile("int $0x80" : : "a"(1), "b"(ptr)); }

} // namespace dts
