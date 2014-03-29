#include <stdio.h>
#define SYMBOL_SIZE 5
char* new_strtok(char* str, const char* tokens);
int main (){
 char str[] ="FB,Goog,Yaho,mtt,";
  char * pch, i=0;
  char dest [7][SYMBOL_SIZE];
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = new_strtok(str," ,");
  strcpy (dest[i],pch );
  i++;
  while (pch != NULL)
  {
  	//printf ("I am here\n");
    printf ("%s\n",pch);
    pch = new_strtok(NULL, " ,");
    //strcpy (dest[i],pch);
    i++;  
  }
  
  return 0;	
}

char* new_strtok(char* str, const char* tokens)
{
    //Making a static string to be used again on next function call.
    static char *temp;
    int chars=0, len = strlen(tokens), flag=0;
    int i;
    //If string passed to function is not null, copy it to our static variable
    if(str!=NULL)
    {
        temp=(char*)malloc(strlen(str));
        strcpy(temp,str);
    }

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

