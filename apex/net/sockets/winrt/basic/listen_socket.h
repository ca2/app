/** \file listen_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/

// xxx ref_Anders_Hedstrom_sockets_library.txt

#pragma once
/*
#ifdef _WIN32
//
#else
//#include <errno.h>
#endif
*/



namespace sockets
{


   /** Binds incoming port number to new socket class X.
\ingroup basic */
   class CLASS_DECL_APEX listen_socket_base :
      virtual public socket
   {
   public:


      i32                  m_depth;
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
      virtual i32 Bind(port_t port, i32 depth = 20);

      virtual i32 Bind(const ::net::address& paddress, i32 depth);

      /** Bind and listen to any interface, with optional protocol.
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(port_t port, const string& protocol, i32 depth = 20);

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam depth Listen queue depth */
      virtual i32 Bind(const string& intf, port_t port, i32 depth = 20);

      /** Bind and listen to specific interface.
      \lparam intf Interface hostname
      \lparam port Port (0 is random)
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(const string& intf, port_t port, const string& protocol, i32 depth = 20);

//#ifdef BSD_STYLE
//      /** Bind and listen to ipv4 interface.
//      \lparam a Ipv4 interface address
//      \lparam port Port (0 is random)
//      \lparam depth Listen queue depth */
//      virtual i32 Bind(in_addr a, port_t port, i32 depth = 20);
//
//      /** Bind and listen to ipv4 interface.
//      \lparam a Ipv4 interface address
//      \lparam port Port (0 is random)
//      \lparam protocol Network protocol
//      \lparam depth Listen queue depth */
//      virtual i32 Bind(in_addr a, port_t port, const string& protocol, i32 depth);
//
//      /** Bind and listen to ipv6 interface.
//      \lparam a Ipv6 interface address
//      \lparam port Port (0 is random)
//      \lparam depth Listen queue depth */
//      virtual i32 Bind(in6_addr a, port_t port, i32 depth = 20);
//
//
//      /** Bind and listen to ipv6 interface.
//      \lparam a Ipv6 interface address
//      \lparam port Port (0 is random)
//      \lparam protocol Network protocol
//      \lparam depth Listen queue depth */
//      virtual i32 Bind(in6_addr a, port_t port, const string& protocol, i32 depth);

      /** Bind and listen to network interface.
      \lparam ad Interface address
      \lparam protocol Network protocol
      \lparam depth Listen queue depth */
      virtual i32 Bind(const ::net::address& paddress, const string& protocol, i32 depth);

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
      //virtual SOCKET Accept(SOCKET socket, struct sockaddr* saptr, socklen_t* lenptr);

      virtual bool HasCreator();

      virtual void OnOptions(i32, i32, i32, SOCKET);



   };


