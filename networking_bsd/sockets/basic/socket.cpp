#include "framework.h"
#include "socket.h"
#include "socket_handler.h"
////#include "acme/exception/exception.h"
#include "networking_bsd/address.h"
#include "networking_bsd/sockets/transfer_socket.h"


#ifdef _WIN32
#else
#include <fcntl.h>
#endif
////#include <ctype.h>


#if defined(LINUX) || defined(__BSD__)
#undef USE_MISC
#include <unistd.h>
#endif

#if defined(__APPLE__) || defined(__BSD__)
#include <netdb.h>
#endif




#undef ERROR
#define log_error(...) TRACE_LOG_ERROR(__VA_ARGS__)


namespace sockets_bsd
{


   socket::socket() //:
      //::object(h),
      //base_socket(h)
   {

      m_iBindPort    = -1;
      m_timeStart.Now();
      //m_pcallback    = nullptr;
      
      m_iFamily = -1;
      m_iSocketType = -1;
      m_iProtocolType = -1;

   }


   socket::~socket()
   {

      //if(&socket_handler() != nullptr)
      //{
      //   socket_handler()->erase(this);
      //}

      if (m_socketid != INVALID_SOCKET            && !m_bRetain         )
      {
         close();
      }

   }


   //void socket::initialize_socket(base_socket_handler* phandler)
   //{




   //}


   int socket::close_socket(SOCKET s)
   {

      return ::closesocket(s);

   }


   void socket::close()
   {

      if (m_socketid == INVALID_SOCKET) // this could happen
      {

         if(!::is_null(socket_handler()))
         {

            warning() <<"socket::close: file descriptor invalid";

         }

         return;

      }

      int n;

      if ((n = close_socket(m_socketid)) == -1)
      {

         if(!::is_null(socket_handler()))
         {

            // failed...
            error() <<"close" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         }

      }

      //if(::is_set(m_phandlerSlave))
      //{

      //   m_phandlerSlave->erase_socket(m_socketid);

      //}

      if (::is_set(socket_handler()))
      {

         ::pointer < ::sockets_bsd::socket_handler > phandler = m_psockethandler;

         phandler->erase_socket(m_socketid);

      }

      m_socketid = INVALID_SOCKET;
      
   }


   SOCKET socket::CreateSocket(int af, int iType, const ::scoped_string & scopedstrProtocol)
   {

      SOCKET s;
      
      m_iFamily = af;

      m_iSocketType = iType;
      
      m_strSocketProtocol = scopedstrProtocol;

      int protno;

#ifdef __ANDROID__

      protno = 6;

      if (strProtocol.case_insensitive_order("tcp") == 0)
      {

         protno = 6;

      }

#else

      protno = IPPROTO_TCP;

      {

         struct protoent * pprotoent = nullptr;

         if (scopedstrProtocol.length())
         {

            pprotoent = getprotobyname(scopedstrProtocol);

            if (pprotoent == nullptr)
            {

               fatal() <<"getprotobyname" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

               SetCloseAndDelete();

               throw ::exception(error_socket, string("getprotobyname() failed: ") + bsd_socket_error(networking_last_error()));

               return INVALID_SOCKET;

            }

         }

         if (pprotoent != nullptr)
         {

            protno = pprotoent->p_proto;

         }

      }

#endif
      
      m_iProtocolType = protno;

#ifdef WINDOWS

      s = ::socket(af, iType, protno);

#elif defined(__APPLE__)
      
      s = ::socket(af, iType, protno);
      
      fcntl(s, O_CLOEXEC);

#else

      s = ::socket(af, iType | SOCK_CLOEXEC, protno);

#endif

      if (s == INVALID_SOCKET)
      {

         fatal() <<"socket" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

         SetCloseAndDelete();
         throw ::exception(error_socket, string("socket() failed: ") + bsd_socket_error(networking_last_error()));
         return INVALID_SOCKET;
      }
      //attach(s);
      OnOptions(af, iType, protno, s);
      //attach(INVALID_SOCKET);
      return s;
   }


   //void socket::set(bool bRead, bool bWrite, bool bException)
   //{

   //   ::pointer < ::sockets_bsd::socket_handler > phandler = m_psockethandler;
   //   
   //   phandler->set(m_socketid, bRead, bWrite, bException);

   //}


   bool socket::Ready()
   {

      if (m_socketid != INVALID_SOCKET && !IsCloseAndDelete())
      {

         return true;

      }

      return false;

   }


   bool socket::is_valid()
   {

      return Ready();

   }


   bool socket::SetNonblocking(bool bNb, SOCKET s)
   {
#ifdef _WIN32
      u_long l = bNb ? 1 : 0;
      int n = ioctlsocket(s, FIONBIO, &l);
      if (n != 0)
      {

         information() << "ioctlsocket(FIONBIO) " << networking_last_error();

         return false;
      }
      return true;
#else
      if (bNb)
      {
         if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
         {

            error() <<"fcntl(F_SETFL, O_NONBLOCK)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

            return false;
         }
      }
      else
      {
         if (fcntl(s, F_SETFL, 0) == -1)
         {

            error() <<"fcntl(F_SETFL, 0)" << networking_last_error() << ", " << bsd_socket_error(networking_last_error());

            return false;
         }
      }
      return true;
#endif
   }


   ::pointer<::networking::address>socket::get_peer_address() // const
   {
      //ASSERT(psa != nullptr);
      //ASSERT(m_hSocket != INVALID_SOCKET);

      // gets the address of the socket at the other end
      auto paddress = __allocate ::networking_bsd::address();
      socklen_t nLengthAddr = sizeof(sockaddr);
      if (getpeername(GetSocketId(), paddress->sa(), &nLengthAddr) == SOCKET_ERROR)
      {
         
         throw ::exception(error_socket, "GetPeerName");

      }

      return paddress;

   }


   ::pointer<::networking::address>socket::get_socket_address() // const
   {
      //ASSERT(psa != nullptr);
      //ASSERT(m_hSocket != INVALID_SOCKET);

      // gets the address of the socket at this end
      auto paddress = __allocate ::networking_bsd::address();
      socklen_t nLengthAddr = sizeof(sockaddr);
      if (getsockname(GetSocketId(), paddress->sa(), &nLengthAddr) == SOCKET_ERROR)
      {
         
         throw ::exception(error_socket, "GetSockName");

      }

      return paddress;

   }


} // namespace sockets_bsd




