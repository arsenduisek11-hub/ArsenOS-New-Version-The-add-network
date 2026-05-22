// Это boo загрузчик на ассемблере.t
section .multiboot2
align 8
    dd 0xE85250D6
    dd 0
    dd header_end - header_start
    dd 0x100000000 - (0xE85250D6 + 0 + (header_end - header_start))
header_start:
    dw 0
    dw 0
    dd 8
header_end:

section .text
global _start
extern kmain

_start:
    mov esp, stack_top
    push ebx
    push eax
    call kmain
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