   /** Binds incoming port number to new socket class SOCKET_IMPL.
   \ingroup basic */
   template <class SOCKET_IMPL>
   class listen_socket : 
      virtual public listen_socket_base
   {
   public:

//#if defined(__cplusplus_winrt)


      ref class bridge
      {
      internal:
         listen_socket* m_p;

            bridge(listen_socket* p) :
            m_p(p)
         {
         }

      public:



               

         void StreamSocketListener_ConnectionReceived(::Windows::Networking::Sockets::StreamSocketListener^ listener,
            ::Windows::Networking::Sockets::StreamSocketListenerConnectionReceivedEventArgs^ args)
         {

            m_p->StreamSocketListener_ConnectionReceived(listener, args);

         }

      };

      ::Windows::Networking::Sockets::StreamSocketListener  ^ m_listener;
      Windows::Foundation::EventRegistrationToken m_tokenConnectionReceived;
      bridge ^ m_bridge;
      //class on_listener_accept_data
      //{
      //public:

      //   ::Windows::Networking::Sockets::StreamSocketListener ^ listener;
      //   ::Windows::Networking::Sockets::StreamSocketListenerConnectionReceivedEventArgs ^ args;

      //};

//#else
//
//         class os_data;
//         class on_listener_accept_data;
//
//#endif

//       os_data * m_posdata;
      bool m_bDetach;


      /** Constructor.
      \param h base_socket_handler context_object
      \param use_creator Optional use of creator (default true) */
      listen_socket(base_socket_handler& h,bool use_creator = true) :
         ::object(h.get_context_application()), 
         listen_socket_base(h),
         base_socket(h),
         socket(h), 
         m_depth(0), 
         m_creator(nullptr)
         ,m_bHasCreate(false),
         m_bDetach(false)
      {
            
         m_bridge = ref new bridge(this);
            
         //m_posdata = new os_data;

         if (use_creator)
         {
            m_creator = new SOCKET_IMPL(h);
            base_socket *tmp = m_creator ->new_listen_socket();
            if (tmp && dynamic_cast<SOCKET_IMPL *>(tmp))
            {
               m_bHasCreate = true;
            }
            if (tmp)
            {
               delete tmp;
            }
         }
      }
      ~listen_socket() {
         if (m_creator)
         {
            delete m_creator;
         }
         //delete m_posdata;
      }

      /** close file descriptor. */
      void close()
      {
            
         m_listener = nullptr;

         //if(m_listener != nullptr)
         //{
         //   m_listener = nullptr;
         //}
/*            if (GetSocket() != INVALID_SOCKET)
         {
            ::closesocket(GetSocket());
         }*/
         //return 0;
      }

      /** Bind and listen to any interface.
      \param port Port (0 is random)
      \param depth Listen queue depth */
      int Bind(port_t port, int depth = 20)
      {

         return Bind(port, "tcp", depth);

      }

      int Bind(const char * psz, port_t port, int depth = 20)
      {

         return Bind(psz, port, "tcp", depth);

      }

      int Bind(::net::address & ad,int depth)
      {

#ifdef USE_SCTP

         if (dynamic_cast<SctpSocket *>(m_creator))
         {

            return Bind(ad, "sctp", depth);

         }

#endif

         return Bind(ad, "tcp", depth);

      }

      /** Bind and listen to any interface, with optional protocol.
      \param port Port (0 is random)
      \param protocol Network protocol
      \param depth Listen queue depth */
      int Bind(port_t port, const string & protocol, int depth = 20)
      {

         m_listener = ref new ::Windows::Networking::Sockets::StreamSocketListener;

         m_listener->BindServiceNameAsync(__str(port));

         m_depth = depth;

         //::sockets::socket::os_data data;

         //data.o = m_posdata->m_listener;

         //attach(data);

         create_socket();

         return 0;

      }


      int Bind(const char * pszInterface, port_t port, const string & protocol, int depth = 20)
      {

         return Bind(::net::address(pszInterface, port), protocol, depth);

      }


      /** Bind and listen to network interface.
      \param ad Interface address
      \param protocol Network protocol
      \param depth Listen queue depth */
      int Bind(::net::address & ad, const string & protocol, int depth = 20)
      {

         create_socket();

         m_listener = ref new ::Windows::Networking::Sockets::StreamSocketListener;

         m_tokenConnectionReceived = m_listener->ConnectionReceived += ref new ::Windows::Foundation::TypedEventHandler < ::Windows::Networking::Sockets::StreamSocketListener^, ::Windows::Networking::Sockets::StreamSocketListenerConnectionReceivedEventArgs^>(m_bridge, &bridge::StreamSocketListener_ConnectionReceived);

         //SOCKET s;
         //m_iBindPort = ad.GetPort();
         m_listener->BindEndpointAsync(ad.m_hostname, __str(ad.get_service_number()));
/*            {
            return -1;
         }
         if (bind(s, ad, ad) == -1)
         {
            log("bind() failed for port " + ::ca__str(ad.GetPort()), Errno, bsd_socket_error(Errno), ::ca::log::level_fatal);
            ::closesocket(s);
            return -1;
         }
         if (listen(s, depth) == -1)
         {
            log("listen", Errno, bsd_socket_error(Errno), ::ca::log::level_fatal);
            ::closesocket(s);
            __throw(::exception::exception("listen() failed for port " + ::ca__str(ad.GetPort()) + ": " + bsd_socket_error(Errno)));
            return -1;
         }*/
         m_depth = depth;
         //::sockets::socket::os_data data;
         //data.o = m_listener;
         //m_socket = ::apex::get_system()->sockets().net().m_
         //attach(data);
         return 0;

      }


      /** Return assigned port number. */
      port_t GetPort()
      {
         return GetLocalPort();
      }

      /** Return listen queue depth. */
      int GetDepth()
      {
         return m_depth;
      }

      /** OnRead on a listen_socket receives an incoming connection. */
      void StreamSocketListener_ConnectionReceived(::Windows::Networking::Sockets::StreamSocketListener ^ listener, ::Windows::Networking::Sockets::StreamSocketListenerConnectionReceivedEventArgs ^ args)
      {

         //struct sockaddr sa;

         //socklen_t sa_len = sizeof(struct sockaddr);

         //SOCKET a_s = accept(GetSocket(), &sa, &sa_len);

         //if (a_s == INVALID_SOCKET)
         //{
         //   
         //   //log("accept", Errno, bsd_socket_error(Errno), ::ca::log::level_error);

         //   return;

         //}
            
         //if (!Handler().OkToAccept(this))
         //{
         //   
         //   //log("accept", -1, "Not OK to accept", ::ca::log::level_warning);
         //   
         //   ::closesocket(a_s);

         //   return;

         //}
            
         //if (Handler().get_count() >= FD_SETSIZE)
         //{
         //   
         //   //log("accept", (int)Handler().get_count(), "base_socket_handler fd_set limit reached", ::ca::log::level_fatal);
         //   ::closesocket(a_s);

         //   return;

         //}
            
         stream_socket* pstreamsocket = nullptr;

         if (m_bHasCreate)
         {

            pstreamsocket = dynamic_cast <stream_socket*>(m_creator->new_listen_socket());
               
         }
         else
         {

            pstreamsocket = new SOCKET_IMPL(Handler());

         }

         pstreamsocket->m_strCat = m_strCat;
         pstreamsocket->EnableSSL(IsSSL()); // SSL Enabled socket
         pstreamsocket->SetIpv6( IsIpv6() );
         pstreamsocket->set_parent(this);
         pstreamsocket->m_streamsocket = args->Socket;
         //pstreamsocket->attach(args->Socket);
         pstreamsocket->SetNonblocking(true);
            
//            {
//               
//               if (sa_len == sizeof(struct sockaddr_in6))
//               {
//                  
//                  struct sockaddr_in6 *p = (struct sockaddr_in6 *)&sa;
//                  
//                  if (p -> sin6_family == AF_INET6)
//                  {
//                     
//                     ipv6_address ad(get_context_application(), p -> sin6_addr,ntohs(p -> sin6_port));
//                     
//                     ad.SetFlowinfo(p -> sin6_flowinfo);
//
//#ifndef _WIN32
//
//                     ad.SetScopeId(p -> sin6_scope_id);
//
//#endif
//
//                     tmp -> SetRemoteAddress(ad);
//
//                  }
//
//               }
//
//               if (sa_len == sizeof(struct sockaddr_in))
//               {
//
//                  struct sockaddr_in *p = (struct sockaddr_in *)&sa;
//
//                  if (p -> sin_family == AF_INET)
//                  {
//                     
//                     ipv4_address ad(get_context_application(), p->sin_addr, ntohs(p->sin_port));
//
//                     tmp -> SetRemoteAddress(ad);
//
//                  }
//
//               }
//
//            }

         pstreamsocket->m_iBindPort = m_iBindPort;
         pstreamsocket->SetConnected(true);
         pstreamsocket->Init();
         pstreamsocket->SetDeleteByHandler(true);
            
         //Handler().add(tmp);

         if(m_bDetach)
         {

            pstreamsocket->detach();

         }

         if (pstreamsocket->IsSSL()) // SSL Enabled socket
         {

            // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
            // %! If that happens and negotiation fails, the 'tmp' instance is
            // %! still added to the list of active sockets in the sockethandler.
            // %! See bugfix for this in socket_handler::Select - don't Set rwx
            // %! flags if IsCloseAndDelete() flag is true.
            // %! An even better fugbix (see tcp_socket::OnSSLAccept) now avoids
            // %! the add problem altogether, so ignore the above.
            // %! (OnSSLAccept does no longer call SSLNegotiate().)
            pstreamsocket->OnSSLAccept();

         }
         else
         {

            pstreamsocket->OnAccept();

         }

      }


      /** Please don't use this method.
      "accept()" is handled automatically in the OnRead() method. */
      //virtual SOCKET Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr)
      //{
         // return accept(socket, saptr, lenptr);
      //}

      bool HasCreator() { return m_bHasCreate; }

      void OnOptions(int,int,int,SOCKET)
      {
         SetSoReuseaddr(true);
      }

      int m_depth;
      SOCKET_IMPL *m_creator;
      bool m_bHasCreate;


   };


} // namespace sockets



