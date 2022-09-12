#pragma once

#include <dts/Assert.hpp>
#include <dts/String.hpp>
#include <dts/Types.hpp>

#include "../DescriptorTables/InterruptServiceRoutine.hpp"
#include "../Io/SerialPort.hpp"
#include "../Memory/Heap.hpp"

namespace Syscalls {

using SyscallHandlerFnPtr = void (*)(dts::u32, dts::u32, dts::u32, dts::u32);

} // namespace Syscalls
