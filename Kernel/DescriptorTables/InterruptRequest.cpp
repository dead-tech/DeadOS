#include "InterruptRequest.hpp"

namespace Irq {

static HandlerFnPtr irq_handlers[16];

void irq_handler(Isr::CpuRegisters registers)
{
    Pic::send_end_of_interrupt(registers.interrupt_number, 0x20);

    if ((registers.interrupt_number - 32) >= 16) { return; }

    if (irq_handlers[registers.interrupt_number - 32] != 0) {
        irq_handlers[registers.interrupt_number - 32](registers);
    } else {
        debug("[WARNING]: Unhandled Interrupt!")
    }
}

void register_interrupt_handler(dts::u8 index, HandlerFnPtr handler)
{
    irq_handlers[index] = handler;
}

} // namespace Irq
