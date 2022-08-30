#include "Keyboard.hpp"

namespace Keyboard {

static void keyboard_callback([[maybe_unused]] Isr::CpuRegisters regs)
{
    const auto status = Io::inb(KEYBOARD_STATUS_PORT);
    if (status & 0x1) {
        const dts::u8 key = Io::inb(KEYBOARD_DATA_PORT);

        switch (key) {
            case ENTER: {
                Screen::Framebuffer::write_char('\n');
                break;
            }
            case BACKSPACE: {
                Screen::Framebuffer::write_char(Charset::BACKSPACE);
                break;
            }
            case TAB: {
                Screen::Framebuffer::write_char(Charset::TAB);
                break;
            }
            default: {
                Screen::Framebuffer::write_char(keyboard_map[key]);
            }
        }
    }
}

void init()
{
    Irq::register_interrupt_handler(1, &keyboard_callback);
    debug("Keyboard driver initialized!");
}

} // namespace Keyboard
