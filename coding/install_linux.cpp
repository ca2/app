//
// Created by camilo on 2024-05-28 23:36 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application.h"
#include "install.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/platform/node.h"
#include "acme/nano/nano.h"
#include "acme/nano/archive/archive.h"
#include "acme/nano/http/http.h"
#include "acme/platform/system.h"
#include "acme/operating_system/summary.h"
//#include "apex/filesystem/fs/folder_sync.h"
#include <sys/stat.h>


#include "acme/constant/windowing2.h"


namespace coding
{


   ::string install::get_latest_git_credential_manager_download_url()
   {

      auto strUrl = "https://github.com/git-ecosystem/git-credential-manager/releases/latest";

      informationf("gonna get effective url of : %s", strUrl);

      ::property_set set;

      auto strRedir = http()->get_effective_url(strUrl, set).as_string();

      auto pszRedir = strRedir.c_str();

      informationf("latest release url : %s", pszRedir);

      ::file::path pathRedir = strRedir;

      ::string strRel = pathRedir.name();

      ::string strNum = strRel;

      strNum.case_insensitive_begins_eat("v");

      auto psummary = node()->operating_system_summary();

      ::string strDownload;

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {
         strDownload.formatf(
            "https://github.com/git-ecosystem/git-credential-manager/releases/download/%s/gcm-linux_amd64.%s.deb",
            strRel.c_str(),
            strNum.c_str());
      }
      else
      {
         strDownload.formatf(
            "https://github.com/git-ecosystem/git-credential-manager/releases/download/%s/gcm-linux_amd64.%s.tar.gz",
            strRel.c_str(),
            strNum.c_str());
      }

      ::file::path pathSource = strDownload;

      informationf("latest_git_credential_manager : %s", pathSource.c_str());

      return pathSource;

      //      auto pathDownload = directory_system()->download() / pathSource.name();
      //
   }


