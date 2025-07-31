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


   ::pointer<code> code::compile(pcre_context * m_pcreContext, const ::scoped_string & scopedstr)
   {

      ::pointer<pcre_context_impl> pimpl = m_pcreContext;

      auto pcode = __allocate code_impl(pimpl);

      pcode->compile(str);

      return pcode;

   }


} // namespace regular_expression_pcre2



