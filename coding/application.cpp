#include "framework.h"
#include "application.h"

#include <ranges>

#include "code.h"
// #include "document.h"
// #include "frame.h"
// #include "group_machine_box.h"
// #include "group_netnode.h"
// #include "group_operating_system.h"
// #include "main_frame.h"
//#include "impact.h"
#include "install.h"
//#include "log_impact.h"
//#include "summary.h"
//#include "tab_impact.h"
//#include "task_group.h"
//#include "coding.h"
//#include "install_impact_interface.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/http.h"
#include "acme/platform/node.h"
#include "acme/platform/scoped_restore.h"
//#include "apex/database/stream.h"
//#include "apex/filesystem/fs/folder_sync.h"
//#include "berg/user/user/single_document_template.h"
//#include "berg/user/simple/tab_document.h"
#include "dropbox/_.h"
#include "dropbox/dropbox.h"

//void coding_factory(::factory::factory * pfactory);
#define TEST_DATA_LOCAL 1
bool debian_is_package_installed(const ::scoped_string & scopedstrPackageName);
::string_array_base debian_not_installed_packages(const ::string_array_base & straPackages);



__IMPLEMENT_APPLICATION_RELEASE_TIME(coding);


namespace coding
{


   application::application()//:
      // m_propertyCloudDataProvider(this, "cloud_data_provider"),
      // m_propertyCloudDataProviderTitle(this, "cloud_data_provider_title"),
      // m_propertyBrowser(this, "browser"),
      // m_propertyBrowserTitle(this, "browser_title"),
      // m_propertyRepository(this, "repository"),
      // m_propertyRepositoryTitle(this, "repository_title"),
      // m_propertyRepositoryDescription(this, "repository_description")
   {
      m_bFirstFolderSetupDetection = true;

      m_bWinRT = false;
      //m_eapplication = e_application_none;

      m_bJustInstalledDropbox = false;
      m_bJustCreatedDropboxFolder = false;

      m_strBrowser = "chrome";

#if INTEGRATION_INTEGRATION_HAS_AUDIO

      m_bAudio = true;

      scoped_restore(m_bAudio);

#endif

      //      m_ptemplateIntegrationMain = nullptr;
      //
      //      m_ptemplateIntegrationImpact = nullptr;

      m_strAppId = "integration/integration";

      m_strAppName = "integration/integration";

      m_strBaseSupportId = "integration/integration";

      m_eexclusiveinstance = e_exclusive_instance_global;

      m_bLicense = false;

      //m_ptabimpact = nullptr;

      m_bEnableAutoStartOption = true;

      m_bStartingInstallation2 = false;


   }


   application::~application()
   {

   }


   void application::micro_preempt(const char * pszMessage)
   {

      print_line(pszMessage);
      preempt(200_ms);

   }

   void application::preempt_message(const char * pszMessage)
   {

      print_line("");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line("____________________________________");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line(::string("   ") + ::string(pszMessage));
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
      print_line("");
      preempt(200_ms);
   }

   bool application::is_code_in_initial_setup()
   {

      return get_code_mode() == ::coding::e_mode_initial_setup;

   }


   bool application::gcm_code_mode()
   {

      return get_code_mode() == ::coding::e_mode_gcm;

   }


   bool application::ssh_code_mode()
   {

      return get_code_mode() == ::coding::e_mode_ssh;

   }


   bool application::standard_code_mode()
   {

      return get_code_mode() == ::coding::e_mode_standard;

   }


   // bool application::did_just_install_cloud_data_provider()
   // {
   //
   //    auto atomProvider = m_strCloudDataProvider;
   //
   //    if(atomProvider == "dropbox")
   //    {
   //
   //       return m_bJustInstalledDropbox;
   //
   //    }
   //
   //    return false;
   //
   // }

//
//    ::atom application::current_fs_folder_sync_provider()
//    {
//
// #if defined(WINDOWS)
//       return "onedrive";
// #else
//       return "dropbox";
// #endif
//
//    }




   ::atom application::current_browser()
   {

#if defined(WINDOWS)
      return "chrome";
#else
      return "";
#endif

   }

   //
   //
   // ::fs::folder_sync* application::current_fs_folder_sync()
   // {
   //
   //    return fs_folder_sync(current_fs_folder_sync_provider());
   //
   // }
   //
   //
   // ::file::path application::cloud_folder()
   // {
   //
   //    return current_fs_folder_sync()->m_pathProtocol;
   //
   // }


   void application::init_instance()
   {

      //factory()->add_factory_item <::coding::document >();
      //factory()->add_factory_item <::coding::frame >();
      //factory()->add_factory_item <::coding::main_frame >();
      //factory()->add_factory_item <::coding::impact >();
      //factory()->add_factory_item <::coding::log_impact >();
      //factory()->add_factory_item <::coding::tab_impact >();
      //factory()->add_factory_item <::coding::integration >();
      //factory()->add_factory_item <::coding::summary >();
      
      //coding_factory(factory());
      
      
      //factory()->add_factory_item <::integration_integration::options_impact >();

      //safactory()->add_factory_item < ::coding::options_impact_handler, ::user::options_impact_handler >();

      ::platform::application::init_instance();

      m_strDnsSuffix = ".camilothomas.com";
      //
      // add_impact_system(
      //    "main",
      //    allocateø::user::single_document_template(
      //       "main",
      //       ::type < document >(),
      //       ::type < main_frame >(),
      //       ::type < tab_impact >()));

      //      m_ptemplateIntegrationMain = ptemplate;
      //
      //      add_document_template(ptemplate);

            //add_impact_system(
            //                  "impact",
            //                  allocateø <::user::single_document_template >(
            //                 "main",
            //                         ::type < document >(),
            //                         ::type < frame >(),
            //                         ::type < impact >()));

      //      m_ptemplateIntegrationImpact = ptemplate;
      //
      //      add_document_template(ptemplate);
      //


   }


