#include "framework.h"
#include "code_application.h"
//#include "code_document.h"
//#include "code_frame.h"
//#include "code_impact.h"
//#include "code_install_form_handler.h"
//#include "code_main_frame.h"
//#include "code_tab_impact.h"
#include "acme/constant/id.h"
#include "acme/exception/exit.h"
#include "acme/platform/node.h"
#include "acme/handler/sequence.h"
#include "acme/platform/scoped_restore.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/application.h"
#include "acme/operating_system/main_window.h"
#include "acme/operating_system/process.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/nano/http/http.h"

#include "acme/platform/node.h"
//#include "axis/user/user/line_layout.h"
//#include "apex/platform/os_context.h"

//#include "aura/node/windows/registry.h"
#include "acme/platform/session.h"
//#include "aura/os/_os.h"
//#include "aura/update.h"
#include "code.h"
#include "acme/operating_system/summary.h"
// #include "aura/user/user/button.h"
// #include "aura/user/user/check_box.h"
// #include "aura/user/user/user.h"
// #include "aura/windowing/windowing.h"
// #include "berg/user/user/show.h"
// #include "berg/user/user/single_document_template.h"
// #include "berg/user/simple/tab_document.h"
#include "coding/install.h"
//#include "coding/install_impact_interface.h"
//#include "coding/install_log_interface.h"

//#ifdef WINDOWS_DESKTOP


//#include "acme_windows/_.h"
//#include "acme_windows/registry.h"

//#endif

#define TEST_DATA_LOCAL 1




// void code_debugging();


namespace coding
{

   code_application::code_application() //:
//      m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization(this, "checkbox_exclude_all_folders_except_box_folder_from_dropbox_synchronization")
   {

      //m_eapplication = ::coding::e_application_code;

      //preempt(30_s);

#if defined(LINUX)

      m_strGraphicalIdeName = "CLion";

#elif defined(WINDOWS_DESKTOP)

      m_strGraphicalIdeName = "Visual Studio";

#elif defined(MACOS)

      m_strGraphicalIdeName = "Xcode";

#endif

      //m_bInstallingGraphicalIde = false;
      m_bJustInstalledGraphicalIde = false;
      m_bSourceOk = false;
      //m_bGraphicalIdeOk = false;

      //m_pimpact = nullptr;
      //m_bInstalling = false;
      m_bInterprocessCommunication = true;
      //m_bStartingInstallation = false;
      //m_ptemplateCodeMain = nullptr;


      m_bLastDeferReleaseInstallInstalling = false;

      //m_bInstallingGit = false;
      //m_bInstallingTortoiseGit = false;

      m_strAppId = "integration/code";
      m_strBaseSupportId = "integration/code";
      m_strAppName = "Code!!";
      m_bLicense = false;

      m_bFirstStageOk = false;

   }


   code_application::~code_application()
   {

   }




   // void code_application::on_change_current_cloud_data_provider(const ::action_context& actioncontext)
   // {
   //
   //    // auto atomProvider = m_strCloudDataProvider;
   //    //
   //    // auto iIndex = m_atomaCloudDataProviderOptions.find_first(atomProvider);
   //    //
   //    // if (iIndex >= 0)
   //    // {
   //    //
   //    //    m_propertyCloudDataProviderTitle.set_property(
   //    //       m_straCloudDataProviderOptionsNames[iIndex],
   //    //       actioncontext);
   //    //
   //    // }
   //    // else
   //    // {
   //    //
   //    //    m_propertyCloudDataProviderTitle.set_property(
   //    //       "(Unespecified Cloud Data Provider)",
   //    //       actioncontext);
   //    //
   //    // }
   //    //
   //    // {
   //    //
   //    //    auto pinstall = code()->install_map()[::coding::e_install_cloud_data_provider];
   //    //
   //    //    if (pinstall)
   //    //    {
   //    //
   //    //       if (pinstall->m_pinstallimpactinterface)
   //    //       {
   //    //
   //    //          pinstall->m_pinstallimpactinterface->update_title();
   //    //
   //    //       }
   //    //
   //    //    }
   //    //
   //    // }
   //    //
   //    // {
   //    //
   //    //    auto pinstall = code()->install_map()[::coding::e_install_repositories];
   //    //
   //    //    if (pinstall)
   //    //    {
   //    //
   //    //       if (pinstall->m_pinstallimpactinterface)
   //    //       {
   //    //
   //    //          pinstall->m_pinstallimpactinterface->update_title();
   //    //
   //    //       }
   //    //
   //    //    }
   //    //
   //    // }
   //    //
   // }


   // void code_application::on_change_current_browser(const ::action_context& actioncontext)
   // {
   //
   //    auto iIndex = m_atomaBrowser.find_first(m_propertyBrowser.get_property().as_atom());
   //
   //    if (iIndex >= 0)
   //    {
   //
   //       m_propertyBrowserTitle.set_property(
   //          m_straBrowserNames[iIndex],
   //          actioncontext);
   //
   //    }
   //    else
   //    {
   //
   //       m_propertyBrowserTitle.set_property(
   //          "(Unespecified browser)",
   //          actioncontext);
   //
   //    }
   //
   //    auto pinstall = code()->install_map()[::coding::e_install_browser];
   //
   //    if (pinstall)
   //    {
   //
   //       if (pinstall->m_pinstallimpactinterface)
   //       {
   //
   //          pinstall->m_pinstallimpactinterface->update_title();
   //
   //       }
   //
   //    }
   //
   // }


   // void code_application::on_change_current_repository(const ::action_context& actioncontext)
   // {
   //
   //    auto iIndex = m_atomaRepository.find_first(m_propertyRepository.get_property().as_atom());
   //
   //    if (iIndex >= 0)
   //    {
   //
   //       m_propertyRepositoryTitle.set_property(
   //          m_straRepositoryNames[iIndex],
   //          actioncontext);
   //
   //       m_propertyRepositoryDescription.set_property(
   //          m_straRepositoryDescription[iIndex],
   //          actioncontext);
   //
   //    }
   //    else
   //    {
   //
   //       m_propertyRepositoryTitle.set_property(
   //          "(Unespecified repository)",
   //          actioncontext);
   //
   //       m_propertyRepositoryDescription.set_property(
   //          "(Unespecified repository)",
   //          actioncontext);
   //
   //    }
   //
   //    auto pinstall = code()->install_map()[::coding::e_install_repositories];
   //
   //    if (pinstall)
   //    {
   //
   //       if (pinstall->m_pinstallimpactinterface)
   //       {
   //
   //          pinstall->m_pinstallimpactinterface->update_title();
   //
   //       }
   //
   //    }
   //
   // }