   ::file::path install::get_download_url(::string& strName)
   {

      ::file::path pathUrl;

      auto psummary = node()->operating_system_summary();


      // strName = "VisualStudioSetup.exe";

      switch (m_einstall)
      {
      case e_install_jetbrains_clion:
         //pathUrl = "https://download.jetbrains.com/cpp/CLion-2024.1.2.tar.gz";
         pathUrl = m_papp->fetch_download_link("linux/clion");
         break;
      case e_install_jetbrains_toolbox:
         pathUrl = "https://download.jetbrains.com/toolbox/jetbrains-toolbox-2.3.2.31487.tar.gz";
         break;
      case e_install_browser:
         {
         m_papp->__google_chrome_download_url();
         }
         break;
      case e_install_visual_studio_code:
         {

         if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
            {

               ::string strRedirectingUrl = "https://code.visualstudio.com/sha/download?build=stable&os=linux-deb-x64";

               ::property_set set;

               pathUrl = http()->get_effective_url(strRedirectingUrl, set).as_string();

               strName = "visual_studio_code.deb";

            }
            else
            {

               pathUrl = "()";

            }

         }
         break;
      case e_install_tortoise_git:
         pathUrl = "https://download.tortoisegit.org/tgit/2.15.0.0/TortoiseGit-2.15.0.0-64bit.msi";
         break;
      case e_install_git_credential_manager:
         pathUrl = get_latest_git_credential_manager_download_url();
         break;
      case e_install_visual_studio:
         pathUrl =
            "https://c2rsetup.officeapps.live.com/c2r/downloadVS.aspx?sku=community&channel=Release&version=VS2022&source=VSLandingPage";
         strName = "VisualStudioSetup.exe";
         break;
      case e_install_smart_git:
         //pathUrl = "https://www.syntevo.com/downloads/smartgit/smartgit-linux-23_1_3.tar.gz";
         pathUrl = m_papp->fetch_download_link("linux/smartgit");
         break;
      case e_install_msys2:
         pathUrl = path_system()->get_uniform_resource_locator(
            "https://ca2.software/link/windows/msys2.uniform_resource_locator");
         break;
      case e_install_strawberry_perl:
         pathUrl = path_system()->get_uniform_resource_locator(
            "https://ca2.software/link/windows/strawberry_perl.uniform_resource_locator");
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


   // void install::dropbox_exclude_all_except(const ::string_array& straInclude)
   // {
   //
   //    auto pfsfoldersyncDropbox = application()->fs_folder_sync("dropbox");
   //
   //    bool bShouldRemoveFromExclusion = false;
   //
   //    pfsfoldersyncDropbox->m_iStableOkCount = 0;
   //
   //    ::string_array straExclusionList;
   //
   //    ::function<void(const ::scoped_string&)> callbackStatus = [this](const ::scoped_string& scopedstr)
   //    {
   //
   //       set_status2(scopedstr);
   //
   //    };
   //
   //    while (::task_get_run())
   //    {
   //
   //       restart:
   //
   //       auto straExclude = pfsfoldersyncDropbox->ls_folder("", callbackStatus);
   //
   //       straExclude.erase(straInclude);
   //
   //       auto straToExclude = straExclude;
   //
   //       straToExclude.erase(straExclusionList);
   //
   //       if (straToExclude.has_elements())
   //       {
   //
   //          pfsfoldersyncDropbox->sync_exclude(straToExclude, callbackStatus);
   //
   //       }
   //
   //       if (bShouldRemoveFromExclusion)
   //       {
   //
   //          pfsfoldersyncDropbox->sync_reinclude(straInclude, callbackStatus);
   //
   //          bShouldRemoveFromExclusion = false;
   //
   //       }
   //
   //       for (::collection::index j = 0; j < 12; j++)
   //       {
   //
   //          set_status2("Excluding other folders from synchronization... please wait...");
   //
   //          straExclusionList = pfsfoldersyncDropbox->sync_exclusion_list(callbackStatus);
   //
   //          if (pfsfoldersyncDropbox->has_operation_error())
   //          {
   //
   //             pfsfoldersyncDropbox->m_iStableOkCount = 0;
   //
   //             continue;
   //
   //          }
   //
   //          if (straExclusionList.is_empty())
   //          {
   //
   //             set_status2("At least one extra folder other than box should exist at Dropbox folder...");
   //
   //             pfsfoldersyncDropbox->m_iStableOkCount = 0;
   //
   //             continue;
   //
   //          }
   //
   //          bool bOk = true;
   //
   //          for (auto& str : straExclusionList)
   //          {
   //
   //             if (straInclude.contains(str))
   //             {
   //
   //                bShouldRemoveFromExclusion = true;
   //
   //                bOk = false;
   //
   //                pfsfoldersyncDropbox->m_iStableOkCount = 0;
   //
   //                goto restart;
   //
   //             }
   //
   //          }
   //
   //          if(bOk)
   //          {
   //
   //             for (auto& strExclude : straExclude)
   //             {
   //
   //                if (!straExclusionList.contains(strExclude))
   //                {
   //
   //                   bOk = false;
   //
   //                   pfsfoldersyncDropbox->m_iStableOkCount  = 0;
   //
   //                   goto restart;
   //
   //                }
   //
   //             }
   //
   //          }
   //
   //          if(bOk)
   //          {
   //
   //             for (auto& strExclude : straExclude)
   //             {
   //
   //                auto path = pfsfoldersyncDropbox->local_folder_path() / strExclude;
   //
   //                if(directory_system()->is(path))
   //                {
   //
   //                   bOk = false;
   //
   //                   break;
   //
   //                }
   //
   //             }
   //
   //          }
   //
   //          if(bOk)
   //          {
   //
   //             for (auto& strExclude : straExclusionList)
   //             {
   //
   //                auto path = pfsfoldersyncDropbox->local_folder_path() / strExclude;
   //
   //                if(directory_system()->is(path))
   //                {
   //
   //                   bOk = false;
   //
   //                   break;
   //
   //                }
   //
   //             }
   //
   //          }
   //
   //          if (bOk)
   //          {
   //
   //             bShouldRemoveFromExclusion = false;
   //
   //             pfsfoldersyncDropbox->m_iStableOkCount++;
   //
   //             if (pfsfoldersyncDropbox->m_iStableOkCount >= 8)
   //             {
   //
   //                return;
   //
   //             }
   //
   //          }
   //          else
   //          {
   //
   //             pfsfoldersyncDropbox->m_iStableOkCount = 0;
   //
   //          }
   //
   //       }
   //
   //    }
   //
   // }


   // void install::dropbox_include_box()
   // {
   //
   //     int iStableOkCount = 0;
   //
   //     while(::task_get_run())
   //     {
   //
   //         ::string strLs1;
   //
   //         int iExitCode1 = node()->get_posix_shell_command_output(
   //             strLs1, dropbox_client() + " exclude remove box");
   //
   //         for(::collection::index j = 0; j < 12; j++)
   //         {
   //
   //             set_status2("Excluding box folder from synchronization exclusion... please wait...");
   //
   //             preempt(5_s);
   //
   //             ::string strLs;
   //
   //             int iExitCode = node()->get_posix_shell_command_output(
   //                 strLs, dropbox_client() + " exclude list");
   //
   //             auto pszLs = strLs.c_str();
   //
   //             print_line(pszLs);
   //
   //             ::string_array stra;
   //
   //             stra.add_lines(pszLs);
   //
   //             if (stra.has_element())
   //             {
   //
   //                 ::string strFirstLine = stra.first();
   //
   //                 if (strFirstLine.case_insensitive_begins("excluded:"))
   //                 {
   //
   //                     if (!stra.contains("box"))
   //                     {
   //
   //                         iStableOkCount++;
   //
   //                         if(iStableOkCount >= 8)
   //                         {
   //
   //                             return;
   //
   //                         }
   //
   //                     }
   //                     else
   //                     {
   //
   //                         iStableOkCount = 0;
   //
   //                     }
   //
   //                 }
   //                 else
   //                 {
   //
   //                     iStableOkCount = 0;
   //
   //                 }
   //
   //             }
   //             else
   //             {
   //
   //                 iStableOkCount = 0;
   //
   //             }
   //
   //         }
   //
   //     }
   //
   // }


   // void install::dropbox_exclude_all_except_box()
   // {
   //
   //    dropbox_exclude_all_except({"box"});
   //
   //    //dropbox_exclude_all();
   //
   //    //dropbox_include_box();
   //
   // }

   //
   // bool install::dropbox_is_box_excluded()
   // {
   //
   //    bool bBoxExcludedFromSyncing = true;
   //
   //    int iStableResponseCount = 0;
   //
   //    while (true)
   //    {
   //
   //       preempt(1_s);
   //
   //       ::string strLs;
   //
   //       int iExitCode = node()->get_posix_shell_command_output(
   //          strLs, dropbox_client() + " exclude list");
   //
   //       auto pszLs = strLs.c_str();
   //
   //       print_line(pszLs);
   //
   //       ::string_array stra;
   //
   //       stra.add_lines(pszLs);
   //
   //       if (stra.has_element())
   //       {
   //
   //          ::string strFirstLine = stra.first();
   //
   //          if (strFirstLine.case_insensitive_begins("excluded:"))
   //          {
   //
   //             auto bResponse = stra.contains("box");
   //
   //             if (is_equal(bResponse, bBoxExcludedFromSyncing))
   //             {
   //
   //                iStableResponseCount++;
   //
   //                if (iStableResponseCount >= 5)
   //                {
   //
   //                   break;
   //
   //                }
   //
   //             }
   //             else
   //             {
   //
   //                iStableResponseCount = 0;
   //
   //                bResponse = bBoxExcludedFromSyncing;
   //
   //             }
   //
   //          }
   //
   //       }
   //
   //    }
   //
   //    return bBoxExcludedFromSyncing;
   //
   // }
   //
   //
   // bool install::_install_dropbox()
   // {
   //
   //    ::file::path pathHomeFolder = directory_system()->home();
   //
   //    ::file::path pathDropboxBin = pathHomeFolder / "bin/dropbox";
   //
   //    if (!m_papp->has_Dropbox_folder())
   //    {
   //
   //       m_papp->m_bJustCreatedDropboxFolder = true;
   //
   //       ::file::path pathUrl = "https://www.dropbox.com/download?plat=lnx.x86_64";
   //
   //       download_and_gzuntar(pathUrl, pathHomeFolder);
   //
   //       set_status2("Starting Dropbox daemon...");
   //
   //       node()->detached_command(pathHomeFolder / ".dropbox-dist/dropboxd &", {});
   //
   //       m_papp->m_bJustInstalledDropbox = true;
   //
   //    }
   //
   //    if (!file_system()->exists(pathDropboxBin))
   //    {
   //
   //       set_status2("Installing Dropbox client...");
   //
   //       ::file::path pathUrl = "https://www.dropbox.com/download?dl=packages/dropbox.py";
   //
   //       ::file::path pathFinalUrl = http()->get_effective_url(pathUrl).as_string();
   //
   //       auto pszFinalUrl = pathFinalUrl.c_str();
   //
   //       auto path = download_to_downloads_code__(pathFinalUrl, "dropbox");
   //
   //       file_system()->copy(pathDropboxBin, path, true);
   //
   //       chmod(pathDropboxBin, S_IRWXU);
   //
   //       m_papp->m_bJustInstalledDropbox = true;
   //
   //    }
   //
   //    {
   //
   //       ::function<void(const ::scoped_string&)> callbackStatus = [this](auto & str)
   //       {
   //          set_status2(str);
   //       };
   //
   //       set_status2("Waitin Dropbox daemon...");
   //
   //       auto pfoldersync = m_papp->current_fs_folder_sync();
   //
   //       if (pfoldersync)
   //       {
   //
   //          pfoldersync->wait_up_and_running(callbackStatus);
   //
   //       }
   //
   //    }
   //
   //    return m_papp->m_bJustInstalledDropbox;
   //
   // }
   //
   //
   // void install::defer_setup_dropbox()
   // {
   //
   //    bool bJustInstalledDropbox = m_papp->m_bJustInstalledDropbox;
   //
   //    set_status2("Waiting for Dropbox to be up and running... please wait...");
   //
   //    {
   //
   //       auto pfoldersync = m_papp->current_fs_folder_sync();
   //
   //       if (pfoldersync)
   //       {
   //
   //          pfoldersync->wait_up_and_running();
   //
   //       }
   //
   //    }
   //
   //    if (bJustInstalledDropbox
   //       ||
   //       (m_papp->m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization.is_checked()))
   //    {
   //
   //       set_status2("Limiting Dropbox synchronization to just \"box\" folder... please wait...");
   //
   //       dropbox_exclude_all_except_box();
   //
   //    }
   //    else
   //    {
   //
   //       set_status2(
   //          "Checking that \"box\" folder is not excluded from Dropbox synchronization... please wait...");
   //
   //       bool bBoxExcludedFromSyncing = dropbox_is_box_excluded();
   //
   //       if (bBoxExcludedFromSyncing)
   //       {
   //
   //          set_status2("Removing \"box\" from Dropbox synchronization exclusion list... please wait...");
   //
   //          dropbox_exclude_all_except_box();
   //
   //       }
   //
   //    }
   //
   // }


   void install::install_setup_folders()
   {

//      defer_setup_cloud_data_provider();

      install_user_ssh_keys();

      // auto psummary = node()->operating_system_summary();
      //
      // ::file::path pathFolder = directory_system()->home();
      //
      // {
      //     set_status2("Setting up SSH keys... please wait...");
      //
      //     ::file::path pathSourceFolder = directory_system()->home() / "Dropbox/box/ca2/id";
      //
      //     ::file::path pathTargetFolder = directory_system()->home() / ".ssh";
      //
      //     ::string_array straSource;
      //
      //     straSource.add("id_auth");
      //     straSource.add("id_auth.pub");
      //     straSource.add("id_sign");
      //     straSource.add("id_sign.pub");
      //
      //     while (true)
      //     {
      //         bool bOk = true;
      //
      //         for (auto& str : straSource)
      //         {
      //             ::file::path pathSource;
      //
      //             pathSource = pathSourceFolder / str;
      //
      //             if (!file_system()->exists(pathSource))
      //             {
      //                 set_status2(pathSource + " doesn't exist");
      //
      //                 bOk = false;
      //
      //                 break;
      //             }
      //
      //             ::file::path pathTarget;
      //
      //             pathTarget = pathTargetFolder / str;
      //
      //             try
      //             {
      //                 file_system()->copy(pathTarget, pathSource, true);
      //             }
      //             catch (...)
      //             {
      //                 set_status2("Failed to copy from" + pathSource + " to " + pathTarget);
      //
      //                 bOk = false;
      //
      //                 break;
      //             }
      //
      //             if (!file_system()->exists(pathTarget))
      //             {
      //                 set_status2(pathTarget + " doesn't exist");
      //
      //                 bOk = false;
      //
      //                 break;
      //             }
      //
      //             if (pathTarget.case_insensitive_ends(".pub"))
      //             {
      //                 chmod(pathTarget, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      //             }
      //             else
      //             {
      //                 chmod(pathTarget, S_IRUSR | S_IWUSR);
      //             }
      //         }
      //
      //         if (bOk)
      //         {
      //             break;
      //         }
      //
      //         preempt(1_s);
      //     }
      // }

      install_user_fonts();

      //auto eoperatingambient = windowing::get_eoperating_ambient();

      //if (eoperatingambient & ::windowing::e_operating_ambient_gnome)
      //{

      /// please check applicability of gnome extensions for
      /// target platform at the own function (_install_gnome_extensions)
         defer_install_gnome_extensions();

         //         auto pathGnomeExtensionsFolder = directory_system()->home() / ".config/___gnome_extensions";
         //
         //         auto pathTarget = pathGnomeExtensionsFolder / "index.txt";
         //
         //         auto pathGnomeExtensionsSourceFolder = pathFolder / "Dropbox/box/___gnome_extensions";
         //
         //         auto pathGnomeExtensionsSourceIndex = pathFolder / "Dropbox/box/___gnome_extensions/index.txt";
         //
         //         if (!file_system()->exists(pathTarget))
         //         {
         //
         //            set_status2(
         //                    "Checking for index.txt gnome extensions for urls to open respective pages... (index.txt should exist to continue installation with code...)");
         //
         //            while (!directory_system()->is(pathGnomeExtensionsSourceFolder))
         //            {
         //               preempt(1_s);
         //            }
         //
         //            directory_system()->change_current(pathGnomeExtensionsSourceFolder);
         //
         //            set_status2(
         //                    "Checking for index.txt at Dropbox/box/___gnome_extensions... (index.txt should exist to continue installation with code...)");
         //
         //            while (true)
         //            {
         //
         //               if (file_system()->exists(pathGnomeExtensionsSourceIndex))
         //               {
         //
         //                  break;
         //
         //               }
         //               preempt(1_s);
         //            }
         //
         //            set_status2("Checking if index.txt is up-to-date and present...");
         //
         //            ::string_array lines;
         //
         //            lines.add("index.txt");
         //
         //            while (true)
         //            {
         //               preempt(1_s);
         //
         //               ::string strLs;
         //
         //               int iExitCode = node()->
         //                       get_posix_shell_command_output(strLs, strDropboxCommand + " dropbox filestatus");
         //
         //               auto pszLs = strLs.c_str();
         //
         //               print_line(pszLs);
         //
         //               ::string_array stra;
         //
         //               stra.add_lines(pszLs);
         //
         //               bool bOk = true;
         //               for (auto & line: lines)
         //               {
         //                  auto pszLine = line.c_str();
         //
         //                  print_line("font_at_index.txt: " + line);
         //
         //                  int iFind = stra.case_insensitive_find_first_begins(line + ":");
         //
         //                  if (iFind < 0)
         //                  {
         //                     bOk = false;
         //
         //                     break;
         //                  }
         //
         //                  auto dropboxLine = stra[iFind];
         //
         //                  if (!dropboxLine.case_insensitive_ends("up to date"))
         //                  {
         //                     bOk = false;
         //                     break;
         //                  }
         //
         //                  auto pathFile = pathGnomeExtensionsSourceFolder / line;
         //
         //                  if (!file_system()->exists(pathFile))
         //                  {
         //                     bOk = false;
         //
         //                     break;
         //                  }
         //
         //                  if (file_system()->as_string(pathFile).trimmed().is_empty())
         //                  {
         //                     bOk = false;
         //
         //                     break;
         //                  }
         //               }
         //
         //
         //               if (bOk)
         //               {
         //                  break;
         //               }
         //            }
         //
         //            {
         //
         //               auto pathSource = pathGnomeExtensionsSourceIndex;
         //
         //               file_system()->copy(pathTarget, pathSource, true);
         //
         //               auto lines = file_system()->lines(pathTarget);
         //
         //               lines.trim();
         //
         //               lines.erase_empty();
         //
         //               if (lines.has_elements())
         //               {
         //
         //                  _install("gnome-shell-extensions gnome-tweaks gnome-browser-connector");
         //
         //               }
         //
         //               for (auto line: lines)
         //               {
         //
         //                  node()->open_url_link_at_system_browser(line);
         //
         //               }
         //
         //            }
         //
         //         }
      //}

      //if (!_are_user_packages_installed())
      //{

         defer_install_user_packages();

      //}

      on_finished();

   }


   // void install::install_cloud_listed_repositories()
   // {
   //    auto psummary = node()->operating_system_summary();
   //
   //    ::file::path pathFolder = directory_system()->home();
   //
   //    ::file::path pathDropboxBin = directory_system()->home() / "bin/dropbox";
   //
   //    ::string strDropboxCommand(pathDropboxBin);
   //
   //    ::file::path pathIndex = directory_system()->home() / ".config/integration/code/___repositories/index.txt";
   //
   //    auto pathSourceFolder = pathFolder / "Dropbox/box/___repositories";
   //
   //    auto pathSourceIndex = pathSourceFolder / "index.txt";
   //
   //    set_status2(
   //       "Checking for index.txt at Dropbox/box/___repositories... (index.txt should exist to continue installation with code...)");
   //
   //    while (true)
   //    {
   //       if (file_system()->exists(pathSourceIndex))
   //       {
   //          break;
   //       }
   //       preempt(1_s);
   //    }
   //
   //    set_status2("Checking if index.txt is up-to-date and present...");
   //
   //    ::string_array lines;
   //
   //    lines.add("index.txt");
   //
   //    directory_system()->change_current(pathSourceFolder);
   //
   //    while (true)
   //    {
   //       preempt(1_s);
   //
   //       ::string strLs;
   //
   //       int iExitCode = node()->
   //          get_posix_shell_command_output(strLs, strDropboxCommand + " dropbox filestatus");
   //
   //       auto pszLs = strLs.c_str();
   //
   //       print_line(pszLs);
   //
   //       ::string_array stra;
   //
   //       stra.add_lines(pszLs);
   //
   //       bool bOk = true;
   //       for (auto& line : lines)
   //       {
   //          auto pszLine = line.c_str();
   //
   //          print_line("font_at_index.txt: " + line);
   //
   //          int iFind = stra.case_insensitive_find_first_begins(line + ":");
   //
   //          if (iFind < 0)
   //          {
   //             bOk = false;
   //
   //             break;
   //          }
   //
   //          auto dropboxLine = stra[iFind];
   //
   //          if (!dropboxLine.case_insensitive_ends("up to date"))
   //          {
   //             bOk = false;
   //             break;
   //          }
   //
   //          auto pathFile = pathSourceFolder / line;
   //
   //          if (!file_system()->exists(pathFile))
   //          {
   //             bOk = false;
   //
   //             break;
   //          }
   //
   //          if (file_system()->as_string(pathFile).trimmed().is_empty())
   //          {
   //             bOk = false;
   //
   //             break;
   //          }
   //       }
   //
   //
   //       if (bOk)
   //       {
   //          break;
   //       }
   //    }
   //
   //    set_status2("Checking if index.txt contents are ok...");
   //
   //    ::string strIndex;
   //
   //    while (true)
   //    {
   //       strIndex = file_system()->as_string(pathSourceIndex);
   //
   //       strIndex.trim();
   //
   //       if (strIndex.has_character())
   //       {
   //          break;
   //       }
   //    }
   //
   //    if (strIndex.case_insensitive_equals("(empty)"))
   //    {
   //
   //       set_status2("index.txt is (empty) so installing simple repository");
   //
   //       install_app_simple_repository();
   //
   //    }
   //    else
   //    {
   //
   //       ::string_array straLines;
   //
   //       straLines.add_lines(strIndex);
   //
   //       for (auto& strLine : straLines)
   //       {
   //
   //          set_status2("Installing repository \"" + strLine + "\"...");
   //
   //          _install_repository(strLine);
   //
   //       }
   //
   //    }
   //
   //    if (m_papp->__are_repositories_installed(strIndex))
   //    {
   //
   //       file_system()->copy(pathIndex, pathSourceIndex, true);
   //
   //    }
   //
   //    on_finished();
   //
   // }


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


   void install::install_git_scm()
   {

      //directory_system()->change_current(m_path.folder());

      //int iExitCode = node()->synchronous_posix_terminal("echo \"sudo apt install git\"; sudo apt install git");

      //informationf("sudo apt install git Exit Code : %d", iExitCode);

      defer_install_packages({"git"});

      on_finished();

   }


   void install::install_patch_shell()
   {

      information() << "install_patch_shell";

      auto pathPatchShell = directory_system()->home() / "code/operating_system/tool/bin/patch_shell";

      information() << "Gonna run command : " << pathPatchShell;

      int iExitCode = synchronous_posix_terminal("cd " + pathPatchShell.folder() + "; ./" + pathPatchShell.name());

      information() << "patch shell exit code : " << iExitCode;

      ::string strPath;

      if (!node()->_is_code_exe_user_path_environment_variable_ok(&strPath))
      {

         node()->set_environment_variable("PATH", strPath);

      }

      on_finished();

   }


   void install::install_deps()
   {

      //      auto psummary = node()->operating_system_summary();
      //
      //      if (psummary->m_strDistro.case_insensitive_equals("ubuntu"))
      //      {
      //         _install("nala");
      //
      //         ::string strCommand;
      //
      //         strCommand += "sudo nala fetch; sudo nala update; sudo nala upgrade";
      //
      //         synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
      //      }

      auto depsa = m_papp->get_install_dep_package_names();

      defer_install_packages(depsa);

      // system()->install_operating_system_packages_command_line(depsa);
      //
      // int iRetryCount = 5;
      // int iTry = 0;
      // int iFailureCount;
      //
      // int iTotalCount;
      // while (true)
      // {
      //    int iFailureCount = 0;
      //
      //    int iTotalCount = 0;
      //
      //    for (auto& deps : depsa)
      //    {
      //       ::file::path path = directory_system()->home() / "code/operating_system/tool/bin" / deps;
      //
      //       int iExitCode = synchronous_posix_terminal("echo \\\"" + path + "\\\"; " + path);
      //
      //       informationf("%s Exit Code : %d", path.c_str(), iExitCode);
      //
      //       if (iExitCode)
      //       {
      //          iFailureCount++;
      //       }
      //
      //       iTotalCount++;
      //    }
      //
      //    if (iFailureCount <= 0)
      //    {
      //       break;
      //    }
      //    iTry++;
      //
      //    if (iTry >= iRetryCount)
      //    {
      //       on_finished();
      //
      //       return;
      //    }
      // }

      //::string strSummary;

      //strSummary.formatf("Failure Count : %d, Total Count : %d", iFailureCount, iTotalCount);

      //file_system()->put_block(directory_system()->home() / ".config/integration/code/install_deps.txt", strSummary);

      on_finished();

   }


   // void install::install_deps()
   // {
   //
   //    //      auto psummary = node()->operating_system_summary();
   //    //
   //    //      if (psummary->m_strDistro.case_insensitive_equals("ubuntu"))
   //    //      {
   //    //         _install("nala");
   //    //
   //    //         ::string strCommand;
   //    //
   //    //         strCommand += "sudo nala fetch; sudo nala update; sudo nala upgrade";
   //    //
   //    //         synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
   //    //      }
   //
   //    auto depsa = m_papp->get_install_dep_script_names();
   //
   //    int iRetryCount = 5;
   //    int iTry = 0;
   //    int iFailureCount;
   //
   //    int iTotalCount;
   //    while (true)
   //    {
   //       int iFailureCount = 0;
   //
   //       int iTotalCount = 0;
   //
   //       for (auto& deps : depsa)
   //       {
   //          ::file::path path = directory_system()->home() / "code/operating_system/tool/bin" / deps;
   //
   //          int iExitCode = synchronous_posix_terminal("echo \\\"" + path + "\\\"; " + path);
   //
   //          informationf("%s Exit Code : %d", path.c_str(), iExitCode);
   //
   //          if (iExitCode)
   //          {
   //             iFailureCount++;
   //          }
   //
   //          iTotalCount++;
   //       }
   //
   //       if (iFailureCount <= 0)
   //       {
   //          break;
   //       }
   //       iTry++;
   //
   //       if (iTry >= iRetryCount)
   //       {
   //          on_finished();
   //
   //          return;
   //       }
   //    }
   //
   //    ::string strSummary;
   //
   //    strSummary.formatf("Failure Count : %d, Total Count : %d", iFailureCount, iTotalCount);
   //
   //    file_system()->put_block(directory_system()->home() / ".config/integration/code/install_deps.txt", strSummary);
   //
   //    on_finished();
   // }


   void install::install_git_credential_manager()
   {
      if (m_path.ends(".deb"))
      {
         directory_system()->change_current(m_path.folder());

         int iExitCode = synchronous_posix_terminal(
            "echo \"sudo apt install " + m_path + "\"; sudo apt install " + m_path);
      }
      else
      {
         directory_system()->change_current(m_path.folder());

         int iExitCode = synchronous_posix_terminal(
            "echo \"sudo tar -xzvf " + m_path + " -C /usr/local/bin\"; sudo tar -xzvf " + m_path +
            " -C /usr/local/bin");
      }

      int iExitCode = synchronous_posix_terminal("git-credential-manager configure");

      int iExitCode2 = node()->posix_shell_command(
         "git config --global credential.credentialStore secretservice",
         e_posix_shell_system_default,
         [this](auto etracelevel, auto str, bool bCarriage)
         {

            set_status2(str);

         });

      on_finished();

   }


   bool application::__is_git_scm_installed()
   {

      bool bGitInstalled = node()->has_posix_shell_command("git");

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


   void install::install_smart_git()
   {
      try
      {
         set_status2("Uncompressing...");

         auto pathSyntevo = directory_system()->home() / "application/syntevo";

         directory_system()->create(pathSyntevo);

         node()->posix_shell_command("tar -xzvf \""+ m_path + "\" -C \"" + pathSyntevo + "\"",
            e_posix_shell_system_default, [this](auto etracelevel, auto & str, bool bCarriage)
         {
            set_status2(str);
         });
         set_status2("Installing...");

         node()->posix_shell_command(pathSyntevo / "smartgit/bin/add-menuitem.sh");

         node()->detached_command("/bin/bash -c " + (pathSyntevo / "smartgit/bin/smartgit.sh"), {});
      }
      catch (...)
      {
      }

      on_finished();
   }


   void install::install_google_chrome()
   {
      auto psummary = node()->operating_system_summary();

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {
         _install_deb();
      }
      else
      {
         _install_rpm();
      }

      if (psummary->m_strSystem.case_insensitive_equals("debian"))
      {
         _uninstall("firefox-esr");
      }
      else
      {
         _uninstall("firefox");
      }

      if (psummary->m_strSystem.case_insensitive_equals("ubuntu"))
      {
         _snap_uninstall("firefox");
      }

      on_finished();
   }


   void install::install_visual_studio_code()
   {
      auto psummary = node()->operating_system_summary();

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {
         install_deb();

         return;
      }

      ::string strCommand;

      strCommand = "sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc; ";
      strCommand +=
         "echo -e \"[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc\" | sudo tee /etc/yum.repos.d/vscode.repo > /dev/null; ";
      strCommand += "dnf check-update; ";
      strCommand += "sudo dnf install code;";


      synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);

      on_finished();
   }


   void install::defer_install_packages(const ::string_array_base & straPackageNames)
   {

      auto straNotInstalledPackageNames = system()->not_installed_operating_system_packages(straPackageNames);

      if (straNotInstalledPackageNames.is_empty())
      {

         return;

      }

      _install_packages(straPackageNames);

   }


   void install::_install_packages(const ::string_array_base & straPackageNames)
   {

      ::string strCommand = system()->install_operating_system_packages_command_line(straPackageNames);

      synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);

   }


   void install::_uninstall(const scoped_string& scopedstrPackageName)
   {
      auto psummary = node()->operating_system_summary();

      ::string strCommand;

      strCommand = "sudo ";

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {
         strCommand += "apt remove";
      }
      else
      {
         strCommand += "dnf remove";
      }

      strCommand += " ";

      strCommand += scopedstrPackageName;

      synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
   }


   void install::_snap_uninstall(const scoped_string& scopedstrPackageName)
   {
      ::string strCommand;

      strCommand = "sudo snap remove ";

      strCommand += scopedstrPackageName;

      synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
   }


   bool install::_is_package_installed(const ::scoped_string& scopedstrPackageName)
   {
      auto psummary = node()->operating_system_summary();

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {
         ::string strCommand;

         strCommand = "apt -qq list " + scopedstrPackageName;

         ::string strOutput;

         int iExitCode = node()->get_posix_shell_command_output(strOutput, strCommand);

         if (iExitCode == 0)
         {
            strOutput.trim();

            if (strOutput.case_insensitive_ends("[installed]"))
            {
               return true;
            }
         }
      }
      else
      {
         set_status2("_is_package_installed not implemented for this distro : " + psummary->m_strSystem);
      }

      return false;
   }


   bool install::_are_user_packages_installed()
   {

      auto pathHome = directory_system()->home();

      auto pathInstallIndex = pathHome / ".config/integration/code/___install/index.txt";

      if (!file_system()->exists(pathInstallIndex))
      {

         return false;

      }

      auto lines = file_system()->lines(pathInstallIndex);

      lines.trim();

      lines.erase_empty();

      lines.erase_duplicates();

      for (auto& strInstall : lines)
      {

         if (!_is_package_installed(strInstall))
         {

            return false;

         }

      }

      return true;
   }


   // void install::_install_user_fonts()
   // {
   //     auto pathSource = _dropbox_ensure_files_in_index_txt_are_up_to_date_and_present("box/___fonts", "ttf", 1_KiB);
   //
   //     if (pathSource.has_character())
   //     {
   //     }
   // }


   void install::install_user_fonts_from_font_listing(const ::file::path& pathListing)
   {

      //        node()->root_execute_sync("C:\\operating_system\\bin\\application_build_helper.exe", "--install-fonts-from-folder-listing=" + pathListing);

      auto pathApplicationBuildHelper = directory_system()->home() / "bin/application_build_helper";

      ::file::path pathSourceFolder = pathListing.folder();

      ::string strCommand;

      strCommand = "sudo ";

      strCommand += ::string(pathApplicationBuildHelper);

      strCommand += " --install-fonts-from-folder-listing=" + ::string(pathListing);

      synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);

      node()->command_system("fc-cache -v", std_inline_log());

   }


