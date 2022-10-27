/** \file listen_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/
// xxx ref_Anders_Hedstrom_sockets_library.txt
#pragma once


#include "networking_bsd/sockets/basic/socket.h"
#include "apex/networking/sockets/basic/listen_socket.h"


namespace sockets_bsd
{


   /** Binds incoming port number to memory_new socket class X.
   \ingroup basic */
   class CLASS_DECL_NETWORKING_BSD listen_socket :
      virtual public ::sockets_bsd::socket,
      virtual public ::sockets::listen_socket_base
   {
   public:


      i32              m_depth;
      bool                 m_bDetach;
      base_socket *        m_pbasesocket;


      /** Constructor.
      \lparam h base_socket_handler object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket();
      virtual ~listen_socket();

      void initialize(::particle * pparticle) override;


      void set_ssl_catalog(const ::string & strCat) override;


      void set_ssl_cipher_list(const ::string & strCipherList) override;


      void set_should_detach(bool bSet) override;
      bool should_detach() const override;

      //virtual ::pointer<::sockets::socket>create_listen_socket();

      /** close file descriptor. */
      void close() override;

      /** Bind and listen to any interface.
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(::networking::port_t port,i32 depth = 20) override;

      i32 Bind(::networking::address * paddress,i32 depth) override;

      /** Bind and listen to any interface, with optional protocol.
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      i32 Bind(::networking::port_t port,const string & protocol,i32 depth = 20)  override;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      i32 Bind(const string & intf,::networking::port_t port,i32 depth = 20) override;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      i32 Bind(const string & intf,::networking::port_t port,const string & protocol,i32 depth = 20) override;

      /** Bind and listen to ipv4 interface.
      \lparam a Ipv4 interface address
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(in_addr a,::networking::port_t port,i32 depth = 20);

      /** Bind and listen to ipv4 interface.
      \lparam a Ipv4 interface address
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(in_addr a,::networking::port_t port,const string & protocol,i32 depth);

      /** Bind and listen to ipv6 interface.
      \lparam a Ipv6 interface address
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(in6_addr a,::networking::port_t port,i32 depth = 20);


      /** Bind and listen to ipv6 interface.
      \lparam a Ipv6 interface address
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(in6_addr a,::networking::port_t port,const string & protocol,i32 depth);

      /** Bind and listen to network interface.
      \lparam ad Interface address
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      i32 Bind(::networking::address * paddress,const string & protocol,i32 depth) override;

      /** Return assigned port number. */
//         ::networking::port_t GetPort()
//       {
//        return GetSockPort();
      //   }

      /** Return listen queue depth. */
      i32 GetDepth() override;

      /** OnRead on a listen_socket receives an incoming connection. */
      void OnRead() override;

      /** Please don't use this method.
      "accept()" is handled automatically in the OnRead() method. */
      virtual SOCKET Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr);

      virtual bool HasCreator() override;

      void OnOptions(i32,i32,i32,SOCKET) override;



   };


} // namespace sockets_bsd



