/** \file listen_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/

// xxx ref_Anders_Hedstrom_sockets_library.txt

#pragma once

#include "socket.h"

namespace sockets
{


   /** Binds incoming port number to memory_new socket class X.
   \ingroup basic */
   class CLASS_DECL_APEX listen_socket_base :
      virtual public socket
   {
   public:


      i32              m_depth;
      base_socket *        m_pbasesocket;

      __pointer(listen_socket_base)       m_pcomposite;
      bool                                m_bImpl;
      /** Constructor.
      \lparam h base_socket_handler object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket_base();




      virtual ~listen_socket_base();

      void initialize(::object * pobject) override;

      base_socket * base_socket_composite() override;

      virtual __pointer(socket) create_listen_socket();

      virtual void set_ssl_catalog(const ::string & strCat);

      virtual void set_ssl_cipher_list(const ::string & strCipherList);

      /** close file descriptor. */
      void close() override;

      virtual void set_should_detach(bool bSet);
      virtual bool should_detach() const;

      /** Bind and listen to any interface.
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(::networking::port_t port,i32 depth = 20);

      virtual i32 Bind(::networking::address * paddress,i32 depth);

      /** Bind and listen to any interface, with optional protocol.
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(::networking::port_t port,const string & protocol,i32 depth = 20) ;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(const string & intf,::networking::port_t port,i32 depth = 20);

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(const string & intf,::networking::port_t port,const string & protocol,i32 depth = 20);

      ///** Bind and listen to ipv4 interface.
      //\lparam a Ipv4 interface address
      //\lparam port Port (0 is random)
      //\lparam depth Listen queue depth */
      //virtual i32 Bind(in_addr a,::networking::port_t port,i32 depth = 20);

      ///** Bind and listen to ipv4 interface.
      //\lparam a Ipv4 interface address
      //\lparam port Port (0 is random)
      //\lparam protocol Network protocol
      //\lparam depth Listen queue depth */
      //virtual i32 Bind(in_addr a,::networking::port_t port,const string & protocol,i32 depth);

      ///** Bind and listen to ipv6 interface.
      //\lparam a Ipv6 interface address
      //\lparam port Port (0 is random)
      //\lparam depth Listen queue depth */
      //virtual i32 Bind(in6_addr a,::networking::port_t port,i32 depth = 20);


      ///** Bind and listen to ipv6 interface.
      //\lparam a Ipv6 interface address
      //\lparam port Port (0 is random)
      //\lparam protocol Network protocol
      //\lparam depth Listen queue depth */
      //virtual i32 Bind(in6_addr a,::networking::port_t port,const string & protocol,i32 depth);

      /** Bind and listen to network interface.
      \lparam ad Interface address
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(::networking::address * paddress,const string & protocol,i32 depth);

      /** Return assigned port number. */
//         ::networking::port_t GetPort()
//       {
//        return GetSockPort();
      //   }

      /** Return listen queue depth. */
      virtual i32 GetDepth();

      /** OnRead on a listen_socket receives an incoming connection. */
      void OnRead() override;

      /** Please don't use this method.
      "accept()" is handled automatically in the OnRead() method. */
      //virtual socket_id Accept(socket_id socket, struct sockaddr *saptr, socklen_t *lenptr);

      virtual bool HasCreator();

      //virtual void OnOptions(i32,i32,i32,socket_id);



   };


   /** Binds incoming port number to memory_new socket class X.
   \ingroup basic */
   template < class LISTENER >
   class listen_socket :
      virtual public listen_socket_base
   {
   public:


      LISTENER *     m_creator;
      bool           m_bHasCreate;
      LISTENER *     m_psocket;


      /** Constructor.
      \lparam h base_socket_handler object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket(bool use_creator = true) :
         m_bHasCreate(false),
         m_creator(nullptr)
      {

         if (use_creator)
         {

            //m_creator = memory_new LISTENER(h);
            m_creator = memory_new LISTENER();

            base_socket * plistener = m_creator->new_listen_socket();

            if(plistener != nullptr)
            {

               if(dynamic_cast < LISTENER * >(plistener) != nullptr)
               {

                  m_bHasCreate = true;

               }

               delete plistener;
            }

         }
      }

      virtual ~listen_socket()
      {
         if (m_creator)
         {
            delete m_creator;
         }
      }


      virtual __pointer(socket) create_listen_socket()
      {

         __pointer(::sockets::base_socket) pbasesocket;

         if (HasCreator())
         {

            pbasesocket = m_creator->new_listen_socket();

            m_psocket = dynamic_cast < LISTENER * > (pbasesocket.m_p);

            if (m_psocket == nullptr)
            {

               pbasesocket.release();

            }

            m_pbasesocket = pbasesocket;

         }
         else
         {

            pbasesocket = __new(LISTENER());

            m_psocket = dynamic_cast < LISTENER * >(pbasesocket.m_p);

            if (pbasesocket == nullptr)
            {

               pbasesocket.release();

               m_psocket = nullptr;

            }

            m_pbasesocket = pbasesocket;

         }

         return pbasesocket;

      }


      bool HasCreator()
      {
         return m_bHasCreate;
      }


   };


} // namespace sockets


