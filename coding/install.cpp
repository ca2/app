//Created as main_item.cpp by camilo on 2024-04-27 22:45 <3ThomasBorregaardSorensen!!
//From main_item.cpp by camilo on 2024-04-27 22:52 <3ThomasBorregaardSorensen!!
//From install_base.cpp by camilo on 2024-04-27 22:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "impact.h"
#include "install.h"
#include "code.h"
#include "code_application.h"
//#include "install_impact_interface.h"
//#include "coding.h"
//#include "task_group.h"
#include "acme/constant/id.h"
#include "acme/compress/uncompress.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/nano/nano.h"
#include "acme/nano/archive/archive.h"
#include "acme/nano/http/http.h"
#include "acme/parallelization/queue.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/platform/scoped_restore.h"
#include "acme/prototype/prototype/url.h"
//#include "apex/filesystem/fs/folder_sync.h"
//#include "apex/networking/http/context.h"
//#include "axis/user/user/line_layout.h"
#if defined(LINUX) || defined(MACOS)
#include <sys/stat.h>
#endif

namespace coding
{


   install::install()// :
      //m_propertyTitle(this, "title"),
      //m_propertyRemark(this, "remark")
   {

      m_bInstalling = false;

   }


   install::~install()
   {

   }


   void install::create_install(::coding::enum_install einstall)
   {

      m_einstall = einstall;

      //auto pcolumn = puserinteractionParent;

      ::string strCheck;

      if (is_installed(true))
      {

         strCheck = "☑";

      }

      //auto pline = create_line_layout(pcolumn, e_orientation_horizontal);

      //m_plinelayout = pline;

      //pline->m_ealignrelativeOrthogonal = ::user::line_layout::e_align_relative_base_bottom_line;

      //m_pstillTitle = create_title2(pline, strCheck + m_papp->installget_title(einstall));

      //m_pstillRemark = create_label(pline, m_papp->get_remark(einstall));

      //::string strAddVs;

      //if (!is_installed(true))
      //{

      //   m_pstillStatus = create_label(pline, "Not installed.");

      //   m_pcheckbox = create_check_box_with_label(pline, "Install", &m_pstillCheckBox);

      //   m_pcheckbox->set_check(e_check_checked, e_source_initialize);

      //   m_pcheckbox->m_callbackOnCheck = [this](auto pcheckbox)
      //      {

      //         m_papp->m_pimpact->update_start_button();

      //         m_papp->defer_release_install();

      //         m_papp->on_checkbox(pcheckbox);

      //      };


      //}

      //m_papp->m_installmap[m_einstall] = this;

      ///return pmainitem;

   }


   void install::install_repositories()
   {

      if (m_papp->current_repository() == "simple")
      {

         install_app_simple_repository();

      }
      // else
      // {
      //
      //    install_cloud_listed_repositories();
      //
      // }

   }

   void install::run_normal_install()
   {

      switch (m_einstall)
      {
      case e_install_tool_os:
         install_repository(e_repository_tool_os);
         break;
      case e_install_repositories:
         install_repositories();
         break;
      case e_install_smart_git:
         install_smart_git();
         break;
      case e_install_git_scm:
         install_git_scm();
         break;
      case e_install_setup_folders:
         install_setup_folders();
         break;
      case e_install_storage_windows:
         install_storage_os("windows");
         break;
      case e_install_storage_universal_windows:
         install_storage_os("universal_windows");
         break;
      case e_install_patch_shell:
         install_patch_shell();
         break;
      case e_install_browser:
         install_browser();
         break;
      case e_install_cloud_data_provider:
         //install_cloud_data_provider();
         break;

#if JETBRAINS_CLION
      case e_install_jetbrains_clion:
         install_jetbrains_clion();
         break;
      case e_install_jetbrains_toolbox:
         install_jetbrains_toolbox();
         break;
#endif
#ifdef MACOS
         case e_install_xcode:
            install_xcode();
            break;
#endif
#ifdef LINUX
      case e_install_visual_studio_code:
         install_visual_studio_code();
         break;
#endif
#ifdef WINDOWS_DESKTOP
      case e_install_tortoise_git:
         install_tortoise_git();
         break;
      case e_install_msys2:
         install_msys2();
         break;
      //case e_install_browser:
        // install_browser();
         //break;
      case e_install_visual_studio_code:
         install_exe();
         break;
      case e_install_strawberry_perl:
         install_strawberry_perl();
         break;
#else
#ifdef LINUX
      case e_install_git_credential_manager:
         install_git_credential_manager();
         break;
      case e_install_deps:
         install_deps();
         break;
#endif
#endif
      default:
         throw ::exception(error_failed);
      }


   }


   void install::install_browser()
   {

      if (m_papp->m_strBrowser == "chrome")
      {

         install_google_chrome();

      }
#if defined(WINDOWS)
      else if (m_papp->m_strBrowser == "opera")
      {

         install_opera_browser();

      }
#endif

   }