   void code_application::init_instance()
   {

      if (property_set().is_true("code_debugging"))
      {

         //code_debugging();

      }

      //default_data_save_handling(m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization);

      //data_get(m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization);

      // ::payload payloadAlreadyRun;
      //
      // if(!data_get_payload("already_run", payloadAlreadyRun))
      // {
      //
      //    payloadAlreadyRun = true;
      //
      //    data_set_payload("already_run", payloadAlreadyRun);
      //
      //    if(has_Dropbox_folder())
      //    {
      //
      //       m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization.set(::e_check_unchecked, e_source_initialize);
      //
      //    }
      //    else
      //    {
      //
      //       m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization.set(::e_check_checked, e_source_initialize);
      //
      //    }
      //
      //    data_set(m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization);
      //
      // }

      //set_local_data();

      //::aura::session * pcoression = &Session;

      // factory()->add_factory_item<::coding::document>();
      // factory()->add_factory_item<::coding::frame>();
      // factory()->add_factory_item<::coding::main_frame>();
      // factory()->add_factory_item<::user::button_impact>();
      // factory()->add_factory_item<::coding::impact>();
      // factory()->add_factory_item<::coding::tab_impact>();

      ::platform::application::init_instance();

      //if (!::aura::application::init_instance())
      //{

      //   return false;

      //}

      //#if TORTOISE_SVN
      //      get_property_set()["tortoise_svn"] true);
      //#endif
      //#if SMART_SVN
      //      set("smart_svn", true);
      //#endif



      // add_impact_system("main",
      //    allocateø::user::single_document_template(
      //       "main",
      //       ::type < simple_tab_document >(),
      //       ::type < ::coding::main_frame >(),
      //       ::type < ::coding::tab_impact >()));

      //m_ptemplateCodeMain = ptemplate;

      //add_document_template(ptemplate);


      //return true;

      // m_propertyCloudDataProvider.property_changed() += [this](auto& propertychanged)
      //    {
      //
      //       if (m_propertyCloudDataProvider && propertychanged)
      //       {
      //
      //          on_change_current_cloud_data_provider(propertychanged.m_actioncontext);
      //
      //       }
      //
      //    };
      //
      // m_propertyBrowser.property_changed() += [this](auto& propertychanged)
      //    {
      //
      //       if (m_propertyBrowser && propertychanged)
      //       {
      //
      //          on_change_current_browser(propertychanged.m_actioncontext);
      //
      //       }
      //
      //    };
      //
      // m_propertyRepository.property_changed() += [this](auto& propertychanged)
      //    {
      //
      //       if (m_propertyRepository && propertychanged)
      //       {
      //
      //          on_change_current_repository(propertychanged.m_actioncontext);
      //
      //       }
      //
      //    };
      //
      // data_get(m_propertyRepository);
      //
      // default_data_save_handling(m_propertyRepository);
      //
      //
      // data_get(m_propertyCloudDataProvider);
      //
      // default_data_save_handling(m_propertyCloudDataProvider);

#if defined(WINDOWS)
      m_atomaCloudDataProviderOptions.add("onedrive");
      m_straCloudDataProviderOptionsNames.add("OneDrive");
#endif

#if defined(WINDOWS)

      m_atomaCloudDataProviderOptions.add("google_drive");
      m_straCloudDataProviderOptionsNames.add("Google Drive");

#endif

      m_atomaCloudDataProviderOptions.add("dropbox");
      m_straCloudDataProviderOptionsNames.add("Dropbox");


      m_atomaBrowser.add("chrome");
      m_straBrowserNames.add("Google Chrome");

#if defined(WINDOWS)

      m_atomaBrowser.add("opera");
      m_straBrowserNames.add("Opera Browser");

#endif

#if defined(WINDOWS)

      m_atomaBrowser.add("edge");
      m_straBrowserNames.add("Edge");

#endif

#if defined(MACOS)

      m_atomaBrowser.add("safari");
      m_straBrowserNames.add("Safari");

#endif


#if defined(LINUX)

      m_atomaBrowser.add("system");
      m_straBrowserNames.add("System Browser");

#endif

      m_atomaRepository.add("simple");
      m_straRepositoryNames.add("Simple Repository");
      m_straRepositoryDescription.add("github.com/ca2/app-simple Repository");

      m_atomaRepository.add("repositories");
      m_straRepositoryNames.add("Repositories");
      m_straRepositoryDescription.add("Repositories listed at $fs_folder_sync://box/.repositories/index.txt file");

      // auto cloudDataProviderOption = m_strCloudDataProvider;
      //
      // if (!m_atomaCloudDataProviderOptions.contains(cloudDataProviderOption))
      // {
      //
      //    m_propertyCloudDataProvider.set_property(
      //       m_atomaCloudDataProviderOptions.first(),
      //       e_source_initialize | e_source_user);
      //
      // }
      //
      //
      // auto browserOption = m_strBrowser;
      //
      // if (!m_atomaBrowser.contains(browserOption))
      // {
      //
      //    m_propertyBrowser.set_property(
      //       m_atomaBrowser.first(),
      //       e_source_initialize | e_source_user);
      //
      // }
      //
      //
      // auto repositoryOption = m_strRepository;
      //
      // if (!m_atomaRepository.contains(repositoryOption))
      // {
      //
      //    m_propertyRepository.set_property(
      //       m_atomaRepository.first(),
      //       e_source_initialize | e_source_user);
      //
      // }


   }


   void code_application::term_application()
   {

      ::coding::application::term_application();

   }



   // ::atom code_application::current_fs_folder_sync_provider()
   // {
   //
   //    return m_strCloudDataProvider;
   //    //{
   //    //case id_one_drive:
   //    //   return "onedrive://";
   //    //case id_dropbox:
   //    //   return "dropbox://";
   //    //default:
   //    //   break;
   //    //}
   //
   //    //return ::coding::application::cloud_folder();
   //
   // }
   //
   //
   // ::atom code_application::current_browser()
   // {
   //
   //    return m_strBrowser;
   //
   // }


   bool code_application::has_Dropbox_folder()
   {

#if defined(LINUX)

      auto pathHome = directory_system()->home();

      bool bHasFolder1 = directory_system()->is(pathHome / "Dropbox");

      bool bHasFolder2 = directory_system()->is(pathHome / ".dropbox-dist");

      bool bHasFolder3 = directory_system()->is(pathHome / ".dropbox");

      return bHasFolder1 && bHasFolder2 && bHasFolder3;

#else

      auto pathDropbox = defer_process_path("dropbox://");

      if (!directory_system()->is(pathDropbox))
      {

         return false;

      }

      return true;

#endif
   }



   // void code_application::create_options_impact(const ::atom & atom, ::user::interaction * puserinteractionParent)
   // {
   //
   //
   //    auto pline = create_line_layout(puserinteractionParent, e_orientation_horizontal);
   //
   //    m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization = create_check_box(pline, "checkbox_exclude_all_folders_except_box_folder_from_dropbox_synchronization");
   //
   //    m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization->set_check_property(m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization);
   //
   //    m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization->set_size({24, 24});
   //
   //    m_pstillExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization= create_label(pline, "Exclude all folders except \"box\" folder from Dropbox synchronization.");
   //
   //    m_pstillExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization->m_bAutoResize = true;
   //
   //
   // }


   ::coding::e_mode code_application::as_emode(const ::scoped_string & scopedstr)
   {

      ::coding::enum_mode emode = ::coding::e_mode_none;

      if(scopedstr.case_insensitive_equals("standard"))
      {

         emode = ::coding::e_mode_standard;

      }
      else if(scopedstr.case_insensitive_equals("ssh"))
      {

         emode = ::coding::e_mode_ssh;

      }
      else if(scopedstr.case_insensitive_equals("gcm"))
      {

         emode = ::coding::e_mode_gcm;

      }
      else
      {

         emode = ::coding::e_mode_initial_setup;

      }

      return emode;

   }


   // enum_mode code_application::as_emode(const ::domain_id & domainid)
   // {
   //
   //    if(domainid.m_edomain == e_domain_1024)
   //    {
   //
   //       return (enum_mode) domainid.m_iId;
   //
   //    }
   //
   //    return e_mode_none;
   //
   // }


   ::string code_application::as_string(const ::coding::e_mode & emode)
   {

      switch(emode.m_eenum)
      {
      case ::coding::e_mode_standard:
         return "standard";
      case ::coding::e_mode_gcm:
         return "gcm";
      case ::coding::e_mode_ssh:
         return "ssh";
      default:
         return "initial_setup";
      }

   }


   // ::atom code_application::filter_code_mode(const ::atom & atom)
   // {
   //
   //    ::string strMode(atom.as_string());
   //
   //    if(strMode.case_insensitive_equals("standard"))
   //    {
   //
   //       strMode = "standard";
   //
   //    }
   //    else if(strMode.case_insensitive_equals("ssh"))
   //    {
   //
   //       strMode = "ssh";
   //
   //    }
   //    else if(strMode.case_insensitive_equals("gcm"))
   //    {
   //
   //       strMode = "gcm";
   //
   //    }
   //    else
   //    {
   //
   //       strMode.empty();
   //
   //    }
   //
   //    return strMode;
   //
   // }


   ::coding::e_mode code_application::get_code_mode()
   {

      auto strMode = file_system()->as_string(directory_system()->home()/".config/integration/code/mode.txt");

      auto emode = as_emode(strMode);

      if(emode.is_nok())
      {

         return ::coding::e_mode_none;

      }

      return emode;

   }


   void code_application::set_code_mode(const ::coding::e_mode & emode)
   {

      auto strMode = as_string(emode);

      if(strMode.is_empty())
      {

         return;

      }

      file_system()->put_block(directory_system()->home()/".config/integration/code/mode.txt", strMode);

   }


   void code_application::on_request(::request* prequest)
   {

#ifdef WINDOWS

      m_pathCode = directory()->download() / "Code!!/code.exe";

      m_pathApplicationBuildHelper = "C:/operating_system/bin/application_build_helper.exe";

      m_pathApplicationBuildHelperZip = "C:/operating_system/bin/application_build_helper.zip";

#else

      m_pathCode = directory_system()->home() / "code/operating_system/bin/code";

      m_pathApplicationBuildHelper = directory_system()->home() / "code/operating_system/bin/application_build_helper";

      m_pathApplicationBuildHelperZip = directory_system()->home() / "code/operating_system/bin/application_build_helper.zip";

#endif

      // if (impact_system("main")->get_document_count() <= 0)
      // {
      //
      //    impact_system("main")->open_new_document(this);
      //
      // }

   }


#if TORTOISE_SVN


   void code_application::install_tortoise_svn()
   {

      set_status1("Downloading TortoiseSVN");

      ::file::path path = download("tortoisesvn");

      set_status1("Installing TortoiseSVN");

      ::property_set set;

      //call_sync("msiexec.exe", "/i \"" + path + "\" /passive /norestart ADDLOCAL=ALL", path.folder(), ::e_display_default, 10_min, set);

   }


#endif


#if SMART_SVN


