#pragma once


#include "base/user/experience/button.h"


namespace experience_core
{


   class CLASS_DECL_APP_EXPERIENCE_CORE control_box_button :
      virtual public ::experience::button
   {
   public:




      control_box_button();
      ~control_box_button() override;


      //virtual ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      void _001OnNcClip(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void install_message_routing(::channel * pchannel) override;


      void _001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool keyboard_focus_is_focusable() override;


   };


} // namespace experience



