// cs<3tbs!! 2023-12-16 04:20 2020-11-28 21:16 BRT
// From simple_webserver to networking application socket by camilo on 2021-11-07 11:21 BRT <3TBS_!!
#pragma once


#include "apex/networking/netserver/incoming_socket.h"


namespace networking
{


   class CLASS_DECL_APEX application_incoming_socket :
      virtual public ::netserver::incoming_socket
   {
   public:


      ::pointer<::networking::application>      m_pnetworkingapplication;


      application_incoming_socket();
      ~application_incoming_socket() override;


      void on_initialize_particle() override;


    /*  virtual void on_send_response() override;


      string on_send_http_response();*/


   };


} // namespace networking



