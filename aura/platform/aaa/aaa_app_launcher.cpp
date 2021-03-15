#include "framework.h"
#include "aura/os/_c.h"
#include "aura/os/_.h"


namespace aura
{


   app_launcher::app_launcher(string strPlatform, string strApp)
   {

      m_strPlatform     = strPlatform;

      m_strApp          = strApp;

   }


   string app_launcher::get_executable_path()
   {

      ::file::path path = get_last_run_application_path(m_strApp);

      if(file_exists(path))
      {

         return ::move(path);

      }

      string strExe = m_strApp;

      strExe.replace("-", "_");

      strExe.replace("/", "_");

#ifdef WINDOWS

      strExe += ".exe";

#endif

      ::file::path pathCandidate = pcontext->dir().ca2module() / strExe;

      if (pcontext->file().exists(pathCandidate))
      {

         return ::move(pathCandidate);

      }

      return ::path::app_app(m_strPlatform, process_configuration_dir_name());

   }


   string app_launcher::get_params()
   {

      string strParameters;

#if !defined(MACOS)

#ifdef WINDOWS_DESKTOP
      if (::str::ends_ci(get_executable_path(), "\\app.exe"))
#endif
      {

         strParameters = " : app=" + m_strApp;

      }

#endif

      return strParameters;

   }


   bool app_launcher::start()
   {

#ifdef _UWP

      return false;

#elif defined(WINDOWS)

      wstring wstrApp(get_executable_path());

      wstring wstrDir(dir::name(string(wstrApp)));

      wstring wstrParams = get_params();

      STARTUPINFOW si;
      __memset(&si,0,sizeof(si));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_SHOWNORMAL;
      PROCESS_INFORMATION pi;
      __memset(&pi,0,sizeof(pi));

      wstring wstrCmdLine = L"\"" + wstrApp + L"\"" + wstrParams;

      if(::CreateProcessW((unichar *)wstrApp.c_str(),(unichar *)wstrCmdLine.c_str(),
                          nullptr,nullptr,false,0,nullptr,wstrDir,
                          &si,&pi))
         return true;

#elif defined(MACOS)

      ::file::path path = get_executable_path();

      path -= 3;

      string strParams = get_params();

      if(strParams.is_empty())
      {

         launch_macos_app(path);

      }
      else
      {

         launch_macos_app_args(path, strParams);

      }

#else

      string strPath = get_executable_path();

      string strDir = dir::name(strPath);

      string strParams = get_params();

      if (call_async(strPath, strParams, strDir, e_display_none, false) == 0)
         return true;

#endif

      return false;

   }


} // namespace aura


