//
//  apple_ip_enum.cpp
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/17.
//

#include "framework.h"
#include "_.h"
#include <unistd.h>

/*
 Example code to obtain IP and MAC for all available interfaces on Linux.
 by Adam Pierce <adam@doctort.org>
 
 http://www.doctort.org/adam/
 Ķ
 */

#ifndef __USE_MISC
#define __USE_MISC
#endif
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace apple
{
   
   
   ip_enum::ip_enum()
   {
      
   }
   
   
   ip_enum::~ip_enum()
   {
      
   }
   
   
   ::count ip_enum::enumerate(string_array & stra)
   {
      //get this machines host name
      char szHostname[256];
      if (gethostname(szHostname, sizeof(szHostname)))
      {
         TRACE("Failed in call to gethostname, errno returns %d\n", errno);
         return false;
      }
      
      //get host information from the host name
      hostent * phostent = gethostbyname(szHostname);
      if (phostent == nullptr)
      {
         TRACE("Failed in call to gethostbyname, errno returns %d\n", errno);
         return false;
      }
      
      //check the length of the IP adress
      if (phostent->h_length != 4)
      {
         TRACE("IP address returned is not 32 bits !!\n");
         return false;
      }
      
      //call the virtual callback function in a loop
      
      i32 nAdapter = 0;
      
      string str;
      
      while(phostent->h_addr_list[nAdapter])
      {
         
         in_addr addr;
         
         ::memcpy_dup(&addr.s_addr, phostent->h_addr_list[nAdapter], phostent->h_length);
         
         ::str::from(str, addr);
         
         if(str.has_char())
         {
            
            stra.add(str);
            
         }
         
         nAdapter++;
         
      }
      
      return true;
      
   }
   
   
} // namespace apple












