#pragma once


#include "apex/operating_system.h"


#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

#include <netinet/in.h>

#if defined(APPLEOS)

typedef in6_addr in_addr6;

#endif

#endif


namespace net
{

   
   class address;


} // namespace net


namespace str
{


   CLASS_DECL_APEX void to(in6_addr & addr, const ansichar * psz);
   CLASS_DECL_APEX void from(string & str, const in6_addr & addr);
   CLASS_DECL_APEX void to(in_addr & addr, const ansichar * psz);
   CLASS_DECL_APEX void from(string & str, const in_addr & addr);
   CLASS_DECL_APEX void from(string & str, const sockaddr_in & addr);
   CLASS_DECL_APEX void from(string & str, const sockaddr_in6 & addr);
   CLASS_DECL_APEX void to(sockaddr_in & addr, const ansichar * psz);
   CLASS_DECL_APEX void to(sockaddr_in6 & addr, const ansichar * psz);
#ifdef BSD_STYLE_SOCKETS
   CLASS_DECL_APEX void from(string & str, const sockaddr & addr);
   CLASS_DECL_APEX void to(sockaddr & addr, ansichar * psz);
#endif


} // namespace str


//inline void __exchange(::stream & s, in6_addr & addr);

//inline void __exchange(::stream & s, in_addr & addr);



