#ifndef STOCK_INFO_H
#define STOCK_INFO_H

/*Initialize the stock info page*/
void page_stock_info_init(void);

/*Destroy the stock info page*/
void page_stock_info_deinit(void);

/*Show the stock info page window*/
void page_stock_info_show(int index);

/*Sets the symbol for the stock page*/
void page_stock_info_set_symbol_index(int index);

/*Updates the information for the current stock symbol*/
void page_stock_info_update(void);

#endif //STOCK_INFO_H
