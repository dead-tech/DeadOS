#include "Cursor.hpp"

namespace Screen {

void Cursor::init(dts::u8 cursor_start, dts::u8 cursor_end)
{
    Io::outb(FB_COMMAND_PORT, 0x0A);
    Io::outb(FB_DATA_PORT, (Io::inb(FB_DATA_PORT) & 0xC0) | cursor_start);

    Io::outb(FB_COMMAND_PORT, 0x0B);
    Io::outb(FB_DATA_PORT, (Io::inb(FB_DATA_PORT) & 0xE0) | cursor_end);
}

void Cursor::disable()
{
    Io::outb(FB_COMMAND_PORT, 0x0A);
    Io::outb(FB_DATA_PORT, 0x20);
}

dts::u16 Cursor::x() { return cursor_location() % COLUMNS; }

dts::u16 Cursor::y() { return cursor_location() / COLUMNS; }

dts::u16 Cursor::cursor_location()
{
    dts::u16 pos = 0;
    Io::outb(FB_COMMAND_PORT, 0x0F);
    pos |= Io::inb(FB_DATA_PORT);
    Io::outb(FB_COMMAND_PORT, 0x0E);
    pos |= (static_cast<dts::u16>(Io::inb(FB_DATA_PORT)) << 8);

    return pos;
}

void Cursor::increase_x(dts::u16 amount) { move_cursor(x() + amount, y()); }

void Cursor::increase_y(dts::u16 amount) { move_cursor(x(), y() + amount); }

void Cursor::decrease_x(dts::u16 amount) { move_cursor(x() - amount, y()); }

void Cursor::decrease_y(dts::u16 amount) { move_cursor(x(), y() - amount); }

void Cursor::backspace()
{
    if (x() > 0) { decrease_x(); }
}

void Cursor::carriage_return() { move_cursor(0, y()); }

void Cursor::tab() { move_cursor((x() + 8) & ~(8 - 1), y()); }

void Cursor::newline() { move_cursor(0, y() + 1); }

void Cursor::insert_newline_if_necessary()
{
    if (x() > COLUMNS) { newline(); }
}

void Cursor::move_cursor(dts::u16 x, dts::u16 y)
{
    dts::u16 pos = y * COLUMNS + x;
    Io::outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    Io::outb(FB_DATA_PORT, ((pos >> 8) & 0xFF));
    Io::outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    Io::outb(FB_DATA_PORT, (pos & 0xFF));
}

} // namespace Screen
