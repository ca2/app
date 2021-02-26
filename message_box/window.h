#pragma once


namespace app_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX_APP window :
      virtual public ::user::main_window
   {
   public:


      double                        m_dBreathPeriod;
      millis                        m_millisStart;
      double                        m_dPhaseShift;
      int                           m_iCloseButtonDraw;
      __pointer(::user::button)     m_pbuttonShowMessageBox;


      window();
      virtual ~window();


      virtual void on_create_user_interaction() override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item* pitem) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_control_event(::user::control_event * pevent) override;



   };


} // namespace app_message_box












