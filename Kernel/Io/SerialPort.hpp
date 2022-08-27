#pragma once

#include <DT/String.hpp>
#include <DT/Types.hpp>

#include "Io.hpp"

namespace Io {
constexpr static dt::u32 COM1_SERIAL_PORT = 0x3F8;

class SerialPort
{
  public:
    static SerialPort init(dt::u32 serial_port);

    [[nodiscard]] bool serial_received() const;
    [[nodiscard]] char read_serial() const;

    [[nodiscard]] bool is_transmit_empty() const;
    void               write_char(const char ch) const;
    void               write_cstr(const char *str) const;

  private:
    SerialPort(dt::u32 serial_port);

    dt::u32 m_serial_port;
};

} // namespace Io
