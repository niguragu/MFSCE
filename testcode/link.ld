OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM (rw) : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    .text : { *(.text) } > ROM
    .rodata : { *(.rodata) } > ROM
    .data : { *(.data) } > RAM
    .bss : { *(.bss) } > RAM
    _end = .;
}