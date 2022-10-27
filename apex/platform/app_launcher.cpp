#include "framework.h"
#include "launcher.h"
#include "app_launcher.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "apex/operating_system.h"
#include "apex/platform/context.h"


namespace apex
{


   app_launcher::app_launcher()
   {


   }


   void app_launcher::initialize_app_launcher(::particle * pparticle, string strPlatform, string strApp)
   {

      //auto estatus = ::object::initialize(pparticle);

      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_strPlatform = strPlatform;

      m_strApp = strApp;

      //return estatus;

   }


   string app_launcher::get_executable_path()
   {

      auto psystem = acmesystem();

      auto pnode = psystem->node();

      ::file::path path = pnode->get_last_run_application_path(m_strApp);

      if(acmefile()->exists(path))
      {

         return ::move(path);

      }

      string strExe = m_strApp;

      strExe.replace_with("_", "-");

      strExe.replace_with("_", "/");

#ifdef WINDOWS

      strExe += ".exe";

#endif

      auto pcontext = get_context();

      ::file::path pathCandidate = m_pcontext->m_papexcontext->dir().module() / strExe;

      if (m_pcontext->m_papexcontext->file().exists(pathCandidate))
      {

         return ::move(pathCandidate);

      }

      return acmedirectory()->app_app(m_strPlatform, process_configuration_dir_name());

   }


   string app_launcher::get_params()
   {

      string strParameters;

#if !defined(MACOS)

      
#ifdef WINDOWS_DESKTOP
      
      if (::str().ends_ci(get_executable_path(), "\\app.exe"))
         
#endif
         
      {

         strParameters = " : app=" + m_strApp;

      }

#endif

      return strParameters;

   }


   void app_launcher::run()
   {

#ifdef _UWP

      //return false;

      return;

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

      if (::CreateProcessW((unichar*)wstrApp.c_str(), (unichar*)wstrCmdLine.c_str(),
         nullptr, nullptr, false, 0, nullptr, wstrDir,
         &si, &pi))
      {
         return;

      }

#elif defined(MACOS)

      ::file::path path = get_executable_path();
      
      auto psystem = acmesystem();
      
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
         
         pnode->call_async(path, "", "", e_display_none, false);
         
         //auto estatus = pnode->call_async(path, "", "", e_display_none, false);

//         if (::succeeded(estatus))
//         {
//
//            return true;
//
//         }
         
      }

#else

      if(m_strApp == "app-core/clockverse")
      {

         ::output_debug_string("app-core/clockverse");

      }

//      string strPath = get_executable_path();
//
//      string strDir = ::file_path_folder(strPath);
//
//      string strParams = get_params();

      auto psystem = acmesystem();

      auto pnode = psystem->node();

      pnode->shell_launch(m_strApp);

      //pnode->call_async(strPath, strParams, strDir, e_display_none, false);

//      if (::succeeded(pnode->call_async(strPath, strParams, strDir, e_display_none, false)))
//      {
//
//         return true;
//
//      }

#endif

      //return false;

   }


} // namespace apex