   void install::defer_install_gnome_extensions()
   {

      auto eoperatingambient = ::windowing::get_eoperating_ambient();

      if (eoperatingambient == ::windowing::e_operating_ambient_gnome)
      {

         return;

      }

      _install_gnome_extensions();

   }


   void install::_install_gnome_extensions()
   {

//       auto path = m_papp->current_fs_folder_sync()->m_pathProtocol / ("box/___gnome_extensions/" OPERATING_SYSTEM_NAME
//          ".txt");
//
//       ::string strMessage;
//
//       strMessage.formatf("Checking for packages to install at %s", path.c_str());
//
//       set_status2(strMessage);
//
//       auto lines = m_papp->current_fs_folder_sync()->safe_get_lines(path);
//
//       lines.trim();
//
//       lines.erase_empty();
//
//       lines.erase_duplicates();
//
//       if (lines.has_elements())
//       {
//
//          _install_packages(
// {
//          "gnome-shell-extensions",
//          "gnome-tweaks",
//          "gnome-browser-connector"
//          });
//
//       }
//
//       for (auto line : lines)
//       {
//
//          node()->open_internet_link(line);
//
//       }

   }


   void install::defer_install_user_packages()
   {

      if (_are_user_packages_installed())
      {

         return;

      }

      _install_user_packages();

   }


