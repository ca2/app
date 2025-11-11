// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/windows/library.cpp by
// camilo on 2024-06-02 21:27 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/universal_windows/library.cpp by
// camilo on 2024-06-10 07:32 <3ThomasBorregaardSorensen!!
// Created by camilo on 2024-06-02 23:17 <3ThomasBorregaardSorensen!!
// From windows/library on 2024-06-10 07:32 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/platform/application.h"
#include "acme/_operating_system.h"
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/application.h"
#include "acme/_operating_system.h"


namespace universal_windows
{




         dynamic_library::dynamic_library()
         {

         }


         dynamic_library::~dynamic_library()
         {


         }


         ::file::path dynamic_library::module_path(library_t * plibrary)
         {

            auto hmodule = (HMODULE)plibrary;

            DWORD dwSize = 128;

            while (dwSize < 16_MiB)
            {

               ::wstring wstrPath;

               auto pwsz = wstrPath.get_buffer(dwSize + 1);

               DWORD dwPossiblyTruncatedSize = GetModuleFileNameW(hmodule, pwsz, dwSize);

               wstrPath.release_buffer(dwPossiblyTruncatedSize);

               if (dwPossiblyTruncatedSize == 0)
               {

                  throw_last_error_exception();

               }
               else if (dwPossiblyTruncatedSize < dwSize)
               {

                  return wstrPath;

               }

               dwSize *= 2;

            }

            throw ::exception(error_failed);

            return {};

         }


         ::library_t * dynamic_library::module_by_name(const ::scoped_string & scopedstrName)
         {

            ::string strName(scopedstrName);

            if (case_insensitive_ansi_ends(strName, ".ilk"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strName, ".pdb"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strName, ".lib"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strName, ".exp"))
            {

               return nullptr;

            }

            if (ansi_find_string(file_path_name(strName), ".") == nullptr)
            {

               strName += ".dll";

            }

            wstring wstrName(strName);

            HMODULE hmodule = ::GetModuleHandleW(wstrName);

            auto plibrary = (library_t *)hmodule;

            return plibrary;

         }


         ::library_t * dynamic_library::module_by_path(const ::file::path & path)
         {

            ::string strPath(path);

            if (case_insensitive_ansi_ends(strPath, ".ilk"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strPath, ".pdb"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strPath, ".lib"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strPath, ".exp"))
            {

               return nullptr;

            }

            if (ansi_find_string(file_path_name(strPath), ".") == nullptr)
            {

               strPath += ".dll";

            }

            auto windowspath = ::file::path(strPath).windows_path();

            ::wstring wstrPath;

            wstrPath = windowspath.extended_path();

            HMODULE hmodule = ::GetModuleHandleW(wstrPath);

            auto plibrary = (library_t *)hmodule;

            return plibrary;

         }


         //library_t* dynamic_library::touch(const ::file::path& pathParam, string& strMessage)
         //{

         //   strMessage.empty();

         //   string strError;

         //   string strPath(pathParam);

         //   unsigned int uiError;

         //   void* plibrary = nullptr;


         //   informationf("---->  Going to touch library (1) " + string(strPath) + "\n");

         //   ::file::path path;

         //   path = strPath;

         //   try
         //   {

         //      plibrary = ::GetModuleHandleW(wstring(path));

         //   }
         //   catch (...)
         //   {

         //   }

         //   if (plibrary != nullptr)
         //   {

         //      goto finished;

         //   }

         //   uiError = ::GetLastError();

         //   strError = "\n (1) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

         //   strMessage += strError;

         //   path = "\\\\?\\" + strPath;

         //   try
         //   {

         //      plibrary = ::GetModuleHandleW(wstring(path));

         //   }
         //   catch (...)
         //   {

         //   }

         //   if (plibrary != nullptr)
         //   {

         //      goto finished;

         //   }

         //   uiError = ::GetLastError();

         //   strError = "\n (2) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

         //   strMessage += strError;

         //   path = application()->get_module_folder() / strPath;

         //   try
         //   {

         //      plibrary = ::GetModuleHandleW(wstring(path));

         //   }
         //   catch (...)
         //   {

         //   }

         //   uiError = ::GetLastError();

         //   strError = "\n (3) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

         //   strMessage += strError;

         //   path = "\\\\?\\" + string(application()->get_module_folder() / strPath);

         //   try
         //   {

         //      plibrary = ::GetModuleHandleW(wstring(path));

         //   }
         //   catch (...)
         //   {

         //   }

         //   if (plibrary != nullptr)
         //   {

         //      goto finished;

         //   }

         //   uiError = ::GetLastError();

         //   strError = "\n (4) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

         //   strMessage += strError;

         //   /*path = ::dir_base_module() / strPath;

         //   try
         //   {

         //      plibrary = ::GetModuleHandleW(wstring(path));

         //   }
         //   catch (...)
         //   {

         //   }

         //   if (plibrary != nullptr)
         //   {

