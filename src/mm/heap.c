#include <mm/heap.h>
#include <libc/stdlib.h>

// end is defined in link.ld file
extern uint32_t end;
uint32_t placement_addr = (uint32_t)&end;

#define PAGE_SZ               0x1000

/* Paging in x86(chapter 4 in the Intel manual [33]) consists of a 
 * page directory(PDT) that can contain references to 1024 page tables(PT), 
 * each of which can point to 1024 sections of physical memory called page
 * frames(PF).Each page frame is 4096 byte large.In a virtual (linear) 
 * address, the highest 10 bits specifies the offset of a page directory 
 * entry(PDE) in the current PDT, the next 10 bits the offset of a page 
 * table entry(PTE) within the page table pointed to by that PDE.The 
 * lowest 12 bits in the address is the offset within the page frame to 
 * be addressed.*/

/* The PDE and PTE structure is very similar to each other: 32 bits 
 * (4 bytes), where the highest 20 bits points to a PTE or PF, and the 
 * lowest 12 bits control access rights and other configurations. 4 bytes 
 * times 1024 equals 4096 bytes, so a page directory and page table both 
 * fit in a page frame themselves.*/

/* Page-aligned means the address is a multiple of the page size, 
 * i.e. on a page boundary.4096 is 0x1000 is hexa,so aligned addresses 
 * are all of the form 0xzzzzz000.*/

uint32_t malloc_os(uint32_t size,int align,uint32_t *pyhs_addr){
  /* 0xFFFFF000 is 11111111111111111111000000000000 in binary,so 
   * this & operation keeps the upper 20 bits of placement_address.*/
  if(align == 1 && (placement_addr & 0xFFFFF000)){
    // align the placement addr
    placement_addr &= 0xFFFFF000;
    placement_addr += PAGE_SZ;
  }

  // Save also the physical address 
  if(pyhs_addr)
    *pyhs_addr = placement_addr;

  uint32_t tmp = placement_addr;
  placement_addr += size;
  return tmp;
}

// page aligned
uint32_t malloc_align(uint32_t size){
  return malloc_os(size, 1, 0);
}

// returns a physical address
uint32_t malloc_pyhs(uint32_t size, uint32_t *pyhs_addr){
  return malloc_os(size, 0, pyhs_addr);
}

uint32_t malloc_align_pyhs(uint32_t size, uint32_t *pyhs_addr){
  return malloc_os(size, 1, pyhs_addr);
}