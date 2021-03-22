#include <libc/stdint.h>
#include <sys/gdt.h>

// To access ASM functions from C code
extern void gdt_flush(uint32_t);
static void set_gate(int32_t, uint32_t, uint32_t, 
  uint8_t, uint8_t);

gdt_entry_t entries[5];
gdt_ptr_t gdt_ptr;

void init_gdt(){
  gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
  gdt_ptr.base  = (uint32_t)&entries;

  /* Access Bytes
  -------------------------------------
  |7                                 0|
  ------------------------------------
  | Pr | Prvl | S | Ex | DC | RW | Ac |    
  -------------------------------------
  
  Pr: Present bit. This must be 1 for all valid selectors.
  Privl: Privilege, 2 bits. Contains the ring level, 0 = highest (kernel), 
  3 = lowest (user applications).
  S: Descriptor type. This bit should be set for code or data segments and 
  should be cleared for system segments (eg. a Task State Segment)
  Ex: Executable bit. If 1 code in this segment can be executed, ie. a code 
  selector. If 0 it is a data selector.
  DC: Direction bit/Conforming bit. Tells the direction. 0 the segment grows up. 
  1 the segment grows down, ie. the offset has to be greater than the limit.
  RW: Readable bit/Writable bit.
  Ac: Accessed bit. Just set to 0. The CPU sets this to 1 when the segment 
  is accessed.

  Flags
  -------------------
  |7              4 |
  -------------------
  | Gr | Sz | 0 | 0 |
  -------------------

  Gr: Granularity bit. If 0 the limit is in 1 B blocks (byte granularity), 
  if 1 the limit is in 4 KiB blocks (page granularity).
  Sz: Size bit. If 0 the selector defines 16 bit protected mode. If 1 it 
  defines 32 bit protected mode. 

  Granularity = 1 (for 4KB pages)
  Size = 1 (32-bit style)
  1100 1111 as hex value = 0xCF  */

  // Null Segment
  set_gate(0, 0, 0, 0, 0);
  
  /* Code Segment
   * Pr=1,Privl=0(two bit longs),S=1,
   * Ex=1,DC=0,RW=1,Ac=0
   * 1001 1010 as hex value = 0x9A */
  set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  
  /* Data Segment 
   * Pr=1,Privl=0(two bit longs),S=1,
   * Ex=0,DC=0,RW=1,Ac=0
   * 1001 0010 as hex value = 0x92 */
  set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 
  
  /* User Mode Code Segment 
   * Pr=1,Privl=1(two bit longs),S=1,
   * Ex=1,DC=0,RW=1,Ac=0
   * 1111 1010 as hex value = 0xFA */
  set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 
  
  /* User Mode Data Segment 
   * Pr=1,Privl=1(two bit longs),S=1,
   * Ex=0,DC=0,RW=1,Ac=0
   * 1111 0010 as hex value = 0xF2 */
  set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 

  gdt_flush((uint32_t)&gdt_ptr);
}

static void set_gate(int32_t num, uint32_t base, uint32_t limit, 
  uint8_t access_byte, uint8_t flags){ 
  entries[num].base_low    = (base  /*& 0xFFFF*/);
  entries[num].base_middle = (base >> 16) /*& 0xFF*/;
  entries[num].base_high   = (base >> 24) /*& 0xFF*/;

  entries[num].limit_low   = (limit /*& 0xFFFF*/);
  entries[num].limit_high  = ((limit >> 16) /*& 0x0F*/); 
 
  access_byte |= 0x00; /*0x10*/
  entries[num].flags       = flags;
  entries[num].access_byte = access_byte;
}