   // ::string install::dropbox_client()
   // {
   //
   //    throw ::exception(todo);
   //
   //    //return file()->dropbox_client();
   //
   //    return {};
   //
   // }
   //

   // void install::wait_cloud_data_provider_up_and_running()
   // {
   //
   //    //auto atomProvider = m_papp->current_fs_folder_sync_provider();
   //
   //    auto pfoldersync = m_papp->current_fs_folder_sync();
   //
   //    if(pfoldersync)
   //    {
   //
   //       pfoldersync->wait_up_and_running();
   //
   //    }
   //
   //    //if(atomProvider == "dropbox")
   //    //{
   //
   //      // wait_dropbox_up_and_running();
   //
   //    //}
   //
   // }
   //
   //
   // void install::defer_setup_cloud_data_provider()
   // {
   //
   //    auto atomProvider = m_papp->current_fs_folder_sync_provider();
   //
   //    if(atomProvider == "dropbox")
   //    {
   //
   //       defer_setup_dropbox();
   //
   //    }
   //
   // }
   //

   void install::on_finished()
   {

      m_bInstalling = false;

      auto strTitle = get_title();

      information() << "install::on_finished : " << get_title();

      //set_status1("Downloading TortoiseSVN");

      //::file::path path = download("tortoisesvn");

      //set_status1("Installing TortoiseSVN");

      //::property_set set;

      ////call_sync("msiexec.exe", "/i \"" + path + "\" /passive /norestart ADDLOCAL=ALL", path.folder(), ::e_display_default, 10_min, set);
      //{

      if (is_installed(false))
      {

         set_status2("");

         if (m_iTry == 0)
         {

            //   ::string str;

            //   str = "Already installed";

            //   set_status(str);

            //}
            //else if (m_iTry == 1)
            //{

            ::string str;

            str = "Just installed.";

            set_status(str);

         }
         else if (m_iTry >= 1)
         {

            ::string str;

            str.formatf("Installed after multiple attempts (%d).", m_iTry + 1);

            set_status(str);

         }

         m_papp->on_installed(m_einstall, true);

         //m_pimpact->set_need_redraw();

         //m_pimpact->post_redraw();

      }
      else
      {

         ::string str;

         str = "Not installed!! ";

         str.append_formatf("Attempt no. %d to install", m_iTry);

         set_status(str);

         task_sleep(500_ms);

         if (m_iTry < m_iTryCount)
         {


            m_iTry++;

            defer_start_installation();

         }
         else
         {

            //      //m_strGitInstallationStatus += "Important options to select: \n";

            //      run();


            //   iTry--;

            //}

            ::string str2 = "Couldn't be installed...";

            str2.append_formatf("In %d attempts...", m_iTry);

            str2 += "You can retry...\n\n";

            set_status2(str2);

         }

      }

      m_happeningFinished.set_happening();

   }


   void install::start_installation(int iTryCount)
   {

      if (has_download_step())
      {

         information() << get_title() << " has download step... ";

         set_status2("Waiting to download...");

         m_papp->queue(id_download)->sync([this]()
            {

               download();

            }, 30_min);

      }

      append_status2("Waiting to install...");

      m_iTryCount = iTryCount;

      m_iTry = 0;

      defer_start_installation();

   }


   void install::wait_installation()
   {

      m_happeningFinished.wait(2_hour);

   }


   void install::defer_start_installation()
   {

      m_bInstalling = true;

      m_happeningFinished.reset_happening();

      m_papp->m_bStartingInstallation2 = false;

      wait_dependencies();

      if (m_einstall == e_install_visual_studio)
      {

         m_papp->queue(id_system_install)->sync([this]()
            {

               install_graphical_ide();

            }, 2_hour);

      }
      else if (m_einstall >= e_install_repository_first
         && m_einstall < e_install_repository_first + 100)
      {

         m_papp->queue(id_repository_install)->async([this]()
            {

               try
               {

                  run_normal_install();

               }
               catch (...)
               {

               }

            });

      }
      else if (m_einstall >= e_install_storage_first
         && m_einstall < e_install_storage_first + 100)
      {

         m_papp->queue(id_storage_install)->async([this]()
            {

               try
               {

                  run_normal_install();

               }
               catch (...)
               {

               }

            });

      }
      else
      {

         m_papp->queue(id_system_install)->sync([this]()
            {

               try
               {

                  run_normal_install();

               }
               catch (...)
               {

               }

            }, 30_min);

      }

   }


   //void install::install_graphical_ide()
   //{

   //   m

   //   //void application::start_install_graphical_ide()
   //   //{

   //      //fork([this]()
   //      //   {

   //   //::index iTry = 0;

   //   //while (!is_installed() && iTry < 6)
   //   //{

   //   //   m_bInstalling = true;

   //   //   install_graphical_ide();

   //   //   iTry++;

   //   //   task_sleep(1_s);

   //   //}

   //   //if (is_installed())
   //   //{

