/*
That is a keyboard driver which expects the keyboard input from IRQ line 1! Which means that is a PS/2 keyboard driver!
*/

#include <drivers/keyboard.h>
#include <drivers/us_keyboard_map.h>
#include <drivers/screen.h>
#include <sys/shell.h>
#include <sys/io.h>
#include <sys/isr.h>
#include <libc/stdint.h>
#include <libc/string.h>

extern uint8_t us_keyboard_map[128];
#define BUFFER_SIZE 256

int buffer_index = 0;
char shell_buffer[BUFFER_SIZE]; 
char temp[BUFFER_SIZE];

void clear_buffer(){
  for(int i = 0; i < BUFFER_SIZE; i++)
    shell_buffer[i] = 0;
}

void keyboard_handler(){
  uint8_t status;
  char scan_code;

  // 0x64: Keyboard status port
  status = inb(0x64);

  // Check the data, is it empty?
  if(status & 0x01){
    // 0x60 : Keyboard data port
    scan_code = inb(0x60);

    if(scan_code < 0)
      return;
  
    // Backspace Key
    if(scan_code == 0x0E){
      /* if we're at the first character of the command
       * then avoid backspace to not to delete prompt.*/
      if(buffer_index <= 0)
        return;
      
      buffer_index--;
      shell_buffer[buffer_index] = '\0';
      back_space();
      return;
    }

    // 0x1C : Enter Key
    if (scan_code == 0x1C){
      if(!strcmp(shell_buffer, "help"))
        printf("\nuname: Print system information");
      else if(!strcmp(shell_buffer, "uname"))
        printf("\nJupiteerOS");
      else if(!strcmp(shell_buffer, "clear"))
        clear_screen();
      init_prompt();
      buffer_index = 0;
      clear_buffer();
      return;
    }

    char c = us_keyboard_map[(uint8_t)scan_code];
    printf("%c",c);
    shell_buffer[buffer_index] = c;
    buffer_index += 1;
  }

}

void init_keyboard(){ 
  register_interrupt_handler(IRQ1, &keyboard_handler); 
}