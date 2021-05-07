#include "framework.h"


namespace regular_expression_pcre2
{


   regular_expression::regular_expression(pcre_context_impl* pcreContext)
   {

      m_pcreContext = pcreContext;
      m_pc = nullptr;

   }


   regular_expression::~regular_expression()
   {

      if (m_pc != nullptr)
      {

         pcre2_code_free(m_pc);

         m_pc = nullptr;

      }

   }


   bool regular_expression::compile(const string& str)
   {

      int e;

      PCRE2_SIZE eo;

      auto pcontext = (context *) m_pcontext->m_pContext;

      m_pc = pcre2_compile((PCRE2_SPTR)(const char*)str, str.get_length(), 0, &e, &eo, pcontext->m_pcompilecontext);

      if (m_pc == nullptr)
      {

         return false;

      }

      return true;

   }
   

   bool regular_expression::matches(const string& str)
   {

      int c = pcre2_match(m_pc, (PCRE2_SPTR)(const char*)str, str.get_length(), 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

      return c > 0;

   }


   bool regular_expression::matches(const char* psz, strsize len)
   {

      int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

      return c > 0;

   }


   ::count regular_expression::match_count(const string& str)
   {

      return match_count(str.c_str(), str.length());

   }

   
   ::count regular_expression::match_count(const char* psz, strsize len)
   {

      int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

      return c;

   }


   __pointer(::str::range_array) regular_expression::matches_ranges(const string& str)
   {

      return matches_ranges(str.c_str(), str.get_length());

   }


   __pointer(::str::range_array) regular_expression::matches_ranges(const char* psz, strsize len)
   {

      auto c = match_count(psz, len);

      if (c <= 0)
      {

         return nullptr;

      }

      PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(m_pcreContext->m_pimpl->m_pmd);

      auto prangeaMatches = __new(::str::range_array);

      for (strsize i = 0; i < c; i++)
      {

         prangeaMatches->add(::str::range(ovector[2 * i], ovector[2 * i + 1]));

      }

      return prangeaMatches;

   }


   bool regular_expression::replace(string& str, const string& strPrefix, string& strRet)
   {

      size_t s = maximum(256, str.get_length() + strPrefix.get_length() * 3);

      int err;

      while (true)
      {

         err = pcre2_substitute(
            m_pc,
            (PCRE2_SPTR8)str.c_str(),
            str.get_length(),
            0,
            PCRE2_SUBSTITUTE_GLOBAL, m_pcreContext->m_pimpl->m_pmd, nullptr, (PCRE2_SPTR8)strPrefix.c_str(), strPrefix.get_length(), (PCRE2_UCHAR8*)strRet.get_string_buffer(s), &s);

         strRet.release_string_buffer(s);

         if (err >= 0)
         {
            return true;

         }
         else if (err != PCRE2_ERROR_NOMEMORY)
         {

            return false;

         }


         s *= 2;

      }

      return true;

   }


} // namespace regular_expression_pcre2



