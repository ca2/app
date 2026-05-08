//Created as main_item.cpp by camilo on 2024-04-27 22:45 <3ThomasBorregaardSorensen!!
//From main_item.cpp by camilo on 2024-04-27 22:52 <3ThomasBorregaardSorensen!!
//From install_base.cpp by camilo on 2024-04-27 22:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "code.h"
#include "option.h"
#include "code_impact.h"
#include "code_option_form_handler.h"
#include "acme/constant/id.h"
#include "acme/compress/uncompress.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/queue.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/platform/scoped_restore.h"
#include "apex/networking/http/context.h"
#include "axis/user/user/line_layout.h"
#include "coding/install.h"


namespace coding
{


   option_form_handler::option_form_handler()
   {

   }


   option_form_handler::~option_form_handler()
   {

   }


   ::pointer<::user::multiple_option > option_form_handler::create_option_form_handler(::coding::code * pcode, ::coding::option * poption, ::user::interaction* puserinteractionParent)
   {

      m_pcode = pcode;

      m_poption = poption;

      auto payloadOption = poption->m_property.get_property();

      m_pmultipleoption = create_multiple_option(puserinteractionParent, poption->m_property, poption->m_atomaOptions, poption->m_straName);

      m_pmultipleoption->m_bAutoResize = false;

      //::string strAddVs;

      //if (!m_pinstall->is_installed(true))
      //{

      //   m_pstillStatus = create_label(pline, "Not installed.");

      //   m_pcheckbox = create_check_box_with_label(pline, "Install", &m_pstillCheckBox);

      //   m_pcheckbox->set_check(e_check_checked, e_source_initialize);

      //   m_pcheckbox->check_changed(this) += [this](auto & check)
      //      {

      //         m_pcode->m_pimpact->update_start_button();

      //         m_papp->defer_release_install();

      //         m_papp->code_on_change_selection();

      //      };


      //}

      ////m_papp->m_installmap[m_einstall] = this;

      /////return pmainitem;

      return m_pmultipleoption;

   }


   //void install::run_normal_install()
   //{


   //   if (m_einstall == e_install_tool_os || m_einstall == e_install_app_simple)
   //   {

   //      install_repository();

   //   }
   //   else if (m_einstall == e_install_git_scm)
   //   {

   //      install_git_scm();

   //   }
   //   else if (m_einstall == e_install_tortoise_git)
   //   {

   //      install_tortoise_git();

   //   }
   //   else if (m_einstall == e_install_smart_git)
   //   {

   //      install_smart_git();

   //   }
   //   else
   //   {

   //      throw ::exception(error_failed);

