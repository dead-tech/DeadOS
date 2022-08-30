#include "Framebuffer.hpp"

namespace Screen {

void Framebuffer::write_char(const char ch) { write_char(ch, FramebufferColor::WHITE, FramebufferColor::BLACK); }

void Framebuffer::write_char(const char ch, const dts::u8 attribute)
{
    volatile char *video_memory = reinterpret_cast<volatile char *>(0xb8000) + Cursor::cursor_location() * 2;

    switch (ch) {
        case Charset::BACKSPACE: {
            *video_memory-- = ' ';
            *video_memory-- = 0x0f;
            Cursor::backspace();
            break;
        }
        case Charset::TAB: {
            Cursor::tab();
            break;
        }
        case Charset::CARRIAGE_RETURN: {
            Cursor::carriage_return();
            break;
        }
        case Charset::NEWLINE: {
            Cursor::newline();
            break;
        }
    }

    if (ch >= Charset::SPACE) {
        *video_memory++ = ch;
        *video_memory++ = attribute;
        Cursor::increase_x();
    }

    Cursor::insert_newline_if_necessary();
    scroll_if_necessary();
}

void Framebuffer::write_char(const char ch, const FramebufferColor foreground)
{
    const dts::u8 attribute =
      (dts::to_underlying_type(FramebufferColor::BLACK) << 4) | (dts::to_underlying_type(foreground) & 0x0F);

    write_char(ch, attribute);
}

void Framebuffer::write_char(const char ch, const FramebufferColor foreground, const FramebufferColor background)
{
    const dts::u8 attribute = (dts::to_underlying_type(background) << 4) | (dts::to_underlying_type(foreground) & 0x0F);

    write_char(ch, attribute);
}


void Framebuffer::write_cstr(const char *str) { write_cstr(str, FramebufferColor::WHITE, FramebufferColor::BLACK); }

void Framebuffer::write_cstr(const char *str, const dts::u8 attribute)
{
    for (dts::u32 i = 0; str[i] != 0; ++i) { write_char(str[i], attribute); }
}

void Framebuffer::write_cstr(const char *str, const FramebufferColor foreground)
{
    const dts::u8 attribute =
      (dts::to_underlying_type(FramebufferColor::BLACK) << 4) | (dts::to_underlying_type(foreground) & 0x0F);
    write_cstr(str, attribute);
}

void Framebuffer::write_cstr(const char *str, const FramebufferColor foreground, const FramebufferColor background)
{
    const dts::u8 attribute = (dts::to_underlying_type(background) << 4) | (dts::to_underlying_type(foreground) & 0x0F);
    write_cstr(str, attribute);
}

void Framebuffer::clear()
{
    dts::u16 *video_memory = reinterpret_cast<dts::u16 *>(0xb8000);
    for (dts::u32 i = 0; i < FB_COLUMNS * FB_ROWS; ++i) { video_memory[i] = CLEAR_CHARACTER; }

    // TODO: create Cursor::reset() or something
    Cursor::move_cursor(0, 0);
}

void Framebuffer::scroll_if_necessary()
{
    dts::u16 *video_memory = reinterpret_cast<dts::u16 *>(0xb8000);
    if (Cursor::y() >= 25) {
        for (dts::u32 i = 0; i < FB_COLUMNS * (FB_ROWS - 1); ++i) { video_memory[i] = video_memory[i + 80]; }

        for (dts::u32 i = (FB_ROWS - 1) * FB_COLUMNS; i < FB_COLUMNS * FB_ROWS; ++i) {
            video_memory[i] = CLEAR_CHARACTER;
        }

        Cursor::decrease_y();
    }
}


} // namespace Screen
