#pragma once


#include "aura/user/user/button.h"


namespace experience
{


   class  CLASS_DECL_BASE button :
      virtual public ::user::button
   {
   public:


      enum_button                   m_ebutton;
      ::pointer<control_box>       m_pcontrolbox;
      ::draw2d::region_pointer      m_pregion;


      button();
      ~button() override;


      void install_message_routing(::channel* pchannel) override;

      bool should_draw() override;

      ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

      virtual void UpdateWndRgn();

      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      bool keyboard_focus_is_focusable() override;


   };


} // namespace experience


