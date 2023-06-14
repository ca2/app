#include "framework.h"
#include "_ios.h"
#include <netdb.h>


namespace ios
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

         information("Failed in call to gethostname, errno returns %d\n", errno);
         
         return false;
         
      }

      //get host information from the host name
      struct hostent * phostent = gethostbyname(szHostname);
      
      if (phostent == nullptr)
      {

         information("Failed in call to gethostbyname, errno returns %d\n", errno);
         
         return false;
         
      }

      //check the length of the IP adress
      if (phostent->h_length != 4)
      {
         
         information("IP address returned is not 32 bits !!\n");
         
         return false;
         
      }

      //call the virtual callback function in a loop

      i32 nAdapter = 0;

      string str;

      while(phostent->h_addr_list[nAdapter])
      {

         in_addr addr;

         ::memory_copy(&addr.s_addr, phostent->h_addr_list[nAdapter], phostent->h_length);

         str = addr;

         if(str.has_char())
         {

            stra.add(str);

         }

         nAdapter++;

      }

      return true;
      
   }


} // namespace ios



