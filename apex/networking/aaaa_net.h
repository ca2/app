#pragma once

#if defined(LINUX) || defined(__APPLE__)

#include <netinet/in.h>

#if defined(__APPLE__)

typedef in6_addr in_addr6;

#endif

#endif


//namespace str
//{


CLASS_DECL_APEX int_bool to(in6_addr & addr,const ::scoped_string & scopedstr);
CLASS_DECL_APEX ::string as_string(const in6_addr & addr);
CLASS_DECL_APEX int_bool to(in_addr & addr,const ::scoped_string & scopedstr);
CLASS_DECL_APEX ::string as_string(const in_addr & addr);
CLASS_DECL_APEX ::string as_string(const sockaddr_in &  addr);
CLASS_DECL_APEX ::string as_string(const sockaddr_in6 &  addr);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_APEX ::string as_string(const sockaddr & addr);
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


CLASS_DECL_APEX unsigned int c_inet_addr(const char *src);
CLASS_DECL_APEX int c_inet_pton(int af,const char *src,void *dst);
CLASS_DECL_APEX const char * c_inet_ntop(int af,const void *src,char *dst,int cnt);
CLASS_DECL_APEX string c_inet_ntop(int af,const void *src);



CLASS_DECL_APEX string c_gethostbyname(const char * hostname);

CLASS_DECL_APEX string get_file_extension_mime_type(const ::scoped_string & scopedstrExtension);


#include "byte_order.h"


