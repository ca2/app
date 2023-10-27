// Created by Camilo on 2023-01-31 05:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "../networking.h"
#include "../address.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/primitive/primitive/memory.h"
#include "apex/platform/system.h"
#include <stdio.h>
#include <stdlib.h>
#if defined(__APPLE__)
#define BSD_UNIX 1
#elif defined(FREEBSD)
#define BSD_UNIX 1
#endif


#if !defined(BSD_UNIX)


namespace networking_bsd
{


   ::pointer < ::item_array > networking::list_computers()
   {

      ::pointer < ::item_array > pitema;

      __defer_construct_new(pitema);

      char line[500]; // Read with fgets().
      char ip_address[500]; // Obviously more space than necessary, just illustrating here.
      int hw_type;
      int flags;
      char mac_address[500];
      char mask[500];
      char device[500];

      auto lines = file()->lines("/proc/net/arp");
      
      lines.erase_at(0);
      
      for(auto & line : lines)
      {

         sscanf(line.c_str(), "%s 0x%x 0x%x %s %s %s\n",
                ip_address,
                &hw_type,
                &flags,
                mac_address,
                mask,
                device);

         auto paddress = acmesystem()->m_papexsystem->networking()->create_address(ip_address);

         pitema->add(paddress);
          
      }

      for (::index iItem = 0; iItem < pitema->size(); iItem++)
      {

         auto pitem = pitema->element_at(iItem);

         pitem->m_item.m_iItem = iItem;

      }

      return pitema;

   }



} // namespace networking_bsd


#endif

