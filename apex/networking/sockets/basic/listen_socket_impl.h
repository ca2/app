/** \file listen_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/

// xxx ref_Anders_Hedstrom_sockets_library.txt

#pragma once

#include "socket.h"

namespace sockets
{


   /** Binds incoming port number to ___new socket class X.
\ingroup basic */
   class CLASS_DECL_APEX listen_socket_impl :
      virtual public socket
   {
   public:


      int                                 m_depth;
      base_socket* m_pbasesocket;

      ::pointer < listen_socket_impl >    m_plistensocketImpl;
      listen_socket_impl *                m_plistensocketInterface;
      bool                                m_bImpl;
      bool                                m_bListeningDetach;
      //::type                         m_typeListenSocket;

      //::pointer < ::factory::factory >    m_pfactory;
      //::type                         m_typeDetachSocket;

      /** Constructor.
      \lparam h base_socket_handler object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket_impl();
      ~listen_socket_impl() override;


      virtual void set_detach_socket_type(const ::type& typeatom);

      virtual void Reset();
      ::pointer<listen_socket_impl>create_listen_socket_impl();

      void initialize(::particle* pparticle) override;

      void destroy() override;

      bool is_listening_socket() override;

      base_socket* base_socket_impl() override;
      base_socket* base_socket_interface() override;

      virtual ::pointer<socket>create_attend_socket();

      virtual void set_ssl_catalog(const ::scoped_string & scopedstrCat);

      virtual void set_ssl_cipher_list(const ::scoped_string & scopedstrCipherList);

      /** close file descriptor. */
      void close() override;

      //virtual void set_should_detach(bool bSet);
      //virtual bool should_detach() const;

      virtual void SetListeningDetach(bool bSet);
      virtual bool IsListeningDetach();


      /** Bind and listen to any interface.
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual int Bind(::networking::port_t port, int depth = 20);

      virtual int Bind(::networking::address* paddress, int depth);

      /** Bind and listen to any interface, with optional protocol.
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual int Bind(::networking::port_t port, const string& protocol, int depth = 20);

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual int Bind(const ::scoped_string & scopedstrInterface, ::networking::port_t port, int depth = 20);

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual int Bind(const ::scoped_string & scopedstrInterface, ::networking::port_t port, const string& protocol, int depth = 20);

      ///** Bind and listen to ipv4 interface.
      //\lparam a Ipv4 interface address
      //\lparam port Port (0 is random)
      //\lparam depth Listen queue depth */
      //virtual int Bind(in_addr a,::networking::port_t port,int depth = 20);

      ///** Bind and listen to ipv4 interface.
      //\lparam a Ipv4 interface address
      //\lparam port Port (0 is random)
      //\lparam protocol Network protocol
      //\lparam depth Listen queue depth */
      //virtual int Bind(in_addr a,::networking::port_t port,const string & protocol,int depth);

      ///** Bind and listen to ipv6 interface.
      //\lparam a Ipv6 interface address
      //\lparam port Port (0 is random)
      //\lparam depth Listen queue depth */
      //virtual int Bind(in6_addr a,::networking::port_t port,int depth = 20);


      ///** Bind and listen to ipv6 interface.
      //\lparam a Ipv6 interface address
      //\lparam port Port (0 is random)
      //\lparam protocol Network protocol
      //\lparam depth Listen queue depth */
      //virtual int Bind(in6_addr a,::networking::port_t port,const string & protocol,int depth);

      /** Bind and listen to network interface.
      \lparam ad Interface address
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual int Bind(::networking::address* paddress, const string& protocol, int depth);

      /** Return assigned port number. */
//         ::networking::port_t GetPort()
//       {
//        return GetSockPort();
      //   }

      /** Return listen queue depth. */
      virtual int GetDepth();

      /** OnRead on a listen_socket receives an incoming connection. */
      void OnRead() override;

      /** Please don't use this method.
      "accept()" is handled automatically in the OnRead() method. */
      //virtual socket_id Accept(socket_id socket, struct sockaddr *saptr, socklen_t *lenptr);

      virtual bool HasCreator();

      //virtual void OnOptions(int,int,int,socket_id);



   };

} // namespace sockets