   void application::term_application()
   {

      ::platform::application::term_application();

   }


   void application::on_request(::request* prequest)
   {

      // if (impact_system("main")->get_document_count() == 0)
      // {
      //
      //    impact_system("main")->request(prequest);
      //
      //    ::pointer < ::coding::document > pdocument = impact_system("main")->get_document(0);
      //
      //    if (pdocument)
      //    {
      //
      //       if (pdocument->is_opened())
      //       {
      //
      //          pdocument->m_pintegrationimpact->defer_auto_start_integration();
      //
      //       }
      //
      //    }
      //
      // }

   }


   string application::preferred_experience()
   {

      return "tranquillum";

   }


//   void application::defer_task_groups(::coding::integration* pintegration)
//   {
//
//
//   }


   // void application::on_initialize_operating_system_integrate_list(::numeric_array_base < enum_integrate > & eintegrateaOperatingSystem)
   // {
   //
   //
   // }


   bool application::assume_not_installed(enum_install einstall)
   {

      auto path = directory_system()->home() / "assume_not_installed.txt";

      if (!file()->exists(path))
      {

         return false;

      }

      auto lines = file()->lines(path);

      lines.trim();

      lines.erase_empty();

      if (lines.is_empty())
      {

         return true;

      }

      ::string strName = install_name(einstall);

      return lines.case_insensitive_contains(strName);


   }


   bool application::is_installed(enum_install einstall, bool bMayAssumeNotInstalled)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto ppair = code()->install_map().find(einstall);

      if(!ppair)
      {

         return false;

      }

      auto pinstall = ppair->m_element2;

      if (!pinstall)
      {

         return false;

      }

