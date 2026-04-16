//
// Created by camilo on 2026-04-06 06:16 <3ThomasBorregaardSørensen!!
//
// From subsystem_windows/_.h by camilo on 2026-04-12 06:32 <3ThomasBorregaardSørensen!!
//
//

#pragma once



#include "subsystem/_.h"



#ifndef ACME_OPERATING_SYSTEM
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
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


} // namespace subsystem_bsd_sockets




