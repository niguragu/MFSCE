OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM (rw) : ORIGIN = 0x20000000, LENGTH = 64K
    MMIO (rw) : ORIGIN = 0x40000000, LENGTH = 4K
}

SECTIONS
{
    . = 0x00000000;
    .text : { *(.text) } > ROM
    .rodata : { *(.rodata) } > ROM
    .data : { *(.data) } > RAM
    .bss : { *(.bss) } > RAM
    .mmio : { KEEP(*(.mmio)) } > MMIO
    _end = .;
}