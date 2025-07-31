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

bool pcre_util_impl::compile(const ::scoped_string & scopedstr)
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



::collection::count pcre_util_impl::matches(const ::scoped_string & scopedstr, pcre_context*)
{

   return pcre_code_impl::matches(str, m_pcre);

}


::collection::count pcre_util_impl::matches(const ::scoped_string & scopedstr, character_count len, pcre_context*)
{

   return pcre_code_impl::matches(scopedstr, len);

}


::pointer<::strsize_range_array>pcre_util_impl::matches_ranges(const ::scoped_string & scopedstr)
{

   return pcre_code_impl::matches_ranges(str);

}


::pointer<::strsize_range_array>pcre_util_impl::matches_ranges(const ::scoped_string & scopedstr, character_count len)
{

   return pcre_code_impl::matches_ranges(scopedstr, len);

}



