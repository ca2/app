#pragma once

//#define AF_UNSPEC       0                 
//#define AF_INET         2                 // internetwork: UDP, TCP, etc.
//#define AF_INET6        23                // Internetwork Version 6
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
///*
// * Basic system type definitions, taken from the BSD file sys/types.h.
// */
//typedef unsigned char   u_char;
//typedef unsigned short  u_short;
//typedef unsigned int    u_int;
//typedef unsigned long   u_long;
//
//#if(_WIN32_WINNT >= 0x0501)
//typedef unsigned __int64 u_int64;
//#endif //(_WIN32_WINNT >= 0x0501)
//
//#ifdef __cplusplus
//}
//#endif
//
//#ifndef s_addr
///*
// * Internet address (old style... should be updated)
// */
//struct in_addr {
//        union {
//                struct { u_char s_b1,s_b2,s_b3,s_b4; } S_un_b;
//                struct { u_short s_w1,s_w2; } S_un_w;
//                u_long S_addr;
//        } S_un;
//#define s_addr  S_un.S_addr
//                                /* can be used for most tcp & ip code */
//#define s_host  S_un.S_un_b.s_b2
//                                /* host on imp */
//#define s_net   S_un.S_un_b.s_b1
//                                /* network */
//#define s_imp   S_un.S_un_w.s_w2
//                                /* imp */
//#define s_impno S_un.S_un_b.s_b4
//                                /* imp # */
//#define s_lh    S_un.S_un_b.s_b3
//                                /* logical host */
//};
//#endif
//
//
//
///* we have to define hton/ntoh as macros to avoid conflicts with Unix headers */
//#ifndef USE_WS_PREFIX
//
//#undef htonl
//#undef htons
//#undef ntohl
//#undef ntohs
//
//#ifdef WORDS_BIGENDIAN
//
//#define htonl(l) ((ULONG)(l))
//#define htons(s) ((u_short)(s))
//#define ntohl(l) ((ULONG)(l))
//#define ntohs(s) ((u_short)(s))
//
//#else  /* WORDS_BIGENDIAN */
//
//static inline u_short __wine_ushort_swap(u_short s)
//{
//    return (s >> 8) | (s << 8);
//}
//static inline ULONG __wine_ulong_swap(ULONG l)
//{
//    return ((ULONG)__wine_ushort_swap((u_short)l) << 16) | __wine_ushort_swap((u_short)(l >> 16));
//}
//#define htonl(l) __wine_ulong_swap(l)
//#define htons(s) __wine_ushort_swap(s)
//#define ntohl(l) __wine_ulong_swap(l)
//#define ntohs(s) __wine_ushort_swap(s)
//
//#endif  /* WORDS_BIGENDIAN */
//
//#endif  /* USE_WS_PREFIX */
//
//
//
//
//
//
//
////
//// IPv6 Internet address (RFC 2553)
//// This is an 'on-wire' format structure.
////
////typedef struct in6_addr {
////    union {
////        UCHAR       Byte[16];
////        USHORT      Word[8];
////    } u;
////} IN6_ADDR, *PIN6_ADDR, FAR *LPIN6_ADDR;
////
////#define in_addr6 in6_addr
////
//////
////// Defines to match RFC 2553.
//////
////#define _S6_un      u
////#define _S6_u8      Byte
////#define s6_addr     _S6_un._S6_u8
////
//////
////// Defines for our implementation.
//////
////#define s6_bytes    u.Byte
////#define s6_words    u.Word
//
//
///*
// * Structure used by kernel to store most
// * addresses.
// */
////struct sockaddr {
////        u_short sa_family;              /* address family */
////        char    sa_data[14];            /* up to 14 bytes of direct address */
////};
////
/////*
//// * Structure used by kernel to pass protocol
//// * information in raw sockets.
//// */
////struct sockproto {
////        u_short sp_family;              /* address family */
////        u_short sp_protocol;            /* protocol */
////};
//
//
//
////struct sockaddr_in
////{
////   short sin_family;
////   unsigned short sin_port;
////   struct in_addr sin_addr;
////   char sin_zero[8];
////};
////
////
////struct sockaddr_in6
////{
////  short sin6_family;
////  u_short sin6_port;
////  u_long sin6_flowinfo;
////  struct in6_addr sin6_addr;
////  u_long sin6_scope_id;
////};
////
////
////
////typedef struct addrinfo {
////  int             ai_flags;
////  int             ai_family;
////  int             ai_socktype;
////  int             ai_protocol;
////  size_t          ai_addrlen;
////  char            *ai_canonname;
////  struct sockaddr  *ai_addr;
////  struct addrinfo  *ai_next;
////} ADDRINFOA, *PADDRINFOA;
////
//
//
//#define AI_NUMERICHOST  0x00000004  // Nodename must be a numeric address string
//#define NI_NUMERICHOST  0x02  /* Return numeric form of the host's address */
//#define NI_NUMERICSERV  0x08  /* Return numeric form of the service (port #) */
//
//
////typedef int SOCKET;
////
////#define INVALID_SOCKET ((SOCKET) -1)
//
//
//
//
