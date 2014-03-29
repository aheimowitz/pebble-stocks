#ifndef STOCK_LIST_H
#define STOCK_LIST_H

#define MAX_SYMBOLS 20
#define SYMBOL_SIZE 5

typedef struct {
   char symbols[MAX_SYMBOLS][SYMBOL_SIZE];
   int size;
} stock_list_t;

stock_list_t* get_stock_list();

#endif //STOCK_LIST_H
