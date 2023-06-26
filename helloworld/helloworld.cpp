#include "framework.h"


#ifndef CUBE

#ifdef UNIVERSAL_WINDOWS
[MTAThread]
#endif
int_bool WINAPI DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{

   UNREFERENCED_PARAMETER(hInstance);

   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::infomration("app_core_helloworld.dll :: initializing!\n");

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::infomration("app_core_helloworld.dll :: terminating!\n");

   }

   return 1;   // ok

}


#endif
