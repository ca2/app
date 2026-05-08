// Created by camilo on 2024-05-04 16:42 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "install.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/queue.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "apex/filesystem/fs/folder_sync.h"
#include "apex/networking/http/context.h"


void edge_installed();

CLASS_DECL_ACME::file::path windows_bash_path(const ::file::path& path);


namespace coding
{


   void install::install_msys2()
   {

      try
      {

         auto pathExe = m_path;

         set_status2("Installing MSYS2...");

         node()->root_execute_sync(pathExe, "install --root C:\\msys64 --confirm-command", 20_min, pathExe.folder());

      }
      catch (...)
      {

      }

      on_finished();

   }


   void install::install_strawberry_perl()
   {

      _run_msi_exec();

   }


   void install::install_tortoise_git()
   {

      _run_msi_exec();

   }


   void install::_on_after_msi_exec()
   {

      if (m_einstall == e_install_strawberry_perl)
      {

         node()->command_system("ren C:\\msys64\\usr\\bin\\perl.exe perl_.exe", 2_min);

         ::string strCmd = node()->get_environment_variable("ComSpec");

         node()->root_execute_sync(strCmd, "/c \"ren \\\"C:\\\\Program Files\\\\Git\\\\usr\\\\bin\\\\perl.exe\\\" perl_.exe\"", 2_min);

         node()->system_notify_environment_variable_change();

         node()->update_process_environment_variables();

      }

   }


   //void install::wait_dropbox_installed()
   //{

   //   while (true)
   //   {

   //      if (directory()->is_dropbox_installed())
   //      {

   //         break;

   //      }

   //      preempt(2_s);

   //      directory()->calculate_dropbox_installed();

   //   }

   //   ::file::path pathDropbox = m_pcontext->defer_process_path("dropbox://");

   //   directory_system()->change_current(pathDropbox);

   //   ::file::path pathBox = pathDropbox / "box";

   //   //if (path.has_character() && directory_system()->is(path))
   //   //{

   //     // break;

   //   //}


   //   int iTryStart = 0;

   //   int iRetryStart = 3;

   //   class ::time timeLastTryStart;

   //   int iExitCodeLastTryStart = -1;

   //   ::string strOutputLastTryStart;

   //   while (true)
   //   {

   //      if (directory_system()->is(pathBox))
   //      {

   //         break;

   //      }

   //      set_status2("Waiting for " + pathBox + " appear... please wait...");

   //      preempt(1_s);

   //   }

   //}


   //bool install::install_dropbox()
   bool install::_install_dropbox()
   {

      bool bJustCreatedDropboxFolder = false;

      if (!m_papp->__is_dropbox_installed())
      {

         bJustCreatedDropboxFolder = true;

         ::file::path pathUrl = "https://www.dropbox.com/download?os=win&plat=win";

         auto path = download_to_downloads_code__(pathUrl, "DropboxInstaller.exe");

         _install_exe(path);

         auto pathClient = file()->dropbox_client();

         node()->launch_app(pathClient, nullptr, 0);

      }

      //wait_dropbox_installed();

      //if (!file_system()->exists(pathDropboxBin))
      //{

      //   ::file::path pathUrl = "https://www.dropbox.com/download?dl=packages/dropbox.py";

      //   ::file::path pathFinalUrl = system()->http_get_effective_url(pathUrl);

      //   auto pszFinalUrl = pathFinalUrl.c_str();

      //   auto path = download_to_downloads_code__(pathFinalUrl, "dropbox");

      //   file_system()->copy(pathDropboxBin, path, true);

      //   chmod(pathDropboxBin, S_IRWXU);

      //}

      return bJustCreatedDropboxFolder;

   }


