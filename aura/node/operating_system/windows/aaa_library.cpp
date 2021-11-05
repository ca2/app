#include "framework.h"


//void * __node_library_open(const ::string & pszPath, string & strMessage)
//{
//
//   strMessage.Empty();
//
//   string strError;
//
//   string strPath(pszPath);
//
//   u32 uiError;
//
//   void * plibrary = nullptr;
//
//   if (ansi_ends_ci(strPath, ".ilk"))
//   {
//
//      return false;
//
//   }
//
//   if(ansi_ends_ci(strPath,".pdb"))
//   {
//
//      return false;
//
//   }
//
//   if(ansi_ends_ci(strPath,".lib"))
//   {
//
//      return false;
//
//   }
//
//   if(ansi_ends_ci(strPath,".exp"))
//   {
//
//      return false;
//
//   }
//
//   if (strPath.find('.') < 0 || !m_psystem->m_pacmefile->exists(strPath))
//   {
//
//      strPath += ".dll";
//
//   }
//
//   ::file::path path;
//
//   path = strPath;
//
//   try
//   {
//
//      plibrary = ::LoadLibraryW(wstring(path));
//
//   }
//   catch(...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      FORMATTED_TRACE("Loaded Library (1) %s", strPath.c_str());
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (1) LoadLibraryW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = "\\\\?\\" + strPath;
//
//   try
//   {
//
//      plibrary = ::LoadLibraryW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (2) LoadLibraryW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = ::dir::ca2_module() / strPath;
//
//   try
//   {
//
//      plibrary = ::LoadLibraryW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (3) LoadLibraryW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = "\\\\?\\" + string(::dir::ca2_module() / strPath);
//
//   try
//   {
//
//      plibrary = ::LoadLibraryW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (4) LoadLibraryW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = ::dir::base_module() / strPath;
//
//   try
//   {
//
//      plibrary = ::LoadLibraryW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (5) LoadLibraryW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = "\\\\?\\" + string(::dir::base_module() / strPath);
//
//   try
//   {
//
//      plibrary = ::LoadLibraryW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (6) LoadLibraryW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//
//finished:
//
//   if (plibrary != nullptr)
//   {
//
//      strMessage = "node_library_open Success opening " + path;
//
//   }
//   else
//   {
//
//      strMessage = "node_library_open Failed opening " + strPath + strMessage;
//
//   }
//
//   ::output_debug_string(strMessage + "\n\n");
//
//   return plibrary;
//
//}


//void * __node_library_touch(const ::string & pszPath, string & strMessage)
//{
//
//   strMessage.Empty();
//
//   string strError;
//
//   string strPath(pszPath);
//
//   u32 uiError;
//
//   void * plibrary = nullptr;
//
//   if (ansi_ends_ci(strPath, ".ilk"))
//   {
//
//      return false;
//
//   }
//
//   if (ansi_ends_ci(strPath, ".pdb"))
//   {
//
//      return false;
//
//   }
//
//   if (ansi_ends_ci(strPath, ".lib"))
//   {
//
//      return false;
//
//   }
//
//   if (ansi_ends_ci(strPath, ".exp"))
//   {
//
//      return false;
//
//   }
//
//   if (ansi_find_string(file_path_name(strPath), ".") == nullptr)
//   {
//
//      strPath += ".dll";
//
//   }
//
//   ::output_debug_string("\n\nGoing to touch library (1) " + string(strPath) + "\n");
//
//   ::file::path path;
//
//   path = strPath;
//
//   try
//   {
//
//      plibrary = ::GetModuleHandleW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (1) GetModuleHandleW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = "\\\\?\\" + strPath;
//
//   try
//   {
//
//      plibrary = ::GetModuleHandleW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (2) GetModuleHandleW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = ::dir::ca2_module() / strPath;
//
//   try
//   {
//
//      plibrary = ::GetModuleHandleW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (3) GetModuleHandleW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = "\\\\?\\" + string(::dir::ca2_module() / strPath);
//
//   try
//   {
//
//      plibrary = ::GetModuleHandleW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (4) GetModuleHandleW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = ::dir::base_module() / strPath;
//
//   try
//   {
//
//      plibrary = ::GetModuleHandleW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (5) GetModuleHandleW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//   path = "\\\\?\\" + string(::dir::base_module() / strPath);
//
//   try
//   {
//
//      plibrary = ::GetModuleHandleW(wstring(path));
//
//   }
//   catch (...)
//   {
//
//   }
//
//   if (plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   uiError = ::get_last_error();
//
//   strError = "\n (6) GetModuleHandleW " + path + " failed with (" + __string(uiError) + ") " + get_error_string(uiError);
//
//   strMessage += strError;
//
//
//finished:
//
//   if (plibrary != nullptr)
//   {
//
//      strMessage = "node_library_touch Success touching " + path;
//
//   }
//   else
//   {
//
//      strMessage = "node_library_touch Failed touch " + strPath + strMessage;
//
//   }
//
//   ::output_debug_string(strMessage + "\n\n");
//
//   return plibrary;
//
//}
//
//bool __node_library_close(void * plibrary)
//{
//
//   if(plibrary == nullptr)
//      return false;
//
//   bool bOk = false;
////#ifndef MEMDLEAK
//   try
//   {
//
//      bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;
//
//   }
//   catch(...)
//   {
//
//   }
////#endif
//   return bOk;
//
//}
//
//
//void * __node_library_open_ca2(const ::string & psz, string & strMessage)
//{
//
//   void * p = LoadLibraryW(wstring(psz));
//
//   if (p != nullptr)
//   {
//
//      strMessage = "Loaded Library (2) " + string(psz);
//
//   }
//   else
//   {
//
//      u32 uiError = get_last_error();
//
//      strMessage = "Failed to Load Library (2) " + string(psz) + " with error (" + __string(uiError) +
//                   ")" + get_error_string(uiError);
//
//   }
//
//   ::output_debug_string("\n" + strMessage + "\n\n");
//
//   return p;
//
//}
//
//void * __node_library_raw_get(void * plibrary, const ::string & pszEntryName)
//{
//
//   return ::GetProcAddress((HINSTANCE)plibrary,pszEntryName);
//
//}


