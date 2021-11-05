#pragma once


#include "apex/operating_system.h"


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

#include <netinet/in.h>

#if defined(__APPLE__)

typedef in6_addr in_addr6;

#endif

#endif


namespace net
{

   
   class address;


} // namespace net


// namespace str
// {


   CLASS_DECL_APEX void from_string(in6_addr & addr, const ansichar * psz);
   CLASS_DECL_APEX void to_string(string & str, const in6_addr & addr);
   CLASS_DECL_APEX void from_string(in_addr & addr, const ansichar * psz);
   CLASS_DECL_APEX void to_string(string & str, const in_addr & addr);
   CLASS_DECL_APEX void to_string(string & str, const sockaddr_in & addr);
   CLASS_DECL_APEX void to_string(string & str, const sockaddr_in6 & addr);
   CLASS_DECL_APEX void from_string(sockaddr_in & addr, const ansichar * psz);
   CLASS_DECL_APEX void from_string(sockaddr_in6 & addr, const ansichar * psz);
#ifdef BSD_STYLE_SOCKETS
   CLASS_DECL_APEX void to_string(string & str, const sockaddr & addr);
   CLASS_DECL_APEX void from_string(sockaddr & addr, ansichar * psz);
#endif


// } // namespace str



