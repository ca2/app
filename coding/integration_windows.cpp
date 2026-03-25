//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSørensen!!
// Merge from integration_windows_build_tool.cpp on 2024-05-15 03:35 by
// camilo <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application.h"
#include "code.h"
#include "impact.h"
#include "integration.h"
#include "group.h"
#include "integration_windows.h"
#include "item.h"
#include "install.h"
#include "task_group.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/file/buffered_file.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/handler/sequence.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
//#include "apex/platform/node.h"
#include "acme_windows/_.h"
#include "acme_windows/registry.h"

//void command_system(string_array & straOutput, int & iExitCode, const char * psz, enum_command_system ecommandsystem, const class time & timeTimeout);


namespace windows
{

   
   namespace coding
   {


      integration::integration()
      {


      }


      integration::~integration()
      {


      }


      void integration::on_initialize_application_build_tool_task_groups()
      {

         _defer_task_group(::coding::e_task_openssl);
         _defer_task_group(::coding::e_task_ffmpeg);
         _defer_task_group(::coding::e_task_port);

      }



      void integration::on_initialize_application_build_tool_operating_system_integrate_list()
      {

         if (m_papp->m_bWinRT)
         {

            m_eintegrateaOperatingSystem.copy_initializer_list(
               {
                  ::coding::e_integrate_universal_windows_openssl,
                  ::coding::e_integrate_universal_windows_ffmpeg,
                  ::coding::e_integrate_universal_windows_port,
               });

         }
         else
         {

            m_eintegrateaOperatingSystem.copy_initializer_list(
               {
                  ::coding::e_integrate_universal_windows_openssl,
                  ::coding::e_integrate_universal_windows_ffmpeg,
                  ::coding::e_integrate_universal_windows_port,
               });

         }

      }
   
   
   void integration::task_group_tasks_ordinals(::coding::enum_task etaskGroup, ::numeric_array_base < ::coding::enum_task >& etaskaOrdinal)
   {
      
      
      switch (etaskGroup)
      {
      case ::coding::e_task_port:
      case ::coding::e_task_openssl:
      case ::coding::e_task_ffmpeg:
      {
         etaskaOrdinal.add(::coding::e_task_win32_debug);
         etaskaOrdinal.add(::coding::e_task_win32_release);
         etaskaOrdinal.add(::coding::e_task_win32_static_debug);
         etaskaOrdinal.add(::coding::e_task_win32_static_release);
         etaskaOrdinal.add(::coding::e_task_x64_debug);
         etaskaOrdinal.add(::coding::e_task_x64_release);
         etaskaOrdinal.add(::coding::e_task_x64_static_debug);
         etaskaOrdinal.add(::coding::e_task_x64_static_release);
      }
      break;
      case ::coding::e_task_windows:
      {

         etaskaOrdinal.add(::coding::e_task_x64_release);

      }
      break;
      default:
         break;

      }

   }