      return pinstall->is_installed(bMayAssumeNotInstalled);

   }



   bool application::__is_installed(enum_install einstall, bool bMayAssumeNotInstalled)
   {

      if (bMayAssumeNotInstalled)
      {

         if (assume_not_installed(einstall))
         {

            return false;

         }

      }

      switch (einstall)
      {
#ifdef WINDOWS_DESKTOP
      case  e_install_visual_studio:
         return __is_visual_studio_installed();
      case     e_install_tortoise_git:
         return __is_tortoise_git_installed();
      case     e_install_msys2:
         return __is_msys2_installed();
      case     e_install_strawberry_perl:
         return __is_strawberry_perl_installed();
#endif
      case     e_install_git_scm:
         return __is_git_scm_installed();
      case     e_install_smart_git:
         return __is_smart_git_installed();
      case     e_install_git_credential_manager:
         return __is_git_credential_manager_installed();
      case     e_install_patch_shell:
         return __is_shell_patched();
      case     e_install_tool_os:
         return __is_repository_installed(e_repository_tool_os);
      case     e_install_storage_windows:
         return __is_storage_os_installed("windows");
      case     e_install_storage_universal_windows:
         return __is_storage_os_installed("universal_windows");
      case     e_install_repositories:
         return _are_repositories_installed();
#ifdef MACOS
         case e_install_xcode:
            return __is_xcode_installed();
#endif
#if JETBRAINS_CLION
      case     e_install_jetbrains_clion:
         return __is_jetbrains_clion_installed();
            return __is_jetbrains_toolbox_installed();
      case     e_install_jetbrains_toolbox:
            return __is_jetbrains_toolbox_installed();
#endif //  JETBRAINS_CLION
      case     e_install_cloud_data_provider:
         {
            if (m_strCloudDataProvider == "google_drive")
            {
               return __is_google_drive_installed();
            }
            else if (m_strCloudDataProvider == "dropbox")
            {
               return __is_dropbox_installed();
            }
            else if (m_strBrowser == "onedrive")
            {
#ifdef WINDOWS
               return __is_onedrive_installed();
#else
               throw ::exception(error_wrong_state);
#endif
            }
            else if (m_strBrowser == "system")
            {
#ifdef LINUX
               return true;
#else
               throw ::exception(error_wrong_state);
#endif
            }
         }
         break;
      case     e_install_browser:
      {
         if (m_strBrowser == "chrome")
         {
            return __is_google_chrome_installed();
         }
         else if (m_strBrowser == "opera")
         {
            return __is_opera_browser_installed();
         }
         else if (m_strBrowser == "edge")
         {
#ifdef WINDOWS
            return true;
#else
            throw ::exception(error_wrong_state);
#endif
         }
         else if (m_strBrowser == "system")
         {
#ifdef LINUX
            return true;
#else
            throw ::exception(error_wrong_state);
#endif
         }
      }
         break;
      case     e_install_visual_studio_code:
         return __is_visual_studio_code_installed();
      case     e_install_deps:
         return __are_deps_installed();
      case     e_install_setup_folders:
         return __are_folders_setup();
      default:
         throw ::exception(error_failed);

      }

      return false;

   }


   void application::ensure_install(::coding::enum_install einstall, bool bMayAssumeNotInstalled)
   {

      if (is_installed(einstall, bMayAssumeNotInstalled))
      {

         return;

      }
   }


   ::file::path application::operating_system_folder()
   {

#ifdef WINDOWS

      return "C:/operating_system";

#else

      auto pathToolOsFolder = directory_system()->home() / OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME / "operating_system";

      return pathToolOsFolder;

#endif

   }


   ::file::path application::tool_os_folder()
   {

      return operating_system_folder() / ("tool-" OPERATING_SYSTEM_NAME);

   }


   ::file::path application::storage_os_folder(const ::scoped_string& scopedstrOs)
   {

      return operating_system_folder() / ("storage-" + scopedstrOs);

   }


   // integration * application::integration()
   // {
   //
   //    auto pimpactsystem = impact_system("main");
   //
   //    auto pdocument = pimpactsystem->get_document();
   //
   //    auto pintegrationdocument = dynamic_cast<document*>(pdocument);
   //
   //    auto pintegration = pintegrationdocument->m_pintegration;
   //
   //    return pintegration;
   //
   // }


   bool application::__is_graphical_ide_installed()
   {

#if defined(LINUX)

      return __is_jetbrains_clion_installed();

#elif defined(WINDOWS_DESKTOP)

      return __is_visual_studio_installed();

#elif defined(MACOS)

      //return __is_visual_studio_installed();
      
      return true;

#endif

   }



   //bool application::is_smart_git_installed()
   //{

   //   if (file_exists(directory_system()->home() / "assume_not_installed.txt"))
   //   {

   //      return false;

   //   }

   //   if (!node()->_is_smart_git_installed())
   //   {

   //      return false;

   //   }

   //   return true;

   //}



   //bool application::is_installed_vs_studio()
   //{

   //   if (m_bVisualStudioOk)
   //   {

   //      return true;

   //   }

   //   ::acme_windows::registry::key key;

   //   if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\VisualStudio\\17.0"))
   //   {

   //      if (m_bWasInstallingVisualStudio)
   //      {

   //         task_sleep(30_s);

   //      }

   //      m_bVisualStudioOk = true;

   //      return true;

   //   }

   //   if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\17.0"))
   //   {

   //      if (m_bWasInstallingVisualStudio)
   //      {

   //         task_sleep(30_s);

   //      }

   //      m_bVisualStudioOk = true;

   //      return true;

   //   }

   //   return false;

   //}


   //bool application::is_installed_svn_command()
   //{

   //   if (m_bSvnInstalled)
   //   {

   //      return true;

   //   }

   //   if (ASSUME_NOTHING_INSTALLED)
   //   {

   //      return false;

   //   }

   //   throw todo;

   //   //::acme_windows::registry::key key;

   //   //string strPrefix;

   //   //::file::path pathSvn;

   //   //if(::succeeded(key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\TortoiseSVN")))
   //   //{

   //   //   string str;

   //   //   if (::succeeded(key._get("Directory", str)))
   //   //   {

   //   //      if (str.has_character())
   //   //      {

   //   //         pathSvn = str;

   //   //         pathSvn /= "bin/svn.exe";

   //   //      }
   //   //   }

   //   //}

   //   //if (pathSvn.is_empty())
   //   //{

   //   //   return false;

   //   //}

   //   //m_pathSvn = pathSvn;

   //   //::property_set set;

   //   //int iResult = call_sync(m_pathSvn, "--version", dir::home(), ::e_display_none, 15_s, set);

   //   //if (iResult != 0)
   //   //{

   //   //   return false;

   //   //}

   //   m_bSvnInstalled = true;

   //   return true;

   //}


   bool application::__is_smart_git_installed()
   {

#if defined(FREEBSD)

      return false;

#else

      bool bInstalled = node()->_is_smart_git_installed();

      return bInstalled;

#endif

   }


   string application::__smart_git_download_url()
   {

      auto pathUrl = fetch_download_link("linux/smartgit");

      print_line("syntevo Smart Git download url : " + pathUrl);

      return pathUrl;

   }


   void application::__download_smart_git()
   {

      ::file::path pathSource = __smart_git_download_url();

      ::file::path pathTarget = directory()->home() / "Downloads/Code!!" / pathSource.name();

      ::property_set set;

      print_line("Downloading \"" + pathSource+"\" to \""+pathTarget + "\".");

      http()->download(pathTarget, pathSource, set);

      m_pathSmartGitTarGz = pathTarget;

   }


   void application::__install_smart_git()
   {

      __download_smart_git();

      print_line("Uncompressing syntevo Smart Git...");

      auto pathSyntevo = directory_system()->home() / "application_opt/syntevo";

      directory_system()->create(pathSyntevo);

      node()->posix_shell_command("tar -xzvf \""+ m_pathSmartGitTarGz + "\" -C \"" + pathSyntevo + "\"",
         e_posix_shell_system_default,
   [this](auto etracelevel, auto & str, bool bCarriage)
      {

         print_line(str);

      });

      print_line("Installing syntevo Smart Git...");

      node()->posix_shell_command(pathSyntevo / "smartgit/bin/add-menuitem.sh");

      //node()->detached_command("/bin/bash -c " + (pathSyntevo / "smartgit/bin/smartgit.sh"), {});

   }


   bool application::__is_git_credential_manager_installed()
   {

      bool bInstalled = node()->_is_git_credential_manager_installed();

      return bInstalled;

   }


   bool application::__is_shell_patched()
   {

#ifdef WINDOWS

      ::file::path pathBashProfile;

      pathBashProfile = directory_system()->home() / ".bash_profile";

      auto lines = file_system()->lines(pathBashProfile);

      if (lines.find_first_contains("# ca2 patch_shell") < 0)
      {

         return false;

      }

      return true;

#else

      bool bInstalled = node()->_is_shell_patched();

      return bInstalled;

#endif

   }


      ::string_array application::get_install_dep_script_names()
   {
      auto psummary = node()->operating_system_summary();

      if (psummary->m_strSystem == "ubuntu")
      {
         if (psummary->m_strSystemBranch == "xfce")
         {
            return {"xubuntudeps"};
         }
         else if (psummary->m_strSystemBranch == "kde")
         {
            return {"kubuntudeps"};
         }
         else
         {
            if (atoi(psummary->m_strSystemRelease) >= 24)
            {
               return {"ubuntug4deps"};
            }
            else
            {
               return {"ubuntug3deps"};
            }
         }
      }
      else if (psummary->m_strSystem == "linuxmint")
      {
         return {"ubuntug3deps"};
      }
      else if (psummary->m_strSystem == "debian")
      {
         if (psummary->m_strSystemBranch == "xfce")
         {
            return {"xdebiandeps"};
         }
         else if (psummary->m_strSystemBranch == "kde")
         {
            return {"kdebiandeps"};
         }
         else
         {
            return {"debiangdeps"};
         }
      }
       else if (psummary->m_strSystem == "fedora")
       {
           if (psummary->m_strSystemBranch == "xfce")
           {
               return {"fedora_setup", "xfedoradeps"};
           }
           else if (psummary->m_strSystemBranch == "kde")
           {
               return {"fedora_setup", "kfedoradeps"};
           }
           else
           {
               //if (atoi(psummary->m_strDistroRelease) >= 24)
               //{
                 //  return {"ubuntug4deps"};
               //}
               //else
               //{
                   return {"fedora_setup", "fedoradeps"};
               //}
           }
       }

      return {};
   }


   ::string_array application::get_install_dep_package_names()
   {

      auto depsa = get_install_dep_script_names();

      ::string_array straPackageNames;

      for (auto& deps : depsa)
      {

         ::file::path path = directory_system()->home() / "code/operating_system/tool/install_deps" / (deps + ".package_names");

         auto lines = file()->lines(path);

         straPackageNames.append_unique(lines);

      }

      return straPackageNames;

   }


   ::string_array application::get_install_dep_install_group_names()
   {

      auto depsa = get_install_dep_script_names();

      ::string_array straInstallGroupNames;

      for (auto& deps : depsa)
      {

         ::file::path path = directory_system()->home() / "code/operating_system/tool/install_deps" / (deps + ".install_group_names");

         auto lines = file()->lines(path);

         straInstallGroupNames.append_unique(lines);

      }

      return straInstallGroupNames;

   }




   bool application::are_all_operating_system_packages_and_install_groups_installed()
   {

      if (m_bInstallDepsCalculated && m_timeLastInstallDepsCheck.elapsed() < 5_min)
      {

         return m_bAllInstallDepsInstalled;

      }

      m_bInstallDepsCalculated = true;

      m_timeLastInstallDepsCheck.Now();

      auto straPackageNames = get_install_dep_package_names();

      preempt_message("Required dependencies for coding setup");

      for (auto & strPackageName : straPackageNames)
      {

         micro_preempt(strPackageName);

      }

      auto straNotInstalledPackages = system()->not_installed_operating_system_packages(straPackageNames);

      m_bAllInstallDepsInstalled = straNotInstalledPackages.is_empty();

      if (!m_bAllInstallDepsInstalled)
      {

         preempt_message("Required dependencies for coding setup that aren't installed");

         for (auto & strPackageName : straNotInstalledPackages)
         {

            micro_preempt(strPackageName);

         }

      }

      return m_bAllInstallDepsInstalled;

   }


   void application::__install_deps()
   {

      auto depsa = get_install_dep_package_names();

      system()->defer_install_operating_system_packages(depsa);

   }



   bool application::__are_deps_installed()
   {

      //auto psummary = node()->operating_system_summary();

      //auto strSystemFamily = psummary->m_strSystemFamily;

      //if (strSystemFamily == "debian")
      //{

         return are_all_operating_system_packages_and_install_groups_installed();

      //}

      //auto path = directory_system()->home() / ".config/integration/code/install_deps.txt";

      //auto bExists = file_system()->exists(path);

      //return bExists;

   }


   bool application::__are_folders_setup()
   {

      auto bFirstFolderSetupDetection = m_bFirstFolderSetupDetection;

      m_bApplicationFirstRequest = false;

      auto path1 = directory_system()->home() / ".ssh/id_auth";

      auto bExists1 = file_system()->exists(path1);

      auto path2 = directory_system()->home() / ".ssh/id_auth.pub";

      auto bExists2 = file_system()->exists(path2);

      auto path3 = directory_system()->home() / ".ssh/id_sign";

      auto bExists3 = file_system()->exists(path3);

      auto path4 = directory_system()->home() / ".ssh/id_sign.pub";

      auto bExists4 = file_system()->exists(path4);

      if(!bExists1 || !bExists2 || !bExists3 || !bExists4)
      {

         return false;
      }

      if(m_timeFoldersSetupDetected.is_null())
      {

         m_timeFoldersSetupDetected.Now();

         if(bFirstFolderSetupDetection)
         {

            m_timeFoldersSetupDetected -= 5_s;

         }

      }

      return m_timeFoldersSetupDetected.elapsed() > 3_s;

   }


