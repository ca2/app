//
// Created by camilo on 22/10/22.
//
#pragma once


namespace sockets_bsd
{

   __declare_map(socket_flag_map, socket_flag, base_socket *, m_pbasesocket, bool, m_bFlag);
   __declare_map(socket_socket_flag_map, socket_socket_flag, SOCKET, m_socket, socket_flag_map, m_pmap);
   __declare_map(socket_map, socket_pointer_pair, SOCKET, m_socket, socket_pointer, m_psocket);


} // namespace sockets_bsd




