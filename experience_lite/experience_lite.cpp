#include "framework.h"

#ifdef WINDOWS

#ifdef _UWP
[MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{


   __UNREFERENCED_PARAMETER(hInstance);
   __UNREFERENCED_PARAMETER(lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      ::output_debug_string(L"experience_lite.dll :: initializing!\n");


   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {


      ::output_debug_string(L"experience_lite.dll :: terminating!\n");


   }

   return 1;   // ok

}


#endif




