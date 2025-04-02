#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_CORE color_combo_box :
      virtual public ::user::interaction
   {
   public:


      ::pointer < ::user::color_selector_popup >   m_pcolorselectorpopup;
      bool                                         m_bMouseDown;
      ::color::hls                                 m_hls;


      color_combo_box();
      ~color_combo_box() override;


      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();



      void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::handler_context * pcontext) override;


   };


} //  namespace user