#if JETBRAINS_CLION


   bool application::__is_jetbrains_clion_installed()
   {

      bool bInstalled = node()->_is_jetbrains_clion_installed();

      return bInstalled;

   }


   bool application::__is_jetbrains_toolbox_installed()
   {

      bool bInstalled = node()->_is_jetbrains_clion_installed();

      return bInstalled;

   }

#endif //JETBRAINS_CLION


   void application::set_code_mode(const ::coding::e_mode & emode)
   {


   }


   ::coding::e_mode application::get_code_mode()
   {

      return {};

   }


   ::coding::code* application::code()
   {

      return nullptr;

   }




   bool application::__is_google_drive_installed()
   {

      bool bInstalled = node()->_is_google_drive_installed();

      return bInstalled;

   }


   bool application::__is_dropbox_installed()
   {
      
      //node()->calculate_dropbox_installed();

      auto pdropbox = ::dropbox::dropbox::get(this);

      auto pathFolder = pdropbox->folder_path();

      bool bInstalled = pathFolder.has_character();

      return bInstalled;

   }


   bool application::__is_onedrive_installed()
   {

      bool bInstalled = node()->_is_onedrive_installed();

      return bInstalled;

   }


   string application::__google_chrome_download_url()
   {

      ::file::path pathUrl;

      auto psummary = node()->operating_system_summary();

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {
         pathUrl = "https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb";
      }
      else if (psummary->m_strSystem == "fedora" || psummary->m_strSystem == "opensuse")
      {
         pathUrl = "https://dl.google.com/linux/direct/google-chrome-stable_current_x86_64.rpm";
      }

      return pathUrl;

   }


   void application::__download_google_chrome()
   {

      ::file::path pathSource = __google_chrome_download_url();

      ::file::path pathTarget = directory()->home() / "Downloads/Code!!" / pathSource.name();

      ::property_set set;

      print_line("Downloading \"" + pathSource+"\" to \""+pathTarget + "\".");

      http()->download(pathTarget, pathSource, set);

      m_pathBrowserInstaller = pathTarget;

   }


   void application::__install_browser()
   {

      if (m_strBrowser == "chrome")
      {

         __download_google_chrome();

         install_from_operating_system_package_file(m_pathBrowserInstaller);

      }

   }




   bool application::__is_google_chrome_installed()
   {

      bool bInstalled = node()->_is_google_chrome_installed();

      return bInstalled;

   }


   bool application::__is_opera_browser_installed()
   {

      bool bInstalled = node()->_is_opera_browser_installed();

      return bInstalled;

   }


   bool application::__is_visual_studio_code_installed()
   {

      bool bInstalled = node()->_is_visual_studio_code_installed();

      return bInstalled;

   }

   string application::__visual_studio_code_download_url()
   {

      ::file::path pathUrl;

      auto psummary = node()->operating_system_summary();

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {

         pathUrl = "https://code.visualstudio.com/sha/download?build=stable&os=linux-deb-x64";

      }
      else if (psummary->m_strSystem == "fedora" || psummary->m_strSystem == "opensuse")
      {

         ::string strRedirectingUrl = "https://code.visualstudio.com/sha/download?build=stable&os=linux-deb-x64";

         ::property_set set;

         pathUrl = http()->get_effective_url(strRedirectingUrl, set).as_string();

      }

      return pathUrl;

   }


   void application::__download_visual_studio_code()
   {

      ::file::path pathSource1 = __visual_studio_code_download_url();

      print_line("Got this url for downloading Visual Studio Code : \"" + pathSource1+"\".");

      ::property_set set1;

      print_line("Going to calculate effective url...");

      ::file::path pathSource = http()->get_effective_url(pathSource1, set1).as_string();

      ::file::path pathTarget = directory()->home() / "Downloads/Code!!" / pathSource.name();

      ::property_set set;

      print_line("Downloading \"" + pathSource+"\" to \""+pathTarget + "\".");

      http()->download(pathTarget, pathSource, set);

      m_pathVisualStudioCode = pathTarget;

   }


   void application::__install_visual_studio_code()
   {

      auto psummary = node()->operating_system_summary();

      if (psummary->m_strSystemFamily.case_insensitive_contains("debian"))
      {

         __download_visual_studio_code();

         install_from_operating_system_package_file(m_pathVisualStudioCode);

      }
      else
      {
      }

   }


   void application::install_from_operating_system_package_file(const::file::path & pathPackageFile)
   {

      auto strCommandLine = system()->install_operating_system_package_file_command_line(pathPackageFile);

      node()->pty(strCommandLine);

   }




