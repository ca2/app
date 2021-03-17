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
      virtual ~slider();


      virtual void install_message_routing(::channel * pchannel);

      DECL_GEN_SIGNAL(on_message_create);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(on_message_mouse_move);

      void set_scalar(scalar_base * pscalar);

      void set_rate(double dRate);

      double get_slide_rate();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void get_slider_rect(::rectangle_i32 & rectangle);

   };


} // namespace user




































































