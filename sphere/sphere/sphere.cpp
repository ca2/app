#include "framework.h"

#ifdef WINDOWS

#ifdef _UWP
[MTAThread]
#endif
extern "C" i32 WINAPI DllMain(HINSTANCE hInstance, u32 dwReason, LPVOID)
{

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::output_debug_string(L"sphere.dll initializing.\n");

   }
   else if (dwReason == DLL_THREAD_DETACH)
   {

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::output_debug_string(L"sphere.dll terminating.\n");

   }

   return TRUE;

}

#endif


