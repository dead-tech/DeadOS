#include "DescriptorTables/GlobalDescriptorTable.hpp"
#include "DescriptorTables/InterruptDescriptorTable.hpp"
#include "dts/Format.hpp"
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
  " My Operating System written in C++20.\n\n";

void kassert(
  const char               *expr,
  const char               *message,
  char const               *file,
  [[maybe_unused]] unsigned line
)
{
    auto formatted_message = dts::format(
      "[ASSERTION FAILED] -> {}: Expression: `{}`, Error Message: `{}`"_sv,
      file,
      expr,
      message
    );
    debug(formatted_message.c_str());
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
    Heap::init(4096 * 32);
    Screen::Framebuffer::clear();
    Screen::Framebuffer::write_cstr(welcome_message);
    dts::print("{}>"_sv, "dead@beepboop");
}
