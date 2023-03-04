#pragma once


#include "base/user/experience/control_box.h"


namespace experience_nanoui
{


      class CLASS_DECL_APP_EXPERIENCE_CORE control_box :
         virtual public ::experience::control_box
      {
      public:


         control_box();
         ~control_box() override;


         void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
         void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         void install_message_routing(::channel *pframewindow) override;


         DECLARE_MESSAGE_HANDLER(on_message_show_window);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
         void _001OnTimer(::timer * ptimer) override;


         i32 calc_button_size(::draw2d::graphics_pointer & pgraphics) override;
         ::rectangle_i32 get_button_margin(::experience::enum_button ebutton) override;


      };


} // namespace experience_nanoui



