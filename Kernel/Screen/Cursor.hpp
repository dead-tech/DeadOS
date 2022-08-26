#pragma once

#include <DT/Types.hpp>

#include "../Io/Io.hpp"

namespace Screen {

class Cursor
{
  public:
    void enable() const;
    void disable() const;

    [[nodiscard]] dt::u16 x() const;
    [[nodiscard]] dt::u16 y() const;
    [[nodiscard]] dt::u16 cursor_location() const;

    void increase_x(dt::u16 amount = 1);
    void increase_y(dt::u16 amount = 1);
    void decrease_x(dt::u16 amount = 1);
    void decrease_y(dt::u16 amount = 1);

    void backspace();
    void tab();
    void carriage_return();
    void newline();
    void insert_newline_if_necessary();

    void move_cursor(dt::u16 x, dt::u16 y);

  private:
    dt::u16 m_x               = 0;
    dt::u16 m_y               = 0;
    dt::u16 m_cursor_location = 0;

    constexpr static auto   FB_COMMAND_PORT      = 0x3D4;
    constexpr static auto   FB_DATA_PORT         = 0x3D5;
    constexpr static dt::u8 FB_HIGH_BYTE_COMMAND = 0x0E;
    constexpr static dt::u8 FB_LOW_BYTE_COMMAND  = 0x0F;

    constexpr static dt::u16 COLUMNS = 80;
    constexpr static dt::u16 ROWS    = 25;
};

} // namespace Screen
