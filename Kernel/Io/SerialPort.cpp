#include "SerialPort.hpp"

namespace Io {

dts::i8 SerialPort::init()
{
    outb(COM1_SERIAL_PORT + 1, 0x00);
    outb(COM1_SERIAL_PORT + 3, 0x80);
    outb(COM1_SERIAL_PORT + 0, 0x03);
    outb(COM1_SERIAL_PORT + 1, 0x00);
    outb(COM1_SERIAL_PORT + 3, 0x03);
    outb(COM1_SERIAL_PORT + 2, 0xC7);
    outb(COM1_SERIAL_PORT + 4, 0x0B);
    outb(COM1_SERIAL_PORT + 4, 0x1E);
    outb(COM1_SERIAL_PORT + 0, 0xAE);

    if (inb(COM1_SERIAL_PORT + 0) != 0xAE) {
        Screen::Framebuffer::write_cstr("[ERROR]: Failed to initialize COM1 serial port\n");
        return -1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(COM1_SERIAL_PORT + 4, 0x0F);

    return 0;
}


bool SerialPort::serial_received() { return (inb(COM1_SERIAL_PORT + 5) & 0x1) != 0; }

char SerialPort::read_serial()
{
    while (serial_received()) { return inb(COM1_SERIAL_PORT); }

    return 0;
}

bool SerialPort::is_transmit_empty() { return (inb(COM1_SERIAL_PORT + 5) & 0x20) != 0; }

void SerialPort::write_char(const char ch)
{
    while (!is_transmit_empty()) {}
    outb(COM1_SERIAL_PORT, ch);
}

void SerialPort::write_cstr(const char *str)
{
    for (dts::u32 i = 0; str[i] != 0; ++i) { write_char(str[i]); }
}

} // namespace Io
