//
// Created by camilo on 22/10/22.
//
#pragma once


#include "acme/primitive/collection/map.h"
//#include "acme/primitive/primitive/pointer.h"


namespace sockets_bsd
{


   MAKE_PAIR(SOCKET_socket_pointer, SOCKET, socket_pointer, m_socket, m_psocket);
   MAKE_PAIR(base_socket_bool, base_socket *, bool, m_pbasesocket, m_b);


   using socket_flag_map = pair_map < base_socket_bool >;
   using socket_socket_flag_map = map < SOCKET, socket_flag_map >;
   using socket_map = pair_map < SOCKET_socket_pointer >;


} // namespace sockets_bsd




