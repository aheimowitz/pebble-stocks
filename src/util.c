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

static char* new_strtok(char* str, const char* tokens);
static char *temp = NULL;

int symbol_split(char* symbols, char* dest, int max)
{
   char * pch, i=0;
   pch = new_strtok(symbols," ,");
   strcpy (dest+i*SYMBOL_SIZE,pch );
   i++;
   while (pch != NULL && i < max)
   {
      pch = new_strtok(NULL, " ,");
      strcpy (dest+i*SYMBOL_SIZE,pch );
      i++;  
   }
   return i;
}

static char* new_strtok(char* str, const char* tokens)
{
    int chars=0, len = strlen(tokens), flag=0;
    int i;
    //If string passed to function is not null, copy it to our static variable
    if(str!=NULL)
      temp = str;

    //If the string passed is NULL and even the copy is NULL, we are done and return NULL.
    else if(temp==NULL)
    return NULL;

    //If only the string passed is NULL and the copy still has data, work with it.
    else
    {
        str=temp;
    }

    
    
    //Run the loop till we find a token or our copy is fully parsed.
    while(*temp)
    {
        for( i=0;i<len;i++)
        {
            if(*temp==tokens[i])
            {
                if(chars==0)
                {
                    flag=1;
                    str++;
                }
                else
                {
                    temp++;
                    str[chars]='\0';
                    return str;
                }
            }
        }
        if(flag==0)
            chars++;
        temp++;
        flag=0;
    }
    temp=NULL;
    str[chars]='\0';
    return str;
}

