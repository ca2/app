#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/primitive/string/str.h"
#include "acme/_operating_system.h"
#include <io.h>


namespace windows
{


   CLASS_DECL_ACME bool get_alternate_path(wstring & wstr)
   {

      if (wstr.begins_ci(::str().windows_bbqb(wstr)))
      {

         return false;

      }

      if (wstr.begins_ci(::str().windows_bb(wstr)))
      {

         wstr = ::str().windows_bbqbunc(wstr) + wstr.Mid(1);

      }
      else
      {

         wstr = ::str().windows_bbqb(wstr) + wstr;

      }

      return true;

   }


   CLASS_DECL_ACME DWORD get_file_attributes(const char * path)
   {

      wstring wstr(path);

      DWORD dwFileAttributes = ::GetFileAttributesW(wstr);

      if (dwFileAttributes == INVALID_FILE_ATTRIBUTES)
      {

         if (::windows::get_alternate_path(wstr))
         {

            dwFileAttributes = GetFileAttributesW(wstr);

         }

      }

      return dwFileAttributes;

   }


} // namespace windows



void delete_file(const char* path)
{

   wstring wstrPath(path);

   if (!::DeleteFileW(wstrPath))
   {

      auto dwLastError = ::GetLastError();

      auto estatus = ::windows::last_error_status(dwLastError);

      throw ::exception(estatus);

   }

   //return ::success;

}


bool file_exists(const char* path)
{

   auto attributes = ::windows::get_file_attributes(path);

   if (attributes == INVALID_FILE_ATTRIBUTES)
   {

      return false;

   }

   if (attributes & FILE_ATTRIBUTE_DIRECTORY)
   {

      return false;

   }

   return true;

}


