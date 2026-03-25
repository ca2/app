// Created as main_item.h by camilo on 2024-04-27 22:43 <3ThomasBorregaardSorensen!!
// From main_item.h by camilo on 2024-04-27 22:50 <3ThomasBorregaardSorensen!!
// From install_base.h by camilo on 2024-04-27 22:58 <3ThomasBorregaardSorensen!!
// Here remains ui concern by camilo on 2024-05-04 04:11 <3ThomasBorregaardSorensen!!
#pragma once

#include "code_application.h"
#include "apex/platform/app_consumer.h"
#include "berg/user/user/form_handler.h"
#include "berg/user/user/impact.h"
#include "coding/install_impact_interface.h"
#include "coding/install_log_interface.h"


namespace coding
{


   class CLASS_DECL_CODING install_form_handler :
      virtual public app_consumer < ::coding::code_application, ::berg::form_handler, ::coding::install_impact_interface, ::coding::install_log_interface >
   {
   public:


      ::pointer < ::coding::install >   m_pinstall;

      ::pointer < ::coding::code > m_pcode;


      //enum_install                        m_einstall;
      //bool                                m_bInstalling;


      //::file::path                        m_path;
      //int                                 m_iTry;
      //int                                 m_iTryCount;


      //::string                            m_strStatus;
      //::string                            m_strStatus2;


      ::pointer < ::user::line_layout >   m_plinelayout;
      ::pointer < ::user::still >         m_pstillTitle;
      ::pointer < ::user::still >         m_pstillRemark;
      ::pointer < ::user::still >         m_pstillStatus;
      ::pointer < ::user::check_box >     m_pcheckbox;
      //::pointer < ::user::still >         m_pstillCheckBox;


      install_form_handler();
      ~install_form_handler() override;


      void create_install_form_handler(::coding::code * pcode, ::coding::install * pinstall, ::user::interaction* puserinteractionParent);


      //virtual void run_normal_install();

      void on_finished() override;

      void start_installation(int iTryCount) override;

      virtual void defer_start_installation() override;

      void update_title() override;

      void install_status(::coding::install * pinstall, const ::scoped_string& scopedstr) override;
      void install_status2(::coding::install* pinstall, const ::scoped_string& scopedstr) override;
      void install_append_status2(::coding::install* pinstall, const ::scoped_string& scopedstr) override;

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

      

      //::file::path get_download_url(::string & strName);


      // virtual void install_graphical_ide();
      //virtual void install_graphical_ide();
//     
//#ifdef WINDOWS_DESKTOP
//
//      virtual void install_visual_studio();
//
//      virtual bool has_visible_top_level_window_named_visual_studio_installer();
//
//      virtual bool has_visible_top_level_window_named_simple__microsoft_visual_studio();
//
//#endif

      void on_update_install_status(::coding::install* pinstall) override;

      //virtual bool get_debug_project_enabled();

      bool is_selected() override;

      void select() override;

      void unselect() override;

      void disable_selection() override;

      void enable_selection() override;

      void hide_selection() override;

      void enable_window(bool bEnable = true) override;

      bool has_check() override;

      bool has_check(::user::check* pcheck) override; 


   };


} // namespace coding


