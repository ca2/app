// Created by camilo on 2021-08-29 16:00 BRT <3ThomasBS_!!
#include "framework.h"
#include "acme/_operating_system.h"
#include "acme/platform/system.h"


//::file::path dir_base_module()
//{
//
//#if defined(UNIVERSAL_WINDOWS)
//
//   return "";
//
//#elif defined(WINDOWS)
//
//   wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);
//
//   wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);
//
//   HMODULE hmodule = ::GetModuleHandleA("acme.dll");
//
//   if (hmodule == nullptr)
//   {
//
//      hmodule = ::GetModuleHandleA("spalib.dll");
//
//   }
//
//   if (hmodule == nullptr)
//   {
//
//      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));
//
//
//      if (wstrModuleFilePath.empty())
//      {
//
//         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);
//
//      }
//
//      wstrModuleFilePath.trim_right(L"\\/");
//
//      wcscat(wstrModuleFilePath, L"\\ca2\\");
//
//#ifdef X86
//
//      wcscat(wstrModuleFilePath, L"stage\\x86\\");
//
//#else
//      wide_concatenate(wstrModuleFilePath, L"stage\\x64\\");
//
//#endif
//
//      wcscpy(wstrModuleFolder, wstrModuleFilePath);
//
//      return string(wstrModuleFolder);
//
//   }
//
//   if (!GetModuleFileNameW(hmodule, wstrModuleFilePath, (unsigned int)wstrModuleFilePath.length()))
//   {
//
//      return "";
//
//   }
//
//   LPWSTR pszModuleFileName;
//
//   if (!GetFullPathNameW(wstrModuleFilePath, (unsigned int)wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
//   {
//
//      return "";
//
//   }
//
//   wstrModuleFolder.release_buffer();
//
//   wstrModuleFolder.trim_right(L"\\/");
//
//   return wstrModuleFolder;
//
//#else
//
//   string strModuleFolder;
//
//   auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);
//
//   throw ::exception(todo);
//
//   return wstrModuleFolder;
//
//#endif
//
//}





//
//
//void defer_create_acme_application_delegate(::platform::application * papplication);
//
//void apple_defer_nano_application_create(class ::platform::system * psystem)
//{
//   
//   auto papp = psystem->m_papplication;
//   
//   ::platform::application * papplication = (void *) (::platform::application *) papp;
//   
//   defer_create_acme_application_delegate(pApplication);
//   
//}

//bool g_bAcmeMacosApplicationInit = false;
//
//void defer_acme_macos_application_init(::platform::system * psystem)
//{
//
//   if(!g_bAcmeMacosApplicationInit)
//   {
//
//      g_bAcmeMacosApplicationInit = true;
//
//      acme_macos_applicat_defer_create_nano_application_delegateion_init1(psystem);
//
//   }
//
//}

//
//void macos_message_box_factory(::factory::factory * pfactory);
//
//
//void macos_factory(::factory::factory * pfactory)
//{
//
//   macos_message_box_factory(pfactory);
//
//}



