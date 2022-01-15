#include "framework.h"


namespace regular_expression_pcre2
{


   regular_expression::regular_expression()
   {

      m_pRegularExpression = this;

      //m_pcreContext = pcreContext;
      m_pcode = nullptr;

   }


   regular_expression::~regular_expression()
   {

      if (m_pcode != nullptr)
      {

         pcre2_code_free(m_pcode);

         m_pcode = nullptr;

      }

   }


   void regular_expression::create(const string& str)
   {

      m_str = str;

      int e;

      PCRE2_SIZE eo;

      auto pcontext = (context *) m_pcontext->m_pContext;

      m_pcode = pcre2_compile((PCRE2_SPTR)(const char *)m_str, m_str.get_length(), 0, &e, &eo, pcontext->m_pcompilecontext);

      if (m_pcode == nullptr)
      {

         throw_status(error_failed);

      }

      ::u32 uRangeCount = 0;

      auto iResult = pcre2_pattern_info(m_pcode, PCRE2_INFO_CAPTURECOUNT, &uRangeCount);
//    may return:
//    PCRE2_ERROR_NULL           the argument code is NULL
//    PCRE2_ERROR_BADMAGIC       the "magic number" was not found
//    PCRE2_ERROR_BADOPTION      the value of what is invalid
//    PCRE2_ERROR_BADMODE        the pattern was compiled in the wrong mode
//    PCRE2_ERROR_UNSET          the requested information is not set

      if(iResult == 0)
      {

         m_iRangeCount = uRangeCount;

      }

      //return ::success;

   }



   __pointer(::regular_expression::topic) regular_expression::create_topic(const string& str)
   {

      auto ptopic = __new(class topic);

      ptopic->m_pregularexpression = this;

      //auto estatus = 
      
      ptopic->create(str);

      //if(!estatus)
      //{

      //   return nullptr;

      //}

      return ptopic;

   }



   bool regular_expression::replace(string& str, const string& strPrefix, string& strRet)
   {

      size_t s = maximum(256, str.get_length() + strPrefix.get_length() * 3);

      int err;

      while (true)
      {

         err = pcre2_substitute(
            m_pcode,
            (PCRE2_SPTR8)str.c_str(),
            str.get_length(),
            0,
            PCRE2_SUBSTITUTE_GLOBAL,
            /*m_pcreContext->m_pimpl->m_pmd*/
            nullptr,
            nullptr,
            (PCRE2_SPTR8)strPrefix.c_str(), strPrefix.get_length(),
            (PCRE2_UCHAR8*)strRet.get_string_buffer(s), &s);

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



