#include "framework.h"


int g_iWsaStartupError;
WSADATA g_wsadata = {};
bool g_bWsaStartup = false;


CLASS_DECL_APEX bool defer_init_winsock()
{

   BYTE byteHi = 2;

   BYTE byteLo = 2;

   if (!g_bWsaStartup)
   {

      /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
      WORD wVersionRequested = MAKEWORD(byteHi, byteLo);

      g_iWsaStartupError = WSAStartup(wVersionRequested, &g_wsadata);

   }

   if (g_iWsaStartupError != 0)
   {

      output_debug_string("Failed to initialize Winsock.dll!\n");

      return false;

   }

   if (LOBYTE(g_wsadata.wVersion) < byteHi || (LOBYTE(g_wsadata.wVersion) == byteHi && HIBYTE(g_wsadata.wVersion) < 2))
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

