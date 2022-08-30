#include "Keyboard.hpp"

namespace Keyboard {

static void keyboard_callback([[maybe_unused]] Isr::CpuRegisters regs)
{
    const auto status = Io::inb(KEYBOARD_STATUS_PORT);
    if (status & 0x1) {
        const dts::u8 key = Io::inb(KEYBOARD_DATA_PORT);

        switch (key) {
            case 0x1C: {
                Screen::Cursor::newline();
                break;
            }
            case 0x0E: {
                Screen::Cursor::decrease_x();
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
    Io::outb(Pic::MASTER_PIC_DATA, 0xFC);
    Irq::register_interrupt_handler(1, &keyboard_callback);
}

} // namespace Keyboard
