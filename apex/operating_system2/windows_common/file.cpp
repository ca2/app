#include "framework.h"
#include "apex/operating_system.h"


//#ifdef UNIVERSAL_WINDOWS
//CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder^ winrt_folder(string& strPath, string& strPrefix);
//#endif


//CLASS_DECL_APEX ::u32 windows_get_file_attributes(const ::file::path & path)
//{
//
//   wstring wstr(path);
//
//   u32 dwFileAttributes = ::GetFileAttributesW(wstr);
//
//   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES)
//   {
//
//      if (windows_get_alternate_path(wstr))
//      {
//
//         dwFileAttributes = GetFileAttributesW(wstr);
//
//      }
//
//   }
//
//   return dwFileAttributes;
//
//}


//CLASS_DECL_APEX bool windows_create_directory(const ::file::path & path, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
//{
//
//   wstring wstr(path);
//
//
//   if (::CreateDirectoryW(wstr, lpSecurityAttributes))
//   {
//
//      return true;
//
//   }
//
//   if (windows_get_alternate_path(wstr))
//   {
//
//      if (::CreateDirectoryW(wstr, lpSecurityAttributes))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}


//::file::path file::app_module()
//{
//
//   wstring wstrPath(get_buffer, MAX_PATH * 16);
//
//   if (!GetModuleFileNameW(nullptr, wstrPath, (::u32)wstrPath.get_length()))
//   {
//
//      return "";
//
//   }
//
//   return wstrPath.release_buffer();
//
//}


////extern "C"
//CLASS_DECL_APEX int_bool file_copy_dup(const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrSrc, int_bool bOverwrite)
//{
//
//   string strNew(pszNew);
//
//   if (strNew.length() >= MAX_PATH)
//   {
//
//      strNew = "\\\\.\\" + strNew;
//
//   }
//
//   string strSrc(pszSrc);
//
//   if (strSrc.length() >= MAX_PATH)
//   {
//
//      strSrc = "\\\\.\\" + strSrc;
//
//   }
//
//   wstring wstrNew(strNew);
//
//   wstring wstrSrc(strSrc);
//
//   //return ::CopyFileExW(wstrSrc,wstrNew, nullptr, nullptr, nullptr, COPY_FILE_NO_BUFFERING | (bOverwrite ? 0 : COPY_FILE_FAIL_IF_EXISTS)) ? true : false;
//   return ::CopyFileExW(wstrSrc, wstrNew, nullptr, nullptr, nullptr, (bOverwrite ? 0 : COPY_FILE_FAIL_IF_EXISTS)) ? true : false;
//
//}


//CLASS_DECL_APEX ::file::path get_final_path(const ::file::path& path)
//{
//
//   wstring wstr(path);
//
//   HANDLE hfile = INVALID_HANDLE_VALUE;
//
//   try
//   {
//
//      if (         auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->is(path))
//      {
//
//         hfile = create_file(path,
//            GENERIC_READ,          // open for reading
//            FILE_SHARE_READ,       // share for reading
//            nullptr,                  // default security
//            OPEN_EXISTING,         // existing file only
//            FILE_ATTRIBUTE_NORMAL, // normal file
//            nullptr);                 // no attr. template
//
//      }
//      else
//      {
//
//         hfile = create_file(path,
//            FILE_LIST_DIRECTORY,          // open for reading
//            FILE_SHARE_READ,       // share for reading
//            nullptr,                  // default security
//            OPEN_EXISTING,         // existing file only
//            FILE_ATTRIBUTE_NORMAL, // normal file
//            nullptr);                 // no attr. template
//
//      }
//
//      if (hfile == INVALID_HANDLE_VALUE)
//      {
//
//         return wstr;
//
//      }
//
//      ::u32 dw = GetFinalPathNameByHandleW(hfile, nullptr, 0, VOLUME_NAME_DOS);
//
//      if (dw > 0)
//      {
//
//         wstring wstr2;
//
//         auto* pwsz = wstr2.get_buffer(dw + 1);
//
//         dw = GetFinalPathNameByHandleW(hfile, pwsz, dw + 1, VOLUME_NAME_DOS);
//
//         if (dw > 0)
//         {
//
//            wstr2.release_buffer();
//
//            wstr = wstr2;
//
//         }
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//   ::CloseHandle(hfile);
//
//   return wstr;
//
//}


//CLASS_DECL_APEX  bool __node_further_file_is_equal(const ::file::path& path1, const ::file::path& path2)
//{
//
//   ::file::path pathFull1 = get_final_path(path1);
//
//   ::file::path pathFull2 = get_final_path(path2);
//
//   return pathFull1.has_char() && pathFull1.case_insensitive_order(pathFull2) == 0;
//
//}


//CLASS_DECL_APEX int_bool acmepath()->is_file_or_dir(const ::file::path & path, ::file::enum_type* petype)
//{
//
//   auto dwFileAttributes = windows_get_file_attributes(path);
//
//   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES)
//   {
//
//#ifdef UNIVERSAL_WINDOWS
//
//      ::u32 dwLastError = ::get_last_error();
//
//      string strPrefix;
//
//      string strRelative = path;
//
//      auto folderBase = winrt_folder(strRelative, strPrefix);
//
//      if (folderBase != nullptr)
//      {
//
//         strRelative.replace("/", "\\");
//
//         strPrefix.replace("/", "\\");
//
//         strRelative.case_insensitive_begins_eat(strPrefix);
//
//         strRelative.trim("/\\");
//
//         //strPrefix.trim_right("/\\");
//
//         try
//         {
//
//            auto item = ::wait(folderBase->GetItemAsync(strRelative));
//
//            if (item != nullptr)
//            {
//
//               if (item->IsOfType(::winrt::Windows::Storage::StorageItemTypes::Folder))
//               {
//
//                  if (is_set(petype))
//                  {
//
//                     *petype = ::file::e_type_folder;
//
//                  }
//
//                  return true;
//
//               }
//               else if (item->IsOfType(::winrt::Windows::Storage::StorageItemTypes::File))
//               {
//
//                  if (is_set(petype))
//                  {
//
//                     *petype = ::file::e_type_file;
//
//                  }
//
//                  return true;
//
//               }
//
//               return false;
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//#endif
//
//      if (is_set(petype))
//      {
//
//         *petype = ::file::e_type_none;
//
//      }
//
//      return false;
//
//   }
//
//   if (is_set(petype))
//   {
//
//      if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
//      {
//
//         *petype = ::file::e_type_folder;
//
//      }
//      else
//      {
//
//         *petype = ::file::e_type_file;
//
//      }
//
//   }
//
//   return true;
//
//}




