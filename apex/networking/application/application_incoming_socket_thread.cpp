// From another incoming_socket_thread by
// camilo on 2024-11-17 00:41 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application_incoming_socket_thread.h"
#include "application_incoming_socket.h"


namespace networking
{


   application_incoming_socket_thread::application_incoming_socket_thread()
   {

    
   }


   application_incoming_socket_thread::~application_incoming_socket_thread()
   {

   }


   ::pointer < ::httpd::incoming_socket > application_incoming_socket_thread::create_incoming_socket()
   {

      auto pincomingsocket = ::netserver::incoming_socket_thread::create_incoming_socket();

      ::pointer < ::networking::application_incoming_socket > papplicationincomingsocket;

      papplicationincomingsocket = pincomingsocket;

      papplicationincomingsocket->m_pnetworkingapplication = m_pnetworkingapplication;

      return papplicationincomingsocket;

   }


} // namespace networking



