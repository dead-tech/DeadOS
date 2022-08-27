global load_gdt

load_gdt:
    cli
    lgdt [esp + 4]
    ret
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush_cs

flush_cs:
    ret
