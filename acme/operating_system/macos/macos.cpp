// Created by camilo on 2021-08-29 16:00 BRT <3ThomasBS_!!
#include "framework.h"
#include "acme/operating_system.h"





::file::path dir_base_module()
{

#if defined(_UWP)

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

   wstrModuleFolder.release_string_buffer();

   wstrModuleFolder.trim_right(L"\\/");

   return wstrModuleFolder;

#else

   string strModuleFolder;

   auto wstrModuleFolder = strModuleFolder.get_string_buffer(MAX_PATH * 8);

   throw ::exception(todo);

   return wstrModuleFolder;

#endif

}