         //      goto finished;

         //   }

         //   uiError = ::GetLastError();

         //   strError = "\n (5) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

         //   strMessage += strError;

         //   path = "\\\\?\\" + string(::dir_base_module() / strPath);

         //   try
         //   {

         //      plibrary = ::GetModuleHandleW(wstring(path));

         //   }
         //   catch (...)
         //   {

         //   }

         //   if (plibrary != nullptr)
         //   {

         //      goto finished;

         //   }

         //   uiError = ::GetLastError();

         //   strError = "\n (6) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

         //   strMessage += strError;*/


         //finished:

         //   if (plibrary != nullptr)
         //   {

         //      strMessage = "node_library_touch Success touching " + path;

         //   }
         //   else
         //   {

         //      strMessage = "node_library_touch Failed touch " + strPath + strMessage;

         //   }

         //   informationf(strMessage + "\n\n");

         //   return (library_t*)plibrary;

         //}

// touc
///return operating_system_library_open(path, strMessage);

         library_t * dynamic_library::open(const ::file::path & pathParam, string & strMessage)
         {

            library_t * plibrary = nullptr;

            string strPath(pathParam);

            if (case_insensitive_ansi_ends(strPath, ".ilk"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strPath, ".pdb"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strPath, ".lib"))
            {

               return nullptr;

            }

            if (case_insensitive_ansi_ends(strPath, ".exp"))
            {

               return nullptr;

            }

            if (ansi_find_string(file_path_name(strPath), ".") == nullptr)
            {

               strPath += ".dll";

            }

            try
            {

               wstring wstr(strPath);

               plibrary = (::library_t *)(void *)::LoadPackagedLibrary(wstr, 0);

               DWORD dwLastError = ::GetLastError();

               string strLastError = ::windows::last_error_message(dwLastError);

               informationf(strLastError);

            }
            catch (...)
            {

            }

            if (plibrary == nullptr)
            {

               try
               {

                  wstring wstrPath("\\\\?\\" + strPath);

                  plibrary = (::library_t *)(void *)::LoadPackagedLibrary(wstrPath, 0);

               }
               catch (...)
               {

               }

            }

            if (plibrary == nullptr)
            {

               try
               {

                  auto pdirectorysystem = directory_system();

                  if (pdirectorysystem)
                  {

                     wstring wstrPath(directory_system()->module() / strPath);

                     plibrary = (::library_t *)(void *)::LoadPackagedLibrary(wstrPath, 0);

                  }

               }
               catch (...)
               {

               }

            }

            if (plibrary == nullptr)
            {

               try
               {

                  auto pdirectorysystem = directory_system();

                  if (pdirectorysystem)
                  {

                     wstring wstrPath(("\\\\?\\" + pdirectorysystem->module()) / strPath);

                     plibrary = (::library_t *)(void *)::LoadPackagedLibrary(wstrPath, 0);

                  }

               }
               catch (...)
               {

               }

            }

            //if (plibrary == nullptr)
            //{

            //   try
            //   {

            //      wstring wstr(directory_system()->module() / strPath);

            //      plibrary = ::LoadPackagedLibrary(wstr, 0);

            //   }
            //   catch (...)
            //   {

            //   }

            //}

            //if (plibrary == nullptr)
            //{

            //   try
            //   {

            //      wstring wstr(("\\\\?\\" + directory_system()->module()) / strPath);

            //      plibrary = ::LoadPackagedLibrary(wstr, 0);

            //   }
            //   catch (...)
            //   {

            //   }

            //}

            return plibrary;

         }


         library_t * dynamic_library::open_on_context(const ::file::path & path, string & strMessage)
         {
            /*      string str(scopedstr);
            if(str.find("..") >= 0)
            return false;
            if(str.find(":") >= 0)
            return false;
            if(str.find("\\\\") >= 0)
            return false;
            if(str[0] == '\\')
            return false;
            if(str[0] == '/')
            return false;
            #ifdef _M_X64
            //::SetDllDirectory(dir::install("stage\\x64") + "\\");
            #else
            //::SetDllDirectory(dir::install("stage\\x86") + "\\");
            #endif*/

            wstring wstr(path);

            return (library_t *)(void *)LoadPackagedLibrary(wstr, 0);

         }


         bool dynamic_library::close(library_t * plibrary)
         {

            if (plibrary == nullptr)
               return false;

            bool bOk = false;

            try
            {

               bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;

            }
            catch (...)
            {

            }

            return bOk;

         }


         void * dynamic_library::raw_get(library_t * plibrary, const ::scoped_string & scopedstrEntryName)
         {

            return ::GetProcAddress((HINSTANCE)plibrary, scopedstrEntryName);

         }



} // namespace universal_windows



namespace operating_system
{


   CLASS_DECL_ACME::operating_system::dynamic_library * new_dynamic_library()
   {

      return øraw_new::universal_windows::dynamic_library();

   }


} // namespace operating_system






