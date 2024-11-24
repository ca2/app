#pragma once


#include "aura/user/user/interaction.h"


namespace account
{


   class dialog :
      virtual public ::user::interaction
   {
   public:


      ::collection::index                               m_iDelay;
      ::int_rectangle                              m_rectangleFontopus;

      ::pointer<::account::credentials>m_pcredentials;

      ::pointer<login>                 m_plogin;
      bool                                m_bLButtonDown;
      int_point                               m_pointLButtonDown;
      int_point                               m_pointLButtonDownPos;

      bool                                m_bDrag;
      bool                                m_bFontopusSimpleUiLayout;
      ::int_rectangle                              m_rectangleParent;

      dialog **                           m_psimpleuiDeferTranslate;



      dialog();
      virtual ~dialog();


      virtual void initialize_account_dialog(::account::credentials * pcredentials);

      virtual void get_credentials();



      virtual void do_modal(::int_rectangle rectangle);

      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_character);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      void on_timer(::timer * ptimer) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

      //bool has_pending_graphical_update() override;

   };


} // namespace account




