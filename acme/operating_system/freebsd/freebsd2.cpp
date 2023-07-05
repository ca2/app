// Created by camilo on 2021-09-13 00:13 BRT Thomas Month!! <3ThomasBS_!!
#include "framework.h"
#include "acme/_operating_system.h"
#define __BSD_VISIBLE 1
#include <link.h>
#include <dlfcn.h>
#include <string.h>


::file::path dir_ca2_module()
{

#if defined(ANDROID)

   return acmepath()->app_module().folder();

#elif defined(UNIVERSAL_WINDOWS)

   wstring wstrModuleFilePath;

   auto pwszModuleFilePath = wstrModuleFilePath.get_buffer(MAX_PATH * 8);

   if (!GetModuleFileNameW(nullptr, pwszModuleFilePath, MAX_PATH * 8))
   {

      return "";

   }

   wstrModuleFilePath.release_buffer();

   LPWSTR pszModuleFileName;

   wstring wstrModuleFolder;

   auto pwszModuleFolder = wstrModuleFolder.get_buffer(MAX_PATH * 8);

   if (!GetFullPathNameW(wstrModuleFilePath, MAX_PATH * 8, pwszModuleFolder, &pszModuleFileName))
   {

      return "";

   }

   wstrModuleFolder.release_buffer();

   wstrModuleFolder.case_insensitive_ends_eat("\\");
   wstrModuleFolder.case_insensitive_ends_eat("/");
   wstrModuleFolder.case_insensitive_ends_eat("\\");
   wstrModuleFolder.case_insensitive_ends_eat("/");

   return string(wstrModuleFolder);


#elif defined(WINDOWS)


   wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);


   wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);


   HMODULE hmodule = ::GetModuleHandleA("acme.dll");

   if (hmodule == nullptr)
      hmodule = ::GetModuleHandleA("spalib.dll");

   if (hmodule == nullptr)
   {

      PWSTR pwstr = nullptr;

      try
      {

         HRESULT hr = SHGetKnownFolderPath(
            FOLDERID_ProgramFilesX86,
            KF_FLAG_DEFAULT,
            nullptr,
            &pwstr);

         wcscpy(wstrModuleFilePath, pwstr);

      }
      catch (...)
      {


      }

      if (pwstr)
      {

         ::CoTaskMemFree(pwstr);
         pwstr = nullptr;

      }


      //if(wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '\\'

      //      || wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '/')

      //{
      //   wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] = '\0';

      //}
      wcscat(wstrModuleFilePath, L"\\ca2\\");

#ifdef X86
      wcscat(wstrModuleFilePath, L"stage\\x86\\");

#else
      wide_concatenate(wstrModuleFilePath, L"stage\\x64\\");

#endif

      wcscpy(wstrModuleFolder, wstrModuleFilePath);

      wstrModuleFilePath.release_buffer();

      return string(wstrModuleFolder);


   }

   if (!GetModuleFileNameW(hmodule, wstrModuleFilePath, (::u32)wstrModuleFilePath.length()))
   {

      return "";

   }

   wstrModuleFilePath.release_buffer();

   LPWSTR pszModuleFileName;

   if (!GetFullPathNameW(wstrModuleFilePath, (::u32)wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
   {

      return "";

   }

   wstrModuleFolder.release_buffer();

   if (wstrModuleFolder.has_char())
   {

      wstrModuleFolder.trim_right(L"\\/");

   }

   return wstrModuleFolder;

#elif defined(__APPLE__)

   string str;

   {

      //         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
      //
      //         if(str.has_char())
      //         {
      //            str = ::file::path(str).folder();
      //            goto found;
      //
      //         }
      //
      //
      //         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
      //
      //         if(str.has_char())
      //         {
      //            str = ::file::path(str).folder();
      //            goto found;
      //
      //         }

      str = get_exe_path();


      if (str.has_char())
      {
         str = ::file::path(str).folder();
         goto found;
      }


   }
   found:
   ;

   return str;

#else

   string strModuleFolder;

   auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);

   void * handle = dlopen("libacme.so", RTLD_NOW);

   if (handle == nullptr)
   {

      strcpy(wstrModuleFolder, "/ca2/");

   }
   else
   {

      link_map * plm;

      dlinfo(handle, RTLD_DI_LINKMAP, &plm);

      strcpy(wstrModuleFolder, plm->l_name);

      dlclose(handle);

      strcpy(wstrModuleFolder, ::file_path_folder(wstrModuleFolder));

   }

   return string(wstrModuleFolder);

#endif

}



::file::path dir_base_module()
{

#if defined(UNIVERSAL_WINDOWS)

   return "";

#elif defined(WINDOWS)

   wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);

   wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);

   HMODULE hmodule = ::GetModuleHandleA("acme.dll");

   if (hmodule == nullptr)
   {

      hmodule = ::GetModuleHandleA("spalib.dll");

   }

   if (hmodule == nullptr)
   {

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));


      if (wstrModuleFilePath.empty())
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wcscat(wstrModuleFilePath, L"\\ca2\\");

#ifdef X86

      wcscat(wstrModuleFilePath, L"stage\\x86\\");

#else
      wide_concatenate(wstrModuleFilePath, L"stage\\x64\\");

#endif

      wcscpy(wstrModuleFolder, wstrModuleFilePath);

      return string(wstrModuleFolder);

   }

   if (!GetModuleFileNameW(hmodule, wstrModuleFilePath, (::u32)wstrModuleFilePath.length()))
   {

      return "";

   }

   LPWSTR pszModuleFileName;

   if (!GetFullPathNameW(wstrModuleFilePath, (::u32)wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
   {

      return "";

   }

   wstrModuleFolder.release_buffer();

   wstrModuleFolder.trim_right(L"\\/");

   return wstrModuleFolder;

#else

   string strModuleFolder;

   auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);

   throw ::exception(todo);

   return wstrModuleFolder;

#endif

}



