#pragma once

#include <dts/Types.hpp>

#include "../ProgrammableInterruptController/ProgrammableInterruptController.hpp"
#include "../Screen/Framebuffer.hpp"

namespace Isr {

struct [[gnu::packed]] CpuRegisters
{
    // data segment selector
    dts::u32 ds;

    // pushed by pusha
    dts::u32 edi;
    dts::u32 esi;
    dts::u32 ebp;
    dts::u32 esp;
    dts::u32 ebx;
    dts::u32 edx;
    dts::u32 ecx;
    dts::u32 eax;

    dts::u32 interrupt_number;
    dts::u32 error_code;

    // pushed automatically by the cpu
    dts::u32 eip;
    dts::u32 cs;
    dts::u32 eflags;
    dts::u32 user_esp;
    dts::u32 ss;
};

using HandlerFnPtr = void (*)(CpuRegisters);

void register_interrupt_handler(dts::u8 index, HandlerFnPtr handler);

extern "C" void isr_handler(CpuRegisters registers);
} // namespace Isr
