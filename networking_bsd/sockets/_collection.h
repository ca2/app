//
// Created by camilo on 22/10/22.
//
#pragma once


#include "acme/primitive/collection/map.h"
//#include "acme/primitive/primitive/pointer.h"


namespace sockets_bsd
{


   // class base_socket_bool
   // {
   // public:


   //    using TYPE1 = base_socket *;
   //    using TYPE2 = bool;
   //    using CONST_TYPE1 = ::const_of < TYPE1 >;
   //    using CONST_TYPE2 = ::const_of < TYPE2 >;
   //    using ARG_TYPE1 = ::argument_of < TYPE1 >;
   //    using ARG_TYPE2 = ::argument_of < TYPE2 >;


   //    base_socket * m_pbasesocket;
   //    bool       m_b;


   //    inline base_socket *& element1() { return m_pbasesocket; }
   //    inline bool & element2() { return m_b; }
   //    inline CONST_TYPE1 & element1() const { return (CONST_TYPE1 &)m_pbasesocket; }
   //    inline CONST_TYPE2 & element2() const { return (CONST_TYPE2 &)m_b; }
   //    inline base_socket *&& transfer_element1() { return ::transfer(m_pbasesocket); }
   //    inline bool && transfer_element2() { return ::transfer(m_b); }
   //    inline CONST_TYPE1 && transfer_element1() const { return (CONST_TYPE1 &&) ::transfer(m_pbasesocket); }
   //    inline CONST_TYPE2 && transfer_element2() const { return (CONST_TYPE2 &&) ::transfer(m_b); }


   //    base_socket_bool() {}
   //    base_socket_bool(ARG_TYPE1 t1) : m_pbasesocket(t1) {}
   //    base_socket_bool(ARG_TYPE1 t1, ARG_TYPE2 t2) : m_pbasesocket(t1), m_b(t2) {}


   // };


   MAKE_PAIR(SOCKET_socket_pointer, SOCKET, socket_pointer, m_socket, m_psocket);
   MAKE_PAIR(base_socket_bool, base_socket *, bool, m_pbasesocket, m_b);


   using socket_flag_map = pair_map < base_socket_bool >;
   using socket_socket_flag_map = map < SOCKET, socket_flag_map >;
   using socket_map = pair_map < SOCKET_socket_pointer >;


} // namespace sockets_bsd




