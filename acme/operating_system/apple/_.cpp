//
//  apple.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 21/07/17.
//  ThomasBS-LiveEdu.TV(LiveCoding.TV)
//
//

#include "framework.h"

#include "main.h"
#include "acme/constant/user.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
//aaa_//#include "acme/operating_system/_.h"
//#include "acme/operating_system/_os.h"
//#include "acme/update.h"
//char * ns_realpath(const ::file::path & path);
//char * mm_ca2_command_line();


#include "acme/_operating_system.h"


#include <dispatch/dispatch.h>


void * CreateDispatchQueue()
{

   return dispatch_queue_create (nullptr, nullptr);

}


void CancelDispatchSource(void * p)
{

   dispatch_source_cancel((dispatch_source_t) p);

}


void * CreateDispatchTimer(unsigned long long interval, unsigned long long leeway, void * queue, void (*pfnTimer)(void * p), void * p)
{

   dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, (dispatch_queue_t) queue);

   if (timer)
   {

      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);

      dispatch_source_set_event_handler(timer, ^() { pfnTimer(p); });

      dispatch_resume(timer);

   }

   return timer;

}


void * ResetDispatchTimer(void * timerParam, unsigned long long interval, unsigned long long leeway)
{

   dispatch_source_t timer = (dispatch_source_t) timerParam;

   if (timer)
   {

      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);

      //dispatch_resume(timer);

   }

   return timer;

}


void ReleaseDispatch(void * p)
{

   dispatch_release((dispatch_object_t) p);

}


static bool g_bRunSystem = false;


int defer_run_system()
{

   if(g_bRunSystem)
   {

      return 0;

   }

   g_bRunSystem = true;

   //return __start_system_with_file(nullptr);
   
   return 0;

}


//int defer_run_system(const ::file::path & path)
//{
//
//   return __start_system_with_file(scopedstrFileName);
//
//}
//
//
//int defer_run_system(char ** pszaFileName, int iFileCount)
//{
//
//   return __start_system_with_file((const_char_pointer *) pszaFileName, iFileCount);
//
//}
//


char * ns_get_executable_path();

string apple_get_executable_path()
{
   
   return ::string_from_strdup(ns_get_executable_path());
   
}


::file::path get_module_path()
{
   
   return apple_get_executable_path();
   
}


::file::path get_module_folder()
{
   
   return get_module_path().folder();
   
}


//void apple_on_new_file()
//{
//
//   ::acmeacmesystem()->on_open_file(::e_type_empty, "");
//
//}

//// iMillisDelay default 500ms good
//void apple_accumulate_on_open_file(const_char_pointer *psza, int iCount, const ::scoped_string & scopedstrExtra)
//{
//
//   string_array stra;
//
//   stra.c_add((char **) psza, iCount, false);
//
//   for(::collection::index i = 0; i < stra.get_count(); i++)
//   {
//
//      if(::str::case_insensitive_begins_eat(stra[i], "file://"))
//      {
//
//         if(!string_begins(stra[i], "/"))
//         {
//
//            stra[i] = "/" + stra[i];
//
//         }
//
//         stra[i] = ::acmeacmesystem()->url().::url::decode(stra[i]);
//
//      }
//
//   }
//
//   ::acmeacmesystem()->defer_accumulate_on_open_file(stra, pszExtra);
//
//}



//void apple_on_open_file(const_char_pointer *psza, int iCount, const ::scoped_string & scopedstrExtra)
//{
//
//   if(iCount <= 0)
//   {
//
//      apple_on_new_file();
//
//   }
//   else if(iCount == 1)
//   {
//
//      ::acmeacmesystem()->on_open_file(scopedstra[0], pszExtra);
//
//      ::free((void *) psza[0]);
//
//      ::free(scopedstra);
//
//   }
//   else
//   {
//
//      string_array stra;
//
//      stra.c_add((char **) psza, iCount, false);
//
//      ::acmeacmesystem()->on_open_file(stra, pszExtra);
//
//   }
//
//}


::file::path __xxxnode_full_file_path(file::path path)
{

   if(path.is_empty())
   {

      return path;

   }

   //return ::string_from_strdup(ns_realpath(path));

   char sz[4096];

   zero(sz);

   return realpath(path, sz);

}



long long oswindow_id(oswindow w)
{

   return (long long) (w);

}


//int is_window(oswindow window)
//{
//   return (window == nullptr) ? false : (window->get_user_interaction() != nullptr);
//}

//
//
//
//int show_window(oswindow oswindow, int iShow)
//{
//   
//   if(::is_null(oswindow))
//   {
//    
//      return false;
//      
//   }
// 
//   if(::is_null(oswindow->m_pimpl))
//   {
//      
//      return false;
//      
//   }
//   
//   return oswindow->m_pimpl->show_window(iShow);
//   
//}


