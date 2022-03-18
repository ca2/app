#pragma once


namespace experience_anthill
{


   class CLASS_DECL_APP_EXPERIENCE_ANTHILL control_box :
      virtual public ::experience::control_box
   {
   public:


      control_box();
      ~control_box() override;


      void set_button_color_system_default_001() override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      void _001OnTimer(::timer * ptimer) override;


   };


} // namespace experience_anthill




