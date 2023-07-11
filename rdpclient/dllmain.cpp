#include "config.h"

#include <freerdp/client.h>

#include <freerdp/addin.h>
#include <freerdp/assistance.h>
#include <freerdp/client/file.h>
#include <freerdp/client/cmdline.h>
#include <freerdp/client/channels.h>



extern "C" int APIENTRY
DllMain(HINSTANCE hInstance,::u32 dwReason,LPVOID lpReserved)
{


   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   if(dwReason == DLL_PROCESS_ATTACH)
   {
      //freerdp_channels_global_init();


#if defined(_WIN32) && !defined(UNIVERSAL_WINDOWS)
      ::information("::ca2:: axisrdpclient.dll :: initializing!\n");
#endif

   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {

      //freerdp_channels_global_uninit();
#if defined(_WIN32) && !defined(UNIVERSAL_WINDOWS)
      ::information("::ca2:: axisrdpclient.dll :: terminating!\n");
#endif

   }


   return 1;   // ok


}


