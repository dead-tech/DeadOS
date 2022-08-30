#include "InterruptServiceRoutine.hpp"

namespace Isr {

static HandlerFnPtr interrupt_handlers[256];

void isr_handler([[maybe_unused]] CpuRegisters registers) { Screen::Framebuffer::write_cstr("Received interrupt: \n"); }

void register_interrupt_handler(dts::u8 index, HandlerFnPtr handler) { interrupt_handlers[index] = handler; }

} // namespace Isr
