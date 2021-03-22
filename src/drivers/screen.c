#include <drivers/screen.h>
#include <libc/stdint.h>
#include <libc/string.h>
#include <sys/io.h>

// VGA text buffer is located at physical memory address 0xB8000.
volatile uint16_t* VGA_BUFFER = (uint16_t*)0xB8000;

struct term_struct *term_ptr,term_t;

/* To set the cursor at row one, column zero (position 80 = 0x0050), 
   one would use the following assembly code instructions:

  out 0x3D4, 14      ; 14 tells the framebuffer to expect the 
                     ; highest 8 bits of the position
  out 0x3D5, 0x00    ; sending the highest 8 bits of 0x0050
  out 0x3D4, 15      ; 15 tells the framebuffer to expect the 
                     ; lowest 8 bits of the position
  out 0x3D5, 0x50    ; sending the lowest 8 bits of 0x0050 */

void move_cursor(uint16_t pos){
  outb(VGA_COMMAND_PORT, VGA_HIGH_BYTE_COMMAND);
  outb(VGA_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(VGA_COMMAND_PORT, VGA_LOW_BYTE_COMMAND);
  outb(VGA_DATA_PORT, pos & 0x00FF);
}

void reset_screen(){
  term_ptr->col = 0;
  term_ptr->row = 0;
}

void clear_screen(){
  uint16_t i = 0;    
  /* VGA mode 3 provides a text interface 80 characters 
   * wide and 25 characters lines per screen. */
  while(i < VGA_HEIGHT * VGA_WIDTH * 2)
    VGA_BUFFER[i++] = 0;
  reset_screen();
  move_cursor(0);
}

void new_line(){
  if(term_ptr->row >= VGA_HEIGHT){
    reset_screen();
    clear_screen();
  }
  term_ptr->col = 0;
  term_ptr->row++;
}

void print_char(char c){
  // New line character
  if (c == '\n')
    new_line();
  else{
    size_t index = (VGA_WIDTH * term_ptr->row) + term_ptr->col;
    VGA_BUFFER[index] = ((uint16_t)WHITE_COL << 8) | c;
    term_ptr->col++;
    move_cursor(index);
  }
}
 
void print(const char* str){
  for(size_t i=0; str[i] != '\0'; i++)
    print_char(str[i]);
}

void color_print(const char* str,uint8_t col){
  for(size_t i=0; str[i] != '\0'; i++){
    char c = str[i];
    // New line character
    if (c == '\n')
      new_line();
    else{
      size_t index = (VGA_WIDTH * term_ptr->row) + term_ptr->col;
      VGA_BUFFER[index] = ((uint16_t)col << 8) | c;
      term_ptr->col++;
      move_cursor(index);
    }
  }
}

void back_space(){
  term_ptr->col = term_ptr->col - 1;
  size_t index = (VGA_WIDTH * term_ptr->row) + term_ptr->col;
  VGA_BUFFER[index] = ((uint16_t)WHITE_COL << 8) | ' ';
  move_cursor(term_ptr->col + (term_ptr->row * VGA_WIDTH));
}