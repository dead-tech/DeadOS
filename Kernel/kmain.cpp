#include "DescriptorTables/GlobalDescriptorTable.hpp"
#include "DescriptorTables/InterruptDescriptorTable.hpp"
#include "DescriptorTables/InterruptServiceRoutine.hpp"
#include "Io/SerialPort.hpp"
#include "Keyboard/Keyboard.hpp"
#include "ProgrammableIntervalTimer/ProgrammableIntervalTimer.hpp"
#include "Screen/Framebuffer.hpp"

void main()
{
    asm volatile("cli");

    Screen::Cursor::init();
    Keyboard::init();
    Io::SerialPort::init();

    Gdt::init();
    Idt::init();
    Pit::init(50);

    Screen::Framebuffer::clear();
    Screen::Framebuffer::write_cstr("Welcome DeadOS");

    asm volatile("sti");
}
