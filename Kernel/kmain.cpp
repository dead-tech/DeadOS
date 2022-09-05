#include "DescriptorTables/GlobalDescriptorTable.hpp"
#include "DescriptorTables/InterruptDescriptorTable.hpp"
#include "Io/SerialPort.hpp"
#include "Kernel/Syscalls/Syscalls.hpp"
#include "Keyboard/Keyboard.hpp"
#include "Memory/Paging.hpp"
#include "ProgrammableIntervalTimer/ProgrammableIntervalTimer.hpp"
#include "Screen/Framebuffer.hpp"

constexpr static auto welcome_message =
  "  ____                 _    ___  ____  \n"
  " |  _ \\  ___  __ _  __| |  / _ \\/ ___| \n"
  " | | | |/ _ \\/ _` |/ _` | | | | \\___ \\ \n"
  " | |_| |  __/ (_| | (_| | | |_| |___) |\n"
  " |____/ \\___|\\__,_|\\__,_|  \\___/|____/ \n"
  "                                       \n"
  " My Operating System written in C++20.";

void kassert(
  [[maybe_unused]] const char *expr,
  [[maybe_unused]] const char *message,
  [[maybe_unused]] char const *file,
  [[maybe_unused]] unsigned    line)
{
    debug(message);
}

void main()
{
    asm volatile("cli");

    Screen::Cursor::init();
    Keyboard::init();
    Io::SerialPort::init();

    Gdt::init();
    Idt::init();
    Pit::init(5000);


    asm volatile("sti");
    Mem::init_paging();
    Syscalls::init();
    Screen::Framebuffer::clear();
    Screen::Framebuffer::write_cstr(welcome_message);
}
