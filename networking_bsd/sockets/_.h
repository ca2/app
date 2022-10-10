// cs<3tbs!! 2020-11-28 21:25 BRT
#pragma once


#define INVALID_SOCKET_ID (-1)


using socket_id_list = ::comparable_list < SOCKET >;


namespace sockets_bsd
{


   enum enum_list
   {
      
      
      e_list_call_on_connect,
      e_list_detach,
      e_list_timeout,
      e_list_retry_client_connect,
      e_list_close


   };


   class ssl_context;
   class ssl_client_context;

   /* type, host, result */
   typedef string_map < ::string_to_string >       resolv_cache_t;

   /* type, host, time */
   typedef string_map < string_map < time_t > >    resolv_timeout_t;



   class socket_thread;

   class base_socket_handler;

   class socket_handler;

   class base_socket;

   using socket_pointer = ::pointer<base_socket>


   typedef comparable_list < socket_pointer > socket_pointer_list;



   //class socket_handler;

   __declare_map(socket_flag_map, socket_flag, base_socket *, m_pbasesocket, bool, m_bFlag);
   __declare_map(socket_socket_flag_map, socket_socket_flag, SOCKET, m_socket, socket_flag_map, m_pmap);
   __declare_map(socket_map, socket_pointer_pair, SOCKET, m_socket, socket_pointer, m_psocket);


} // namespace sockets_bsd


#include "config.h"


#include "ssl/_.h"



