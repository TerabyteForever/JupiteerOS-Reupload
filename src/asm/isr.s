extern isr_handler

; When the processor receives an interrupt,it saves the contents of the essential registers 
; (instruction pointer, stack pointer, code and data segments, flags register) to the stack. 
; It then finds the interrupt handler location from our IDT and jumps to it. 

; Now, just like POSIX signal handlers,you don't get given any information about what interrupt 
; was called when your handler is run. Many handlers that just push the interrupt number (hardcoded 
; in the ASM) onto the stack, and call a common handler function.

; Some interrupts also push an error code onto the stack. Some of them don't push an
; error code, we push a dummy one.

isr_common:
  ; Pop the registers(edi,esi,ebp,esp,ebx,edx,ecx,eax) from the stack.
  pusha

  ; Lower 16-bits of eax = ds.
  mov ax, ds
  ; save the data segment descriptor
  push ds

  ; load the kernel data segment descriptor
  mov ax, 0x10  
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ; call the C function
  call isr_handler

  ; reload the original data segment descriptor
  pop ebx
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx

  ; Pop the registers from the stack.
  popa
  ; Add 8 to esp (because of the error code and the 
  ; interrupt number pushed earlier).
  add esp, 8
  ; Execute iret to return to the interrupted code.
  iret

; The specific CPU interrupts that put an error code on the 
; stack are 8,10,11,12,13,14,17 and 21.
  
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; 0: Divide By Zero Exception
isr0:
  push byte 0
  push 0
  jmp isr_common

; 1: Debug Exception
isr1:
  push byte 0
  push 1
  jmp isr_common

; 2: Non Maskable Interrupt Exception
isr2:
  push byte 0
  push 2
  jmp isr_common

; 3: Breakpoint Exception
isr3:
  push byte 0
  push 3
  jmp isr_common

; 4: Into Detected Overflow Exception
isr4:
  push byte 0
  push 4
  jmp isr_common

; 5: Out of Bounds Exception
isr5:
  push byte 0
  push 5
  jmp isr_common

; 6: Invalid Opcode Exception
isr6:
  push byte 0
  push 6
  jmp isr_common

; 7: No Coprocessor Exception
isr7:
  push byte 0
  push 7
  jmp isr_common

; 8: Double Fault Exception (With Error Code)
isr8:
  push 8
  jmp isr_common

; 9: Coprocessor Segment Overrun Exception
isr9:
  push byte 0
  push 9
  jmp isr_common

; 10: Bad TSS Exception (With Error Code)
isr10:
  push 10
  jmp isr_common

; 11: Segment Not Present Exception (With Error Code)
isr11:
  push 11
  jmp isr_common

; 12: Stack Fault Exception (With Error Code)
isr12:
  push 12
  jmp isr_common

; 13: General Protection Fault Exception (With Error Code)
isr13:
  push 13
  jmp isr_common

; 14: Page Fault Exception (With Error Code)
isr14:
  push 14
  jmp isr_common

; 15: Unknown Interrupt Exception
isr15:
  push byte 0
  push 15
  jmp isr_common

; 16: Coprocessor Fault Exception
isr16:
  push byte 0
  push 16
  jmp isr_common

; 17: Alignment Check Exception
isr17:
  push 17
  jmp isr_common

; 18: Machine Check Exception
isr18:
  push byte 0
  push 18
  jmp isr_common

; 19: SIMD Floating-Point Exceptions
isr19:
  push byte 0
  push 19
  jmp isr_common

; 20: Virtualization Exceptions
isr20:
  push byte 0
  push 20
  jmp isr_common

; 21: Reserved Exceptions (With Error Code)
isr21:
  push 21
  jmp isr_common

; 22: Reserved Exceptions
isr22:
  push byte 0
  push 22
  jmp isr_common

; 23: Reserved Exceptions
isr23:
  push byte 0
  push 23
  jmp isr_common

; 24: Reserved Exceptions
isr24:
  push byte 0
  push 24
  jmp isr_common

; 25: Reserved Exceptions
isr25:
  push byte 0
  push 25
  jmp isr_common

; 26: Reserved Exceptions
isr26:
  push byte 0
  push 26
  jmp isr_common

; 27: Reserved Exceptions
isr27:
  push byte 0
  push 27
  jmp isr_common

; 28: Reserved Exceptions
isr28:
  push byte 0
  push 28
  jmp isr_common

; 29: Reserved Exceptions
isr29:
  push byte 0
  push 29
  jmp isr_common

; 30: Reserved Exceptions
isr30:
  push 30
  jmp isr_common

; 31: Reserved Exceptions
isr31:
  push byte 0
  push 31
  jmp isr_common