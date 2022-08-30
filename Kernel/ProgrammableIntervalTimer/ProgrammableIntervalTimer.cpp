#include "ProgrammableIntervalTimer.hpp"

namespace Pit {


static void timer_callback([[maybe_unused]] Isr::CpuRegisters regs) {}

void init(dts::u32 frequency)
{
    Irq::register_interrupt_handler(0, &timer_callback);

    dts::u32 scaled_frequency = PIT_MAX_HZ / frequency; // PIC input frequence / our custom frequency

    Io::outb(PIT_COMMAND_PORT, PIT_REPEAT);

    dts::u8 frequency_low  = static_cast<dts::u8>(scaled_frequency & 0xFF);
    dts::u8 frequency_high = static_cast<dts::u8>((scaled_frequency >> 8) & 0xFF);

    Io::outb(PIT_DATA_PORT0, frequency_low);
    Io::outb(PIT_DATA_PORT0, frequency_high);
}

} // namespace Pit
