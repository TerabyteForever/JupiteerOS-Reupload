global loader
; kernel_main is defined in kernel_main.c
extern kernel_main

KERNEL_STACK_SIZE equ 4096

section .text
loader:
  ; set up stack pointer
  mov esp, kernel_stack + KERNEL_STACK_SIZE
  call kernel_main
.loop:
  jmp .loop

section .bss
align 4
kernel_stack:
  ; resb, declare uninitialized storage space. 
  resb KERNEL_STACK_SIZE