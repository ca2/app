// Created by camilo on 2022-09-10 13:40 <3ThomasBorregaardSorensen!!
#include "winsock2.h"


CLASS_DECL_NETWORKING_BSD bool defer_initialize_operating_system_networking()
{

   byte byteHi = 2;

   byte byteLo = 2;

   if (!g_bWsaStartup)
   {

      /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
      ::u16 wVersionRequested = MAKEWORD(byteHi, byteLo);

      g_iWsaStartupError = WSAStartup(wVersionRequested, &g_wsadata);

   }

   if (g_iWsaStartupError != 0)
   {

      output_debug_string("Failed to initialize Winsock.dll!\n");

      return false;

   }

   if (__LOBYTE(g_wsadata.wVersion) < byteHi || (__LOBYTE(g_wsadata.wVersion) == byteHi && HIBYTE(g_wsadata.wVersion) < 2))
   {

      output_debug_string("Could not find a usable version of Winsock.dll!\n");

      WSACleanup();

      return false;

   }
   else
   {

#ifdef DEBUG

      output_debug_string("The Winsock 2.2 dll was found. OK.\n");

#endif

   }

   return true;

}


CLASS_DECL_NETWORKING_BSD bool defer_finalize_operating_system_networking()
{


   WSACleanup();


}



