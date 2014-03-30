#ifndef STOCK_LIST_H
#define STOCK_LIST_H

#define MAX_SYMBOLS 20
#define SYMBOL_SIZE 5

#include "stock_t.h"
#include "util.h"

typedef struct {
   char symbols[MAX_SYMBOLS][SYMBOL_SIZE];
   stock_t infos[MAX_SYMBOLS];
   int size;
} stock_list_t;

stock_list_t* get_stock_list();

int get_stock_list_size();

int set_stock_list(char* symbols);

void delete_stock_list();

void stock_list_refresh();

#endif //STOCK_LIST_H
