#include "Framebuffer.hpp"

namespace Screen {

void Framebuffer::write_char(const char ch) { write_char(ch, FramebufferColor::WHITE, FramebufferColor::BLACK); }

void Framebuffer::write_char(const char ch, const dt::u8 attribute)
{
    volatile char *video_memory = reinterpret_cast<volatile char *>(0xb8000) + m_cursor.cursor_location() * 2;

    switch (ch) {
        case Charset::BACKSPACE: {
            m_cursor.backspace();
            break;
        }
        case Charset::TAB: {
            m_cursor.tab();
            break;
        }
        case Charset::CARRIAGE_RETURN: {
            m_cursor.carriage_return();
            break;
        }
        case Charset::NEWLINE: {
            m_cursor.newline();
            break;
        }
    }

    if (ch >= Charset::SPACE) {
        *video_memory++ = ch;
        *video_memory++ = attribute;
        m_cursor.increase_x();
    }

    m_cursor.insert_newline_if_necessary();
    scroll_if_necessary();
}

void Framebuffer::write_char(const char ch, const FramebufferColor foreground)
{
    const dt::u8 attribute =
      (dt::to_underlying_type(FramebufferColor::BLACK) << 4) | (dt::to_underlying_type(foreground) & 0x0F);

    write_char(ch, attribute);
}

void Framebuffer::write_char(const char ch, const FramebufferColor foreground, const FramebufferColor background)
{
    const dt::u8 attribute = (dt::to_underlying_type(background) << 4) | (dt::to_underlying_type(foreground) & 0x0F);

    write_char(ch, attribute);
}


void Framebuffer::write_cstr(char *str) { write_cstr(str, FramebufferColor::WHITE, FramebufferColor::BLACK); }

void Framebuffer::write_cstr(char *str, const dt::u8 attribute)
{
    for (char *ch = str; *ch != 0; ++ch) { write_char(*ch, attribute); }
}

void Framebuffer::write_cstr(char *str, const FramebufferColor foreground)
{
    const dt::u8 attribute =
      (dt::to_underlying_type(FramebufferColor::BLACK) << 4) | (dt::to_underlying_type(foreground) & 0x0F);
    write_cstr(str, attribute);
}

void Framebuffer::write_cstr(char *str, const FramebufferColor foreground, const FramebufferColor background)
{
    const dt::u8 attribute = (dt::to_underlying_type(background) << 4) | (dt::to_underlying_type(foreground) & 0x0F);
    write_cstr(str, attribute);
}

void Framebuffer::clear()
{
    dt::u16 *video_memory = reinterpret_cast<dt::u16 *>(0xb8000);
    for (dt::u32 i = 0; i < FB_COLUMNS * FB_ROWS; ++i) { video_memory[i] = CLEAR_CHARACTER; }

    // TODO: create m_cursor.reset() or something
    m_cursor.move_cursor(0, 0);
}

void Framebuffer::scroll_if_necessary()
{
    dt::u16 *video_memory = reinterpret_cast<dt::u16 *>(0xb8000);
    if (m_cursor.y() >= 25) {
        for (dt::u32 i = 0; i < FB_COLUMNS * (FB_ROWS - 1); ++i) { video_memory[i] = video_memory[i + 80]; }

        for (dt::u32 i = (FB_ROWS - 1) * FB_COLUMNS; i < FB_COLUMNS * FB_ROWS; ++i) {
            video_memory[i] = CLEAR_CHARACTER;
        }

        m_cursor.decrease_y();
    }
}


} // namespace Screen
