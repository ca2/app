#pragma once


#if !defined(__APPLE__) && !defined(__ANDROID__) && !defined(NETBSD)


#if BYTE_ORDER == BIG_ENDIAN


#define HTONS(n) (n)
#define NTOHS(n) (n)
#define HTONL(n) (n)
#define NTOHL(n) (n)


#else


#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
   ((((unsigned long)(n)& 0xFF00)) << 8) | \
   ((((unsigned long)(n)& 0xFF0000)) >> 8) | \
   ((((unsigned long)(n)& 0xFF000000)) >> 24))

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
   ((((unsigned long)(n)& 0xFF00)) << 8) | \
   ((((unsigned long)(n)& 0xFF0000)) >> 8) | \
   ((((unsigned long)(n)& 0xFF000000)) >> 24))
#endif


#endif


#if BYTE_ORDER == BIG_ENDIAN


#define HTONLL(n) (n)
#define NTOHLL(n) (n)


#else


#ifndef __APPLE__
#define HTONLL(n) (((((unsigned long long)(n) & 0xFFuLL)) << 56) | \
   ((((unsigned long long)(n) & 0xFF00uLL)) << 40) | \
   ((((unsigned long long)(n) & 0xFF0000uLL)) << 24) | \
   ((((unsigned long long)(n) & 0xFF000000uLL)) << 8) | \
   ((((unsigned long long)(n) & 0xFF00000000uLL)) >> 8) | \
   ((((unsigned long long)(n) & 0xFF0000000000uLL)) >> 24) | \
   ((((unsigned long long)(n) & 0xFF000000000000uLL)) >> 40) | \
   ((((unsigned long long)(n) & 0xFF00000000000000uLL)) >> 56))
#define NTOHLL(n) (((((unsigned long long)(n) & 0xFFuLL)) << 56) | \
   ((((unsigned long long)(n) & 0xFF00uLL)) << 40) | \
   ((((unsigned long long)(n) & 0xFF0000uLL)) << 24) | \
   ((((unsigned long long)(n) & 0xFF000000uLL)) << 8) | \
   ((((unsigned long long)(n) & 0xFF00000000uLL)) >> 8) | \
   ((((unsigned long long)(n) & 0xFF0000000000uLL)) >> 24) | \
   ((((unsigned long long)(n) & 0xFF000000000000uLL)) >> 40) | \
   ((((unsigned long long)(n) & 0xFF00000000000000uLL)) >> 56))


#endif


#endif


//#if defined(UNIVERSAL_WINDOWS)
//
//
//#define AF_INET         2               // internetwork: UDP, TCP, etc.
//#define AF_INET6        23              // Internetwork Version 6
//
//
//#define htons(n) HTONS(n)
//#define ntohs(n) NTOHS(n)
//
//#define htonl(n) HTONL(n)
//#define ntohl(n) NTOHL(n)
//
//#endif

