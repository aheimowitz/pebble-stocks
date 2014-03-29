#ifndef STOCK_T_H
#define STOCK_T_H

#include <pebble.h>

typedef struct {
   float open;
   float high;
   float low;
   float close;
   bool valid;
} stock_t;

float stock_t_percent(stock_t* stock);
float stock_t_difference(stock_t* stock);

#endif //STOCK_T_H
