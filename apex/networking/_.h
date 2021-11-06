#pragma once


#ifdef WINDOWS

using port_t = u16;

#endif

namespace net
{


   class address;


} // namespace net


inline void __exchange(::stream & s, ::net::address & address);


CLASS_DECL_APEX u32 c_inet_addr(const char * src);
CLASS_DECL_APEX i32 c_inet_pton(i32 af, const char * src, void * dst);
CLASS_DECL_APEX const char * c_inet_ntop(i32 af, const void * src, char * dst, i32 cnt);
CLASS_DECL_APEX string c_inet_ntop(i32 af, const void * src);



CLASS_DECL_APEX string c_gethostbyname(const char * hostname);

CLASS_DECL_APEX string get_file_extension_mime_type(const ::string & strExtension);


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
//#include "url_domain.h"


#include "email_address.h"
#include "email.h"


#include "port_forward.h"


//#include "url.h"
//#include "url_department.h"
//#include "email_department.h"




