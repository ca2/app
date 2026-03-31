// From app_simple_application/impact.h to app_simple_about_the_operationg_system/main_impact.h by
//    camilo on 2026-03-30 17:50 <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "berg/user/user/impact.h"


namespace berg
{


   class CLASS_DECL_BERG about_the_operating_system_impact
       : virtual public ::app_consumer<application, ::user::impact>
   {
   public:

      // ::write_text::font_pointer m_pfontThomasBSHeading1;
      // ::write_text::font_pointer m_pfontThomasBS_;
      // ::write_text::font_pointer m_pfontThomasBSDetail;
      ::map_base < ::enum_simple_dialog_style, ::write_text::font_pointer > m_mapFontThomasBS_;
      //string m_strFont1;
      int m_iSequence;


      about_the_operating_system_impact();
      ~about_the_operating_system_impact() override;

      //      // void assert_ok() const override;
      //      // void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
#endif

      virtual ::write_text::font * get_font(::simple_dialog_box_line * psimpledialogboxline);

      virtual void install_message_routing(::channel *psender) override;

      virtual void _001OnClip(::draw2d::graphics_pointer &pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer &pgraphics) override;

      void handle(::topic *ptopic, ::handler_context *phandlercontext) override;

      //document *get_document();

      void on_layout(::draw2d::graphics_pointer &pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


      bool on_click(::item *pitem, ::user::mouse *pmouse) override;
   };


} // namespace app_simple_application
