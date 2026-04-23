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


   memsize subsystem::getCurrentMemoryUsage()
   {

      return 0;

   }

   void subsystem::startSockets()
   {


      if (!m_pwindowssockets)
      {

         constructø)m?p
      }
         )

   }

   void subsystem::startSockets()
   {
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

      HOSTENT *ph = gethostbyname(strNameBuf);
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


