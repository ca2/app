#include "framework.h"


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, unsigned int dwReason, LPVOID lpReserved)
{
   // erase this if you use lpReserved
   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      informationf("::ca2:: ca.dll :: initializing!\n");
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      informationf("::ca2:: ca.dll :: terminating!\n");
   }
   return 1;   // ok
}


