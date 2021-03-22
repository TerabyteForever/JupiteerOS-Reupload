#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <sys/shell.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <sys/timer.h>
#include <libc/stdint.h>
#include <libc/string.h>
#include <libc/stdlib.h>

int kernel_main(){
  clear_screen();
  init_gdt();
  init_idt();

  char str[24] = "Welcome to JupiteerOS!\n";
  printf("%s",str);

  /* Example interrupts
   * asm volatile("int $0x3");
   * asm volatile("int $0x2"); */

  uint32_t a = malloc(8);
  uint32_t b = malloc(8);
  uint32_t c = malloc(8);

  printf("a: %x\n", a);
  printf("b: %x\n", b);
  printf("c: %x", c);

  // Initialize keyboard
  init_keyboard();
  // Initialize prompt
  init_prompt();
  
  while(1){
    keyboard_handler();
  }
  /* Sleep 20 second
   * sleep(20); */
  
  return 0;
}