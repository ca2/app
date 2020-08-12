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
      template <class X>
      class listen_socket : public socket
      {
      public:

#if defined(__cplusplus_winrt)

         class os_data
         {
         public:

            ::Windows::Networking::Sockets::StreamSocketListener  ^ m_listener;

         };

         class on_listener_accept_data
         {
         public:

            ::Windows::Networking::Sockets::StreamSocketListener ^ listener;
            ::Windows::Networking::Sockets::StreamSocketListenerConnectionReceivedEventArgs ^ args;

         };

#else

         class os_data;
         class on_listener_accept_data;

#endif

         os_data * m_posdata;
         bool m_bDetach;


         /** Constructor.
         \param h base_socket_handler context_object
         \param use_creator Optional use of creator (default true) */
         listen_socket(base_socket_handler& h,bool use_creator = true) : ::object(h.get_context_application()), base_socket(h), socket(h), m_depth(0), m_creator(nullptr)
            ,m_bHasCreate(false), m_bDetach(false)
         {
            m_posdata = new os_data;
            if (use_creator)
            {
               m_creator = new X(h);
               base_socket *tmp = m_creator -> create();
               if (tmp && dynamic_cast<X *>(tmp))
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
            delete m_posdata;
         }

         /** close file descriptor. */
         void close()
         {

            if(m_posdata->m_listener != nullptr)
            {
               delete m_posdata->m_listener;
            }
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

            m_posdata->m_listener = ref new ::Windows::Networking::Sockets::StreamSocketListener;

            m_posdata->m_listener->BindServiceName(rtstr(::ca__str(port)));

            m_depth = depth;

            ::sockets::socket::os_data data;

            data.o = m_posdata->m_listener;

            attach(data);

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


            m_posdata->m_listener = ref new ::Windows::Networking::Sockets::StreamSocketListener;

            //SOCKET s;
            //m_iBindPort = ad.GetPort();
            m_posdata->m_listener->BindEndpointAsync(ad.m_posdata->m_hostname, __str(ad.get_service_number()));
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
            ::sockets::socket::os_data data;
            data.o = m_posdata->m_listener;
            attach(data);
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
         void on_listener_accept(on_listener_accept_data & data)
         {

            struct sockaddr sa;
            socklen_t sa_len = sizeof(struct sockaddr);
            SOCKET a_s = accept(GetSocket(), &sa, &sa_len);

            if (a_s == INVALID_SOCKET)
            {
               log("accept", Errno, bsd_socket_error(Errno), ::ca::log::level_error);
               return;
            }
            if (!Handler().OkToAccept(this))
            {
               log("accept", -1, "Not OK to accept", ::ca::log::level_warning);
               ::closesocket(a_s);
               return;
            }
            if (Handler().get_count() >= FD_SETSIZE)
            {
               log("accept", (int)Handler().get_count(), "base_socket_handler fd_set limit reached", ::ca::log::level_fatal);
               ::closesocket(a_s);
               return;
            }
            stream_socket *tmp = m_bHasCreate ? m_creator -> create() : new X(Handler());
            tmp->m_strCat = m_strCat;
            tmp -> EnableSSL(IsSSL()); // SSL Enabled socket
            tmp -> SetIpv6( IsIpv6() );
            tmp -> set_parent(this);
            tmp->m_tcpsocket = data.args->Socket;
            tmp -> attach(args->Socket);
            tmp -> SetNonblocking(true);
            {
               if (sa_len == sizeof(struct sockaddr_in6))
               {
                  struct sockaddr_in6 *p = (struct sockaddr_in6 *)&sa;
                  if (p -> sin6_family == AF_INET6)
                  {
                     ipv6_address ad(get_context_application(), p -> sin6_addr,ntohs(p -> sin6_port));
                     ad.SetFlowinfo(p -> sin6_flowinfo);
#ifndef _WIN32
                     ad.SetScopeId(p -> sin6_scope_id);
#endif
                     tmp -> SetRemoteAddress(ad);
                  }
               }
               if (sa_len == sizeof(struct sockaddr_in))
               {
                  struct sockaddr_in *p = (struct sockaddr_in *)&sa;
                  if (p -> sin_family == AF_INET)
                  {
                     ipv4_address ad(get_context_application(), p->sin_addr, ntohs(p->sin_port));
                     tmp -> SetRemoteAddress(ad);
                  }
               }
            }
            tmp->m_iBindPort = m_iBindPort;
            tmp -> SetConnected(true);
            tmp -> Init();
            tmp -> SetDeleteByHandler(true);
            Handler().add(tmp);
            if(m_bDetach)
            {
               tmp->detach();
            }
            if (tmp -> IsSSL()) // SSL Enabled socket
            {
               // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
               // %! If that happens and negotiation fails, the 'tmp' instance is
               // %! still added to the list of active sockets in the sockethandler.
               // %! See bugfix for this in socket_handler::Select - don't Set rwx
               // %! flags if IsCloseAndDelete() flag is true.
               // %! An even better fugbix (see tcp_socket::OnSSLAccept) now avoids
               // %! the add problem altogether, so ignore the above.
               // %! (OnSSLAccept does no longer call SSLNegotiate().)
               tmp -> OnSSLAccept();
            }
            else
            {
               tmp -> OnAccept();
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
         X *m_creator;
         bool m_bHasCreate;


      };


   } // namespace sockets


