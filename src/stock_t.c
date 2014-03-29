#include "stock_t.h"

float stock_t_percent(stock_t* stock)
{
   if (!stock)
      return 0;
   if (stock->open != 0)
      return 100.0f*(stock->close-stock->open)/stock->open;
   return stock->close-stock->open;
}

float stock_t_difference(stock_t* stock)
{
   if (!stock)
      return 0;
   return stock->close-stock->open;
}