#ifdef MACOS

   bool application::__is_xcode_installed()
   {
      
      return false;
      
   }

#endif

   ::file::path application::bash_path(const ::file::path& path)
   {


#ifdef WINDOWS_DESKTOP
      if (::character_isalpha(path[0]) && path[1] == ':' && path[2] == '/')
      {

         return "/" + ::string(::character_tolower(path[0])) + "/" + &path[3];

      }
      else
#endif
      {

         return path;

      }


   }


   string application::fetch_download_link(const ::scoped_string & scopedstrId)
   {

      ::property_set set;

      string str;

      set["disable_ca2_sessid"] = true;

      set["raw_http"] = true;

      ::string strUrl;

      strUrl.format("https://ca2.site/code_download_link?id={}", ::url::encode(scopedstrId));

      str = http()->get(strUrl, set);

      return str;

   }


   ::file::path application::get_repository_path(::coding::enum_repository erepository)
   {

      switch (erepository)
      {

      case e_repository_tool_os:
            return directory_system()->home() / "code/operating_system/tool";
//#ifdef WINDOWS
  //       return "C:/operating_system/tool-windows";
//#else
  //       return directory_system()->home() / OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME / "operating_system/tool-" OPERATING_SYSTEM_NAME;
//#endif
      case e_repository_simple:
#ifdef WINDOWS
         return "C:/simple";
#else
         return directory_system()->home() / "code" / "simple";
#endif
      default:
         throw ::exception(error_failed);

      }
      return "";

   }


   ::file::path application::get_repository_object(::coding::enum_repository erepository)
   {

      switch (erepository)
      {

      case e_repository_tool_os:
         return "ca2/tool-" OPERATING_SYSTEM_NAME;
      case e_repository_simple:
         return "ca2/" OPERATING_SYSTEM_NAME "-simple-" OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME;
      default:
         throw ::exception(error_failed);
      }



   }


   ::string application::get_repository_url_prefix(::coding::enum_repository erepository)
   {

      if (standard_code_mode() || ssh_code_mode())
      {

         return "git@github.com:";

      }
      else
      {

         return "https://github.com/";

      }

   }


   ::file::path application::get_repository_url(::coding::enum_repository erepository)
   {

      return get_repository_url_prefix(erepository) + get_repository_object(erepository);

   }


   //bool application::__is_repository_installed(enum_install einstall)
   //{

   //   ::file::path path = get_repository_path(einstall);

   //   return directory_system()->is(path) && directory_system()->is(path / ".git");

   //}


   bool application::__is_repository_installed(::coding::enum_repository erepository)
   {

      ::file::path path = get_repository_path(erepository);

      return directory_system()->is(path) && directory_system()->is(path / ".git");

   }


   bool application::__is_storage_os_installed(const ::scoped_string & scopedstrOs)
   {

      ::file::path pathStorageOs = storage_os_folder(scopedstrOs);

      if (scopedstrOs == "windows")
      {

         auto bOk1 = directory_system()->is(pathStorageOs / "x64/Debug");

         auto bOk2 = directory_system()->is(pathStorageOs / "x64/Release");

         auto bOk3 = directory_system()->is(pathStorageOs / "x64/StaticDebug");

         auto bOk4 = directory_system()->is(pathStorageOs / "x64/StaticRelease");

         return bOk1 && bOk2 && bOk3 && bOk4;

      }
      else
      {

         return false;

      }

   }


      ::file::path application::_get_repository_path(const ::scoped_string & scopedstr)
   {

      ::string strName(scopedstr);

      strName.trim();

      if(strName.is_empty())
      {

         return {};

      }

      if(strName == "integration")
      {

#ifdef WINDOWS
         return "C:/integration/integration";
#endif

      }
      else if(strName == "netnode")
      {

#ifdef WINDOWS
         return "C:/netnode/netnode";
#endif

      }
      else if(strName == "build-all")
      {
#ifdef WINDOWS
         return "C:/main";
#else
         return directory_system()->home() / OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME / "main";
#endif
      }

      return directory_system()->home() / OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME / strName;

   }


   ::file::path application::_get_repository_object(const ::scoped_string & scopedstr)
   {

      ::string strName(scopedstr);

      strName.trim();

      if(strName.is_empty())
      {

         return {};

      }

      ::string str;

      if(strName == "build-all")
      {

         str.formatf("ca2/%s-build-%s-all",
            OPERATING_SYSTEM_NAME,
            OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME);

      }
      else
      {
         str.formatf("ca2/%s-%s-%s",
            OPERATING_SYSTEM_NAME,
            strName.c_str(),
            OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME);

      }


      return str;

   }


   ::file::path application::_get_repository_url_prefix(const ::scoped_string & scopedstr)
   {

      if (standard_code_mode() || ssh_code_mode())
      {

         return "git@github.com:";

      }
      else
      {

         return "https://github.com/";

      }

   }

   ::file::path application::_get_repository_url(const ::scoped_string & scopedstr)
   {

      return _get_repository_url_prefix(scopedstr) + _get_repository_object(scopedstr);

   }


   bool application::_is_repository_installed(const ::scoped_string & scopedstr)
   {

      ::file::path path = _get_repository_path(scopedstr);

      printf_line("application::_is_repository_installed path : %s", path.c_str());

      return directory_system()->is(path) && directory_system()->is(path / ".git");

   }


   bool application::_are_repositories_installed()
   {

      if (current_repository() == "simple")
      {

         return _is_simple_repository_installed();

      }
      else
      {

         return _are_repositories_once_listed_at_cloud_installed();

      }

   }


   string application::current_repository()
   {


      return m_strRepository;

   }


   bool application::_is_simple_repository_installed()
   {

      return __is_repository_installed(e_repository_simple);

   }


   bool application::_are_repositories_once_listed_at_cloud_installed()
   {

#if defined(WINDOWS)

      ::file::path pathIndex = directory_system()->home() / "application/integration/code/___repositories/index.txt";

#else

      ::file::path pathIndex = directory_system()->home()/".config/integration/code/___repositories/index.txt";

#endif

      if(!file_system()->exists(pathIndex))
      {

         return false;

      }

      ::string strIndex = file_system()->as_string(pathIndex);

      strIndex.trim();

      if(strIndex.is_empty())
      {

         return false;

      }

      return __are_repositories_installed(strIndex);

   }


   bool application::__are_repositories_installed(const ::scoped_string & scopedstrIndex)
   {

      ::string strIndex(scopedstrIndex);

      if(strIndex.case_insensitive_equals("(empty)"))
      {

         return true;

      }

      ::string_array straLines;

      straLines.add_lines(strIndex);

      for(auto & strLine : straLines)
      {

         if(!_is_repository_installed(strLine))
         {

            return false;

         }

      }

      return true;

   }

   //
   // void application::install_on_checkbox(::user::check* pcheck)
   // {
   //
   //
   //
   // }


   void application::defer_install(::coding::enum_install einstall, task_group * ptaskgroup)
   {

      if (!is_installed(einstall, true))
      {

         auto ppair = code()->install_map().find(einstall);

         auto pinstall = ppair->m_element2;

         // if (ptaskgroup)
         // {
         //
         //    if (!pinstall->m_pinstallloginterface && ptaskgroup->m_pintegration)
         //    {
         //
         //       pinstall->m_pinstallloginterface = ptaskgroup->m_pintegration->m_pimpactinterface;
         //
         //    }
         //
         //    pinstall->m_ptaskgroupOptional = ptaskgroup;
         //
         // }

         pinstall->set_status("Installing \"" + pinstall->get_title() + "\"...");

         defer_start_installation(einstall, true);

         pinstall->wait_installation();

      }

      //while (!is_installed(einstall))
      //{



      //}

   }


   void application::defer_start_installation(::coding::enum_install einstall, bool bAutoInstall)
   {

      information() << "defer_start_installation : " << install_name(einstall) << ", auto_install : " << bAutoInstall;

      _synchronous_lock synchronouslock(this->synchronization());

      auto ppair = code()->install_map().find(einstall);

      if(!ppair)
      {

         information() << "defer_start_installation : " << install_name(einstall) << " not found!!";

         return;

      }

      auto pinstall = ppair->m_element2;

      if(pinstall->m_ptaskStart || pinstall->m_bInstalling)
      {

         return;

      }

      // if ((pinstall->m_pinstallimpactinterface && pinstall->m_pinstallimpactinterface->is_selected())
      //    || (bAutoInstall && !is_installed(einstall, true)))
      // {
      //
      //    information() << "defer_start_installation gonna start : " << pinstall->m_strName;
      //
      //    pinstall->m_ptaskStart  = fork([this, pinstall]()
      //       {
      //
      //          try
      //          {
      //
      //             information() << "defer_start_installation starting : " << pinstall->m_strName;
      //
      //             pinstall->start_installation(3);
      //
      //          }
      //          catch (...)
      //          {
      //
      //          }
      //
      //       pinstall->m_ptaskStart.release();
      //
      //       });
      //
      // }
      // else if (is_installed(einstall, false))
      // {
      //
      //    information() << "defer_start_installation yes_it_is_installed : " << pinstall->m_strName;
      //
      //    pinstall->m_ptaskStart = fork([this, pinstall]()
      //       {
      //
      //          try
      //          {
      //
      //             information() << "defer_start_installation on_installed : " << pinstall->m_strName;
      //
      //             on_installed(pinstall->m_einstall, false);
      //
      //          }
      //          catch (...)
      //          {
      //
      //          }
      //
      //       pinstall->m_ptaskStart.release();
      //
      //       });
      //
      // }

   }


   ::string application::install_name(enum_install einstall)
   {

      switch (einstall)
      {

      case  e_install_visual_studio:
         return "visual_studio";
      case     e_install_git_scm:
         return "git_scm";
      case     e_install_tortoise_git:
         return "tortoise_git";
      case     e_install_smart_git:
         return "smart_git";
      case     e_install_git_credential_manager:
         return "git_credential_manager";
      case     e_install_tool_os:
#if defined(WINDOWS)
         return "tool_windows";
#elif defined(LINUX)
         return "tool_linux";
#elif defined(__APPLE__)
         return "tool_macos";
#else
         return "tool_(unknown_os)";
#endif
      case     e_install_storage_windows:
         return "storage-windows";
      case     e_install_storage_universal_windows:
         return "storage-universal_windows";
      //case     e_install_repositories:
        // return "repositories";
      case     e_install_msys2:
         return "msys2";
      case     e_install_patch_shell:
         return "patch_shell";
      case     e_install_strawberry_perl:
         return "strawberry_perl";
      case     e_install_jetbrains_clion:
         return "jetbrains_clion";
      case     e_install_jetbrains_toolbox:
         return "jetbrains_toolbox";
         case e_install_xcode:
            return "xcode";
      case     e_install_cloud_data_provider:
         return m_strCloudDataProvider;
      case     e_install_browser:
         return m_strBrowser;
      case     e_install_repositories:
         return m_strRepository;
      case     e_install_visual_studio_code:
         return "visual_studio_code";
      case     e_install_deps:
         return "deps";
      case     e_install_setup_folders:
         return "setup_folders";
      default:
         throw ::exception(error_failed);

      }

   }


