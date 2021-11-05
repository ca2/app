#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00
#include <windows.h>
#include "windows_common_new_api.h"

template < typename PFN >
void get_proc_address(PFN & pfn, const ::string & pszModule, const ::string & lpszName)
{

   auto hmodule = ::GetModuleHandleW(L"kernel32.dll");

   if (hmodule)
   {

      auto pfnModule = (PFN)GetProcAddress(hmodule, "SetThreadDescription");

      if (pfnModule)
      {
         pfn = pfnModule;

      }

   }

}

void windows10_init()
{

   get_proc_address(g_pfnSetThreadDescription, "kernel32.dll", "SetThreadDescription");

}
