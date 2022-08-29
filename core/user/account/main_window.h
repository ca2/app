#pragma once


#include "aura/user/user/main_window.h"


namespace account
{


   class main_window :
      virtual public ::user::main_window
   {
   public:


      __reference(::account::credentials)    m_pcredentials;

      __pointer(::account::style)            m_pstyle;
      __composite(login)                     m_plogin;
      bool                                   m_bFontopusSimpleUiLayout;
      ::rectangle_i32                        m_rectangleParent;

      main_window **                         m_psimpleuiDeferTranslate;



      main_window();
      virtual ~main_window();


      virtual void initialize_simple_ui(::account::credentials * pcredentials);


      virtual string get_cred(const ::rectangle_i32 & rectangle, string & strUsername, string & strPassword, string strToken, string strTitle);

      virtual string do_account(const ::rectangle_i32 & rectangle);

      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_character);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      void _001OnTimer(::timer * ptimer) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace account