   void install::_install_user_packages()
   {

      // auto path = m_papp->current_fs_folder_sync()->m_pathProtocol / ("box/___install/" OPERATING_SYSTEM_NAME ".txt");
      //
      // ::string strMessage;
      //
      // strMessage.formatf("Checking for packages to install at %s", path.c_str());
      //
      // set_status2(strMessage);
      //
      // auto lines = m_papp->current_fs_folder_sync()->safe_get_lines(path);
      //
      // lines.trim();
      //
      // lines.erase_empty();
      //
      // lines.erase_duplicates();
      //
      // auto straNotInstalled = system()->not_installed_operating_system_packages(lines);
      //
      // _install_packages(straNotInstalled);
      //
      // auto pathHome = directory_system()->home();
      //
      // auto pathInstallIndex = pathHome / ".config/integration/code/___install/index.txt";
      //
      // file_system()->put_lines(pathInstallIndex, lines);

   }


   void install::_install_deb()
   {

      try
      {

         print_line("Going to install .deb package : \""+m_path+"\".");

         int iExitCode = synchronous_posix_terminal(
            "echo \"sudo apt install " + m_path + "\"; sudo apt install " + m_path);
      }
      catch (...)
      {
      }
   }


   void install::_install_rpm()
   {
      try
      {
         int iExitCode = synchronous_posix_terminal(
            "echo \"sudo dnf install " + m_path + "\"; sudo dnf install " + m_path);
      }
      catch (...)
      {
      }
   }


