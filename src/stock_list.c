#include <pebble.h>
#include "stock_list.h"
#include "stock_getter.h"
#include "util.h"

#define KEY 0

static stock_list_t list = {.size = -1};
static stock_t invalid_info = {.open = -1, .high = -1, .low = -1, .close = -1, .current = -1, .valid = false};

static void default_list()
{
   list.size = 1;
   strcpy(list.symbols, "FB");
}

stock_list_t* get_stock_list()
{
   if (list.size == -1)
   {
      list.size = persist_get_size(KEY);
      if (list.size == 0 ||
          persist_read_data(0, list.symbols, list.size) == E_DOES_NOT_EXIST)
            default_list();
      else
         list.size/=SYMBOL_SIZE;
      stock_list_refresh();
   }
   return &list;
}

int stock_list_get_size()
{
   return persist_get_size(KEY)/SYMBOL_SIZE;
}

int set_stock_list(char* symbols)
{
   if (symbols == NULL)
      return 0;

   int size = symbol_split(symbols, list.symbols, MAX_SYMBOLS);

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
   get_stock_info_multi(list.symbols, list.infos, list.size);
}

char* stock_list_get_symbol(int index)
{
   get_stock_list();
   if (index < 0 || index > list.size)
      return "???";
   return list.symbols+index*SYMBOL_SIZE;
}
stock_t* stock_list_get_info(int index)
{
   get_stock_list();
   if (index < 0 || index > list.size)
      return &invalid_info;
   return &list.infos[index];
}
