
//
//  macos.cpp
//  integration_libray
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-05.
////
//  install_macos.cpp
//  coding
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-06-30 04:50 <3ThomasBorregaardSorensen!! ThomasLikesNumber5!!
//
#include "framework.h"
#include "install.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/nano/nano.h"
#include "acme/nano/archive/archive.h"
#include "acme/platform/http.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"

#include <sys/types.h>
#include <sys/stat.h>

namespace coding
{


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
#if JETBRAINS_CLION
void install::install_jetbrains_clion()
{

}
#endif
bool install::get_debug_project_enabled()
{

//    if (!has_visible_top_level_window_named_simple__microsoft_visual_studio())
//    {
//
//       return false;
//
//    }

 return true;

}


::string install::get_latest_git_credential_manager_download_url()
{
   
   auto strUrl = "https://github.com/git-ecosystem/git-credential-manager/releases/latest";
   
   informationf("gonna get effective url of : %s", strUrl);
   
   auto strRedir = http()->get_effective_url(strUrl).as_string();
   
   auto pszRedir = strRedir.c_str();
   
   informationf("latest release url : %s", pszRedir);
   
   ::file::path pathRedir = strRedir;
   
   ::string strRel = pathRedir.name();
   
   ::string strNum = strRel;
   
   strNum.case_insensitive_begins_eat("v");
   
   auto psummary = node()->operating_system_summary();
   
   ::string strDownload;
   
//   if (psummary->m_strDistroFamily == "debian")
//   {
//      strDownload.formatf(
//                          "https://github.com/git-ecosystem/git-credential-manager/releases/download/%s/gcm-linux_amd64.%s.deb",
//                          strRel.c_str(),
//                          strNum.c_str());
//   } else
//   {
//      strDownload.formatf(
//                          "https://github.com/git-ecosystem/git-credential-manager/releases/download/%s/gcm-linux_amd64.%s.tar.gz",
//                          strRel.c_str(),
//                          strNum.c_str());
//   }
   
   ::file::path pathSource = strDownload;
   
   informationf("latest_git_credential_manager : %s", pathSource.c_str());
   
   return pathSource;
   
   //      auto pathDownload = directory_system()->download() / pathSource.name();
   //
}

//::file::path install::get_download_url(::string & strName)
//{
//   ::file::path pathUrl;
//   
//   auto psummary = node()->operating_system_summary();
//   
//   
//   // strName = "VisualStudioSetup.exe";
//   
//   switch (m_einstall)
//   {
//      case e_install_jetbrains_clion:
//         pathUrl = "https://download.jetbrains.com/cpp/CLion-2024.1.2.tar.gz";
//         break;
//      case e_install_jetbrains_toolbox:
//         pathUrl = "https://download.jetbrains.com/toolbox/jetbrains-toolbox-2.3.2.31487.tar.gz";
//         break;
//      case e_install_browser:
//      {
////         if (psummary->m_strDistroFamily == "debian")
////         {
////            pathUrl = "https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb";
////         } else if (psummary->m_strDistro == "fedora" || psummary->m_strDistro == "opensuse")
////         {
////            pathUrl = "https://dl.google.com/linux/direct/google-chrome-stable_current_x86_64.rpm";
////         }
//         
//      }
//         break;
//      case e_install_visual_studio_code:
//      {
//         ::string strRedirectingUrl = "https://code.visualstudio.com/sha/download?build=stable&os=linux-deb-x64";
//         
//         pathUrl = system()->http_get_effective_url(strRedirectingUrl);
//      }
//         break;
//      case e_install_tortoise_git:
//         pathUrl = "https://download.tortoisegit.org/tgit/2.15.0.0/TortoiseGit-2.15.0.0-64bit.msi";
//         break;
//      case e_install_git_credential_manager:
//         pathUrl = get_latest_git_credential_manager_download_url();
//         break;
//      case e_install_visual_studio:
//         pathUrl =
//         "https://c2rsetup.officeapps.live.com/c2r/downloadVS.aspx?sku=community&channel=Release&version=VS2022&source=VSLandingPage";
//         strName = "VisualStudioSetup.exe";
//         break;
//      case e_install_smart_git:
//         pathUrl = "https://www.syntevo.com/downloads/smartgit/smartgit-linux-23_1_3.tar.gz";
//         break;
//      case e_install_msys2:
//         pathUrl = path_system()->get_uniform_resource_locator(
//                                                            "https://ca2.software/link/windows/msys2.uniform_resource_locator");
//         break;
//      case e_install_strawberry_perl:
//         pathUrl = path_system()->get_uniform_resource_locator(
//                                                            "https://ca2.software/link/windows/strawberry_perl.uniform_resource_locator");
//         break;
//      default:
//      {
//         pathUrl = "";
//         break;
//      }
//   }
//   
//   if (strName.is_empty())
//   {
//      strName = pathUrl.name();
//   }
//   
//   return pathUrl;
//}


//void install::wait_dropbox_installed()
//{
//   
//   ::file::path pathHomeFolder = directory_system()->home();
//
//   ::file::path pathDropboxBin = directory_system()->home() / "bin/dropbox";
//
//   if (!directory_system()->is(pathHomeFolder / "Dropbox"))
//   {
//      
//      set_status2("Waiting for Dropbox folder creation... please wait...");
//      
//      while (!directory_system()->is(pathHomeFolder / "Dropbox"))
//      {
//         preempt(1_s);
//      }
//      
//   }
//   
//   set_status2("Waiting for Dropbox service start responding... please wait...");
//   
//   directory_system()->change_current(pathHomeFolder / "Dropbox");
//   
//   int iTryStart = 0;
//   
//   int iRetryStart = 3;
//   
//   class ::time timeLastTryStart;
//   
//   int iExitCodeLastTryStart = -1;
//   
//   ::string strOutputLastTryStart;
//   
//   while (true)
//   {
//      
//      preempt(1_s);
//      
//      ::string strLs;
//      
//      int iExitCode = node()->get_posix_shell_command_output(strLs, pathDropboxBin + " exclude list");
//      
//      auto pszLs = strLs.c_str();
//      
//      print_line(pszLs);
//      
//      ::string_array stra;
//      
//      stra.add_lines(pszLs);
//      
//      if (stra.has_element())
//      {
//         ::string strFirstLine = stra.first();
//         
//         if (strFirstLine.contains("isn't running"))
//         {
//            
//            if (iTryStart < iRetryStart)
//            {
//               
//               if (iTryStart == 0 || timeLastTryStart.elapsed() > 30_s)
//               {
//                  
//                  iTryStart++;
//                  
//                  iExitCodeLastTryStart = node()->get_posix_shell_command_output(strOutputLastTryStart,
//                                                                                 pathDropboxBin + " start");
//                  
//                  timeLastTryStart.Now();
//                  
//               }
//               
//            }
//            
//         }
//         else if (strFirstLine.case_insensitive_begins("excluded:"))
//         {
//            break;
//         }
//         else
//         {
//            if (!strFirstLine.case_insensitive_contains("respond"))
//            {
//               break;
//            }
//         }
//      }
//   }
//   
//}


void install::defer_setup_dropbox()
{

   
}


bool install::dropbox_is_box_excluded()
{
 
   return false;
   
}


void install::dropbox_exclude_all_except(const ::string_array & straInclude)
{
   
   
}


void install::dropbox_exclude_all_except_box()
{
   
   
}


void install::install_cloud_listed_repositories()
{
   
   
}


void install::install_user_fonts_from_font_listing(const ::file::path & pathListing)
{
 
   
}


bool install::_install_dropbox()
{
   
   bool bJustCreatedDropboxFolder = false;
   
   ::file::path pathHomeFolder = directory_system()->home();
   
   ::file::path pathDropboxBin = pathHomeFolder / "bin/dropbox";
   
   if (!m_papp->has_Dropbox_folder())
   {
      
      bJustCreatedDropboxFolder = true;
      
      ::file::path pathUrl = "https://www.dropbox.com/download?plat=lnx.x86_64";
      
      download_and_gzuntar(pathUrl, pathHomeFolder);
      
      node()->detached_command(pathHomeFolder / ".dropbox-dist/dropboxd &", {});
      
   }
   
   if (!file_system()->exists(pathDropboxBin))
   {
      
      ::file::path pathUrl = "https://www.dropbox.com/download?dl=packages/dropbox.py";
      
      auto urlFinal = http()->get_effective_url(pathUrl);
      
      //auto pszFinalUrl = pathFinalUrl.c_str();
      
      auto path = download_to_downloads_code__(urlFinal.as_string(), "dropbox");
      
      file_system()->copy(pathDropboxBin, path, true);
      
      chmod(pathDropboxBin, S_IRWXU);
      
   }
   
   return bJustCreatedDropboxFolder;
   
}


void install::install_setup_folders()
{
   
   auto psummary = node()->operating_system_summary();
   
   ::file::path pathFolder = directory_system()->home();
   
   {
      
      {
         
         bool bJustCreatedDropboxFolder = false;
         
         bJustCreatedDropboxFolder = _install_dropbox();
         
         //wait_dropbox_installed();
         
//         if (bJustCreatedDropboxFolder
//             || m_papp->m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization.is_checked())
//         {
//            
//            set_status2("Limiting Dropbox synchronization to just \"box\" folder... please wait...");
//            
//            while (true)
//            {
//               preempt(1_s);
//               
//               ::string strLs1;
//               
//               int iExitCode1 = node()->get_posix_shell_command_output(
//                                                                       strLs1, m_strDropboxCommand + " exclude add *");
//               
//               ::string strLs2;
//               
//               int iExitCode2 = node()->get_posix_shell_command_output(
//                                                                       strLs2, m_strDropboxCommand + " exclude remove box");
//               
//               ::string strLs;
//               
//               int iExitCode = node()->get_posix_shell_command_output(
//                                                                      strLs, m_strDropboxCommand + " exclude list");
//               
//               auto pszLs = strLs.c_str();
//               
//               print_line(pszLs);
//               
//               ::string_array stra;
//               
//               stra.add_lines(pszLs);
//               
//               if (stra.has_element())
//               {
//                  ::string strFirstLine = stra.first();
//                  
//                  if (strFirstLine.case_insensitive_begins("excluded:"))
//                  {
//                     if (!stra.contains("box"))
//                     {
//                        break;
//                     }
//                  }
//               }
//            }
//         } else
//         {
//            
//            set_status2(
//                        "Checking that \"box\" folder is not excluded from Dropbox synchronization... please wait...");
//            
//            bool bBoxExcludedFromSyncing = true;
//            
//            while (true)
//            {
//               
//               preempt(1_s);
//               
//               ::string strLs;
//               
//               int iExitCode = node()->get_posix_shell_command_output(
//                                                                      strLs, m_strDropboxCommand + " exclude list");
//               
//               auto pszLs = strLs.c_str();
//               
//               print_line(pszLs);
//               
//               ::string_array stra;
//               
//               stra.add_lines(pszLs);
//               
//               if (stra.has_element())
//               {
//                  ::string strFirstLine = stra.first();
//                  
//                  if (strFirstLine.case_insensitive_begins("excluded:"))
//                  {
//                     
//                     bBoxExcludedFromSyncing = stra.contains("box");
//                     
//                     break;
//                  }
//               }
//            }
//            
//            if (bBoxExcludedFromSyncing)
//            {
//               
//               set_status2("Removing \"box\" from Dropbox synchronization exclusion list... please wait...");
//               
//               while (true)
//               {
//                  preempt(1_s);
//                  
//                  ::string strLs1;
//                  
//                  int iExitCode1 = node()->get_posix_shell_command_output(
//                                                                          strLs1, m_strDropboxCommand + " exclude add *");
//                  
//                  ::string strLs2;
//                  
//                  int iExitCode2 = node()->get_posix_shell_command_output(
//                                                                          strLs2, m_strDropboxCommand + " exclude remove box");
//                  
//                  ::string strLs;
//                  
//                  int iExitCode = node()->get_posix_shell_command_output(
//                                                                         strLs, m_strDropboxCommand + " exclude list");
//                  
//                  auto pszLs = strLs.c_str();
//                  
//                  print_line(pszLs);
//                  
//                  ::string_array stra;
//                  
//                  stra.add_lines(pszLs);
//                  
//                  if (stra.has_element())
//                  {
//                     ::string strFirstLine = stra.first();
//                     
//                     if (strFirstLine.case_insensitive_begins("excluded:"))
//                     {
//                        if (!stra.contains("box"))
//                        {
//                           break;
//                        }
//                     }
//                  }
//               }
//            }
//            
//         }
         
         
      }
      
      set_status2("Setting up SSH keys... please wait...");
      
      ::file::path pathSourceFolder = directory_system()->home() / "Dropbox/box/ca2/id";
      
      ::file::path pathTargetFolder = directory_system()->home() / ".ssh";
      
      ::string_array straSource;
      
      straSource.add("id_auth");
      straSource.add("id_auth.pub");
      straSource.add("id_sign");
      straSource.add("id_sign.pub");
      
      while (true)
      {
         bool bOk = true;
         
         for (auto & str: straSource)
         {
            ::file::path pathSource;
            
            pathSource = pathSourceFolder / str;
            
            if (!file_system()->exists(pathSource))
            {
               set_status2(pathSource + " doesn't exist");
               
               bOk = false;
               
               break;
            }
            
            ::file::path pathTarget;
            
            pathTarget = pathTargetFolder / str;
            
            try
            {
               file_system()->copy(pathTarget, pathSource, true);
            }
            catch (...)
            {
               set_status2("Failed to copy from" + pathSource + " to " + pathTarget);
               
               bOk = false;
               
               break;
            }
            
            if (!file_system()->exists(pathTarget))
            {
               set_status2(pathTarget + " doesn't exist");
               
               bOk = false;
               
               break;
            }
            
            if (pathTarget.case_insensitive_ends(".pub"))
            {
               chmod(pathTarget, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            } else
            {
               chmod(pathTarget, S_IRUSR | S_IWUSR);
            }
         }
         
         if (bOk)
         {
            break;
         }
         
         preempt(1_s);
      }
   }
   
   install_user_fonts();
//
//   if (!_are_user_packages_installed())
//   {
//      
//      _install_user_packages();
//      
//   }
//   
   on_finished();
   
}


//void install::install_repositories()
//{
//   
//   auto psummary = node()->operating_system_summary();
//   
//   ::file::path pathFolder = directory_system()->home();
//   
//   ::file::path pathDropboxBin = directory_system()->home() / "bin/dropbox";
//   
//   ::string strDropboxCommand(pathDropboxBin);
//   
//   ::file::path pathIndex = directory_system()->home() / ".config/integration/code/___repositories/index.txt";
//   
//   auto pathSourceFolder = pathFolder / "Dropbox/box/___repositories";
//   
//   auto pathSourceIndex = pathSourceFolder / "index.txt";
//   
//   set_status2(
//               "Checking for index.txt at Dropbox/box/___repositories... (index.txt should exist to continue installation with code...)");
//   
//   while (true)
//   {
//      
//      if (file_system()->exists(pathSourceIndex))
//      {
//         
//         break;
//         
//      }
//      preempt(1_s);
//   }
//   
//   set_status2("Checking if index.txt is up-to-date and present...");
//   
//   ::string_array lines;
//   
//   lines.add("index.txt");
//   
//   directory_system()->change_current(pathSourceFolder);
//   
//   while (true)
//   {
//      preempt(1_s);
//      
//      ::string strLs;
//      
//      int iExitCode = node()->
//      get_posix_shell_command_output(strLs, strDropboxCommand + " dropbox filestatus");
//      
//      auto pszLs = strLs.c_str();
//      
//      print_line(pszLs);
//      
//      ::string_array stra;
//      
//      stra.add_lines(pszLs);
//      
//      bool bOk = true;
//      for (auto & line: lines)
//      {
//         auto pszLine = line.c_str();
//         
//         print_line("font_at_index.txt: " + line);
//         
//         int iFind = stra.case_insensitive_find_first_begins(line + ":");
//         
//         if (iFind < 0)
//         {
//            bOk = false;
//            
//            break;
//         }
//         
//         auto dropboxLine = stra[iFind];
//         
//         if (!dropboxLine.case_insensitive_ends("up to date"))
//         {
//            bOk = false;
//            break;
//         }
//         
//         auto pathFile = pathSourceFolder / line;
//         
//         if (!file_system()->exists(pathFile))
//         {
//            bOk = false;
//            
//            break;
//         }
//         
//         if (file_system()->as_string(pathFile).trimmed().is_empty())
//         {
//            bOk = false;
//            
//            break;
//         }
//      }
//      
//      
//      if (bOk)
//      {
//         break;
//      }
//   }
//   
//   set_status2("Checking if index.txt contents are ok...");
//   
//   ::string strIndex;
//   
//   while (true)
//   {
//      
//      strIndex = file_system()->as_string(pathSourceIndex);
//      
//      strIndex.trim();
//      
//      if (strIndex.has_character())
//      {
//         
//         break;
//         
//      }
//      
//   }
//   
//   if (strIndex.case_insensitive_equals("(empty)"))
//   {
//      
//      set_status2("index.txt is (empty) so installing simple repository");
//      
//      install_repository(e_repository_simple);
//      
//   } else
//   {
//      
//      ::string_array straLines;
//      
//      straLines.add_lines(strIndex);
//      
//      for (auto & strLine: straLines)
//      {
//         
//         set_status2("Installing repository \"" + strLine + "\"...");
//         
//         _install_repository(strLine);
//         
//      }
//      
//   }
//   
//   if (m_papp->__are_repositories_installed(strIndex))
//   {
//      
//      file_system()->copy(pathIndex, pathSourceIndex, true);
//      
//   }
//   
//   on_finished();
//   
//}


int install::synchronous_posix_terminal(const ::scoped_string & scopedstr)
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
   
   int iExitCode = node()->synchronous_posix_terminal("echo \"sudo apt install git\"; sudo apt install git");
   
   informationf("sudo apt install git Exit Code : %d", iExitCode);
   
   on_finished();
}


void install::install_patch_shell()
{
   information() << "install_patch_shell";
   
   auto pathPatchShell = directory_system()->home() / OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME / (
                                                                                              "operating_system/tool-" OPERATING_SYSTEM_NAME "/bin/patch_shell");
   
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


::string_array install::get_install_dep_script_names()
{
   
   auto psummary = node()->operating_system_summary();
   
//   if (psummary->m_strDistro == "ubuntu")
//   {
//      
//      if (psummary->m_strDistroBranch == "xfce")
//      {
//         
//         return {"xubuntudeps"};
//         
//      } else if (psummary->m_strDistroBranch == "kde")
//      {
//         
//         return {"kubuntudeps"};
//         
//      } else
//      {
//         if (atoi(psummary->m_strDistroRelease) >= 24)
//         {
//            return {"ubuntug4deps"};
//         } else
//         {
//            return {"ubuntug3deps"};
//         }
//      }
//   } else if (psummary->m_strDistro == "debian")
//   {
//      
//      if (psummary->m_strDistroBranch == "xfce")
//      {
//         
//         return {"xdebiandeps"};
//         
//      } else if (psummary->m_strDistroBranch == "kde")
//      {
//         
//         return {"kdebiandeps"};
//         
//      } else
//      {
//         return {"debiangdeps"};
//      }
//   }
//   
   return {};
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
   
   auto depsa = get_install_dep_script_names();
   
   int iRetryCount = 5;
   int iTry = 0;
   int iFailureCount;
   int iTotalCount;
   
   while (true)
   {
      iFailureCount = 0;
      
      iTotalCount = 0;
      
      for (auto & deps: depsa)
      {
         ::file::path path = directory_system()->home() / "cmake/operating_system/tool-linux/bin" / deps;
         
         int iExitCode = synchronous_posix_terminal("echo \\\"" + path + "\\\"; " + path);
         
         informationf("%s Exit Code : %d", path.c_str(), iExitCode);
         
         if (iExitCode)
         {
            iFailureCount++;
         }
         
         iTotalCount++;
      }
      
      if (iFailureCount <= 0)
      {
         break;
      }
      iTry++;
      
      if (iTry >= iRetryCount)
      {
         
         on_finished();
         
         return;
         
      }
      
   }
   
   ::string strSummary;
   
   strSummary.formatf("Failure Count : %d, Total Count : %d", iFailureCount, iTotalCount);
   
   file_system()->put_block(directory_system()->home() / ".config/integration/code/install_deps.txt", strSummary);
   
   on_finished();
}


void install::install_git_credential_manager()
{
   if (m_path.ends(".deb"))
   {
      directory_system()->change_current(m_path.folder());
      
      int iExitCode = synchronous_posix_terminal(
                                                 "echo \"sudo apt install " + m_path + "\"; sudo apt install " + m_path);
      
      if(iExitCode != 0)
      {
         
         ::string strMessage;
         
         strMessage.formatf("Failed to install \"%s\".", m_path.c_str());
         
         set_status2(strMessage);
         
         warning(strMessage);
         
      }
      
   } else
   {
      directory_system()->change_current(m_path.folder());
      
      int iExitCode = synchronous_posix_terminal(
                                                 "echo \"sudo tar -xzvf " + m_path + " -C /usr/local/bin\"; sudo tar -xzvf " + m_path +
                                                 " -C /usr/local/bin");
      
      if(iExitCode != 0)
      {
         
         ::string strMessage;
         
         strMessage.formatf("Failed to ungz-untar \"%s\".", m_path.c_str());
         
         set_status2(strMessage);
         
         warning(strMessage);
         
      }

   }
   
   int iExitCode = synchronous_posix_terminal("git-credential-manager configure");
   
   
   if(iExitCode != 0)
   {
      
      ::string strMessage;
      
      strMessage = "Failed to setup git-credential-manager";
      
      set_status2(strMessage);
      
      warning(strMessage);
      
   }

   
   int iExitCode2 = node()->posix_shell_command(
                                                "git config --global credential.credentialStore secretservice",
                                                e_posix_shell_system_default,
                                                [this](auto etracelevel, auto str, bool bCarriage)
                                                {
                                                   set_status2(str);
                                                });
   
   if(iExitCode2 != 0)
   {
      
      ::string strMessage;
      
      strMessage = "Failed to configure git credential store";
      
      set_status2(strMessage);
      
      warning(strMessage);
      
   }

   
   on_finished();
}


bool application::__is_git_scm_installed()
{
   bool bGitInstalled = node()->has_posix_shell_command("git");
   
   if (bGitInstalled)
   {
      //auto p = message_box("Git is installed", "Git is installed", e_message_box_ok);
      
      //p->do_synchronously();
   } else
   {
   }
   
   return bGitInstalled;
}


//void install::install_smart_git()
//{
//   try
//   {
//      set_status2("Uncompressing...");
//      
//      auto pathSyntevo = directory_system()->home() / "application/syntevo";
//      
//      directory_system()->create(pathSyntevo);
//      
//      nano()->archive()->untar(pathSyntevo, m_path, 0,
//                               [this](auto str)
//                               {
//         set_status2(str);
//      });
//      
//      set_status2("Installing...");
//      
//      node()->posix_shell_command(pathSyntevo / "smartgit/bin/add-menuitem.sh");
//      
//      node()->detached_command("/bin/bash -c " + (pathSyntevo / "smartgit/bin/smartgit.sh"), {});
//   }
//   catch (...)
//   {
//   }
//   
//   on_finished();
//}


void install::install_google_chrome()
{
   auto psummary = node()->operating_system_summary();
//   
//   if (psummary->m_strDistroFamily.case_insensitive_equals("debian"))
//   {
//      
//      _install_deb();
//      
//   } else
//   {
//      
//      _install_rpm();
//      
//   }
   
//   if (psummary->m_strDistro.case_insensitive_equals("debian"))
//   {
//      
//      _uninstall("firefox-esr");
//      
//   } else
//   {
//      
//      _uninstall("firefox");
//      
//   }
//   
//   if (psummary->m_strDistro.case_insensitive_equals("ubuntu"))
//   {
//      _snap_uninstall("firefox");
//   }
   
   on_finished();
}


void install::install_visual_studio_code()
{
   
   auto psummary = node()->operating_system_summary();
   
//   if (psummary->m_strDistroFamily.case_insensitive_equals("debian"))
//   {
//      
//      install_deb();
//      
//      return;
//   }
   
   ::string strCommand;
   
   strCommand = "sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc; ";
   strCommand += "echo -e \"[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc\" | sudo tee /etc/yum.repos.d/vscode.repo > /dev/null; ";
   strCommand += "dnf check-update; ";
   strCommand += "sudo dnf install code;";
   
   
   synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
   
   on_finished();
   
}


//void install::_install(const scoped_string & scopedstrPackageName)
//{
//   auto psummary = node()->operating_system_summary();
//   
//   ::string strCommand;
//   
//   strCommand = "sudo ";
//   
////   if (psummary->m_strDistroFamily.case_insensitive_equals("debian"))
////   {
////      strCommand += "apt install";
////   } else
////   {
////      strCommand += "dnf install";
////   }
////   
//   strCommand += " ";
//   
//   strCommand += scopedstrPackageName;
//   
//   synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
//}


//void install::_uninstall(const scoped_string & scopedstrPackageName)
//{
//   auto psummary = node()->operating_system_summary();
//   
//   ::string strCommand;
//   
//   strCommand = "sudo ";
//   
//   if (psummary->m_strDistroFamily.case_insensitive_equals("debian"))
//   {
//      strCommand += "apt remove";
//   } else
//   {
//      strCommand += "dnf remove";
//   }
//   
//   strCommand += " ";
//   
//   strCommand += scopedstrPackageName;
//   
//   synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
//}


//void install::_snap_uninstall(const scoped_string & scopedstrPackageName)
//{
//   ::string strCommand;
//   
//   strCommand = "sudo snap remove ";
//   
//   strCommand += scopedstrPackageName;
//   
//   synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
//}


//bool install::_is_package_installed(const ::scoped_string & scopedstrPackageName)
//{
//   
//   auto psummary = node()->operating_system_summary();
//   
//   if (psummary->m_strDistroFamily.case_insensitive_equals("debian"))
//   {
//      ::string strCommand;
//      
//      strCommand = "apt -qq list " + scopedstrPackageName;
//      
//      ::string strOutput;
//      
//      int iExitCode = node()->get_posix_shell_command_output(strOutput, strCommand);
//      
//      if (iExitCode == 0)
//      {
//         
//         strOutput.trim();
//         
//         if (strOutput.case_insensitive_ends("[installed]"))
//         {
//            
//            return true;
//            
//         }
//         
//      }
//      
//   } else
//   {
//      set_status2("_is_package_installed not implemented for this distro : " + psummary->m_strDistro);
//   }
//   
//   return false;
//   
//}


//bool install::_are_user_packages_installed()
//{
//   
//   auto pathHome = directory_system()->home();
//   
//   auto pathInstallIndex = pathHome / ".config/integration/code/___install/index.txt";
//   
//   if (!file_system()->exists(pathInstallIndex))
//   {
//      
//      return false;
//      
//   }
//   
//   auto lines = file_system()->lines(pathInstallIndex);
//   
//   lines.trim();
//   
//   lines.erase_empty();
//   
//   lines.erase_duplicates();
//   
//   for (auto & strInstall: lines)
//   {
//      
//      if (!_is_package_installed(strInstall))
//      {
//         
//         return false;
//         
//      }
//      
//   }
//   
//   return true;
//   
//}


//void install::_install_user_fonts()
//{
//   
////   auto pathSource = _dropbox_ensure_files_in_index_txt_are_up_to_date_and_present("box/___fonts", "ttf", 1_KiB);
////   
////   if(pathSource.has_character())
////   {
////      
////      auto pathApplicationBuildHelper = directory_system()->home() / "bin/application_build_helper";
////      
////      ::file::path pathSourceFolder = pathSource.folder();
////      
////      ::string strCommand;
////      
////      strCommand = "sudo ";
////      
////      strCommand += ::string(pathApplicationBuildHelper);
////      
////      strCommand += " --install-fonts-from-folder=" + ::string(pathSourceFolder);
////      
////      synchronous_posix_terminal("echo \"" + strCommand + "\"; " + strCommand);
////      
////      node()->command_system("fc-cache -v", std_inline_log());
////      
////   }
//   
//}


//bool install::_dropbox_defer_check_index(::file::path & pathTarget, const ::scoped_string & scopedstrDropboxFolder, bool bForce, ::file::path * ppathSource)
//{
//   
//   ::string strDropboxFolder = scopedstrDropboxFolder;
//   
//   auto pathTargetFolder = directory_system()->home() / ".config/integration/code" / strDropboxFolder;
//   
//   pathTarget = pathTargetFolder / "index.txt";
//   
//   if (bForce || !file_system()->exists(pathTarget) || file_system()->modification_time(pathTarget).elapsed() >= 12_hours)
//   {
//      
//      auto pathSource = _dropbox_ensure_index_txt_is_up_to_date_and_present(strDropboxFolder);
//      
//      file_system()->copy(pathTarget, pathSource, true);
//      
//      if(ppathSource)
//      {
//         
//         *ppathSource = pathSource;
//         
//      }
//      
//      return true;
//      
//   }
//   
//   return false;
//   
//}


//::string_array install::_dropbox_defer_check_index_lines(const ::scoped_string & scopedstrDropboxFolder, bool bForce, ::file::path * ppathTarget, ::file::path * ppathSource)
//{
//   
//   ::file::path pathTarget;
//   
//   if (!_dropbox_defer_check_index(pathTarget, scopedstrDropboxFolder, bForce, ppathSource))
//   {
//      
//      return {};
//      
//   }
//   
//   auto lines = file_system()->lines(pathTarget);
//   
//   lines.trim();
//   
//   lines.erase_empty();
//   
//   lines.erase_duplicates();
//   
//   if(ppathTarget)
//   {
//      
//      *ppathTarget = pathTarget;
//      
//   }
//   
//   return lines;
//   
//}


//
//void install::_install_user_packages()
//{
//   
//   auto lines = _dropbox_defer_check_index_lines(nullptr, "box/___install");
//   
//   for (auto strInstall : lines)
//   {
//      
//      if (!_is_package_installed(strInstall))
//      {
//         
//         _install(strInstall);
//         
//      }
//      
//   }
//   
//}
//

//::file::path
//install::_dropbox_ensure_index_txt_is_up_to_date_and_present(const ::scoped_string & scopedstrDropboxFolder)
//{
//   
//   auto pathDropboxFolder = directory_system()->home() / "Dropbox" / scopedstrDropboxFolder;
//   
//   set_status2("Checking for \"" + scopedstrDropboxFolder +
//               "\" Dropbox folder... (index.txt should exist to continue installation with code...)");
//   
//   while (!directory_system()->is(pathDropboxFolder))
//   {
//      
//      preempt(1_s);
//      
//   }
//   
//   directory_system()->change_current(pathDropboxFolder);
//   
//   set_status2("Checking for index.txt at \"" + scopedstrDropboxFolder +
//               "\" Dropbox folder... (index.txt should exist to continue installation with code...)");
//   
//   auto pathSource = pathDropboxFolder / "index.txt";
//   
//   while (true)
//   {
//      
//      if (file_system()->exists(pathSource))
//      {
//         
//         break;
//         
//      }
//      
//      preempt(1_s);
//      
//   }
//   
//   set_status2("Checking if index.txt is up-to-date and present...");
//   
//   ::string_array lines;
//   
//   lines.add("index.txt");
//   
//   while (true)
//   {
//      
//      preempt(1_s);
//      
//      ::string strLs;
//      
//      int iExitCode = node()->
//      get_posix_shell_command_output(strLs, m_strDropboxCommand + " dropbox filestatus");
//      
//      auto pszLs = strLs.c_str();
//      
//      print_line(pszLs);
//      
//      ::string_array stra;
//      
//      stra.add_lines(pszLs);
//      
//      bool bOk = true;
//      
//      for (auto & line: lines)
//      {
//         
//         auto pszLine = line.c_str();
//         
//         print_line("font_at_index.txt: " + line);
//         
//         int iFind = stra.case_insensitive_find_first_begins(line + ":");
//         
//         if (iFind < 0)
//         {
//            
//            bOk = false;
//            
//            break;
//            
//         }
//         
//         auto dropboxLine = stra[iFind];
//         
//         if (!dropboxLine.case_insensitive_ends("up to date"))
//         {
//            
//            bOk = false;
//            
//            break;
//            
//         }
//         
//         auto pathFile = pathDropboxFolder / line;
//         
//         if (!file_system()->exists(pathFile))
//         {
//            
//            bOk = false;
//            
//            break;
//            
//         }
//         
//         if (file_system()->as_string(pathFile).trimmed().is_empty())
//         {
//            
//            bOk = false;
//            
//            break;
//            
//         }
//         
//      }
//      
//      if (bOk)
//      {
//         
//         break;
//         
//      }
//      
//   }
//   
//   return pathSource;
//   
//}
//
//
//::file::path install::_dropbox_ensure_files_in_index_txt_are_up_to_date_and_present(
//                                                                                    const ::scoped_string & scopedstrDropboxFolder, const ::scoped_string & scopedstrFileExtension, int iMinimumFileSize)
//{
//   
//   ::string_array lines;
//   
//   ::file::path pathTarget;
//   
//   ::file::path pathSource;
//   //if(lines.has_elements())
//   //{
//   
//   
//   //auto pathFolder = pathSource.folder();
//   
//   //::string_array lines;
//   
//   set_status2("Checking if all files in index.txt listing are up-to-date and present...");
//   
//   while (true)
//   {
//      
//      auto lines = _dropbox_defer_check_index_lines(scopedstrDropboxFolder, true, &pathTarget, &pathSource);
//      
//      if (lines.get_size() >= 7)
//      {
//         /// if file listing is empty it should contain empty lines like this
//         ///
//         ///
//         ///
//         /// (empty)
//         ///
//         ///
//         ///
//         ///
//         ///
//         ///
//         
//         break;
//         
//      }
//      
//   }
//   
//   lines.erase_empty();
//   
//   lines.trim();
//   
//   ::string strEnds;
//   
//   strEnds = "." + scopedstrFileExtension;
//   
//   //lines.erase_lines_not_ending(".ttf");
//   lines.predicate_erase([strEnds](auto & str)
//                         {
//      return !str.case_insensitive_ends(strEnds);
//      
//   });
//   
//   while (true)
//   {
//      
//      preempt(1_s);
//      
//      ::string strLs;
//      
//      int iExitCode = node()->
//      get_posix_shell_command_output(strLs, m_strDropboxCommand + " dropbox filestatus");
//      
//      auto pszLs = strLs.c_str();
//      
//      print_line(pszLs);
//      
//      ::string_array stra;
//      
//      stra.add_lines(pszLs);
//      
//      bool bOk = true;
//      
//      for (auto & line: lines)
//      {
//         auto pszLine = line.c_str();
//         
//         print_line("font_at_index.txt: " + line);
//         
//         int iFind = stra.case_insensitive_find_first_begins(line + ":");
//         
//         if (iFind < 0)
//         {
//            bOk = false;
//            
//            break;
//         }
//         
//         auto dropboxLine = stra[iFind];
//         
//         if (!dropboxLine.case_insensitive_ends("up to date"))
//         {
//            bOk = false;
//            break;
//         }
//         
//         auto pathFile = pathSource.folder() / line;
//         
//         if (!file_system()->exists(pathFile))
//         {
//            bOk = false;
//            
//            break;
//         }
//         
//         if (iMinimumFileSize > 0 && file_system()->get_size(pathFile) < iMinimumFileSize)
//         {
//            
//            bOk = false;
//            
//            break;
//            
//         }
//         
//      }
//      
//      if (bOk)
//      {
//         
//         break;
//         
//      }
//      
//   }
//   
//   return pathTarget;
//   
//}
//
//
//void install::install_jetbrains_clion()
//{
//   try
//   {
//      set_status2("Uncompressing JetBrains CLion...");
//      
//      auto pathJetbrains = directory_system()->home() / "application/jetbrains";
//      
//      directory_system()->create(pathJetbrains / "clion");
//      
//      nano()->archive()->untar(pathJetbrains / "clion", m_path, 1, [this](auto str)
//                               {
//         set_status2(str);
//      });
//      
//      set_status2("Installing JetBrains CLion...");
//      
//      node()->posix_shell_command(pathJetbrains / "clion/bin/clion.sh");
//   }
//   catch (...)
//   {
//   }
//   
//   on_finished();
//}
//
//
//void install::install_jetbrains_toolbox()
//{
//   try
//   {
//      set_status2("Uncompressing JetBrains Toolbox...");
//      
//      auto pathJetbrains = directory_system()->home() / "application/jetbrains";
//      
//      directory_system()->create(pathJetbrains / "toolbox");
//      
//      nano()->archive()->untar(pathJetbrains / "toolbox", m_path, 1, [this](auto str)
//                               {
//         set_status2(str);
//      });
//      
//      set_status2("Installing JetBrains Toolbox...");
//      
//      int iExitCode = node()->synchronous_posix_terminal(
//                                                         "echo \"sudo apt install libfuse2\"; sudo apt install libfuse2");
//      
//      int iExitCode2 = node()->posix_shell_command(pathJetbrains / "toolbox/jetbrains-toolbox");
//   }
//   catch (...)
//   {
//   }
//   
//   on_finished();
//}
//
//

//void install::install_browser()
//{
//   
//   if (m_papp->m_strBrowser == "chrome")
//   {
//
//      //install_google_chrome();
//
//   }
//   else if (m_papp->m_strBrowser == "opera")
//   {
//
//      //install_opera_browser();
//
//   }
//
//
//}


void install::install_xcode()
{
   
}

} // namespace coding



