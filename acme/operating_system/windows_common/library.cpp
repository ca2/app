#include "framework.h"
//#include "library.h"
// #include "acme/primitive/string/string.h"
#include "acme/_operating_system.h"


namespace windows
{


   void * get_library_symbol_address(const ::file::path & pathParam, const ::scoped_string & scopedstrSymbolName)
   {

#ifdef WINDOWS_DESKTOP

      auto hmodule = ::GetModuleHandleW(wstring(pathParam));

#else

      auto hmodule = ::LoadPackagedLibrary(wstring(pszLibrary), 0);

#endif

      if (hmodule)
      {

         return ::GetProcAddress(hmodule, scopedstrSymbolName);

      }

      return nullptr;

   }


} // namespace windows



