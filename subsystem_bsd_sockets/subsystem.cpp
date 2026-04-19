//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"


namespace subsystem_bsd_sockets
{


   ::subsystem_bsd_sockets::subsystem *            subsystem::s_p = nullptr;

   critical_section subsystem::s_criticalsectionResolveIp4;



   subsystem::subsystem()
   {

s_p = this;

   }


   subsystem::~subsystem()
   {


   }


   unsigned int subsystem::internet_address4(const ::scoped_string &scopedstr)
   {

#ifdef WINDOWS

      return inet_addr(::string(scopedstr));

#else

      return inet_addr(::string(scopedstr));

#endif

   }


      ::string subsystem::internet_address4_as_string(unsigned int u)
   {

      throw ::interface_only();

      return {};
   }


   unsigned int subsystem::host_to_network_long(unsigned int u)
   {

      return htonl(u);

   }


   unsigned int subsystem::network_to_host_long(unsigned int u)
   {

      return ntohl(u);

   }

    
}//namespace subsystem_bsd_sockets


