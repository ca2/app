#include "framework.h"
#include "pcre.h"

#define PCRE2_CODE_UNIT_WIDTH 8
#ifdef CUBE
#define PCRE2_STATIC
#endif

#ifdef __APPLE__
#include <pcre/pcre2.h>
#else
#include <pcre2.h>
#endif






pcre_context::pcre_context(::object * pobject) :
   ::object(pobject)
{

}

pcre_context::~pcre_context()
{

}

__pointer(regex) pcre_context::compile(const string& str)
{

   return pcre_code::compile(this, str);

}


pcre_regex::pcre_regex(::object * pobject):
   ::object(pobject)
{

}


pcre_regex::~pcre_regex()
{

}


pcre_code::pcre_code(::object * pobject):
   ::object(pobject),
   pcre_regex(pobject)
{

}


pcre_code::~pcre_code()
{

}


class pcre_context_impl:
   virtual public pcre_context
{
public:


   pcre2_general_context * m_pgc;
   pcre2_compile_context * m_pcc;
   pcre2_match_data *      m_pmd;
   int                     m_iSizeData;


   pcre_context_impl(::object * pobject, int iSizeData):
      ::object(pobject),
      pcre_context(pobject)
   {

      m_pimpl = this;

      m_pgc = pcre2_general_context_create(nullptr,nullptr,nullptr);

      m_pcc = pcre2_compile_context_create(m_pgc);

      m_iSizeData = iSizeData;

      if(m_iSizeData <= 0)
      {

         m_pmd = nullptr;

      }
      else
      {

         m_pmd = pcre2_match_data_create(m_iSizeData,m_pgc);

      }


   }


   virtual ~pcre_context_impl()
   {

      if(m_pmd != nullptr)
      {

         pcre2_match_data_free(m_pmd);

         m_pmd = nullptr;

      }


      if(m_pcc != nullptr)
      {

         pcre2_compile_context_free(m_pcc);

         m_pcc = nullptr;

      }


      if(m_pgc != nullptr)
      {

         pcre2_general_context_free(m_pgc);

         m_pgc = nullptr;

      }


   }


};



