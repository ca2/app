//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
//#include "subsystem_bsd_sockets/socket/Sockets.h"
#ifdef __APPLE__
#include <netdb.h>
#endif


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


   ::u32 subsystem::internet_address4(const ::scoped_string &scopedstr)
   {

#ifdef WINDOWS

      return inet_addr(::string(scopedstr));

#else

      return inet_addr(::string(scopedstr));

#endif

   }


      ::string subsystem::internet_address4_as_string(::u32 u)
   {

      throw ::interface_only();

      return {};
   }


   ::u32 subsystem::host_to_network_long(::u32 u)
   {

      return htonl(u);

   }


   ::u32 subsystem::network_to_host_long(::u32 u)
   {

      return ntohl(u);

   }


   memsize subsystem::getCurrentMemoryUsage()
   {

      return 0;

   }


   ::string subsystem::getLocalIpAddressString()
   {

      ::string strNameBuf;

      int iBufferSize = 1024;

      auto namebuf = strNameBuf.get_buffer(iBufferSize);

      if (gethostname(namebuf, 256) != 0)
      {

         strNameBuf.release_buffer();

         return "(Host name unavailable)";

      }

      strNameBuf.release_buffer();

      auto ph = gethostbyname(strNameBuf);
      if (!ph) {
         return "{IP address unavailable)";
      };

      strNameBuf.clear();
      char digtxt[5];
      for (int i = 0; ph->h_addr_list[i]; i++) {
         for (int j = 0; j < ph->h_length; j++) {
            sprintf(digtxt, "{}.", (unsigned char) ph->h_addr_list[i][j]);
            strNameBuf += digtxt;
         }
         if (ph->h_addr_list[i+1] != 0)
            strNameBuf += ", ";
      }
      return strNameBuf;
   }



}//namespace subsystem_bsd_sockets