//::file::path get_module_folder(::particle * pparticle)
//{
//   
//   pparticle->system()-
//
//   critical_section_lock criticalsectionlock()
//   
//   if(!pparticle->system()->m_bModuleFolder)
//   {
//      
//      pparticle->system()->m_pathModuleFolder = ::get_module_path(pparticle).folder();
//      
//   }
//   
//   return pparticle->system()->m_pathModuleFolder;
//   
//}

//::file::path dir_ca2_module()
//{
//
//#if defined(__ANDROID__)
//
//   return path_system()->app_module().folder();
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//   wstring wstrModuleFilePath;
//
//   auto pwszModuleFilePath = wstrModuleFilePath.get_buffer(MAX_PATH * 8);
//
//   if (!GetModuleFileNameW(nullptr, pwszModuleFilePath, MAX_PATH * 8))
//   {
//
//      return "";
//
//   }
//
//   wstrModuleFilePath.release_buffer();
//
//   LPWSTR pszModuleFileName;
//
//   wstring wstrModuleFolder;
//
//   auto pwszModuleFolder = wstrModuleFolder.get_buffer(MAX_PATH * 8);
//
//   if (!GetFullPathNameW(wstrModuleFilePath, MAX_PATH * 8, pwszModuleFolder, &pszModuleFileName))
//   {
//
//      return "";
//
//   }
//
//   wstrModuleFolder.release_buffer();
//
//   wstrModuleFolder.case_insensitive_ends_eat("\\");
//   wstrModuleFolder.case_insensitive_ends_eat("/");
//   wstrModuleFolder.case_insensitive_ends_eat("\\");
//   wstrModuleFolder.case_insensitive_ends_eat("/");
//
//   return string(wstrModuleFolder);
//
//
//#elif defined(WINDOWS)
//
//
//   wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);
//
//
//   wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);
//
//
//   HMODULE hmodule = ::GetModuleHandleA("acme.dll");
//
//   if (hmodule == nullptr)
//      hmodule = ::GetModuleHandleA("spalib.dll");
//
//   if (hmodule == nullptr)
//   {
//
//      PWSTR pwstr = nullptr;
//
//      try
//      {
//
//         HRESULT hr = SHGetKnownFolderPath(
//            FOLDERID_ProgramFilesX86,
//            KF_FLAG_DEFAULT,
//            nullptr,
//            &pwstr);
//
//         wcscpy(wstrModuleFilePath, pwstr);
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//      if (pwstr)
//      {
//
//         ::CoTaskMemFree(pwstr);
//         pwstr = nullptr;
//
//      }
//
//
//      //if(wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '\\'
//
//      //      || wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '/')
//
//      //{
//      //   wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] = '\0';
//
//      //}
//      wcscat(wstrModuleFilePath, L"\\ca2\\");
//
//#ifdef X86
//      wcscat(wstrModuleFilePath, L"stage\\x86\\");
//
//#else
//      wide_concatenate(wstrModuleFilePath, L"stage\\x64\\");
//
//#endif
//
//      wcscpy(wstrModuleFolder, wstrModuleFilePath);
//
//      wstrModuleFilePath.release_buffer();
//
//      return string(wstrModuleFolder);
//
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
//   wstrModuleFilePath.release_buffer();
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
//   if (wstrModuleFolder.has_character())
//   {
//
//      wstrModuleFolder.trim_right(L"\\/");
//
//   }
//
//   return wstrModuleFolder;
//
//#elif defined(__APPLE__)
//
//   string str;
//
//   {
//
//      //         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero double_size
//      //
//      //         if(str.has_character())
//      //         {
//      //            str = ::file::path(str).folder();
//      //            goto found;
//      //
//      //         }
//      //
//      //
//      //         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero double_size
//      //
//      //         if(str.has_character())
//      //         {
//      //            str = ::file::path(str).folder();
//      //            goto found;
//      //
//      //         }
//
//      str = get_exe_path();
//
//
//      if (str.has_character())
//      {
//         str = ::file::path(str).folder();
//         goto found;
//      }
//
//
//   }
//found:
//   ;
//
//   return str;
//
//#else
//
//   string strModuleFolder;
//
//   auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);
//
//   void * handle = dlopen("libacme.so", RTLD_NOW);
//
//   if (handle == nullptr)
//   {
//
//      strcpy(wstrModuleFolder, "/ca2/");
//
//   }
//   else
//   {
//
//      link_map * plm;
//
//      dlinfo(handle, RTLD_DI_LINKMAP, &plm);
//
//      strcpy(wstrModuleFolder, plm->l_name);
//
//      dlclose(handle);
//
//      strcpy(wstrModuleFolder, ::file_path_folder(wstrModuleFolder));
//
//   }
//
//   return string(wstrModuleFolder);
//
//#endif
//
//}








void * apple_get_application_delegate(::platform::application * papplication)
{

   return papplication->system()->m_pApplicationDelegate;

}


void apple_set_application_delegate(::platform::application * papplication, void * pDelegate)
{

   papplication->system()->m_pApplicationDelegate = pDelegate;

}

