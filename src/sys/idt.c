#include <libc/string.h>
#include <sys/idt.h>
#include <sys/pic.h>

void set_gate(
  int32_t num,
  void(*base),
  uint16_t sel,
  unsigned g_type);

extern void idt_flush(idt_ptr_t*);

// IDT contains 256 entries
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_idt(){
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = idt_entries;

  memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);
  
  // ISRs are configured through the Interrupt Descriptor Table.

            /* Interrupt Service Routines */
  /*
  No #            Description            Error Code
  0   Division By Zero Exception              No
  1   Debug Exception                         No
  2   Non Maskable Interrupt Exception        No
  3   Breakpoint Exception                    No
  4   Into Detected Overflow Exception        No
  5   Out of Bounds Exception                 No
  6   Invalid Opcode Exception                No
  7   No Coprocessor Exception                No
  8   Double Fault Exception                  Yes
  9   Coprocessor Segment Overrun Exception   No
  10  Bad TSS Exception                       Yes
  11  Segment Not Present Exception           Yes
  12  Stack Fault Exception                   Yes
  13  General Protection Fault Exception      Yes
  14  Page Fault Exception                    Yes
  15  Unknown Interrupt Exception             No
  16  Coprocessor Fault Exception             No
  17  Alignment Check Exception               No
  18  Machine Check Exception                 No
  19  SIMD Floating-Point Exceptions          No
  20  Virtualization Exceptions               No
  21 to 31  Reserved Exceptions               No
  32 to 255 Maskable Interrupts               No */

  /* 32-bit interrupt gate */
  /* Selector: P=1, DPL=00, S=0 => 1000 = 0x08 
   * interrupt gate Type: 1110 = 0xE */
  set_gate(0, isr0, 0x08, 0xE);
  set_gate(1, isr1, 0x08, 0xE);
  set_gate(2, isr2, 0x08, 0xE);
  set_gate(3, isr3, 0x08, 0xE);
  set_gate(4, isr4, 0x08, 0xE);
  set_gate(5, isr5, 0x08, 0xE);
  set_gate(6, isr6, 0x08, 0xE);
  set_gate(7, isr7, 0x08, 0xE);
  set_gate(8, isr8, 0x08, 0xE);
  set_gate(9, isr9, 0x08, 0xE);
  set_gate(10, isr10, 0x08, 0xE);
  set_gate(11, isr11, 0x08, 0xE);
  set_gate(12, isr12, 0x08, 0xE);
  set_gate(13, isr13, 0x08, 0xE);
  set_gate(14, isr14, 0x08, 0xE);
  set_gate(15, isr15, 0x08, 0xE);
  set_gate(16, isr16, 0x08, 0xE);
  set_gate(17, isr17, 0x08, 0xE);
  set_gate(18, isr18, 0x08, 0xE);
  set_gate(19, isr19, 0x08, 0xE);
  set_gate(20, isr20, 0x08, 0xE);
  set_gate(21, isr21, 0x08, 0xE);
  set_gate(22, isr22, 0x08, 0xE);
  set_gate(23, isr23, 0x08, 0xE);
  set_gate(24, isr24, 0x08, 0xE);
  set_gate(25, isr25, 0x08, 0xE);
  set_gate(26, isr26, 0x08, 0xE);
  set_gate(27, isr27, 0x08, 0xE);
  set_gate(28, isr28, 0x08, 0xE);
  set_gate(29, isr29, 0x08, 0xE);
  set_gate(30, isr30, 0x08, 0xE);
  set_gate(31, isr31, 0x08, 0xE);

  /* Master PIC start interrupt : 0x20
   * Slave PIC start interrupt  : 0x28 */
  PIC_remap(0x20, 0x28);

  set_gate(32, irq0, 0x08, 0xE);
  set_gate(33, irq1, 0x08, 0xE);
  set_gate(34, irq2, 0x08, 0xE);
  set_gate(35, irq3, 0x08, 0xE);
  set_gate(36, irq4, 0x08, 0xE);
  set_gate(37, irq5, 0x08, 0xE);
  set_gate(38, irq6, 0x08, 0xE);
  set_gate(39, irq7, 0x08, 0xE);
  set_gate(40, irq8, 0x08, 0xE);
  set_gate(41, irq9, 0x08, 0xE);
  set_gate(42, irq10, 0x08, 0xE);
  set_gate(43, irq11, 0x08, 0xE);
  set_gate(44, irq12, 0x08, 0xE);
  set_gate(45, irq13, 0x08, 0xE);
  set_gate(46, irq14, 0x08, 0xE);
  set_gate(47, irq15, 0x08, 0xE);

  idt_flush(&idt_ptr);
  // Enable hardware interrupts
  asm volatile ("sti");
}

void set_gate(int32_t num,void(*base),uint16_t sel,unsigned g_type){
  idt_entries[num].offset_low = (uint32_t)base & 0xffff;
  idt_entries[num].selector = sel;
  // Always set to 0.
  idt_entries[num].zero = 0;
  idt_entries[num].gate_type = g_type;
  // Set to 0 for interrupt and trap gates.
  idt_entries[num].s = 0;
  idt_entries[num].dpl = 0;
  // Set to 1 for used interrupts. 
  idt_entries[num].p = 1;
  idt_entries[num].offset_high = ((uint32_t)base >> 16) & 0xffff;
}