#include "framework.h"
//#include "library.h"

#include "acid/_operating_system.h"


namespace windows
{


   void * get_library_symbol_address(const ::file::path& pathLibrary, const ::scoped_string & scopedstrSymbolName)
   {

#ifdef WINDOWS_DESKTOP

      auto hmodule = ::GetModuleHandleW(::wstring(pathLibrary.windows_path()));

#else

      auto hmodule = ::LoadPackagedLibrary(::wstring(pathLibrary.windows_path()), 0);

#endif

      if (hmodule)
      {

         return ::GetProcAddress(hmodule, scopedstrSymbolName);

      }

      return nullptr;

   }


} // namespace windows