      void integration::prepare_build()
      {

         m_pathStoreFolder1 = directory_system()->home() / "store/windows";

         m_pathStorageFolder = directory_system()->home() / "storage/windows";

         //      m_straunion.add_array(m_pintegrationcontext->m_straOutput);
         //      m_straunion.add_array(m_straLine2);

         m_pintegrationcontext->m_strConfiguration = "Release";
         m_pintegrationcontext->m_strPlatform = "x64";

         m_pintegrationcontext->prepare_compile_and_link_environment();

         //      auto pacmedirectory = directory_system();
         //
         //      ::file::path strVars;
         //
         //      if (m_strVs == "2015")
         //      {
         //
         //         strVars = getenv("VS140COMNTOOLS");
         //
         //      }
         //
         //      ::pointer<::aura::application>papp = get_app();
         //
         //      try
         //      {
         //
         //         if (m_strVs == "2022")
         //         {
         //
         //            m_strEnv = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Integration/vcvarsall.bat";
         //
         //            m_strVCVersion = papp->get_visual_studio_build();
         //
         //         }
         //         else if (m_strVs == "2019")
         //         {
         //
         //            m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Integration/vcvarsall.bat";
         //
         //            m_strVCVersion = papp->get_visual_studio_build();
         //
         //         }
         //         else if (m_strVs == "2017")
         //         {
         //
         //            m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Integration/vcvarsall.bat";
         //
         //            ::acme_windows::registry::key key;
         //
         //            key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false);
         //
         //            string strPath;
         //
         //            key.get("15.0", strPath);
         //
         //            ::file::path path = strPath;
         //
         //            m_strEnv = path / "VC/Auxiliary/Integration/vcvarsall.bat";
         //
         //            m_strVCVersion = papp->get_visual_studio_build();
         //
         //         }
         //         else if (m_strVs == "2015")
         //         {
         //
         //            m_strEnv = strVars.ascend(2);
         //
         //            m_strEnv = m_strEnv / "vc\\vcvarsall.bat";
         //
         //         }
         //
         //      }
         //      catch (const ::e_status& estatus)
         //      {
         //
         //         output_debug_string("failed to setup visual studio environment " + ::as_string((long long)estatus.m_eenum));
         //
         //      }
         //
         //
         //      m_strTime = directory()->install() / ("time-" OPERATING_SYSTEM_NAME);
         //
         //      if (m_strVs == "2015")
         //      {
         //
         //         m_strSdk1 = "vc140";
         //
         //      }
         //      else if (m_strVs == "2017")
         //      {
         //
         //         m_strSdk1 = "vc141";
         //
         //      }
         //      else if (m_strVs == "2019")
         //      {
         //
         //         m_strSdk1 = "vc142";
         //
         //      }
         //      else if (m_strVs == "2022")
         //      {
         //
         //         m_strSdk1 = "vc143";
         //
         //      }
         //
         //#ifdef OS64BIT
         //
         //      m_strPlat1 = "64";
         //      m_strPlat2 = "x86_amd64";
         //      //m_strPlat2 = "amd64";
         //      m_strPlatform = "x64";
         //      m_strStagePlatform = "x64";
         //      m_strLibPlatform = "x64/";
         //
         //#else
         //
         //      m_strPlat1 = "32";
         //      m_strPlat2 = " x86";
         //      m_strPlatform = "Win32";
         //      m_strStagePlatform = "x86";
         //      m_strLibPlatform = "x86/";
         //
         //#endif


      }




      //void impact::prepare_windows()
      //{

      //   //string strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Integration/vcvars64.bat\"";

      //   //::operating_system::process_pointer process(e_create, this);

      //   //::file::path pathEnvTxt;

      //   //auto pacmedirectory = directory_system();

      //   //pathEnvTxt = pacmedirectory->system() / "env.txt";

      //   //file_system()->put_contents(pacmedirectory->system() / "env1.bat", pacmedirectory->system() / "env.bat > \"" + pathEnvTxt + "\"");

      //   //file_system()->put_contents(pacmedirectory->system() / "env.bat", "@call " + strBuildCmd + "\r\n@set");

      //   //acmenode()->run_silent(pacmedirectory->system() / "env1.bat", "");

      //   //string strLog = file_system()->as_string(pacmedirectory->system() / "env.txt");

      //   //string_array stra;

      //   //stra.add_lines(strLog);

      //   ////sleep(10000_ms);

      //   //property_set setEnvironment;

      //   //setEnvironment.parse_environment_variable(stra);

      //   //for (auto& pproperty : setEnvironment)
      //   //{

      //   //   SetEnvironmentVariableW(wstring(pproperty->m_atom), wstring(pproperty->as_string()));

      //   //}

      //}


