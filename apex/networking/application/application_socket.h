// cs<3tbs!! 2020-11-28 21:16 BRT
// From simple_webserver to networking application socket by camilo on 2021-11-07 11:21 BRT <3TBS_!!
#pragma once


#include "apex/networking/netserver/socket.h"


namespace networking
{


   class CLASS_DECL_APEX application_socket :
      virtual public ::netserver::socket
   {
   public:


      ::pointer<::networking::application>      m_pnetworkingapplication;


      application_socket();
      ~application_socket() override;


      virtual void on_send_response() override;


      string on_send_http_response();


   };


} // namespace networking



