// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/windows/library.cpp by
// camilo on 2024-06-02 21:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/platform/application.h"
#include "acme/_operating_system.h"


namespace windows
{


   namespace nano
   {


      namespace dynamic_library
      {


         dynamic_library::dynamic_library()
         {

         }


         dynamic_library::~dynamic_library()
         {


         }


         bool dynamic_library::is_loaded(const char* pszPath)
         {

            return ::GetModuleHandleW(wstring(pszPath)) != nullptr;

         }


         library_t* dynamic_library::touch(const ::file::path& pathParam, string& strMessage)
         {

            strMessage.empty();

            string strError;

            string strPath(pathParam);

            u32 uiError;

            void* plibrary = nullptr;

            if (ansi_ends_ci(strPath, ".ilk"))
            {

               return nullptr;

            }

            if (ansi_ends_ci(strPath, ".pdb"))
            {

               return nullptr;

            }

            if (ansi_ends_ci(strPath, ".lib"))
            {

               return nullptr;

            }

            if (ansi_ends_ci(strPath, ".exp"))
            {

               return nullptr;

            }

            if (ansi_find_string(file_path_name(strPath), ".") == nullptr)
            {

               strPath += ".dll";

            }

            ::acme::get()->platform()->informationf("\n\nGoing to touch library (1) " + string(strPath) + "\n");

            ::file::path path;

            path = strPath;

            try
            {

               plibrary = ::GetModuleHandleW(wstring(path));

            }
            catch (...)
            {

            }

            if (plibrary != nullptr)
            {

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (1) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            path = "\\\\?\\" + strPath;

            try
            {

               plibrary = ::GetModuleHandleW(wstring(path));

            }
            catch (...)
            {

            }

            if (plibrary != nullptr)
            {

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (2) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            path = application()->get_module_folder() / strPath;

            try
            {

               plibrary = ::GetModuleHandleW(wstring(path));

            }
            catch (...)
            {

            }

            uiError = ::GetLastError();

            strError = "\n (3) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            path = "\\\\?\\" + string(application()->get_module_folder() / strPath);

            try
            {

               plibrary = ::GetModuleHandleW(wstring(path));

            }
            catch (...)
            {

            }

            if (plibrary != nullptr)
            {

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (4) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            /*path = ::dir_base_module() / strPath;

            try
            {

               plibrary = ::GetModuleHandleW(wstring(path));

            }
            catch (...)
            {

            }

            if (plibrary != nullptr)
            {

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (5) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            path = "\\\\?\\" + string(::dir_base_module() / strPath);

            try
            {

               plibrary = ::GetModuleHandleW(wstring(path));

            }
            catch (...)
            {

            }

            if (plibrary != nullptr)
            {

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (6) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;*/


         finished:

            if (plibrary != nullptr)
            {

               strMessage = "node_library_touch Success touching " + path;

            }
            else
            {

               strMessage = "node_library_touch Failed touch " + strPath + strMessage;

            }

            ::acme::get()->platform()->informationf(strMessage + "\n\n");

            return (library_t*)plibrary;

         }


         library_t* dynamic_library::open(const ::file::path& pathParam, string& strMessage)
         {

            strMessage.empty();

            string strError;

            string strPath(pathParam);

            u32 uiError;

            void* plibrary = nullptr;

            if (strPath.case_insensitive_ends(".ilk")
               || strPath.case_insensitive_ends(".pdb")
               || strPath.case_insensitive_ends(".lib")
               || strPath.case_insensitive_ends(".exp"))
            {

               string strMessage;

               strMessage.formatf("Not going to try to load library. Invalid file extension in name : \"%s\"", pathParam.c_str());

               error() << strMessage;

               throw library_not_loaded(strMessage);

            }

            if (!strPath.contains('.') || !::PathFileExistsW(wstring(strPath)))
            {

               strPath += ".dll";

            }

            ::file::path path;

            path = strPath;

            try
            {

               plibrary = ::LoadLibraryW(wstring(path));

            }
            catch (...)
            {


            }

            if (plibrary != nullptr)
            {

               //informationf("Loaded Library (1) %s", strPath.c_str());

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (1) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            path = "\\\\?\\" + strPath;

            try
            {

               plibrary = ::LoadLibraryW(wstring(path));

            }
            catch (...)
            {

            }

            if (plibrary != nullptr)
            {

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (2) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            path = application()->get_module_folder() / strPath;

            try
            {

               plibrary = ::LoadLibraryW(wstring(path));

            }
            catch (...)
            {

            }

            uiError = ::GetLastError();

            strError = "\n (3) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            strMessage += strError;

            path = "\\\\?\\" + string(application()->get_module_folder() / strPath);

            try
            {

               plibrary = ::LoadLibraryW(wstring(path));

            }
            catch (...)
            {

            }

            if (plibrary != nullptr)
            {

               goto finished;

            }

            uiError = ::GetLastError();

            strError = "\n (4) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            //strMessage += strError;

            //path = ::dir_base_module() / strPath;

            //try
            //{

            //   plibrary = ::LoadLibraryW(wstring(path));

            //}
            //catch (...)
            //{

            //}

            //if (plibrary != nullptr)
            //{

            //   goto finished;

            //}

            //uiError = ::GetLastError();

            //strError = "\n (5) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            //strMessage += strError;

            //path = "\\\\?\\" + string(::dir_base_module() / strPath);

            //try
            //{

            //   plibrary = ::LoadLibraryW(wstring(path));

            //}
            //catch (...)
            //{

            //}

            //if (plibrary != nullptr)
            //{

            //   goto finished;

            //}

            //uiError = ::GetLastError();

            //strError = "\n (6) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

            //strMessage += strError;

         finished:

            if (::is_null(plibrary))
            {

               strMessage = "node_library_open Failed opening " + strPath;

               throw library_not_loaded(strMessage, strError);

               return nullptr;

            }

            strMessage = "node_library_open Success opening " + path;

            information() << strMessage;

            return (library_t*)plibrary;
         }


         library_t* dynamic_library::open_on_context(const ::file::path& path, string& strMessage)
         {

            void* p = LoadLibraryW(wstring(path));

            if (p != nullptr)
            {

               strMessage = "Loaded Library (2) " + string(path);

            }
            else
            {

               u32 uiError = GetLastError();

               strMessage = "Failed to Load Library (2) " + string(path) + " with error (" + ::as_string(uiError) +
                  ")" + ::windows::last_error_message(uiError);

            }

            ::acme::get()->platform()->informationf("\n" + strMessage + "\n\n");

            return (library_t*)p;

         }


         bool dynamic_library::close(library_t* plibrary)
         {

            if (plibrary == nullptr)
               return false;

            bool bOk = false;
            //#ifndef MEMDLEAK
#if !REFERENCING_DEBUGGING

            try
            {

               bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;

            }
            catch (...)
            {

            }
#endif
            //#endif
            return bOk;

         }


         void* dynamic_library::raw_get(library_t* plibrary, const ::scoped_string& scopedstrEntryName)
         {

            return ::GetProcAddress((HINSTANCE)plibrary, scopedstrEntryName);


         }


      } // namespace dynamic_library


   } // namespace nano


} // namespace windows



