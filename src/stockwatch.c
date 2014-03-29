#include "util.h"
#include "pebble.h"
#include "stock_info.h"
#include "stock_list.h"
#include "stock_t.h"

#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 3

static Window *window;


enum {
    STOCK_NAME = 0x0
};


// This is a menu layer
// You have more control than with a simple menu layer
static MenuLayer *menu_layer;

// You can draw arbitrary things in a menu item such as a background
static GBitmap *menu_background;

stock_list_t* stock_list;

// Each section has a number of items;  we use a callback to specify this
// You can also dynamically add and remove items using this
//FIXME
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return get_stock_list_size();
}

// A callback is used to specify the height of the section header
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  // This is a define provided in pebble.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Draw title text in the section header
  menu_cell_basic_header_draw(ctx, cell_layer, "Stocks");
}

// This is the menu item draw callback where you specify what each item should look like
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  char* symbol_name = stock_list->symbols[cell_index->row];
  float difference = stock_t_difference(&stock_list->infos[cell_index->row]);
  float percent = stock_t_percent(&stock_list->infos[cell_index->row]);
  char diff_string[25];
  char percent_string[25];
  char str[50];
  print_float(diff_string, 128, difference, true);
  print_float(percent_string, 128, percent, true);
  int total_size = (strlen(symbol_name) + strlen(diff_string))/2;
  snprintf(str, 256, "%s (%s%%)",diff_string,percent_string);
  //for(int x=0; x<(20-total_size;x++){
    //strcat(str," ");
  //}
  //strcat(str,diff_string);
  menu_cell_basic_draw(ctx, cell_layer,symbol_name, str,NULL);
}

// Here we capture when a user selects a menu item
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {

  stock_info_init();
  Window *stock_info_window = stock_info_get_window();
  window_stack_push (stock_info_window, true); 
  stock_info_set_symbol_index(cell_index->row);
}

// This initializes the menu upon window load
void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(menu_layer, window);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}


void in_received_handler(DictionaryIterator *received, void *context) {
    // incoming message received
    Tuple *stocks_tuple = dict_find(received, STOCK_NAME);
    //Tuple *passwd_tuple = dict_find(received, CONFIG_PASSWD);
    if(stocks_tuple){
        text_layer_set_text(text_layer, stocks_tuple->value->cstring);
    }else{
        text_layer_set_text(text_layer, "Enter stocks in your settings.");
    }
    
}


void window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(menu_layer);

  // And cleanup the background
  gbitmap_destroy(menu_background);
  window_destroy(window);
}

int main(void) {
  window = window_create();

  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  char* symbols[] = {"FB","GOOG", "SIRI", "T"};
  set_stock_list(symbols, 4);
  stock_list = get_stock_list();
  window_stack_push(window, true /* Animated */);

  app_event_loop();

  window_destroy(window);
}
