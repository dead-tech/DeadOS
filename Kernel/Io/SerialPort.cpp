#include "SerialPort.hpp"

namespace Io {

SerialPort SerialPort::init(dts::u32 serial_port)
{
    SerialPort port(serial_port);
    outb(serial_port + 1, 0x00); // Disable all interrupts
    outb(serial_port + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(serial_port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(serial_port + 1, 0x00); //                  (hi byte)
    outb(serial_port + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(serial_port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(serial_port + 4, 0x0B); // IRQs enabled, RTS/DSR set
    outb(serial_port + 4, 0x1E); // Set in loopback mode, test the serial chip
    outb(serial_port + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // FIXME: enable this check once we have some sort of optional
    // Check if serial is faulty (i.e: not same byte as sent)
    // if(inb(serial_port + 0) != 0xAE) {
    //     return 1;
    // }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(serial_port + 4, 0x0F);

    return port;
}

SerialPort::SerialPort(dts::u32 serial_port) : m_serial_port{ serial_port } {}

bool SerialPort::serial_received() const { return inb(m_serial_port + 5) & 0x1; }

char SerialPort::read_serial() const
{
    while (serial_received()) { return inb(m_serial_port); }

    return 0;
}

bool SerialPort::is_transmit_empty() const { return inb(m_serial_port + 5) & 0x20; }

void SerialPort::write_char(const char ch) const
{
    while (!is_transmit_empty())
        ;
    outb(m_serial_port, ch);
}

void SerialPort::write_cstr(const char *str) const
{
    for (dts::u32 i = 0; str[i] != 0; ++i) { write_char(str[i]); }
}

} // namespace Io
