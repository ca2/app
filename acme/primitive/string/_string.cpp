// Created by camilo on 2022-06-07 06:23 <3ThomasBorregaardSorensen!!
#include "framework.h"


void replace_tab(strsize iOffset, string & strParam, int iWidth, strsize_array * piaTab, array < strsize * > intptra)
{

   auto psz = strParam.c_str();

   string str;

   string strTab;

   while (*psz)
   {

      string strChar = ::str().get_utf8_char(psz);

      if (strChar.is_empty())
      {

         break;

      }
      else if (strChar == "\t")
      {

         strTab = string(' ', iWidth - (iOffset % iWidth));

         for (auto pi : intptra)
         {

            if (*pi > iOffset)
            {

               (*pi) += strTab.get_length() - 1;

            }

         }

         str += strTab;

         iOffset += strTab.get_length();

         if (piaTab != nullptr)
         {

            piaTab->add(strTab.get_length());

         }

      }
      else
      {

         str += strChar;

         iOffset++;

      }

      psz += strChar.get_length();

   }

   strParam = str;

}


void replace_tab(strsize iOffset, string & strParam, int iWidth, ::array < strsize * > iaTab)
{

   return replace_tab(iOffset, strParam, iWidth, nullptr, iaTab);

}


string _002Underscore(string str)
{

   str.replace_with("_", "-");

   str.replace_with("_", "/");

   str.replace_with("_", "\\");

   return str;

}



