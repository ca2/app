#pragma once


#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

#include <netinet/in.h>

#if defined(APPLEOS)

typedef in6_addr in_addr6;

#endif

#endif


namespace net
{

   struct address;

} // namespace net


namespace str
{

   CLASS_DECL_AQUA void to(struct in6_addr & addr, const ansichar * psz);
   CLASS_DECL_AQUA void from(string & str, const in6_addr & addr);
   CLASS_DECL_AQUA void to(struct in_addr & addr, const ansichar * psz);
   CLASS_DECL_AQUA void from(string & str, const in_addr & addr);
   CLASS_DECL_AQUA void from(string & str, const sockaddr_in & addr);
   CLASS_DECL_AQUA void from(string & str, const sockaddr_in6 & addr);
#ifdef BSD_STYLE_SOCKETS
   CLASS_DECL_AQUA void from(string & str, const sockaddr & addr);
#endif

} // namespace str


inline void __exchange(::stream & s, struct in6_addr & addr);

inline void __exchange(::stream & s, struct in_addr & addr);

inline void __exchange(::stream & s, ::net::address & address);


CLASS_DECL_AQUA u32 c_inet_addr(const char * src);
CLASS_DECL_AQUA i32 c_inet_pton(i32 af, const char * src, void * dst);
CLASS_DECL_AQUA const char * c_inet_ntop(i32 af, const void * src, char * dst, i32 cnt);
CLASS_DECL_AQUA string c_inet_ntop(i32 af, const void * src);



CLASS_DECL_AQUA string c_gethostbyname(const char * hostname);

CLASS_DECL_AQUA string get_file_extension_mime_type(const string & strExtension);


#include "byte_order.h"


namespace sockets
{


   class socket_handler;
   class http_client_socket;
   class http_session;


} // namespace sockets


#include "http/_.h"






namespace net
{


   class email;


} // namespace net



#include "ip_enum.h"
#include "url_domain.h"


#include "email_address.h"
#include "email.h"


#include "port_forward.h"


#include "url.h"
#include "url_department.h"
//#include "email_department.h"



