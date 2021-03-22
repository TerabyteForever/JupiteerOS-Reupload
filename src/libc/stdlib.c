#include <libc/stdlib.h>
#include <mm/heap.h>

uint32_t malloc(uint32_t size){
  return malloc_os(size, 0, 0);
}