#include <libc/string.h>
#include <sys/io.h>
#include <sys/isr.h>
#include <sys/pic.h>

isr_t interrupt_handlers[256];

const char *interrupts[] = {
  "Division By Zero Exception",
  "Debug Exception",
  "Non Maskable Interrupt Exception",
  "Breakpoint Exception",
  "Into Detected Overflow Exception",
  "Out of Bounds Exception",
  "Invalid Opcode Exception",
  "No Coprocessor Exception",
  "Double Fault Exception",
  "Coprocessor Segment Overrun Exception",
  "Bad TSS Exception",
  "Segment Not Present Exception",
  "Stack Fault Exception",
  "General Protection Fault Exception",
  "Page Fault Exception",
  "Unknown Interrupt Exception",
  "Coprocessor Fault Exception",
  "Alignment Check Exception",
  "Machine Check Exception",
  "SIMD Floating-Point Exceptions",
  "Virtualization Exceptions",
};

void isr_handler(reg_t regs){
  int index = regs.int_no;
  
  printf("Received interrupt: ");
  if(index >= 21 && index <= 31)
    printf("Reserved Exception");
  if(index > 31 && index < 256)
    printf("Maskable Interrupt");
  else
    printf(interrupts[index]);
  printf("\n");
}

void irq_handler(reg_t *regs){
	/* If interrupt number > 40), we send a reset signal to the slave. 
	 * In either case, we send one to the master also. */
	if(regs->int_no >= 40)
		outb(SLAVE_PIC_COMMAND, PIC_EOI);

	outb(MASTER_PIC_COMMAND, PIC_EOI);

	if(interrupt_handlers[regs->int_no] != 0){
		isr_t handler = interrupt_handlers[regs->int_no];
		handler(regs);
	}

}

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}