#pragma once

#if defined(LINUX) || defined(__APPLE__)

#include <netinet/in.h>

#if defined(__APPLE__)

typedef in6_addr in_addr6;

#endif

#endif


//namespace str
//{


CLASS_DECL_APEX int_bool to(in6_addr & addr,const ::string & str);
CLASS_DECL_APEX void to_string(string & str, const in6_addr & addr);
CLASS_DECL_APEX int_bool to(in_addr & addr,const ::string & str);
CLASS_DECL_APEX void to_string(string & str, const in_addr & addr);
CLASS_DECL_APEX void to_string(string & str, const sockaddr_in &  addr);
CLASS_DECL_APEX void to_string(string & str, const sockaddr_in6 &  addr);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_APEX void to_string(string & str, const sockaddr & addr);
#endif

//
//} // namespace str


inline stream & operator <<(stream & s, const ::in6_addr & addr)
{

   string str;

   to_string(str, addr);

   s << str;

   return s;

}



inline stream & operator >>(stream & s, ::in6_addr & addr)
{

   string str;

   s >> str;

   from_string(addr, str);

   return s;

}



inline stream & operator <<(stream & s, const ::in_addr & addr)
{

   string str;

   to_string(str, addr);

   s << str;

   return s;

}



inline stream & operator >>(stream & s, ::in_addr & addr)
{

   string str;

   s >> str;

   from_string(addr, str);

   return s;

}


CLASS_DECL_APEX u32 c_inet_addr(const char *src);
CLASS_DECL_APEX i32 c_inet_pton(i32 af,const char *src,void *dst);
CLASS_DECL_APEX const char * c_inet_ntop(i32 af,const void *src,char *dst,i32 cnt);
CLASS_DECL_APEX string c_inet_ntop(i32 af,const void *src);



CLASS_DECL_APEX string c_gethostbyname(const char * hostname);

CLASS_DECL_APEX string get_file_extension_mime_type(const ::string & strExtension);


#include "byte_order.h"


