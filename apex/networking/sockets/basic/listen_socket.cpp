#include "framework.h"
#include "listen_socket.h"


namespace sockets
{


   //listen_socket_base::listen_socket_base() :
   listen_socket_base::listen_socket_base() :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      m_depth(0)
      //, m_bDetach(false)
   {
      m_bImpl = false;
   }


   listen_socket_base::~listen_socket_base()
   {

   }


   /** close file descriptor. */
   void listen_socket_base::close()
   {

      //if (get_socket_id() != INVALID_SOCKET)
      //{

      //   close_socket(get_socket_id());

      //}

   }


   void listen_socket_base::set_should_detach(bool bSet)
   {

      m_pcomposite->set_should_detach(bSet);

   }


   bool listen_socket_base::should_detach() const
   {

      return m_pcomposite->should_detach();

   }


   /** Bind and listen to any interface.
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket_base::Bind(::networking::port_t port,i32 depth)
   {
      //if (IsIpv6())
      //{
      //   ::networking::address ad(AF_INET6, port);
      //   return Bind(ad, depth);
      //}
      //else
      //{
      //   ::networking::address ad(AF_INET, port);
      //   return Bind(ad, depth);
      //}
      return 0;
   }

   i32 listen_socket_base::Bind(::networking::address * ad,i32 depth)
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
   \lparam port Port (0 is random)
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket_base::Bind(::networking::port_t port,const string & protocol,i32 depth)
   {
      /*if (IsIpv6())
      {
         ::networking::address ad(AF_INET6, port);
         return Bind(ad.u.m_addr6.sin6_addr, port, protocol, depth);
      }
      else
      {
         ::networking::address ad(AF_INET, port);
         return Bind(ad.u.m_addr.sin_addr, port, protocol, depth);
      }*/
      return 0;
   }

   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket_base::Bind(const string & intf,::networking::port_t port,i32 depth)
   {
      
      return m_pcomposite->Bind(intf, port, depth);
      //::networking::address address(intf, port);

      //if (address.is_valid())
      //{

      //   return Bind(address, depth);

      //}

      //FATAL("Bind: name resolution of interface name failed");

      return -1;

   }


   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket_base::Bind(const string & intf,::networking::port_t port,const string & protocol,i32 depth)
   {
      //::networking::address ad(intf, port);
      //if (ad.is_valid())
      //{
      //   return Bind(ad, protocol, depth);
      //}

      //FATAL("Bind: name resolution of interface name failed");

      return -1;

   }


