#include "framework.h"

#include "acme/_operating_system.h"


int debug_string_iterator()
{

   string str = "This is a phrase this is a link http://test.com/test_file?test_parameter=test_value";

   int iLinkLen = 0;

   int iColon = 0;

   for(auto character : str)
   {

      if (character_isalpha(character)
          || character == L'.'
          || character == L'/'
          || character == L'?'
          || character == L'&'
          || (character == L':' && iColon++ == 0))
      {

         iLinkLen++;

      }
      else
      {

         break;

      }

   }

   return iLinkLen;

}




//string string_format(const ::scoped_string & scopedstrFormat, ...)
//{
//
//   string str;
//
//   va_list argList;
//
//   va_start(argList, pszFormat);
//
//   str.formatf_arguments(pszFormat, argList);
//
//   va_end(argList);
//
//   return ::transfer(str);
//
//}
//

CLASS_DECL_ACME inline character_count safe_strlen(void * p, character_count n)
{

   if (p == nullptr)
   {

      return 0;

   }

   auto psz = (const char *)p;

   character_count i = 0;

   for (; i < n; i++)
   {

      if (psz[i] == '\0')
      {

         break;

      }

   }

   return i;

}



CLASS_DECL_ACME string demangle(const ::scoped_string & scopedstr);

CLASS_DECL_ACME void copy(::string & str, const subparticle & subparticle)
{

   str = demangle(typeid((::subparticle &)subparticle).name());

}






CLASS_DECL_ACME void erase_sharp_comment(::string& str)
{

   auto sharp = str.find_first('#');

   if (sharp)
   {

      str.truncate(sharp);

   }

}


CLASS_DECL_ACME void erase_sharp_comment(::string_array& stra)
{

   for (auto& str : stra)
   {

      erase_sharp_comment(str);

   }

}
