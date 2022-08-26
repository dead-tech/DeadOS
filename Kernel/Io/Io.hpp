#pragma once

#include <DT/Types.hpp>

namespace Io {

void    outb(dt::u16 port, dt::u8 value);
dt::u8  inb(dt::u16 port);
dt::u16 inw(dt::u16 port);

} // namespace Io
