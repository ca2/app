#include "framework.h"
#include "socket.h"


//#ifdef _WIN32
//#else
//#include <fcntl.h>
//#endif
//////#include <ctype.h>


//#if defined(LINUX) || defined(FREEBSD)
//#undef USE_MISC
//#include <unistd.h>
//#endif
//
//#if defined(__APPLE__) || defined(FREEBSD)
//#include <netdb.h>
//#endif

namespace sockets
{


   socket::socket() //:
      //::object(h),
      //base_socket(h)
   {

      //m_iBindPort    = -1;
      //m_timeStart.Now();
      //m_pcallback    = nullptr;

   }


   socket::~socket()
   {

      //if(&socket_handler() != nullptr)
      //{
      //   socket_handler()->erase(this);
      //}

      //if (m_socket != INVALID_SOCKET            && !m_bRetain         )
      //{
      //   close();
      //}

   }


   //void socket::initialize_socket(base_socket_handler* phandler)
   //{




   //}


   //i32 socket::close_socket(socket_id s)
   //{

   //   return ::closesocket(s);

   //}


   void socket::close()
   {

      //if (m_socket == INVALID_SOCKET) // this could happen
      //{

      //   if(!is_null(socket_handler()))
      //   {

      //      WARNING("socket::close: file descriptor invalid");

      //   }

      //   return;

      //}

      //i32 n;

      //if ((n = close_socket(m_socket)) == -1)
      //{

      //   if(!is_null(socket_handler()))
      //   {

      //      // failed...
      //      ERROR("close" << Errno << ", " << bsd_socket_error(Errno));

      //   }

      //}

      ////if(::is_set(m_phandlerSlave))
      ////{

      ////   m_phandlerSlave->erase_socket(m_socket);

      ////}

      //if (::is_set(m_psockethandler))
      //{

      //   m_psockethandler->erase_socket(m_socket);

      //}

      //m_socket = INVALID_SOCKET;
      
   }


//   socket_id socket::CreateSocket(i32 af, i32 iType, const ::string & strProtocol)
//   {
//
//      socket_id s;
//
//      m_iSocketType = iType;
//
//      m_strSocketProtocol = strProtocol;
//
//      i32 protno;
//
//#ifdef ANDROID
//
//      protno = 6;
//
//      if (strProtocol.case_insensitive_order("tcp") == 0)
//      {
//
//         protno = 6;
//
//      }
//
//#else
//
//      protno = IPPROTO_TCP;
//
//      {
//
//         struct protoent * pprotoent = nullptr;
//
//         if (strProtocol.length())
//         {
//
//            pprotoent = getprotobyname(strProtocol);
//
//            if (pprotoent == nullptr)
//            {
//
//               FATAL("getprotobyname" << Errno << ", " << bsd_socket_error(Errno));
//
//               SetCloseAndDelete();
//
//               throw ::exception(error_socket, string("getprotobyname() failed: ") + bsd_socket_error(Errno));
//
//               return INVALID_SOCKET;
//
//            }
//
//         }
//
//         if (pprotoent != nullptr)
//         {
//
//            protno = pprotoent->p_proto;
//
//         }
//
//      }
//
//#endif
//
//      s = ::socket(af, iType, protno);
//
//      if (s == INVALID_SOCKET)
//      {
//
//         FATAL("socket" << Errno << ", " << bsd_socket_error(Errno));
//
//         SetCloseAndDelete();
//         throw ::exception(error_socket, string("socket() failed: ") + bsd_socket_error(Errno));
//         return INVALID_SOCKET;
//      }
//      attach(s);
//      OnOptions(af, iType, protno, s);
//      attach(INVALID_SOCKET);
//      return s;
//   }


   void socket::set(bool bRead, bool bWrite, bool bException)
   {
      //socket_handler()->set(m_socket, bRead, bWrite, bException);
   }


   bool socket::Ready()
   {
      return false;      //if (m_socket != INVALID_SOCKET && !IsCloseAndDelete())
      //   return true;

   }

   bool socket::is_ok()
   {

      return Ready();

   }


//   bool socket::SetNonblocking(bool bNb, socket_id s)
//   {
//#ifdef _WIN32
//      u_long l = bNb ? 1 : 0;
//      i32 n = ioctlsocket(s, FIONBIO, &l);
//      if (n != 0)
//      {
//
//         INFORMATION("ioctlsocket(FIONBIO) " << Errno);
//
//         return false;
//      }
//      return true;
//#else
//      if (bNb)
//      {
//         if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
//         {
//
//            ERROR("fcntl(F_SETFL, O_NONBLOCK)" << Errno << ", " << bsd_socket_error(Errno));
//
//            return false;
//         }
//      }
//      else
//      {
//         if (fcntl(s, F_SETFL, 0) == -1)
//         {
//
//            ERROR("fcntl(F_SETFL, 0)" << Errno << ", " << bsd_socket_error(Errno));
//
//            return false;
//         }
//      }
//      return true;
//#endif
//   }


   ::networking::address_pointer socket::get_peer_address() // const
   {
      //ASSERT(psa != nullptr);
      //ASSERT(m_hSocket != INVALID_SOCKET);

      //// gets the address of the socket at the other end
      //::networking::address psa;
      //socklen_t nLengthAddr = sizeof(SOCKADDR);
      //if (getpeername(get_socket_id(), psa.sa(), &nLengthAddr) == SOCKET_ERROR)
      //{
      //   
      //   throw transfer_socket_exception("GetPeerName");

      //}

      //return psa;

      return {};

   }


   ::networking::address_pointer socket::get_socket_address() // const
   {
      //ASSERT(psa != nullptr);
      //ASSERT(m_hSocket != INVALID_SOCKET);

      // gets the address of the socket at this end
      //::networking::address psa;
      //socklen_t nLengthAddr = sizeof(SOCKADDR);
      //if (getsockname(get_socket_id(), psa.sa(), &nLengthAddr) == SOCKET_ERROR)
      //{
      //   
      //   throw transfer_socket_exception("GetSockName");

      //}

      //return psa;
      return {};

   }


} // namespace sockets