//   /** Bind and listen to ipv4 interface.
//   \lparam a Ipv4 interface address
//   \lparam port Port (0 is random)
//   \lparam depth Listen queue depth */
//   i32 listen_socket_base::Bind(in_addr a,::networking::port_t port,i32 depth)
//   {
//      ::networking::address ad(a, port);
//#ifdef USE_SCTP
//      if (dynamic_cast<SctpSocket *>(m_creator))
//      {
//         return Bind(ad, "sctp", depth);
//      }
//#endif
//      return Bind(ad, "tcp", depth);
//   }
//   /** Bind and listen to ipv4 interface.
//   \lparam a Ipv4 interface address
//   \lparam port Port (0 is random)
//   \lparam protocol Network protocol
//   \lparam depth Listen queue depth */
//   i32 listen_socket_base::Bind(in_addr a,::networking::port_t port,const string & protocol,i32 depth)
//   {
//      ::networking::address ad(a, port);
//      return Bind(ad, protocol, depth);
//   }
//
//   /** Bind and listen to ipv6 interface.
//   \lparam a Ipv6 interface address
//   \lparam port Port (0 is random)
//   \lparam depth Listen queue depth */
//   i32 listen_socket_base::Bind(in6_addr a,::networking::port_t port,i32 depth)
//   {
//      ::networking::address ad(a, port);
//#ifdef USE_SCTP
//      if (dynamic_cast<SctpSocket *>(m_creator))
//      {
//         return Bind(ad, "sctp", depth);
//      }
//#endif
//      return Bind(ad, "tcp", depth);
//   }
//   /** Bind and listen to ipv6 interface.
//   \lparam a Ipv6 interface address
//   \lparam port Port (0 is random)
//   \lparam protocol Network protocol
//   \lparam depth Listen queue depth */
//   i32 listen_socket_base::Bind(in6_addr a,::networking::port_t port,const string & protocol,i32 depth)
//   {
//      ::networking::address ad(a, port);
//      return Bind(ad, protocol, depth);
//   }

   /** Bind and listen to network interface.
   \lparam ad Interface address
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket_base::Bind(::networking::address * ad,const string & protocol,i32 depth)
   {

      //socket_id s;
      //m_iBindPort = ad.get_service_number();
      //if ( (s = CreateSocket(ad.get_family(), SOCK_STREAM, protocol)) == INVALID_SOCKET)
      //{
      //   return -1;
      //}
      ////::networking::address a = ad;
      ////if (ad.get_family() == AF_INET6)
      ////{
      ////
      ////   ::net::ip_enum_pointer e(e_create);

      ////   ::array < ::networking::address > ipa;

      ////   e->enumerate(ipa);

      ////   for (auto & item : ipa)
      ////   {

      ////      if (item.get_family() == AF_INET6)
      ////      {

      ////         if (!__memcmp(&item.u.m_addr6.sin6_addr, &ad.u.m_addr6.sin6_addr, sizeof(ad.u.m_addr6.sin6_addr)))
      ////         {

      ////            a = item;

      ////            break;

      ////         }

      ////      }

      ////   }

      ////}

      //auto psockaddr = ad.sa();

      //auto sockaddr_len = ad.sa_len();

      //if (bind(s, psockaddr, sockaddr_len) == -1)
      //{

      //   FATAL("bind() failed for port " << as_string(ad.get_service_number()) << ", " << Errno << ", " << bsd_socket_error(Errno));
      //   
      //   close_socket(s);

      //   return -1;

      //}

      //if (listen(s, depth) == -1)
      //{

      //   FATAL("listen" << Errno << ", " << bsd_socket_error(Errno));

      //   close_socket(s);

      //   throw ::exception(error_socket, "listen() failed for port " + as_string(ad.get_service_number()) + ": " + bsd_socket_error(Errno));

      //   return -1;

      //}

      //m_depth = depth;

      //attach(s);

      return 0;

   }


   /** Return assigned port number. */
   //         ::networking::port_t GetPort()
   //       {
   //        return GetSockPort();
   //   }

   /** Return listen queue depth. */
   i32 listen_socket_base::GetDepth()
   {
      return m_depth;
   }


   /** OnRead on a listen_socket_base receives an incoming connection. */
   void listen_socket_base::OnRead()
   {
//      char sz[sizeof(sockaddr_in6)];
//      struct sockaddr * psa = (sockaddr *)sz;
//      socklen_t sa_len = sizeof(sz);
//      socket_id a_s = accept(get_socket_id(), psa, &sa_len);
//
//      if (a_s == INVALID_SOCKET)
//      {
//
//         ERROR("accept" << Errno << bsd_socket_error(Errno));
//
//         return;
//
//      }
//
//      if (!socket_handler()->OkToAccept(this))
//      {
//
//         WARNING("accept: -1 Not OK to accept");
//
//         close_socket(a_s);
//
//         return;
//
//      }
//
//      if (socket_handler()->get_count() >= FD_SETSIZE)
//      {
//
//         FATAL("accept " << (i32)socket_handler()->get_count() << " base_socket_handler fd_set limit reached");
//
//         close_socket(a_s);
//
//         return;
//
//      }
//
//      auto tmp = ::move(create_listen_socket());
//
//      tmp->initialize(this);
//
//      tmp->set_start_time();
//
//
//      auto psystem = acmesystem()->m_papexsystem;
//
//      auto lId = psystem->sockets().m_lListenSocket++;
//
//      string strTopicText;
//
//      if (sizeof(lId) == 4)
//      {
//
//         strTopicText.format("listensckt_%" PRId32 "> ", lId);
//
//      }
//      else
//      {
//
//         strTopicText.format("listensckt_%" PRId64 "> ", lId);
//
//      }
//
//      //tmp->set_topic_text(strTopicText);
//
//      tmp->m_strCat = m_strCat;
//      
//      tmp->m_strCipherList = m_strCipherList;
//      tmp -> EnableSSL(IsSSL()); // SSL Enabled socket
//      tmp -> SetIpv6( IsIpv6() );
//      tmp -> set_parent(this);
//      tmp -> attach(a_s);
//      tmp -> SetNonblocking(true);
//      tmp->SetRemoteHostname(::networking::address(*psa));
//      tmp->m_iBindPort = m_iBindPort;
//      tmp -> SetConnected(true);
//      tmp -> Init();
//      tmp -> SetDeleteByHandler(true);
//      if (tmp -> IsSSL()) // SSL Enabled socket
//      {
//         // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
//         // %! If that happens and negotiation fails, the 'tmp' instance is
//         // %! still added to the list of active sockets in the sockethandler.
//         // %! See bugfix for this in socket_handler::Select - don't set rwx
//         // %! flags if IsCloseAndDelete() flag is true.
//         // %! An even better fugbix (see tcp_socket::OnSSLAccept) now avoids
//         // %! the add problem altogether, so ignore the above.
//         // %! (OnSSLAccept does no longer call SSLNegotiate().)
//         tmp -> OnSSLAccept();
//      }
//      else
//      {
//         tmp -> OnAccept();
//      }
//      
//      if (m_bDetach)
//      {
//         
//         tmp->prepare_for_detach();
//
//      }
////      auto passociation = m_psockethandler->new_association(tmp);
//
//      //socket_handler()->move(passociation);
//
//      socket_handler()->move2(::move(tmp));

   }

   ///** Please don't use this method.
   //"accept()" is handled automatically in the OnRead() method. */
   //socket_id listen_socket_base::Accept(socket_id socket, struct sockaddr *saptr, socklen_t *lenptr)
   //{
   //   return accept(socket, saptr, lenptr);
   //}

   bool listen_socket_base:: HasCreator()
   {
      return false;
   }

   //void listen_socket_base::OnOptions(i32,i32,i32,socket_id)
   //{
   //   SetSoReuseaddr(true);
   //}


   void listen_socket_base::initialize(::particle * pparticle)
   {

      socket::initialize(pparticle);

      __construct(m_pcomposite);

      m_p2 = m_pcomposite->m_p2;

      m_pcomposite->m_pcomposite = this;

      m_pcomposite->m_bImpl = true;
      
   }


   base_socket * listen_socket_base::base_socket_composite()
   {

      return m_pcomposite;

   }


   ::pointer<socket>listen_socket_base::create_listen_socket()
   {

      return m_pcomposite->create_listen_socket();

   }


   void listen_socket_base::set_ssl_catalog(const ::string & strCat)
   {

      return m_pcomposite->set_ssl_catalog(strCat);

   }

   void listen_socket_base::set_ssl_cipher_list(const ::string & strCipherList)
   {

      return m_pcomposite->set_ssl_cipher_list(strCipherList);

   }



} // namespace sockets



