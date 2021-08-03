#include "framework.h"
#include "_regular_expression_pcre2.h"


namespace regular_expression_pcre2
{


   code::code()
   {

   }


   code::~code()
   {

   }


   __pointer(code) code::compile(pcre_context * m_pcreContext, const ::string & str)
   {

      __pointer(pcre_context_impl) pimpl = m_pcreContext;

      auto pcode = __new(code_impl(pimpl));

      pcode->compile(str);

      return pcode;

   }


} // namespace regular_expression_pcre2



