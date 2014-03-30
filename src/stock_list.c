#include <pebble.h>
#include "stock_list.h"
#include "stock_getter.h"

#define KEY 0

static stock_list_t list = {.size = 0};

stock_list_t* get_stock_list()
{
   if (list.size == 0)
   {
      list.size = persist_get_size(KEY);
      if (list.size == 0)
         return NULL;
      if (persist_read_data(0, list.symbols, list.size) == E_DOES_NOT_EXIST)
         return NULL;
      list.size/=SYMBOL_SIZE;
      stock_list_refresh();
   }
   return &list;
}

int get_stock_list_size()
{
   return persist_get_size(KEY)/SYMBOL_SIZE;
}

int set_stock_list(char* symbols)
{
   if (symbols == NULL)
      return 0;

   int size = symbol_split(symbols, &list.symbols, MAX_SYMBOLS);

   int count = persist_write_data(KEY, list.symbols, size*SYMBOL_SIZE);

   list.size = size;
   stock_list_refresh();

   return count;
}

void delete_stock_list()
{
   persist_delete(0);
}

void stock_list_refresh()
{
   get_stock_info_multi(*list.symbols, list.infos, list.size);
}
