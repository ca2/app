#include "framework.h"
#include "apex/net/sockets/_.h"

#ifdef _WIN32
#else
#include <fcntl.h>
#endif
////#include <ctype.h>


#ifdef LINUX
#undef USE_MISC
#include <unistd.h>
#endif

#ifdef __APPLE__
#include <netdb.h>
#endif

namespace sockets
{


   socket::socket(base_socket_handler& h) :
      ::context_object(h),
      base_socket(h)
   {

      m_iBindPort    = -1;
      m_tickStart.Now();
      m_pcallback    = nullptr;

   }


   socket::~socket()
   {

      //if(&Handler() != nullptr)
      //{
      //   Handler().remove(this);
      //}

      if (m_socket != INVALID_SOCKET            && !m_bRetain         )
      {
         close();
      }

   }


   i32 socket::close_socket(SOCKET s)
   {

      return ::closesocket(s);

   }


   void socket::close()
   {

      if (m_socket == INVALID_SOCKET) // this could happen
      {

         if(!is_null_ref(Handler()))
         {

            WARN("socket::close", 0, "file descriptor invalid");

         }

         return;

      }

      i32 n;

      if ((n = close_socket(m_socket)) == -1)
      {

         if(!is_null_ref(Handler()))
         {

            // failed...
            ERR("close", Errno, bsd_socket_error(Errno));

         }

      }

      if(!is_null_ref(Handler()))
      {

         Handler().set(m_socket, false, false, false); // remove from fd_set's
         Handler().AddList(m_socket, LIST_CALLONCONNECT, false);
         Handler().AddList(m_socket, LIST_DETACH, false);
         Handler().AddList(m_socket, LIST_TIMEOUT, false);
         Handler().AddList(m_socket, LIST_RETRY, false);
         Handler().AddList(m_socket, LIST_CLOSE, false);

      }

      m_socket = INVALID_SOCKET;
      
   }


   SOCKET socket::CreateSocket(i32 af, i32 iType, const string & strProtocol)
   {

      SOCKET s;

      m_iSocketType = iType;

      m_strSocketProtocol = strProtocol;

      i32 protno;

#ifdef ANDROID

      protno = 6;

      if (strProtocol.compare_ci("tcp") == 0)
      {

         protno = 6;

      }

#else

      protno = IPPROTO_TCP;

      {

         struct protoent *point = nullptr;

         if (strProtocol.get_length())
         {

            point = getprotobyname(strProtocol);

            if (point == nullptr)
            {

               FATAL(log_this, "getprotobyname", Errno, bsd_socket_error(Errno));

               SetCloseAndDelete();

               __throw(::exception::exception(string("getprotobyname() failed: ") + bsd_socket_error(Errno)));

               return INVALID_SOCKET;

            }

         }

         if (point != nullptr)
         {

            protno = point->p_proto;

         }

      }

#endif

      s = ::socket(af, iType, protno);

      if (s == INVALID_SOCKET)
      {

         FATAL(log_this, "socket", Errno, bsd_socket_error(Errno));

         SetCloseAndDelete();
         __throw(::exception::exception(string("socket() failed: ") + bsd_socket_error(Errno)));
         return INVALID_SOCKET;
      }
      attach(s);
      OnOptions(af, iType, protno, s);
      attach(INVALID_SOCKET);
      return s;
   }





   void socket::set(bool bRead, bool bWrite, bool bException)
   {
      Handler().set(m_socket, bRead, bWrite, bException);
   }


   bool socket::Ready()
   {
      if (m_socket != INVALID_SOCKET && !IsCloseAndDelete())
         return true;
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
      i32 n = ioctlsocket(s, FIONBIO, &l);
      if (n != 0)
      {

         INFO(log_this, "ioctlsocket(FIONBIO)", Errno, "");

         return false;
      }
      return true;
#else
      if (bNb)
      {
         if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
         {

            ERR("fcntl(F_SETFL, O_NONBLOCK)", Errno, bsd_socket_error(Errno));

            return false;
         }
      }
      else
      {
         if (fcntl(s, F_SETFL, 0) == -1)
         {

            ERR("fcntl(F_SETFL, 0)", Errno, bsd_socket_error(Errno));

            return false;
         }
      }
      return true;
#endif
   }


   ::net::address socket::get_peer_address() // const
   {
      //ASSERT(psa != nullptr);
      //ASSERT(m_hSocket != INVALID_SOCKET);

      // gets the address of the socket at the other end
      ::net::address psa;
      socklen_t nLengthAddr = sizeof(SOCKADDR);
      if (getpeername(GetSocket(), psa.sa(), &nLengthAddr) == SOCKET_ERROR)
      {
         __throw(transfer_socket_exception("GetPeerName"));
      }
      return psa;
   }

   ::net::address socket::get_socket_address() // const
   {
      //ASSERT(psa != nullptr);
      //ASSERT(m_hSocket != INVALID_SOCKET);

      // gets the address of the socket at this end
      ::net::address psa;
      socklen_t nLengthAddr = sizeof(SOCKADDR);
      if (getsockname(GetSocket(), psa.sa(), &nLengthAddr) == SOCKET_ERROR)
      {
         __throw(transfer_socket_exception("GetSockName"));
      }
      return psa;
   }

} // namespace sockets





