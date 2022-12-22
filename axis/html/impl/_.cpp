#include "framework.h"
#include "acme/primitive/string/string.h"


void trim001(string & str)
{

   uchar uch;

   while (str.length() > 0)
   {
      uch = str[0];
      if (isdigit(uch) || isalpha(uch))
         break;
      str = str.substr(1);
   }
   while (str.length() > 0)
   {
      uch = str[str.length() - 1];
      if (isdigit(uch) || isalpha(uch))
         break;
      str = str.left(str.length() - 1);
   }
}


