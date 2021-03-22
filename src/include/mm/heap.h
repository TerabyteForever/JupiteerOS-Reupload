#ifndef HEAP_H
#define HEAP_H

#include <libc/stdint.h>

/* Allocate a chunk of memory, size in size. If align == 1,
 * the chunk must be page-aligned. If pyhs_addr != 0, the pyhs_addrical
 * location of the allocated chunk will be stored into pyhs_addr.
 * This is the internal version of malloc. */
uint32_t malloc_os(uint32_t size, int align, uint32_t *pyhs_addr);

/* Allocate a chunk of memory, size in size. 
 * The chunk must be page aligned. */
uint32_t malloc_align(uint32_t size);

/* Allocate a chunk of memory, size in size.The pyhs_addrical address
 * is returned in pyhs_addr. pyhs_addr MUST be a valid pointer to uint32_t!*/
uint32_t malloc_pyhs(uint32_t size, uint32_t *pyhs_addr);

/* Allocate a chunk of memory, size in size.The pyhs_addrical address
 * is returned in pyhs_addr. It must be page-aligned.*/
uint32_t malloc_align_pyhs(uint32_t size, uint32_t *pyhs_addr);

#endif // HEAP_H