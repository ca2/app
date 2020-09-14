#include "framework.h"
#include "_pcre.h"


pcre_context_impl::pcre_context_impl(int iSizeData) 
{

   m_pimpl = this;

   m_pgc = pcre2_general_context_create(nullptr, nullptr, nullptr);

   m_pcc = pcre2_compile_context_create(m_pgc);

   m_iSizeData = iSizeData;

   if (m_iSizeData <= 0)
   {

      m_pmd = nullptr;

   }
   else
   {

      m_pmd = pcre2_match_data_create(m_iSizeData, m_pgc);

   }


}


pcre_context_impl::~pcre_context_impl()
{

   if (m_pmd != nullptr)
   {

      pcre2_match_data_free(m_pmd);

      m_pmd = nullptr;

   }


   if (m_pcc != nullptr)
   {

      pcre2_compile_context_free(m_pcc);

      m_pcc = nullptr;

   }


   if (m_pgc != nullptr)
   {

      pcre2_general_context_free(m_pgc);

      m_pgc = nullptr;

   }


}






//__pointer(pcre_context) pcre_context::create_context(int iSizeData)
//{
//
//   return __new(pcre_context_impl( iSizeData));
//
//}
////
//
//__pointer(regex) pcre_regex::compile(::object* pobject, const string& str)
//{
//
//   __pointer(pcre_context_impl) pcreContextImpl = pcre_context::create_context(pobject, 0);
//
//   auto putil = __new(pcre_util_impl(pcreContextImpl));
//
//   putil->compile(str);
//
//   return putil;
//
//}
//
//
//__pointer(pcre_code) pcre_code::compile(pcre_context* m_pcreContext, const string& str)
//{
//
//   __pointer(pcre_context_impl) pimpl = m_pcreContext;
//
//   auto pcode = __new(pcre_code_impl(pimpl));
//
//   pcode->compile(str);
//
//   return pcode;
//
//}
//
//
//namespace axis
//{
//
//
//   __pointer(regex) system::create_pcre(const string& str)
//   {
//
//      return pcre_regex::compile(this, str);
//
//   }
//
//   __pointer(regex_context) system::create_pcre_context(int iCount)
//   {
//
//      return pcre_context::create_context(this, iCount);
//   }
//
//
//   int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)
//   {
//
//      throw_todo();
//
//      return -1;
//
//   }
//
//
//} // namespace axis
//
//
//
//namespace axis
//{
//
//
//}
//
//
//
