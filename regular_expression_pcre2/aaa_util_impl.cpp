#include "framework.h"
#include "_regular_expression_pcre2.h"


pcre_util_impl::pcre_util_impl(pcre_context_impl* ppcreContext):
pcre_code_impl(ppcreContext)
{

   m_pcre = m_pcreContext;

}


pcre_util_impl::~pcre_util_impl()
{


}

bool pcre_util_impl::compile(const string& str)
{


   if (!pcre_code_impl::compile(str))
      return false;


   if (m_pcre->m_pmd != nullptr)
   {

      pcre2_match_data_free(m_pcre->m_pmd);

      m_pcre->m_pmd = nullptr;

   }

   m_pcre->m_pmd = pcre2_match_data_create_from_pattern(m_pc, m_pcre->m_pgc);

   if (m_pcre->m_pmd == nullptr)
      return false;

   return true;

}



::count pcre_util_impl::matches(const string& str, pcre_context*)
{

   return pcre_code_impl::matches(str, m_pcre);

}


::count pcre_util_impl::matches(const ::string & psz, strsize len, pcre_context*)
{

   return pcre_code_impl::matches(psz, len);

}


__pointer(::str::range_array) pcre_util_impl::matches_ranges(const string& str)
{

   return pcre_code_impl::matches_ranges(str);

}


__pointer(::str::range_array) pcre_util_impl::matches_ranges(const ::string & psz, strsize len)
{

   return pcre_code_impl::matches_ranges(psz, len);

}



