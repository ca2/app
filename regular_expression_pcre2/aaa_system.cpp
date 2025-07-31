#include "framework.h"
#include "_.h"


namespace axis
{


   ::pointer<regex>system::compile_pcre(const ::scoped_string & scopedstr)
   {

      return pcre_regex::compile(str);

   }

   ::pointer<regex_context>system::create_pcre_context(int iCount)
   {

      return pcre_context::create_context(iCount);
   }


   int system::pcre_add_tokens(string_array& stra, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrRegexp, int nCount)
   {


      {

         throw_todo();

         return -1;

      }

   }

   
}  // namespace axis



