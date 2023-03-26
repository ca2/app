#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/_operating_system.h"


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

   wstring wstr(e_get_buffer, MAX_PATH * 8);

   ::GetModuleFileNameW(hmodule, wstr, (::u32)wstr.length());

   return solve_relative(string(wstr.release_string_buffer()));

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

//    i32 iCmp = -1;

//    if (GetFullPathNameW(wstr1, (DWORD)(pwszPath1.m_iSize / sizeof(unichar)), pwszPath1, &pwszFile1))
//    {

//       if (GetFullPathNameW(wstr2, (DWORD)(pwszPath2.m_iSize / sizeof(unichar)), pwszPath2, &pwszFile2))
//       {

//          iCmp = _wcsicmp(pwszPath1, pwszPath2);

//       }

//    }

//    return iCmp == 0;

// }





