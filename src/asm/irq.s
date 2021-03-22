extern irq_handler

; When the processor receives an interrupt,it saves the contents of the essential registers 
; (instruction pointer, stack pointer, code and data segments, flags register) to the stack. 
; It then finds the interrupt handler location from our IDT and jumps to it. 

; Now, just like POSIX signal handlers,you don't get given any information about what interrupt 
; was called when your handler is run. Many handlers that just push the interrupt number (hardcoded 
; in the ASM) onto the stack, and call a common handler function.

; Some interrupts also push an error code onto the stack. Some of them don't push an
; error code, we push a dummy one.

irq_common:
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
  call irq_handler

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

; IRQs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 0: Programmable Interrupt Timer Interrupt 
irq0:
  ;irq number
  push byte 0
  ; interrupt number
  push byte 32
  jmp irq_common

; 1: Keyboard Interrupt 
irq1:
  ;irq number
  push byte 1
  ; interrupt number
  push byte 33
  jmp irq_common

; 2: PIC2
irq2:
  ;irq number
  push byte 2
  ; interrupt number
  push byte 34
  jmp irq_common

; 3: COM2
irq3:
  ;irq number
  push byte 3
  ; interrupt number
  push byte 35
  jmp irq_common

; 4: COM1
irq4:
  ;irq number
  push byte 4
  ; interrupt number
  push byte 36
  jmp irq_common

; 5: LPT 2
irq5:
  ;irq number
  push byte 5
  ; interrupt number
  push byte 37
  jmp irq_common

; 6: Floopy Disk
irq6:
  ;irq number
  push byte 6
  ; interrupt number
  push byte 38
  jmp irq_common

; 7: LPT 1
irq7:
  ;irq number
  push byte 7
  ; interrupt number
  push byte 39
  jmp irq_common

; 8: Real Time Clock
irq8:
  ;irq number
  push byte 8
  ; interrupt number
  push byte 40
  jmp irq_common

; 9: Free for peripherals/legacy SCSI/NIC 
irq9:
  ;irq number
  push byte 9
  ; interrupt number
  push byte 41
  jmp irq_common

; 10: Free for peripherals/legacy SCSI/NIC 
irq10:
  ;irq number
  push byte 10
  ; interrupt number
  push byte 42
  jmp irq_common

; 11: Free for peripherals/legacy SCSI/NIC 
irq11:
  ;irq number
  push byte 11
  ; interrupt number
  push byte 43
  jmp irq_common

; 12: PS2 Mouse
irq12:
  ;irq number
  push byte 12
  ; interrupt number
  push byte 44
  jmp irq_common

; 13: FPU/Coprocessor/Inter-processor 
irq13:
  ;irq number
  push byte 13
  ; interrupt number
  push byte 45
  jmp irq_common

; 14: Primary ATA Hard Disk 
irq14:
  ;irq number
  push byte 14
  ; interrupt number
  push byte 46
  jmp irq_common

; 15: Primary ATA Hard Disk 
irq15:
  ;irq number
  push byte 15
  ; interrupt number
  push byte 47
  jmp irq_common