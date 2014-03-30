#ifndef STOCK_GETTER_H
#define STOCK_GETTER_H

#include <pebble.h>
#include "stock_t.h"

/*Initializes the getter*/
void stock_getter_init();
/*Deinitializes the getter*/
void stock_getter_deinit();

/*Gets information about a stock.
  Returns false if there is an error with the request.
  If this function returns true, the stock info may
  still be invalid (for example, if the stock symbol is invalid)*/
bool get_stock_info(char* symbol, stock_t* info);

/*Gets information about multiple stocks.
  Returns false if there is an error with the request.
  If this function returns true, the stock infos may
  still be invalid (for example, if a stock symbol is invalid)*/
bool get_stock_info_multi(char* symbols, stock_t* infos, int num);

bool get_stock_history(char* symbol, float* points, int num);

#endif //STOCK_GETTER_H
