/** \file listen_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/

// xxx ref_Anders_Hedstrom_sockets_library.txt
#pragma once


#include "listen_socket_impl.h"


namespace sockets
{



   /** Binds incoming port number to ___new socket class X.
   \ingroup basic */
   class CLASS_DECL_APEX listen_socket :
      virtual public listen_socket_impl
   {
   public:


      //int                                 m_depth;
      //base_socket *                       m_pbasesocket;

      //::pointer < listen_socket_impl >    m_plistensocket;
      //bool                                m_bImpl;
      //bool                                m_bListeningDetach;
      //::type_atom                         m_typeListenSocket;

      ::pointer < ::factory::factory >    m_pfactory;
      ::type_atom                         m_typeAttendSocket;

      /** Constructor.
      \lparam h base_socket_handler object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket();
      ~listen_socket() override;

      
      virtual void set_attend_socket_type(const ::type_atom& type);

      void Reset() override;

      ::pointer<listen_socket_impl> create_listen_socket_impl();


      void initialize(::particle * pparticle) override;

      void destroy() override;

      base_socket * base_socket_impl() override;
      base_socket* base_socket_interface() override;

      ::pointer<socket>create_attend_socket() override;

      void set_ssl_catalog(const ::scoped_string & scopedstrCat) override;

      void set_ssl_cipher_list(const ::scoped_string & scopedstrCipherList) override;

      /** close file descriptor. */
      void close() override;

      //virtual void set_should_detach(bool bSet);
      //virtual bool should_detach() const;

      void SetListeningDetach(bool bSet) override;
      bool IsListeningDetach() override;


      /** Bind and listen to any interface.
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      int Bind(::networking::port_t port,int depth = 20) override;

      int Bind(::networking::address * paddress,int depth) override;

      /** Bind and listen to any interface, with optional protocol.
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      int Bind(::networking::port_t port,const string & protocol,int depth = 20) override;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      int Bind(const ::scoped_string & scopedstrInterface,::networking::port_t port,int depth = 20) override;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      int Bind(const ::scoped_string & scopedstrInterface,::networking::port_t port,const string & protocol,int depth = 20) override;

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
      //virtual socket_id Accept(socket_id socket, struct sockaddr *saptr, socklen_t *lenptr);

      bool HasCreator() override;

      //virtual void OnOptions(int,int,int,socket_id);



   };


   ///** Binds incoming port number to ___new socket class X.
   //\ingroup basic */
   ////template < class LISTENER >
   //class listen_socket :
   //   virtual public listen_socket_base
   //{
   //public:


   //   //LISTENER *     m_creator;
   //   ::type_atom                               m_typeListenSocket;
   //   //bool                                      m_bHasCreate;
   //   ::pointer < ::sockets::base_socket >      m_psocket;

   //   listen_socket()
   //   {

   //   }
   //   ///** Constructor.
   //   //\lparam h base_socket_handler object
   //   //\lparam use_creator Optional use of creator (default true) */
   //   //listen_socket(bool use_creator = true) :
   //   //   m_bHasCreate(false),
   //   //   m_creator(nullptr)
   //   //{

   //   //   if (use_creator)
   //   //   {

   //   //      //m_creator = ___new LISTENER(h);
   //   //      m_creator = ___new LISTENER();

   //   //      base_socket * plistener = m_creator->new_listen_socket();

   //   //      if(plistener != nullptr)
   //   //      {

   //   //         if(dynamic_cast < LISTENER * >(plistener) != nullptr)
   //   //         {

   //   //            m_bHasCreate = true;

   //   //         }

   //   //         delete plistener;
   //   //      }

   //   //   }
   //   //}

   //   virtual ~listen_socket()
   //   {
   //      //if (m_creator)
   //      //{
   //      //   delete m_creator;
   //      //}
   //   }


   //   virtual ::pointer<socket>create_listen_socket()
   //   {

   //      ::pointer<::sockets::base_socket>pbasesocket;

   //      if (HasCreator())
   //      {

   //         pbasesocket = m_creator->new_listen_socket();

   //         m_psocket = dynamic_cast < LISTENER * > (pbasesocket.m_p);

   //         if (m_psocket == nullptr)
   //         {

   //            pbasesocket.release();

   //         }

   //         m_pbasesocket = pbasesocket;

   //      }
   //      else
   //      {

   //         pbasesocket = øallocate LISTENER();

   //         m_psocket = dynamic_cast < LISTENER * >(pbasesocket.m_p);

   //         if (pbasesocket == nullptr)
   //         {

   //            pbasesocket.release();

   //            m_psocket = nullptr;

   //         }

   //         m_pbasesocket = pbasesocket;

   //      }

   //      return pbasesocket;

   //   }


   //   //bool HasCreator()
   //   //{
   //   //   return m_bHasCreate;
   //   //}


   //};


} // namespace sockets


