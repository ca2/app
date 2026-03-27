// Created 2024-05-01 03:21 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "berg/user/user/impact.h"
//#include "berg/user/user/options_impact_handler.h"
#include "log_interface.h"



namespace coding
{


   class CLASS_DECL_CODING log_impact :
      virtual public ::app_consumer < application, ::user::impact >
   {
   public:


      enum_task                              m_etaskOrdinal;

      int                                    m_iLeftMargin;
      int                                    m_iLeftWidth;
      int                                    m_yStart;



      ::pointer<::write_text::font>         m_pfontLog;
      ::pointer<::write_text::font>         m_pfontFinished;
      ::pointer<::write_text::font>         m_pfontTopic;
      ::pointer<::write_text::font>         m_pfontTopic2;
      ::pointer<::write_text::font>         m_pfontBold;

      ::pointer<::write_text::font>         m_pfontStatus;
      ::pointer<::write_text::font>         m_pfontElapsed;



      log_impact();
      ~log_impact() override;

      void install_message_routing(::channel* pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

#if defined(WINDOWS)
      void prepare_windows();
#endif

      //bool update_impact() override;


      void handle(::topic* ptopic, ::handler_context* phandlercontext) override;


      virtual log_interface* get_log();


      //#ifdef _DEBUG
      //      // void assert_ok() const override;
      //      void dump(dump_context& dumpcontext) const override;
      //#endif

      document* get_document();

      void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;


      void on_lines_change();


      virtual void update_elapsed_still();



      //void set_topic_text(const ::scoped_string& scopedstr) override;

      //void set_topic_text2(const ::scoped_string& scopedstr) override;



      void on_timer(::timer* ptimer) override;


      void on_perform_top_down_layout(::draw2d::graphics_pointer& pgraphics) override;


   };


} // namespace coding



