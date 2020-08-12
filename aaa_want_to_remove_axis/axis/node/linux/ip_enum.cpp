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

namespace linux
{


   ip_enum::ip_enum()
   {

   }


   ip_enum::~ip_enum()
   {

   }


   ::count ip_enum::enumerate(string_array & stra)
   {
      /*
      //get this machines host name
      char szHostname[256];
      if (gethostname(szHostname, sizeof(szHostname)))
      {
         TRACE("Failed in call to gethostname, errno returns %d\n", errno);
         return FALSE;
      }

      //get host information from the host name
      hostent * phostent = gethostbyname(szHostname);
      if (phostent == nullptr)
      {
         TRACE("Failed in call to gethostbyname, errno returns %d\n", errno);
         return FALSE;
      }

      //check the length of the IP adress
      if (phostent->h_length != 4)
      {
         TRACE("IP address returned is not 32 bits !!\n");
         return FALSE;
      }

      //call the virtual CALLBACK function in a loop

      i32 nAdapter = 0;

      string str;

      while(phostent->h_addr_list[nAdapter])
      {

         in_addr addr;

         ::memcpy_dup(&addr.s_addr, phostent->h_addr_list[nAdapter], phostent->h_length);

         str = ::to_vsstring(&addr);

         if(str.has_char())
         {

            stra.add(str);

         }

         nAdapter++;

      }

      return TRUE;*/


char          buf[1024];
	 ifconf ifc;
	 ifreq *ifr;
	int           sck;
	int           nInterfaces;
	int           i;

/* Get a socket handle. */
	sck = socket(AF_INET, SOCK_DGRAM, 0);
	if(sck < 0)
	{
		perror("socket");
		return 1;
	}

/* Query available interfaces. */
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if(ioctl(sck, SIOCGIFCONF, &ifc) < 0)
	{
		perror("ioctl(SIOCGIFCONF)");
		return 1;
	}

/* Iterate through the list of interfaces. */
	ifr         = ifc.ifc_req;
	nInterfaces = ifc.ifc_len / sizeof(struct ifreq);
	for(i = 0; i < nInterfaces; i++)
	{
		struct ifreq *item = &ifr[i];

	/* Show the device name and IP address */
	string strName = item->ifr_name;
	string strIp = inet_ntoa(((struct sockaddr_in *)&item->ifr_addr)->sin_addr);
	stra.add(strIp);
	/* Get the MAC address */
		if(ioctl(sck, SIOCGIFHWADDR, item) < 0)
		{
			perror("ioctl(SIOCGIFHWADDR)");
			return 1;
		}

	/* Get the broadcast address (added by Eric) */
		if(ioctl(sck, SIOCGIFBRDADDR, item) >= 0)
		{
		   string strBroadcast = inet_ntoa(((struct sockaddr_in *)&item->ifr_broadaddr)->sin_addr);
		}
	}

        return 0;
   }



} // namespace win


