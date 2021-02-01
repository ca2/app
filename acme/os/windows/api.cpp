#include "framework.h"
#include "acme/operating_system.h"


namespace windows
{


   FARPROC api_base::get_address(const char* pszModule, const char* lpszName)
   {

      auto hmodule = ::GetModuleHandleW(wstring(pszModule));

      if (hmodule)
      {

         return GetProcAddress(hmodule, lpszName);

      }

      return nullptr;

   }


} // namespace windows



