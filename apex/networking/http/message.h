#pragma once


//////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/primitive/payload.h"
#include "apex/message/message.h"


namespace http
{


   class CLASS_DECL_APEX message :
      public ::message::message //,
      //virtual public ::object
   {
   public:


      //memory                           m_memoryRet;
      ::e_status                      m_estatusRet;

      string                           m_strUrl;
      property_set                     m_setPost;
      property_set                     m_setHeaders;

      ::pointer<::http::cookies>      m_pcookies;


      string                           m_strVersion;
      //::function < void(double, filesize, filesize) > m_functionProgress;

      message();


      void want_memory_response(memory_base * pusermessage = nullptr);
      void want_string_response();

      memory_pointer get_memory_response();
      string get_string_response();


   };


} // namespace message



