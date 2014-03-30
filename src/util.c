#include "util.h"

void print_float(char* buffer, int size, float number, bool sign)
{
   int dec = (int)(number*100);
   int int_part = dec/100;
   if (dec < 0) dec = -dec;
   int frc_part = dec%100;

   if (sign)
      snprintf(buffer, size, "%+d.%02d", int_part, frc_part);
   else
      snprintf(buffer, size, "%d.%02d", int_part, frc_part);
}

int symbol_split(char* symbols, char* dest, int max)
{
   char* head = symbols;
   char* tail = symbols;

   int i = 0;
   while(1)
   {
      if (*tail == 0 || *tail == ',')
      {
         strncpy(dest+i*SYMBOL_SIZE, head, (tail-head));
         head = tail+1;
         i++;
         if (i == max || *tail == 0)
            break; 
      }
      tail++;
   }
   return i;
}
