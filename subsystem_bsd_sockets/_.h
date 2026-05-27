//
// Created by camilo on 2026-04-06 06:16 <3ThomasBorregaardSørensen!!
//
// From subsystem_macos/_.h by camilo on 2026-04-12 06:32 <3ThomasBorregaardSørensen!!
//
//

#pragma once



#include "subsystem/_.h"



#ifndef ACME_OPERATING_SYSTEM
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#endif


#ifdef __APPLE__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#if defined(_subsystem_bsd_sockets_project)
#define CLASS_DECL_SUBSYSTEM_BSD_SOCKETS CLASS_DECL_EXPORT
#else
#define CLASS_DECL_SUBSYSTEM_BSD_SOCKETS CLASS_DECL_IMPORT
#endif


namespace subsystem_bsd_sockets
{



   class SocketAddressIPv4;

   //class SocketAddressIPv4Interface;

   class SocketIPv4;

   //class SocketIPv4Interface;

   class subsystem;

#ifdef WINDOWS


   class WindowsSockets;


using socket_t = SOCKET;

inline static const ::i32 _SOCKET_ERROR = SOCKET_ERROR;

inline static const socket_t _INVALID_SOCKET = INVALID_SOCKET;

#else

using socket_t = ::i32;

inline static const ::i32 _SOCKET_ERROR = -1;

inline static const socket_t _INVALID_SOCKET = -1;

#endif


} // namespace subsystem_bsd_sockets