      void integration::integrate_new_release_prefix_windows()
      {

         //::file::path pathTargetReleaseTime = "C:/release/release_time.txt";

         //auto strReleaseTime = datetime()->international().get_date_time();

         //file_system()->put_block(pathTargetReleaseTime, strReleaseTime);

         //m_strIntegration = strReleaseTime;

         string_array straCommand;
         string_array straLabel;

         ::string strProgramFiles = node()->get_environment_variable("ProgramFiles");

         straCommand.add("unix://repo-rinse.sh");
         straLabel.add("Repository Rinse");

         straCommand.add("unix://checkout");
         straLabel.add("Checkout");

         straCommand.add("unix://new_release_time");
         straLabel.add("New Release Time");

         straCommand.add("unix://set_release_time");
         straLabel.add("Set Release Time");

         straCommand.add("unix:commit");
         straLabel.add("Commit");

         ::file_pointer pfileLog;

         trace_function functionTrace = [&](auto etracelevel, auto& str, bool bCarriage)
            {

               {

                  _synchronous_lock synchronouslock(this->synchronization());

                  ::string s;

                  s.formatf("%c: %s", trace_level_letter(etracelevel), str.c_str());

                  m_straLine3.feed_line(s, bCarriage);

               }

               m_pimpactinterface->on_lines_change();

               std_inline_log()(etracelevel, str, bCarriage);

               pfileLog->write(str + "\r\n");

            };

         functionTrace.set_timeout(1_hour);

         directory_system()->change_current("C:/release");

         for (::collection::index i = 0; i < straCommand.size(); i++)
         {

            auto strCommand = straCommand[i];

            auto strLabel = straLabel[i];

            main_status("New Release Time:" + strLabel);

            int iExitCode = 0;

            auto pathLogFolder = integration_folder();

            //auto pathLogFolder = integration_folder() / "integration";

            //pathLogFolder /= node()->get_environment_variable("__SYSTEM_SLASHED_OPERATING_SYSTEM");

            pathLogFolder /= "new_release_prefix";

            ::string strIndex;

            strIndex.formatf("%03d_", i + 1);

            auto pathLog = pathLogFolder / (strIndex + strLabel + ".txt");

            pfileLog = file()->get_writer(pathLog, ::file::e_open_share_deny_none);

            string strCmd(strCommand);

            //if (strCmd.begins_eat("unix:"))
            //{

            //   node()->posix_shell_command(strCmd, functionTrace);

            //}
            //else
            //{

            node()->command_system(strCmd, functionTrace);

            //}

         }

      }


