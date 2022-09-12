#include "Syscalls.hpp"

namespace Syscalls {

static void sys_malloc(
  [[maybe_unused]] dts::u32 eax,
  dts::u32                  ebx,
  [[maybe_unused]] dts::u32 ecx,
  [[maybe_unused]] dts::u32 edx
)
{
    debug("Malloc syscall");

    if (Heap::list_head == nullptr) { Heap::init(ebx); }

    void *ptr = Heap::malloc(ebx);

    Heap::merge_free_blocks();

    asm volatile("mov %0, %%eax" ::"r"(reinterpret_cast<dts::u32>(ptr)));
}

static void sys_free(
  [[maybe_unused]] dts::u32 eax,
  dts::u32                  ebx,
  [[maybe_unused]] dts::u32 ecx,
  [[maybe_unused]] dts::u32 edx
)
{
    debug("Free syscall");
    Heap::free(reinterpret_cast<void *>(ebx));
}

static void sys_print(
  [[maybe_unused]] dts::u32 eax,
  dts::u32                  ebx,
  [[maybe_unused]] dts::u32 ecx,
  [[maybe_unused]] dts::u32 edx
)
{
    debug("Print syscall");
    Screen::Framebuffer::write_cstr(reinterpret_cast<const char *>(ebx));
}

extern "C" SyscallHandlerFnPtr syscalls_handlers[];
SyscallHandlerFnPtr            syscalls_handlers[] = {
               sys_malloc,
               sys_free,
               sys_print,
};

} // namespace Syscalls