   //void code_application::install_smart_svn()
   //{

   //   ::file::path path = download("smartsvn");

   //}

#endif


#if TORTOISE_GIT


   //bool code_application::defer_install_main_item(enum_install einstall, int iTry)
   //{

   //   ::string strTitle = get_title(einstall);

   //   //set_status1("Downloading TortoiseSVN");

   //   //::file::path path = download("tortoisesvn");

   //   //set_status1("Installing TortoiseSVN");

   //   //::property_set set;

   //   ////call_sync("msiexec.exe", "/i \"" + path + "\" /passive /norestart ADDLOCAL=ALL", path.folder(), ::e_display_default, 10_min, set);
   //   {

   //      int iAttempt = 0;

   //      while (iTry > 0)
   //      {

   //         if (is_installed(einstall))
   //         {

   //            set_status2(einstall, "");

   //            if (iAttempt == 0)
   //            {

   //               ::string str;
   //
   //               str = "Already installed";

   //               set_status(einstall, str);

   //            }
   //            else if (iAttempt == 1)
   //            {
   //
   //               ::string str;

   //               str = "Now installed.";

   //               set_status(einstall, str);

   //            }
   //            else if (iAttempt >= 2)
   //            {

   //               ::string str;

   //               str.formatf("Installed after multiple attempts (%d).", iAttempt);

   //               set_status(einstall, str);

   //            }

   //            //m_pimpact->set_need_redraw();

   //            //m_pimpact->post_redraw();

   //            return true;

   //         }

   //         iAttempt++;

   //         ::string str;

   //         str = "Not installed!!\n";

   //         str.append_formatf("Attempt no. %d to install\n", iAttempt);

   //         set_status(einstall, str);

   //         //m_strGitInstallationStatus += "Important options to select: \n";

   //         install_tortoise_git();

   //         task_sleep(500_ms);

   //         iTry--;

   //      }

   //      ::string str2 = "Couldn't be installed...";

   //      str2.append_formatf("In %d attempts...", iAttempt);

   //      str2 += "You can retry...\n\n";

   //      set_status2(einstall, str2);

   //      return false;

   //   }

   //}


   //bool code_application::is_tortoise_git_installed()
   //{

   //   throw ::exception(todo);

   //   return false;

   //}


   //void code_application::install_main_item_type2(enum_install einstall)
   //{

   //   scoped_restore(m_bInstallingTortoiseGit);

   //   m_bInstallingTortoiseGit = true;

   ////   ::file::path pathInf = "C:/operating_system/git-scm.inf";

   ////   if (!file_system()->exists(pathInf))
   ////   {

   ////      ::file::path pathUrl = "https://ca2.software/download/windows/git-scm.inf";

   ////      ::property_set set;

   ////      set["raw_http"] = true;

   ////      http().download(pathUrl, pathInf, set);

   ////}

   //   auto transferprogressfunction = [this](double d, filesize done, filesize total)
   //      {

   //         if (total == 0 || total == (filesize)-1)
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading TortoiseGit (%lld)", done);

   //            set_status2(einstall, (str2);

   //         }
   //         else
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading TortoiseGit %0.1f%% (%lld of %lld)", d * 100.0, done, total);

   //            set_status2(e_install_tortoise_git, str2);

   //         }

   //         //m_pimpact->set_need_redraw();

   //         //m_pimpact->post_redraw();

   //      };

   //   ::file::path path = download("tortoisegit", transferprogressfunction);

   //   information(path);

   //   set_status2(e_install_tortoise_git, "\nInstalling TortoiseGit...\n");

   //   //m_pimpact->set_need_redraw();

   //   //m_pimpact->post_redraw();

   //   ::property_set set;

   //   int iExitCode = -1;
   //
   //   node()->call_sync("msiexec", "/package \"" + path.name() + "\" /quiet /passive", path.folder(), e_display_normal, 2_hour, set, &iExitCode);

   //   ::string strTortoiseGitExit;

   //   strTortoiseGitExit.formatf("TortoiseGit exit code %d", iExitCode);

   //   //m_strTortoiseGitStatus2 += strTortoiseGitExit;

   //   set_status2(e_install_tortoise_git, strTortoiseGitExit);

   //   information(strTortoiseGitExit);

   //}


#endif


#if SMART_GIT

   //bool code_application::defer_install_smart_git(int iTry)
   //{

   //   //set_status1("Downloading TortoiseSVN");

   //   //::file::path path = download("tortoisesvn");

   //   //set_status1("Installing TortoiseSVN");

   //   //::property_set set;

   //   ////call_sync("msiexec.exe", "/i \"" + path + "\" /passive /norestart ADDLOCAL=ALL", path.folder(), ::e_display_default, 10_min, set);
   //   {

   //      int iAttempt = 0;

   //      while (iTry > 0)
   //      {

   //         if (is_installed(e_install_))
   //         {

   //            set_smart_git_status2("");
   //            //m_strSmartGitStatus2.clear();

   //            if (iAttempt == 0)
   //            {

   //               set_smart_git_status("SmartGit is already installed.");

   //            }
   //            else if (iAttempt == 1)
   //            {

   //               set_smart_git_status("SmartGit is now installed.");

   //            }
   //            else if (iAttempt >= 2)
   //            {

   //               ::string str;

   //               str.formatf("SmartGit is installed after multiple attempts (%d).", iAttempt);

   //               set_smart_git_status(str);

   //            }

   //            //m_pimpact->set_need_redraw();

   //            //m_pimpact->post_redraw();

   //            return true;

   //         }

   //         iAttempt++;

   //         ::string str;

   //         str = "SmartGit is not installed!!\n";
   //         str.append_formatf("Attempt no. %d to install\n", iAttempt);

   //         set_smart_git_status(str);
   //         //m_strGitInstallationStatus += "Important options to select: \n";

   //         install_tortoise_git();

   //         task_sleep(500_ms);

   //         iTry--;

   //      }

   //      ::string str2;

   //      str2 = "TortoiseGit couldn't be installed...";

   //      str2.append_formatf("In %d attempts...", iAttempt);

   //      str2 += "You can retry...\n\n";

   //      set_tortoise_git_status2(str2);

   //      return false;

   //   }

   //}

   //void code_application::install_smart_git()
   //{
   //   auto transferprogressfunction = [this](double d, filesize done, filesize total)
   //      {

   //         if (total == 0 || total == (filesize)-1)
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading TortoiseGit (%lld)", done);

   //            set_smart_git_status2(str2);

   //         }
   //         else
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading TortoiseGit %0.1f%% (%lld of %lld)", d * 100.0, done, total);

   //            set_smart_git_status2(str2);

   //         }

   //         //m_pimpact->set_need_redraw();

   //         //m_pimpact->post_redraw();

   //      };
   //   ::file::path path = download("smartgit", transferprogressfunction);

   //}

   //bool code_application::__is_smart_git_installed()
   //{

   //   return false;

   //}

#endif


#if INSTALL_GIT_SCM

   //bool code_application::defer_install_git_scm(int iTry)
   //{

   //   int iAttempt = 0;

   //   while (iTry > 0)
   //   {

   //      if (is_git_scm_installed())
   //      {

   //         set_git_scm_status2("");

   //         if (iAttempt == 0)
   //         {

   //            set_git_scm_status("Git(git-scm) is already installed.");

   //         }
   //         else if (iAttempt == 1)
   //         {

   //            set_git_scm_status("Git(git-scm) is now installed.");

   //         }
   //         else if (iAttempt >= 2)
   //         {

   //            ::string str;
   //            str.formatf("Git(git-scm) is installed after multiple attempts (%d).", iAttempt);

   //            set_git_scm_status(str);

   //         }

   //         //m_pimpact->set_need_redraw();

   //         //m_pimpact->post_redraw();

   //         return true;

   //      }

   //      iAttempt++;

   //      ::string str;
   //
   //      str  = "Git is not installed!!\n";
   //      str.append_formatf("Attempt no. %d to install\n", iAttempt);

   //      set_git_scm_status(str);

   //      //m_strGitInstallationStatus += "Important options to select: \n";

   //      install_git_scm();

   //      task_sleep(500_ms);

   //      iTry--;

   //   }

   //   ::string str2;

   //    str2 = "Git couldn't be installed...";

   //   str2.append_formatf("In %d attempts...", iAttempt);

   //   str2 += "You can retry...\n\n";

   //   set_git_scm_status2(str2);

   //   return false;

   //}


   //void code_application::install_git_scm()
   //{

   //   scoped_restore(m_bInstallingGit);

   //   m_bInstallingGit = true;

   //   ::file::path pathInf = "C:/operating_system/git-scm.inf";

   //   if (!file_system()->exists(pathInf))
   //   {

   //      ::file::path pathUrl = "https://ca2.software/download/windows/git-scm.inf";

   //      ::property_set set;

