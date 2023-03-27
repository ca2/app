// Created by camilo on 2022-09-10 16:52 <3ThomasBorregaardSørensen!!
#pragma once


#include <sys/socket.h>
#include <netinet/in.h>


#if defined(LINUX) || defined(FREEBSD) || defined(ANDROID)


#include <netdb.h>


//#define in_addr6 in6_addr
//#elif defined(ANDROID)
///#include <netdb.h>
//#include <netinet/in.h>
//#define in_addr6 in6_addr


#endif
//using SOCKET = int;


#if defined(FREEBSD)


#include <netinet/in.h>


#endif


#if defined(__arm__)


#if !defined(RASPBERRYPIOS)

#include <sys/endian.h>


#endif


#include <arpa/inet.h>


#endif