   //   }
   //}


//   void option_form_handler::on_finished()
//   {
//
//      m_pinstall->m_bInstalling = false;
//
//      ::string strTitle = m_pinstall->get_title();
//
//      //set_status1("Downloading TortoiseSVN");
//
//      //::file::path path = download("tortoisesvn");
//
//      //set_status1("Installing TortoiseSVN");
//
//      //::property_set set;
//
//      ////call_sync("msiexec.exe", "/i \"" + path + "\" /passive /norestart ADDLOCAL=ALL", path.folder(), ::e_display_default, 10_min, set);
//      //{
//
//      if (m_pinstall->is_installed(false))
//      {
//
//         install_status2(m_pinstall, "");
//
//         if (m_pinstall->m_iTry == 0)
//         {
//
//         //   ::string str;
//
//         //   str = "Already installed";
//
//         //   set_status(str);
//
//         //}
//         //else if (m_iTry == 1)
//         //{
//
//            ::string str;
//
//            str = "Just installed.";
//
//            install_status(m_pinstall, str);
//
//         }
//         else if (m_pinstall->m_iTry >= 1)
//         {
//
//            ::string str;
//
//            str.formatf("Installed after multiple attempts (%d).", m_pinstall->m_iTry + 1);
//
//            install_status(m_pinstall, str);
//
//         }
//
//         m_papp->on_installed(m_pinstall->m_einstall, true);
//
//         //m_pimpact->set_need_redraw();
//
//         //m_pimpact->post_redraw();
//
//      }
//      else
//      {
//
//         ::string str;
//
//         str = "Not installed!! ";
//
//         str.append_formatf("Attempt no. %d to install", m_pinstall->m_iTry);
//
//         install_status(m_pinstall, str);
//
//         task_sleep(500_ms);
//
//         if (m_pinstall->m_iTry < m_pinstall->m_iTryCount)
//         {
//
//            m_pinstall->m_iTry++;
//
//            defer_start_installation();
//
//         }
//         else
//         {
//
//            //      //m_strGitInstallationStatus += "Important options to select: \n";
//
//            //      run();
//
//
//            //   iTry--;
//
//            //}
//
//            ::string str2 = "Couldn't be installed...";
//
//            str2.append_formatf("In %d attempts...", m_pinstall->m_iTry);
//
//            str2 += "You can retry...\n\n";
//
//            install_status2(m_pinstall, str2);
//
//         }
//
//      }
//
//   }
//
//
//   void option_form_handler::start_installation(int iTryCount)
//   {
//
//      if (m_pinstall->has_download_step())
//      {
//
//         install_status2(m_pinstall, "Waiting to download...");
//
//         m_papp->queue(id_download)->sync([this]()
//            {
//
//               m_pinstall->download();
//
//            }, 30_min);
//
//      }
//
//      install_append_status2(m_pinstall, "Waiting to install...");
//
//      m_pinstall->m_iTryCount = iTryCount;
//
//      m_pinstall->m_iTry = 0;
//
//      defer_start_installation();
//
//   }
//
//
//   void option_form_handler::defer_start_installation()
//   {
//
//      m_pinstall->m_bInstalling = true;
//
//      m_papp->m_bStartingInstallation2 = false;
//
//      if (m_pinstall->m_einstall == ::coding::e_install_visual_studio)
//      {
//
//         m_papp->queue(id_system_install)->sync([this]()
//            {
//
//               m_pinstall->install_graphical_ide();
//
//            }, 2_hour);
//
//      }
//      else
//      {
//
//         m_papp->queue(id_system_install)->sync([this]()
//         {
//
//            try
//            {
//
//               m_pinstall->run_normal_install();
//
//            }
//            catch (...)
//            {
//            }
//
//         }, 30_min);
//
//      }
//
//   }
//
//
//   //void install::install_graphical_ide()
//   //{
//
//   //   m
//
//   //   //void application::start_install_graphical_ide()
//   //   //{
//
//   //      //fork([this]()
//   //      //   {
//
//   //   //::index iTry = 0;
//
//   //   //while (!is_installed() && iTry < 6)
//   //   //{
//
//   //   //   m_bInstalling = true;
//
//   //   //   install_graphical_ide();
//
//   //   //   iTry++;
//
//   //   //   task_sleep(1_s);
//
//   //   //}
//
//   //   //if (is_installed())
//   //   //{
//
//   //   //   if (m_bInstalling)
//   //   //   {
//
//   //   //      m_bInstalling = false;
//
//   //   //      m_papp->m_bJustInstalledGraphicalIde = true;
//
//   //   //      m_papp->m_timeFinishedInstallingGraphicalIde.Now();
//
//   //   //   }
//
//   //   //   ::string str;
//
//   //   //   //str.formatf("Installed", m_strGraphicalIdeName.c_str());
//
//   //   //   str = "Installed";
//
//   //   //   m_papp->set_status(m_einstall, str);
//
//   //   //   m_papp->set_status2(m_einstall, str);
//
//   //   //   //m_pimpact->set_need_redraw();
//
//   //   //   //m_pimpact->post_redraw();
//
//   //   //}
//
//
//   //}
//
//
//   //bool install::is_installed()
//   //{
//
//   //   return m_papp->is_installed(m_einstall);
//
//   //}
//
//
//   //void install_impact_handler::download()
//   //{
//
//
//   //   //scoped_restore(m_bInstalling);
//
//   //   //m_bInstalling = true;
//
//   //   //   ::file::path pathInf = "C:/operating_system/git-scm.inf";
//
//   //   //   if (!file_system()->exists(pathInf))
//   //   //   {
//
//   //   //      ::file::path pathUrl = "https://ca2.software/download/windows/git-scm.inf";
//
//   //   //      ::property_set set;
//
//   //   //      set["raw_http"] = true;
//
//   //   //      http().download(pathUrl, pathInf, set);
//
//   //   //}
//
//   //   ::transfer_progress_function transferprogressfunction = [this](double d, filesize done, filesize total)
//   //      {
//
//   //         if (total == 0 || total == (filesize)-1)
//   //         {
//
//   //            ::string str2;
//
//   //            str2.formatf("Dowloading TortoiseGit (%lld)", done);
//
//   //            set_status2(str2);
//
//   //         }
//   //         else if (total == done)
//   //         {
//
//   //            ::string str2;
//
//   //            str2.formatf("Dowloaded %lld bytes", done);
//
//   //            set_status2(str2);
//
//   //         }
//   //         else
//   //         {
//
//   //            ::string str2;
//
//   //            str2.formatf("Dowloading %0.1f%% (%lld of %lld)", d * 100.0, done, total);
//
//   //            set_status2(str2);
//
//   //         }
//
//   //         //m_pimpact->set_need_redraw();
//
//   //         //m_pimpact->post_redraw();
//
//   //      };
//
//   //   ::string strName;
//
//   //   auto pathUrl = get_download_url(strName);
//
//   //   information(pathUrl);
//
//   //   set_status2("Downloading...");
//
//   //   //m_pimpact->set_need_redraw();
//
//   //   //m_pimpact->post_redraw();
//
//   //   ::property_set set;
//
//   //   set["raw_http"] = true;
//
//   //   set["transfer_progress_function"] = transferprogressfunction.m_pbase;
//
//   //   ::file::path pathDownloadFolder;
//
//   //   pathDownloadFolder = directory()->download() / "Code!!";
//
//   //   m_path = pathDownloadFolder / strName;
//
//   //   m_papp->http().download(pathUrl, m_path, set);
//
//
//   //   //_run_installer();
//
//
//
//   //}
//
//
//   //void install_impact_handler::_run_installer()
//   //{
//
//
//
//   //}
//
//
//   //bool install_impact_handler::has_download_step()
//   //{
//
//   //   ::string strName;
//
//   //   auto pathUrl = get_download_url(strName);
//
//   //   return pathUrl.has_character();
//
//   //}
//
//
//   //void install_impact_handler::_run_msi_exec()
//   //{
//
//   //   m_papp->queue(id_system_install)->sync([this]()
//   //      {
//
//   //         try
//   //         {
//
//   //            ::property_set set;
//
//   //            //auto pathPowerShell = node()->_get_power_shell_path();
//
//   //            ::string strParams;
//
//   //            strParams = "start /wait msiexec.exe /package \"" + m_path.name() + "\" /quiet /passive";
//
//   //            int iExitCode = node()->command_system(strParams, 2_hour, m_path.folder());
//
//   //            ::string strExit;
//
//   //            if (iExitCode == 0)
//   //            {
//
//   //               strExit = "Installed";
//
//   //            }
//   //            else
//   //            {
//
//   //               strExit = "Failed to install";
//
//   //            }
//
//   //            set_status2(strExit);
//
//   //            information(strExit);
//
//   //         }
//   //         catch (...)
//   //         {
//
//   //         }
//
//   //         on_finished();
//
//   //      }, 30_min);
//
//   //}
//
//
//   //void install::download()
//   //{
//
//   //   auto transferprogressfunction = [this](double d, filesize done, filesize total)
//   //      {
//
//   //         if (total == 0 || total == (filesize)-1)
//   //         {
//
//   //            ::string str2;
//
//   //            str2.formatf("Dowloading (%lld)", done);
//
//   //            m_papp->set_status2(m_einstall, str2);
//
//   //         }
//   //         else
//   //         {
//
//   //            ::string str2;
//
//   //            str2.formatf("Dowloading %0.1f%% (%lld of %lld)", d * 100.0, done, total);
//
//   //            m_papp->set_status2(m_einstall, str2);
//
//   //         }
//
//   //         //m_pimpact->set_need_redraw();
//
//   //         //m_pimpact->post_redraw();
//
//   //      };
//
//   //   ::file::path path = m_papp->download(m_einstall, transferprogressfunction);
//
//   //   information(path);
//
//
//   //}
//
//
//   //void install_impact_handler::install_git_scm()
//   //{
//
//   //   try
//   //   {
//
//   //      ::file::path pathInf = "C:/operating_system/git-scm.inf";
//
//   //      if (!file_system()->exists(pathInf))
//   //      {
//
//   //         ::file::path pathUrl = "https://ca2.software/download/windows/git-scm.inf";
//
//   //         ::property_set set;
//
//   //         set["raw_http"] = true;
//
//   //         m_papp->http().download(pathUrl, pathInf, set);
//
//   //      }
//
//   //      ::string str2;
//
//   //      str2 = "Installing";
//
//   //      set_status2(str2);
//
//   //      int iExitCode = node()->command_system(m_path + " /verysilent /loadinf=" + pathInf, 2_hour);
//
//   //      ::string strExit;
//
//   //      if (iExitCode == 0)
//   //      {
//
//   //         strExit = "Installed";
//
//   //      }
//   //      else
//   //      {
//
//   //         strExit = "Failed to install";
//
//   //      }
//
//   //      set_status2(strExit);
//
//   //      information(strExit);
//
//   //      auto tracefunction = ::std_inline_log();
//
//   //      tracefunction.m_timeTimeout = 5_min;
//
//   //      int iExitCode2 = node()->unix_shell_command("git config --global core.symlinks true", tracefunction);
//
//   //   }
//   //   catch (...)
//   //   {
//   //   }
//
//   //   on_finished();
//
//   //}
//
//
//   //void install_impact_handler::install_tortoise_git()
//   //{
//
//   //   _run_msi_exec();
//
//   //}
//
//
//   //void install_impact_handler::install_smart_git()
//   //{
//
//   //   try
//   //   {
//
//   //      set_status2("Uncompressing...");
//
//   //      auto uncompressFolder = m_path.folder() / m_path.title();
//
//   //      auto pathExe = file()->unzip_exe(m_path);
//
//   //      set_status2("Installing...");
//
//   //      node()->root_execute_sync(pathExe, "/silent /norestart", 20_min, pathExe.folder());
//
//   //   }
//   //   catch (...)
//   //   {
//
//   //   }
//
//   //   on_finished();
//
//   //}
//
//
//   //void install_impact_handler::install_repository()
//   //{
//
//   //   try
//   //   {
//
//   //      {
//
//   //         if (m_papp->__is_repository_installed(m_einstall))
//   //         {
//
//   //            set_status("Already Installed!!");
//
//   //         }
//   //         else
//   //         {
//
//   //            ::file::path path = m_papp->get_repository_path(m_einstall);
//
//   //            ::file::path pathForBash;
//
//   //            pathForBash = m_papp->bash_path(path);
//
//   //            ::file::path pathUrl;
//
//   //            pathUrl = m_papp->get_repository_url(m_einstall);
//
//   //            m_papp->set_status(m_einstall, "Cloning " + pathUrl + "to " + pathForBash + " ...");
//
//   //            int iExitCode = node()->command_system(
//   //               "\"C:\\Program Files\\Git\\bin\\bash.exe\" -c \"git clone " + pathUrl + " " +
//   //               pathForBash + " --recurse-submodules\"",
//   //               [this](auto etracelevel, auto str)
//   //               {
//
//
//   //                  set_status2("Cloning : " + str);
//
//   //                  //m_pimpact->set_need_redraw();
//
//   //                  //m_pimpact->post_redraw();
//
//   //               });
//
//   //            if (iExitCode == 0)
//   //            {
//
//   //               int iExitCode2 = node()->command_system(
//   //                  "\"C:\\Program Files\\Git\\bin\\bash.exe\" -c \"checkout\"",
//   //                  [this](auto etracelevel, auto str)
//   //                  {
//
//
//   //                     set_status2("Checking out : " + str);
//
//   //                     //m_pimpact->set_need_redraw();
//
//   //                     //m_pimpact->post_redraw();
//
//   //                  }, path);
//
//   //               if (iExitCode2 == 0)
//   //               {
//
//   //                  set_status("Cloned and Checked Out!!");
//
//   //               }
//   //               else
//   //               {
//
//   //                  set_status("Checkout Failed!");
//
//   //               }
//
//   //            }
//   //            else
//   //            {
//
//   //               set_status("Not installed!");
//
//   //            }
//
//   //         }
//
//   //      }
//
//   //   }
//   //   catch (...)
//   //   {
//
//   //   }
//
//   //   on_finished();
//
//   //}
//
//
//   //::file::path install_impact_handler::get_download_url(::string& strName)
//   //{
//
//   //   ::file::path pathUrl;
//
//   //   // strName = "VisualStudioSetup.exe";
//
//   //   switch (m_einstall)
//   //   {
//   //   case e_install_tortoise_git:
//   //      pathUrl = "https://download.tortoisegit.org/tgit/2.15.0.0/TortoiseGit-2.15.0.0-64bit.msi";
//   //      break;
//   //   case e_install_git_scm:
//   //      pathUrl = "https://github.com/git-for-windows/git/releases/download/v2.44.0.windows.1/Git-2.44.0-64-bit.exe";
//   //      break;
//   //   case e_install_visual_studio:
//   //      pathUrl = "https://c2rsetup.officeapps.live.com/c2r/downloadVS.aspx?sku=community&channel=Release&version=VS2022&source=VSLandingPage";
//   //      strName = "VisualStudioSetup.exe";
//   //      break;
//   //   case e_install_smart_git:
//   //      pathUrl = "https://www.syntevo.com/downloads/smartgit/smartgit-win-23_1_3.zip";
//   //      break;
//   //   default:
//   //   {
//   //      pathUrl = "";
//   //      break;
//
//   //   }
//   //   //   property_set set;
//
//   //   //   set["raw_http"] = true;
//
//   //   //   ::string strName = m_papp->get_title(m_einstall);
//
//   //   //   for (int i = 0; i < 10; i++)
//   //   //   {
//
//   //   //      pathUrl = m_papp->http().get("https://ca2.software/code/script/windows/" + strName, set);
//
//   //   //      if (pathUrl.case_insensitive_begins("https://"))
//   //   //      {
//
//   //   //         break;
//
//   //   //      }
//
//   //   //   }
//
//   //   //};
//   //   //break;
//   //   }
//
//   //   if (strName.is_empty())
//   //   {
//
//   //      strName = pathUrl.name();
//
//   //   }
//
//
//   //   return pathUrl;
//   //   //property_set set;
//
//   //   //set["raw_http"] = true;
//
//   //   //set["transfer_progress_function"] = transferprogressfunction.m_pbase;
//
//   //   //::file::path pathDownloadFolder;
//
//   //   //pathDownloadFolder = directory()->download() / "Code!!";
//
//   //   //::file::path path = pathDownloadFolder / strName;
//
//   //   //http().download(pathUrl, path, set);
//
//   //   //return path;
//
//   //}
//
//
////   void install_impact_handler::install_graphical_ide()
////   {
////
////#if defined(LINUX)
////
////      install_clion();
////
////#elif defined(WINDOWS_DESKTOP)
////
////      install_visual_studio();
////
////#endif
////
////   }
//
//
//   //bool install_impact_handler::is_installed(bool bMayAssumeNotInstalled)
//   //{
//
//   //   if (m_bInstalling)
//   //   {
//
//   //      return false;
//
//   //   }
//
//   //   if (m_einstall == e_install_visual_studio)
//   //   {
//
//   //      if (m_papp->m_bJustInstalledGraphicalIde)
//   //      {
//
//   //         if (m_papp->m_timeFinishedInstallingGraphicalIde.elapsed() < 30_s)
//   //         {
//
//   //            return false;
//
//   //         }
//
//   //      }
//
//   //   }
//
//   //   return m_papp->__is_installed(m_einstall, bMayAssumeNotInstalled);
//
//   //}
//
//
//   void option_form_handler::install_status(::coding::install * pinstall, const ::scoped_string& scopedstr)
//   {
//
//      if (m_pstillRemark)
//      {
//
//         m_pinstall->m_strStatus = scopedstr;
//
//         m_pstillRemark->set_window_text(m_pinstall->m_strStatus);
//
//      }
//
//   }
//
//
//   void option_form_handler::install_status2(::coding::install* pinstall, const ::scoped_string& scopedstr)
//   {
//
//      if (m_pstillStatus)
//      {
//
//         m_pinstall->m_strStatus2= scopedstr;
//
//         m_pstillStatus->set_window_text(m_pinstall->m_strStatus2);
//
//      }
//
//   }
//
//
//
//   void option_form_handler::install_append_status2(::coding::install* pinstall, const ::scoped_string& scopedstr)
//   {
//
//      if (m_pstillStatus)
//      {
//
//         m_pstillStatus->set_window_text(m_pinstall->m_strStatus2);
//
//      }
//
//   }
//
//
//
//   //bool application::_is_graphical_ide_installed()
//   //{
//
//   //   if (m_bGraphicalIdeOk)
//   //   {
//
//   //      return true;
//
//   //   }
//
//   //   m_bGraphicalIdeOk = __is_graphical_ide_installed();
//
//   //   return m_bGraphicalIdeOk;
//
//   //}
//
//   //   bool application::has_unix_shell_command(const ::scoped_string& scopedstrCommand)
//   //   {
//   //
//   //      try
//   //      {
//   //
//   //         ::string strCommand;
//   //
//   //         strCommand.format("command -v %s", scopedstrCommand.c_str());
//   //
//   //         auto iExitCode = unix_shell_command(strCommand);
//   //
//   //         return iExitCode == 0;
//   //
//   //      }
//   //      catch (...)
//   //      {
//   //
//   //      }
//   //
//   //      return false;
//   //
//   //   }
//
//
//   void option_form_handler::on_update_install_status(::coding::install * pinstall)
//   {
//
//
//   }
//
//
//   bool option_form_handler::is_selected()
//   {
//
//      return m_pcheckbox && m_pcheckbox->is_checked();
//
//   }
//
//
//   void option_form_handler::select()
//   {
//
//      m_pcheckbox->set_check(::e_check_checked, e_source_sync);
//
//      m_pcheckbox->set_need_redraw();
//
//      m_pcheckbox->post_redraw();
//
//
//
//   }
//
//   void option_form_handler::unselect()
//   {
//      
//      m_pcheckbox->set_check(::e_check_unchecked, e_source_sync);
//
//      m_pcheckbox->set_need_redraw();
//
//      m_pcheckbox->post_redraw();
//
//
//
//   }
//
//
//
//   void option_form_handler::hide_selection()
//   {
//
//      m_pcheckbox->hide();
//      m_pstillCheckBox->hide();
//
//      m_pcheckbox->set_need_redraw();
//
//      m_pcheckbox->post_redraw();
//      m_pstillCheckBox->set_need_redraw();
//
//      m_pstillCheckBox->post_redraw();
//
//
//
//   }
//
//
//   void option_form_handler::enable_window(bool bEnable)
//   {
//
//      m_plinelayout->enable_window(bEnable);
//
//      m_plinelayout->set_need_redraw();
//
//      m_plinelayout->post_redraw();
//
//
//
//   }
//
//
//   bool option_form_handler::has_check()
//   {
//
//      return m_pcheckbox;
//
//   }
//   
//
//   bool option_form_handler::has_check(::user::check* pcheck)
//   {
//
//      return m_pcheckbox && m_pcheckbox == pcheck;
//
//   }
//
//   void option_form_handler::enable_selection()
//   {
//
//      if (m_pcheckbox)
//      {
//
//         m_pcheckbox->enable_window();
//
//      }
//
//   }
//
//
//
//   void option_form_handler::disable_selection()
//   {
//
//      if (m_pcheckbox)
//      {
//
//         m_pcheckbox->enable_window(false);
//
//      }
//
//
//   }


} // namespace coding


