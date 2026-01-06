#pragma once


#include "aura/user/user/interaction.h"
#include "acme/prototype/mathematics/scalar.h"


namespace user
{


   class CLASS_DECL_CORE step_slider :
      public ::user::interaction
   {
   public:


      ::number::scalar        m_scalar;


      step_slider();
      ~step_slider() override;

      
      //bool create_window(::user::interaction * puserinteractionParent, atom atom);


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void GetStepHoverRect(::int_rectangle * prectangle, long long iVal, long long iMin, long long iMax, const ::int_rectangle & rectangleX);

      void GetStepRect(::int_rectangle * prectangle, long long iVal, long long iMin, long long iMax, const ::int_rectangle & lpcrectClient);


      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;

      //void update_hover();


      DECLARE_MESSAGE_HANDLER(on_message_create);
      void on_timer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   };

} // namespace user
