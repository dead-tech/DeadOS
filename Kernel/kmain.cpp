#include "DescriptorTables/GlobalDescriptorTable.hpp"
#include "DescriptorTables/InterruptDescriptorTable.hpp"
#include "DescriptorTables/InterruptServiceRoutine.hpp"
#include "Io/SerialPort.hpp"
#include "ProgrammableIntervalTimer/ProgrammableIntervalTimer.hpp"
#include "Screen/Framebuffer.hpp"

void main()
{
    Screen::Cursor::init();
    asm volatile("cli");
    Io::SerialPort com1_port = Io::SerialPort::init(Io::COM1_SERIAL_PORT);
    com1_port.write_cstr("COM1: Calling Gdt::init()\n");
    Gdt::init();
    com1_port.write_cstr("COM1: GDT initialized\n");

    com1_port.write_cstr("COM1: Calling Idt::init()\n");
    Idt::init();
    com1_port.write_cstr("COM1: IDT initialized\n");

    Pit::init(50);

    Screen::Framebuffer::clear();
    Screen::Framebuffer::write_cstr("Welcome to DeadOS");

    asm volatile("sti");
    com1_port.write_cstr("COM1: Interrupts Enabled!\n");
}
