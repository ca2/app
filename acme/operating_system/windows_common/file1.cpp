#include "framework.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/primitive/string/str.h"
#include "acme/_operating_system.h"
#include <io.h>


namespace windows
{


   // CLASS_DECL_ACME bool alternate_path(::windows_path & windowspath)
   // {

   //    if (windowspath.case_insensitive_begins(::str::windows_bbqb(wstr)))
   //    {

   //       return false;

   //    }

   //    if (wstr.case_insensitive_begins(::str::windows_bb(wstr)))
   //    {

   //       wstr = ::str::windows_bbqbunc(wstr) + wstr.substr(1);

   //    }
   //    else
   //    {

   //       wstr = ::str::windows_bbqb(wstr) + wstr;

   //    }

   //    return true;

   // }


   CLASS_DECL_ACME DWORD _get_file_attributes(const ::file::path & path)
   {

      ::windows_path windowspath = path.windows_path();

      auto attributes = ::GetFileAttributesW(windowspath);

      return attributes;

   }


   CLASS_DECL_ACME DWORD get_file_attributes(const ::file::path & path)
   {

      auto attributes = _get_file_attributes(path);

      if (attributes == INVALID_FILE_ATTRIBUTES)
      {

         throw_last_error_exception();

      }

      return attributes;

   }


   CLASS_DECL_ACME int_bool is_win32_accessible(DWORD dwFileAttributes, DWORD dwLastError)
   {

      if (dwFileAttributes == INVALID_FILE_ATTRIBUTES)
      {

         if (dwLastError == ERROR_PATH_NOT_FOUND)
         {

            // Path would be accessible...

            // Parent Folder is not folder...

            return true;

         }
         else if (dwLastError == ERROR_FILE_NOT_FOUND)
         {

            // Path would be accessible...

            // Parent folder exists...

            return true;

         }

         return false;

      }
      else
      {

         return true;

      }


   }

   
   CLASS_DECL_ACME int_bool is_win32_accessible(const ::file::path & path)
   {
   
     auto dwFileAttributes = ::windows::_get_file_attributes(path);

     if(dwFileAttributes == INVALID_FILE_ATTRIBUTES)
     {

         auto dwLastError = ::GetLastError();

         return is_win32_accessible(dwFileAttributes, dwLastError);

     }
     else
     {

      return true;

     }

   }


   CLASS_DECL_ACME void set_file_attributes(const ::file::path & path, DWORD dwAttributes)
   {

      ::windows_path windowspath = path.windows_path();

      if (::SetFileAttributesW(windowspath, dwAttributes))
      {

         throw_last_error_exception();

      }

   }


} // namespace windows


void delete_file(const ::file::path & path)
{

   ::windows_path windowspath = path.windows_path();

   if (!::DeleteFileW(windowspath))
   {

      throw_last_error_exception();

   }

}


CLASS_DECL_ACME ::file::enum_type safe_get_file_system_item_type(const ::file::path & path)
{

   auto attributes = ::windows::_get_file_attributes(path);

   if (attributes == INVALID_FILE_ATTRIBUTES)
   {

      auto lasterror = ::GetLastError();

      if (lasterror == ERROR_FILE_NOT_FOUND || lasterror == ERROR_PATH_NOT_FOUND)
      {

         return ::file::e_type_doesnt_exist;

      }

      //throw_last_error_exception(nullptr, lasterror);

      return ::file::e_type_doesnt_exist;

   }

   if (attributes & FILE_ATTRIBUTE_DIRECTORY)
   {

      return ::file::e_type_folder;

   }

   return ::file::e_type_file;

}