      void integration::integrate_main2(::coding::item* pitem)
      {

         //bool bOk = true;

         auto& ptaskgroup = pitem->m_ptaskgroup;

         _defer_task_group(::coding::e_task_windows, &ptaskgroup);

         string& strBuildResult = m_strBuildResult;

         ptaskgroup->m_pathBuildFolder = m_strRepositoryPath;

         ::file::path pathOperatingSystemFolder;

         pathOperatingSystemFolder = ptaskgroup->m_pathBuildFolder / "operating_system/operating_system-windows";

         auto pacmedirectory = directory_system();

         auto pacmefile = file_system();

         pacmedirectory->change_current(ptaskgroup->m_pathBuildFolder);

         ::file::path pathDeploymentTemplate;

         pathDeploymentTemplate = pathOperatingSystemFolder / "deployment/deployment.txt";

         string strFileName;

         ////string strProjectName;

         //string strReleaseDot;

         //string strReleaseComma;

         //string strReleaseDateTime;

         //string strFileNameTimeBuild;

         strFileName = "ca2";

         //strProjectName = "ca2";

         //auto pdatetime = datetime();

         //strReleaseDot = pdatetime->format("%Y.%m%d.%H%M.%S",m_timeBuild);

         //strReleaseComma = pdatetime->format("%Y,%m%d,%H%M,%S", m_timeBuild);

         //strReleaseDateTime = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);

         //strFileNameTimeBuild = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);

         //::file::path pathDeployment;

         //pathDeployment = pathOperatingSystemFolder / ("deployment/deployment" + strFileNameTimeBuild + ".txt");

         //::file::path pathDeploymentRcTemplate;

         //pathDeploymentRcTemplate = pathOperatingSystemFolder / "deployment/deployment_rc.txt";

         //auto strDeploymentRcTemplate = pacmefile->as_string(pathDeploymentTemplate);

         //strDeploymentRcTemplate.find_replace("%FILENAME%", strFileName);
         ////strDeploymentRcTemplate.find_replace("%PROJECTNAME%", strProjectName);
         //strDeploymentRcTemplate.find_replace("%RELEASEDOT%", strReleaseDot);
         //strDeploymentRcTemplate.find_replace("%RELEASECOMMA%", strReleaseComma);
         //strDeploymentRcTemplate.find_replace("%RELEASEDATETIME%", strReleaseDateTime);

         //pacmefile->put_contents(pathDeployment, strDeploymentRcTemplate);

         //pacmefile->copy(pathDeploymentRcTemplate, pathDeployment, true);

         string strBuildSln;

         strBuildSln = ptaskgroup->m_pathBuildFolder / "solution-windows/all.sln";

         strBuildSln.find_replace("/", "\\");

         //pathDeployment = ptaskgroup->m_pathBuildFolder / "operating_system/operating_system-windows/deployment/deployment.txt";

         //directory_system()->change_current(ptaskgroup->m_pathBuildFolder);

         //string strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat\"";

         //file_system()->put_contents(pacmedirectory->system() / "build.bat", "@call " + strBuildCmd + "\n" + strSh1 + "\n" + strSh2 + "\n" + strSh3 + "\n" + strSh4 + "\n" + strCmd1 + "\n" + strCmd2 + "\n" + strSh10);

         //file_system()->put_contents(m_straLine2, )

         //acmenode()->command_system(pacmedirectory->system() / "build.bat"

         //auto& straCommand = m_straCommand;

         //auto& straLabel = m_straLabel;

         //auto& timea = m_timea;

         ::string strProgramFiles = node()->get_environment_variable("ProgramFiles");

         if (m_baPhaseEnable[::coding::e_phase_checkout])
         {

            add_command("checkout",
               "posix://checkout",
               20_minute);

         }

         if (m_baPhaseEnable[::coding::e_phase_application_list])
         {

            add_command("application_list",
               "application_build_helper --application-list",
               10_minute);

         }

         if (m_baPhaseEnable[::coding::e_phase_prepare_applications])
         {

            add_command("prepare_applications",
               "application_build_helper --prepare-applications",
               10_minute);

         }

         if (m_baPhaseEnable[::coding::e_phase_project_list])
         {

            add_command("project_list",
               "application_build_helper --project-list",
               10_minute);

         }

         if (m_baPhaseEnable[::coding::e_phase_prepare_projects])
         {

            add_command("prepare_projects",
               "application_build_helper --prepare-projects",
               10_minute);

         }

         if (m_baPhaseEnable[::coding::e_phase_clean])
         {

            add_command("clean",
               "cmd /c devenv \"" + strBuildSln + "\" /Clean \"Release|x64\"",
               10_minute);

         }

         add_command("build",
            "cmd /c devenv \"" + strBuildSln + "\" /Build \"Release|x64\"",
            2_hour);

         add_command("package",
            "\"" + strProgramFiles + "\\Git\\bin\\bash.exe\" -c package",
            20_minute);

         integrate_command_list();

         //::file_pointer pfileLog;

         //trace_function functionTrace = [&](auto etracelevel, auto& str)
         //{

         //   {

         //      _synchronous_lock synchronouslock(this->synchronization());

         //      m_straLine2.append_formatf("%c: %s\n", trace_level_letter(etracelevel), str.c_str());

         //   }

         //   m_pimpactinterface->on_lines_change();

         //   std_inline_log()(etracelevel, str);

         //   pfileLog->write(str + "\r\n");

         //};

         //functionTrace.m_timeTimeout = 1_hour;

         //int iExitCode = 0;

         //::string strLabel;

         //for (::index i = 0; i < straCommand.size(); i++)
         //{

         //   auto strCommand = straCommand[i];

         //   strLabel = straLabel[i];

         //   main_status("windows:" + strLabel);

         //   auto pathLogFolder = m_pathBuildFolder.folder() / "integration";

         //   pathLogFolder /= node()->get_environment_variable("__SYSTEM_SLASHED_OPERATING_SYSTEM");

         //   pathLogFolder /= "build" / strFileNameTimeBuild;

         //   ::string strIndex;

         //   strIndex.formatf("%03d_", i + 1);

         //   auto pathLog = pathLogFolder / (strIndex + strLabel + ".txt");

         //   pfileLog = file()->get_writer(pathLog, ::file::e_open_share_deny_none);

         //   string strCmd(strCommand);

         //   if (strCmd.begins_eat("unix:"))
         //   {

         //      iExitCode = node()->unix_shell_command(strCmd, functionTrace);

         //   }
         //   else
         //   {

         //      iExitCode = node()->command_system(strCmd, functionTrace);

         //   }

         //   if (iExitCode != 0)
         //   {

         //      bOk = false;

         //      break;

         //   }


         //}

         ////file_system()->put_contents(pacmedirectory->system() / "build.bat", "@call " + strBuildCmd + "\n" + strSh1 + "\n" + strSh2 + "\n" + strSh3 + "\n" + strSh4 + "\n" + strCmd1 + "\n" + strCmd2 + "\n" + strSh10);

         ////string strCmd = "cmd /c \"" + (pacmedirectory->system() / "build.bat") + "\"";

         ////string strOutput;

         ////string strError;

         ////int iExitCode = 0;

         //if (bOk)
         //{

         //   strBuildResult += "Build succeeded!!";

         //   m_pitem->m_pstillStatus->set_window_text("OK");

         //}
         //else
         //{

         //   strBuildResult += "Build stopped at step \"" + strLabel + "\"";

         //   m_pitem->m_pstillStatus->set_window_text("Failed at " + strLabel + "!");

         //   auto pathFailedStep = pacmedirectory->home() / "build/log" / m_strReleaseDash / (strStep + " _____ Step Failed!!.txt");

         //   file_system()->put_contents(pathFailedStep, strBuildResult);

         //}

      }


