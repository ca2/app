// Created by Camilo on 2023-01-31 05:45 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "../networking.h"
#include "../address.h"
#include "acme/primitive/primitive/memory.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iphlpapi.h>


// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")


#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3


#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))


/* Note: could also use malloc() and free() */


namespace networking_bsd
{


   ::pointer_array < ::networking::address >networking::list_computers()
   {

      ::pointer_array < ::networking::address > addressa;

      ULONG u = 0;

      auto uResult = ::GetIpNetTable(nullptr, &u, TRUE);

      ::memory memory;

      memory.set_size(u * 2);

      auto ptable = (PMIB_IPNETTABLE)memory.data();

      u = (ULONG) memory.size();
         
      auto uResult2 = ::GetIpNetTable(ptable, &u, TRUE);

      for (index i = 0; i < ptable->dwNumEntries; i++)
      {

         //auto & row = *(MIB_IPNETROW *)(memory.data() + SIZEOF_IPNETTABLE(i));

         auto & row = ptable->table[i];

         
         auto paddress = __create_new<::networking_bsd::address>();

         sockaddr_in in{};

         in.sin_family = AF_INET;
         in.sin_port = 0;
         in.sin_addr.S_un.S_addr = row.dwAddr;

         paddress->set_address(in);

         addressa.add(paddress);

      }

      //::output_debug_string(strLog);

      return addressa;

   }



} // namespace networking_bsd




