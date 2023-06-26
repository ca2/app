#include "framework.h"

#ifdef WINDOWS

#ifdef UNIVERSAL_WINDOWS
[MTAThread]
#endif
extern "C" i32 WINAPI DllMain(HINSTANCE hInstance, u32 dwReason, LPVOID)
{

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::infomration(L"sphere.dll initializing.\n");

   }
   else if (dwReason == DLL_THREAD_DETACH)
   {

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::infomration(L"sphere.dll terminating.\n");

   }

   return true;

}

#endif


