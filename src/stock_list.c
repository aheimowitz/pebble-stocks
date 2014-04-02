#include <pebble.h>
#include "stock_list.h"
#include "stock_getter.h"
#include "util.h"

#define KEY 0

//Invalid symbol name
static char* symbol_invalid = "???";
//Stock list
static stock_list_t list = {.quotes = NULL, .size = 0};
//Invalid stock quote
static stock_t quote_invalid = {.symbol = "???", .valid = false};
//Array to store stock symbols
static char* symbols_list = NULL;

/*Allocates memory for the stock list*/
bool stock_list_init()
{
   //Allocate memory for symbols
   symbols_list = malloc(MAX_SYMBOLS*SYMBOL_SIZE);
   //Check for error
   if (!symbols_list)
      return false;

   //Allocate memory for quotes
   list.quotes = malloc(MAX_SYMBOLS*sizeof(stock_t));
   //Check for error
   if (!list.quotes)
   {
      free(symbols_list);
      symbols_list = NULL;
      return false;
   }


   for(int i=0;i<MAX_SYMBOLS;i++)
      list.symbols[i] = symbols_list+SYMBOL_SIZE;

   list.size = 0;
   return true;
}

/*Frees memory for the stock list*/
void stock_list_deinit()
{
   if (symbols_list)
      free(symbols_list);
   if (list.quotes)
      free(list.quotes);

   symbols_list = NULL;
   list.quotes = NULL;
   list.size = 0;
}

/*Returns the size of the stock list*/
int stock_list_get_size()
{
   return list.size;
}

/*Gets the symbol for the stock at the given index.
  Returns "???" if the index is invalid.*/
char* stock_list_get_symbol(int index)
{
   int size = stock_list_get_size();
   if (index < 0 || index >= size)
      return symbol_invalid;
   return list.symbols[index];
}

/*Gets the quote for the stock at the given index.
  Returns an invalid quote if the index is invalid.*/
stock_t* stock_list_get_quote(int index)
{
   int size = stock_list_get_size();
   if (index < 0 || index >= size)
      return &quote_invalid;
   return &list.quotes[index];
}

/*Gets the quote for the stock with the given symbol.
  Returns an invalid quote if the symbol is not in the list.*/
stock_t* stock_list_get_quote_from_symbol(char* symbol)
{
   int index = stock_list_get_index(symbol);
   return index == -1 ? &quote_invalid : &list.quotes[index];
}

/*Gets the list index of the given symbol.
  Returns -1 if the symbol is not in the list.*/
int stock_list_get_index(char* symbol)
{
   if (symbol)
      for(int i=0;i<list.size;i++)
      {
         if (strcmp(symbol, list.symbols[i]) == 0)
            return i;
      }
   return -1;
}

/*Sets the symbols in the stock list.
  The parameter should have the format SYM1,SYM2,SYM3,...
  where SYM1, SYM2, and SYM3 are stock symbols.
  The comma may be replaced with any punctuation mark.
  Returns the number of symbols, or 0 if the stock list is not initialized*/
int stock_list_set_symbols(char* symbols)
{
   if (!symbols_list || !symbols)
      return 0;

   char* head = symbols;
   char* tail = symbols;

   int n;
   int i=0;
   while(tail)
   {
      tail = strchrs(head, ", +");
      n = SYMBOL_SIZE;
      if (tail && (tail-head) < n)
         n = tail-head;

      strncpy(list.symbols[i], head, n);
      head = tail+1;
      i++;
   }
   for(int j=0;j<i;j++)
      list.quotes[i].valid = false;
   list.size = i;
   return i;
}

/*Sets the symbols in the stock list.*/
void stock_list_set_symbols_array(char** symbols, int count)
{
   if (!symbols_list || !symbols)
      return;

   for(int i=0;i<count;i++)
   {
      strncpy(list.symbols[i], symbols[i], SYMBOL_SIZE);
      list.quotes[i].valid = false;
   }
   list.size = count;
}

/*Attempts to refresh all stock quotes in the list.*/
void stock_list_refresh()
{
   stock_list_refresh_callback(NULL);
}

/*Attempts to refresh all stock quotes in the list.
  When finished, the callback function is called for each index*/
void stock_list_refresh_callback(stock_list_refresh_cb cb)
{
   //TODO: Implement
}

/*Attemps to refresh the stock quote at the given index.*/
void stock_list_refresh_index(int index)
{
   stock_list_refresh_index_callback(index, NULL);
}
/*Attemps to refresh the stock quote at the given index.
  When finished, the callback function is called for each index*/
void stock_list_refresh_index_callback(int index, stock_list_refresh_cb cb)
{
   //TODO: Implement
}
