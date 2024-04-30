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

      ::acme::get()->platform()->informationf("app_core_helloaxis.dll :: initializing!\n");

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::acme::get()->platform()->informationf("app_core_helloaxis.dll :: terminating!\n");

   }

   return 1;   // ok

}


#endif
