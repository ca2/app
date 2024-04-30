// Created by Camilo on 2023-01-31 01:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "../networking.h"
#include "../address.h"
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <string.h>
#include <errno.h>


// Link with Iphlpapi.lib
#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3


/* Note: could also use malloc() and free() */

namespace networking_bsd
{


   ::pointer < ::item_array > networking::list_network_interfaces()
   {

      ::pointer < ::item_array > pitema;

      __defer_construct_new(pitema);

//      enum 
//      {
//          IFACE_IPv4 = (1<<0),
//          IFACE_IPv6 = (1<<1),
//          IFACE_IP   = (1<<0) | (1<<1),
//      };

      struct ifaddrs *curr, *list = NULL;

//      int result = 0;

//      if (!name || !(*name)) 
//      {
//      
//         errno = EINVAL;
//        
//         return 0;
//         
//      }

       if (getifaddrs(&list) == -1)
       {

          information() << "getifaddrs failed";

          return {};

       }

       for (curr = list; curr != NULL; curr = curr->ifa_next)
       {
   //        if (!strcmp(name, curr->ifa_name)) {
   //            if (->sa_family == AF_INET)
   //                result |= IFACE_IPv4;
   //            if (curr->ifa_addr->sa_family == AF_INET6)
   //                result |= IFACE_IPv6;
   //        }

//          if (curr->ifa_addr->sa_family != AF_INET
//              && curr->ifa_addr->sa_family != AF_INET6)
//          {
//             
//             continue;
//             
//          }

          ::string strName(curr->ifa_name);

          strName.trim();

          if(strName.is_empty())
          {

             continue;

          }

          information() << "Interface Name : " << strName;

         auto paddress = __create_new<::networking_bsd::address>();

         paddress->set_address(*curr->ifa_addr);

         paddress->m_strName = strName;

         paddress->m_item.m_eelement = e_element_item;

         pitema->add(paddress);

      }

      freeifaddrs(list);

      //::acme::get()->platform()->informationf(strLog);

      for (::raw::index iItem = 0; iItem < pitema->size(); iItem++)
      {

         auto pitem = pitema->element_at(iItem);

         pitem->m_item.m_iItem = iItem;

      }

      return pitema;

   }


} // namespace networking_bsd