   //      set["raw_http"] = true;

   //      http().download(pathUrl, pathInf, set);

   //   }

   //   auto transferprogressfunction = [this](double d, filesize done, filesize total)
   //      {

   //         if (total == 0 || total == (filesize)-1)
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading git-scm (%lld)", done);

   //            set_git_scm_status2(str2);

   //         }
   //         else
   //         {

   //            ::string str2;

   //            str2.formatf("Dowloading git-scm %0.1f%% (%lld of %lld)", d * 100.0, done, total);

   //            set_git_scm_status2(str2);

   //         }

   //         //m_pimpact->set_need_redraw();

   //         //m_pimpact->post_redraw();

   //      };

   //   ::file::path path = download("git-scm", transferprogressfunction);

   //   information(path);

   //   ::string str2;

   //   str2 = "\nInstalling git-scm...\n";

   //   set_tortoise_git_status2(str2);

   //   //m_pimpact->set_need_redraw();

   //   //m_pimpact->post_redraw();

   //   int iExitCode = node()->command_system(path + " /verysilent /loadinf=" + pathInf, 2_hour);

   //   ::string strGitScmExit;

   //   strGitScmExit.formatf("git-scm exit code %d", iExitCode);

   //   set_git_scm_status2( strGitScmExit);

   //   information(strGitScmExit);

   //   auto tracefunction = ::std_inline_log();

   //   tracefunction.m_timeTimeout = 5_min;

   //   int iExitCode2 = node()->unix_shell_command("git config --global core.symlinks true", tracefunction);

   //}

#endif





   //::file::path code_application::download(enum_install einstall, transfer_progress_function transferprogressfunction)
   //{

   //   ::file::path pathUrl;

   //   ::string strName;

   //   if (str == "tortoisegit")
   //   {

   //      pathUrl = "https://download.tortoisegit.org/tgit/2.15.0.0/TortoiseGit-2.15.0.0-64bit.msi";

   //   }
   //   else if (str == "git-scm")
   //   {

   //      pathUrl = "https://github.com/git-for-windows/git/releases/download/v2.44.0.windows.1/Git-2.44.0-64-bit.exe";

   //   }
   //   else if (str == "vs_community")
   //   {

   //      strName = "VisualStudioSetup.exe";

   //      pathUrl = "https://c2rsetup.officeapps.live.com/c2r/downloadVS.aspx?sku=community&channel=Release&version=VS2022&source=VSLandingPage";

   //   }
   //   else
   //   {

   //      property_set set;

   //      set["raw_http"] = true;

   //      for (int i = 0; i < 10; i++)
   //      {

   //         pathUrl = http().get("https://ca2.software/code/script/windows/" + str, set);

   //         if (pathUrl.case_insensitive_begins("https://"))
   //         {

   //            break;

   //         }

   //      }

   //   }

   //   if (pathUrl.is_empty())
   //   {

   //      return "";

   //   }

   //   if (strName.is_empty())
   //   {

   //      strName = pathUrl.name();

   //   }

   //   property_set set;

   //   set["raw_http"] = true;

   //   set["transfer_progress_function"] = transferprogressfunction.m_pbase;

   //   ::file::path pathDownloadFolder;

   //   pathDownloadFolder = directory()->download() / "Code!!";

   //   ::file::path path = pathDownloadFolder / strName;

   //   http().download(pathUrl, path, set);

   //   return path;

   //}


   bool code_application::does_need_code_exe_relocation()
   {

#if defined(LINUX)

      return false;

#else

      auto pathModule = file_system()->module();

      if (path_system()->real_path_is_same(pathModule, m_pathCode))
      {

         return false;

      }
      else
      {

         return true;

      }

#endif

   }


//   bool code_application::does_need_code_exe_relocation()
//   {
//
//#if defined(LINUX)
//
//      return false;
//
//#else
//
//      auto pathModule = file_system()->module();
//
//      if (path_system()->real_path_is_same(pathModule, m_pathCode))
//      {
//
//         return false;
//
//      }
//      else
//      {
//
//         return true;
//
//      }
//
//#endif
//
//   }


   void code_application::wait_first_stage()
   {

      while(!m_bFirstStageOk)
      {

         sleep(300_ms);

      }

   }


   bool code_application::defer_first_stage()
   {

      if(m_bFirstStageOk)
      {

         return true;

      }


      if (!defer_relocate_code_exe())
      {

         return false;

      }

      if (!defer_application_build_helper())
      {

         return false;

      }

      if (!defer_initial_ambient_setup())
      {

         return false;

      }

      m_bFirstStageOk = true;

      return true;

   }


   bool code_application::defer_relocate_code_exe()
   {
      
      return true;
      
   }


   bool code_application::_defer_relocate_code_exe()
   {

      auto pathModule = file_system()->module();

      if (does_need_code_exe_relocation())
      {

         // gonna display main window just to give call for action
         // feedback and tell quickly that it is relocating the executable.

         auto pcodeInitialSetup = code(::coding::e_mode_initial_setup);

         pcodeInitialSetup->set_main_status1("Relocating code.exe to \""+m_pathCode+"\"");

         try
         {

            file_system()->copy(m_pathCode, pathModule, true);

            node()->shell_open(m_pathCode, "--previous-location=\"" + pathModule + "\"", m_pathCode.folder());

            class ::time time;

            time.Now();

            while (time.elapsed() < 5_minutes)
            {

               auto pida = node()->module_path_processes_identifiers(m_pathCode);

               if (pida.has_element())
               {

                  auto papp = node()->process_identifier_application(pida.first());

                  if (papp)
                  {

                     auto pmainwindow = createø < ::operating_system::main_window>();

                     pmainwindow->from_application(papp);

                     if (pmainwindow->is_window())
                     {

                        pmainwindow->activate();

                        break;

                     }

                  }

               }

               preempt(300_ms);

            }

         }
         catch (...)
         {

            // could not copy to target location (file in use? already running?)
            // exit silently.

         }

         throw ::exit_exception(this);

         return false;

      }
      else
      {

         //MessageBox(nullptr, NULL, NULL, MB_OK);

         //auto pmessageboxpayload = message_box("code.exe is starting in correct location");

         //psequencer->do_synchronously();

         try
         {

            fork([this]()
               {

                  auto strPreviousLocation = platform()->get_argument_begins_eat("--previous-location=");

                  if (strPreviousLocation.has_character())
                  {

                     strPreviousLocation.trim("\"");

                     if (strPreviousLocation.is_empty())
                     {

                        return;

                     }

                     // todo: check strPreviousLocation executable image
                     // is the same as this executable image.
                     for (int i = 1; i <= 3; i++)
                     {

                        try
                        {

                           if (file_system()->exists(strPreviousLocation)
                              && file_system()->as_memory(strPreviousLocation)
                              == file_system()->as_memory(get_module_path())
                              && file()->length(get_module_path()) > 1_MiB)
                           {


                              preempt(1_s * i);


                              file_system()->erase(strPreviousLocation);


                           }

                        }
                        catch (...)
                        {

                           continue;

                        }

                        break;

                     }

                  };

               });

         }
         catch (...)
         {

         }

         return true;

      }

   }


   bool code_application::is_application_build_helper_ok()
   {

      return file_system()->exists(m_pathApplicationBuildHelper)
         && file()->length(m_pathApplicationBuildHelper) > 100_KiB;

   }


