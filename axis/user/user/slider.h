#pragma once


#include "aura/user/user/interaction.h"
#include "acme/prototype/mathematics/scalar.h"


namespace user
{


   class CLASS_DECL_AXIS slider:
      virtual public ::user::interaction
   {
   public:


      ::number::scalar        m_scalar;

      double                  m_dRate;

      bool                    m_bSlide;

      
      slider();
      ~slider() override;


      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

      void on_timer(::timer * ptimer) override;
      
      void set_scalar(const ::number::scalar & scalar);

      void set_rate(double dRate);

      double get_slide_rate();

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void get_slider_rect(::int_rectangle & rectangle);

   };


} // namespace user




































































