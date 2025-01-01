.section .text.init;
.globl _start
.data
      .align 4

.text
.align 4
_start:
    lui sp, 0x20010      
    addi sp, sp, 0x0000
    jal main
1: j 1b