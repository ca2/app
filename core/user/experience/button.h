#pragma once


namespace experience
{


   class  CLASS_DECL_CORE button :
      virtual public ::user::button
   {
   public:


      e_button             m_ebutton;
      control_box *        m_pcontrolbox;


      button();
      virtual ~button();


      virtual void install_message_routing(::channel* pchannel) override;

      virtual void UpdateWndRgn();


      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


      DECL_GEN_SIGNAL(_001OnLButtonDown);

      virtual bool keyboard_focus_is_focusable() override;


   };


} // namespace experience


