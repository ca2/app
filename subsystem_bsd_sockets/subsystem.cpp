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

s_p = nullptr;

   }


   subsystem::~subsystem()
   {


   }

    
}//namespace subsystem_bsd_sockets


