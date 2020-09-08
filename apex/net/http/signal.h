#pragma once


namespace http
{


   class CLASS_DECL_APEX message :
      public ::message::message,
      virtual public ::object
   {
   public:


      //memory                           m_memoryRet;
      ::estatus                        m_estatusRet;

      string                           m_strUrl;
      property_set                     m_setPost;
      property_set                     m_setHeaders;

      // in replacement of object prop
      //property_set                   m_propset;

      __pointer(::http::cookies)       m_pcookies;
      //__composite(::account::user)     m_puser;


      string                           m_strVersion;


      message();


      void want_memory_response(memory_base * pbase = nullptr);
      void want_string_response();

      memory_pointer get_memory_response();
      string get_string_response();


   };


} // namespace message



