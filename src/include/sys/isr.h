#ifndef ISR_H
#define ISR_H

#include <libc/stdint.h>

#define IRQ0   32
#define IRQ1   33
#define IRQ2   34
#define IRQ3   35
#define IRQ4   36
#define IRQ5   37
#define IRQ6   38
#define IRQ7   39
#define IRQ8   40
#define IRQ9   41
#define IRQ10  42
#define IRQ11  43
#define IRQ12  44
#define IRQ13  45
#define IRQ14  46
#define IRQ15  47

typedef struct reg{
  // Data segment selector
  uint32_t ds;
  // Pushed by pusha.
  uint32_t edi,esi,ebp,useless_value,ebx,edx,ecx,eax; 
  // Interrupt number and error code.
  uint32_t int_no,err_code;
  // Pushed by the processor automatically.
  uint32_t eip,cs,eflags,esp,ss; 
}reg_t;

typedef void (*isr_t)(reg_t*);

void register_interrupt_handler(uint8_t n, isr_t handler);

#endif // ISR_H