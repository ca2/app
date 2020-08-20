#pragma once


namespace app_app
{


   class CLASS_DECL_APP_APP_APP window :
      virtual public ::user::main_window
   {
   public:


      double      m_dBreathPeriod;
      double      m_dStartTime;
      //double      m_dLastTime;
      double      m_dPhaseShift;


      window();


      virtual void on_create_user_interaction() override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace app_app












