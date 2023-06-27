#include "framework.h"

#ifdef WINDOWS

#ifdef UNIVERSAL_WINDOWS
[MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{


   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      ::information(L"experience_lite.dll :: initializing!\n");


   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {


      ::information(L"experience_lite.dll :: terminating!\n");


   }

   return 1;   // ok

}


#endif




