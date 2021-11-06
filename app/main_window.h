#pragma once


namespace app_app
{


   class CLASS_DECL_APP_APP_APP main_window :
      virtual public ::user::main_window
   {
   public:


      double      m_dBreathPeriod;
      ::duration      m_durationStart;
      double      m_dPhaseShift;
      int         m_iCloseButtonDraw;


      main_window();
      ~main_window() override;


      //bool is_frame_window() override;


      virtual void on_create_user_interaction() override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem) override;


   };


} // namespace app_app












