#include "framework.h"
#include "listen_socket_impl.h"
#include "socket_handler.h"
////#include "acme/exception/exception.h"
#include "apex/platform/system.h"
#include "networking_bsd/address.h"
#include "networking_bsd/networking.h"
#include "acme/operating_system/networking.h"

#undef ERROR
#define log_error(...) TRACE_LOG_ERROR(__VA_ARGS__)


#if defined(OPENBSD)

#include <signal.h>

#include <libunwind.h>

#include <cxxabi.h>
#include <cstring>

// Demangle C++ symbols using __cxa_demangle
void demangle_and_print(const_char_pointer mangled_name) {
    int status = 0;
    char *demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    
    if (status == 0) {
        // Successful demangling
        fprintf(stderr, "%s\n", demangled_name);
    } else {
        // If demangling fails, print the mangled name
        fprintf(stderr, "Failed to demangle: %s\n", mangled_name);
    }
    
    // Free the allocated memory for the demangled name
    free(demangled_name);
}

// Print a backtrace using libunwind
void print_backtrace() {
    unw_cursor_t cursor;
    unw_context_t context;

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    fprintf(stderr, "Backtrace:\n");

    while (unw_step(&cursor) > 0) {
        char func_name[256];
        unw_word_t offset, pc;

        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        if (unw_get_proc_name(&cursor, func_name, sizeof(func_name), &offset) == 0) {
            fprintf(stderr, "  0x%lx: ", (long)pc);
            demangle_and_print(func_name);  // Demangle the function name
        } else {
            fprintf(stderr, "  0x%lx: [unknown]\n", (long)pc);
        }
    }
}

#endif

namespace sockets_bsd
{

#if defined(OPENBSD)

   // Signal handler function
   void handle_sigpipe(int signum) 
   {
      
      fprintf(stderr, "Caught SIGPIPE (signal %d)\n", signum);
      
      ::print_backtrace();

   }
   
#endif


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


   void listen_socket_impl::destroy()
   {

      ::sockets_bsd::socket::destroy();

      ::sockets::listen_socket_impl::destroy();

   }


   void listen_socket_impl::set_ssl_catalog(const ::scoped_string & scopedstrCat)
   {

      m_strCat = scopedstrCat;

   }


   void listen_socket_impl::set_ssl_cipher_list(const ::scoped_string & scopedstrCipherList)
   {

      m_strCipherList = scopedstrCipherList;

   }


   /** close file descriptor. */
   void listen_socket_impl::close()
   {

      if (GetSocketId() != INVALID_SOCKET)
      {

         close_socket((int) GetSocketId());

      }

   }

