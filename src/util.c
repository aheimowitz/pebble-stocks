#include "util.h"

/*Prints a float to a character buffer.
  If sign is true a '+' is printed before a positive number*/
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

/*Returns a pointer to the first occurrence of c in str*/
/*char* strchr(char* str, char c)
{
   while(str)
   {
      if (*str == c)
         return str;
      str++;
   }
   return NULL;
}*/

/*Returns a pointer to the first occurrence of any character in cs in str*/
char* strchrs(char* str, char* cs)
{
   while(str)
   {
      if (strchr(cs, *str))
         return str;
      str++;
   }
   return NULL;
}
