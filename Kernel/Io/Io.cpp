#include "Io.hpp"

namespace Io {

void outb(dt::u16 port, dt::u8 value) { asm volatile("outb %1, %0" : : "dN"(port), "a"(value)); }

dt::u8 inb(dt::u16 port)
{
    dt::u8 ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

dt::u16 inw(dt::u16 port)
{
    dt::u16 ret;
    asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

} // namespace Io
