#pragma once


#include "networking_bsd/sockets/base/socket.h"
#include "apex/networking/sockets/basic/socket.h"


namespace sockets_bsd
{


   /** \defgroup basic Basic sockets */
   /** socket axis class.
   \ingroup basic */
   class CLASS_DECL_NETWORKING_BSD socket :
      virtual public ::sockets_bsd::base_socket,
      virtual public ::sockets::socket
   {
   public:

#ifdef _UWP
      static SOCKET s_socketNextIdSeed;
#endif

      /** "Default" constructor */
      socket();

      ~socket() override;



      /** create a socket file descriptor.
      \lparam af Address family AF_INET / AF_INET6 / ...
      \lparam type SOCK_STREAM / SOCK_DGRAM / ...
      \lparam protocol "tcp" / "udp" / ... */
      SOCKET CreateSocket(i32 af,i32 type,const string & protocol = "");



      /** close connection immediately - internal use.
      \sa SetCloseAndDelete */
      void close() override;

      /** add file descriptor to sockethandler fd_set's. */
      void set(bool bRead,bool bWrite,bool bException = true);

      /** Returns true when socket file descriptor is valid
      and socket is not about to be closed. */
      bool Ready() override;

      bool is_valid() override;

      i32 close_socket(SOCKET s) override;




      /** SSL; get pointer to ssl action_context structure. */
      virtual SSL_CTX *GetSslContext() { return nullptr; }
      /** SSL; get pointer to ssl structure. */
      virtual SSL *GetSsl() { return nullptr; }
      //@}


      using base_socket::SetNonblocking;
      bool SetNonblocking(bool bNb, SOCKET s);


      ::pointer<::networking::address>get_peer_address() override;
      ::pointer<::networking::address>get_socket_address() override;


   };


} // namespace sockets_bsd




