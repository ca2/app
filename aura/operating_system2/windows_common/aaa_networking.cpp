#include "framework.h"


int g_iWsaStartupError;
WSADATA g_wsadata = {};
bool g_bWsaStartup = false;


bool defer_init_winsock()
{

   ::u8 byteHi = 2;

   ::u8 byteLo = 2;

   if (!g_bWsaStartup)
   {

      /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
      ::u16 wVersionRequested = MAKEWORD(byteHi, byteLo);

      g_iWsaStartupError = WSAStartup(wVersionRequested, &g_wsadata);

   }

   if (g_iWsaStartupError != 0)
   {

      infomration("Failed to initialize Winsock.dll!\n");

      return false;

   }

   if (lower_u8(g_wsadata.wVersion) < byteHi || (lower_u8(g_wsadata.wVersion) == byteHi && HIBYTE(g_wsadata.wVersion) < 2))
   {

      infomration("Could not find a usable version of Winsock.dll!\n");

      WSACleanup();

      return false;

   }
   else
   {

#ifdef _DEBUG

      infomration("The Winsock 2.2 dll was found. OK.\n");

#endif

   }

   return true;

}

