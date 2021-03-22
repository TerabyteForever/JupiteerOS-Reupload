#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libc/stdarg.h>
#include <drivers/screen.h>

// Calculate the length of a string
int strlen(const char *s){
  int i = 0;
  while(s[i] != '\0') i++;
  return i;
}

// Compare two string
int strcmp(const char *s1, const char *s2){
  for(; *s1==*s2; s1++,s2++)
    if(*s1 == '\0')
      return 0;
  return *s1 - *s2;
}

/* The memset() function fills the first n bytes of the
 * memory area pointed to by s with the constant byte c.*/
void *memset(void *s, int c, size_t n){
  char *m = (char *)s;

  for (size_t i = 0; i < n; i++)
    m[i] = (uint8_t)c;

  return s;
}

void reverse_str(char s[]){
  int c;
  for(int i = 0, j = strlen(s) - 1; i < j; i++,j--){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

// Converts an integer to a string.
char *itoa(int val, char *buf, int base){
  static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  char temp;
  int sign,i = 0;

  // Sign
  if((sign = val) < 0)
    val = -val;

  // Convert
  do{
    buf[i++] = num[val % base];
  }while(val /= base);

  if(sign < 0)
    buf[i++] = '-';

  // End of the string
  buf = '\0';

  char *end = buf - 1;
  char *begin = buf;

  // Reverse string
  while (end > begin) {
    temp = *end;
    *end-- = *begin;
    *begin++ = temp;
  }

  return buf;
}

 // Converts an unsigned integer to a string.
char *uitoa(uint32_t val, char *buf, int radix) {
  uint32_t i = 0;
  uint32_t start = i;
  uint32_t temp = val;

  if(radix == 16){
    buf[i++] = '0';
    buf[i++] = 'x';
    start = i;
  }

  do{
    uint32_t a = temp % radix;
    if(a < 10) 
      buf[i++] = a + '0';
    else 
      buf[i++] = a + 'a' - 10;
  }while(temp /= radix);

  char *s = buf + start;
  char *e = buf + (i - 1);

  while(s < e){
    char t = *s;
    *s = *e;
    *e = t;
    s++; 
    e--;
  }

  buf[i] = 0;
  return buf;
}

int printf(const char *format, ...){
  char buf[20],c,*s;
  int val;

  /* ap is the object of va_list and it will hold the 
   * information needed to retrieve the additional 
   * arguments with va_arg */
  va_list ap;

  va_start(ap,format);
  
  /* d,i => int; decimal number
   * x => int; unsigned hexadecimal number
   * c => int; single character
   * s => char *; print characters from the string until a '\0' 
   * or the number of characters given by the precision.*/
  for(int i=0; i < strlen(format); i++){
    if (format[i] == '%'){
      i++;
      switch(format[i]){
        case 'i':
          val = va_arg(ap, int);
          itoa(val, buf, 10);
          print(buf);
          break;
        case 'x':
          val = va_arg(ap, uint32_t);
          uitoa(val, buf, 16);
          print(buf);
          break;
        case 'd':
          val = va_arg(ap, uint32_t);
          uitoa(val, buf, 10);
          print(buf);
          break;
        case 'c':
          c = (char)va_arg(ap, int);
          print_char(c);
          break;
        case 's':
          s = va_arg(ap, char*);
          print(s);
          break;
        default:
          print_char(format[i]);
      }
    } 
    else{
      print_char(format[i]);
    }
  }

  va_end(ap);
  return 0;
}