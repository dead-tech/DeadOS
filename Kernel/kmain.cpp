#include "DescriptorTables/GlobalDescriptorTable.hpp"
#include "Io/SerialPort.hpp"
#include "Screen/Framebuffer.hpp"

int main()
{
    Screen::Framebuffer framebuffer;
    framebuffer.clear();
    char buffer[] = "Welcome to DeadOS";
    framebuffer.write_cstr(buffer);

    Io::SerialPort com1_port = Io::SerialPort::init(Io::COM1_SERIAL_PORT);
    com1_port.write_cstr("COM1: Hello sailor!");

    Gdt::init();

    return 0;
}
