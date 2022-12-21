#include "framework.h"
#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/string/string.h"
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
//   str.format_arguments(pszFormat, argList);
//
//   va_end(argList);
//
//   return ::move(str);
//
//}
//

CLASS_DECL_ACME inline strsize safe_strlen(void * p, strsize n)
{

   if (p == nullptr)
   {

      return 0;

   }

   auto psz = (const char *)p;

   strsize i = 0;

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

CLASS_DECL_ACME void copy(::string & str, const particle & particle)
{

   str = demangle(typeid((::particle &)particle).name());

}


