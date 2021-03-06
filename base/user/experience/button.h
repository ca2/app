#pragma once


namespace experience
{


   class  CLASS_DECL_BASE button :
      virtual public ::user::button
   {
   public:


      enum_button                   m_ebutton;
      __pointer(control_box)        m_pcontrolbox;
      ::draw2d::region_pointer      m_pregion;



      button();
      virtual ~button();


      virtual void install_message_routing(::channel* pchannel) override;

      virtual void on_hit_test(::user::item & item) override;

      virtual void UpdateWndRgn();

      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);

      virtual bool keyboard_focus_is_focusable() const override;


   };


} // namespace experience


