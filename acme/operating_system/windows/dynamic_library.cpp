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

#pragma comment(lib, "shlwapi.lib")
namespace windows
{


   dynamic_library::dynamic_library()
   {

   }


   dynamic_library::~dynamic_library()
   {


   }


   ::file::path dynamic_library::module_path(library_t* plibrary)
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


   ::library_t* dynamic_library::module_by_name(const ::scoped_string& scopedstrName)
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

      auto plibrary = (library_t*)hmodule;

      return plibrary;

   }


   ::library_t* dynamic_library::module_by_path(const ::file::path& path)
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

      HMODULE hmodule = ::GetModuleHandleW(windowspath.extended_path());

      auto plibrary = (library_t*)hmodule;

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


   library_t* dynamic_library::open(const ::file::path& pathParam, string& strMessage)
   {

      strMessage.empty();

      string strError;

      string strPath(pathParam);

      unsigned int uiError;

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

      if ((!strPath.contains('.') || !::PathFileExistsW(wstring(strPath)))
         && !strPath.case_insensitive_ends(".dll"))
      {

         strPath += ".dll";

      }

      ::file::path path;

      path = strPath;

      try
      {

         wstring wstr(path);

         auto pwsz = wstr.c_str();

         plibrary = ::LoadLibraryW(pwsz);

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

         unsigned int uiError = GetLastError();

         strMessage = "Failed to Load Library (2) " + string(path) + " with error (" + ::as_string(uiError) +
            ")" + ::windows::last_error_message(uiError);

      }

      information("\n" + strMessage + "\n\n");

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


} // namespace windows


namespace operating_system
{

   
   CLASS_DECL_ACME::operating_system::dynamic_library* new_dynamic_library()
   {

      return øraw_new ::windows::dynamic_library();

   }


} // namespace operating_system




