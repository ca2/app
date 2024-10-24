// From apex/platform/app_launcher.h by camilo on 2023-02-15 19:26 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "launcher.h"
#include "app_launcher.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include "apex/operating_system.h"
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


   string app_launcher::get_executable_extension()
   {

      return {};

   }


   string app_launcher::get_executable_path()
   {

      auto psystem = system();

      auto pnode = psystem->node();

      ::file::path path = pnode->get_last_run_application_path(m_strApp);

      if(file_system()->exists(path))
      {

         return ::transfer(path);

      }

      string strExe = m_strApp;

      strExe.replace_with("_", "-");

      strExe.replace_with("_", "/");

      strExe += get_executable_extension();

      auto pcontext = get_context();

      ::file::path pathCandidate = directory()->module() / strExe;

      if (file()->exists(pathCandidate))
      {

         return ::transfer(pathCandidate);

      }

      return directory_system()->app_app(m_strPlatform, node()->process_configuration_name());

   }


   string app_launcher::get_params()
   {

      return {};

//      string strParameters;
//
//#if !defined(MACOS)
//
//      
//#ifdef WINDOWS_DESKTOP
//      
//      if (case_insensitive_string_ends(get_executable_path(), "\\app.exe"))
//         
//#endif
//         
//      {
//
//         strParameters = " : app=" + m_strApp;
//
//      }
//
//#endif
//
//      return strParameters;

   }


   void app_launcher::run()
   {

//#ifdef UNIVERSAL_WINDOWS
//
//      //return false;
//
//      return;
//
//#elif defined(WINDOWS)
//
//      wstring wstrApp(get_executable_path());
//
//      wstring wstrDir(::file_path_folder(string(wstrApp)));
//
//      wstring wstrParams = get_params();
//
//      STARTUPINFOW si;
//      
//      memory_set(&si,0,sizeof(si));
//      si.cb = sizeof(si);
//      si.dwFlags = STARTF_USESHOWWINDOW;
//      si.wShowWindow = SW_SHOWNORMAL;
//      PROCESS_INFORMATION pi;
//      memory_set(&pi,0,sizeof(pi));
//
//      wstring wstrCmdLine = L"\"" + wstrApp + L"\"" + wstrParams;
//
//      if (::CreateProcessW((unichar*)wstrApp.c_str(), (unichar*)wstrCmdLine.c_str(),
//         nullptr, nullptr, false, 0, nullptr, wstrDir,
//         &si, &pi))
//      {
//         return;
//
//      }
//
//#elif defined(MACOS)
//
//      ::file::path path = get_executable_path();
//      
//      auto psystem = system();
//      
//      auto pnode = psystem->node();
//
//      if(path.case_insensitive_find(".app//") >= 0)
//      {
//
//         path -= 3;
//
//         string strParams = get_params();
//         
//         if(strParams.is_empty())
//         {
//
//            pnode->_launch_macos_app(path);
//
//         }
//         else
//         {
//
//            pnode->_launch_macos_app_args(path, strParams);
//
//         }
//            
//      }
//      else
//      {
//         
//         pnode->call_async(path, "", "", e_display_none, false);
//         
//         //auto estatus = pnode->call_async(path, "", "", e_display_none, false);
//
////         if (::succeeded(estatus))
////         {
////
////            return true;
////
////         }
//         
//      }
//
//#else
//
//      if(m_strApp == "app-core/clockverse")
//      {
//
//         informationf("app-core/clockverse");
//
//      }
//
////      string strPath = get_executable_path();
////
////      string strDir = ::file_path_folder(strPath);
////
////      string strParams = get_params();
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
      node()->shell_launch(m_strApp);
//
//      //pnode->call_async(strPath, strParams, strDir, e_display_none, false);
//
////      if (::succeeded(pnode->call_async(strPath, strParams, strDir, e_display_none, false)))
////      {
////
////         return true;
////
////      }
//
//#endif
//
//      //return false;

   }


} // namespace apex



