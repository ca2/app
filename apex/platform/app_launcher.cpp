#include "framework.h"
#include "apex/operating_system.h"
#include "launcher.h"
#include "app_launcher.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"


namespace apex
{


   app_launcher::app_launcher()
   {


   }


   ::e_status app_launcher::initialize_app_launcher(::object * pobject, string strPlatform, string strApp)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_strPlatform = strPlatform;

      m_strApp = strApp;

      return estatus;

   }


   string app_launcher::get_executable_path()
   {

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      ::file::path path = pnode->get_last_run_application_path(m_strApp);

      if(m_psystem->m_pacmefile->exists(path))
      {

         return ::move(path);

      }

      string strExe = m_strApp;

      strExe.replace("-", "_");

      strExe.replace("/", "_");

#ifdef WINDOWS

      strExe += ".exe";

#endif

      auto pcontext = get_context();

      ::file::path pathCandidate = m_pcontext->m_papexcontext->dir().module() / strExe;

      if (m_pcontext->m_papexcontext->file().exists(pathCandidate))
      {

         return ::move(pathCandidate);

      }

      return m_psystem->m_pacmedir->app_app(m_strPlatform, process_configuration_dir_name());

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


   ::e_status app_launcher::run()
   {

#ifdef _UWP

      return false;

#elif defined(WINDOWS)

      wstring wstrApp(get_executable_path());

      wstring wstrDir(::file_path_folder(string(wstrApp)));

      wstring wstrParams = get_params();

      STARTUPINFOW si;
      
      __memset(&si,0,sizeof(si));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_SHOWNORMAL;
      PROCESS_INFORMATION pi;
      __memset(&pi,0,sizeof(pi));

      wstring wstrCmdLine = L"\"" + wstrApp + L"\"" + wstrParams;

      if(::CreateProcessW( (unichar *) wstrApp.c_str(), (unichar *) wstrCmdLine.c_str(),
                          nullptr,nullptr,false,0,nullptr,wstrDir,
                          &si,&pi))
         return true;

#elif defined(MACOS)

      ::file::path path = get_executable_path();
      
      auto psystem = m_psystem;
      
      auto pnode = psystem->node();

      if(path.find_ci(".app//") >= 0)
      {

         path -= 3;

         string strParams = get_params();
         
         if(strParams.is_empty())
         {

            pnode->_launch_macos_app(path);

         }
         else
         {

            pnode->_launch_macos_app_args(path, strParams);

         }
            
      }
      else
      {
         
         auto estatus = pnode->call_async(path, "", "", e_display_none, false);

         if (::succeeded(estatus))
         {

            return true;

         }
         
      }

#else

      if(m_strApp == "app-core/clockverse")
      {

         ::output_debug_string("app-core/clockverse");

      }

      string strPath = get_executable_path();

      string strDir = ::file_path_folder(strPath);

      string strParams = get_params();

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      if (::succeeded(pnode->call_async(strPath, strParams, strDir, e_display_none, false)))
      {

         return true;

      }

#endif

      return false;

   }


} // namespace apex



