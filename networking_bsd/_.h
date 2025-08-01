// https://avatars.githubusercontent.com/u/5128963?v=4
#pragma once

//#error "test"


#include "apex/_.h"


#if defined(_networking_bsd_project)
#define CLASS_DECL_NETWORKING_BSD  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NETWORKING_BSD  CLASS_DECL_IMPORT
#endif


#define BSD_STYLE_SOCKETS 1
#define HAVE_OPENSSL 1


#include "_operating_system.h"


//CLASS_DECL_NETWORKING_BSD const_char_pointer bsd_socket_error(int x);



#ifdef HAVE_OPENSSL
//#ifdef FREEBSD
//#define OPENSSL_API_COMPAT 101000
//#enddif
#define index bsd_index
#include <openssl/opensslv.h>
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
//#include <openssl/engine.h>
#include <openssl/conf.h>


#include <openssl/conf.h>
#include <openssl/ssl.h>
#include <openssl/safestack.h>
#include <openssl/x509v3.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/evp.h>
//#if OPENSSL_VERSION_NUMBER < 0x10101000L  || defined(LIBRESSL_VERSION_NUMBER)
//#include <openssl/whrlpool.h>
//#endif
#undef index
#endif


#include "_constant.h"


//#include "_net.h"



CLASS_DECL_NETWORKING_BSD int_bool to(in6_addr & addr,const ::scoped_string & scopedstr);
CLASS_DECL_NETWORKING_BSD ::string as_string(const in6_addr & addr);
CLASS_DECL_NETWORKING_BSD int_bool to(in_addr & addr,const ::scoped_string & scopedstr);
CLASS_DECL_NETWORKING_BSD ::string as_string(const in_addr & addr);
CLASS_DECL_NETWORKING_BSD ::string as_string(const sockaddr_in &  addr);
CLASS_DECL_NETWORKING_BSD ::string as_string(const sockaddr_in6 &  addr);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_NETWORKING_BSD ::string as_string(const sockaddr & addr);
#endif


CLASS_DECL_NETWORKING_BSD [[nodiscard]] ::e_status from_string(in6_addr& addr, const ::ansi_character* psz);
CLASS_DECL_NETWORKING_BSD ::string as_string(const in6_addr & addr);
CLASS_DECL_NETWORKING_BSD [[nodiscard]] ::e_status from_string(in_addr & addr, const_char_pointer psz);
CLASS_DECL_NETWORKING_BSD ::string as_string(const in_addr & addr);
CLASS_DECL_NETWORKING_BSD ::string as_string(const sockaddr_in & addr);
CLASS_DECL_NETWORKING_BSD ::string as_string(const sockaddr_in6 & addr);
//CLASS_DECL_NETWORKING_BSD void from_string(sockaddr_in & addr, const_char_pointer psz);
//CLASS_DECL_NETWORKING_BSD void from_string(sockaddr_in6 & addr, const_char_pointer psz);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_NETWORKING_BSD ::string as_string(const sockaddr & addr);
//CLASS_DECL_NETWORKING_BSD void from_string(sockaddr & addr, ::ansi_character * psz);
#endif


CLASS_DECL_NETWORKING_BSD string c_gethostbyname(const_char_pointer hostname);





namespace networking_bsd
{


   class address;



   CLASS_DECL_NETWORKING_BSD int family_len(int family);


} // namespace networking_bsd


//#define __Address(paddress) \
//   ((::networking_bsd::address *)((paddress)->m_p2))
//
//#define __Socket(psocket) \
//   ((::sockets_bsd::base_socket *)((psocket)->m_p2))
//
//#define __Handler(phandler) \
//   ((::sockets_bsd::socket_handler *)((phandler)->m_p2))
//
#define __SystemNetworking(psystem) \
   ((::networking_bsd::networking *)((psystem)->networking()))


CLASS_DECL_NETWORKING_BSD int networking_last_error();


//inline void __exchange(::binary_stream & s, ::networking::address & address);


//CLASS_DECL_NETWORKING_BSD unsigned int c_inet_addr(const_char_pointer src);
//CLASS_DECL_NETWORKING_BSD int c_inet_pton(int af, const_char_pointer src, void * dst);
//CLASS_DECL_NETWORKING_BSD const_char_pointer c_inet_ntop(int af, const void * src, char * dst, int cnt);
//CLASS_DECL_NETWORKING_BSD string c_inet_ntop(int af, const void * src);



CLASS_DECL_NETWORKING_BSD string c_gethostbyname(const_char_pointer hostname);


#include "_byte_order.h"


namespace net
{


   class email;
   class port_forward;
   typedef ::pointer<port_forward>port_forward_pointer;



} // namespace net


#include "sockets/_.h"



