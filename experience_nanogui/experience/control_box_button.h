#pragma once


#include "base/user/experience/button.h"


namespace experience_nanoui
{


   class CLASS_DECL_APP_EXPERIENCE_CORE control_box_button :
      virtual public ::experience::button
   {
   public:



      control_box_button();
      ~control_box_button() override;


      //virtual ::item_pointer on_hit_test(const ::point_i32 & point) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void install_message_routing(::channel * pchannel) override;



      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool keyboard_focus_is_focusable() override;


   };


} // namespace experience_nanoui



