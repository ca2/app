#include "framework.h"
#include "listen_socket.h"
#include "socket_handler.h"
////#include "acme/exception/exception.h"
#include "apex/platform/system.h"
#include "networking_bsd/address.h"
#include "networking_bsd/networking.h"


#undef ERROR
#define ERROR(...) TRACE_LOG_ERROR(__VA_ARGS__)

namespace sockets_bsd
{


   //listen_socket::listen_socket() :
   listen_socket::listen_socket() :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      m_depth(0),
      m_bDetach(false)
   {

   }


   listen_socket::~listen_socket()
   {

   }


   void listen_socket::initialize(::particle * pparticle)
   {

      socket::initialize(pparticle);

   }

   void listen_socket::set_ssl_catalog(const ::string & strCat)
   {

      m_strCat = strCat;

   }

   void listen_socket::set_ssl_cipher_list(const ::string & strCipherList)
   {

      m_strCipherList = strCipherList;

   }
   /** close file descriptor. */
   void listen_socket::close()
   {

      if (GetSocketId() != INVALID_SOCKET)
      {

         close_socket(GetSocketId());

      }

   }

   /** Bind and listen to any interface.
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket::Bind(::networking::port_t port,i32 depth)
   {
      if (IsIpv6())
      {
         auto paddress = __new(::networking_bsd::address);
         paddress->set_family(AF_INET6, port);
         //::networking::address ad(AF_INET6, port);
         return Bind(paddress.m_p, depth);
      }
      else
      {
         auto paddress = __new(::networking_bsd::address);
         paddress->set_family(AF_INET, port);
         return Bind(paddress.m_p, depth);
      }
   }

   i32 listen_socket::Bind(::networking::address * ad,i32 depth)
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
   i32 listen_socket::Bind(::networking::port_t port,const string & protocol,i32 depth)
   {
      if (IsIpv6())
      {
         auto paddress = __new(::networking_bsd::address);
         paddress->set_family(AF_INET6, port);
         return Bind(paddress->u.m_addr6.sin6_addr, port, protocol, depth);
      }
      else
      {
         auto paddress = __new(::networking_bsd::address);
         paddress->set_family(AF_INET, port);
         return Bind(paddress->u.m_addr.sin_addr, port, protocol, depth);
      }
   }

   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket::Bind(const string & intf,::networking::port_t port,i32 depth)
   {
      
      auto paddress = __SystemNetworking(acmesystem())->create_address(intf, port);

      if (paddress->is_valid())
      {

         return Bind(paddress.m_p, depth);

      }

      FATAL("Bind: name resolution of interface name failed");

      return -1;

   }


   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket::Bind(const string & intf,::networking::port_t port,const string & protocol,i32 depth)
   {

      auto paddress = __SystemNetworking(acmesystem())->create_address(intf, port);

      if (paddress->is_valid())
      {

         return Bind(paddress.m_p, protocol, depth);

      }

      FATAL("Bind: name resolution of interface name failed");

      return -1;

   }


   /** Bind and listen to ipv4 interface.
   \lparam a Ipv4 interface address
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket::Bind(in_addr a,::networking::port_t port,i32 depth)
   {

      auto paddress = __new(::networking_bsd::address);

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
   i32 listen_socket::Bind(in_addr a,::networking::port_t port,const string & protocol,i32 depth)
   {

      auto paddress = __new(::networking_bsd::address);

      paddress->set_address(a, port);

      return Bind(paddress.m_p, protocol, depth);

   }

   /** Bind and listen to ipv6 interface.
   \lparam a Ipv6 interface address
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   i32 listen_socket::Bind(in6_addr a,::networking::port_t port,i32 depth)
   {

      auto paddress = __new(::networking_bsd::address);

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
   i32 listen_socket::Bind(in6_addr a,::networking::port_t port,const string & protocol,i32 depth)
   {

      auto paddress = __new(::networking_bsd::address);

      paddress->set_address(a, port);

      return Bind(paddress.m_p, protocol, depth);

   }


   /** Bind and listen to network interface.
   \lparam ad Interface address
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   i32 listen_socket::Bind(::networking::address * paddress,const string & protocol,i32 depth)
   {

      auto paddress2 = __Address(paddress);

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

      if (bind(s, psockaddr, sockaddr_len) == -1)
      {

         FATAL("bind() failed for port " << ::as_string(paddress2->get_service_number()) << ", " << networking_last_error() << ", " << bsd_socket_error(networking_last_error()));
         
         close_socket(s);

         return -1;

      }

      if (listen(s, depth) == -1)
      {

         FATAL("listen" << networking_last_error() << ", " << bsd_socket_error(networking_last_error()));

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
   i32 listen_socket::GetDepth()
   {
      return m_depth;
   }

   void listen_socket::set_should_detach(bool bSet)
   {

      m_bDetach = bSet;

   }


   bool listen_socket::should_detach() const
   {

      return m_bDetach;

   }


   /** OnRead on a listen_socket receives an incoming connection. */
   void listen_socket::OnRead()
   {

      auto socketid = GetSocketId();

      struct sockaddr sockaddr{};

      socklen_t sockaddr_len = sizeof(sockaddr);

      SOCKET socketAccept = accept(socketid, &sockaddr, &sockaddr_len);

      if (socketAccept == INVALID_SOCKET)
      {

         ERROR("accept" << networking_last_error() << bsd_socket_error(networking_last_error()));

         return;

      }

      if (!__Handler(m_psockethandler)->OkToAccept(this))
      {

         WARNING("accept: -1 Not OK to accept");

         close_socket(socketAccept);

         return;

      }

      if (socket_handler()->get_count() >= FD_SETSIZE)
      {

         FATAL("accept " << (i32)socket_handler()->get_count() << " base_socket_handler fd_set limit reached");

         close_socket(socketAccept);

         return;

      }

      auto tmp1 = ::move(create_listen_socket());

      tmp1->initialize(this);

      auto tmp = __Socket(tmp1);

      tmp->set_start_time();

      auto psystem = acmesystem()->m_papexsystem;

      auto pnetworking2 = __SystemNetworking(psystem);

      auto lId = pnetworking2->m_iListenSocket++;

      string strTopicText;

      if (sizeof(lId) == 4)
      {

         strTopicText.format("listensckt_%" PRId32 "> ", lId);

      }
      else
      {

         strTopicText.format("listensckt_%" PRId64 "> ", lId);

      }

      //tmp->set_topic_text(strTopicText);

      tmp->m_strCat = m_strCat;
      
      tmp->m_strCipherList = m_strCipherList;
      tmp -> EnableSSL(IsSSL()); // SSL Enabled socket
      tmp -> SetIpv6( IsIpv6() );
      tmp -> set_parent(this);
      tmp -> attach(socketAccept);
      tmp -> SetNonblocking(true);
      auto paddressRemote = __new(::networking_bsd::address);
      paddressRemote->set_address(sockaddr, sockaddr_len);
      //tmp->SetRemoteHostname(::networking::address(*psa));
      tmp->SetRemoteHostname(paddressRemote);
      tmp->m_iBindPort = m_iBindPort;
      tmp -> SetConnected(true);
      tmp -> Init();
      tmp -> SetDeleteByHandler(true);
      if (tmp -> IsSSL()) // SSL Enabled socket
      {
         // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
         // %! If that happens and negotiation fails, the 'tmp' instance is
         // %! still added to the list of active networking_bsd in the sockethandler.
         // %! See bugfix for this in socket_handler::Select - don't set rwx
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
      
      if (m_bDetach)
      {
         
         tmp->prepare_for_detach();

      }
//      auto passociation = m_psockethandler->new_association(tmp);

      //socket_handler()->move(passociation);

      __Handler(m_psockethandler)->move2(::move(tmp));

   }

   /** Please don't use this method.
   "accept()" is handled automatically in the OnRead() method. */
   SOCKET listen_socket::Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr)
   {
      return accept(socket, saptr, lenptr);
   }

   bool listen_socket:: HasCreator()
   {
      return false;
   }

   void listen_socket::OnOptions(i32,i32,i32,SOCKET)
   {
      SetSoReuseaddr(true);
   }


   //void listen_socket::initialize(::particle * pparticle)
   //{


   //}


   //::pointer<::sockets::socket>listen_socket::create_listen_socket()
   //{

   //   return nullptr;

   //}


} // namespace sockets_bsd



