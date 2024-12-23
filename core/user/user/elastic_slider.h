#pragma once


#include "aura/user/user/interaction.h"
#include "acme/prototype/mathematics/scalar.h"


namespace user
{


   class CLASS_DECL_CORE elastic_slider :
      public ::user::interaction

   {
   public:



      ::pointer < scalar >          m_pscalarVelocity;
      ::pointer < scalar >          m_pscalarPosition;

      enum_scalar                   m_escalar;

      class ::time                    m_timeLastTime;

      double                        m_dPosition;// 0.0 = minimum 1.0 = maximum
      double                        m_dTensionPosition;// 0.0 = minimum 1.0 = maximum
      bool                          m_bSlide;
      ::collection::index                         m_iScalar;
      double_array                  m_daScalar;


      elastic_slider();
      virtual ~elastic_slider();


      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void on_timer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);


      void Slide();




      void SetStreamingVelocityMode(scalar * pscalarVelocity, scalar* pscalarPosition);


      void UpdatePosition();
      void CalcTension(int_point & point);
      void SetSliderPos(double dPos);

      double CalcScalar();
      void CalcTension();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      double GetForce();

      void GetSliderRect(::int_rectangle & rectangle);


   };


} // namespace user