class pcre_code_impl :
   virtual public pcre_code
{
public:


   pcre2_code *               m_pc;

   pcre_context_impl *        m_pcreContext;


   pcre_code_impl(pcre_context_impl * pcreContext) :
      ::object(pcreContext),
      pcre_regex(pcreContext),
      pcre_code(pcreContext)
   {

      m_pcreContext = pcreContext;

      m_pc = nullptr;

   }

   virtual ~pcre_code_impl()
   {

      if(m_pc != nullptr)
      {

         pcre2_code_free(m_pc);

         m_pc = nullptr;

      }

   }


   bool compile(const string &str)
   {

      int e;

      PCRE2_SIZE eo;

      m_pc = pcre2_compile((PCRE2_SPTR)(const char *)str,str.get_length(),0,&e,&eo, m_pcreContext->m_pcc);

      if(m_pc == nullptr)
         return false;

      return true;

   }
   virtual bool matches(const string & str) override
   {

      int c = pcre2_match(m_pc, (PCRE2_SPTR)(const char *)str, str.get_length(), 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

      return c > 0;
   }

   virtual bool matches(const char * psz, strsize len) override
   {

      int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

      return c > 0;
   }


   virtual ::count match_count(const string & str) override
   {

      return match_count(str.c_str(), str.length());

   }

   virtual ::count match_count(const char * psz, strsize len) override
   {

      int c = pcre2_match(m_pc,(PCRE2_SPTR)psz,len,0,0,m_pcreContext->m_pimpl->m_pmd,nullptr);

      return c;
   }


   virtual __pointer(::str::range_array) matches_ranges(const string & str) override
   {

      return matches_ranges(str.c_str(), str.get_length());

   }


   virtual __pointer(::str::range_array) matches_ranges(const char * psz, strsize len) override
   {

      auto c = match_count(psz, len);

      if (c <= 0)
      {

         return nullptr;

      }

      PCRE2_SIZE * ovector = pcre2_get_ovector_pointer(m_pcreContext->m_pimpl->m_pmd);

      auto prangeaMatches = __new(::str::range_array);

      for (strsize i = 0; i < c; i++)
      {

         prangeaMatches->add(::str::range(ovector[2 * i], ovector[2 * i + 1]));

      }

      return prangeaMatches;


   }


   virtual bool replace(string & str,const string & strPrefix,string & strRet) override
   {

      size_t s=MAX(256, str.get_length() + strPrefix.get_length() * 3);

      int err;

      while(true)
      {

         err = pcre2_substitute(
               m_pc,
               (PCRE2_SPTR8)str.c_str(),
               str.get_length(),
               0,
               PCRE2_SUBSTITUTE_GLOBAL,m_pcreContext->m_pimpl->m_pmd,nullptr,(PCRE2_SPTR8)strPrefix.c_str(),strPrefix.get_length(),(PCRE2_UCHAR8 *)strRet.get_string_buffer(s),&s);

         strRet.release_string_buffer(s);

         if(err >= 0)
         {
            return true;

         }
         else if(err != PCRE2_ERROR_NOMEMORY)
         {

            return false;

         }


         s *= 2;

      }

      return true;

   }


};


class pcre_util_impl:
   virtual public pcre_code_impl
{
public:


   __pointer(pcre_context_impl) m_pcre;


   pcre_util_impl(pcre_context_impl * m_pcreContext):
      ::object(m_pcreContext),
      pcre_regex(m_pcreContext->get_context_application()),
      pcre_code(m_pcreContext->get_context_application()),
      pcre_code_impl(m_pcreContext)
   {

      m_pcre = m_pcreContext;

   }


   virtual ~pcre_util_impl()
   {


   }

   bool compile(const string &str)
   {


      if(!pcre_code_impl::compile(str))
         return false;


      if(m_pcre->m_pmd != nullptr)
      {

         pcre2_match_data_free(m_pcre->m_pmd);

         m_pcre->m_pmd = nullptr;

      }

      m_pcre->m_pmd = pcre2_match_data_create_from_pattern(m_pc,m_pcre->m_pgc);

      if(m_pcre->m_pmd == nullptr)
         return false;

      return true;

   }



   virtual ::count matches(const string & str, pcre_context *)
   {

      return pcre_code_impl::matches(str,m_pcre);

   }

   virtual ::count matches(const char * psz, strsize len,pcre_context *)
   {

      return pcre_code_impl::matches(psz, len);

   }

   virtual __pointer(::str::range_array) matches_ranges(const string & str) override
   {

      return pcre_code_impl::matches_ranges(str);

   }

   virtual __pointer(::str::range_array) matches_ranges(const char * psz,strsize len) override
   {

      return pcre_code_impl::matches_ranges(psz, len);

   }

};


__pointer(pcre_context) pcre_context::create_context(::object * pobject, int iSizeData)
{

   return __new(pcre_context_impl(pobject, iSizeData));

}


__pointer(regex) pcre_regex::compile(::object * pobject, const string & str)
{

   __pointer(pcre_context_impl) pcreContextImpl = pcre_context::create_context(pobject, 0);

   auto putil  = __new(pcre_util_impl(pcreContextImpl));

   putil->compile(str);

   return putil;

}


__pointer(pcre_code) pcre_code::compile(pcre_context * m_pcreContext,const string & str)
{

   __pointer(pcre_context_impl) pimpl = m_pcreContext;

   auto pcode  = __new(pcre_code_impl(pimpl));

   pcode->compile(str);

   return pcode;

}


namespace axis
{


   __pointer(regex) system::create_pcre(const string& str)
   {

      return pcre_regex::compile(this, str);

   }

   __pointer(regex_context) system::create_pcre_context(int iCount)
   {

      return pcre_context::create_context(this, iCount);
   }


   int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)
   {

       throw_todo();

       return -1;

   }


} // namespace axis



