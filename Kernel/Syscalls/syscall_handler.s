global syscall_common_handler
extern syscalls_handlers

syscall_common_handler:
    xchg bx, bx
    push gs
    push fs
    push es
    push ds
    push ebp
    push edi
    push esi
    push esp
    push edx
    push ecx
    push ebx
    push eax
    call [syscalls_handlers+eax*4]
    xchg bx, bx
    add esp, 4
    pop ebx
    pop ecx
    pop edx
    add esp, 4
    pop esi
    pop edi
    pop ebp
    pop ds
    pop es
    pop fs
    pop gs
    iretd
