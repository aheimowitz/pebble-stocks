#ifndef UTIL_H
#define UTIL_H

#include <pebble.h>
#include "stock_list.h"

void print_float(char* buffer, int size, float number, bool sign);

int symbol_split(char* symbols, char* dest, int max);

#endif //UTIL_H
