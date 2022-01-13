#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/operating_system.h"


CLASS_DECL_ACME bool windows_get_alternate_path(wstring& wstr)
{

   if (wstr.begins_ci(str::windows_bbqb(wstr)))
   {

      return false;

   }

   if (wstr.begins_ci(str::windows_bb(wstr)))
   {

      wstr = str::windows_bbqbunc(wstr) + wstr.Mid(1);

   }
   else
   {

      wstr = str::windows_bbqb(wstr) + wstr;

   }

   return true;

}


CLASS_DECL_ACME::u32 windows_get_file_attributes(const char* path)
{

   wstring wstr(path);

   u32 dwFileAttributes = ::GetFileAttributesW(wstr);

   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES)
   {

      if (windows_get_alternate_path(wstr))
      {

         dwFileAttributes = GetFileAttributesW(wstr);

      }

   }

   return dwFileAttributes;

}


void delete_file(const char* path)
{

   wstring wstrPath(path);

   if (!::DeleteFileW(wstrPath))
   {

      auto dwLastError = ::GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      throw_status(estatus);

   }

   //return ::success;

}


bool file_exists(const char* path)
{

   auto attributes = windows_get_file_attributes(path);

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

      if (windows_get_alternate_path(wstr))
      {

         if (!::CreateDirectoryW(wstr, nullptr))
         {

            auto lastError = ::GetLastError();

            auto estatus = last_error_to_status(lastError);

            throw_status(estatus);

         }

      }
      else
      {

         auto estatus = last_error_to_status(lastError);

         throw_status(estatus);


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

      auto estatus = last_error_to_status(lastError);

      throw_status(estatus);

   }

}