   //   //   if (m_bInstalling)
   //   //   {

   //   //      m_bInstalling = false;

   //   //      m_papp->m_bJustInstalledGraphicalIde = true;

   //   //      m_papp->m_timeFinishedInstallingGraphicalIde.Now();

   //   //   }

   //   //   ::string str;

   //   //   //str.formatf("Installed", m_strGraphicalIdeName.c_str());

   //   //   str = "Installed";

   //   //   m_papp->set_status(m_einstall, str);

   //   //   m_papp->set_status2(m_einstall, str);

   //   //   //m_pimpact->set_need_redraw();

   //   //   //m_pimpact->post_redraw();

   //   //}


   //}


   //bool install::is_installed()
   //{

   //   return m_papp->is_installed(m_einstall);

   //}
   //
   //
   // trace_function install::task_group_trace_function(task_group* ptaskgroup)
   // {
   //
   //    if (ptaskgroup)
   //    {
   //
   //       if (!m_pinstallloginterface && ptaskgroup->m_pintegration)
   //       {
   //
   //          m_pinstallloginterface = ptaskgroup->m_pintegration->m_pimpactinterface;
   //
   //       }
   //
   //       m_ptaskgroupOptional = ptaskgroup;
   //
   //    }
   //
   //    ::trace_function tracefunction = [this](enum_trace_level etracelevel, const ::scoped_string& scopedstr, bool bCarriage)
   //       {
   //
   //
   //          if (m_ptaskgroupOptional)
   //          {
   //
   //             ::string strStatus;
   //
   //             ::string strLine(scopedstr);
   //
   //             strStatus.formatf("%c: %s", trace_level_letter(etracelevel), strLine.c_str());
   //
   //             {
   //
   //                _synchronous_lock synchronouslock(m_ptaskgroupOptional->synchronization());
   //
   //                m_ptaskgroupOptional->m_straLine3.feed_line(strStatus, bCarriage);
   //
   //             }
   //
   //             m_ptaskgroupOptional->m_pintegration->m_pimpactinterface->on_lines_change();
   //
   //          }
   //          else
   //          {
   //
   //             ::string strStatus;
   //
   //             strStatus.formatf("%c: %s%c", trace_level_letter(etracelevel), scopedstr.c_str(), line_feed_letter(bCarriage));
   //
   //             set_status2(strStatus);
   //
   //          }
   //
   //       };
   //
   //    return tracefunction;
   //
   // }


   void install::download_and_gzuntar(const ::file::path& pathUrl, const ::file::path& pathFolder, int iEat)
   {

      property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      //auto path = m_pathFolder / m_path / (m_strName + ".tar.gz");

      ::file::path pathDownloadFolder;

      pathDownloadFolder = directory()->download() / "Code!!";

      auto pathTarGz = pathDownloadFolder / pathUrl.name();

      {

         auto pfileTarGz = file()->get_writer(pathTarGz);

         ::property_set set;

         auto url = http()->get_effective_url(pathUrl, set);

         set_status2("Downloading \"" + url + "\"...");

         ::particle* pparticle = this;

         set["transfer_progress_function"] = ::transfer_progress_function(
            [this](double dRate, filesize done, filesize total)
            {

               if (total > 0)
               {

                  ::string strTopic2;

                  strTopic2.formatf("Downloading %0.2f%% %d of %d...", dRate * 100.0,
                     done, total);


                  set_status2(strTopic2);

                  // if (done == total)
                  // {
                  //
                  //    information() << "\r" << strTopic2 << "\n";
                  //
                  //    information() << "Downloading complete";
                  //
                  // }
                  // else
                  // {
                  //
                  //    information() << "\r" << strTopic2;
                  //
                  // }

                  //m_pimpactinterface->on_state_change();

               }

            });



         pparticle->http()->download(pfileTarGz, url, set);

         //auto pathTar = m_pathFolder / m_path / (m_strName + ".tar");

         set_status2("Download finished.");

      }

      auto pathTar = pathTarGz;
      if (!pathTar.case_insensitive_ends_eat(".gz"))
      {
         pathTar += ".gz";
      }

      {
         auto pfileTarGz = file()->get_reader(pathTarGz);

         auto pfileTar = file()->get_writer(pathTar);

         set_status2("Uncompressing...");

         auto t2 = ::transfer_progress_function(
            [this](double dRate, filesize done, filesize total)
            {

               if (total > 0)
               {

                  ::string strTopic2;

                  strTopic2.formatf("Uncompressing %0.2f%% %d of %d...", dRate * 100.0,
                     done, total);

                  // if (done == total)
                  // {
                  //
                  //    set_status2(strTopic2);
                  //
                  //    //set_status2("Uncompressing complete");
                  //
                  // }
                  // else
                  // {

                  set_status2(strTopic2);



                  //                    }

                                      //m_pimpactinterface->on_state_change();

               }

            });


         system()->zlib_uncompress(pfileTar, pfileTarGz, t2);

         set_status2("Uncompressing complete");

      }

      {
         auto pfileTar = file()->get_reader(pathTar);
         //pmemoryFileTar->seek_to_begin();

         set_status2("Untarring to \"" + pathFolder + "\"...");

         ::function<void(const::scoped_string& scopedstr) > callback;

         character_count iLastLineLength = 0;
         int iFilesExtracted = 0;
         callback = [this, &iLastLineLength, &iFilesExtracted](const ::scoped_string& scopedstr)
            {

               auto s = scopedstr.size();

               auto extra = iLastLineLength - s;

               ::string str;

               ::string strExtra(' ', maximum(0, extra + 1));

               if (scopedstr.ends("\n"))
               {

                  str << "\r" << scopedstr(0, scopedstr.size() - 1) << strExtra << "\n";

               }
               else
               {

                  str << "\r" << scopedstr << strExtra;

               }

               set_status2(str);

               iLastLineLength = s;

               iFilesExtracted++;

            };

         nano()->archive()->untar(pathFolder, pfileTar, iEat, callback);

         // ::string str;
         // str << iFilesExtracted << " files extracted\n";
         // callback(str);
      }

      set_status2("Untarring complete");

   }



