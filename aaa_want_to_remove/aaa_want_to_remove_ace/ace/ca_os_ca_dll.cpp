#include "framework.h"


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{
   // erase this if you use lpReserved
   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::output_debug_string("::ca2:: ca.dll :: initializing!\n");
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      ::output_debug_string("::ca2:: ca.dll :: terminating!\n");
   }
   return 1;   // ok
}