   void install::install_deb()
   {
      _install_deb();

      on_finished();
   }


   void install::install_jetbrains_clion()
   {
      try
      {
         set_status2("Uncompressing JetBrains CLion...");

         auto pathJetbrains = directory_system()->home() / "application/jetbrains";

         auto pathClion = pathJetbrains / "clion";

         directory_system()->create(pathClion);

         node()->posix_shell_command("tar -xzvf \""+ m_path + "\" -C \"" + pathClion + "\" --strip-components=1",
            e_posix_shell_system_default, [this](auto etracelevel, auto & str, bool bCarriage)
         {
            set_status2(str);
         });

         set_status2("Installing JetBrains CLion...");

         node()->posix_shell_command(pathJetbrains / "clion/bin/clion");
      }
      catch (...)
      {
      }

      on_finished();
   }


   void install::install_jetbrains_toolbox()
   {
      try
      {
         set_status2("Uncompressing JetBrains Toolbox...");

         auto pathJetbrains = directory_system()->home() / "application/jetbrains";

         directory_system()->create(pathJetbrains / "toolbox");

         nano()->archive()->untar(pathJetbrains / "toolbox", m_path, 1, [this](auto str)
         {
            set_status2(str);
         });

         set_status2("Installing JetBrains Toolbox...");

         int iExitCode = node()->synchronous_posix_terminal(
            "echo \"sudo apt install libfuse2\"; sudo apt install libfuse2");

         int iExitCode2 = node()->posix_shell_command(pathJetbrains / "toolbox/jetbrains-toolbox");
      }
      catch (...)
      {
      }

      on_finished();
   }
} // namespace coding




// int main()
// {
//    const std::string package_name = "libgtk-4-dev";
//
//    if (is_package_installed(package_name))
//    {
//       std::cout << package_name << " is installed\n";
//    }
//    else
//    {
//       std::cout << package_name << " is NOT installed\n";
//    }
//
//    return 0;
// }