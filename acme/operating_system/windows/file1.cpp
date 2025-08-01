#include "framework.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/operating_system/console.h"
#include "acme/_operating_system.h"

#include <ShlObj.h>


string CLASS_DECL_ACME windows_get_short_file_name(const ::scoped_string & scopedstrPath)
{

   wstring wstrLongName("\\\\?\\" + scopedstrPath);

   auto requiredLength = ::GetShortPathNameW(wstrLongName, nullptr, 0);

   if (!requiredLength)
   {

      // rare failure case (especially on not-so-modern file systems)
      return scopedstrPath;

   }

   wstring wstrShortName;

   auto pwsz = wstrShortName.get_buffer(requiredLength);

   auto requiredLength2 = ::GetShortPathNameW(wstrLongName, pwsz, requiredLength);

   wstrShortName.release_buffer(requiredLength2);

   if (requiredLength2 != requiredLength)
   {

      // rare failure case (especially on not-so-modern file systems)
      return scopedstrPath;

   }

   return wstrShortName;

}


CLASS_DECL_ACME ::file::path get_module_path(HMODULE hmodule)
{


#if defined(UNIVERSAL_WINDOWS)

   return "m_app.exe";

#else

   wstring wstr;
   
   auto p = wstr.get_buffer(MAX_PATH * 8);

   ::GetModuleFileNameW(hmodule, p, MAX_PATH * 8);

   wstr.release_buffer();

   return solve_relative(string(wstr));

#endif


}


CLASS_DECL_ACME::file::path get_module_path(HANDLE hProcess, HMODULE hmodule)
{


#if defined(UNIVERSAL_WINDOWS)

   return "m_app.exe";

#else

   wstring wstr;

   auto p = wstr.get_buffer(MAX_PATH * 8);

   ::GetModuleFileNameExW(hProcess, hmodule, p, MAX_PATH * 8);

   wstr.release_buffer();

   return solve_relative(string(wstr));

#endif


}


// bool file_path_is_equal(const ::file::path & pathParam1, const ::file::path & pathParam2)
// {

//    wstring wstr1(pathParam1);

//    wstring wstr2(pathParam2);

//    unichar * pwszFile1;

//    unichar * pwszFile2;

//    ::acme::malloc < unichar * > pwszPath1;

//    ::acme::malloc < unichar * > pwszPath2;

//    pwszPath1.alloc((size_t)(wstr1.length() * 2 * sizeof(unichar)));

//    pwszPath2.alloc((size_t)(wstr2.length() * 2 * sizeof(unichar)));

//    int iCmp = -1;

//    if (GetFullPathNameW(wstr1, (DWORD)(pwszPath1.m_iSize / sizeof(unichar)), pwszPath1, &pwszFile1))
//    {

//       if (GetFullPathNameW(wstr2, (DWORD)(pwszPath2.m_iSize / sizeof(unichar)), pwszPath2, &pwszFile2))
//       {

//          iCmp = _wcsicmp(pwszPath1, pwszPath2);

//       }

//    }

//    return iCmp == 0;

// }


CLASS_DECL_ACME::file::path home_folder_path()
{

   wchar_t path[MAX_PATH + 1];
   zero(path);
   ::SHGetSpecialFolderPathW(HWND_DESKTOP, path, CSIDL_PROFILE, FALSE);
   return path;

}




