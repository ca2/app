// Created by camilo on 2022-09-10 13:40 <3ThomasBorregaardSorensen!!
#include "framework.h"



static int g_iWsaStartupError;
static WSADATA g_wsadata = {};
static bool g_bWsaStartup = false;




CLASS_DECL_NETWORKING_BSD bool defer_initialize_operating_system_networking()
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

      information("Failed to initialize Winsock.dll!\n");

      return false;

   }

   if (lower_u8(g_wsadata.wVersion) < byteHi || (lower_u8(g_wsadata.wVersion) == byteHi && HIBYTE(g_wsadata.wVersion) < 2))
   {

      information("Could not find a usable version of Winsock.dll!\n");

      WSACleanup();

      return false;

   }
   else
   {

#ifdef DEBUG

      information("The Winsock 2.2 dll was found. OK.\n");

#endif

   }

   return true;

}


CLASS_DECL_NETWORKING_BSD bool defer_finalize_operating_system_networking()
{


   WSACleanup();

   return true;

}







i32 networking_last_error()
{

   return WSAGetLastError();

}




// only to be included in win32 projects
CLASS_DECL_NETWORKING_BSD string bsd_socket_error(int x)
{
   static   char tmp[100];
   switch (x)
   {
   case 10004: return "Interrupted function call.";
   case 10013: return "Permission denied.";
   case 10014: return "Bad address.";
   case 10022: return "Invalid argument.";
   case 10024: return "Too many open files.";
   case 10035: return "Resource temporarily unavailable.";
   case 10036: return "Operation now in progress.";
   case 10037: return "Operation already in progress.";
   case 10038: return "socket operation on nonsocket.";
   case 10039: return "Destination address required.";
   case 10040: return "Message too long.";
   case 10041: return "Protocol wrong type for socket.";
   case 10042: return "Bad protocol option.";
   case 10043: return "Protocol not supported.";
   case 10044: return "socket type not supported.";
   case 10045: return "Operation not supported.";
   case 10046: return "Protocol family not supported.";
   case 10047: return "Address family not supported by protocol family.";
   case 10048: return "Address already in use.";
   case 10049: return "Cannot assign requested address.";
   case 10050: return "Network is down.";
   case 10051: return "Network is unreachable.";
   case 10052: return "Network dropped connection on reset.";
   case 10053: return "Software caused connection abort.";
   case 10054: return "Connection reset by peer.";
   case 10055: return "No buffer space available.";
   case 10056: return "socket is already connected.";
   case 10057: return "socket is not connected.";
   case 10058: return "Cannot send after socket shutdown.";
   case 10060: return "Connection timed out.";
   case 10061: return "Connection refused.";
   case 10064: return "Host is down.";
   case 10065: return "No route to host.";
   case 10067: return "Too many processes.";
   case 10091: return "Network subsystem is unavailable.";
   case 10092: return "Winsock.dll version out of range.";
   case 10093: return "Successful WSAStartup not yet performed.";
   case 10101: return "Graceful shutdown in progress.";
   case 10109: return "Class type not found.";
   case 11001: return "Host not found.";
   case 11002: return "Nonauthoritative host not found.";
   case 11003: return "This is a nonrecoverable error.";
   case 11004: return "Valid name, no data record of requested type.";

   default:
      break;
   }
   sprintf(tmp, "Winsock error code: %d", x);
   return tmp;
}



