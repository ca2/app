// Created by camilo on 2022-08-30 16:18 <3ThomasBorregaardSorensen!!
#pragma once




namespace sockets
{


   class socket_thread;

   class base_socket;

   using socket_pointer = __pointer(base_socket);

   class httpd_socket;
   //namespace sockets
   //{

   class link_out_socket;
   class link_in_socket;
      class socket_handler;
      class http_client_socket;
      class http_session;

      using in_link_map = map < link_out_socket *, link_in_socket * >;
      
   //} // namespace sockets


}