CLASS_DECL_ACME::file::enum_type get_file_system_item_type(const ::file::path & path)
{

   auto attributes = ::windows::_get_file_attributes(path);

   if (attributes == INVALID_FILE_ATTRIBUTES)
   {

      auto lasterror = ::GetLastError();

      if (lasterror == ERROR_FILE_NOT_FOUND || lasterror == ERROR_PATH_NOT_FOUND)
      {

         return ::file::e_type_doesnt_exist;

      }

      throw_last_error_exception(nullptr, lasterror);

      return ::file::e_type_doesnt_exist;

   }

   if (attributes & FILE_ATTRIBUTE_DIRECTORY)
   {

      return ::file::e_type_folder;

   }

   return ::file::e_type_file;

}


bool safe_file_exists(const ::file::path & path)
{

   auto attributes = ::windows::_get_file_attributes(path);

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


bool file_exists(const ::file::path & path)
{

   auto attributes = ::windows::_get_file_attributes(path);

   if (attributes == INVALID_FILE_ATTRIBUTES)
   {

      auto lasterror = ::GetLastError();

      if (lasterror == ERROR_FILE_NOT_FOUND || lasterror == ERROR_PATH_NOT_FOUND)
      {

         return false;

      }

      throw_last_error_exception(nullptr, lasterror);

      return false;

   }

   if (attributes & FILE_ATTRIBUTE_DIRECTORY)
   {

      return false;

   }

   return true;

}


bool safe_is_directory(const ::file::path & path)
{

   auto attributes = ::windows::_get_file_attributes(path);

   if (attributes == INVALID_FILE_ATTRIBUTES)
   {

      return false;

   }

   if (!(attributes & FILE_ATTRIBUTE_DIRECTORY))
   {

      return false;

   }

   return true;

}


bool is_directory(const ::file::path & path)
{

   auto attributes = ::windows::_get_file_attributes(path);

   if (attributes == INVALID_FILE_ATTRIBUTES)
   {
      
      auto lasterror = ::GetLastError();

      if (lasterror == ERROR_FILE_NOT_FOUND || lasterror == ERROR_PATH_NOT_FOUND)
      {

         return false;

      }

      throw_last_error_exception(nullptr, lasterror);

      return false;

   }
   
   if(!(attributes & FILE_ATTRIBUTE_DIRECTORY))
   {

      return false;

   }

   return true;

}


void create_directory(const ::file::path & path)
{

   auto strWindowsPath = path.windows_path();

   ::windows_path windowspath = strWindowsPath;

   if (!::CreateDirectoryW(windowspath, nullptr))
   {

      auto lasterror = ::GetLastError();

      if (lasterror == ERROR_ALREADY_EXISTS)
      {

         return;

      }

      string strDetails;

      strDetails.format("Failed to create directory (2) \"%s\"", strWindowsPath.c_str());

      throw_last_error_exception(strDetails, lasterror);

      //if (::windows::alternate_path(windowspath))
      //{

      //   if (!::CreateDirectoryW(windowspath, nullptr))
      //   {

         /*   auto lasterror = ::GetLastError();

            if (lasterror == ERROR_ALREADY_EXISTS)
            {

               return;

            }

            auto estatus = ::windows::last_error_status(lasterror);

            string strDetails;

            strDetails.format("Failed to create directory (2) \"%s\"", string(wstr).c_str());

            throw ::exception(estatus, strDetails);

         }*/

      //}
      //else
      //{

         //auto estatus = ::windows::last_error_status(lasterror);

         //string strDetails;

         //strDetails.format("Failed to create directory (1) \"%s\"", string(wstr).c_str());

         //throw ::exception(estatus, strDetails);

      //}

   }

   //return true;

}


void erase_directory(const ::file::path & path)
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

      auto lasterror = ::GetLastError();

      auto estatus = ::windows::last_error_status(lasterror);

      throw ::exception(estatus);

   }

}


namespace windows
{


   wstring CLASS_DECL_ACME get_file_path_root(const wstring & wstrPath)
   {

      wstring wstrRoot;

      auto iLength = wstrPath.length();

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

      return ::transfer(wstrRoot);

   }


} // namespace windows




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



