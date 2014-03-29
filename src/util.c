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
