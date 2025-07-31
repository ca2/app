// Created by camilo on 2022-11-04 04:26 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/string/str.h"


CLASS_DECL_ACME string_array stringa_from_strdupa(::ansi_character ** ppParam)
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


CLASS_DECL_ACME ::collection::count explode_command_line(string_array & stra, const ::scoped_string & scopedstr, address_array < char * > * argv)
{

   auto range = str();

   while (range.has_character())
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


CLASS_DECL_ACME string_array & csstidy_explode_ws(string_array & stra, char sep, const ::scoped_string & scopedstr)
{

   ::string istring(scopedstr);

   // 1 = st // 2 = str
   ::collection::index status = 1;
   char to = '\0';

   stra.add("");
   character_count num = 0;
   character_count len = istring.length();
   for (character_count i = 0; i < len; i++)
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


CLASS_DECL_ACME char ** strdupa_from_stringa(const ::string_array & stra)
{
   
   auto pp = (char **) malloc((stra.size() + 1) * sizeof(char*));
   
   ::collection::index i = 0;
   
   for(; i < stra.size(); i++)
   {
    
      pp[i] = ::c::strdup(stra[i]);
      
   }
   
   pp[i] = nullptr;
   
   return pp;
   
}

