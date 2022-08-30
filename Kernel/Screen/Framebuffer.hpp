#pragma once

#include <dts/String.hpp>
#include <dts/Types.hpp>
#include <dts/TypeTraits.hpp>

#include "../Charset/Charset.hpp"
#include "Cursor.hpp"

namespace Screen {

enum class FramebufferColor : dts::u8
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
    static void write_char(const char ch);
    static void write_char(const char ch, const dts::u8 attribute);
    static void write_char(const char ch, const FramebufferColor foreground);
    static void write_char(const char ch, const FramebufferColor foreground, const FramebufferColor background);

    static void write_cstr(const char *str);
    static void write_cstr(const char *str, const dts::u8 attribute);
    static void write_cstr(const char *str, const FramebufferColor foreground);
    static void write_cstr(const char *str, const FramebufferColor foreground, const FramebufferColor background);

    static void clear();

  private:
    static void scroll_if_necessary();

    constexpr static auto FB_COLUMNS = 80;
    constexpr static auto FB_ROWS    = 25;

    constexpr static auto CLEAR_CHARACTER = 0x0f20;
};

} // namespace Screen
