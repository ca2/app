#include "framework.h"
#include "acme/operating_system.h"
#include "api.h"


string const char* psz
{

   if (psz[0] == 'c' &&
      psz[1] == 'l' &&
      psz[2] == 'a' &&
      psz[3] == 's' &&
      psz[4] == 's' &&
      psz[5] == ' ')
   {

      return psz + 6;

   }
   else if (psz[0] == 's' &&
      psz[1] == 't' &&
      psz[2] == 'r' &&
      psz[3] == 'u' &&
      psz[4] == 'c' &&
      psz[5] == 't' &&
      psz[6] == ' ')
   {

      return psz + 7;

   }
   else
   {

      return psz;

   }

}


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



