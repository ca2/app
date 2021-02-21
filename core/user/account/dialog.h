#pragma once



namespace account
{


   class dialog :
      virtual public ::user::interaction,
      virtual public ::simple_ui::style
   {
   public:


      index                               m_iDelay;
      ::rectangle_i32                              m_rectFontopus;

      __reference(::account::credentials) m_pcredentials;

      __composite(login)                  m_plogin;
      bool                                m_bLButtonDown;
      point_i32                               m_pointLButtonDown;
      point_i32                               m_pointLButtonDownPos;

      bool                                m_bDrag;
      bool                                m_bFontopusSimpleUiLayout;
      ::rectangle_i32                              m_rectParent;

      dialog **                           m_psimpleuiDeferTranslate;



      dialog();
      virtual ~dialog();


      virtual ::e_status initialize_account_dialog(::account::credentials * pcredentials);

      virtual void get_credentials();



      virtual void do_modal(::rectangle_i32 rectangle);

      void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      void _001OnTimer(::timer * ptimer) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace account




