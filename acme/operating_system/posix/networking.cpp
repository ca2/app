// From windows_common/networking.cpp by camilo on 2025-10-02 20:51 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system/networking.h"


int _open_socket(int af, int type, int protocol)
{

   auto socket = ::socket(af, type, protocol);

   if (socket != -1)
   {

      increment_count_of_opened_sockets();

   }

   return socket;

}


int _close_socket(int s)
{

   auto iError = ::close(s);

   if (iError == 0)
   {

      decrement_count_of_opened_sockets();

   }

   return iError;

}


int _accept_socket(int s, sockaddr* addr, int* addrlen)
{

   auto socket = ::accept(s, addr, addrlen);

   if (socket != -1)
   {

      increment_count_of_opened_sockets();

   }

   return socket;

}


