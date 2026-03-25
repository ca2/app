// Changed from integration_code/application to coding/code_application by
// camilo on 2026-03-22 03:41 <3ThomasBorregaardSørensen!!
#pragma once


#include "coding/application.h"


namespace coding
{

   class impact;

   class CLASS_DECL_CODING code_application :
      virtual public ::coding::application
   {
   public:


      //::data::check_property                 m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization;

      bool                                   m_bLastDeferReleaseInstallInstalling;
      ::string                               m_strGraphicalIdeName;
      ::user::document *                     m_pdocMenu;
      //::user::single_document_template *     m_ptemplateCodeMain;
      //::string_map < impact * >              m_impactmap;

      //bool                                   m_bInstalling;
      ::coding::tab_impact *       m_pcodetabimpact;

      string_to_string                       m_mapSource;
      ::file::path                           m_pathSvn;
      //bool                                   m_bSvnInstalled;
      bool                                   m_bSourceOk;
      //bool                                   m_bGraphicalIdeOk;
      //bool                                   m_bInstallingGraphicalIde;
      ::file::path                           m_pathCode;
      ::file::path                           m_pathApplicationBuildHelper;
      ::file::path                           m_pathApplicationBuildHelperZip;

      ::string                               m_strDistro;
      ::string                               m_strSlashedOperatingSystem;

      //::coding::enum_mode          m_emode;


      ::coding::code_map           m_codemap;


      ::string                               m_strToolOsStatus;
      ::string                               m_strToolOsStatus2;

      ::string                               m_strAppSimpleStatus;
      ::string                               m_strAppSimpleStatus2;

      //::string                               _m_strFirstStageStatus;

      ::string                               _m_strGraphicalIdeStatus;
      ::string                               _m_strGraphicalIdeStatus2;

      ::string                               _m_strGitScmStatus;
      ::string                               _m_strGitScmStatus2;

      ::string                               _m_strTortoiseGitStatus;
      ::string                               _m_strTortoiseGitStatus2;

      ::string                               _m_strSmartGitStatus;
      ::string                               _m_strSmartGitStatus2;

      ::string                               m_strBinariesStatus;
      ::string                               m_strBinariesStatus2;

      //bool                                   m_bInstallingGit;
      //bool                                   m_bInstallingTortoiseGit;
      bool                                   m_bFirstStageOk;

      ::pointer < ::parallelization::queue > m_pqueueSystemInstall;
      ::pointer < ::parallelization::queue > m_pqueueDownload;


      //::pointer<::user::check_box>              m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization;
      //::pointer<::user::still>                  m_pstillExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization;


      code_application();
      ~code_application() override;


      //__DECLARE_APPLICATION_RELEASE_TIME();


      virtual void on_request(::request * prequest) override;


      ::coding::code * code(const ::coding::e_mode & emode);

      ::coding::code * code() override;

      virtual string preferred_experience() override;
      virtual void init_instance() override;
      virtual void term_application() override;


      //void on_change_current_cloud_data_provider(const ::action_context& actioncontext);
      //void on_change_current_browser(const ::action_context & actioncontext);
      //void on_change_current_repository(const ::action_context& actioncontext);


      //::file::path cloud_folder() override;
      //::atom current_fs_folder_sync_provider() override;
      //::string current_browser() override;

      virtual bool has_Dropbox_folder();


      //void create_options_impact(const ::atom & atom, ::user::interaction * pparent) override;


      bool defer_first_stage();
      void wait_first_stage();
      bool does_need_code_exe_relocation();
      bool defer_relocate_code_exe();
      bool _defer_relocate_code_exe();
      bool is_application_build_helper_ok();
      bool defer_application_build_helper();
      bool defer_initial_ambient_setup();

      ::e_status application_build_helper_initial_ambient_setup(bool bSystemNotifyIfNeeded);

      virtual void post_impact_redraw();

      void on_installed(::coding::enum_install einstall, bool bJustInstalled) override;
      bool is_installing();

      bool is_install_selected(::coding::enum_install einstall);
      //void _install_graphical_ide();
      bool can_start_installing();


      virtual bool calculate_enable(::coding::enum_install einstall);

      virtual void code_on_change_selection();

      //int unix_shell_command(const ::scoped_string& scopedstrCommand);
      //bool has_unix_shell_command(const ::scoped_string& scopedstrCommand);
      //bool is_git_installed(int iAttempt = 0);
      // bool is_tortoise_git_insftalled(int iAttempt = 0);
      //void set_status1(string strStatus);
      //void set_status2(string strStatus);
      void defer_release_install();
      //void release_source();

      void start_install_graphical_ide();

      virtual void start_debugging_project();
      void update_debug_project_enable();

      bool get_debug_project_enable();


      //void install_on_checkbox(::user::check* pcheck) override;


      void set_code_mode(const ::coding::e_mode & emode) override;
      ::coding::e_mode get_code_mode() override;


      ::coding::e_mode as_emode(const ::scoped_string & scopedstr);
      ::string as_string(const ::coding::e_mode & emode);


   };


} // namespace coding



