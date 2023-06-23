// From https://stackoverflow.com/questions/41413534/get-app-path-for-fopen-in-uwpby by camilo on 2023-02-11 01:17 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/_operating_system.h"
//#include <windows.h>
//#include <string>

extern "C" IMAGE_DOS_HEADER __ImageBase;

::file::path get_module_path()
{

   ::wstring buffer;

   DWORD dwBufferLength = MAX_PATH;

   for (;;)
   {
      auto psz = buffer.get_buffer(dwBufferLength);

      ::SetLastError(ERROR_SUCCESS);

      auto pathLength = ::GetModuleFileNameW(reinterpret_cast<HMODULE>(&__ImageBase), psz, dwBufferLength);

      if (pathLength == 0)
      {

         throw ::exception(error_failed, "GetModuleFileName failed"); // You can call GetLastError() to get more info here

      }

      if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
      {

         buffer.release_buffer(pathLength);

         return buffer;

      }

      dwBufferLength *= 2;

   }

}
