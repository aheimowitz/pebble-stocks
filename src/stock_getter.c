#include "stock_getter.h"

void stock_getter_init()
{
   //TODO: Implement
}
void stock_getter_deinit()
{
   //TODO: Implement
}

bool get_stock_info(char* symbol, stock_t* info)
{
   if (!info || !symbol)
      return false;

   //TODO: Implement

   //For now, just return some default values

   info->open = 60;
   info->close = 80;
   info->high = 90;
   info->low = 50;
   info->valid = true;

   return true;
}
bool get_stock_info_multi(char* symbols, stock_t* infos, int num)
{
   if (!infos || !symbols)
      return false;
   if (num == 0)
      return true;

   //TODO: Implement
   int i;
   for(i=0;i<num;i++)
   {
      infos[i].open = 60;
      infos[i].close = 80;
      infos[i].high = 90;
      infos[i].low = 50;
      infos[i].valid = true;
   }

   return true;
}