      bool integration::on_packaging(::string& strAppId, ::string& strTarget, ::string& strSource)
      {

         if (!on_more_packaging(strAppId, strTarget, strSource))
         {

            return false;

         }

         if (strAppId == "app-core/store")
         {

            ::string strCommand = "application_build_helper --release-store-installer";

            trace_function tracefunction = [&](auto etracelevel, auto& str, bool bCarriage)
               {

                  //{

                  //   _synchronous_lock synchronouslock(m_pmutexLines);

                  //   m_straLine2.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());

                  //}

                  std_inline_log()(etracelevel, str, bCarriage);

                  //            pfileLog->write(str + "\r\n");

               };

            node()->command_system(strCommand, tracefunction);

            auto psummary = node()->operating_system_summary();

            ::string strSlashedOperatingSystem = psummary->m_strSlashedIntegration;

            ::string strPlatform = psummary->m_strPackagePlatform;

            ::string strExtension = psummary->m_strStandardPackageFileExtension;

            strTarget = strSlashedOperatingSystem / ("store_" + strPlatform + "." + strExtension);

            strSource = m_pathStoreFolder1 / ("store_" + strPlatform + "." + strExtension);

         }

         return true;

      }


      //::file::path integration::path_base_folder()
      //{

      //   return "C:\\port";

      //}





      // void integration::integrate_windows_openssl(::coding::item* pitem)
      // {

      //    integrate_windows_task_group(e_task_openssl, pitem);

      // }


      // void integration::integrate_windows_ffmpeg(::coding::item* pitem)
      // {

      //    integrate_windows_task_group(e_task_ffmpeg, pitem);

      // }


