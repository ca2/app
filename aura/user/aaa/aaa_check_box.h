#pragma once


namespace user
{


   class CLASS_DECL_AURA check_box :
      virtual public ::user::interaction
   {
   public:




      enum e_style
      {

         style_normal,
         style_red_green_circle,
         style_toggle_switch,

      };

   protected:


      //::enum_check     m_echeck;
      bool                 m_bMouseDown;


   public:


      e_style              m_estyle;
      ::duration                 m_durationAnimationStart;
      double               m_dPosition;
      ::duration                 m_durationAnimationPeriod;


      check_box(e_style estyle = style_normal);
      virtual ~check_box();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDrawNormal(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawRedGreenCircle(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawToggleSwitch(::draw2d::graphics_pointer & pgraphics);
//      virtual ::enum_check get_check() override;
      //using ::user::interaction::set_check;
      virtual void set_check(::enum_check check, const ::action_context & action_context) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::topic * ptopic, ::handler_context * pcontext) override;

      virtual bool on_click(::item * pitem) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      virtual void on_timer(::timer * ptimer) override;

   };


} // namespace user



