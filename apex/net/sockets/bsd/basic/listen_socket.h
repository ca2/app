/** \file listen_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/

// xxx ref_Anders_Hedstrom_sockets_library.txt

#pragma once



namespace sockets
{

   /** Binds incoming port number to new socket class X.
   \ingroup basic */
   class CLASS_DECL_APEX listen_socket_base :
      virtual public socket
   {
   public:


      i32              m_depth;
      bool                 m_bDetach;
      base_socket *        m_pbasesocket;


      /** Constructor.
      \lparam h base_socket_handler context_object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket_base(base_socket_handler& h);




      virtual ~listen_socket_base();


      virtual __pointer(socket) create_listen_socket();

      /** close file descriptor. */
      virtual void close();

      /** Bind and listen to any interface.
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(port_t port,i32 depth = 20);

      virtual i32 Bind(const ::net::address & paddress,i32 depth);

      /** Bind and listen to any interface, with optional protocol.
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(port_t port,const string & protocol,i32 depth = 20) ;

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(const string & intf,port_t port,i32 depth = 20);

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(const string & intf,port_t port,const string & protocol,i32 depth = 20);

      /** Bind and listen to ipv4 interface.
      \lparam a Ipv4 interface address
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(in_addr a,port_t port,i32 depth = 20);

      /** Bind and listen to ipv4 interface.
      \lparam a Ipv4 interface address
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(in_addr a,port_t port,const string & protocol,i32 depth);

      /** Bind and listen to ipv6 interface.
      \lparam a Ipv6 interface address
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(in6_addr a,port_t port,i32 depth = 20);


      /** Bind and listen to ipv6 interface.
      \lparam a Ipv6 interface address
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(in6_addr a,port_t port,const string & protocol,i32 depth);

      /** Bind and listen to network interface.
      \lparam ad Interface address
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(const ::net::address & paddress,const string & protocol,i32 depth);

      /** Return assigned port number. */
//         port_t GetPort()
//       {
//        return GetSockPort();
      //   }

      /** Return listen queue depth. */
      virtual i32 GetDepth();

      /** OnRead on a listen_socket receives an incoming connection. */
      virtual void OnRead();

      /** Please don't use this method.
      "accept()" is handled automatically in the OnRead() method. */
      virtual SOCKET Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr);

      virtual bool HasCreator();

      virtual void OnOptions(i32,i32,i32,SOCKET);



   };

   /** Binds incoming port number to new socket class X.
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
      \lparam h base_socket_handler context_object
      \lparam use_creator Optional use of creator (default true) */
      listen_socket(base_socket_handler& h,bool use_creator = true) :
         base_socket(h),
         socket(h),
         listen_socket_base(h),
         m_bHasCreate(false),
         m_creator(nullptr)
      {

         if (use_creator)
         {

            m_creator = new LISTENER(h);

            base_socket * plistener = m_creator->create();

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

            pbasesocket = m_creator->create();

            m_psocket = pbasesocket.cast < LISTENER > ();

            if (m_psocket == nullptr)
            {

               pbasesocket->release();

               pbasesocket = nullptr;

            }

            m_pbasesocket = pbasesocket;

         }
         else
         {

            pbasesocket = __new(LISTENER(Handler()));

            m_psocket = pbasesocket.cast < LISTENER >();

            if (pbasesocket == nullptr)
            {

               m_psocket->release();

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