   void install::defer_setup_dropbox()
   {

      bool bJustInstalledDropbox = m_papp->m_bJustInstalledDropbox;

      set_status2("Waiting for Dropbox to be up and running... please wait...");

      {

         auto pfoldersync = m_papp->current_fs_folder_sync();

         if (pfoldersync)
         {

            pfoldersync->wait_up_and_running();

         }

      }

      //if (bJustInstalledDropbox
      //   ||
      //   (m_papp->m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization.is_checked()))
      //{

      //   set_status2("Limiting Dropbox synchronization to just \"box\" folder... please wait...");

      //   dropbox_exclude_all_except_box();

      //}
      //else
      //{

      //   set_status2(
      //      "Checking that \"box\" folder is not excluded from Dropbox synchronization... please wait...");

      //   bool bBoxExcludedFromSyncing = dropbox_is_box_excluded();

      //   if (bBoxExcludedFromSyncing)
      //   {

      //      set_status2("Removing \"box\" from Dropbox synchronization exclusion list... please wait...");

      //      dropbox_exclude_all_except_box();

      //   }

      //}

   }


   ::file::path install::get_download_url(::string& strName)
   {

      ::file::path pathUrl;

      // strName = "VisualStudioSetup.exe";

      switch (m_einstall)
      {
      case e_install_tortoise_git:
         pathUrl = "https://download.tortoisegit.org/tgit/2.15.0.0/TortoiseGit-2.15.0.0-64bit.msi";
         break;
      case e_install_git_scm:
         pathUrl = "https://github.com/git-for-windows/git/releases/download/v2.44.0.windows.1/Git-2.44.0-64-bit.exe";
         break;
      case e_install_visual_studio:
         pathUrl = "https://c2rsetup.officeapps.live.com/c2r/downloadVS.aspx?sku=community&channel=Release&version=VS2022&source=VSLandingPage";
         strName = "VisualStudioSetup.exe";
         break;
      case e_install_browser:
      {
         if (m_papp->m_strBrowser == "chrome")
         {
            auto str1 = "http://dl.google.com/chrome/install/375.126/chrome_installer.exe";

            pathUrl = http()->get_effective_url(str1).as_string();

         }
         else if (m_papp->m_strBrowser == "opera")
         {
            
            auto str1 = "https://net.geo.opera.com/opera/stable/windows";

            pathUrl = http()->get_effective_url(str1).as_string();
            strName = "OperaSetup.exe";


         }
      }
      break;
      case e_install_visual_studio_code:
      {
         auto str1 = "https://code.visualstudio.com/sha/download?build=stable&os=win32-x64-user";

         pathUrl = http()->get_effective_url(str1).as_string();
      }
      break;
      case e_install_smart_git:
         pathUrl = "https://www.syntevo.com/downloads/smartgit/smartgit-win-23_1_3.zip";
         break;
      case e_install_msys2:
         pathUrl = path_system()->get_uniform_resource_locator("https://ca2.software/link/windows/msys2.uniform_resource_locator");
         break;
      case e_install_strawberry_perl:
         pathUrl = path_system()->get_uniform_resource_locator("https://ca2.software/link/windows/strawberry_perl.uniform_resource_locator");
         break;
      default:
      {
         pathUrl = "";
         break;

      }

      }

      if (strName.is_empty())
      {

         strName = pathUrl.name();

      }

      return pathUrl;


   }


   void install::install_google_chrome()
   {

      install_exe();

   }


   void install::install_opera_browser()
   {

      install_exe();

   }


   void install::install_edge()
   {

      on_finished();

   }

   void install::install_smart_git()
   {

      try
      {

         set_status2("Uncompressing...");

         auto uncompressFolder = m_path.folder() / m_path.title();

         auto pathExe = file()->unzip_exe(m_path);

         set_status2("Installing...");

         node()->root_execute_sync(pathExe, "/silent /norestart", 20_min, pathExe.folder());

      }
      catch (...)
      {

      }

      on_finished();

   }

   bool application::__is_visual_studio_installed()
   {

      if (!node()->_is_visual_studio_installed())
      {

         return false;

      }

      return true;

   }


#ifdef WINDOWS_DESKTOP

