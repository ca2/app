#include "framework.h"
#include "_.h"


namespace axis
{


   __pointer(regex) system::create_pcre(const string& str)
   {

      return pcre_regex::compile(str);

   }

   __pointer(regex_context) system::create_pcre_context(int iCount)
   {

      return pcre_context::create_context(iCount);
   }


   int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)
   {


      {

         throw_todo();

         return -1;

      }

   }

   
}  // namespace axis



