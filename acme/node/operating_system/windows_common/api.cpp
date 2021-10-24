#include "framework.h"
#include "acme/operating_system.h"
#include "api.h"



namespace windows
{


   FARPROC api_base::get_address(const char* pszModule, const char* lpszName)
   {

#ifdef WINDOWS_DESKTOP

      auto hmodule = ::GetModuleHandleW(wstring(pszModule));

#else

      auto hmodule = ::LoadPackagedLibrary(wstring(pszModule), 0);

#endif

      if (hmodule)
      {

         return GetProcAddress(hmodule, lpszName);

      }

      return nullptr;

   }


} // namespace windows



