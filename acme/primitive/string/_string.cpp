// Created by camilo on 2022-06-07 06:23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_string.h"
//#include "string.h"
//#include "acme/primitive/collection/numeric_array.h"


void replace_tab(strsize iOffset, string & strParam, int iWidth, strsize_array * piaTab, array < strsize * > intptra)
{

   auto psz = strParam.c_str();

   string str;

   //string strTab;

   auto pszStart = psz;

   decltype(pszStart) pszNext = nullptr;

   while (*psz)
   {

      pszNext = unicode_next(psz);

      if (*psz == '\t')
      {

         auto lenTab = iWidth - (iOffset % iWidth);

         for (auto pi : intptra)
         {

            if (*pi > iOffset)
            {

               (*pi) += lenTab - 1;

            }

         }

         str.append(pszStart, psz - pszStart);

         str.append(lenTab, ' ');

         pszStart = pszNext;

         iOffset += lenTab;

         if (piaTab != nullptr)
         {

            piaTab->add(lenTab);

         }

      }
      else
      {

         if (::is_empty(pszNext))
         {

            break;

         }

         //str.append(psz, pszNext - psz);

         iOffset++;

      }

      psz = pszNext;

   }

   if (pszNext > pszStart)
   {

      str.append(pszStart, pszNext - pszStart);

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



