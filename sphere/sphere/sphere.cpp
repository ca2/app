#include "framework.h"

#ifdef WINDOWS

#ifdef UNIVERSAL_WINDOWS
[MTAThread]
#endif
extern "C" int WINAPI DllMain(HINSTANCE hInstance, unsigned int dwReason, LPVOID)
{

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::information(L"sphere.dll initializing.\n");

   }
   else if (dwReason == DLL_THREAD_DETACH)
   {

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::information(L"sphere.dll terminating.\n");

   }

   return true;

}

#endif


