#pragma once

#include <dts/Types.hpp>

#include "../Io/Io.hpp"

namespace Screen {

class Cursor
{
  public:
    void enable() const;
    void disable() const;

    [[nodiscard]] dts::u16 x() const;
    [[nodiscard]] dts::u16 y() const;
    [[nodiscard]] dts::u16 cursor_location() const;

    void increase_x(dts::u16 amount = 1);
    void increase_y(dts::u16 amount = 1);
    void decrease_x(dts::u16 amount = 1);
    void decrease_y(dts::u16 amount = 1);

    void backspace();
    void tab();
    void carriage_return();
    void newline();
    void insert_newline_if_necessary();

    void move_cursor(dts::u16 x, dts::u16 y);

  private:
    dts::u16 m_x               = 0;
    dts::u16 m_y               = 0;
    dts::u16 m_cursor_location = 0;

    constexpr static auto    FB_COMMAND_PORT      = 0x3D4;
    constexpr static auto    FB_DATA_PORT         = 0x3D5;
    constexpr static dts::u8 FB_HIGH_BYTE_COMMAND = 0x0E;
    constexpr static dts::u8 FB_LOW_BYTE_COMMAND  = 0x0F;

    constexpr static dts::u16 COLUMNS = 80;
    constexpr static dts::u16 ROWS    = 25;
};

} // namespace Screen
