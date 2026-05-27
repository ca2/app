#include "framework.h"
#include "_.h"


namespace axis
{


   ::pointer<regex>system::compile_pcre(const ::scoped_string & scopedstr)
   {

      return pcre_regex::compile(str);

   }

   ::pointer<regex_context>system::create_pcre_context(::i32 iCount)
   {

      return pcre_context::create_context(iCount);
   }


   ::i32 system::pcre_add_tokens(string_array_base& stra, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrRegexp, ::i32 nCount)
   {


      {

         throw_todo();

         return -1;

      }

   }

   
}  // namespace axis



