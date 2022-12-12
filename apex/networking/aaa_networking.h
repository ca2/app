#pragma once


//#include "apex/operating_system.h"


//#if defined(FREEBSD)
//
//
//#include <sys/socket.h>
//
//
//#endif
//
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
//
//#include <netinet/in.h>
//
//#if defined(__APPLE__)
//
//typedef in6_addr in_addr6;
//
//#endif
//
//#endif


namespace net
{

   
   class address;


} // namespace net


//// namespace str
//// {
//
//
//   CLASS_DECL_APEX void from_string(in6_addr & addr, const ::ansi_character * psz);
//   CLASS_DECL_APEX ::string as_string(const in6_addr & addr);
//   CLASS_DECL_APEX void from_string(in_addr & addr, const ::ansi_character * psz);
//   CLASS_DECL_APEX ::string as_string(const in_addr & addr);
//   CLASS_DECL_APEX ::string as_string(const sockaddr_in & addr);
//   CLASS_DECL_APEX ::string as_string(const sockaddr_in6 & addr);
//   CLASS_DECL_APEX void from_string(sockaddr_in & addr, const ::ansi_character * psz);
//   CLASS_DECL_APEX void from_string(sockaddr_in6 & addr, const ::ansi_character * psz);
//#ifdef BSD_STYLE_SOCKETS
//   CLASS_DECL_APEX ::string as_string(const sockaddr & addr);
//   CLASS_DECL_APEX void from_string(sockaddr & addr, ::ansi_character * psz);
//#endif
//
//
//// } // namespace str



