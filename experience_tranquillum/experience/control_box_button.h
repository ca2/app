#pragma once


#include "base/user/experience/button.h"


namespace experience_tranquillum
{


   class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM control_box_button :
      virtual public ::experience::button
   {
   public:


      ::draw2d::region_pointer                 m_spregion;
      ::draw2d::pen_pointer                    m_ppen;
      ::draw2d::brush_pointer                  m_pbrush;


      control_box_button();
      ~control_box_button() override;


      virtual ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics)override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      
      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      bool keyboard_focus_is_focusable() override;


   };


} // namespace experience_tranquillum