   ::file::path install::download_to_folder(
      const ::file::path& pathDownloadFolder,
      const ::file::path& pathUrl, const ::scoped_string& scopedstrName)
   {

      ::transfer_progress_function transferprogressfunction = [this](double d, filesize done, filesize total)
         {

            if (total == 0 || total == (filesize)-1)
            {

               ::string str2;

               str2.formatf("Dowloading (%lld)", done);

               set_status2(str2);

            }
            else if (total == done)
            {

               ::string str2;

               str2.formatf("Downloaded %lld bytes", done);

               set_status2(str2);

            }
            else
            {

               ::string str2;

               str2.formatf("Dowloading %0.1f%% (%lld of %lld)", d * 100.0, done, total);

               set_status2(str2);

            }

         };

      information(pathUrl);

      set_status2("Downloading \"" + pathUrl.name() + "\"...");

      preempt(600_ms);

      //m_pimpact->set_need_redraw();

      //m_pimpact->post_redraw();

      ::property_set set;

      set["raw_http"] = true;

      set["transfer_progress_function"] = transferprogressfunction.m_p;

      auto path = pathDownloadFolder / scopedstrName;

      m_papp->http()->download(path, pathUrl, set);

      auto sizeFile = file()->length(path);

      double dSizeKbytes = sizeFile/1024.0;

      auto strFileSize = ::format("{:.1f} kbytes", dSizeKbytes);

      print_line("Downloaded \""+pathUrl+"\" to \""+path+"\" ("+strFileSize+").");

      return path;

      //_run_installer();

   }


   ::file::path install::download_to_downloads_code__(const ::file::path& pathUrl, const ::scoped_string& scopedstrName)
   {

      ::file::path pathDownloadFolder;

      pathDownloadFolder = directory()->download() / "Code!!";

      return download_to_folder(
         pathDownloadFolder,
         pathUrl,
         scopedstrName);

   }


   void install::install_storage_os(const ::scoped_string& scopedstrOs)
   {

      ::string strName = "storage-" + scopedstrOs + ".zip";

      auto pathUrl = "https://" + scopedstrOs + ".ca2.store/storage-" + scopedstrOs + ".zip";

      m_path = download_to_operating_system(pathUrl, strName);

      unzip(m_papp->operating_system_folder(), m_path);

      on_finished();

   }

   //
   // void install::install_cloud_data_provider()
   // {
   //
   //    auto atomProvider = m_papp->current_fs_folder_sync_provider();
   //
   //    if (atomProvider == "dropbox")
   //    {
   //
   //       _install_dropbox();
   //
   //    }
   //
   //    on_finished();
   //
   // }


   void install::install_user_ssh_keys()
   {

      auto callbackStatus2 = [this](const ::scoped_string& scopedstr)
         {

            set_status2(scopedstr);

         };

      set_status2("Setting up SSH keys... please wait...");

      //::file::path pathSourceFolder = m_papp->cloud_folder() / "box/.ssh";

//       ::string_array straSource;
//
//       straSource.add("id_auth");
//       straSource.add("id_auth.pub");
//       straSource.add("id_sign");
//       straSource.add("id_sign.pub");
//
//       ::file::path pathTargetFolder = directory_system()->home() / ".ssh";
//
//       if (directory_system()->contains_files(pathTargetFolder, straSource, 32))
//       {
//
//          return;
//
//       }
//
//       auto pfsfoldersync = m_papp->current_fs_folder_sync();
//
//       if (pfsfoldersync->check_files(pathSourceFolder, straSource, callbackStatus2))
//       {
//
//          pfsfoldersync->copy_files_out(pathTargetFolder, pathSourceFolder, straSource, callbackStatus2);
//
//       }
//
// #if defined(LINUX) || defined(MACOS)
//
//       chmod(pathTargetFolder / "id_auth", S_IRUSR | S_IWUSR);
//
// #endif


   }


