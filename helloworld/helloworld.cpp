#include "framework.h"


#ifndef CUBE

#ifdef UNIVERSAL_WINDOWS
[MTAThread]
#endif
int_bool WINAPI DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{

   __UNREFERENCED_PARAMETER(hInstance);

   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      informationf("app_core_helloworld.dll :: initializing!\n");

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      informationf("app_core_helloworld.dll :: terminating!\n");

   }

   return 1;   // ok

}


#endif