   bool code_application::defer_application_build_helper()
   {

      auto pcodeInitialSetup = code(::coding::e_mode_initial_setup);

      if (is_application_build_helper_ok())
      {

         pcodeInitialSetup->set_main_status1("application_build_helper is ok.");

         return true;

      }
      
      ::string strUrl;

#if defined(LINUX)

      auto psummary = node()->operating_system_summary();

      strUrl.format("https://linux.ca2.store/application_build_helper_{}",
                            psummary->m_strSystemArchitecture);

      // if (psummary->m_strSystem.case_insensitive_equals("ubuntu"))
      // {
      //
      //    if(psummary->m_strSystemBranch.case_insensitive_equals("kde"))
      //    {
      //
      //       strUrl.formatf("https://kubuntu.ca2.store/%s/application_build_helper",
      //                      psummary->m_strSystemRelease.c_str());
      //
      //    }
      //    else if(psummary->m_strSystemBranch.case_insensitive_equals("xfce"))
      //    {
      //
      //       strUrl.formatf("https://xubuntu.ca2.store/%s/application_build_helper",
      //                      psummary->m_strSystemRelease.c_str());
      //
      //    }
      //    else
      //    {
      //
      //       strUrl.formatf("https://ubuntu.ca2.store/%s/application_build_helper",
      //                      psummary->m_strSystemRelease.c_str());
      //
      //    }
      //
      // }
      // else if (psummary->m_strSystem.case_insensitive_equals("linuxmint"))
      // {
      //
      //    if(psummary->m_strSystemRelease.case_insensitive_equals("20"))
      //    {
      //
      //       strUrl.formatf("https://ubuntu.ca2.store/%s/application_build_helper",
      //                      "20.04");
      //
      //    }
      //    else if(psummary->m_strSystemBranch.case_insensitive_equals("xfce"))
      //    {
      //
      //       strUrl.formatf("https://ubuntu.ca2.store/%s/application_build_helper",
      //                      "22.04");
      //
      //    }
      //    else
      //    {
      //
      //       strUrl.formatf("https://ubuntu.ca2.store/%s/application_build_helper",
      //                      "24.04");
      //
      //    }
      //
      // }
      // else if (psummary->m_strSystemBranch.has_character())
      // {
      //
      //    strUrl.formatf("https://%s.ca2.store/%s/%s/application_build_helper",
      //       psummary->m_strSystem.c_str(),
      //       psummary->m_strSystemBranch.c_str(),
      //       psummary->m_strSystemRelease.c_str());
      //
      // }
      // else
      // {
      //
      //    strUrl.formatf("https://%s.ca2.store/%s/application_build_helper",
      //       psummary->m_strSystem.c_str(),
      //       psummary->m_strSystemRelease.c_str());
      //
      // }

#elif defined(WINDOWS_DESKTOP)

      strUrl = "https://windows.ca2.store/application_build_helper.exe";

#elif defined(FREEBSD)


      auto psummary = node()->operating_system_summary();

      strUrl.formatf("https://freebsd.ca2.store/%s/application_build_helper",
                     psummary->m_strSystemRelease.c_str());


      ::file::path pathUrl = strUrl;
#elif defined(MACOS)
      
      
      strUrl = "https://macos.ca2.store/application_build_helper";

#endif
      ::file::path pathUrl = strUrl;


      int iAttemptCount = 5;

      for (int i = 0; i < iAttemptCount; i++)
      {

         ::property_set set;

         set["raw_http"] = true;

         set["disable_common_name_cert_check"] = true;

         ::string str;

         if (i == 0)
         {

#if defined(WINDOWS_DESKTOP)

            str.formatf("dOWNloading application_build_helper.exe (%s)", pathUrl.c_str());

#else

            str.formatf("Downloading application_build_helper (%s)", pathUrl.c_str());

#endif

         }
         else
         {

#if defined(WINDOWS_DESKTOP)

            str.formatf("Retrying to download application_build_helper.exe (Attempt %d) (%s)", i + 1, pathUrl.c_str());

#else

            str.formatf("Retrying to download application_build_helper (Attempt %d) (%s)", i + 1, pathUrl.c_str());

#endif

         }

         pcodeInitialSetup->set_main_status1(str);

         http()->download(m_pathApplicationBuildHelper, pathUrl, set);

         if (is_application_build_helper_ok())
         {

            pcodeInitialSetup->set_main_status1("Finished downloading application_build_helper.");

            return true;

         }

         int iWaitSeconds = 2 * i;

         while (iWaitSeconds > 0)
         {

            ::string str;

#if defined(WINDOWS_DESKTOP)

            str.formatf("Failed to download application_build_helper.exe, retrying in %d", iWaitSeconds);

#else

            str.formatf("Failed to download application_build_helper, retrying in %d (%s)", iWaitSeconds, pathUrl.c_str());

#endif

            pcodeInitialSetup->set_main_status1(str);

            preempt(1_s);

            iWaitSeconds--;

         }

      }

      ::string str;

#if defined(WINDOWS_DESKTOP)

      str.formatf("Failed to download application_build_helper.exe. Stopping after %d attempts.", iAttemptCount);

#else

      str.formatf("Failed to download application_build_helper.exe. Stopping after %d attempts.", iAttemptCount);

#endif

      pcodeInitialSetup->set_main_status1(str);

      return false;

   }


   bool code_application::defer_initial_ambient_setup()
   {

#if defined(WINDOWS_DESKTOP)

      // beta uf8 currently needed for development at windows...
      // ca2 source contains unicode characters that prevents
      // code to be compiled without this enabled...
      if (!node()->_has_beta_use_unicode_utf8() || !node()->_is_coder_mode_enabled())
      {

         auto pcodeInitialSetup = this->code(e_mode_initial_setup);

         if (pcodeInitialSetup)
         {

            auto pimpact = pcodeInitialSetup->m_pimpact;

            if (pimpact)
            {

               auto pstill = pimpact->m_pstillMainStatus2;

               pstill->set_window_text("Computer needs to be restarted due change in UTF-8 system settings.");

               pimpact->m_bNeedPerformLayout = true;

               pimpact->set_need_layout();

               pimpact->set_need_redraw();

               pimpact->post_redraw();

            }


         }

         //m_pimpact->parent_frame()->hide();

         //application_build_helper_initial_ambient_setup(false);

         //node()->set_user_run_once("Code!!", m_pathCode);

         node()->root_execute_sync("C:\\operating_system\\bin\\application_build_helper.exe", "--root-initial-ambient-setup");

         //         node()->reboot();

         //}
         //else
         //{

         //   m_strFirstStageStatus = "You"

         //}

         //set_finish();

         //   });

         m_strMayNeedRestartStatus = "Computer needs to be restarted due change in UTF-8 system settings.";

         //psequencer->do_synchronously();

         //return true;

      }

      if (!node()->_is_code_exe_user_path_environment_variable_ok())
      {

         auto estatus = application_build_helper_initial_ambient_setup(true);

         if (!estatus.ok())
         {

            return false;

         }

      }

#endif

      return true;

   }





   // void code_application::on_installed(::coding::enum_install einstall, bool bJustInstalled)
   // {
   //
   //    _synchronous_lock synchronouslock(this->synchronization());
   //
   //    auto pinstall = code()->install_map()[einstall];
   //
   //    // if (pinstall->m_pinstallimpactinterface->is_selected())
   //    // {
   //    //
   //    //    pinstall->m_pinstallimpactinterface->unselect();
   //    //
   //    // }
   //
   //    switch (einstall)
   //    {
   //    case ::coding::e_install_browser:
   //       if(bJustInstalled)
   //       {
   //          if (m_strBrowser == "chrome")
   //          {
   //
   //             node()->detached_command("google-chrome", {});
   //
   //          }
   //          else if (m_strBrowser == "opera")
   //          {
   //
   //
   //          }
   //
   //
   //
   //       }
   //       break;
   //    case ::coding::e_install_visual_studio_code:
   //       if(bJustInstalled)
   //       {
   //
   //          node()->detached_command("code", {});
   //
   //       }
   //       break;
   //    default:
   //       break;
   //
   //    }
   //
   //    defer_release_install();
   //
   // }


   //
   //
   // ::e_status code_application::application_build_helper_initial_ambient_setup(bool bSystemNotifyIfNeeded)
   // {
   //
   //    auto pcodeInitialSetup = code(::coding::e_mode_initial_setup);
   //
   //    pcodeInitialSetup->m_strMainStatus = "Downloading application_build_helper...";
   //
   //    post_impact_redraw();
   //
   //    pcodeInitialSetup->m_strMainStatus = "Running application_build_helper --initial-ambient-setup ...";
   //
   //    post_impact_redraw();
   //
   //    ::string strOptions;
   //
   //    if (!bSystemNotifyIfNeeded)
   //    {
   //
   //       strOptions = " --no-system-notify-even-if-needed";
   //
   //    }
   //
   //    node()->command_system(m_pathApplicationBuildHelper + " --initial-ambient-setup" + strOptions, 15_min);
   //
   //    preempt(2_s);
   //
   //    pcodeInitialSetup->m_strMainStatus = "Setting up coding ambient...";
   //
   //    return ::success;
   //
   // }





   void code_application::start_debugging_project()
   {

      //m_pcodetabimpact->parent_frame()->display(e_display_none);

      //m_pcodetabimpact->parent_frame()->set_need_redraw();

      //m_pcodetabimpact->parent_frame()->post_redraw();

      task_sleep(8_s);

      ::file::path path;

#ifdef WINDOWS

      path = "C:/simple/solution-windows/simple.sln";

#else

      path = directory_system()->home() / "simple/solution-" OPERATING_SYSTEM_NAME "/simple.sln";

#endif

      //path = directory_system()->home() / "simple/solution-" OPERATING_SYSTEM_NAME "/simple.sln";

      for (int iTry = 0; iTry < 6; iTry++)
      {

         preempt(3_s);

         if (iTry % 2 == 0)
         {

            auto pmessageboxpayload = message_box("There maybe a prompt for which program to open simple.sln.\n\n\"Visual Studio Version selector\" is good default choice as it generally selects Visual Studio of same version as the one used to edit project/solution file being opened.", "Prompt for selecting code_application for opening simple.sln", ::user::e_message_box_ok);

            post(pmessageboxpayload);

            preempt(2_s);

         }

         try
         {

            node()->file_open(path);

            break;

         }
         catch (...)
         {


         }

      }

      //auto p = message_box("Git is installed", "Git is installed", e_message_box_ok);

      //p->do_synchronously();


      task_sleep(10_s);

#if defined(WINDOWS_DESKTOP)

      ::coding::visual_studio_select_project(system(), "ca2project://source/simple/app-simple/drawing");

      task_sleep(2_s);

      ::coding::visual_studio_select_configuration_platform(system(), "Debug", "x64");

#endif

      task_sleep(5_s);

      set_finish();


   }


