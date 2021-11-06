#pragma once



namespace account
{


   class dialog :
      virtual public ::user::interaction
   {
   public:


      index                               m_iDelay;
      ::rectangle_i32                              m_rectangleFontopus;

      __reference(::account::credentials) m_pcredentials;

      __composite(login)                  m_plogin;
      bool                                m_bLButtonDown;
      point_i32                               m_pointLButtonDown;
      point_i32                               m_pointLButtonDownPos;

      bool                                m_bDrag;
      bool                                m_bFontopusSimpleUiLayout;
      ::rectangle_i32                              m_rectangleParent;

      dialog **                           m_psimpleuiDeferTranslate;



      dialog();
      virtual ~dialog();


      virtual ::e_status initialize_account_dialog(::account::credentials * pcredentials);

      virtual void get_credentials();



      virtual void do_modal(::rectangle_i32 rectangle);

      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_character);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      void _001OnTimer(::timer * ptimer) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace account




