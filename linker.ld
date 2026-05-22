ENTRY(_start)

SECTIONS
{
    . = 1M;
    .multiboot2 : {
        *(.multiboot2)
    }
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
}
// Это linker.ld (Удалите если хотите запустить ОСз
