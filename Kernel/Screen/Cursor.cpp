#include "Cursor.hpp"

namespace Screen {

void Cursor::enable() const
{
    Io::outb(FB_COMMAND_PORT, 0x0A);
    Io::outb(FB_DATA_PORT, (Io::inb(FB_DATA_PORT) & 0xC0) | 0);
    Io::outb(FB_COMMAND_PORT, 0x0B);
    Io::outb(FB_DATA_PORT, (Io::inb(FB_DATA_PORT) & 0xE0) | 15);
}

dts::u16 Cursor::x() const { return m_x; }

dts::u16 Cursor::y() const { return m_y; }

dts::u16 Cursor::cursor_location() const { return (m_y * COLUMNS + m_x); }

void Cursor::increase_x(dts::u16 amount) { move_cursor(m_x + amount, m_y); }

void Cursor::increase_y(dts::u16 amount) { move_cursor(m_x, m_y + amount); }

void Cursor::decrease_x(dts::u16 amount) { move_cursor(m_x - amount, m_y); }

void Cursor::decrease_y(dts::u16 amount) { move_cursor(m_x, m_y - amount); }

void Cursor::backspace()
{
    if (m_x > 0) { decrease_x(); }
}

void Cursor::carriage_return() { move_cursor(0, m_y); }

void Cursor::tab() { move_cursor((m_x + 8) & ~(8 - 1), m_y); }

void Cursor::newline() { move_cursor(0, m_y + 1); }

void Cursor::insert_newline_if_necessary()
{
    if (m_x > COLUMNS) { newline(); }
}

void Cursor::move_cursor(dts::u16 x, dts::u16 y)
{
    m_x          = x;
    m_y          = y;
    dts::u16 pos = x * COLUMNS * y;
    Io::outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    Io::outb(FB_DATA_PORT, ((pos >> 8) & 0xFF));
    Io::outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    Io::outb(FB_DATA_PORT, (pos & 0xFF));
}

} // namespace Screen
