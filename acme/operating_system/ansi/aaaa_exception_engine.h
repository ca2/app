#pragma once


namespace exception
{


   class CLASS_DECL_ACME os_engine :
      virtual public ::engine

   {

      void * m_uia[64];


      char_pointer stack_trace(iptr iSkip = 0, void * caller_address = nullptr, const ::scoped_string & scopedstrFormat = default_format(), ::i32 iCount = -1);

#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      void backtrace(void ** pinteraction, ::i32 & c);
      char_pointer stack_trace(void * const * pinteraction, ::i32 c, const ::scoped_string & scopedstrFormat = default_format());

#endif
   };


} // namespace exception



