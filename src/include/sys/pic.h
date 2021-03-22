#ifndef PIC_H
#define PIC_H

/* The 8259 PIC controls the CPU's interrupt mechanism, 
 * by accepting several interrupt requests and feeding them to the processor in order. 
 * For instance, when a keyboard registers a keyhit, 
 * it sends a pulse along its interrupt line (IRQ 1) to the PIC chip, 
 * which then translates the IRQ into a system interrupt, and sends a message to interrupt 
 * the CPU from whatever it is doing. Part of the kernel's job is to either handle 
 * these IRQs and perform the necessary procedures (poll the keyboard for the scancode) 
 * or alert a userspace program to the interrupt (send a message to the keyboard driver).*/

#define MASTER_PIC_COMMAND  0x20  
#define MASTER_PIC_DATA     0x21 
#define SLAVE_PIC_COMMAND   0xA0
#define SLAVE_PIC_DATA      0xA1
// End-of-interrupt command code
#define PIC_EOI             0x20

// ICW4 (not) needed
#define ICW1_ICW4           0x01
// Initialization - required!
#define ICW1_INIT           0x10
// 8086/88 (MCS-80/85) mode
#define ICW4_8086           0x01

void PIC_remap(int offset1, int offset2);

#endif // PIC_H