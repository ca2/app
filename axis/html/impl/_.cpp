#include "framework.h"
#include "acme/primitive/string/string.h"


void trim001(string & str)
{

   uchar uch;

   while (str.get_length() > 0)
   {
      uch = str[0];
      if (isdigit(uch) || isalpha(uch))
         break;
      str = str.Mid(1);
   }
   while (str.get_length() > 0)
   {
      uch = str[str.get_length() - 1];
      if (isdigit(uch) || isalpha(uch))
         break;
      str = str.Left(str.get_length() - 1);
   }
}


