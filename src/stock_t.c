#include "stock_t.h"

float stock_t_percent(stock_t* stock)
{
   if (!stock)
      return 0;
   if (stock->open != 0)
      return 100.0f*(stock->current-stock->open)/stock->open;
   return stock->current-stock->open;
}

float stock_t_difference(stock_t* stock)
{
   if (!stock)
      return 0;
   return stock->current-stock->open;
}
