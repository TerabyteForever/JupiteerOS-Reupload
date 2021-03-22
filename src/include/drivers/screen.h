#ifndef TTY_H
#define TTY_H
#include <libc/stdint.h>

#define VGA_WIDTH  				 80
#define VGA_HEIGHT				 25
#define VGA_COMMAND_PORT         0x3D4
#define VGA_DATA_PORT            0x3D5
#define VGA_HIGH_BYTE_COMMAND    14
#define VGA_LOW_BYTE_COMMAND     15

struct term_struct{
  int col;
  int row;
};

void clear_screen();
void print(const char *string);
void color_print(const char* str,uint8_t col);
void new_line();
void reset_screen();
void print_char(char c);
void back_space();
void print_time(char *sec);

#define BLACK_COL           0
#define BLUE_COL            1
#define GREEN_COL           2
#define CYAN_COL            3
#define RED_COL             4
#define MAGENTA_COL         5
#define BROWN_COL           6
#define LIGHT_GREY_COL      7
#define DARK_GREY_COL       8
#define LIGHT_BLUE_COL      9
#define LIGHT_GREEN_COL     10
#define LIGHT_CYAN_COL      11
#define LIGHT_RED_COL       12
#define LIGHT_MAGENTA_COL   13
#define LIGHT_BROWN_COL     14
#define WHITE_COL           15

#endif // TTY_H