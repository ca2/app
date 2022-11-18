#pragma once


#include "aura/user/user/interaction.h"
#include "acme/primitive/mathematics/scalar.h"


namespace user
{


   class CLASS_DECL_CORE step_slider :
      public ::user::interaction
   {
   public:


      scalar       m_scalar;


      step_slider();
      ~step_slider() override;

      
      //bool create_window(::user::interaction * puserinteractionParent, atom atom);


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void GetStepHoverRect(RECTANGLE_I32 * prectangle, i64 iVal, i64 iMin, i64 iMax, const ::rectangle_i32 & rectangleClient);

      void GetStepRect(RECTANGLE_I32 * prectangle, i64 iVal, i64 iMin, i64 iMax, const ::rectangle_i32 & lpcrectClient);


      ::item_pointer on_hit_test(const ::point_i32 & point) override;

      //void update_hover();


      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   };

} // namespace user
