// Created by camilo on 2022-08-30 16:18 <3ThomasBorregaardSorensen!!
#pragma once


//using socket_id = ::i64;
//
namespace sockets
{

   class socket_thread;

   class base_socket;

   class base_socket_handler;

   using socket_pointer = ::pointer<base_socket>;

   class httpd_socket;
   //namespace sockets
   //{

   class socket;

   class link_out_socket;
   class link_in_socket;
      class socket_handler;
      class http_client_socket;
      class http_session;

      using in_link_map = map < link_out_socket *, link_in_socket * >;
      
   //} // namespace sockets

      class listen_socket_base;

} // namespace sockets


//#include "ssl/_.h"



