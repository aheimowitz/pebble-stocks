#ifndef STOCK_INFO_H
#define STOCK_INFO_H

/*Initialize the stock info page*/
void stock_info_init(void);

/*Destroy the stock info page*/
void stock_info_deinit(void);

/*Get the stock info page window*/
Window* stock_info_get_window(void);

/*Sets the symbol for the stock page*/
void stock_info_set_symbol_index(int index);

/*Updates the information for the current stock symbol*/
void stock_info_update(void);

#endif //STOCK_INFO_H
