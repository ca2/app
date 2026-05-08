#pragma once


#include "apex/platform/app_consumer.h"
#include "berg/user/user/impact.h"
#include "impact_interface.h"
#include "install_log_interface.h"


namespace coding
{


   class CLASS_DECL_CODING impact :
      virtual public ::app_consumer < application, ::user::impact, impact_interface, install_log_interface >
   {
   public:

      enum
      {
         check_box_base = 1000,
         still_base = 2000,
         still_status_base = 4000,
         still_elapsed_base = 5000,
      };


      int                                    m_iLeftMargin;
      int                                    m_iLeftWidth;
      int                                    m_yStart;
      
      ::pointer<::user::plain_edit>          m_pplaineditRepositoryPath;
      ::pointer<::user::button>              m_pbuttonBrowseRepositoryPath;
      ::pointer_array<::user::button>        m_buttonaHandlePulseCallIntegration;

      
      ::pointer<::user::button>             m_pbuttonStart;
      ::pointer<::user::still>              m_pstillFinished;
      ::pointer<::user::still>              m_pstillTopic1;
      ::pointer<::user::still>              m_pstillTopic12;
      ::pointer<::user::list_box>           m_plistTaskGroup;
      ::pointer<::write_text::font>         m_pfontNormal;
      ::pointer<::write_text::font>         m_pfontFinished;
      ::pointer<::write_text::font>         m_pfontTopic;
      ::pointer<::write_text::font>         m_pfontTopic2;
      ::pointer<::write_text::font>         m_pfontBold;

      ::pointer<::write_text::font>         m_pfontStatus;
      ::pointer<::write_text::font>         m_pfontElapsed;



      impact();
      ~impact() override;

      void install_message_routing(::channel* pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

#if defined(WINDOWS)
      void prepare_windows();
#endif

      //bool update_impact() override;

      virtual void defer_auto_start_integration();

      void handle(::topic* ptopic, ::handler_context* phandlercontext) override;
      
      
      virtual void set_repository_path(const ::scoped_string & scopedstr);


      void on_start_task_group(enum_task etaskGroup) override;

      virtual task_group* displaying_task_group();
      
//#ifdef _DEBUG
//      // void assert_ok() const override;
//      void dump(dump_context& dumpcontext) const override;
//#endif

      document * get_document();

      void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;

      string get_windows_prompt();

      void on_integrate_change() override;

      void on_lines_change() override;

      void enable_pulse(const ::scoped_string& scopedstr) override;

      virtual void update_elapsed_still();

      void start();

      void set_topic_text(const ::scoped_string& scopedstr) override;

      void set_topic_text2(const ::scoped_string& scopedstr) override;



      void on_timer(::timer * ptimer) override;


      void on_perform_top_down_layout(::draw2d::graphics_pointer& pgraphics) override;

      void install_status(install* pinstall, const ::scoped_string& scopedstr) override;
      void install_status2(install* pinstall, const ::scoped_string& scopedstr) override;
      void install_append_status2(install* pinstall, const ::scoped_string& scopedstr) override;


      void on_update_install_status(install* pinstall) override;

      void defer_select_sequential_task_ordinal(enum_task etaskOrdinal) override;

      void defer_select_main_impact() override;


   };


} // namespace coding



