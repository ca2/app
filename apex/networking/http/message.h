#pragma once


//////#include "acme/prototype/prototype/object.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/nano/http/get.h"
#include "apex/message/message.h"


namespace http
{


   class CLASS_DECL_APEX message :
      virtual public ::message::message,
      virtual public ::nano::http::get
   {
   public:


      //memory                         m_memoryRet;


      //::url::url                       m_url;
      // ::property_set                     m_setPost;
      // ::property_set                     m_setHeaders;

      ::pointer<::http::cookies>       m_pcookies;


      string                           m_strVersion;
      //::function < void(double, filesize, filesize) > m_functionProgress;

      message();


      void run();

   };


} // namespace message



