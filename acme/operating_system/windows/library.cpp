#include "framework.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/platform/tracer.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows_common/_string.h"


void * __node_library_open(const char * pszPath, string & strMessage)
{

   strMessage.Empty();

   string strError;

   string strPath(pszPath);

   u32 uiError;

   void * plibrary = nullptr;

   if (ansi_ends_ci(strPath, ".ilk")
      || ansi_ends_ci(strPath, ".pdb")
      || ansi_ends_ci(strPath, ".lib")
      || ansi_ends_ci(strPath, ".exp"))
   {

      string strMessage;

      strMessage.format("Not going to try to load library. Invalid file extension in name : \"%s\"", pszPath);

      ERROR(strMessage);

      throw library_not_loaded(strMessage);

   }

   if (strPath.find('.') < 0 || !::PathFileExistsW(wstring(strPath)))
   {

      strPath += ".dll";

   }

   ::file::path path;

   path = strPath;

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch(...)
   {


   }

   if (plibrary != nullptr)
   {

      //FORMATTED_TRACE("Loaded Library (1) %s", strPath.c_str());

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (1) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

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

   strError = "\n (2) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

   path = ::dir_ca2_module() / strPath;

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch (...)
   {

   }

   uiError = ::GetLastError();

   strError = "\n (3) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir_ca2_module() / strPath);

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

   strError = "\n (4) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

   path = ::dir_base_module() / strPath;

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

   strError = "\n (5) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir_base_module() / strPath);

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

   strError = "\n (6) LoadLibraryW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

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


void * __node_library_touch(const char * pszPath, string & strMessage)
{

   strMessage.Empty();

   string strError;

   string strPath(pszPath);

   u32 uiError;

   void * plibrary = nullptr;

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

   strError = "\n (1) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

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

   strError = "\n (2) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

   path = ::dir_ca2_module() / strPath;

   try
   {

      plibrary = ::GetModuleHandleW(wstring(path));

   }
   catch (...)
   {

   }

   uiError = ::GetLastError();

   strError = "\n (3) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir_ca2_module() / strPath);

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

   strError = "\n (4) GetModuleHandleW " + path + " failed with (" + as_string(uiError) + ") " + ::windows::last_error_message(uiError);

   strMessage += strError;

   path = ::dir_base_module() / strPath;

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

   strMessage += strError;


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

bool __node_library_close(void * plibrary)
{

   if(plibrary == nullptr)
      return false;

   bool bOk = false;
//#ifndef MEMDLEAK
   try
   {

      bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;

   }
   catch(...)
   {

   }
//#endif
   return bOk;

}


void * __node_library_open_ca2(const char * psz, string & strMessage)
{

   void * p = LoadLibraryW(wstring(psz));

   if (p != nullptr)
   {

      strMessage = "Loaded Library (2) " + string(psz);

   }
   else
   {

      u32 uiError = GetLastError();

      strMessage = "Failed to Load Library (2) " + string(psz) + " with error (" + as_string(uiError) +
                   ")" + ::windows::last_error_message(uiError);

   }

   ::output_debug_string("\n" + strMessage + "\n\n");

   return p;

}

void * __node_library_raw_get(void * plibrary,const char * pszEntryName)
{

   return ::GetProcAddress((HINSTANCE)plibrary,pszEntryName);

}


