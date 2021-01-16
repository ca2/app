#pragma once



namespace account
{


   class dialog :
      virtual public ::user::interaction,
      virtual public ::simple_ui::style
   {
   public:


      index                               m_iDelay;
      ::rect                              m_rectFontopus;

      __reference(::account::credentials) m_pcredentials;

      __composite(login)                  m_plogin;
      bool                                m_bLButtonDown;
      point                               m_pointLButtonDown;
      point                               m_pointLButtonDownPos;

      bool                                m_bDrag;
      bool                                m_bFontopusSimpleUiLayout;
      ::rect                              m_rectParent;

      dialog **                           m_psimpleuiDeferTranslate;



      dialog();
      virtual ~dialog();


      virtual ::e_status initialize_account_dialog(::account::credentials * pcredentials);

      virtual void get_credentials();



      virtual void do_modal(::rect rect);

      void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      void _001OnTimer(::timer * ptimer) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace account




