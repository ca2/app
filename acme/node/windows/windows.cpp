#include "framework.h"
#include "acme/node/windows/_windows.h"
#include "acme/os/windows_common/file.h"


namespace windows
{


   i32 windows::function()
   {

      return 0;

   }


   HINSTANCE load_library(const char * psz)

   {

      return ::LoadLibraryW(::str::international::utf8_to_unicode(psz));


   }


   bool CLASS_DECL_ACME shell_get_special_folder_path(oswindow oswindow,::file::path &str,i32 csidl,bool fCreate)
   {

      return ::SHGetSpecialFolderPathW(oswindow,wtostring(str,MAX_PATH * 8),csidl,fCreate) != FALSE;

   }


   ::file::path CLASS_DECL_ACME shell_get_special_folder_path(i32 csidl, bool fCreate, oswindow oswindow)
   {

      ::file::path path;

      if (!shell_get_special_folder_path(nullptr, path, csidl, fCreate))
      {

         return "";

      }

      return path;

   }




   ::u32 get_current_directory(string & str)
   {

      return ::GetCurrentDirectoryW(MAX_PATH * 8,wtostring(str,MAX_PATH * 8));

   }


   ::u32 get_temp_path(string & str)
   {

      return ::GetTempPathW(MAX_PATH * 8,wtostring(str,MAX_PATH * 8));

   }


   ::i32 reg_query_value(HKEY hkey,const char * pszSubKey,string & str)

   {

      ::u32 dwType = 0;
      ::u32 dwSize = 0;
      ::i32 lResult = RegQueryValueExW(hkey,wstring(pszSubKey),nullptr,&dwType,nullptr,&dwSize);

      if(lResult != ERROR_SUCCESS)
         return lResult;
      ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
      if(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
      {

         natural_wstring pwsz(byte_count, dwSize);

         lResult = RegQueryValueExW(hkey, wstring(pszSubKey),nullptr,&dwType,(byte *)(unichar *)pwsz,&dwSize);

         str = pwsz;

         //str.release_string_buffer(dwSize);

         return lResult;

      }
      else
      {

         return ERROR_NOT_SUPPORTED;

      }

   }


   HICON extract_icon(HINSTANCE hInst,const char * pszExeFileName,::u32 nIconIndex)

   {

      return ::ExtractIconW(hInst,::str::international::utf8_to_unicode(pszExeFileName),nIconIndex);


   }


   bool delete_file(const char * pFileName)

   {

      return ::DeleteFileW(::str::international::utf8_to_unicode(pFileName)) != FALSE;


   }


   CLASS_DECL_ACME void time_to_filetime(::matter * pobject,const ::datetime::time& time,LPFILETIME pFileTime)
   {

      SYSTEMTIME sysTime;

      sysTime.wYear           = (::u16)time.GetYear();
      sysTime.wMonth          = (::u16)time.GetMonth();
      sysTime.wDay            = (::u16)time.GetDay();
      sysTime.wHour           = (::u16)time.GetHour();
      sysTime.wMinute         = (::u16)time.GetMinute();
      sysTime.wSecond         = (::u16)time.GetSecond();
      sysTime.wMilliseconds   = 0;

      // convert system time to local file time
      FILETIME localTime;
      if(!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime,&localTime))
         ::file::throw_os_error((::i32)::get_last_error());

      // convert local file time to UTC file time
      if(!LocalFileTimeToFileTime(&localTime,pFileTime))
         ::file::throw_os_error((::i32)::get_last_error());

   }



} // namespace windows



//LRESULT CALLBACK __window_procedure(HWND oswindow, const ::id & id, WPARAM wparam, LPARAM lparam);
//
//WNDPROC get_window_procedure()
//{
//
//   return &::__window_procedure;
//
//}




