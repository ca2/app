#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/operating_system/console.h"
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

   auto pwsz = wstrShortName.get_buffer(requiredLength);

   auto requiredLength2 = ::GetShortPathNameW(wstrLongName, pwsz, requiredLength);

   wstrShortName.release_buffer(requiredLength2);

   if (requiredLength2 != requiredLength)
   {

      // rare failure case (especially on not-so-modern file systems)
      return strPath;

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









void std_out_buffer::write(const void * pdata, memsize nCount)
{

#ifdef WINDOWS

   DWORD dw;

   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pdata, (::u32)nCount, &dw, nullptr);

#else

   fwrite(pdata, nCount, 1, stdout);


#endif

}