   //#endif // WINDOWS_DESKTOP


   //void code_application::release_source()
   //{

   //   m_cPendingSource--;

   //   if (m_cPendingSource == 1)
   //   {

   //      set_status1("1 Working Copy to Download...");

   //   }
   //   else if (m_cPendingSource <= 0)
   //   {

   //      m_bSourceOk = true;

   //   }
   //   else
   //   {

   //      set_status1(as_string((int)(long long)m_cPendingSource) + " Working Copies to Download...");

   //   }

   //}


   // void code_application::defer_release_install()
   // {
   //
   //    //m_pimpact->release_install("C:/simple/solution-windows/simple.sln");
   //
   //    //preempt(5_s);
   //
   //    bool bInstalling = is_installing();
   //
   //    if (m_bLastDeferReleaseInstallInstalling)
   //    {
   //
   //       if (!bInstalling)
   //       {
   //
   //          _synchronous_lock synchronouslock(this->synchronization());
   //
   //          auto & installmap = code()->install_map();
   //
   //          // for (auto& pinstall : installmap.payloads())
   //          // {
   //          //
   //          //    try
   //          //    {
   //          //
   //          //       if (pinstall)
   //          //       {
   //          //
   //          //          if (pinstall->m_pinstallimpactinterface)
   //          //          {
   //          //             pinstall->m_pinstallimpactinterface->enable_selection();
   //          //          }
   //          //
   //          //       }
   //          //
   //          //
   //          //
   //          //    }
   //          //    catch (...)
   //          //    {
   //          //
   //          //
   //          //    }
   //          //
   //          // }
   //
   //       }
   //
   //    }
   //    else
   //    {
   //
   //       if (bInstalling)
   //       {
   //
   //          _synchronous_lock synchronouslock(this->synchronization());
   //
   //          auto & installmap = code()->install_map();
   //
   //          // for (auto& pinstall : installmap.payloads())
   //          // {
   //          //
   //          //    try
   //          //    {
   //          //
   //          //       if (pinstall)
   //          //       {
   //          //
   //          //          if (pinstall->m_pinstallimpactinterface)
   //          //          {
   //          //
   //          //             pinstall->m_pinstallimpactinterface->disable_selection();
   //          //
   //          //          }
   //          //
   //          //       }
   //          //
   //          //    }
   //          //    catch (...)
   //          //    {
   //          //
   //          //
   //          //    }
   //          //
   //          // }
   //
   //       }
   //
   //    }
   //
   //    m_bLastDeferReleaseInstallInstalling = bInstalling;
   //
   //    auto pcode = code(get_code_mode());
   //
   //    // if(pcode && pcode->m_pimpact)
   //    // {
   //    //
   //    //    pcode->m_pimpact->defer_enable_release_install();
   //    //
   //    // }
   //
   //    bool bGitScmOk = is_installed(::coding::e_install_git_scm, true);
   //
   //    //bool bGitScmScheduled = is_install_selected(::coding::e_install_git_scm);
   //
   //    _synchronous_lock synchronouslock(this->synchronization());
   //
   //    auto & installmap = code()->install_map();
   //
   //    auto pitemToolOs = installmap[::coding::e_install_tool_os];
   //
   //    // if (pitemToolOs)
   //    // {
   //    //
   //    //    if (pitemToolOs->m_pinstallimpactinterface)
   //    //    {
   //    //
   //    //       pitemToolOs->m_pinstallimpactinterface->enable_window(bGitScmOk || bGitScmScheduled);
   //    //
   //    //    }
   //    //
   //    // }
   //
   //    auto pitemAppSimple = installmap[::coding::e_install_repositories];
   //
   //    // if (pitemAppSimple && pitemAppSimple->m_pinstallimpactinterface)
   //    // {
   //    //
   //    //    pitemAppSimple->m_pinstallimpactinterface->enable_window(bGitScmOk || bGitScmScheduled);
   //    //
   //    // }
   //    //
   //    // if (pcode && pcode->m_pimpact)
   //    // {
   //    //
   //    //    pcode->m_pimpact->update_start_button();
   //    //
   //    // }
   //
   //
   //    //      m_pimpact->parent_frame()->display(e_display_none);
   //    //
   //    //      m_pimpact->parent_frame()->set_need_redraw();
   //    //
   //    //      m_pimpact->parent_frame()->post_redraw();
   //    //
   //    //      task_sleep(8_s);
   //    //
   //    //      ::file::path path;
   //    //
   //    //#ifdef WINDOWS
   //    //
   //    //      path = "C:/simple/solution-windows/simple.sln";
   //    //
   //    //#else
   //    //
   //    //      path = directory_system()->home() / "simple/solution-" OPERATING_SYSTEM_NAME "/simple.sln";
   //    //
   //    //#endif
   //    //
   //    //      //path = directory_system()->home() / "simple/solution-" OPERATING_SYSTEM_NAME "/simple.sln";
   //    //
   //    //      for(int iTry = 0; iTry < 6; iTry++)
   //    //      {
   //    //
   //    //         preempt(3_s);
   //    //
   //    //         if (iTry % 2 == 0)
   //    //         {
   //    //
   //    //            auto p = message_box("There maybe a prompt for which program to open simple.sln.\n\n\"Visual Studio Version selector\" is good default choice as it generally selects Visual Studio of same version as the one used to edit project/solution file being opened.", "Prompt for selecting application for opening simple.sln", e_message_box_ok);
   //    //
   //    //            p->do_synchronously();
   //    //
   //    //            preempt(2_s);
   //    //
   //    //         }
   //    //
   //    //         try
   //    //         {
   //    //
   //    //            node()->file_open(path);
   //    //
   //    //            break;
   //    //
   //    //         }
   //    //         catch (...)
   //    //         {
   //    //
   //    //
   //    //         }
   //    //
   //    //      }
   //    //
   //    //      //auto p = message_box("Git is installed", "Git is installed", e_message_box_ok);
   //    //
   //    ////p->do_synchronously();
   //    //
   //    //
   //    //      class ::time tickStart;
   //    //
   //    //      tickStart.Now();
   //    //
   //    //      while (tickStart.elapsed() < 3_min)
   //    //      {
   //    //
   //    //         if (has_visible_top_level_window_named_simple__microsoft_visual_studio())
   //    //         {
   //    //
   //    //            break;
   //    //
   //    //         }
   //    //
   //    //      }
   //    //
   //    //      task_sleep(10_s);
   //    //
   //    //      visual_studio_select_project(acmesystem(), "ca2project://source/simple/app-simple/drawing");
   //    //
   //    //      task_sleep(2_s);
   //    //
   //    //      visual_studio_select_configuration_platform(acmesystem(), "Debug", "x64");
   //    //
   //    //      task_sleep(5_s);
   //    //
   //    //      set_finish();
   //
   // }


   // bool code_application::calculate_enable(::coding::enum_install einstall)
   // {
   //
   //    auto & installmap = code()->install_map();
   //
   //    auto pinstall = installmap[einstall];
   //
   //    if(!pinstall) return true;
   //
   //    auto & einstallaDependency = code()->m_einstallaDependency[einstall];
   //
   //    if(einstallaDependency.is_empty())
   //       return true;
   //
   //    for(auto einstallDependency : einstallaDependency)
   //    {
   //
   //       if(!is_installed(einstallDependency, false) && !is_install_selected(einstallDependency))
   //       {
   //
   //          return false;
   //
   //       }
   //
   //    }
   //
   //    return true;
   //
   // }



