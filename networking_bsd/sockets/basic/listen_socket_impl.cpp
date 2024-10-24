#include "framework.h"
#include "listen_socket_impl.h"
#include "socket_handler.h"
////#include "acme/exception/exception.h"
#include "apex/platform/system.h"
#include "networking_bsd/address.h"
#include "networking_bsd/networking.h"


#undef ERROR
#define log_error(...) TRACE_LOG_ERROR(__VA_ARGS__)

namespace sockets_bsd
{


   //listen_socket_impl::listen_socket_impl() :
   listen_socket_impl::listen_socket_impl() // :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //m_depth(0),
      //m_bDetach(false)
   {

   }


   listen_socket_impl::~listen_socket_impl()
   {

   }


   void listen_socket_impl::initialize(::particle * pparticle)
   {

      socket::initialize(pparticle);

   }

   void listen_socket_impl::set_ssl_catalog(const ::string & strCat)
   {

      m_strCat = strCat;

   }

   void listen_socket_impl::set_ssl_cipher_list(const ::string & strCipherList)
   {

      m_strCipherList = strCipherList;

   }
   /** close file descriptor. */
   void listen_socket_impl::close()
   {

      if (GetSocketId() != INVALID_SOCKET)
      {

         close_socket((::i32) GetSocketId());

      }

   }

   /** Bind and listen to any interface.
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(::networking::port_t port,i32 depth)
   {
      if (IsIpv6())
      {
         auto paddress = __allocate ::networking_bsd::address();
         paddress->set_family(AF_INET6, port);
         //::networking::address ad(AF_INET6, port);
         return Bind(paddress.m_p, depth);
      }
      else
      {
         auto paddress = __allocate ::networking_bsd::address();
         paddress->set_family(AF_INET, port);
         return Bind(paddress.m_p, depth);
      }
   }

   i32 listen_socket_impl::Bind(::networking::address * ad,i32 depth)
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
   i32 listen_socket_impl::Bind(::networking::port_t port,const string & protocol,i32 depth)
   {
      if (IsIpv6())
      {
         auto paddress = __allocate ::networking_bsd::address();
         paddress->set_family(AF_INET6, port);
         return Bind(paddress->u.m_addr6.sin6_addr, port, protocol, depth);
      }
      else
      {
         auto paddress = __allocate ::networking_bsd::address();
         paddress->set_family(AF_INET, port);
         return Bind(paddress->u.m_addr.sin_addr, port, protocol, depth);
      }
   }

   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(const string & intf,::networking::port_t port,i32 depth)
   {
      
      auto paddress = __SystemNetworking(system())->create_address(intf, preferred_address_type(), port);

      if (paddress->is_valid())
      {

         return Bind(paddress.m_p, depth);

      }

      fatal() <<"Bind: name resolution of interface name failed";

      return -1;

   }


   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(const string & intf,::networking::port_t port,const string & protocol,i32 depth)
   {

      auto paddress = __SystemNetworking(system())->create_address(intf, preferred_address_type(), port);

      if (paddress->is_valid())
      {

         return Bind(paddress.m_p, protocol, depth);

      }

      fatal() <<"Bind: name resolution of interface name failed";

      return -1;

   }


   /** Bind and listen to ipv4 interface.
   \lparam a Ipv4 interface address
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(in_addr a,::networking::port_t port,i32 depth)
   {

      auto paddress = __allocate ::networking_bsd::address();

      paddress->set_address(a, port);

#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      
      return Bind(paddress.m_p, "tcp", depth);

   }

   /** Bind and listen to ipv4 interface.
   \lparam a Ipv4 interface address
   \lparam port Port (0 is random)
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(in_addr a,::networking::port_t port,const string & protocol,i32 depth)
   {

      auto paddress = __allocate ::networking_bsd::address();

      paddress->set_address(a, port);

      return Bind(paddress.m_p, protocol, depth);

   }

   /** Bind and listen to ipv6 interface.
   \lparam a Ipv6 interface address
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(in6_addr a,::networking::port_t port,i32 depth)
   {

      auto paddress = __allocate ::networking_bsd::address();

      paddress->set_address(a, port);

#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      
      return Bind(paddress.m_p, "tcp", depth);

   }


   /** Bind and listen to ipv6 interface.
   \lparam a Ipv6 interface address
   \lparam port Port (0 is random)
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(in6_addr a,::networking::port_t port,const string & protocol,i32 depth)
   {

      auto paddress = __allocate ::networking_bsd::address();

      paddress->set_address(a, port);

      return Bind(paddress.m_p, protocol, depth);

   }


   /** Bind and listen to network interface.
   \lparam ad Interface address
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket_impl::Bind(::networking::address * paddress,const string & protocol,i32 depth)
   {

      ::pointer < ::networking_bsd::address > paddress2 = paddress;

      SOCKET s;
      m_iBindPort = paddress->get_service_number();
      if ( (s = CreateSocket(paddress2->get_family(), SOCK_STREAM, protocol)) == INVALID_SOCKET)
      {
         return -1;
      }
      //::networking::address a = ad;
      //if (ad.get_family() == AF_INET6)
      //{
      //
      //   ::net::ip_enum_pointer e(e_create);

      //   ::array < ::networking::address > ipa;

      //   e->enumerate(ipa);

      //   for (auto & item : ipa)
      //   {

      //      if (item.get_family() == AF_INET6)
      //      {

      //         if (!__memcmp(&item.u.m_addr6.sin6_addr, &ad.u.m_addr6.sin6_addr, sizeof(ad.u.m_addr6.sin6_addr)))
      //         {

      //            a = item;

      //            break;

      //         }

      //      }

      //   }

      //}

      auto psockaddr = paddress2->sa();

      auto sockaddr_len = paddress2->sa_len();

      if (::bind(s, psockaddr, sockaddr_len) != 0)
      {

         fatal() <<"bind() failed for port " << ::as_string(paddress2->get_service_number()) << ", " << networking_last_error() << ", " << bsd_socket_error(networking_last_error());
         
         close_socket(s);

         return -1;

      }

      if (::listen(s, depth) != 0)
      {

         fatal() <<"listen" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         close_socket(s);

         throw ::exception(error_socket, "listen() failed for port " + ::as_string(paddress2->get_service_number()) + ": " + bsd_socket_error(networking_last_error()));

         return -1;

      }

      m_depth = depth;

      attach(s);

      return 0;

   }


   /** Return assigned port number. */
   //         ::networking::port_t GetPort()
   //       {
   //        return GetSockPort();
   //   }

