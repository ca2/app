// From windows_common/networking.cpp by camilo on 2025-10-02 20:51 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system/networking.h"
#include <unistd.h>


::i32 _open_socket(::i32 af, ::i32 type, ::i32 protocol)
{

   auto socket = ::socket(af, type, protocol);

   if (socket != -1)
   {

      increment_count_of_opened_sockets();

   }

   return socket;

}


::i32 _close_socket(::i32 s)
{

   auto iError = ::close(s);

   if (iError == 0)
   {

      decrement_count_of_opened_sockets();

   }

   return iError;

}


#if defined(__BSD__) || defined(__ANDROID__) || defined(__APPLE__) || defined(LINUX)
::i32 _accept_socket(::i32 s, sockaddr* addr, socklen_t* addrlen)
#else
::i32 _accept_socket(::i32 s, sockaddr* addr, ::i32* addrlen)
#endif
{

   auto socket = ::accept(s, addr, addrlen);

   if (socket != -1)
   {

      increment_count_of_opened_sockets();

   }

   return socket;

}


