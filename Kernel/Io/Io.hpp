#pragma once

#include <dts/Types.hpp>

namespace Io {

void     outb(dts::u16 port, dts::u8 value);
dts::u8  inb(dts::u16 port);
dts::u16 inw(dts::u16 port);

} // namespace Io
