#include "framework.h"



void trim001(string & str)
{

   char uch;

   while (str.length() > 0)
   {
      uch = str[0];
      if (character_isdigit(uch) || character_isalpha(uch))
         break;
      str = str.substr(1);
   }
   while (str.length() > 0)
   {
      uch = str[str.length() - 1];
      if (character_isdigit(uch) || character_isalpha(uch))
         break;
      str = str.left(str.length() - 1);
   }
}


