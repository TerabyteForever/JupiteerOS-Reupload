#include <sys/io.h>
#include <sys/pic.h>

/* Forces the CPU to wait for an I/O operation to complete. 
 * only use this when there's nothing like a status register
 * or an IRQ to tell you the info has been received. */
static inline void io_wait(void){
  asm volatile("jmp 1f\n\t" 
               "1:jmp 2f\n\t"
               "2:" );
}

void PIC_remap(int offset1, int offset2){
  uint8_t a1, a2;

  // Save masks
  a1 = inb(MASTER_PIC_DATA);                        
  a2 = inb(SLAVE_PIC_DATA);

  // Starts the initialization sequence (in cascade mode)
  outb(MASTER_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);  
  io_wait();
  outb(SLAVE_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);
  io_wait();

  // ICW2: Master PIC vector offset
  outb(MASTER_PIC_DATA, offset1);                 
  io_wait();
  // ICW2: Slave PIC vector offset
  outb(SLAVE_PIC_DATA, offset2);                
  io_wait();
  // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  outb(MASTER_PIC_DATA, 4);   
  io_wait();
  // ICW3: tell Slave PIC its cascade identity (0000 0010)
  outb(SLAVE_PIC_DATA, 2);    
  io_wait();

  outb(MASTER_PIC_DATA, ICW4_8086);
  io_wait();
  outb(SLAVE_PIC_DATA, ICW4_8086);
  io_wait();

  // Restore saved masks
  outb(MASTER_PIC_DATA, a1); 
  outb(SLAVE_PIC_DATA, a2);
}