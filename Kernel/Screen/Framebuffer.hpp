#pragma once

#include <DT/String.hpp>
#include <DT/Types.hpp>
#include <DT/TypeTraits.hpp>

#include "../Charset/Charset.hpp"
#include "Cursor.hpp"

namespace Screen {

enum class FramebufferColor : dt::u8
{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGTH_BLUE,
    LIGTH_GREEN,
    LIGTH_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE
};

class Framebuffer
{
  public:
    void write_char(const char ch);
    void write_char(const char ch, const dt::u8 attribute);
    void write_char(const char ch, const FramebufferColor foreground);
    void write_char(const char ch, const FramebufferColor foreground, const FramebufferColor background);

    void write_cstr(const char *str);
    void write_cstr(const char *str, const dt::u8 attribute);
    void write_cstr(const char *str, const FramebufferColor foreground);
    void write_cstr(const char *str, const FramebufferColor foreground, const FramebufferColor background);

    void clear();

  private:
    void scroll_if_necessary();

    Cursor m_cursor;

    constexpr static auto FB_COLUMNS = 80;
    constexpr static auto FB_ROWS    = 25;

    constexpr static auto CLEAR_CHARACTER = 0x0f20;
};

} // namespace Screen
