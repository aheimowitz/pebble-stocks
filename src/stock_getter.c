#include "stock_getter.h"
#include "stock_list.h"

static stock_t* infos;
static int info_count;
static int current;
static request_callback current_cb;

enum {
   QUOTE_KEY_SYMBOL = 0,
   QUOTE_KEY_OPEN   = 1,
   QUOTE_KEY_HIGH   = 2,
   QUOTE_KEY_LOW    = 3,
   QUOTE_KEY_CLOSE  = 4,
   QUOTE_KEY_LAST   = 5 };

static float to_float(char* str)
{
   int dec = 0;
   int frac = 0;
   int frac_div = 1;
   bool mode = false;

   int i=0;
   char c;

   while((c = str[i]))
   {
      if (c == '.')
         mode = true;
      if (c >= '0' && c <= '9')
      {
         int d = c-'0';
         if (mode)
         {
            frac = frac*10 + d;
            frac_div*=10;
         }
         else
            dec = dec*10 + d;
      }
      str++;
   }

   return dec + (float)frac/frac_div;
}

static void in_received_handler(DictionaryIterator *iter, void *context)
{
   APP_LOG(APP_LOG_LEVEL_DEBUG, "Here we are! %x", (int)iter);
   Tuple* symbol = dict_find(iter, QUOTE_KEY_SYMBOL);
   Tuple *open   = dict_find(iter, QUOTE_KEY_OPEN);
   Tuple *high   = dict_find(iter, QUOTE_KEY_HIGH);
   Tuple *low    = dict_find(iter, QUOTE_KEY_LOW);
   Tuple *close  = dict_find(iter, QUOTE_KEY_CLOSE);
   Tuple *last   = dict_find(iter, QUOTE_KEY_LAST);

   Tuple *tuple = dict_read_first(iter);
   int i=0;
   APP_LOG(APP_LOG_LEVEL_DEBUG, "Iterating through dict!");
   while (tuple) {
      i++;
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Tuple #%d", i);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "   Key: %ld", tuple->key);
      tuple = dict_read_next(iter);
   }
   APP_LOG(APP_LOG_LEVEL_DEBUG, "Done iterating!");
   

   if (!symbol || current == info_count)
   {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Symbol: %x, Current: %d", (int)symbol, current);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%x %x %x %x %x", (int)open, (int)high, (int)low, (int)close, (int)last);
      return;
   }

   APP_LOG(APP_LOG_LEVEL_DEBUG, "Good to go!");

   infos[current].open =    to_float(open->value->cstring);
   infos[current].high =    to_float(high->value->cstring);
   infos[current].low =     to_float(low->value->cstring);
   infos[current].close =   to_float(close->value->cstring);
   infos[current].current = to_float(last->value->cstring);

   current++;
   if (current_cb)
      current_cb(symbol->value->cstring, &infos[current]);
}

static void in_dropped_handler(AppMessageResult reason, void *context)
{
   APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!\n   Code: %d", reason);
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context)
{
   APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
}

void stock_getter_init()
{
  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_failed(out_failed_handler);
  // Init buffers
  app_message_open(64, 64);
}
void stock_getter_deinit()
{
   //TODO: Implement
}

bool send(char* symbol)
{
   if (symbol == NULL)
      return false;
   DictionaryIterator *iter;
   app_message_outbox_begin(&iter);
   if (iter == NULL)
   {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "null iter");
      return false;
   }
   else
   {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "not a null iter!");
   }

   Tuplet tuple = TupletCString(0, symbol);
   dict_write_tuplet(iter, &tuple);
   dict_write_end(iter);

   app_message_outbox_send();

   return true;
}

static void separate_symbols(char* symbols, char* dest, int count, int size)
{
   char* next = dest;
   int n = snprintf(next, size, "%s", symbols);
   next+=n;
   int i;
   for(i=1;i<count;i++)
   {
      n = snprintf(next, size-(next-dest), ",%s", symbols+i*SYMBOL_SIZE);
      next+=n;
   }
}

bool get_stock_info(char* symbol, stock_t* info, request_callback cb)
{
   if (!info || !symbol)
      return false;

   //TODO: Implement

   //For now, just return some default values

   infos = info;
   info_count = 1;
   current = 0;
   current_cb = cb;

   send(symbol);

   info->open = 60;
   info->current = 80;
   info->high = 90;
   info->low = 50;
   info->valid = true;

   return true;
}
bool get_stock_info_multi(char* symbols, stock_t* infos, int num, request_callback cb)
{
   if (!infos || !symbols)
      return false;
   if (num == 0)
      return true;

   char buffer[200];
   separate_symbols(symbols, buffer, num, sizeof(buffer));

   infos = infos;
   info_count = num;
   current = 0;
   current_cb = cb;

   send(buffer);

   //TODO: Implement
   int i;
   for(i=0;i<num;i++)
   {
      infos[i].open = 60;
      infos[i].current = 80;
      infos[i].high = 90;
      infos[i].low = 50;
      infos[i].valid = true;
   }

   return true;
}
bool get_stock_history(char* symbol, float* points, int num, request_callback cb)
{
   if (!symbol || !points || num == 0)
      return false;

   int i;
   for(i=0;i<num;i++)
   {
      points[i] = i*i;
   }
   return true;
}
