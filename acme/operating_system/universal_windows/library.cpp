#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/library.h"
#include "acme/platform/system.h"
//#include "acme/operating_system/windows_common/_.h"
#include "acme/_operating_system.h"


namespace acme
{


   void * system::operating_system_library_touch(const ::file::path & path, string & strMessage)
   {

      return operating_system_library_open(path, strMessage);

   }


   void * system::operating_system_library_open(const ::file::path & path, string & strMessage)
   {

      void * plibrary = nullptr;

      string strPath(path);

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

      try
      {

         wstring wstr(strPath);

         plibrary = ::LoadPackagedLibrary(wstr, 0);

         DWORD dwLastError = ::GetLastError();

         string strLastError = ::windows::last_error_message(dwLastError);

         ::information(strLastError);

      }
      catch (...)
      {

      }

      if (plibrary == nullptr)
      {

         try
         {

            wstring wstrPath("\\\\?\\" + strPath);

            plibrary = ::LoadPackagedLibrary(wstrPath, 0);

         }
         catch (...)
         {

         }

      }

      if (plibrary == nullptr)
      {

         try
         {

            wstring wstrPath(acmedirectory()->module() / strPath);

            plibrary = ::LoadPackagedLibrary(wstrPath, 0);

         }
         catch (...)
         {

         }

      }

      if (plibrary == nullptr)
      {

         try
         {

            wstring wstrPath(("\\\\?\\" + acmedirectory()->module()) / strPath);

            plibrary = ::LoadPackagedLibrary(wstrPath, 0);

         }
         catch (...)
         {

         }

      }

      //if (plibrary == nullptr)
      //{

      //   try
      //   {

      //      wstring wstr(acmedirectory()->module() / strPath);

      //      plibrary = ::LoadPackagedLibrary(wstr, 0);

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      //if (plibrary == nullptr)
      //{

      //   try
      //   {

      //      wstring wstr(("\\\\?\\" + acmedirectory()->module()) / strPath);

      //      plibrary = ::LoadPackagedLibrary(wstr, 0);

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      return plibrary;

   }


   void * system::operating_system_library_open_ca2(const ::file::path & path, ::string & strMessage)
   {
      /*      string str(psz);
      if(str.find("..") >= 0)
      return false;
      if(str.find(":") >= 0)
      return false;
      if(str.find("\\\\") >= 0)
      return false;
      if(str[0] == '\\')
      return false;
      if(str[0] == '/')
      return false;
      #ifdef _M_X64
      //::SetDllDirectory(dir::install("stage\\x64") + "\\");
      #else
      //::SetDllDirectory(dir::install("stage\\x86") + "\\");
      #endif*/

      wstring wstr(path);

      return LoadPackagedLibrary(wstr, 0);

   }


   void * system::operating_system_library_raw_get(void * plibrary, const ::scoped_string & scopedstrEntryName)
   {

      return ::GetProcAddress((HINSTANCE)plibrary, scopedstrEntryName);

   }



   bool system::operating_system_library_close(void * plibrary)
   {

      if (plibrary == nullptr)
         return false;

      bool bOk = false;

      try
      {

         bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;

      }
      catch (...)
      {

      }

      return bOk;

   }


} // namespace acme



