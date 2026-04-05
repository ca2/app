#pragma once


#include "coding/_constant.h"
#include "acme/platform/application.h"
#include "acme/user/user/check.h"


namespace coding
{


   class CLASS_DECL_CODING application :
      virtual public ::platform::application
   {
   public:


      //{
      ::user::check     m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization;


      bool        m_bWinRT;


      
      ::string m_strDnsSuffix;

      //tab_impact* m_ptabimpact;

         bool           m_bJustCreatedDropboxFolder;
         bool       m_bJustInstalledDropbox;

      //bool m_bDoIntegration = true;
      //bool m_bDoBuildTool = true;

      //enum_application                       m_eapplication;

      bool                                   m_bStartingInstallation2;
      bool                                   m_bJustInstalledGraphicalIde;
      class ::time                           m_timeFinishedInstallingGraphicalIde;
      ::string                               m_strMayNeedRestartStatus;
class ::time      m_timeFoldersSetupDetected;
         bool m_bFirstFolderSetupDetection;



         //::string      m_strCloudDataProvider;
      ::file::path m_pathBrowserInstaller;
      ::file::path m_pathSmartGitTarGz;
      ::file::path m_pathJetBrainsTarGz;
      ::string m_strBrowserTitle;
      ::string m_strRepositoryTitle;
      ::string m_strRepositoryDescription;
         ::string        m_strCloudDataProviderTitle;

         ::atom_array            m_atomaCloudDataProviderOptions;
         ::string_array          m_straCloudDataProviderOptionsNames;


      ::string                            m_strBrowser;
      ::string                            m_strCloudDataProvider;
      ::string                            m_strRepository;
         //::data::property        m_propertyBrowser;
         //::data::property        m_propertyBrowserTitle;
         ::atom_array            m_atomaBrowser;
         ::string_array          m_straBrowserNames;
::file::path m_pathVisualStudioCode;
         //::data::property        m_propertyRepository;
         //::data::property        m_propertyRepositoryTitle;
         //::data::property        m_propertyRepositoryDescription;
         ::atom_array            m_atomaRepository;
         ::string_array          m_straRepositoryNames;
         ::string_array          m_straRepositoryDescription;
      class ::time               m_timeLastInstallDepsCheck;
      bool                       m_bInstallDepsCalculated = false;
      bool                       m_bAllInstallDepsInstalled = false;

      application();
      ~application() override;


      __DECLARE_APPLICATION_RELEASE_TIME();
      virtual void preempt_message(const char * pszMessage);
      virtual void micro_preempt(const char * pszMessage);

      /////////////bool did_just_install_cloud_data_provider();
      ///
      ///

      bool is_code_in_initial_setup();
      bool standard_code_mode();
      bool gcm_code_mode();
      bool ssh_code_mode();

      virtual string fetch_download_link(const ::scoped_string & scopedstrId);
      //virtual ::atom current_fs_folder_sync_provider();
      ////////////virtual ::fs::folder_sync* current_fs_folder_sync();
      //virtual ::file::path cloud_folder();

      virtual ::atom current_browser();

      virtual string preferred_experience() override;
      virtual string current_repository();

      virtual void init_instance() override;
      virtual void term_application() override;


      virtual void on_request(::request * prequest) override;

      //virtual void defer_task_groups(::coding::integration* pintegration);

      //virtual void on_initialize_operating_system_integrate_list(::numeric_array_base < enum_integrate > & eintegrateaOperatingSystem);

      virtual bool assume_not_installed(::coding::enum_install einstall);
      virtual bool is_installed(::coding::enum_install einstall, bool bMayAssumeNotInstalled);
      virtual bool __is_installed(::coding::enum_install einstall, bool bMayAssumeNotInstalled);

      virtual void ensure_install(::coding::enum_install einstall, bool bMayAssumeNotInstalled);


      virtual ::file::path tool_os_folder();
      virtual ::file::path operating_system_folder();
      virtual ::file::path storage_os_folder(const ::scoped_string & scopedstrOs);

      virtual bool __is_code_operating_system_folder_present();
      virtual bool __is_operating_system_tool_cloned();

      virtual void __create_code_operating_system_folder();
      virtual void __clone_operating_system_tool();

         virtual bool __is_google_drive_installed();
         virtual bool __is_dropbox_installed();
         virtual bool __is_onedrive_installed();
      
#ifdef MACOS
      virtual bool __is_xcode_installed();
#endif

#if TORTOISE_GIT
      // bool defer_install_tortoise_git(int iTry);
      //void install_tortoise_git();
      virtual bool __is_tortoise_git_installed();
#endif
#if SMART_GIT
      //bool defer_install_smart_git(int iTry);
      virtual void __install_smart_git();
      virtual void __download_smart_git();
      virtual ::string __smart_git_download_url();
      virtual bool __is_smart_git_installed();
#endif

      virtual void install_from_operating_system_package_file(const ::file::path & pathPackageFile);
      virtual void __install_browser();
      virtual void __download_google_chrome();
      virtual ::string __google_chrome_download_url();
         virtual bool __is_google_chrome_installed();
         virtual bool __is_opera_browser_installed();
      virtual void __install_visual_studio_code();
      virtual void __download_visual_studio_code();
      virtual ::string __visual_studio_code_download_url();
         virtual bool __is_visual_studio_code_installed();
      virtual bool __is_git_credential_manager_installed();
      virtual bool __is_shell_patched();
         virtual bool __are_deps_installed();
      virtual ::string_array get_install_dep_script_names();
      virtual ::string_array get_install_dep_package_names();
      virtual ::string_array get_install_dep_install_group_names();
      virtual bool are_all_operating_system_packages_and_install_groups_installed();
      virtual void __install_deps();
         virtual bool __are_folders_setup();
#if JETBRAINS_CLION
         //bool defer_install_smart_git(int iTry);
         //void install_smart_git();
         virtual bool __is_jetbrains_clion_installed();
         virtual bool __is_jetbrains_toolbox_installed();
#endif
#if INSTALL_GIT_ServiceControlManager
      //bool defer_install_git_scm(int iTry);
      //void install_git_scm();
      virtual bool __is_git_scm_installed();
#endif
#ifdef WINDOWS_DESKTOP
      //bool defer_install_git_scm(int iTry);
      //void install_git_scm();
      bool __is_msys2_installed();
      bool __is_strawberry_perl_installed();
#endif

      // virtual bool is_graphical_ide_installed();
      //virtual bool _is_graphical_ide_installed();
      virtual bool __is_graphical_ide_installed();


#ifdef LINUX

      virtual void start_install_clion();

      virtual void __install_jetbrains_clion();
      virtual void __download_jetbrains_clion();
      virtual ::string __jetbrains_clion_download_url();

      //virtual bool is_clion_installed();

#endif


#ifdef WINDOWS_DESKTOP

      //virtual void start_install_visual_studio();

      // virtual void install_visual_studio();

      bool __is_visual_studio_installed();


#endif


      virtual ::string install_name(::coding::enum_install einstall);
      virtual ::string install_title(::coding::enum_install einstall);
      virtual ::string install_remark(::coding::enum_install einstall);

      virtual void on_installed(::coding::enum_install einstall, bool bJustInstalled);

      void create_install(::coding::enum_install einstall);


      virtual ::file::path bash_path(const ::file::path& path);


      virtual ::file::path get_repository_path(::coding::enum_repository einstall);
      virtual ::file::path get_repository_object(::coding::enum_repository einstall);
      virtual ::string get_repository_url_prefix(::coding::enum_repository einstall);
      virtual ::file::path get_repository_url(::coding::enum_repository einstall);

      virtual bool __is_repository_installed(::coding::enum_repository einstall);
      virtual bool __is_storage_os_installed(const ::scoped_string& scopedstrOs);


      virtual ::file::path _get_repository_path(const ::scoped_string & scopedstr);
      virtual ::file::path _get_repository_object(const ::scoped_string & scopedstr);
      virtual ::file::path _get_repository_url_prefix(const ::scoped_string & scopedstr);
      virtual ::file::path _get_repository_url(const ::scoped_string & scopedstr);

      virtual bool _is_repository_installed(const ::scoped_string & scopedstr);
      virtual bool _are_repositories_installed();
      virtual bool _is_simple_repository_installed();
      virtual bool _are_repositories_once_listed_at_cloud_installed();
      virtual bool __are_repositories_installed(const ::scoped_string & scopedstrIndex);

      //void install_set_status(::coding::enum_install einstall, const ::scoped_string& scopedstr);
      //void install_set_status2(::coding::enum_install einstall, const ::scoped_string& scopedstr);
      //void install_append_status2(::coding::enum_install einstall, const ::scoped_string& scopedstr);



      virtual void defer_install(::coding::enum_install einstall, task_group * ptaskgroup);
      virtual void defer_start_installation(::coding::enum_install einstall, bool bAutoStart = false);

      //virtual void unselect();
      
      
      //virtual ::coding::integration * integration();


      virtual void set_code_mode(const ::coding::e_mode & emode);
      virtual ::coding::e_mode get_code_mode();

      virtual ::coding::code* code();


#ifdef WINDOWS_DESKTOP

      virtual void _defer_install_msys2(task_group* ptaskgroup);

#endif



   };


} // namespace installation_coding



