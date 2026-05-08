// From install.h by camilo on 2024-05-04 05:42 <3ThomasBorregaardSorensen!!
#pragma once


#include "application.h"
#include "apex/platform/app_consumer.h"
#include "berg/user/user/form_handler.h"
#include "berg/user/user/impact.h"


namespace coding
{


   class CLASS_DECL_CODING install_impact_interface :
      virtual public app_consumer < application >
   {
   public:


      //enum_install                        m_einstall;
      //bool                                m_bInstalling;


      //::file::path                        m_path;
      //int                                 m_iTry;
      //int                                 m_iTryCount;


      //::string                            m_strStatus;
      //::string                            m_strStatus2;


      //::pointer < ::user::line_layout >   m_plinelayout;
      //::pointer < ::user::still >         m_pstillTitle;
      //::pointer < ::user::still >         m_pstillRemark;
      //::pointer < ::user::still >         m_pstillStatus;
      //::pointer < ::user::check_box >     m_pcheckbox;
      //::pointer < ::user::still >         m_pstillCheckBox;


      install_impact_interface();
      ~install_impact_interface() override;


      //void create_install(enum_install einstall);
      virtual void update_title();
      virtual bool is_selected();

      virtual void unselect();

      virtual void select();

      virtual void enable_selection();

      virtual void disable_selection();

      virtual void hide_selection();

      virtual void enable_window(bool bEnable = true);

      virtual bool has_check();

      virtual bool has_check(::user::check* pcheck);

      //virtual void run_normal_install();

      virtual void on_finished();

      virtual void start_installation(int iTryCount);

      virtual void defer_start_installation();

      //void set_status(const ::scoped_string& scopedstr);
      //void set_status2(const ::scoped_string& scopedstr);
      //void append_status2(const ::scoped_string& scopedstr);

      //void download();

      //virtual bool has_download_step();

      //virtual void _run_installer();
      //virtual void _run_msi_exec();
      //virtual void _run();

      //virtual bool is_installed(bool bMayAssumeNotInstalled);

      //virtual void install_git_scm();

      //virtual void install_tortoise_git();

      //virtual void install_smart_git();

      //virtual void install_repository();



      //::file::path get_download_url(::string& strName);


      // virtual void install_graphical_ide();
      //virtual void install_graphical_ide();

//#ifdef WINDOWS_DESKTOP
//
//      virtual void install_visual_studio();
//
//      virtual bool has_visible_top_level_window_named_visual_studio_installer();
//
//      virtual bool has_visible_top_level_window_named_simple__microsoft_visual_studio();
//
//#endif

      //virtual void on_update_status();

      //virtual bool get_debug_project_enabled();

      //virtual ::string get_name();
      //virtual ::string get_title();
      //virtual ::string get_remark();


   };


} // namespace coding