   // ::string install::cloud_non__empty__file_as_string(const ::file::path& path)
   // {
   //
   //    auto callbackStatus2 = [this](const ::scoped_string& scopedstr)
   //       {
   //
   //          set_status2(scopedstr);
   //
   //       };
   //
   //    auto pfsfoldersync = m_papp->current_fs_folder_sync();
   //
   //    ::string str = pfsfoldersync->non__empty__file_as_string(path, callbackStatus2);
   //
   //    return str;
   //
   // }
   //
   //
   // void install::wait_cloud_folder_contains_files(const ::file::path& path, const ::string_array& straName, int iMinimumSize)
   // {
   //
   //    auto callbackStatus2 = [this](const ::scoped_string& scopedstr)
   //       {
   //
   //          set_status2(scopedstr);
   //
   //       };
   //
   //    auto pfsfoldersync = m_papp->current_fs_folder_sync();
   //
   //    pfsfoldersync->wait_folder_contains_files(path, straName, iMinimumSize, callbackStatus2);
   //
   // }


   bool install::are_fonts_installed()
   {

      auto ___fontsFolder = directory_system()->___fonts();

      if (!directory_system()->is(___fontsFolder))
      {

         return false;

      }

      // auto pathListing = m_papp->cloud_folder() / "box/___fonts/index.txt";
      //
      // auto strListing = cloud_non__empty__file_as_string(pathListing);
      //
      // if (strListing.is_empty() || strListing.trimmed().case_insensitive_equals("(empty)"))
      // {
      //
      //    return true;
      //
      // }

//       ::string_array straName;
//
//       straName.add_lines(strListing);
//
//       straName.trim();
//
//       straName.erase_empty();
//
//       straName.erase_duplicates();
//
// #ifdef WINDOWS
//
//       straName.predicate_erase([](auto& str) {return str.contains("[no-windows]"); });
//
// #else
//
//       straName.predicate_each([](auto& str) {return str.find_replace("[no-windows]", ""); });
//
// #endif
//
//       if (!directory_system()->contains_files(___fontsFolder, straName, 1_KiB))
//       {
//
//          return false;
//
//       }

      return true;

   }


   // ::file::path install::cloud_fonts_folder()
   // {
   //
   //    return m_papp->cloud_folder() / "box/___fonts";
   //
   // }
   //

   void install::install_user_fonts()
   {

      for (int iTry = 0; iTry < 6; iTry++)
      {

         if (are_fonts_installed())
         {

            break;

         }

         preempt(iTry * 5_s);

         _install_user_fonts();

      }

   }


   void install::_install_user_fonts()
   {

//       auto pathSourceFolder = m_papp->cloud_folder() / "box/___fonts";
//
//       auto pathSourceIndex = pathSourceFolder / "index.txt";
//
//       auto pfscloudfolder = m_papp->current_fs_folder_sync();
//
//       set_status2(
//          "Checking for index.txt at " + pathSourceFolder + "... (index.txt should exist to continue installation with code...)");
//
//       while (true)
//       {
//
//          if (pfscloudfolder->file_exists(pathSourceIndex))
//          {
//
//             break;
//
//          }
//
//          preempt(1_s);
//
//       }
//
//       set_status2("Checking if " + ::string(pathSourceIndex) + " is up-to-date and present...");
//
//       //directory_system()->change_current(pathSourceFolder);
//
//       ::string_array lines;
//
//       ::string strIndex;
//
//       while (true)
//       {
//
//          preempt(1_s);
//
//          ::string strLs;
//
//          strIndex = pfscloudfolder->safe_get_string(pathSourceIndex);
//
//          lines.add_lines(strIndex);
//
//          if (lines.size() >= 7)
//          {
//
//             lines.erase_empty();
//
//             if (lines[0] == "empty")
//             {
//
//                break;
//
//             }
//
//          }
//
//          lines.trim();
//
//          lines.erase_empty();
//
//          lines.erase_duplicates();
//
//          if (lines.size() > 0)
//          {
//
//             break;
//
//          }
//
//       }
//
//       lines.predicate_erase([](auto& str) {return !str.case_insensitive_ends(".ttf") || str.begins("."); });
//
//       lines.erase_duplicates();
//
// #ifdef WINDOWS
//
//       lines.predicate_erase([](auto& str) {return str.contains("[no-windows]"); });
//
// #else
//
//       lines.predicate_each([](auto& str) {return str.find_replace("[no-windows]", ""); });
//
// #endif
//
//       if (lines.is_empty() || lines.first().trimmed().case_insensitive_equals("(empty)"))
//       {
//
//          return;
//
//       }
//       else
//       {
//
//          pfscloudfolder->check_files(pathSourceFolder, lines, [this](auto& str)
//             {
//
//                set_status2("Checking file : " + str);
//
//             });
//
//       }
//
//       auto pathSourceIndexProcessed = application()->defer_process_path(pathSourceIndex);
//
//       install_user_fonts_from_font_listing(pathSourceIndexProcessed);

   }


