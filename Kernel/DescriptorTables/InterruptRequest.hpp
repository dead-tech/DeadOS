#pragma once

#include "InterruptServiceRoutine.hpp"

namespace Irq {

using HandlerFnPtr = void (*)(Isr::CpuRegisters);

void register_interrupt_handler(dts::u8 index, HandlerFnPtr handler);

extern "C" void irq_handler(Isr::CpuRegisters registers);

} // namespace Irq
