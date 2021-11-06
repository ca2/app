#include "framework.h"
#include "_regular_expression_pcre2.h"


pcre_regex::pcre_regex()
{

}


pcre_regex::~pcre_regex()
{

}



__pointer(regex) pcre_regex::compile(const string& str)
{

   __pointer(pcre_context_impl) pcreContextImpl = pcre_context::create_context(0);

   auto putil = __new(pcre_util_impl(pcreContextImpl));

   putil->compile(str);

   return putil;

}