   void install::unzip(const ::file::path& pathFolder, const ::file::path& pathZip)
   {

      ::function<bool(const::scoped_string& scopedstr) > callback;

      character_count iLastLineLength = 0;

      int iFilesExtracted = 0;

      callback = [this, &iLastLineLength, &iFilesExtracted](const ::scoped_string& scopedstr)->bool
      {

         auto s = scopedstr.size();

         auto extra = iLastLineLength - s;

         ::string str;

         ::string strExtra(' ', maximum(0, extra + 1));

         if (scopedstr.ends("\n"))
         {

            str << "\r" << scopedstr(0, scopedstr.size() - 1) << strExtra << "\n";

         }
         else
         {

            str << "\r" << scopedstr << strExtra;

         }

         set_status2(str);

         iLastLineLength = s;

         iFilesExtracted++;

      };

      file()->unzip_to_folder(m_papp->operating_system_folder(), m_path, callback);

      set_status2("Unzip complete");

   }


   ::file::path install::download_to_operating_system(const ::file::path& pathUrl, const ::scoped_string& scopedstrName)
   {

      ::file::path pathDownloadFolder;

      pathDownloadFolder = directory()->download() / "Code!!";

      return download_to_folder(
         pathDownloadFolder,
         pathUrl,
         scopedstrName);

   }


   void install::download()
   {

      ::string strName;

      auto pathUrl = get_download_url(strName);

      m_path = download_to_downloads_code__(pathUrl, strName);

   }


   void install::_run_installer()
   {



   }


   bool install::has_download_step()
   {

      ::string strName;

      auto pathUrl = get_download_url(strName);

      information() << "get_download_url : " << get_title() << " URL : " << pathUrl;

      return pathUrl.has_character();

   }


   //void install::download()
   //{

   //   auto transferprogressfunction = [this](double d, filesize done, filesize total)
   //      {

   //         if (total == 0 || total == (filesize)-1)
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading (%lld)", done);

   //            m_papp->set_status2(m_einstall, str2);

   //         }
   //         else
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading %0.1f%% (%lld of %lld)", d * 100.0, done, total);

   //            m_papp->set_status2(m_einstall, str2);

   //         }

   //         //m_pimpact->set_need_redraw();

   //         //m_pimpact->post_redraw();

   //      };

   //   ::file::path path = m_papp->download(m_einstall, transferprogressfunction);

   //   information(path);


   //}


   void install::_install_app_simple_repository()
   {

      _install_repository(e_repository_simple);

   }


   void install::install_app_simple_repository()
   {

      _install_app_simple_repository();

      on_finished();

   }


   void install::_install_repository(::coding::enum_repository erepository)
   {

      try
      {

         {

            if (m_papp->__is_repository_installed(erepository))
            {

               set_status("Already Installed!!");

            }
            else
            {

               ::file::path path = m_papp->get_repository_path(erepository);

               printf_line("Repository Path : %s", path.c_str());

               ::file::path pathForBash;

               pathForBash = m_papp->bash_path(path);

               printf_line("Repository Path (bash path): %s", pathForBash.c_str());

               ::file::path pathUrl;

               pathUrl = m_papp->get_repository_url(erepository);

               printf_line("Repository URL (bash path): %s", pathUrl.c_str());

               set_status("Cloning " + pathUrl + "to " + pathForBash + " ...");

               directory_system()->create(path.folder());

               directory_system()->change_current(path.folder());

               if (m_papp->ssh_code_mode() || m_papp->standard_code_mode())
               {

                  int iExitCode = synchronous_posix_terminal(
                     "eval $(ssh-agent -s); ssh-add ~/.ssh/id_auth; git clone --recurse-submodules "
                     + pathUrl + " " + pathForBash);

                  if (iExitCode == 0)
                  {

                     directory_system()->change_current(path);

                     ::file::path pathCheckout = m_papp->get_repository_path(e_repository_tool_os) / "bin/checkout";

                     int iExitCode2 = synchronous_posix_terminal(pathCheckout);

                     if (iExitCode2 == 0)
                     {

                        set_status("Cloned and Checked Out!!");

                     }
                     else
                     {

                        set_status("Checkout Failed!");

                     }

                  }
                  else
                  {

                     set_status("Not installed!");

                  }

               }
               else
               {


#ifdef WINDOWS

                  int iExitCode = synchronous_posix_terminal(
                     "git clone --recurse-submodules " + pathUrl + " " + pathForBash);

                  if (iExitCode == 0)
                  {

                     directory_system()->change_current(path);

                     ::file::path pathCheckout = m_papp->get_repository_path(e_repository_tool_os) / "bin/checkout";

                     int iExitCode2 = synchronous_posix_terminal(pathCheckout);

                     if (iExitCode2 == 0)
                     {

                        set_status("Cloned and Checked Out!!");

                     }
                     else
                     {

                        set_status("Checkout Failed!");

                     }

                  }
                  else
                  {

                     set_status("Not installed!");

                  }

#else

                  int iExitCode = synchronous_posix_terminal(
                     "git clone " + pathUrl + " " +
                     pathForBash + " --recurse-submodules");

                  if (iExitCode == 0)
                  {

                     directory_system()->change_current(path);

                     int iExitCode2 = synchronous_posix_terminal("checkout");

                     if (iExitCode2 == 0)
                     {

                        set_status("Cloned and Checked Out!!");

                     }
                     else
                     {

                        set_status("Checkout Failed!");

                     }

                  }
                  else
                  {

                     set_status("Not installed!");

                  }

#endif


               }

            }

         }

      }
      catch (...)
      {

      }

   }


