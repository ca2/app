// cs<3tbs!! 2020-11-28 21:25 BRT
#pragma once


#include "config.h"
//#include "acme/primitive/collection/string_map.h"


#define INVALID_SOCKET_ID (-1)


namespace sockets_bsd
{


   class ssl_context;
   class ssl_client_context;

   /* type, host, result */
//   typedef string_map < ::string_to_string >       resolv_cache_t;

   /* type, host, time */
//   typedef string_map < string_map < time_t > >    resolv_timeout_t;



   class socket_thread;

   class base_socket_handler;

   class socket_handler;

   class base_socket;

   using socket_pointer = ::pointer<base_socket>;


   //typedef comparable_list < socket_pointer > socket_pointer_list;


} // namespace sockets_bsd


#include "ssl/_.h"