   /** Return listen queue depth. */
   i32 listen_socket_impl::GetDepth()
   {
      return m_depth;
   }


   //void listen_socket_impl::SetStartDetach(bool bSet)
   //{

   //   m_bStartDetach = bSet;

   //}


   //bool listen_socket_impl::IsStartDetach()
   //{

   //   return m_bStartDetach;

   //}


   /** OnRead on a listen_socket_impl receives an incoming connection. */
   void listen_socket_impl::OnRead()
   {
      union sockaddr_union
      {
         sockaddr_in a;
         sockaddr_in6 b;
         sockaddr c;
      };

      auto socketid = GetSocketId();

      sockaddr_union sockaddr{};

      socklen_t sockaddr_len = sizeof(sockaddr_union);

      SOCKET socketAccept = accept(socketid, &sockaddr.c, &sockaddr_len);

      if (socketAccept == INVALID_SOCKET)
      {

         error() <<"accept" << networking_last_error() << bsd_socket_error(networking_last_error());

         return;

      }

      ::pointer < ::sockets_bsd::socket_handler> phandler = m_psockethandler;

      if (!phandler->OkToAccept(this))
      {

         warning() <<"accept: -1 Not OK to accept";

         close_socket(socketAccept);

         return;

      }

      if (socket_handler()->get_count() >= FD_SETSIZE)
      {

         fatal() <<"accept " << (i32)socket_handler()->get_count() << " base_socket_handler fd_set limit reached";

         close_socket(socketAccept);

         return;

      }
      
      auto psocketAttend = m_plistensocketInterface->create_attend_socket();

      //psocketAttend->initialize(this);

      ::pointer < ::sockets_bsd::base_socket > psocketImpl = psocketAttend->base_socket_impl();

      psocketImpl->set_start_time();

      auto psystem = system();

      auto pnetworking2 = __SystemNetworking(psystem);

      auto lId = pnetworking2->m_iListenSocket++;

      string strTopicText;

      if (sizeof(lId) == 4)
      {

         strTopicText.formatf("listensckt_%" PRId32 "> ", lId);

      }
      else
      {

         strTopicText.formatf("listensckt_%" PRId64 "> ", lId);

      }

      //tmp->set_topic_text(strTopicText);

      psocketImpl->m_strCat = m_strCat;
      
      psocketImpl->m_strCipherList = m_strCipherList;
      psocketImpl-> EnableSSL(IsSSL()); // SSL Enabled socket
      psocketImpl-> SetIpv6( IsIpv6() );
      psocketImpl-> set_parent(this);
      psocketImpl-> attach(socketAccept);
      psocketImpl->OnOptions(m_iFamily, m_iSocketType, m_iProtocolType, socketAccept);
      //psocketImpl-> SetNonblocking(true);
      auto paddressRemote = __allocate ::networking_bsd::address();
      paddressRemote->set_address(sockaddr.c, sockaddr_len);
      //tmp->SetRemoteHostname(::networking::address(*psa));
      psocketImpl->SetRemoteHostname(paddressRemote);
      psocketImpl->m_iBindPort = m_iBindPort;
      psocketImpl-> SetConnected(true);
      psocketImpl-> Init();
      psocketImpl-> SetDeleteByHandler(true);
      if (psocketImpl-> IsSSL()) // SSL Enabled socket
      {
         // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
         // %! If that happens and negotiation fails, the 'tmp' instance is
         // %! still added to the list of active networking_bsd in the sockethandler.
         // %! See bugfix for this in socket_handler::Select - don't set rwx
         // %! flags if IsCloseAndDelete() flag is true.
         // %! An even better fugbix (see tcp_socket::OnSSLAccept) now avoids
         // %! the add problem altogether, so ignore the above.
         // %! (OnSSLAccept does no longer call SSLNegotiate().)
         psocketImpl-> OnSSLAccept();
      }
      else
      {
         psocketImpl-> OnAccept();
      }
      
      if (m_plistensocketInterface->m_bListeningDetach)
      {
         
         psocketImpl->prepare_for_detach();

      }
      else
      {

         throw "Debug... is it not detached?!?!";

      }
//      auto passociation = m_psockethandler->new_association(tmp);

      //socket_handler()->transfer(passociation);

      m_psockethandler->add(psocketAttend);

   }

   /** Please don't use this method.
   "accept()" is handled automatically in the OnRead() method. */
   SOCKET listen_socket_impl::Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr)
   {
      return accept(socket, saptr, lenptr);
   }

   bool listen_socket_impl:: HasCreator()
   {
      return false;
   }

   void listen_socket_impl::OnOptions(i32,i32,i32,SOCKET s)
   {
      //_SetSoReuseaddr(s, true);
   }


   //void listen_socket_impl::initialize(::particle * pparticle)
   //{


   //}


   //::pointer<::sockets::socket>listen_socket_impl::create_listen_socket()
   //{

   //   return nullptr;

   //}


} // namespace sockets_bsd



