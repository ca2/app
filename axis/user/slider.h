#pragma once


namespace user
{


   class CLASS_DECL_AXIS slider:
      virtual public ::user::interaction
   {
   public:


      scalar_base *  m_pscalar;

      double         m_dRate;

      bool           m_bSlide;

      
      slider();
      ~slider() override;


      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

      void _001OnTimer(::timer * ptimer) override;
      
      void set_scalar(scalar_base * pscalar);

      void set_rate(double dRate);

      double get_slide_rate();

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void get_slider_rect(::rectangle_i32 & rectangle);

   };


} // namespace user




































































