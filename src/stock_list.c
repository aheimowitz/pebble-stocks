#include <pebble.h>
#include "stock_list.h"

#define KEY 0

static stock_list_t list = {.size = 0};

stock_list_t* get_stock_list()
{
   if (list.size == 0)
   {
      /*list.size = 2;
      strncpy(list.symbols[0], "FB", SYMBOL_SIZE);
      strncpy(list.symbols[1], "GOGL", SYMBOL_SIZE);*/
      list.size = persist_get_size(KEY);
      if (list.size == 0)
         return NULL;
      if (persist_read_data(0, list.symbols, list.size) == E_DOES_NOT_EXIST)
         return NULL;
      list.size/=SYMBOL_SIZE;
   }
   return &list;
}

int get_stock_list_size()
{
   return persist_get_size(KEY)/SYMBOL_SIZE;
}

int set_stock_list(char** symbols, int size)
{
   if (symbols == NULL)
      return 0;
   char* symbol_array = malloc(size*SYMBOL_SIZE);
   if (symbol_array == NULL)
      return 0;
   int i;
   for(i=0;i<size;i++)
      strncpy(symbol_array+i*SYMBOL_SIZE, symbols[i], SYMBOL_SIZE);

   int count = persist_write_data(KEY, symbol_array, size*SYMBOL_SIZE);

   free(symbol_array);
   return count;
}

void delete_stock_list()
{
   persist_delete(0);
}
