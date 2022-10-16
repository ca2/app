#pragma once


#if defined(FREEBSD)


#include <sys/socket.h>


#endif


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)

#include <netinet/in.h>

#if defined(__APPLE__)

typedef in6_addr in_addr6;

#endif

#endif




#if defined(LINUX) || defined(__APPLE__)

#include <netinet/in.h>

#if defined(__APPLE__)

typedef in6_addr in_addr6;

#endif

#endif


//namespace str
//{


CLASS_DECL_NETWORKING_BSD int_bool to(in6_addr & addr,const ::string & str);
CLASS_DECL_NETWORKING_BSD ::string __string(const in6_addr & addr);
CLASS_DECL_NETWORKING_BSD int_bool to(in_addr & addr,const ::string & str);
CLASS_DECL_NETWORKING_BSD ::string __string(const in_addr & addr);
CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr_in &  addr);
CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr_in6 &  addr);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr & addr);
#endif

//
//} // namespace str




// namespace str
// {


CLASS_DECL_NETWORKING_BSD void from_string(in6_addr & addr, const ansichar * psz);
CLASS_DECL_NETWORKING_BSD ::string __string(const in6_addr & addr);
CLASS_DECL_NETWORKING_BSD void from_string(in_addr & addr, const ansichar * psz);
CLASS_DECL_NETWORKING_BSD ::string __string(const in_addr & addr);
CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr_in & addr);
CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr_in6 & addr);
//CLASS_DECL_NETWORKING_BSD void from_string(sockaddr_in & addr, const ansichar * psz);
//CLASS_DECL_NETWORKING_BSD void from_string(sockaddr_in6 & addr, const ansichar * psz);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr & addr);
//CLASS_DECL_NETWORKING_BSD void from_string(sockaddr & addr, ansichar * psz);
#endif


// } // namespace str

template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::in6_addr & addr)
{

   s.write(&addr, sizeof(addr));

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::in6_addr & addr)
{

   s.read(&addr, sizeof(addr));

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::in_addr & addr)
{

   s.write(&addr, sizeof(addr));

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::in_addr & addr)
{

   s.read(&addr, sizeof(addr));

   return s;

}


//CLASS_DECL_NETWORKING_BSD u32 c_inet_addr(const char *src);
//CLASS_DECL_NETWORKING_BSD i32 c_inet_pton(i32 af,const char *src,void *dst);
//CLASS_DECL_NETWORKING_BSD const char * c_inet_ntop(i32 af,const void *src,char *dst,i32 cnt);
//CLASS_DECL_NETWORKING_BSD string c_inet_ntop(i32 af,const void *src);



CLASS_DECL_NETWORKING_BSD string c_gethostbyname(const char * hostname);



//#include "byte_order.h"


