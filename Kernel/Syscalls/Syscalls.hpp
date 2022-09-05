#pragma once

#include <dts/Assert.hpp>
#include <dts/Types.hpp>

#include "../DescriptorTables/InterruptServiceRoutine.hpp"
#include "../Io/SerialPort.hpp"
#include "../Memory/Heap.hpp"

namespace Syscalls {

using SyscallHandlerFnPtr = void (*)(Isr::CpuRegisters regs);

void init();
void common_syscall_handler(const Isr::CpuRegisters regs);

} // namespace Syscalls
