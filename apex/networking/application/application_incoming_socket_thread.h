// From another incoming_socket_thread by
// camilo on 2024-11-17 00:37 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/networking/netserver/incoming_socket_thread.h"


namespace networking
{


   class CLASS_DECL_APEX application_incoming_socket_thread :
      virtual public ::netserver::incoming_socket_thread
   {
   public:


      ::pointer<::networking::application>      m_pnetworkingapplication;


      application_incoming_socket_thread();
      ~application_incoming_socket_thread() override;


      ::pointer < ::httpd::incoming_socket > create_incoming_socket() override;


   };



} // namespace networking




