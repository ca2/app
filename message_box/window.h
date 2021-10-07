#pragma once


namespace app_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX_APP window :
      virtual public ::user::main_window
   {
   public:


      double                        m_dBreathPeriod;
      ::duration                        m_durationStart;
      double                        m_dPhaseShift;
      int                           m_iCloseButtonDraw;
      __pointer(::user::button)     m_pbuttonShowMessageBox;


      window();
      virtual ~window();


      virtual void on_create_user_interaction() override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual void show_message_box();


   };


} // namespace app_message_box












