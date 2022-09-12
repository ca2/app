#pragma once


#include "tcp_socket.h"
#include "apex/networking/sockets/basic/tls_socket.h"


namespace sockets_bsd
{


   class CLASS_DECL_NETWORKING_BSD tls_socket :
      virtual public tcp_socket,
      virtual public ::sockets::tls_socket
   {
   public:


      tls_socket();
      ~tls_socket();


      virtual void InitSSLClient();

   };



} // namespace sockets_bsd