      void integration::on_start_task_group(::coding::enum_task etaskGroup)
      {

         m_etaskGroupRunning = etaskGroup;

         m_pimpactinterface->on_start_task_group(etaskGroup);

         if (etaskGroup == ::coding::e_task_openssl)
         {

            auto ptaskgroup = m_taskgroup[etaskGroup];

            m_papp->_defer_install_msys2(ptaskgroup);

            m_papp->defer_install(::coding::e_install_strawberry_perl, ptaskgroup);

            if (!m_papp->is_installed(::coding::e_install_strawberry_perl, false))
            {

               throw ::exception(error_wrong_state, "StrawberryPerl isn't installed or not installed at C:\\Strawberry");

            }

         }
         else if (etaskGroup == ::coding::e_task_ffmpeg)
         {

            auto ptaskgroup = m_taskgroup[etaskGroup];

            m_papp->_defer_install_msys2(ptaskgroup);

            if (m_papp->m_bWinRT)
            {

               auto pinstall = m_papp->code()->m_installmap[::coding::e_install_msys2];

               auto tracefunction = pinstall->task_group_trace_function(ptaskgroup);

               node()->defer_install_posix_shell_command("cmp", e_posix_shell_msys2, tracefunction);


            }

         }

      }


      //   int integration::_do_windows_task(::coding::task* ptask)
      //   {
      //
      //      ::file_pointer pfileLog;
      //
      //      auto ploginterface = task_log(ptask->etask());
      //
      //      ::string strTitle;
      //
      //      ::string strTask;
      //
      //      strTask.formatf("%02d", ptask->m_etaskOrdinal);
      //
      //      auto strLabel = ptask->m_strLabel2;
      //
      //      strTitle = strTask + "_" + strLabel;
      //
      //      ptask->m_strTopic1 = strTitle;
      //
      //      auto strLogName = strTitle;
      //
      //      strLogName.find_replace(" ", "_");
      //
      //      strLogName.find_replace("|", "_");
      //
      //      auto strCommand = ptask->m_strCommand;
      //
      //      int iExitCode = 0;
      //
      //      ploginterface->m_iIndex = -1;
      //
      //      ploginterface->m_iStage = 0;
      //
      //      pfileLog = file()->get_writer(ptask->m_ptaskgroup->m_pathBuildFolder / "time-windows" / (strLabel + "_log") / (strLogName + ".txt"), ::file::e_open_share_deny_none);
      //
      //      trace_function functionTrace = [ploginterface, pfileLog](auto etracelevel, auto& str, bool bCarriage)
      //         {
      //
      //            ploginterface->on_trace(etracelevel, str, bCarriage);
      //
      //            pfileLog->write(str + "\r\n");
      //
      //         };
      //
      //      {
      //
      //         _synchronous_lock synchronouslock(ptask->synchronization());
      //
      //         ptask->m_strTopic1 = ptask->m_strLabel2;
      //
      //         ptask->m_strTopic12 = "Starting...";
      //
      //      }
      //
      //      functionTrace.m_timeTimeout = 2_hour;
      //
      //      ptask->on_start();
      //
      //      try
      //      {
      //
      //         iExitCode = node()->command_system(
      //            ptask->m_strCommand
      //            + ptask->m_ptaskgroup->m_strTaskParallelizationArguments
      //            + ptask->m_ptaskgroup->m_strTaskInteractivenessArguments,
      //            functionTrace,
      //            ptask->m_ptaskgroup->m_pathBuildFolder);
      //
      //         //preempt(1_s * mathematics()->random(1.0, 60.0));
      //         //preempt(1_s * mathematics()->random(1.0, 5.0));
      //
      //         //iExitCode = 1;
      //
      //      }
      //      catch (...)
      //      {
      //
      //      }
      //
      //      return iExitCode;
      //
      //   }

   } // namespace coding


} // namespace windows


void integration_library_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item<::windows::coding::integration, ::coding::integration>();

}



