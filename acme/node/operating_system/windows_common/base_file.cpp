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


::e_status delete_file(const char* path)
{

   wstring wstrPath(path);

   if (!::DeleteFileW(wstrPath))
   {

      auto dwLastError = ::GetLastError();

      auto estatus = last_error_to_status(dwLastError);

      return estatus;

   }

   return ::success;

}


::e_status file_exists(const char* path)
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



