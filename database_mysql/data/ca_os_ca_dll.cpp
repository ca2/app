#include "framework.h"


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, unsigned int dwReason, LPVOID lpReserved)
{
   // erase this if you use lpReserved
   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      informationf("::ca2:: data.dll :: initializing!\n");

#ifndef UNIVERSAL_WINDOWS
      /* initialize client library */
      if(mysql_library_init(0,nullptr,nullptr))
      {
         informationf("mysql_library_init() failed");
         return false;
      }
#endif

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
#ifndef UNIVERSAL_WINDOWS
      try
      {
         mysql_library_end();
      }
      catch(...)
      {
      }
#endif

      informationf("::ca2:: data.dll :: terminating!\n");
   }
   return 1;   // ok
}


