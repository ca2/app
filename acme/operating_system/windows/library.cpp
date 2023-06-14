#include "framework.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/platform/tracer.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows_common/_string.h"


namespace acme
{


   void* system::operating_system_library_open(const ::file::path & pathParam, string& strMessage)
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

         strMessage.format("Not going to try to load library. Invalid file extension in name : \"%s\"", pathParam.c_str());

         ERROR(strMessage);

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

         //information("Loaded Library (1) %s", strPath.c_str());

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

      path = acmeapplication()->get_module_folder() / strPath;

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

      path = "\\\\?\\" + string(acmeapplication()->get_module_folder() / strPath);

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

      ::output_debug_string(strMessage + "\n\n");

      return plibrary;

   }


   void* system::operating_system_library_touch(const ::file::path & pathParam, string& strMessage)
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

      ::output_debug_string("\n\nGoing to touch library (1) " + string(strPath) + "\n");

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

      path = acmeapplication()->get_module_folder() / strPath;

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

      path = "\\\\?\\" + string(acmeapplication()->get_module_folder() / strPath);

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

      ::output_debug_string(strMessage + "\n\n");

      return plibrary;

   }

   bool system::operating_system_library_close(void* plibrary)
   {

      if (plibrary == nullptr)
         return false;

      bool bOk = false;
      //#ifndef MEMDLEAK
      try
      {

         bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;

      }
      catch (...)
      {

      }
      //#endif
      return bOk;

   }


   void* system::operating_system_library_open_ca2(const ::file::path & pathParam, string& strMessage)
   {

      void* p = LoadLibraryW(wstring(pathParam));

      if (p != nullptr)
      {

         strMessage = "Loaded Library (2) " + string(pathParam);

      }
      else
      {

         u32 uiError = GetLastError();

         strMessage = "Failed to Load Library (2) " + string(pathParam) + " with error (" + ::as_string(uiError) +
            ")" + ::windows::last_error_message(uiError);

      }

      ::output_debug_string("\n" + strMessage + "\n\n");

      return p;

   }

   void* system::operating_system_library_raw_get(void* plibrary, const ::scoped_string & scopedstrEntryName)
   {

      return ::GetProcAddress((HINSTANCE)plibrary, scopedstrEntryName);

   }
   
   
} // namespace acme



