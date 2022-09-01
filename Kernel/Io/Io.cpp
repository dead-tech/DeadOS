#include "Io.hpp"

namespace Io {

void outb(dts::u16 port, dts::u8 value) { asm volatile("outb %1, %0" : : "dN"(port), "a"(value)); }

dts::u8 inb(dts::u16 port)
{
    dts::u8 ret; // NOLINT
    asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

dts::u16 inw(dts::u16 port)
{
    dts::u16 ret; // NOLINT
    asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

} // namespace Io
