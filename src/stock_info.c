#include <pebble.h>
#include "stock_info.h"
#include "stock_getter.h"
#include "stock_list.h"
#include "util.h"

//144 x 168

//#define GRAPH_SIZE 20

static char* text_info_default =  "OP: -\nHI: -\nLO: -\nCL: -";

static Window *window;
static TextLayer* text_symbol;
static TextLayer* text_value_diff;
static TextLayer* text_value_info;
static char str_symbol[20];
static char str_value_diff[20];
static char str_value_info[80];
static int current_index;

static TextLayer* background_workaround;

static stock_t stock_info;

//static GPoint graph_points[GRAPH_SIZE+2];
//static GPathInfo graph_info = { GRAPH_SIZE+2, graph_points };
//static GPath* graph;

//static GFont font_stock_name;
/*
static void init_graph()
{
   srand(0);
   int i;
   graph_points[0] = (GPoint){ 8, 40 };
   for(i=1;i<=GRAPH_SIZE;i++)
   {
      graph_points[i].x = 8+i*5;
      graph_points[i].y = 40+(int) ((float)rand()/RAND_MAX*40);
   }
   graph_points[GRAPH_SIZE+1] = (GPoint){ 8+GRAPH_SIZE*5, 40 };
}

static void graph_draw(struct Layer* layer, GContext* ctx)
{
   gpath_draw_outline(ctx, graph);
}*/

static void update_text()
{
   float percent = stock_t_percent(&stock_info);
   float difference = stock_t_difference(&stock_info);

   /*int dec_pc = (int)(percent*100);
   int int_pc = dec_pc/100;
   if (dec_pc < 0) dec_pc = -dec_pc;
   int frc_pc = dec_pc%100;

   int dec_ab = (int)(difference*100);
   int int_ab = dec_ab/100;
   if (dec_ab < 0) dec_ab = -dec_ab;
   int frc_ab = dec_ab%100;*/

   char str_percent[10];
   char str_difference[10];

   print_float(str_percent, sizeof(str_percent), percent, true);
   print_float(str_difference, sizeof(str_difference), difference, true);


   snprintf(str_value_diff, sizeof(str_value_diff),
            "%s (%s%%)", str_percent, str_difference);
   char str_op[10];
   char str_hi[10];
   char str_lo[10];
   char str_cl[10];

   print_float(str_op, sizeof(str_op), stock_info.open, false);
   print_float(str_hi, sizeof(str_hi), stock_info.high, false);
   print_float(str_lo, sizeof(str_lo), stock_info.low, false);
   print_float(str_cl, sizeof(str_cl), stock_info.close, false);

   snprintf(str_value_info, sizeof(str_value_info),
            "OP: %s\nHI: %s\nLO: %s\nCL: %s", str_op, str_hi, str_lo, str_cl);
   text_layer_set_text(text_value_diff, str_value_diff);
   text_layer_set_text(text_value_info, str_value_info);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
   //set_stock_value_str();
   stock_info_set_symbol_index(current_index-1);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
   //set_stock_value_str();
   stock_info_set_symbol_index(current_index+1);
}

static void click_config_provider(void *context)
{
   window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
   window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window)
{
   Layer *window_layer = window_get_root_layer(window);
   GRect bounds = layer_get_bounds(window_layer);

   //Stock name (at the top)
   text_symbol = text_layer_create((GRect) {
         .origin = { 8, 8 },
         .size = { bounds.size.w-16, 20 }
   });
   text_layer_set_text(text_symbol, "???");
   text_layer_set_text_alignment(text_symbol, GTextAlignmentCenter);
   text_layer_set_background_color(text_symbol, GColorBlack);
   text_layer_set_text_color(text_symbol, GColorWhite);


   //Stock value (at the bottom)
   text_value_diff = text_layer_create((GRect) {
         .origin = { 8, bounds.size.h-28 },
         .size = { bounds.size.w-16, 20 }
   });
   text_layer_set_text(text_value_diff, "-----");
   text_layer_set_text_alignment(text_value_diff, GTextAlignmentCenter);

   //Stock value (at the bottom)
   text_value_info = text_layer_create((GRect) {
         .origin = { 8, 28 },
         .size = { bounds.size.w-16, bounds.size.h-56 }
   });
   text_layer_set_text(text_value_info, text_info_default);

   background_workaround = text_layer_create(bounds);

   
   layer_add_child(window_layer, text_layer_get_layer(background_workaround));
   layer_add_child(window_layer, text_layer_get_layer(text_symbol));
   layer_add_child(window_layer, text_layer_get_layer(text_value_diff));
   layer_add_child(window_layer, text_layer_get_layer(text_value_info));
   //layer_set_update_proc(window_layer, graph_draw);
}

static void window_unload(Window *window)
{
   text_layer_destroy(text_symbol);
   text_layer_destroy(text_value_diff);
   text_layer_destroy(text_value_info);
   text_layer_destroy(background_workaround);

   text_symbol = NULL;
   text_value_diff = NULL;
   text_value_info = NULL;
   background_workaround = NULL;
}

/*Initialize the stock info page*/
void stock_info_init(void)
{
   //Create window
   window = window_create();
   window_set_click_config_provider(window, click_config_provider);
   window_set_window_handlers(window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
   });

   //init_graph();

   //graph = gpath_create(&graph_info);

   //font_stock_name = fonts_load_custom_font(
   //      resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_20));


   stock_info.valid = false;
   //stock_info_update();
}

/*Destroy the stock info page*/
void stock_info_deinit(void)
{
   window_destroy(window);
   window = NULL;
}

/*Get the stock info page window*/
Window* stock_info_get_window(void)
{
   return window;
}

/*Sets the symbol for the stock page*/
void stock_info_set_symbol_index(int index)
{
   stock_list_t* list = get_stock_list();
   if (list == NULL)
      return;
   if (index < 0)
      index = list->size-1;
   else if (index >= list->size)
      index = 0;
   char* symbol_name = list->symbols[index];
   current_index = index;
   

   strncpy(str_symbol, symbol_name, SYMBOL_SIZE);
   text_layer_set_text(text_symbol, str_symbol);
   stock_info.valid = true;
   stock_info_update();
}

/*Updates the information for the current stock symbol*/
void stock_info_update(void)
{
   if (stock_info.valid)
   {
      bool res = get_stock_info(str_symbol, &stock_info);
      if (!res)
      {
         //Something bad happened
         text_layer_set_text(text_value_diff, "Error Occurred");
      }
      else if (stock_info.valid)
      {
         //This is what we want
         update_text();
      }
      return;
   }
   //Something bad happened
   text_layer_set_text(text_value_diff, "Invalid Symbol");
}
