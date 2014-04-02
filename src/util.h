#ifndef UTIL_H
#define UTIL_H

#include <pebble.h>

/*Prints a float to a character buffer.
  If sign is true a '+' is printed before a positive number*/
void print_float(char* buffer, int size, float number, bool sign);

/*Returns a pointer to the first occurrence of c in str*/
//char* strchr(char* str, char c);

/*Returns a pointer to the first occurrence of any character in cs in str*/
char* strchrs(char* str, char* cs);

#endif //UTIL_H
