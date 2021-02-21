#pragma once



namespace account
{


   class simple_ui :
      virtual public ::simple_ui::top
   {
   public:


      __reference(::account::credentials)    m_pcredentials;


      __composite(login)                     m_plogin;
      bool                                   m_bFontopusSimpleUiLayout;
      ::rectangle_i32                                 m_rectParent;

      simple_ui **                           m_psimpleuiDeferTranslate;



      simple_ui();
      virtual ~simple_ui();


      virtual ::e_status initialize_simple_ui(::account::credentials * pcredentials);


      virtual string get_cred(const ::rectangle_i32 & rectangle, string & strUsername, string & strPassword, string strToken, string strTitle);

      virtual string do_account(const ::rectangle_i32 & rectangle);

      void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      void _001OnTimer(::timer * ptimer) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace account




