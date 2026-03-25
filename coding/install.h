// Created as main_item.h by camilo on 2024-04-27 22:43 <3ThomasBorregaardSorensen!!
// From main_item.h by camilo on 2024-04-27 22:50 <3ThomasBorregaardSorensen!!
// From install_base.h by camilo on 2024-04-27 22:58 <3ThomasBorregaardSorensen!!
// From integration/code:install.h and separation
//       of ui concern into integration/code:install_impact_handler by
//       camilo on 2024-05-04 04:07 <3ThomasBorregaardSorensen!!
#pragma once


#include "code_application.h"
#include "acme/platform/trace.h"
#include "apex/platform/app_consumer.h"
//#include "berg/user/user/form_handler.h"
//#include "berg/user/user/impact.h"
#include "acme/parallelization/manual_reset_happening.h"


namespace coding
{


   class CLASS_DECL_CODING install :
      virtual public app_consumer < ::coding::code_application >,
      virtual public ::data::property_container
   {
   public:


      ::pointer < task_group >               m_ptaskgroupOptional;
      //::pointer < install_impact_interface > m_pinstallimpactinterface;
      //::pointer < install_log_interface > m_pinstallloginterface;
      ::coding::enum_install                        m_einstall;
      bool                                m_bInstalling;
      ::string                             m_strName;

      ::property                   m_propertyTitle;
      ::property                   m_propertyRemark;

      manual_reset_happening              m_happeningFinished;
      ::file::path                        m_path;
      int                                 m_iTry;
      int                                 m_iTryCount;

      ::task_pointer m_ptaskStart;
      ::string                            m_strStatus;
      ::string                            m_strStatus2;

      //::pointer < ::user::line_layout >   m_plinelayout;
      //::pointer < ::user::still >         m_pstillTitle;
      //::pointer < ::user::still >         m_pstillRemark;
      //::pointer < ::user::still >         m_pstillStatus;
      //::pointer < ::user::check_box >     m_pcheckbox;
      //::pointer < ::user::still >         m_pstillCheckBox;

      //::string m_strDropboxCommand;


      install();
      ~install() override;

      //::string dropbox_client();

      void create_install(enum_install einstall);

      //virtual bool _install_dropbox();

#if !defined(WINDOWS)

      //virtual void dropbox_exclude_all_except(const ::string_array& straInclude);

      //virtual void dropbox_include_box();

      //virtual bool dropbox_is_box_excluded();

      //virtual void dropbox_exclude_all_except_box();

#endif

      virtual void run_normal_install();

      virtual void on_finished();

      virtual void start_installation(int iTryCount);

      virtual void wait_installation();

      virtual void defer_start_installation();

      void set_status(const ::scoped_string& scopedstr);
      void set_status2(const ::scoped_string& scopedstr);
      void append_status2(const ::scoped_string& scopedstr);

      int synchronous_posix_terminal(const ::scoped_string& scopedstr);

  //    ::trace_function task_group_trace_function(task_group* ptaskgroup);
//

      void download();


      virtual ::file::path download_to_folder(const ::file::path& pathDownloadFolder, const ::file::path& pathUrl, const ::scoped_string& scopedstrName);
      virtual ::file::path download_to_downloads_code__(const ::file::path& pathUrl, const ::scoped_string& scopedstrName);
      virtual ::file::path download_to_operating_system(const ::file::path& pathUrl, const ::scoped_string& scopedstrName);

      virtual void unzip(const ::file::path& pathFolder, const ::file::path& pathZip);

      virtual void download_and_gzuntar(const ::file::path& pathUrl, const ::file::path& pathFolder, int iEat = 0);

      virtual bool has_download_step();

      virtual void _run_installer();
      //virtual void _run();

      virtual bool is_installed(bool bMayAssumeNotInstalled);
      virtual string_array missing_dependencies();
      virtual bool are_all_dependencies_installed();


      virtual void install_smart_git();

      virtual void install_repository(::coding::enum_repository erepository);
      virtual void _install_repository(::coding::enum_repository erepository);
      virtual void _install_repository(const ::scoped_string& scopedstrUrl);
      virtual void install_repositories();
      virtual void install_storage_os(const ::scoped_string& scopedstrOs);
      virtual void _install_app_simple_repository();
      virtual void install_app_simple_repository();
//      virtual void install_cloud_listed_repositories();

  ///    virtual void install_cloud_data_provider();


      virtual bool are_fonts_installed();
      virtual void install_user_fonts();
      //virtual ::file::path cloud_fonts_folder();
      //virtual void wait_cloud_folder_contains_files(const ::file::path& path, const ::string_array& straName, int iMinimumSize);
      //virtual bool check_whether_folder_contains_files(const ::file::path& path, const ::string_array& straName, int iMinimumSize);

      //virtual ::string cloud_non__empty__file_as_string(const ::file::path& path);

      virtual void _install_user_fonts();
      virtual void install_user_fonts_from_font_listing(const ::file::path& pathListing);

      virtual void install_browser();
      virtual void install_google_chrome();

#if defined(LINUX) || defined(FREEBSD)

      virtual void defer_install_gnome_extensions();
      virtual void _install_gnome_extensions();
      virtual void defer_install_user_packages();
      virtual bool _are_user_packages_installed();
      virtual void _install_user_packages();
      virtual void defer_install_packages(const ::string_array_base & straPackageName);
      virtual void _install_packages(const ::string_array_base & straPackageName);
      virtual void _uninstall(const ::scoped_string& scopedstrPackageName);
      virtual bool _is_package_installed(const ::scoped_string& scopedstrPackageName);

#endif

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD)

