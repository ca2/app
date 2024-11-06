/** \file listen_socket_impl.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/
// xxx ref_Anders_Hedstrom_sockets_library.txt
#pragma once


#include "networking_bsd/sockets/basic/socket.h"
#include "apex/networking/sockets/basic/listen_socket_impl.h"


namespace sockets_bsd
{


   /** Binds incoming port number to ___new socket class X.
   \ingroup basic */
   class CLASS_DECL_NETWORKING_BSD listen_socket_impl :
      virtual public ::sockets_bsd::socket,
      virtual public ::sockets::listen_socket_impl
   {
   public:


      //int              m_depth;
      //bool                 m_bStartDetach;
      //base_socket *        m_pbasesocket;


      /** Constructor.
      \lparam h base_socket_handler object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket_impl();
      ~listen_socket_impl() override;

      void initialize(::particle * pparticle) override;


      void set_ssl_catalog(const ::string & strCat) override;


      void set_ssl_cipher_list(const ::string & strCipherList) override;



      //virtual ::pointer<::sockets::socket>create_listen_socket();

      /** close file descriptor. */
      void close() override;

      /** Bind and listen to any interface.
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual int Bind(::networking::port_t port,int depth = 20) override;

      int Bind(::networking::address * paddress,int depth) override;

      /** Bind and listen to any interface, with optional protocol.
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      int Bind(::networking::port_t port,const string & protocol,int depth = 20)  override;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      int Bind(const string & intf,::networking::port_t port,int depth = 20) override;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      int Bind(const string & intf,::networking::port_t port,const string & protocol,int depth = 20) override;

      /** Bind and listen to ipv4 interface.
      \lparam a Ipv4 interface address
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual int Bind(in_addr a,::networking::port_t port,int depth = 20);

      /** Bind and listen to ipv4 interface.
      \lparam a Ipv4 interface address
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual int Bind(in_addr a,::networking::port_t port,const string & protocol,int depth);

      /** Bind and listen to ipv6 interface.
      \lparam a Ipv6 interface address
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual int Bind(in6_addr a,::networking::port_t port,int depth = 20);


      /** Bind and listen to ipv6 interface.
      \lparam a Ipv6 interface address
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual int Bind(in6_addr a,::networking::port_t port,const string & protocol,int depth);

      /** Bind and listen to network interface.
      \lparam ad Interface address
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      int Bind(::networking::address * paddress,const string & protocol,int depth) override;

      /** Return assigned port number. */
//         ::networking::port_t GetPort()
//       {
//        return GetSockPort();
      //   }

      /** Return listen queue depth. */
      int GetDepth() override;

      /** OnRead on a listen_socket receives an incoming connection. */
      void OnRead() override;

      /** Please don't use this method.
      "accept()" is handled automatically in the OnRead() method. */
      virtual SOCKET Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr);

      virtual bool HasCreator() override;

      void OnOptions(int,int,int,SOCKET) override;



   };


} // namespace sockets_bsd



