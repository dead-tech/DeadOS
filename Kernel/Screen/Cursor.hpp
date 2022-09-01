#pragma once

#include <dts/Types.hpp>

#include "../Io/Io.hpp"

namespace Screen {

class Cursor
{
  public:
    static void init(dts::u8 cursor_start = 0, dts::u8 cursor_end = 15);
    static void disable();

    [[nodiscard]] static dts::u16 x();
    [[nodiscard]] static dts::u16 y();
    [[nodiscard]] static dts::u16 cursor_location();

    static void increase_x(dts::u16 amount = 1);
    static void increase_y(dts::u16 amount = 1);
    static void decrease_x(dts::u16 amount = 1);
    static void decrease_y(dts::u16 amount = 1);

    static void backspace();
    static void tab();
    static void carriage_return();
    static void newline();
    static void insert_newline_if_necessary();

    static void move_cursor(dts::u16 x, dts::u16 y);
    static void reset();

  private:
    constexpr static auto    FB_COMMAND_PORT      = 0x3D4;
    constexpr static auto    FB_DATA_PORT         = 0x3D5;
    constexpr static dts::u8 FB_HIGH_BYTE_COMMAND = 0x0E;
    constexpr static dts::u8 FB_LOW_BYTE_COMMAND  = 0x0F;

    constexpr static dts::u16 COLUMNS = 80;
    constexpr static dts::u16 ROWS    = 25;
};

} // namespace Screen
