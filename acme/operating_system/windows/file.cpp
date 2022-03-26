#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/operating_system.h"


string CLASS_DECL_ACME windows_get_short_file_name(const string & strPath)
{

   wstring wstrLongName("\\\\?\\" + strPath);

   auto requiredLength = ::GetShortPathNameW(wstrLongName, nullptr, 0);

   if (!requiredLength)
   {

      // rare failure case (especially on not-so-modern file systems)
      return strPath;

   }

   wstring wstrShortName;

   auto pwsz = wstrShortName.get_string_buffer(requiredLength);

   auto requiredLength2 = ::GetShortPathNameW(wstrLongName, pwsz, requiredLength);

   wstrShortName.release_string_buffer(requiredLength2);

   if (requiredLength2 != requiredLength)
   {

      // rare failure case (especially on not-so-modern file systems)
      return strPath;

   }

   return wstrShortName;

}


CLASS_DECL_ACME ::file::path get_module_path(HMODULE hmodule)
{


#if defined(_UWP)

   return "m_app.exe";

#else

   wstring wstr(get_buffer, MAX_PATH * 8);

   ::GetModuleFileNameW(hmodule, wstr, (::u32)wstr.length());

   return solve_relative(string(wstr.release_string_buffer()));

#endif


}