   /** Bind and listen to any interface.
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   int listen_socket_impl::Bind(::networking::port_t port,int depth)
   {
      if (IsIpv6())
      {
         auto paddress = øallocate ::networking_bsd::address();
         paddress->set_family(AF_INET6, port);
         //::networking::address ad(AF_INET6, port);
         return Bind(paddress.m_p, depth);
      }
      else
      {
         auto paddress = øallocate ::networking_bsd::address();
         paddress->set_family(AF_INET, port);
         return Bind(paddress.m_p, depth);
      }
   }

   int listen_socket_impl::Bind(::networking::address * ad,int depth)
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
   int listen_socket_impl::Bind(::networking::port_t port,const string & protocol,int depth)
   {
      if (IsIpv6())
      {
         auto paddress = øallocate ::networking_bsd::address();
         paddress->set_family(AF_INET6, port);
         return Bind(paddress->u.m_addr6.sin6_addr, port, protocol, depth);
      }
      else
      {
         auto paddress = øallocate ::networking_bsd::address();
         paddress->set_family(AF_INET, port);
         return Bind(paddress->u.m_addr.sin_addr, port, protocol, depth);
      }
   }

   /** Bind and listen to specific interface.
   \lparam intf Interface hostname
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   int listen_socket_impl::Bind(const ::scoped_string & scopedstrInterface,::networking::port_t port,int depth)
   {
      
      auto paddress = __SystemNetworking(system())->create_address(scopedstrInterface, preferred_address_type(), port);

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
   int listen_socket_impl::Bind(const ::scoped_string & scopedstrInterface,::networking::port_t port,const string & protocol,int depth)
   {

      auto paddress = __SystemNetworking(system())->create_address(scopedstrInterface, preferred_address_type(), port);

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
   int listen_socket_impl::Bind(in_addr a,::networking::port_t port,int depth)
   {

      auto paddress = øallocate ::networking_bsd::address();

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
   int listen_socket_impl::Bind(in_addr a,::networking::port_t port,const string & protocol,int depth)
   {

      auto paddress = øallocate ::networking_bsd::address();

      paddress->set_address(a, port);

      return Bind(paddress.m_p, protocol, depth);

   }

   /** Bind and listen to ipv6 interface.
   \lparam a Ipv6 interface address
   \lparam port Port (0 is random)
   \lparam depth Listen queue depth */
   int listen_socket_impl::Bind(in6_addr a,::networking::port_t port,int depth)
   {

      auto paddress = øallocate ::networking_bsd::address();

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
   int listen_socket_impl::Bind(in6_addr a,::networking::port_t port,const string & protocol,int depth)
   {

      auto paddress = øallocate ::networking_bsd::address();

      paddress->set_address(a, port);

      return Bind(paddress.m_p, protocol, depth);

   }


   /** Bind and listen to network interface.
   \lparam ad Interface address
   \lparam protocol Network protocol
   \lparam depth Listen queue depth */
   int listen_socket_impl::Bind(::networking::address * paddress,const string & protocol,int depth)
   {
      
#if defined(OPENBSD)
      
  //    if (signal(SIGPIPE, handle_sigpipe) == SIG_ERR) 
//      {
      
    //    return 1;
        
      //}
      
#endif

      ::pointer < ::networking_bsd::address > paddress2 = paddress;

      SOCKET s{};
      
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
      
      ::string strAddress;
      
      ::cast < ::networking_bsd::networking > pbsdnetworking = networking();
     
      pbsdnetworking->convert(strAddress, ((sockaddr_in*)psockaddr)->sin_addr);
      
      information() << "bind() succeeded for address "
                    << strAddress
                    << " and port "
                    << ::as_string(paddress2->get_service_number())
                    << " with socket "
                    << s;

      if (::listen(s, depth) != 0)
      {

         fatal() <<"listen" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         close_socket(s);

         throw ::exception(error_socket, "listen() failed for port " + ::as_string(paddress2->get_service_number()) + ": " + bsd_socket_error(networking_last_error()));

         return -1;

      }

      information() << "listen() succeeded with depth "
                    << depth
                    << " for socket "
                    << s 
                    << " at thread "
                    << ::task_get_name()
                    << "(" << ::current_task_index() << ")";

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
   int listen_socket_impl::GetDepth()
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

      SOCKET socketAccept = _accept_socket(socketid, &sockaddr.c, &sockaddr_len);

      if (socketAccept == INVALID_SOCKET)
      {

         error() <<"accept" << networking_last_error() << bsd_socket_error(networking_last_error());

         return;

      }
      
      printf_line("listen_socket_impl::OnRead accept succeeded");

      ::pointer < ::sockets_bsd::socket_handler> phandler = m_psockethandler;

      if (!phandler->OkToAccept(this))
      {

         warning() <<"accept: -1 Not OK to accept";

         close_socket(socketAccept);

         return;

      }

      if (socket_handler()->get_count() >= FD_SETSIZE)
      {

         fatal() <<"accept " << (int)socket_handler()->get_count() << " base_socket_handler fd_set limit reached";

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
      printf_line("listen_socket_impl::OnRead 1");
      psocketImpl-> set_parent_socket(this);
      printf_line("listen_socket_impl::OnRead 2");
      psocketImpl-> attach(socketAccept);
      printf_line("listen_socket_impl::OnRead 3");
      psocketImpl->OnOptions(m_iFamily, m_iSocketType, m_iProtocolType, socketAccept);
      printf_line("listen_socket_impl::OnRead 4");
      //psocketImpl-> SetNonblocking(true);
      auto paddressRemote = øallocate ::networking_bsd::address();
      paddressRemote->set_address(sockaddr.c, sockaddr_len);
      printf_line("listen_socket_impl::OnRead 5");
      //tmp->SetRemoteHostname(::networking::address(*psa));
      psocketImpl->SetRemoteHostname(paddressRemote);
      printf_line("listen_socket_impl::OnRead 6");
      psocketImpl->m_iBindPort = m_iBindPort;
      printf_line("listen_socket_impl::OnRead 7");
      psocketImpl-> SetConnected(true);
      printf_line("listen_socket_impl::OnRead 8");
      psocketImpl-> Init();
      printf_line("listen_socket_impl::OnRead 9");
      psocketImpl-> SetDeleteByHandler(true);
      printf_line("listen_socket_impl::OnRead A");
      if (psocketImpl-> IsSSL()) // SSL Enabled socket
      {
         // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
         // %! If that happens and negotiation fails, the 'tmp' instance is
         // %! still added to the list_base of active networking_bsd in the sockethandler.
         // %! See bugfix for this in socket_handler::Select - don't set rwx
         // %! flags if IsCloseAndDelete() flag is true.
         // %! An even better fugbix (see tcp_socket::OnSSLAccept) now avoids
         // %! the add problem altogether, so ignore the above.
         // %! (OnSSLAccept does no longer call SSLNegotiate().)
         psocketImpl-> OnSSLAccept();
         printf_line("listen_socket_impl::OnRead B");
      }
      else
      {
         psocketImpl-> OnAccept();
         printf_line("listen_socket_impl::OnRead C");
      }
      
      if (m_plistensocketInterface->m_bListeningDetach)
      {
         
         psocketImpl->prepare_for_detach();
         printf_line("listen_socket_impl::OnRead D");
         
      }
      else
      {
         
         printf_line("listen_socket_impl::OnRead Exception... is it not detached?!?!");

         throw "Debug... is it not detached?!?!";

      }
//      auto passociation = m_psockethandler->new_association(tmp);

      //socket_handler()->transfer(passociation);

      m_psockethandler->add(psocketAttend);

   }

   /** Please don't use this method.
   "accept()" is handled automatically in the OnRead() method. */
#if defined(__ANDROID__) || defined(__BSD__) || defined(__APPLE__) || defined(LINUX)
   SOCKET listen_socket_impl::Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr)
#else
   SOCKET listen_socket_impl::Accept(SOCKET socket, struct sockaddr *saptr, int *lenptr)
#endif
   {
      return ::_accept_socket(socket, saptr, lenptr);
   }

   bool listen_socket_impl:: HasCreator()
   {
      return false;
   }

   void listen_socket_impl::OnOptions(int,int,int,SOCKET s)
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