   //void application::install_on_checkbox(::user::check* pcheck)
   void code_application::code_on_change_selection()
   {
//
//
//       //bool bGitScmOk = is_installed(::coding::e_install_git_scm, true);
//
//       //bool bGitScmScheduled = is_install_selected(::coding::e_install_git_scm);
//
// //      _synchronous_lock synchronouslock(this->synchronization());
//       //
//       // auto & installmap = this->install_map();
//       //
//       // auto pitemToolOs = installmap[::coding::e_install_tool_os];
//       //
//       // auto pitemAppSimple = installmap[::coding::e_install_app_simple];
//       //
//       // if (pitemAppSimple->m_pinstallimpactinterface->has_check(pcheck))
//       // {
//       //
//       //    if (pitemAppSimple->m_pinstallimpactinterface->is_selected())
//       //    {
//       //
//       //       if (!__is_installed(::coding::e_install_tool_os, false))
//       //       {
//       //
//       //          if (pitemToolOs->m_pinstallimpactinterface->has_check())
//       //          {
//       //
//       //             if (pitemToolOs->m_pinstallimpactinterface->is_selected())
//       //             {
//       //
//       //                // ok;
//       //
//       //             }
//       //             else
//       //             {
//       //
//       //                pitemToolOs->m_pinstallimpactinterface->select();
//       //
//       //             }
//       //
//       //          }
//       //          else
//       //          {
//       //
//       //             pitemAppSimple->m_pinstallimpactinterface->unselect();
//       //
//       //             //m_pimpact->set_need_redraw();
//       //
//       //             //m_pimpact->post_redraw();
//       //
//       //          }
//       //
//       //       }
//       //
//       //    }
//       //
//       // }
//       // else if (pitemToolOs->m_pinstallimpactinterface->has_check(pcheck))
//       // {
//       //
//       //    if (pitemToolOs->m_pinstallimpactinterface->is_selected()
//       //       || __is_installed(::coding::e_install_tool_os, false))
//       //    {
//       //
//       //       // ok
//       //
//       //    }
//       //    else
//       //    {
//       //
//       //       if (pitemAppSimple->m_pinstallimpactinterface->has_check())
//       //       {
//       //
//       //          if (pitemAppSimple->m_pinstallimpactinterface->is_selected())
//       //          {
//       //
//       //             pitemAppSimple->m_pinstallimpactinterface->unselect();
//       //
//       //          }
//       //
//       //          //m_pimpact->set_need_redraw();
//       //
//       //          //m_pimpact->post_redraw();
//       //
//       //       }
//       //
//       //    }
//       //
//       // }
//
//       auto & installmap = code()->m_installmap;
//
//       for(auto pinstall : installmap.payloads())
//       {
//
//          if(pinstall && pinstall->m_pinstallimpactinterface)
//          {
//
//             auto bEnable = calculate_enable(pinstall->m_einstall);
//
//             if(bEnable)
//             {
//
//                pinstall->m_pinstallimpactinterface->enable_selection();
//
//             }
//             else
//             {
//
//                pinstall->m_pinstallimpactinterface->disable_selection();
//
//             }
//
//          }
//
//
//       }
//
//       defer_release_install();

   }


   string code_application::preferred_experience()
   {

      return "tranquillum";

   }




   // bool code_application::is_installing()
   // {
   //
   //    if (can_start_installing())
   //    {
   //
   //       if (m_bStartingInstallation2)
   //       {
   //
   //          return true;
   //
   //       }
   //
   //    }
   //
   //    _synchronous_lock synchronouslock(this->synchronization());
   //
   //    auto & installmap = code()->install_map();
   //
   //    for (auto & pinstall : installmap.payloads())
   //    {
   //
   //       //auto p = pinstall.m_p;
   //
   //       if (pinstall && pinstall->m_bInstalling)
   //       {
   //
   //          return true;
   //
   //       }
   //
   //    }
   //
   //    return false;
   //
   // }


   // bool code_application::is_install_selected(::coding::enum_install einstall)
   // {
   //
   //    _synchronous_lock synchronouslock(this->synchronization());
   //
   //    auto & installmap = code()->install_map();
   //
   //    auto ppair = installmap.find(einstall);
   //
   //    if(::is_set(ppair))
   //    {
   //       auto pinstall = ppair->m_element2;
   //       if (pinstall
   //          && pinstall->m_pinstallimpactinterface
   //          && pinstall->m_pinstallimpactinterface->has_check() && pinstall->m_pinstallimpactinterface->is_selected())
   //       {
   //
   //          return true;
   //
   //       }
   //    }
   //
   //    return false;
   //
   // }


   // bool code_application::can_start_installing()
   // {
   //
   //    if (is_install_selected(::coding::e_install_visual_studio))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_jetbrains_clion))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_jetbrains_toolbox))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_browser))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_cloud_data_provider))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_visual_studio_code))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_git_scm))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_patch_shell))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_deps))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_git_credential_manager))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_tortoise_git))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_smart_git))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_install_selected(::coding::e_install_setup_folders))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    if (is_installed(::coding::e_install_git_scm, true))
   //    {
   //
   //       if (is_install_selected(::coding::e_install_tool_os))
   //       {
   //
   //          return true;
   //
   //       }
   //
   //       if (is_install_selected(::coding::e_install_repositories))
   //       {
   //
   //          return true;
   //
   //       }
   //
   //    }
   //
   //    return false;
   //
   // }


   //void code_application::set_status1(string strStatus)
   //{

   //   m_strSourceStatus = strStatus;

   //   if (m_pimpact)
   //   {

   //      m_pimpact->set_need_redraw();

   //      m_pimpact->post_redraw();

   //   }

   //}


   //void code_application::set_status2(string strStatus)
   //{

   //   m_strStatus2 = strStatus;

   //   if (m_pimpact)
   //   {

   //      m_pimpact->set_need_redraw();

   //      m_pimpact->post_redraw();

   //   }

   //}


   //bool code_application::is_installed_smart_svn()
   //{

   //   if (ASSUME_NOTHING_INSTALLED)
   //   {

   //      return false;

   //   }

   //   return false;

   //}


   // void code_application::post_impact_redraw()
   // {
   //
   //    if (::is_set(m_pcodetabimpact))
   //    {
   //
   //       m_pcodetabimpact->set_need_redraw();
   //
   //       m_pcodetabimpact->post_redraw();
   //
   //    }
   //
   // }


#ifdef LINUX


//   void code_application::start_debugging_project()
//   {
//
//
//   }


#endif


   ::coding::code * code_application::code()
   {

      return code(get_code_mode());

   }


   ::coding::code * code_application::code(const ::coding::e_mode & emode)
   {

      auto & pcode = m_codemap[emode];

      if(!pcode)
      {

         construct_newø(pcode);

         pcode->m_emode = emode;

      }

      return pcode;

   }


   // ::pointer < ::coding::impact > & code_application::impact(const ::atom & atom)
   // {
   //
   //    return this->code(atom)->m_pimpact;
   //
   // }



   //void code_application::set_visual_studio_status(const ::scoped_string& scopedstr)
   //{

   //   _m_strGraphicalIdeStatus = scopedstr;

   //   //m_pimpact->post_redraw();
   //   if (m_pimpact->m_pstillVisualStudioRemark)
   //      m_pimpact->m_pstillVisualStudioRemark->set_window_text(_m_strGraphicalIdeStatus);
   //   if (m_pimpact->m_pstillVisualStudioStatus)
   //      m_pimpact->m_pstillVisualStudioStatus->set_window_text(_m_strGraphicalIdeStatus2);

   //}


   //void code_application::set_visual_studio_status2(const ::scoped_string& scopedstr)
   //{

   //   _m_strGraphicalIdeStatus2 = scopedstr;

   //   //m_pimpact->post_redraw();
   //   if (m_pimpact->m_pstillVisualStudioRemark)
   //      m_pimpact->m_pstillVisualStudioRemark->set_window_text(_m_strGraphicalIdeStatus);
   //   if (m_pimpact->m_pstillVisualStudioStatus)
   //      m_pimpact->m_pstillVisualStudioStatus->set_window_text(_m_strGraphicalIdeStatus2);

   //}


   //void code_application::set_git_scm_status(const ::scoped_string& scopedstr)
   //{

   //   _m_strGitScmStatus = scopedstr;

   //   //m_pimpact->post_redraw();

   //   if (m_pimpact->m_pstillGitScmRemark)
   //      m_pimpact->m_pstillGitScmRemark->set_window_text(_m_strGitScmStatus);
   //   if (m_pimpact->m_pstillGitScmStatus)
   //      m_pimpact->m_pstillGitScmStatus->set_window_text(_m_strGitScmStatus2);


   //}


   //void code_application::set_git_scm_status2(const ::scoped_string& scopedstr)
   //{

   //   _m_strGitScmStatus2 = scopedstr;

   //   //m_pimpact->post_redraw();
   //   if (m_pimpact->m_pstillGitScmRemark)
   //      m_pimpact->m_pstillGitScmRemark->set_window_text(_m_strGitScmStatus);
   //   if (m_pimpact->m_pstillGitScmStatus)
   //      m_pimpact->m_pstillGitScmStatus->set_window_text(_m_strGitScmStatus2);

   //}


   //void code_application::set_tortoise_git_status(const ::scoped_string& scopedstr)
   //{
   //   _m_strTortoiseGitStatus2 = scopedstr;

   //   //m_pimpact->post_redraw();
   //   if (m_pimpact->m_pstillTortoiseGitRemark)
   //      m_pimpact->m_pstillTortoiseGitRemark->set_window_text(_m_strTortoiseGitStatus);
   //   if (m_pimpact->m_pstillTortoiseGitStatus)
   //      m_pimpact->m_pstillTortoiseGitStatus->set_window_text(_m_strTortoiseGitStatus2);