   bool application::__is_msys2_installed()
   {
      bool bInstalled = node()->_is_msys2_installed();

      if (bInstalled)
      {

         //auto p = message_box("Git is installed", "Git is installed", e_message_box_ok);

         //p->do_synchronously();

      }
      else
      {

      }

      return bInstalled;

   }


   bool application::__is_strawberry_perl_installed()
   {


      bool bInstalled = node()->_is_strawberry_perl_installed();

      if (bInstalled)
      {

         //auto p = message_box("Git is installed", "Git is installed", e_message_box_ok);

         //p->do_synchronously();

      }
      else
      {

      }

      return bInstalled;


   }


#endif


   bool application::__is_tortoise_git_installed()
   {

      bool bInstalled = node()->_is_tortoise_git_installed();

      return bInstalled;

   }


   void install::_run_msi_exec()
   {

      m_papp->queue(id_system_install)->sync([this]()
         {

            try
            {

               auto strExit = _install_exe(m_path);
               //::property_set set;

               ////auto pathPowerShell = node()->_get_power_shell_path();

               //::string strParams;

               //strParams = "start /wait msiexec.exe /package \"" + m_path.name() + "\" /quiet /passive";

               //int iExitCode = node()->command_system(strParams, 2_hour, m_path.folder());

               //::string strExit;

               //if (iExitCode == 0)
               //{

               //   strExit = "Installed";

               //}
               //else
               //{

               //   strExit = "Failed to install";

               //}

               _on_after_msi_exec();

               set_status2(strExit);

               information(strExit);

            }
            catch (...)
            {

            }

            on_finished();

         }, 30_min);

   }


   ::string install::_install_exe(const ::file::path& path)
   {

      try
      {

         ::property_set set;

         //auto pathPowerShell = node()->_get_power_shell_path();

         int iExitCode = node()->shell_execute_sync(path, "", 10_minutes, path.folder());

         ::string strExit;

         if (iExitCode == 0)
         {

            strExit = "Installed";

         }
         else
         {

            strExit = "Failed to install";

         }

         return strExit;

      }
      catch (...)
      {

      }

      return "Failed to install (2)";

   }


   void install::install_exe()
   {

      m_papp->queue(id_system_install)->sync([this]()
         {

            _install_exe(m_path);

            on_finished();

         }, 30_min);

   }


   void install::install_git_scm()
   {

      try
      {

         ::file::path pathInf = "C:/operating_system/git-scm.inf";

         if (!file_system()->exists(pathInf))
         {

            ::file::path pathUrl = "https://ca2.software/download/windows/git-scm.inf";

            ::property_set set;

            set["raw_http"] = true;

            m_papp->http()->download(pathInf, pathUrl, set);

         }

         ::string str2;

         str2 = "Installing";

         set_status2(str2);

         int iExitCode = node()->command_system(m_path + " /verysilent /loadinf=" + pathInf, 2_hour);

         ::string strExit;

         if (iExitCode == 0)
         {

            strExit = "Installed";

         }
         else
         {

            strExit = "Failed to install";

         }

         set_status2(strExit);

         information(strExit);

         auto tracefunction = ::std_inline_log();

         tracefunction.set_timeout(5_min);

         int iExitCode2 = node()->posix_shell_command("git config --global core.symlinks true", e_posix_shell_git_bash, tracefunction);

      }
      catch (...)
      {
      }

      on_finished();

   }


   bool application::__is_git_scm_installed()
   {

      bool bGitInstalled = node()->has_posix_shell_command("git", e_posix_shell_git_bash);

      if (bGitInstalled)
      {

         //auto p = message_box("Git is installed", "Git is installed", e_message_box_ok);

         //p->do_synchronously();

      }
      else
      {

      }

      return bGitInstalled;

   }

#if JETBRAINS_CLION
   void install::install_clion()
   {


   }
#endif // JETBRAINS_CLION


