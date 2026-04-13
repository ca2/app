//
// Created by camilo on 2026-04-05 20:14 <3ThomasBorregaardSørensen!!
//


// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "subsystem/subsystem.h"
#include "subsystem_bsd_sockets/_common_header.h"


namespace subsystem_bsd_sockets
{


   class CLASS_DECL_SUBSYSTEM_BSD_SOCKETS subsystem :
      virtual public ::subsystem::subsystem
   {
   public:


      static ::subsystem_bsd_sockets::subsystem *            s_p;

      static critical_section s_criticalsectionResolveIp4;


      subsystem();
      ~subsystem() override;


      int get_last_socket_error() override;

      ::string get_socket_error_message_text(int iError) override;

      ::pointer < ::subsystem::SocketAddressIPv4Interface > resolve_ip4_address(const ::scoped_string & scopedstrHost, unsigned short port) override;


   };



} // namespace subsystem_bsd_sockets



inline ::subsystem_bsd_sockets::subsystem * bsd_sockets_subsystem()
{

   return ::subsystem_bsd_sockets::subsystem::s_p;

}

