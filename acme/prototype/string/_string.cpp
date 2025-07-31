// Created by camilo on 2022-06-07 06:23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_string.h"
//#include "string.h"
//#include "acme/prototype/collection/numeric_array.h"


void replace_tab(character_count iOffset, string & strParam, int iWidth, strsize_array * piaTab, array < character_count * > intptra)
{

   auto psz = strParam.c_str();

   string str;

   //string strTab;

   auto pszStart = psz;

   decltype(scopedstrStart) pszNext = nullptr;

   while (*psz)
   {

      pszNext = unicode_next(scopedstr);

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

         str.append(scopedstrStart, psz - pszStart);

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

         if (::is_empty(scopedstrNext))
         {

            break;

         }

         //str.append(scopedstr, pszNext - psz);

         iOffset++;

      }

      psz = pszNext;

   }

   if (scopedstrNext > pszStart)
   {

      str.append(scopedstrStart, pszNext - pszStart);

   }

   strParam = str;

}


void replace_tab(character_count iOffset, string & strParam, int iWidth, ::array < character_count * > iaTab)
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


CLASS_DECL_ACME::string _(const ::scoped_string & scopedstr)
{

   return scopedstr;

}