   void install::install_repository(::coding::enum_repository erepository)
   {

      _install_repository(erepository);

      on_finished();

   }


   void install::_install_repository(const ::scoped_string& scopedstr)
   {

      try
      {

         if (m_papp->_is_repository_installed(scopedstr))
         {

            set_status("Already Installed!!");

         }
         else 
         {
            
            ::file::path path = m_papp->_get_repository_path(scopedstr);
            
            ::file::path pathForBash;
            
            pathForBash = m_papp->bash_path(path);
            
            ::file::path pathUrl;
            
            pathUrl = m_papp->_get_repository_url(scopedstr);
            
            set_status("Cloning " + pathUrl + "to " + pathForBash + " ...");
            
            if (m_papp->ssh_code_mode() || m_papp->standard_code_mode()) 
            {
               
               int iExitCode = synchronous_posix_terminal(
                                                          "eval $(ssh-agent -s); ssh-add ~/.ssh/id_auth; git clone " + pathUrl + " " +
                                                          pathForBash + " --recurse-submodules");
               
               if (iExitCode == 0) 
               {
                  
                  directory_system()->change_current(path);
                  
                  auto pathCheckout = m_papp->tool_os_folder() / "bin/checkout";
                  
                  int iExitCode2 = synchronous_posix_terminal(
                                                              "eval $(ssh-agent -s); ssh-add ~/.ssh/id_auth; " + pathCheckout);
                  
                  if (iExitCode2 == 0) 
                  {
                     
                     set_status("Cloned and Checked Out!!");
                     
                  }
                  else 
                  {
                     
                     set_status("Checkout Failed!");
                     
                  }
                  
               }
               else 
               {
                  
                  set_status("Not installed!");
                  
               }
               
            }
            else 
            {
               
#ifdef WINDOWS
               
               int iExitCode = node()->command_system(
                                                      "\"C:\\Program Files\\Git\\bin\\bash.exe\" -c \"git clone " + pathUrl + " " +
                                                      pathForBash + " --recurse-submodules\"",
                                                      [this](auto etracelevel, auto str, bool bCarriage)
                                                      {
                                                         
                                                         
                                                         set_status2("Cloning : " + str);
                                                         
                                                         //m_pimpact->set_need_redraw();
                                                         
                                                         //m_pimpact->post_redraw();
                                                         
                                                      });
               
               if (iExitCode == 0)
               {
                  
                  int iExitCode2 = node()->command_system(
                                                          "\"C:\\Program Files\\Git\\bin\\bash.exe\" -c \"checkout\"",
                                                          [this](auto etracelevel, auto str, bool bCarriage)
                                                          {
                                                             
                                                             
                                                             set_status2("Checking out : " + str);
                                                             
                                                             //m_pimpact->set_need_redraw();
                                                             
                                                             //m_pimpact->post_redraw();
                                                             
                                                          }, path);
                  
                  if (iExitCode2 == 0)
                  {
                     
                     set_status("Cloned and Checked Out!!");
                     
                  }
                  else
                  {
                     
                     set_status("Checkout Failed!");
                     
                  }
                  
               }
               else
               {
                  
                  set_status("Not installed!");
                  
               }
               
            }
            
#else
            
            int iExitCode = synchronous_posix_terminal(
                                                       "git clone " + pathUrl + " " +
                                                       pathForBash + " --recurse-submodules");
            
            if (iExitCode == 0) {
               
               directory_system()->change_current(path);
               
               int iExitCode2 = synchronous_posix_terminal("checkout");
               
               if (iExitCode2 == 0) {
                  
                  set_status("Cloned and Checked Out!!");
                  
               }
               else {
                  
                  set_status("Checkout Failed!");
                  
               }
               
            }
            else {
               
               set_status("Not installed!");
               
            }
            
         }

#endif

         }

         }
         catch (...)
         {

         }


      }


      void install::install_graphical_ide()
      {

#if defined(LINUX)

         //install_clion();

         install_jetbrains_toolbox();

#elif defined(WINDOWS_DESKTOP)

         install_visual_studio();

#endif

      }


      bool install::is_installed(bool bMayAssumeNotInstalled)
      {

         if (m_bInstalling)
         {

            return false;

         }

         if (m_einstall == e_install_visual_studio)
         {

            if (m_papp->m_bJustInstalledGraphicalIde)
            {

               if (m_papp->m_timeFinishedInstallingGraphicalIde.elapsed() < 30_s)
               {

                  return false;

               }

            }

         }

         return m_papp->__is_installed(m_einstall, bMayAssumeNotInstalled);

      }


      void install::set_status(const ::scoped_string& scopedstr)
      {

         m_strStatus = scopedstr;

         // if (m_pinstallloginterface)
         // {
         //
         //    m_pinstallloginterface->install_status(this, scopedstr);
         //
         //    m_pinstallloginterface->on_update_install_status(this);
         //
         // }

      }


      void install::set_status2(const ::scoped_string& scopedstr)
      {

         m_strStatus2 = scopedstr;

         // if (m_pinstallloginterface)
         // {
         //
         //    m_pinstallloginterface->install_status2(this, scopedstr);
         //
         //    m_pinstallloginterface->on_update_install_status(this);
         //
         // }

      }



      void install::append_status2(const ::scoped_string& scopedstr)
      {

         m_strStatus2 += scopedstr;
         //
         // if (m_pinstallloginterface)
         // {
         //
         //    m_pinstallloginterface->install_append_status2(this, scopedstr);
         //
         //    m_pinstallloginterface->on_update_install_status(this);
         //
         // }
         //


      }



      //bool application::_is_graphical_ide_installed()
      //{

      //   if (m_bGraphicalIdeOk)
      //   {

      //      return true;

      //   }

      //   m_bGraphicalIdeOk = __is_graphical_ide_installed();

      //   return m_bGraphicalIdeOk;

      //}

      //   bool application::has_unix_shell_command(const ::scoped_string& scopedstrCommand)
      //   {
      //
      //      try
      //      {
      //
      //         ::string strCommand;
      //
      //         strCommand.format("command -v %s", scopedstrCommand.c_str());
      //
      //         auto iExitCode = unix_shell_command(strCommand);
      //
      //         return iExitCode == 0;
      //
      //      }
      //      catch (...)
      //      {
      //
      //      }
      //
      //      return false;
      //
      //   }


      // void install::on_update_install_status()
      // {
      //
      //    if (m_pinstallloginterface)
      //    {
      //
      //       m_pinstallloginterface->on_update_install_status(this);
      //
      //    }
      //
      // }


      ::string install::get_name()
      {
         return m_papp->install_name(m_einstall);
      }
      ::string install::get_title()
      {
         return m_papp->install_title(m_einstall);
      }
      ::string install::get_remark()
      {
         return m_papp->install_remark(m_einstall);
      }


   bool install::are_all_dependencies_installed()
   {

      auto pcode = m_papp->code();

      auto& einstallaDependency = pcode->m_einstallaDependency[m_einstall];

      for (auto einstallDependency : einstallaDependency)
      {

         if (!m_papp->is_installed(einstallDependency, false))
         {

            return false;

         }

      }

      auto& einstallaSoftDependency = pcode->m_einstallaSoftDependency[m_einstall];

      for (auto einstallSoftDependency : einstallaSoftDependency)
      {

         auto ppair = m_papp->code()->install_map().find(einstallSoftDependency);

         if (ppair)
         {

            auto pinstall = ppair->m_element2;
            //
            // if (pinstall->m_pinstallimpactinterface
            //    && pinstall->m_pinstallimpactinterface->is_selected()
            //    && !m_papp->is_installed(einstallSoftDependency, false))
            // {
            //
            //    return false;
            //
            // }

         }

      }

      return true;

   }

      string_array install::missing_dependencies()
      {

         ::string_array straMissingDependencies;

         auto pcode = m_papp->code();

         auto& einstallaDependency = pcode->m_einstallaDependency[m_einstall];

         for (auto einstallDependency : einstallaDependency)
         {

            if (!m_papp->is_installed(einstallDependency, false))
            {

               ::string strDependencyName;

               strDependencyName = m_papp->install_name(einstallDependency);

               straMissingDependencies.add(strDependencyName);

            }

         }

         return straMissingDependencies;

      }


      void install::wait_dependencies()
      {

         auto timeTimeout = 8_hour;

         class ::time timeStart;

         timeStart.Now();

         while (::task_get_run())
         {

            if (timeStart.elapsed() > timeTimeout)
            {


               throw ::exception(error_wait_timeout);

            }

            if (are_all_dependencies_installed())
            {

               break;

            }

            preempt(2_s);

            information() << get_title() << " is in wait_dependencies waiting for : " << missing_dependencies()._008Implode(", ", " and ") << ".";

         }

      }




   } // namespace coding