   void install::install_patch_shell()
   {

      information() << "install_patch_shell";

      ::file::path pathPatchShell = "C:/operating_system/tool-windows/bin/patch_shell";

      while (!file_system()->exists(pathPatchShell))
      {

         set_status2("patch_shell still doesn't exist (\"" + pathPatchShell + "\")");

         preempt(1_s);

      }

      information() << "Gonna run command : " << pathPatchShell;

      int iExitCode = node()->synchronous_posix_terminal("cd " + windows_bash_path(pathPatchShell.folder()) + "; ./" + pathPatchShell.name());

      information() << "patch shell exit code : " << iExitCode;

      ::string strPath;

      if (!node()->_is_code_exe_user_path_environment_variable_ok(&strPath))
      {

         node()->set_environment_variable("PATH", strPath);

      }

      on_finished();

   }



   int install::synchronous_posix_terminal(const ::scoped_string& scopedstr)
   {

      int iExitCode = node()->synchronous_posix_terminal(
         scopedstr,
         e_posix_shell_system_default,
         [this](auto etracelevel, auto str, bool bCarriage)
         {

            set_status2(str);

         });

      return iExitCode;

   }


   //bool install::are_fonts_installed()
   //{

   //   auto ___fontsFolder = node()->___fonts_folder();

   //   check_fonts_installed_at_folder(___fontsFolder);

   //}


   void install::install_user_fonts_from_font_listing(const ::file::path & pathListing)
   {

      node()->root_execute_sync("C:\\operating_system\\bin\\application_build_helper.exe", "--install-fonts-from-folder-listing=" + pathListing);

   }


   void install::install_setup_folders()
   {

      install_cloud_data_provider();

      install_user_ssh_keys();

      install_user_fonts();

      on_finished();

   }


   void install::install_cloud_listed_repositories()
   {

      auto psummary = node()->operating_system_summary();

      ::file::path pathFolder = directory_system()->home();

      //::file::path pathDropboxBin = directory_system()->home() / "bin/dropbox";

      //::string strDropboxCommand(pathDropboxBin);

      ::file::path pathIndex = directory_system()->home() / "application/integration/code/___repositories/index.txt";

      auto pathSourceFolder = m_papp->cloud_folder() / "box/.repositories";

      auto pfscloudfolder = m_papp->current_fs_folder_sync();

      auto pathSourceIndex = pathSourceFolder / "index.txt";

      set_status2(
         "Checking for index.txt at "+pathSourceFolder+"... (index.txt should exist to continue installation with code...)");

      while (true)
      {

         if (pfscloudfolder->file_exists(pathSourceIndex))
         {

            break;

         }

         preempt(1_s);

      }

      set_status2("Checking if index.txt is up-to-date and present...");

      directory_system()->change_current(pathSourceFolder);

      ::string_array lines;

      ::string strIndex;

      while (true)
      {

         preempt(1_s);

         ::string strLs;

         strIndex = pfscloudfolder->safe_get_string(pathSourceIndex);

         lines.add_lines(strIndex);

         if (lines.size() >= 7)
         {

            lines.erase_empty();

            if (lines[0] == "empty")
            {

               break;

            }

         }

         strIndex.trim();

         lines.erase_empty();

         lines.erase_duplicates();

         if (lines.size() > 0)
         {

            break;

         }

      }

      if (lines.is_empty() || lines.first().trimmed().case_insensitive_equals("(empty)"))
      {

         set_status2("index.txt is (empty) so installing simple repository");

         install_app_simple_repository();

      }
      else
      {

         for (auto & strLine : lines)
         {

            set_status2("Installing repository \"" + strLine + "\"...");

            _install_repository(strLine);

         }

      }

      if (m_papp->__are_repositories_installed(strIndex))
      {

         file_system()->copy(pathIndex, pathSourceIndex, true);

      }

      on_finished();

   }


} // namespace coding



