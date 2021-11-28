#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/operating_system.h"


CLASS_DECL_ACME bool windows_get_alternate_path(wstring& wstr);


::e_status create_directory(const char* path)
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

      if (windows_get_alternate_path(wstr))
      {

         if (!::CreateDirectoryW(wstr, nullptr))
         {

            return error_failed;

         }

      }
      else
      {

         return error_failed;

      }

   }

   return true;

}


::e_status is_directory(const char* path)
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
   //               ::str::begins_eat_ci(strRelative, strPrefix);
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



