// Created by camilo on 2022-11-04 04:26 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "acid/primitive/collection/string_array.h"
#include "acid/primitive/string/str.h"


CLASS_DECL_ACID string_array stringa_from_strdup(::ansi_character ** ppParam)
{

   string_array stra;

   ::ansi_character ** ppsz = ppParam;

   while (*ppsz != nullptr)
   {

      stra.add(::string_from_strdup(*ppsz));

      ppsz++;

   }

   free(ppParam);

   return ::transfer(stra);

}


CLASS_DECL_ACID ::collection::count explode_command_line(string_array & stra, const ::string & str, address_array < char * > * argv)
{

   auto range = str();

   while (range.has_char())
   {

      stra.add(range.consume_command_line_argument());

   }

   if (argv != nullptr)
   {

      for (::collection::index i = 0; i < stra.get_count(); i++)
      {

         char * pch = (char *)stra.element_at(i).c_str();

         argv->add(pch);

      }

      argv->add(nullptr);

   }

   return stra.get_count();

}


CLASS_DECL_ACID string_array & csstidy_explode_ws(string_array & stra, char sep, const ::string & psz)
{

   ::string istring(psz);

   // 1 = st // 2 = str
   ::collection::index status = 1;
   char to = '\0';

   stra.add("");
   strsize num = 0;
   strsize len = istring.length();
   for (strsize i = 0; i < len; i++)
   {

      switch (status)
      {
      case 1:
         if (istring[i] == sep && !::str::simple_escaped(istring, i))
         {
            ++num;
            stra.add("");
         }
         else if ((istring[i] == '"' || istring[i] == '\'' || istring[i] == '(') && !::str::simple_escaped(istring, i))
         {
            status = 2;
            to = (istring[i] == '(') ? ')' : istring[i];
            stra.element_at(num) += ::string(istring[i]);
         }
         else
         {
            stra.element_at(num) += ::string(istring[i]);
         }
         break;

      case 2:
         if (istring[i] == to && !::str::simple_escaped(istring, i))
         {
            status = 1;
         }
         stra.element_at(num) += ::string(istring[i]);
         break;
      }

   }

   return stra;

}