   //}


   //void code_application::set_tortoise_git_status2(const ::scoped_string& scopedstr)
   //{
   //   _m_strTortoiseGitStatus2 = scopedstr;

   //   //m_pimpact->post_redraw();
   //   if (m_pimpact->m_pstillTortoiseGitRemark)
   //      m_pimpact->m_pstillTortoiseGitRemark->set_window_text(_m_strTortoiseGitStatus);
   //   if (m_pimpact->m_pstillTortoiseGitStatus)
   //      m_pimpact->m_pstillTortoiseGitStatus->set_window_text(_m_strTortoiseGitStatus2);

   //}


   //void code_application::set_smart_git_status(const ::scoped_string& scopedstr)
   //{
   //   _m_strSmartGitStatus = scopedstr;

   //   if (m_pimpact->m_pstillSmartGitRemark)
   //      m_pimpact->m_pstillSmartGitRemark->set_window_text(_m_strSmartGitStatus);
   //   if (m_pimpact->m_pstillSmartGitStatus)
   //      m_pimpact->m_pstillSmartGitStatus->set_window_text(_m_strSmartGitStatus2);


   //}


   //void code_application::set_smart_git_status2(const ::scoped_string& scopedstr)
   //{
   //   _m_strSmartGitStatus2 = scopedstr;

   //   //m_pimpact->post_redraw();
   //   if (m_pimpact->m_pstillSmartGitRemark)
   //      m_pimpact->m_pstillSmartGitRemark->set_window_text(_m_strSmartGitStatus);
   //   if (m_pimpact->m_pstillSmartGitStatus)
   //      m_pimpact->m_pstillSmartGitStatus->set_window_text(_m_strSmartGitStatus2);


   //}
   //void code_application::set_status(enum_install einstall, const ::scoped_string& scopedstr)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   auto pinstall = m_installmap[einstall];

   //   if (!pinstall)
   //   {

   //      return;

   //   }

   //   pinstall->m_strStatus2 = scopedstr;

   //   pinstall->on_update_status();


   //}


   //void code_application::set_status2(enum_install einstall, const ::scoped_string& scopedstr)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   auto pinstall = m_installmap[einstall];

   //   if (!pinstall)
   //   {

   //      return;

   //   }

   //   pinstall->m_strStatus2 = scopedstr;

   //   pinstall->on_update_status();


   //}


   //void code_application::append_status2(enum_install einstall, const ::scoped_string& scopedstr)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   auto pinstall = m_installmap[einstall];

   //   if (!pinstall)
   //   {

   //      return;

   //   }

   //   pinstall->m_strStatus2 += scopedstr;

   //   pinstall->on_update_status();

   //}


   //bool code_application::is_installed(enum_install einstall, bool bMayAssumeNotInstalled)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   auto pinstall = m_installmap[einstall];

   //   if (!pinstall)
   //   {

   //      return false;

   //   }

   //   return pinstall->is_installed(bMayAssumeNotInstalled);

   //}



   //::string code_application::get_name(enum_install einstall)
   //{

   //   switch (einstall)
   //   {

   //   case  e_install_visual_studio:
   //      return "visual_studio";
   //   case     e_install_git_scm:
   //      return "git_scm";
   //   case     e_install_tortoise_git:
   //      return "tortoise_git";
   //   case     e_install_smart_git:
   //      return "smart_git";
   //   case     e_install_tool_os:
   //      return "tool_windows";
   //   case     e_install_app_simple:
   //      return "app_simple";
   //   default:
   //      throw ::exception(error_failed);

   //   }

   //}



   //::string code_application::get_title(enum_install einstall)
   //{

   //   switch (einstall)
   //   {

   //   case  e_install_visual_studio:
   //      return "Visual Studio";
   //   case     e_install_git_scm:
   //      return "git";
   //   case     e_install_tortoise_git:
   //      return "TortoiseGit";
   //   case     e_install_smart_git:
   //      return "SmartGit";
   //   case     e_install_tool_os:
   //      return "tool-windows";
   //   case     e_install_app_simple:
   //      return "app-simple source";
   //   default:
   //      throw ::exception(error_failed);

   //   }

   //}


   //::string code_application::get_remark(enum_install einstall)
   //{

   //   switch (einstall)
   //   {

   //   case  e_install_visual_studio:
   //      return "Required for opening and build ca2 solution files";
   //   case     e_install_git_scm:
   //      return "Required for downloading and managing source.";
   //   case     e_install_tortoise_git:
   //      return "Recommended for File Explorer Right Click[Context] Menu and Icon Overlay.";
   //   case     e_install_smart_git:
   //      return"Recommended IDE for Git Source Control.";
   //   case     e_install_tool_os:
   //      return "Required for using ca2";
   //   case     e_install_app_simple:
   //      return "Good repository to start with...";
   //   default:
   //      throw ::exception(error_failed);

   //   }

   //}


   //void code_application::serialize_download(const procedure& procedure, const class ::time& timeOut)
   //{

   //   auto pevent = create_newø < manual_reset_happening >();

   //   {

   //      _synchronous_lock synchronouscock(this->synchronization());

   //      m_procedureaDownloads.add([procedure, pevent]()
   //         {
   //            procedure();

   //            pevent->set_happening();
   //         });

   //   }

   //   defer_run_downloads();

   //   pevent->_wait(timeTimeout);

   //}

   //void code_application::serialize_system_install(const procedure& procedure, const class ::time & timeTimeout)
   //{

   //   auto pevent = create_newø < manual_reset_happening >();

   //   {

   //      _synchronous_lock synchronouscock(this->synchronization());

   //      m_procedureaSystemInstalls.add([procedure, pevent]()
   //         {
   //            procedure();

   //               pevent->set_happening();
   //         });

   //   }

   //   defer_run_system_installs();

   //   pevent->_wait(timeTimeout);

   //}


   //void code_application::defer_run_downloads()
   //{

   //   ::procedure procedure;


   //   {

   //      _synchronous_lock synchronouscock(this->synchronization());

   //      if (m_procedureaDownloads.is_empty())
   //      {

   //         return;

   //      }

   //      if (!m_ptaskDownloads)
   //      {

   //         m_ptaskDownloads = fork([this]()
   //            {

   //               _synchronous_lock synchronouslock(this->synchronization());

   //               while (m_procedureaDownloads.has_element())
   //               {

   //                  auto procedure = m_procedureaDownloads.pick_first();

   //                  synchronouslock.unlock();

   //                  try
   //                  {

   //                     procedure();

   //                  }
   //                  catch (...)
   //                  {


   //                  }

   //                  synchronouslock._lock();

   //               }

   //               m_ptaskDownloads.release();

   //            });

   //      }

   //   }

   //}

   //void code_application::defer_run_system_installs()
   //{

   //   ::procedure procedure;


   //   {

   //      _synchronous_lock synchronouscock(this->synchronization());

   //      if (m_procedureaSystemInstalls.is_empty())
   //      {

   //         return;

   //      }

   //      if (!m_ptaskWindowsInstalls)
   //      {

   //         m_ptaskWindowsInstalls = fork([this]()
   //            {

   //               _synchronous_lock synchronouslock(this->synchronization());

   //               while (m_procedureaSystemInstalls.has_element())
   //               {

   //                  auto procedure = m_procedureaSystemInstalls.pick_first();

   //                  synchronouslock.unlock();

   //                  try
   //                  {

   //                     procedure();

   //                  }
   //                  catch (...)
   //                  {


   //                  }

   //                  synchronouslock._lock();

   //               }

   //               m_ptaskWindowsInstalls.release();

   //            });

   //      }

   //   }

   //}


   void code_application::update_debug_project_enable()
   {

      //auto bEnable = get_debug_project_enable();

      //m_pbuttonDebugProject->enable_window(bEnable);

   }

   bool code_application::get_debug_project_enable()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto & installmap = code()->install_map();

      auto ppair = installmap.find(::coding::e_install_visual_studio);

      if(::is_set(ppair))
      {
         auto pinstall = ppair->m_element2;

         return pinstall->get_debug_project_enabled();
      }

      return false;

   }


} // namespace coding


//
//extern "C"
//::acme::library * integration_code_get_new_library()
//{
//
//   return memory_new ::apex::single_application_library < ::coding::code_application >("app-core/integration_code");
//
//}


//aura_app aura_integration_code("app-core/integration_code", &integration_code_get_new_library);
//
//
//void code_debugging()
//{
//
//   const char* pszFree;
//
//   {
//
//      string strOh = "Oh!! Life!!";
//
//      pszFree = strOh;
//
//      string strXX;
//
//      strXX = strOh + "123" + as_string(15.59) + "%";
//
//      information(strXX);
//
//   }
//
//   information(pszFree);
//
//}


