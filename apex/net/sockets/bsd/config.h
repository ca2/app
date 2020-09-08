//#include "config.h"

#pragma once

#ifndef _RUN_DP
/* First undefine symbols if already defined. */
#undef ENABLE_IPV6
#undef USE_SCTP
#undef NO_GETADDRINFO
#undef ENABLE_SOCKS4
#undef ENABLE_RECONNECT
#undef ENABLE_TRIGGERS
#undef ENABLE_EXCEPTIONS
#endif // _RUN_DP




/* Ipv6 support. */
#define ENABLE_IPV6


/* SCTP support. */
//#define USE_SCTP


/* Define NO_GETADDRINFO if your operating system does not support
the "getaddrinfo" and "getnameinfo" function calls. */
//#define NO_GETADDRINFO




/* Socks4 client support. */
//#define ENABLE_SOCKS4




/* Enable TCP reconnect on lost connection.
socket::OnReconnect
socket::OnDisconnect
*/
#define ENABLE_RECONNECT




/* Enable socket to socket triggers. Not yet in use. */
//#define ENABLE_TRIGGERS


/* Enabled exceptions. */
#define ENABLE_EXCEPTIONS







// common defines affecting library and applications using library

/* Define SOCKETS_DYNAMIC_TEMP to use dynamically allocated buffers
in read operations - helps on ECOS */
#define SOCKETS_DYNAMIC_TEMP

//#include <openssl/ssl.h>
#include "internal/SSLInitializer.h"

/*
// platform specific stuff
#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/lparam.h>
#endif

// i64
#ifdef _WIN32
#else
#ifdef SOLARIS
#else
# include "_stdint.h"
#endif
#endif

*/

#ifndef _WIN32

// all typedefs in this file will be declared outside the sockets namespace,
// because some System's will already have one or more of the type defined.
typedef i32 SOCKET;
#define Errno errno
#define bsd_socket_error strerror

#ifdef sockets
namespace sockets
{
#endif


   // WIN32 adapt
#define closesocket close
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#ifndef INADDR_NONE
#define INADDR_NONE ((unsigned long) -1)
#endif // INADDR_NONE

#ifdef sockets
}
#endif

#endif // !_WIN32


// ----------------------------------------
// Generic
#ifndef SOL_IP
#define SOL_IP IPPROTO_IP
#endif


// ----------------------------------------
// App specific adaptions

#ifdef SOLARIS
// ----------------------------------------
// Solaris
typedef u16 port_t;
#ifdef sockets
namespace sockets
{
#endif
   // no defs

#ifdef sockets
}
#endif

#define s6_addr16 _S6_un._S6_u8
#define MESSAGE_NOSIGNAL 0

#elif defined __FreeBSD__
// ----------------------------------------
// FreeBSD
# if __FreeBSD_version >= 400014
#  define s6_addr16 __u6_addr.__u6_addr16
#  if !defined(MESSAGE_NOSIGNAL)
#   define MESSAGE_NOSIGNAL 0
#  endif
typedef   in_addr_t ipaddr_t;
typedef   in_port_t port_t;
#ifdef sockets
namespace sockets
{
#endif
   // no defs

#ifdef sockets
}
#endif

#  define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#  define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP
# else
#  error FreeBSD versions prior to 400014 does not support ipv6
# endif

#elif defined APPLEOS
// ----------------------------------------
// Mac App X
#ifdef __DARWIN_UNIX03
typedef u16 port_t;
#else
#include <mach/port.h>
#endif // __DARWIN_UNIX03
#ifdef sockets
namespace sockets
{
#endif
   // no defs

#ifdef sockets
}
#endif

#define s6_addr16 __u6_addr.__u6_addr16
#define MESSAGE_NOSIGNAL 0 // oops - thanks Derek
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP

//#elif defined(WINDOWS_DESKTOP)
#elif defined(WINDOWS)





#define MSG_NOSIGNAL 0
//#define SHUT_RDWR 2
#define SHUT_WR 1

#define Errno WSAGetLastError()
CLASS_DECL_APEX string bsd_socket_error(i32 x);

//namespace sockets
//{
//
//   // class WSAInitializer is a part of the socket class (on win32)
//   // as a static instance - so whenever an application uses a socket,
//   // winsock is initialized
//   class WSAInitializer // Winsock Initializer
//   {
//   public:
//
//      WSADATA m_wsadata;
//
//      WSAInitializer()
//      {
//         if (WSAStartup(0x101,&m_wsadata))
//         {
//            exit(-1);
//         }
//      }
//      ~WSAInitializer() {
//         WSACleanup();
//      }
//   };
//
//} // namespace sockets

#elif defined(_UWP)

CLASS_DECL_APEX const char *bsd_socket_error(i32 x);
#define Errno get_last_error()


#else


// ----------------------------------------
// LINUX
typedef u32 ipaddr_t;
typedef u16 port_t;

namespace sockets
{
   // no defs

} // namespace sockets

#endif


#include "sockets_socket_id_list.h"


// getaddrinfo / getnameinfo replacements
#ifdef NO_GETADDRINFO
#ifndef AI_NUMERICHOST
#define AI_NUMERICHOST 1
#endif
#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1
#endif
#endif

