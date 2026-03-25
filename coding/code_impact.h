#pragma once


#include "code_application.h"
#include "apex/platform/app_consumer.h"
#include "berg/user/user/form_handler.h"
#include "berg/user/user/impact.h"


namespace coding
{



   class CLASS_DECL_CODING impact :
      virtual public app_consumer < ::coding::code_application, ::user::impact, ::berg::form_handler >
   {
   public:


      ::write_text::font_pointer m_pfontTitle;
      ::write_text::font_pointer m_pfont;
      ::write_text::font_pointer m_pfontTitleInstance;
      ::write_text::font_pointer m_pfontInstance;

      ::pointer < ::coding::code > m_pcode;

      //::pointer < ::user::button >     m_pbuttonDebugProject;

      ::pointer < ::user::button >        m_pbuttonStart;
      ::pointer < ::user::button >        m_pbuttonLaunchSolution;
      ::pointer < ::user::button >        m_pbuttonOpenSolutionFolder;
      ::pointer < ::user::button >        m_pbuttonOpenBaseFolder;

      ::pointer < ::user::still >         m_pstillCodeTitle;
      ::pointer < ::user::still >         m_pstillMainRemark;
      ::pointer < ::user::still >         m_pstillMainStatus1;
      ::pointer < ::user::still >         m_pstillMainStatus2;


      /*::pointer < ::user::still >         m_pstillVisualStudioTitle;
      ::pointer < ::user::still >         m_pstillVisualStudioRemark;
      ::pointer < ::user::still >         m_pstillVisualStudioStatus;
      ::pointer < ::user::check_box >     m_pcheckboxVisualStudio;

      ::pointer < ::user::still >         m_pstillGitScmTitle;
      ::pointer < ::user::still >         m_pstillGitScmRemark;
      ::pointer < ::user::still >         m_pstillGitScmStatus;
      ::pointer < ::user::check_box >     m_pcheckboxGitScm;


      ::pointer < ::user::still >         m_pstillTortoiseGitTitle;
      ::pointer < ::user::still >         m_pstillTortoiseGitRemark;
      ::pointer < ::user::still >         m_pstillTortoiseGitStatus;
      ::pointer < ::user::check_box >     m_pcheckboxTortoiseGit;

      ::pointer < ::user::still >         m_pstillSmartGitTitle;
      ::pointer < ::user::still >         m_pstillSmartGitRemark;
      ::pointer < ::user::still >         m_pstillSmartGitStatus;
      ::pointer < ::user::check_box >     m_pcheckboxSmartGit;

      ::pointer < ::user::still >         m_pstillToolOsTitle;
      ::pointer < ::user::still >         m_pstillToolOsRemark;
      ::pointer < ::user::still >         m_pstillToolOsStatus;
      ::pointer < ::user::check_box >     m_pcheckboxToolOs;


      ::pointer < ::user::still >         m_pstillAppSimpleTitle;
      ::pointer < ::user::still >         m_pstillAppSimpleRemark;
      ::pointer < ::user::still >         m_pstillAppSimpleStatus;
      ::pointer < ::user::check_box >     m_pcheckboxAppSimple;*/

      ::file::path m_pathReleaseInstall;


      int m_iAllButtonsHeight;
      int m_iButtonHeight;
      int m_iButtonPadding;
      int m_iButtonCount;

      ::data::property     m_propertyMainRemark;

      ::pointer < ::user::line_layout >      m_plinelayoutMainColumn;

      impact();
      virtual ~impact();


      bool is_initial_setup() const;
      bool is_gcm() const;
      bool is_ssh() const;
      bool is_std() const;

      virtual void update_main_remark(const ::action_context & actioncontext);

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG
      virtual ::collection::index increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      virtual ::collection::index decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }
#endif

      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      ::user::document * get_document();

      void create_main_screen(::user::interaction* puserinteractionParent);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


      void create_release_install_buttons(::user::interaction * puserinteractionParent);

      void defer_enable_release_install();


      
      void update_start_button();


   };


} // namespace coding


