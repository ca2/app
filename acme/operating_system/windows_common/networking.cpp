// Created by camilo on 2025-10-02 06:27 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system/networking.h"


SOCKET _open_socket(::i32 af, ::i32 type, ::i32 protocol)
{

   auto socket = ::socket(af, type, protocol);

   if (socket != INVALID_SOCKET)
   {

      increment_count_of_opened_sockets();

   }

   return socket;

}


::i32 _close_socket(SOCKET s)
{

   if (s == INVALID_SOCKET)
   {

      return -1;

   }

   auto iError = ::closesocket(s);

   if (iError == 0)
   {

      decrement_count_of_opened_sockets();

   }

   return iError;

}


SOCKET _accept_socket(SOCKET s, sockaddr* addr, ::i32* addrlen)
{

   auto socket = ::accept(s, addr, addrlen);

   if (socket != INVALID_SOCKET)
   {

      increment_count_of_opened_sockets();

   }

   return socket;

}


