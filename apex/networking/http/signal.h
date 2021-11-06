#pragma once


namespace http
{


   class CLASS_DECL_APEX message :
      public ::message::message,
      virtual public ::object
   {
   public:


      //memory                           m_memoryRet;
      ::e_status                        m_estatusRet;

      string                           m_strUrl;
      property_set                     m_setPost;
      property_set                     m_setHeaders;

      __pointer(::http::cookies)       m_pcookies;


      string                           m_strVersion;


      message();


      void want_memory_response(memory_base * pusermessage = nullptr);
      void want_string_response();

      memory_pointer get_memory_response();
      string get_string_response();


   };


} // namespace message