bool is_directory(const char* path)
{

   //#ifdef _UWP
   //
   //      //string str;
   //
   //      ////str = "\\\\?\\";
   //      ////str += path1;
   //
   //      //str = path1;
   //
   //      //str.ends_eat_ci("\\");
   //      //str.ends_eat_ci("/");
   //      //str.ends_eat_ci("\\");
   //      //str.ends_eat_ci("/");
   //
   //      u32 dwFileAttributes = ::windows_get_file_attributes(path1);
   //
   //      if (dwFileAttributes != INVALID_FILE_ATTRIBUTES)
   //      {
   //
   //         return dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
   //
   //      }
   //      else
   //      {
   //
   //         ::u32 dwLastError = ::GetLastError();
   //
   //         string strPrefix;
   //
   //         {
   //
   //            string strRelative = path1;
   //
   //            auto folderBase = winrt_folder(strRelative, strPrefix);
   //
   //            if (folderBase != nullptr)
   //            {
   //
   //               strRelative.replace("/", "\\");
   //
   //               strPrefix.replace("/", "\\");
   //
   //               ::str().begins_eat_ci(strRelative, strPrefix);
   //
   //               strRelative.trim("/\\");
   //
   //               //strPrefix.trim_right("/\\");
   //
   //               try
   //               {
   //
   //                  auto folder = folderBase->GetFolderAsync(strRelative);
   //
   //                  if (folder != nullptr)
   //                  {
   //
   //                     return true;
   //
   //                  }
   //
   //               }
   //               catch (...)
   //               {
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //         return false;
   //
   //         //auto folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path1));
   //
   //         //bool bOk = folder != nullptr;
   //
   //         //if (!bOk)
   //         //{
   //
   //         //   set_last_error(dwLastError);
   //
   //         //}
   //
   //         //if (bOk)
   //         //{
   //
   //         //   return true;
   //
   //         //}
   //
   //         //return bOk;
   //
   //      }
   //
   //
   //#elif defined(WINDOWS_DESKTOP)

         //auto dwFileAttributes = ::windows_get_file_attributes(path1);

   wstring wstrPath(path);

   auto dwFileAttributes = ::GetFileAttributesW(wstrPath);

   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || !(dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
   {

      return false;

   }

   return true;

   //#else
   //
   //      // dedicaverse stat -> Sir And Arthur - Cesar Serenato
   //
   //      return is_dir(path1);
   //
   //#endif

}


void create_directory(const char* path)
{

   wstring wstr;

   if (file_path_is_absolute(path))
   {

      wstr = L"\\\\?\\" + wstring(path);

   }
   else
   {

      wstr = path;

   }

   if (!::CreateDirectoryW(wstr, nullptr))
   {

      auto lastError = ::GetLastError();

      if (lastError == ERROR_ALREADY_EXISTS)
      {

         return;

      }

      if (::windows::get_alternate_path(wstr))
      {

         if (!::CreateDirectoryW(wstr, nullptr))
         {

            auto lastError = ::GetLastError();

            if (lastError == ERROR_ALREADY_EXISTS)
            {

               return;

            }

            auto estatus = ::windows::last_error_status(lastError);

            string strDetails;

            strDetails.format("Failed to create directory (2) \"%s\"", string(wstr).c_str());

            throw ::exception(estatus, nullptr, strDetails);

         }

      }
      else
      {

         auto estatus = ::windows::last_error_status(lastError);

         string strDetails;

         strDetails.format("Failed to create directory (1) \"%s\"", string(wstr).c_str());

         throw ::exception(estatus, nullptr, strDetails);

      }

   }

   //return true;

}


void erase_directory(const char* path)
{

   

   wstring wstr;

   if (file_path_is_absolute(path))
   {

      wstr = L"\\\\?\\" + wstring(path);

   }
   else
   {

      wstr = path;

   }

   if (!::RemoveDirectoryW(wstr))
   {

      auto lastError = ::GetLastError();

      auto estatus = ::windows::last_error_status(lastError);

      throw ::exception(estatus);

   }

}





namespace windows
{


   wstring CLASS_DECL_ACME get_file_path_root(const wstring & wstrPath)
   {

      wstring wstrRoot;

      auto iLength = wstrPath.get_length();

      unichar * pszRoot = wstrRoot.get_string_buffer(iLength);

      wcsncpy(pszRoot, wstrPath.c_str(), iLength + 1);

      unichar * psz = pszRoot;

      for (; *psz != '\0'; psz = _wcsinc(psz))
      {

         // find first double slash and stop
         if (IsDirSep(psz[0]) && IsDirSep(psz[1]))
         {

            break;

         }

      }

      if (*psz != '\0')
      {

         // it is a UNC name, find second slash past '\\'
         ASSERT(IsDirSep(psz[0]));

         ASSERT(IsDirSep(psz[1]));

         psz += 2;

         while (*psz != '\0' && (!IsDirSep(*psz)))
         {

            psz = _wcsinc(psz);

         }

         if (*psz != '\0')
         {

            psz = _wcsinc(psz);

         }

         while (*psz != '\0' && (!IsDirSep(*psz)))
         {

            psz = _wcsinc(psz);

         }

         // terminate it just after the UNC root (ie. '\\server\share\')
         if (*psz != '\0')
         {

            psz[1] = '\0';

         }

      }
      else
      {

         // not a UNC, look for just the first slash
         psz = pszRoot;

         while (*psz != '\0' && (!IsDirSep(*psz)))
         {

            psz = _wcsinc(psz);

         }

         // terminate it just after root (ie. 'x:\')
         if (*psz != '\0')
         {

            psz[1] = '\0';

         }

      }

      return ::move(wstrRoot);

   }


} // namespace windows


CLASS_DECL_ACME bool ensure_file_size_handle(HANDLE h, u64 iSize)
{

   LARGE_INTEGER largeinteger{};

   if (!::GetFileSizeEx(h, &largeinteger))
   {

      return false;

   }

   auto size = largeinteger.QuadPart;

   if (size != iSize)
   {

      largeinteger.QuadPart = iSize;

      if (!::SetFilePointerEx(h, largeinteger, nullptr, SEEK_SET))
      {

         return false;

      }

      if (!::SetEndOfFile(h))
      {

         return false;

      }

   }

   return true;

}


//CLASS_DECL_ACME bool ensure_file_size_handle(HANDLE h, u64 iSize)
//{
//
//   DWORD dwHi;
//
//   DWORD dwLo = GetFileSize(h, &dwHi);
//
//   if (((u64)dwLo | ((u64)dwHi << 32)) != iSize)
//   {
//
//      LONG l = (iSize >> 32) & 0xffffffff;
//
//      if (SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET) != (DWORD)(iSize & 0xffffffff))
//      {
//
//         return false;
//
//      }
//
//      if (l != ((iSize >> 32) & 0xffffffff))
//      {
//
//         return false;
//
//      }
//
//      if (!SetEndOfFile(h))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return 1;
//
//}



