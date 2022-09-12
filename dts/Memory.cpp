#include "Memory.hpp"

namespace dts {

void *memset(void *address, const int constant, const dts::u32 num)
{
    auto *ptr = reinterpret_cast<dts::u8 *>(address);
    for (dts::u32 i = 0; i < num; ++i) {
        ptr[i] = static_cast<dts::u8>(constant);
    }

    return ptr;
}

void *memcpy(void *dst, const void *src, const dts::u32 num)
{
    auto       *dest_byte_ptr = reinterpret_cast<dts::u8 *>(dst);
    const auto *src_byte_ptr  = reinterpret_cast<const dts::u8 *>(src);
    for (dts::u32 i = 0; i < num; ++i) { dest_byte_ptr[i] = src_byte_ptr[i]; }

    return dest_byte_ptr;
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
