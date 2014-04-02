#ifndef STOCK_LIST_H
#define STOCK_LIST_H

#define MAX_SYMBOLS 20
#define SYMBOL_SIZE 5

#include "stock_t.h"

typedef struct {
   char* symbols[MAX_SYMBOLS];
   stock_t* quotes;
   int size;
} stock_list_t;

/*Callback function called when a quote is refreshed*/
typedef void (*stock_list_refresh_cb) (int index, bool success);

/*Allocates memory for the stock list. Returns whether successful*/
bool stock_list_init();
/*Frees memory for the stock list*/
void stock_list_deinit();

/*Returns the size of the stock list*/
int stock_list_get_size();


/*Gets the symbol for the stock at the given index.
  Returns "???" if the index is invalid.*/
char* stock_list_get_symbol(int index);



/*Gets the quote for the stock at the given index.
  Returns an invalid quote if the index is invalid.*/
stock_t* stock_list_get_quote(int index);

/*Gets the quote for the stock with the given symbol.
  Returns an invalid quote if the symbol is not in the list.*/
stock_t* stock_list_get_quote_from_symbol(char* symbol);


/*Gets the list index of the given symbol.
  Returns -1 if the symbol is not in the list.*/
int stock_list_get_index(char* symbol);



/*Sets the symbols in the stock list.
  The parameter should have the format SYM1,SYM2,SYM3,...
  where SYM1, SYM2, and SYM3 are stock symbols.
  The comma may be replaced with any punctuation mark
  Returns the number of symbols*/
int stock_list_set_symbols(char* symbols);

/*Sets the symbols in the stock list.*/
void stock_list_set_symbols_array(char** symbols, int count);



/*Attempts to refresh all stock quotes in the list.*/
void stock_list_refresh();

/*Attempts to refresh all stock quotes in the list.
  When finished, the callback function is called for each index*/
void stock_list_refresh_callback(stock_list_refresh_cb cb);

/*Attemps to refresh the stock quote at the given index.*/
void stock_list_refresh_index(int index);
/*Attemps to refresh the stock quote at the given index.
  When finished, the callback function is called for each index*/
void stock_list_refresh_index_callback(int index, stock_list_refresh_cb cb);


#endif //STOCK_LIST_H
