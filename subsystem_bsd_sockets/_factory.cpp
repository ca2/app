//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "subsystem.h"
#include "SocketAddressIPv4.h"
#include "SocketIPv4.h"


CLASS_DECL_EXPORT void subsystem_bsd_sockets_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::subsystem_bsd_sockets::subsystem, ::subsystem::subsystem>();
   
   pfactory->add_factory_item<::subsystem_bsd_sockets::SocketAddressIPv4, ::subsystem::SocketAddressIPv4>();

   pfactory->add_factory_item<::subsystem_bsd_sockets::SocketIPv4, ::subsystem::SocketIPv4>();

}


//} // namespace subsystem_win32

