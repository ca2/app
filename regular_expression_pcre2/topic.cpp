//
// Created by camilo on 2021-05-07 07:24 BRT <3ThomasBS_!!
//
#include "framework.h"


namespace regular_expression_pcre2
{


   topic::topic()
   {

      m_pmatchdata = nullptr;


   }


   topic::~topic()
   {

      if (m_pmatchdata != nullptr)
      {

         pcre2_match_data_free(m_pmatchdata);

         m_pmatchdata = nullptr;

      }

   }


   ::e_status topic::create(const string & str)
   {

      m_str = str;

      auto pregularexpression = (regular_expression *)m_pregularexpression->m_pRegularExpression;

      auto pcontext = (context *) pregularexpression->m_pcontext->m_pContext;

      m_pmatchdata = pcre2_match_data_create(pregularexpression->m_iRangeCount + 1, pcontext->m_pgeneralcontext);

      auto iMatchResult = pcre2_match(pregularexpression->m_pcode, (PCRE2_SPTR)m_str.c_str(), m_str.get_length(), 0, 0, m_pmatchdata, nullptr);

      if(iMatchResult < 0)
      {

         m_cMatchCount = -1;

         return error_failed;

      }

      return ::success;

   }


   ::count topic::get_count() const
   {

      auto c = pcre2_get_ovector_count(m_pmatchdata);

      return c;

   }


   string topic::get_match(::index i) const
   {

      PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(m_pmatchdata);

      string str = m_str.substr(ovector[2 * i], ovector[2 * i + 1]);

      return str;

   }


   void topic::_get_range_array()
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

         m_rangea.add(::str::range(ovector[2 * i], ovector[2 * i + 1]));

      }


   }


//   bool topic::matches(const string& str)
//   {
//
//      int c = pcre2_match(m_pc, (PCRE2_SPTR)(const char*)str, str.get_length(), 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);
//
//      return c > 0;
//
//   }

//
//   bool topic::matches(const char* psz, strsize len)
//   {
//
//      int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);
//
//      return c > 0;
//
//   }


//   ::count topic::match_count(const string& str)
//   {
//
//      return match_count(str.c_str(), str.length());
//
//   }
//
//
//   ::count topic::match_count(const char* psz, strsize len)
//   {
//
//      int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);
//
//      return c;
//
//   }


//   __pointer(::str::range_array) topic::matches_ranges(const string& str)
//   {
//
//      return matches_ranges(str.c_str(), str.get_length());
//
//   }
//
//
//   __pointer(::str::range_array) topic::matches_ranges(const char* psz, strsize len)
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
//      auto prangeaMatches = __new(::str::range_array);
//
//      for (strsize i = 0; i < c; i++)
//      {
//
//         prangeaMatches->add(::str::range(ovector[2 * i], ovector[2 * i + 1]));
//
//      }
//
//      return prangeaMatches;
//
//   }


} // namespace regular_expression_pcre2



