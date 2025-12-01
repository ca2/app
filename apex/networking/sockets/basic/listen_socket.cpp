#include "framework.h"
#include "listen_socket.h"


namespace sockets
{


   //listen_socket::listen_socket() :
   listen_socket::listen_socket() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //m_bListeningDetach(false),
      //m_depth(0)
      //, m_bDetach(false)
   {
      m_bImpl = false;
   }


   listen_socket::~listen_socket()
   {

   }





   void listen_socket::set_attend_socket_type(const ::platform::type & type)
   {

      m_typeAttendSocket = type;

   }


   /** close file descriptor. */
   void listen_socket::close()
   {

      //if (get_socket_id() != INVALID_SOCKET)
      //{

      //   close_socket(get_socket_id());

      //}

   }



   void listen_socket::SetListeningDetach(bool bSet)
   {

      m_bListeningDetach = true;

   }


   bool listen_socket::IsListeningDetach()
   {

      return m_bListeningDetach;

   }


   //void listen_socket::set_should_detach(bool bSet)
   //{

   //   m_plistensocketimpl->set_should_detach(bSet);

   //}


   //bool listen_socket::should_detach() const
   //{

   //   return m_plistensocketimpl->should_detach();

   //}


   /** Bind and listen to any interface.
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   int listen_socket::Bind(::networking::port_t port,int depth)
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

   int listen_socket::Bind(::networking::address * ad,int depth)
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
   int listen_socket::Bind(::networking::port_t port,const string & protocol,int depth)
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
   int listen_socket::Bind(const ::scoped_string & scopedstrInterface,::networking::port_t port,int depth)
   {
      
      return m_plistensocketImpl->Bind(scopedstrInterface, port, depth);
      //::networking::address address(intf, port);

      //if (address.is_valid())
      //{

      //   return Bind(address, depth);

      //}

      //fatal() <<"Bind: name resolution of interface name failed";

      return -1;

   }


   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   int listen_socket::Bind(const ::scoped_string & scopedstrInterface,::networking::port_t port,const string & protocol,int depth)
   {
      //::networking::address ad(intf, port);
      //if (ad.is_valid())
      //{
      //   return Bind(ad, protocol, depth);
      //}

      //fatal() <<"Bind: name resolution of interface name failed";

      return -1;

   }


//   /** Bind and listen to ipv4 interface.
//   \lparam a Ipv4 interface address
//   \lparam port Port (0 is random)
//   \lparam depth Listen queue depth */
//   int listen_socket::Bind(in_addr a,::networking::port_t port,int depth)
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
//   int listen_socket::Bind(in_addr a,::networking::port_t port,const string & protocol,int depth)
//   {
//      ::networking::address ad(a, port);
//      return Bind(ad, protocol, depth);
//   }
//
//   /** Bind and listen to ipv6 interface.
//   \lparam a Ipv6 interface address
//   \lparam port Port (0 is random)
//   \lparam depth Listen queue depth */
//   int listen_socket::Bind(in6_addr a,::networking::port_t port,int depth)
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
//   int listen_socket::Bind(in6_addr a,::networking::port_t port,const string & protocol,int depth)
//   {
//      ::networking::address ad(a, port);
//      return Bind(ad, protocol, depth);
//   }

   /** Bind and listen to network interface.
   \lparam ad Interface address
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   int listen_socket::Bind(::networking::address * ad,const string & protocol,int depth)
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

      //   fatal() <<"bind() failed for port " << as_string(ad.get_service_number()) << ", " << Errno << ", " << bsd_socket_error(Errno);
      //   
      //   close_socket(s);

      //   return -1;

      //}

      //if (listen(s, depth) == -1)
      //{

      //   fatal() <<"listen" << Errno << ", " << bsd_socket_error(Errno);

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
   int listen_socket::GetDepth()
   {
      return m_depth;
   }


   /** OnRead on a listen_socket receives an incoming connection. */
   void listen_socket::OnRead()
   {

      listen_socket_impl::OnRead();

//      char sz[sizeof(sockaddr_in6)];
//      struct sockaddr * psa = (sockaddr *)sz;
//      socklen_t sa_len = sizeof(sz);
//      socket_id a_s = accept(get_socket_id(), psa, &sa_len);
//
//      if (a_s == INVALID_SOCKET)
//      {
//
//         error() <<"accept" << Errno << bsd_socket_error(Errno);
//
//         return;
//
//      }
//
//      if (!socket_handler()->OkToAccept(this))
//      {
//
//         warning() <<"accept: -1 Not OK to accept";
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
//         fatal() <<"accept " << (int)socket_handler()->get_count() << " base_socket_handler fd_set limit reached";
//
//         close_socket(a_s);
//
//         return;
//
//      }
//
//      auto tmp = ::transfer(create_listen_socket());
//
//      tmp->initialize(this);
//
//      tmp->set_start_time();
//
//
//      auto psystem = system();
//
//      auto lId = psystem->sockets().m_lListenSocket++;
//
//      string strTopicText;
//
//      if (sizeof(lId) == 4)
//      {
//
//         strTopicText.formatf("listensckt_%" PRId32 "> ", lId);
//
//      }
//      else
//      {
//
//         strTopicText.formatf("listensckt_%" PRId64 "> ", lId);
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
//         // %! still added to the list_base of active sockets in the sockethandler.
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
//      //socket_handler()->transfer(passociation);
//
//      socket_handler()->move2(::transfer(tmp));

   }

   ///** Please don't use this method.
   //"accept()" is handled automatically in the OnRead() method. */
   //socket_id listen_socket::Accept(socket_id socket, struct sockaddr *saptr, socklen_t *lenptr)
   //{
   //   return accept(socket, saptr, lenptr);
   //}

   bool listen_socket:: HasCreator()
   {
      return false;
   }


   ::pointer < ::sockets::socket > listen_socket::create_attend_socket()
   {
      return øcreate_by_type(m_typeAttendSocket, m_pfactory);
   }

   //void listen_socket::OnOptions(int,int,int,socket_id)
   //{
   //   SetSoReuseaddr(true);
   //}


   void listen_socket::initialize(::particle * pparticle)
   {

      socket::initialize(pparticle);

      øconstruct(m_plistensocketImpl);

      //m_p2 = m_plistensocketImpl->m_p2;

      m_plistensocketImpl->m_plistensocketInterface = this;

      m_plistensocketImpl->m_bImpl = true;
      
   }


   void listen_socket::destroy()
   {

      m_plistensocketImpl.defer_destroy();

      m_pfactory.release();

      listen_socket_impl::destroy();

   }


   void listen_socket::Reset()
   {


   }


   base_socket * listen_socket::base_socket_impl()
   {

      return m_plistensocketImpl;

   }

   base_socket* listen_socket::base_socket_interface()
   {

      return m_plistensocketInterface;

   }

   ::pointer<listen_socket_impl>listen_socket::create_listen_socket_impl()
   {

      return øcreate < listen_socket_impl >();

   }


   void listen_socket::set_ssl_catalog(const ::scoped_string & scopedstrCat)
   {

      return m_plistensocketImpl->set_ssl_catalog(scopedstrCat);

   }


   void listen_socket::set_ssl_cipher_list(const ::scoped_string & scopedstrCipherList)
   {

      return m_plistensocketImpl->set_ssl_cipher_list(scopedstrCipherList);

   }



} // namespace sockets