#ifdef WINDOWS_DESKTOP


   void application::_defer_install_msys2(task_group* ptaskgroup)
   {

      defer_install(e_install_msys2, ptaskgroup);

      if (!is_installed(e_install_msys2, false))
      {

         throw ::exception(error_wrong_state, "msys2 isn't installed or not installed at C:\\msys64");

      }

      auto pinstall = code()->m_installmap[e_install_msys2];

      auto tracefunction = pinstall->task_group_trace_function(ptaskgroup);

      node()->defer_install_posix_shell_command("make", e_posix_shell_msys2, tracefunction);

      node()->defer_install_posix_shell_command("pkgconf", e_posix_shell_msys2, tracefunction);

      //node()->system_notify_environment_variable_change();

      //node()->update_process_environment_variables();

   }


#endif


   ::string application::install_title(enum_install einstall)
   {

      switch (einstall)
      {

      case  e_install_visual_studio:
         return "Visual Studio";
      case     e_install_git_scm:
         return "git";
      case     e_install_tortoise_git:
         return "TortoiseGit";
      case     e_install_smart_git:
         return "SmartGit";
      case     e_install_git_credential_manager:
         return "Git Credential Manager";
      case     e_install_tool_os:
#if defined(WINDOWS)
         return "tool-windows";
#elif defined(LINUX)
         return "tool-linux";
#elif defined(__APPLE__)
         return "tool-macos";
#else
         return "tool-(unknown operating system)";
#endif
      case     e_install_storage_windows:
         return "storage-windows";
      case     e_install_storage_universal_windows:
         return "storage-universal_windows";
      //case     e_install_repositories:
        // return "repositories";
      case     e_install_patch_shell:
         return "patch shell";
      case     e_install_msys2:
         return "MSYS2";
      case     e_install_strawberry_perl:
         return "Strawberry Perl";
      case     e_install_jetbrains_clion:
         return "CLion";
      case     e_install_jetbrains_toolbox:
         return "JetBrains Toolbox";
         case e_install_xcode:
            return "Xcode";
      case     e_install_cloud_data_provider:
         return m_strCloudDataProviderTitle;
      case     e_install_browser:
         return m_strBrowserTitle;
      case     e_install_repositories:
         return m_strRepositoryTitle;
      case     e_install_visual_studio_code:
         return "Visual Studio Code";
      case     e_install_deps:
         return "Dependencies";
      case     e_install_setup_folders:
         return "Setup Folders";
      default:
         throw ::exception(error_failed);

      }

      return {};

   }


   ::string application::install_remark(enum_install einstall)
   {

      switch (einstall)
      {

      case  e_install_visual_studio:
         return "Required for opening and build ca2 solution files";
      case     e_install_git_scm:
         return "Required for downloading and managing source.";
      case     e_install_tortoise_git:
         return "Recommended for File Explorer Right Click[Context] Menu and Icon Overlay.";
      case     e_install_smart_git:
         return"Recommended IDE for Git Source Control.";
      case     e_install_git_credential_manager:
         return"Git Credential Manager is a good manager for git credentials.";
      case     e_install_tool_os:
         return "Required for using ca2";
      //case     e_install_repositories:
        // return "Repositories to code with...";
      case     e_install_storage_windows:
         return "Pre-built libraries for coding with ca2 for Windows...";
      case     e_install_storage_universal_windows:
         return "Pre-built libraries for coding with ca2 for Universal Windows...";
      case     e_install_patch_shell:
         return "Some shell/environment setup and tweaks for ca2 coding...";
      case     e_install_msys2:
         return "Required for building many open source projects...";
      case     e_install_strawberry_perl:
         return "Required for building OpenSSL...";
      case     e_install_jetbrains_clion:
         return "An excellent free for non commercial use IDE for coding ca2 projects.";
      case     e_install_jetbrains_toolbox:
         return "For installing CLion: an excellent IDE for coding ca2 projects.";
         case     e_install_xcode:
            return "An excellent IDE for coding ca2 projects.";
      case     e_install_cloud_data_provider:
         return m_strCloudDataProviderTitle;
      case     e_install_browser:
         return m_strBrowserTitle;
      case     e_install_repositories:
         return m_strRepositoryDescription;
      case     e_install_visual_studio_code:
         return "Visual Studio Code";
      case     e_install_deps:
         return "Dependencies for building ca2 projects.";
      case     e_install_setup_folders:
         return "Setup Folders for building ca2 projects in Standard Mode.";
      default:
         throw ::exception(error_failed);

      }

   }


   void application::on_installed(::coding::enum_install einstall, bool bJustInstalled)
   {

      if (einstall == e_install_strawberry_perl)
      {

         // if (bJustInstalled)
         // {
         //
         //    auto pdocument = m_ptabimpact->get_document();
         //
         //    auto pintegration = pdocument->m_pintegration;
         //
         //    pintegration->prepare_build();
         //
         // }

      }

   }


   void application::create_install(::coding::enum_install einstall)
   {


#ifdef DEBUG

      ::string strName = install_name(einstall);

      auto lines = file()->lines(directory_system()->home() / "assume_not_installed.txt");

      lines.trim();

      lines.erase_empty();

      for (auto& line : lines)
      {

         line.erase_character(' ');
         line.erase_character('\t');

      }

      if (!lines.case_insensitive_contains(strName) && !lines.case_insensitive_contains("#" + strName))
      {

         lines.add("#" + strName);

         file()->put_lines(directory_system()->home() / "assume_not_installed.txt", lines);

      }

#endif


      auto pinstall = create_newø<::coding::install>();

      pinstall->create_install(einstall);

      _synchronous_lock synchronouslock(this->synchronization());

      auto & installmap = code()->install_map();

      installmap[einstall] = pinstall;


   }



// void application::defer_task_groups(::coding::integration* pintegration)
// {
//
// }

} // namespace coding






