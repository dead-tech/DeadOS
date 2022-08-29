global loader

extern main


section .__mbHeader
MAGIC_NUMBER    equ 0x1BADB002
FLAGS           equ 0x00000001
CHECKSUM        equ -(MAGIC_NUMBER + FLAGS )

align 4
    dd MAGIC_NUMBER,
    dd FLAGS,
    dd CHECKSUM

section .text
KERNEL_STACK_SIZE equ 4096

loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    mov eax, 0xCAFEBABE

    add  esp, 4
    push ebx
    call main

.loop:
    jmp .loop


section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE
