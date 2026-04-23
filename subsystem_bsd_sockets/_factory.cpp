//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "subsystem.h"
#include "SocketAddressIPv4.h"
#include "SocketIPv4.h"
#include "Sockets.h"


IMPLEMENT_FACTORY(subsystem_bsd_sockets)
{

   pfactory->add_factory_item<::subsystem_bsd_sockets::subsystem, ::subsystem::subsystem>();
   
   pfactory->add_factory_item<::subsystem_bsd_sockets::SocketAddressIPv4, ::subsystem::SocketAddressIPv4Interface>();

   pfactory->add_factory_item<::subsystem_bsd_sockets::SocketIPv4, ::subsystem::SocketIPv4Interface>();

   pfactory->add_factory_item<::subsystem_bsd_sockets::Sockets, ::subsystem::Sockets>();

}


//} // namespace subsystem_windows

