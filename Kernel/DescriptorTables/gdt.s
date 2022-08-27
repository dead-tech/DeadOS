global load_gdt
global reload_segment_registers

load_gdt:
    lgdt [esp + 4]
    ret

reload_segment_registers:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush_cs

flush_cs:
    ret
