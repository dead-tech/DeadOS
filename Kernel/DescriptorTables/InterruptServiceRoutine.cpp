#include "InterruptServiceRoutine.hpp"

namespace Isr {

static HandlerFnPtr interrupt_handlers[256];

void isr_handler(CpuRegisters registers)
{
    if (interrupt_handlers[registers.interrupt_number] != nullptr) {
        interrupt_handlers[registers.interrupt_number](registers);
    } else {
        debug("[WARNING]: Unhandled interrupt!")
    }
}

void register_interrupt_handler(dts::u8 index, HandlerFnPtr handler)
{
    interrupt_handlers[index] = handler;
}

} // namespace Isr
