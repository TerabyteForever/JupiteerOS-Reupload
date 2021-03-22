#include <drivers/screen.h>
#include <libc/string.h>

void init_prompt(){
  new_line();
  color_print("jupiteer@jupiteerOS ",GREEN_COL);
}

void print_time(char* sec){
  reset_screen();
  for(int i = 0; i < strlen(sec); i++)
    printf("%c",sec[i]);
}