#include "framework.h"
#include "_pcre.h"



pcre_context::pcre_context()
{

}


pcre_context::~pcre_context()
{

}


__pointer(regex) pcre_context::compile(const string& str)
{

   return pcre_code::compile(this, str);

}


__pointer(pcre_context) pcre_context::create_context(int iSizeData)
{

   return __new(pcre_context_impl(iSizeData));

}






