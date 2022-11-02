#include "framework.h"
//#include "library.h"
#include "acme/primitive/string/string.h"
#include "acme/_operating_system.h"


namespace windows
{


   void * get_library_symbol_address(const char * pszLibrary, const char* pszSymbolName)
   {

#ifdef WINDOWS_DESKTOP

      auto hmodule = ::GetModuleHandleW(wstring(pszLibrary));

#else

      auto hmodule = ::LoadPackagedLibrary(wstring(pszLibrary), 0);

#endif

      if (hmodule)
      {

         return ::GetProcAddress(hmodule, pszSymbolName);

      }

      return nullptr;

   }


} // namespace windows



