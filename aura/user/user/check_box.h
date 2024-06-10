#pragma once


#include "interaction.h"
#include "acme/user/user/check.h"


namespace user
{


   class CLASS_DECL_AURA check_box :
      virtual public ::user::interaction,
      virtual public ::user::check
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
      class ::time                 m_timeAnimationStart;
      double               m_dPosition;
      class ::time                 m_timeAnimationPeriod;


      check_box(e_style estyle = style_normal);
      ~check_box() override;

      
      ::particle_pointer clone() override;


      enum_element get_default_element() override;


      void _001OnNcDraw(::draw2d::graphics_pointer& pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDrawNormal(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawRedGreenCircle(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawToggleSwitch(::draw2d::graphics_pointer & pgraphics);
//      virtual ::enum_check get_check() override;
      //using ::user::interaction::set_check;
      //using check::set_check;
      //void set_check(const ::e_check & check, const ::action_context & action_context) override;

      void on_check_changed(::data::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext) override;


      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      bool on_click(::item * pitem) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      virtual void _001OnTimer(::timer * ptimer) override;

   };


} // namespace user



