#include "Syscalls.hpp"

namespace Syscalls {

static void sys_malloc([[maybe_unused]] const Isr::CpuRegisters regs)
{
    debug("Malloc syscall");

    const auto bytes = regs.ebx;

    if (Heap::list_head == nullptr) { Heap::init(bytes); }

    void *ptr = Heap::malloc(bytes);

    Heap::merge_free_blocks();

    asm volatile("mov %0, %%eax" : : "r"(ptr));
}

static void sys_free([[maybe_unused]] const Isr::CpuRegisters regs)
{
    debug("Free syscall");
    Heap::free(reinterpret_cast<void *>(regs.ebx));
}

static SyscallHandlerFnPtr syscall_handlers[] = { sys_malloc, sys_free };

void init() { Isr::register_interrupt_handler(0x80, &common_syscall_handler); }

void common_syscall_handler(const Isr::CpuRegisters regs)
{
    const auto syscall_number = regs.eax;

    if (syscall_handlers[syscall_number] != nullptr) {
        syscall_handlers[syscall_number](regs);
    } else {
        // FIXME: Should we panic here or go on?
        debug("Unrecognized syscall!");
    }
}

} // namespace Syscalls
