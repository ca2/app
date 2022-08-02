//
// Created by camilo on 2021-05-07 07:24 BRT <3ThomasBS_!!
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


namespace regular_expression_pcre2
{


   result::result()
   {

      m_pmatchdata = nullptr;


   }


   result::~result()
   {

      if (m_pmatchdata != nullptr)
      {

         pcre2_match_data_free(m_pmatchdata);

         m_pmatchdata = nullptr;

      }

   }


   ::count result::get_count() const
   {

      return m_cMatchCount;

   }


   string result::get_match(::index i) const
   {

      PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(m_pmatchdata);

      string str = m_str.substr(ovector[2 * i], ovector[2 * i + 1]);

      return str;

   }


   void result::_get_range_array()
   {

      if(m_cMatchCount <= 0)
      {

         return;

      }

      if(m_cMatchCount == m_rangea.get_count())
      {

         return;

      }

      PCRE2_SIZE * ovector = pcre2_get_ovector_pointer(m_pmatchdata);

      m_rangea.set_size(m_cMatchCount);

      for (strsize i = 0; i < m_cMatchCount; i++)
      {

         m_rangea[i] = ::strsize_range(ovector[2 * i], ovector[2 * i + 1]);

      }


   }


//   bool result::matches(const string& str)
//   {
//
//      int c = pcre2_match(m_pc, (PCRE2_SPTR)(const ::string &)str, str.get_length(), 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);
//
//      return c > 0;
//
//   }

//
//   bool result::matches(const ::string & psz, strsize len)
//   {
//
//      int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);
//
//      return c > 0;
//
//   }


//   ::count result::match_count(const string& str)
//   {
//
//      return match_count(str.c_str(), str.length());
//
//   }
//
//
//   ::count result::match_count(const ::string & psz, strsize len)
//   {
//
//      int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);
//
//      return c;
//
//   }


//   __pointer(::strsize_range_array) result::matches_ranges(const string& str)
//   {
//
//      return matches_ranges(str.c_str(), str.get_length());
//
//   }
//
//
//   __pointer(::strsize_range_array) result::matches_ranges(const ::string & psz, strsize len)
//   {
//
//      auto c = match_count(psz, len);
//
//      if (c <= 0)
//      {
//
//         return nullptr;
//
//      }
//
//      PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(m_pcreContext->m_pimpl->m_pmd);
//
//      auto prangeaMatches = __new(::strsize_range_array);
//
//      for (strsize i = 0; i < c; i++)
//      {
//
//         prangeaMatches->add(::strsize_range(ovector[2 * i], ovector[2 * i + 1]));
//
//      }
//
//      return prangeaMatches;
//
//   }


} // namespace regular_expression_pcre2