      virtual void install_visual_studio_code();
      virtual void install_git_credential_manager();
      virtual void install_deps();
#endif

#ifdef MACOS

      virtual void install_xcode();

#endif

#ifdef LINUX
      virtual void _install_deb();
      virtual void _install_rpm();
      virtual void install_deb();
      virtual void _snap_uninstall(const ::scoped_string& scopedstrPackageName);

      //bool _cloud_defer_check_file_txt(::file::path & pathTarget, const ::file::path & pathCloudFile, bool bForce = false, ::file::path * ppathSource = nullptr);
      //::string_array _cloud_get_file_txt_lines(const ::file::path & pathCloudFile, bool bForce = false, ::file::path * ppathTarget = nullptr, ::file::path * ppathSource = nullptr);
      //bool _dropbox_defer_check_index_files(::file::path & pathSource, const ::scoped_string & scopedstrDropboxFolder);

      //::file::path _cloud_ensure_file_txt_is_up_to_date_and_present(const ::file::path & pathCloudFile);
      //::file::path _cloud_ensure_files_in_file_txt_are_up_to_date_and_present(
              //const ::file::path & pathCloudFile, const ::scoped_string & scopedstrFileExtension, int iMinimumFileSize);

#endif

      //void wait_dropbox_up_and_running();

      //void wait_cloud_data_provider_up_and_running();

      //void defer_setup_dropbox();

      //void defer_setup_cloud_data_provider();

#ifdef WINDOWS
      virtual void install_edge();
      virtual void install_opera_browser();
      virtual void install_exe();
      virtual ::string _install_exe(const ::file::path& path);
#endif

      //virtual void install_clion();

      ::file::path get_download_url(::string& strName);


      // virtual void install_graphical_ide();
      virtual void install_graphical_ide();

      virtual void install_git_scm();

      virtual void install_setup_folders();
      virtual void install_user_ssh_keys();
      virtual void install_patch_shell();


#if JETBRAINS_CLION
      virtual void install_jetbrains_clion();
      virtual void install_jetbrains_toolbox();
#endif



#ifdef WINDOWS_DESKTOP

      virtual void install_visual_studio();

      virtual bool has_visible_top_level_window_named_visual_studio_installer();

      virtual bool has_visible_top_level_window_named_simple__microsoft_visual_studio();

      virtual void install_msys2();

      virtual void install_strawberry_perl();

      virtual void _run_msi_exec();

      virtual void _on_after_msi_exec();

      virtual void install_tortoise_git();

#endif

///      virtual void on_update_install_status();

      virtual bool get_debug_project_enabled();

      virtual ::string get_name();
      virtual ::string get_title();
      virtual ::string get_remark();

#if !defined(WINDOWS_DESKTOP)
      virtual ::string get_latest_git_credential_manager_download_url();
#endif

      virtual void wait_dependencies();

   };


} // namespace coding


