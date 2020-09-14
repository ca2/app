#include "framework.h"
#include "_pcre.h"


pcre_code::pcre_code()
{

}


pcre_code::~pcre_code()
{

}





__pointer(pcre_code) pcre_code::compile(pcre_context* m_pcreContext, const string& str)
{

   __pointer(pcre_context_impl) pimpl = m_pcreContext;

   auto pcode = __new(pcre_code_impl(pimpl));

   pcode->compile(str);

   return pcode;

}
