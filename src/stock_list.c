#include <pebble.h>
#include "stock_list.h"

static stock_list_t list = {.size = 0};

stock_list_t* get_stock_list()
{
   if (list.size == 0)
   {
      list.size = 2;
      strncpy(list.symbols[0], "FB", SYMBOL_SIZE);
      strncpy(list.symbols[1], "GOGL", SYMBOL_SIZE);
      /*list.size = persist_get_size(0);
      if (list.size == 0)
         return NULL;
      if (persist_read_data(0, list.symbols, list.size) == E_DOES_NOT_EXIST)
         return NULL;
      list.size/=SYMBOL_SIZE;*/
   }
   return &list;
}
