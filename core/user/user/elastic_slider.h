#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_CORE elastic_slider :
      public ::user::interaction

   {
   public:



      scalar_base *  m_pscalarVelocity;
      scalar_base *  m_pscalarPosition;

      e_scalar       m_escalar;

      ::duration m_durationLastTime;

      double         m_dPosition;// 0.0 = minimum 1.0 = maximum
      double         m_dTensionPosition;// 0.0 = minimum 1.0 = maximum
      bool           m_bSlide;
      index          m_iScalar;
      double_array   m_daScalar;


      elastic_slider();
      virtual ~elastic_slider();


      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);


      void Slide();




      void SetStreamingVelocityMode(scalar_base * pscalarVelocity, scalar_base * pscalarPosition);


      void UpdatePosition();
      void CalcTension(point_i32 & point);
      void SetSliderPos(double dPos);

      double CalcScalar();
      void CalcTension();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      double GetForce();

      void GetSliderRect(::rectangle_i32 & rectangle);


   };


} // namespace user



