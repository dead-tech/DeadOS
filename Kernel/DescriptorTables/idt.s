global load_idt
global keyboard_handler

load_idt:
    ; xchg bx, bx
    mov eax, [esp + 4]
    lidt [eax]
    ret
