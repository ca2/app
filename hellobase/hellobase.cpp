#include "framework.h"


#ifndef CUBE

#ifdef _UWP
[MTAThread]
#endif
int_bool WINAPI DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{

   __UNREFERENCED_PARAMETER(hInstance);

   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::output_debug_string("app_core_hellobase.dll :: initializing!\n");

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::output_debug_string("app_core_hellobase.dll :: terminating!\n");

   }

   return 1;   // ok

}


#endif