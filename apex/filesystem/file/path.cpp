#include "framework.h"


namespace path
{


   ::file::path app(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

   }


   ::file::path app_app_admin(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

   }


   ::file::path app_app_nest(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

   }


   ::file::path app_app(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

   }




   ::file::path vcredist(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

   }


   ::file::path module(HMODULE hmodule)
   {

#ifdef WINDOWS_DESKTOP

      wstring wstr(get_buffer, MAX_PATH * 8);

      GetModuleFileNameW(hmodule,wstr,(DWORD) wstr.length());

      return solve_relative(string(wstr.release_string_buffer()));


#elif defined(_UWP)

      return "m_app.exe";

#else

      char * pszModuleFilePath = br_find_exe_dir("app");


      if(pszModuleFilePath == nullptr)

         return "";

      string strModuleFileName(pszModuleFilePath);


      free(pszModuleFilePath);


      return strModuleFileName;

#endif

   }

   ::file::path install_log(string strPlatform, string strConfiguration)
   {

      return dir::install() / ("install-" + strPlatform + ".log");

   }

   CLASS_DECL_APEX string from(string str)
   {

      string strFsSafe;

      for (index i = 0; i < str.length(); i++)
      {

         if (ansi_char_is_alphanumeric(str[i]))
         {

            strFsSafe += str[i];

         }
         else
         {

            strFsSafe += "-" + ::hex::lower_from(str[i]);

         }

      }

      return strFsSafe;

   }


} // namespace path




