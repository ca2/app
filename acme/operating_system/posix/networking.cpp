// From windows_common/networking.cpp by camilo on 2025-10-02 20:51 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system/networking.h"
#include <unistd.h>


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


#if defined(__BSD__) || defined(__ANDROID__) || defined(__APPLE__) || defined(LINUX)
int _accept_socket(int s, sockaddr* addr, socklen_t* addrlen)
#else
int _accept_socket(int s, sockaddr* addr, int* addrlen)
#endif
{

   auto socket = ::accept(s, addr, addrlen);

   if (socket != -1)
   {

      increment_count_of_opened_sockets();

   }

   return socket;

}


