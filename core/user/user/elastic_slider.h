#pragma once


namespace user
{


   class CLASS_DECL_CORE elastic_slider :
      public ::user::interaction

   {
   public:



      scalar_base *  m_pscalarVelocity;
      scalar_base *  m_pscalarPosition;

      e_scalar       m_escalar;

      tick m_tickLastTime;

      double         m_dPosition;// 0.0 = min 1.0 = max
      double         m_dTensionPosition;// 0.0 = min 1.0 = max
      bool           m_bSlide;
      index          m_iScalar;
      double_array   m_daScalar;


      elastic_slider();
      virtual ~elastic_slider();


      virtual void install_message_routing(::channel * pchannel);

      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      void Slide();




      void SetStreamingVelocityMode(scalar_base * pscalarVelocity, scalar_base * pscalarPosition);


      void UpdatePosition();
      void CalcTension(point & point);
      void SetSliderPos(double dPos);

      double CalcScalar();
      void CalcTension();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      double GetForce();

      void GetSliderRect(::rect & rect);


   };


} // namespace user



