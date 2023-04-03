// Created by camilo on 2022-08-28 00:04 <3ThomasBorregaardSørensen!!
#pragma once


#if defined(__APPLE__) || defined(FREEBSD)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

#endif


// namespace str
// {


CLASS_DECL_APEX ::string as_string(const struct sockaddr & sockaddr);


// } // namespace str


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


namespace sockets
{


   class ssl_context;


} // namespace sockets


/* Ipv6 support. */
#define ENABLE_IPV6





/* SCTP support. */
//#define USE_SCTP


/* Define NO_GETADDRINFO if your operating system does not support
the "getaddrinfo" and "getnameinfo" function calls. */
//#define NO_GETADDRINFO




/* Socks4 client support. */
//#define ENABLE_SOCKS4




/* enable TCP reconnect on lost connection.
socket::OnReconnect
socket::OnDisconnect
*/
#define ENABLE_RECONNECT




/* enable socket to socket triggers. Not yet in use. */
//#define ENABLE_TRIGGERS


/* Enabled exceptions. */
#define ENABLE_EXCEPTIONS







// common defines affecting library and applications using library

/* Define SOCKETS_DYNAMIC_TEMP to use dynamically allocated buffers
in read operations - helps on ECOS */
#define SOCKETS_DYNAMIC_TEMP

////#include <openssl/ssl.h>
//#include "ssl/initializer.h"

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
// because some psystem's will already have one or more of the type defined.
typedef i32 socket_id;
//#define Errno errno
//#define bsd_socket_error strerror

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
typedef u16 ::networking::port_t;
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
typedef   in_::networking::port_t ::networking::port_t;
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

#elif defined __APPLE__
// ----------------------------------------
// Mac App X
#ifdef __DARWIN_UNIX03
typedef u16 ::networking::port_t;
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
CLASS_DECL_APEX const char * bsd_socket_error(i32 x);


#elif defined(UNIVERSAL_WINDOWS)

CLASS_DECL_APEX const char * bsd_socket_error(i32 x);

#define Errno get_last_error()

#else


typedef u32 ipaddr_t;
typedef u16 ::networking::port_t;


#endif



// getaddrinfo / getnameinfo replacements
#ifdef NO_GETADDRINFO
#ifndef AI_NUMERICHOST
#define AI_NUMERICHOST 1
#endif
#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1
#endif
#endif


//namespace sockets
//{
//
//
//   class socket_thread;
//
//   class base_socket_handler;
//
//   class base_socket;
//
//   using socket_pointer = ::pointer<base_socket>
//
//   class socket_handler;
//
//   __declare_map(socket_flag_map, socket_flag, base_socket*, m_pbasesocket, bool, m_bFlag);
//   __declare_map(socket_socket_flag_map, socket_socket_flag, socket_id, m_socket, socket_flag_map, m_pmap);
//   __declare_map(socket_map, socket_pointer_pair, socket_id, m_socket, socket_pointer, m_psocket);
//
//
//} // namespace sockets

//
//
//#include "ssl/client_context.h"
//#include "ssl/client_context_map.h"
//#include "apex/networking/address.h"
//#include "apex/networking/sockets/base/base_socket.h"
//#include "apex/networking/sockets/base/socket_thread.h"
//#include "apex/networking/sockets/bsd/ssl/context.h"
//#include "basic/socket.h"
//#include "apex/networking/sockets/base/base_socket_handler.h"
//#include "basic/stream_socket.h"
//#include "basic/sctp_socket.h"
//#include "ssl/ticket_key.h"
//#include "basic/tcp_socket.h"
//#include "basic/udp_socket.h"
//
//#include "basic/tls_socket.h"
//
//
//#include "apex/networking/sockets/base/base_socket_handler.h"
//#include "basic/socket_handler.h"
//#include "basic/listen_socket.h"
//
//
//#include "apex/networking/sockets/http/_.h"
//
//
////#include "webserver/ajp_base_socket.h"
////#include "webserver/ajp13_socket.h"
////#include "webserver/ajp13.h"
//#include "apex/networking/sockets/http/socket.h"
////#include "webserver/http_base_socket.h"
//#include "webserver/httpd_socket.h"
//
////#include "sip/sip_base.h"
////
////#include "sip/sip_transaction.h"
////#include "sip/sip_request.h"
////#include "sip/sip_response.h"
////
////#include "sip/sip_base_client_socket.h"
////#include "sip/sip_tcp_client_socket.h"
////#include "sip/sip_udp_client_socket.h"
////#include "sip/sip_client.h"
////#include "sip/sip_server.h"
//
//
////#include "smtp/smtp_socket.h"
////#include "smtp/smtpd_socket.h"
//
////#include "timer/event_time.h"
////#include "timer/_.h"
//
////#include "timer/ievent_handler.h"
////#include "timer/ievent_owner.h"
////#include "timer/event_handler.h"
//
//#include "dns/resolv_socket.h"
//#include "dns/resolv_server.h"
//
//
//#include "basic/sync_socket_handler.h"
//
//
//#include "apex/networking/sockets/link_out_socket.h"
//#include "apex/networking/sockets/link_in_socket.h"
//
//
//#include "basic/net.h"
//
//
//
//#include "sockets.h"
//
//
//


namespace sockets
{
   
   class net;
   
   ///* type, host, result */
   //typedef string_map < ::string_to_string >       resolv_cache_t;

   ///* type, host, time */
   //typedef string_map < string_map < time_t > >    resolv_timeout_t;



   class socket_thread;

   class base_socket_handler;

   class base_socket;

   using socket_pointer = ::pointer<base_socket>

   class socket_handler;

   __declare_map(socket_flag_map, socket_flag, base_socket *, m_pbasesocket, bool, m_bFlag);
   __declare_map(socket_socket_flag_map, socket_socket_flag, socket_id, m_socket, socket_flag_map, m_pmap);
   __declare_map(socket_map, socket_pointer_pair, socket_id, m_socket, socket_pointer, m_psocket);


} // namespace sockets



#include "ssl/_.h"




