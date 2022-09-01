#pragma once

#include <dts/String.hpp>
#include <dts/Types.hpp>

#include "../Screen/Framebuffer.hpp"
#include "Io.hpp"

#define STRINGIFY(x) STRINGIFY_IMPL(x)
#define STRINGIFY_IMPL(x) #x
#define debug(msg)                                                           \
    Io::SerialPort::write_cstr("#(" __FILE__ ":" STRINGIFY(__LINE__) "): "); \
    Io::SerialPort::write_cstr(msg);                                         \
    Io::SerialPort::write_char('\n');

namespace Io {

constexpr static dts::u32 COM1_SERIAL_PORT = 0x3F8;

class SerialPort
{
  public:
    static dts::i8 init();

    [[nodiscard]] static bool serial_received();
    [[nodiscard]] static char read_serial();

    [[nodiscard]] static bool is_transmit_empty();
    static void               write_char(const char ch);
    static void               write_cstr(const char *str);
};

} // namespace Io
