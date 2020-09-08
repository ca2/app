#pragma once


namespace exception
{


   class CLASS_DECL_AQUA os_engine :
      virtual public ::engine

   {

      void * m_uia[64];


      char * stack_trace(iptr iSkip = 0, void * caller_address = nullptr, const char * pszFormat = default_format(), int iCount = -1);

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      void backtrace(void ** pinteraction, int & c);
      char * stack_trace(void * const * pinteraction, int c, const char * pszFormat = default_format());

#endif
   };


} // namespace exception



