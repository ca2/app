#pragma once





namespace account
{


   class CLASS_DECL_CORE login :
      virtual public ::user::interaction
   {
   public:


      __composite(::user::still)             m_pstillUser;
      __composite(::user::plain_edit)        m_peditUser;
      __composite(::user::still)             m_pstillPassword;
      __composite(::user::plain_edit)        m_peditPassword;
      __composite(::user::button)            m_pbutton;
      __composite(::user::button)            m_pbuttonClose;


      string                        m_strUsername;
      string                        m_strPassword;
      strsize                       m_iPasswordOriginalLength;
      
      bool                          m_bSubmitted;
      
      bool                          m_bSelfLayout;
      double                        m_dRateX;
      double                        m_dRateY;

      bool                          m_bCred;
      string                        m_strCred;

      
      /// the best size_i32 to fit current ca2 icon (as of 2014)
      draw2d::icon *                m_picon95;
      ::image_pointer                         m_pimage;


      login();
      virtual ~login();


      virtual ::e_status initialize(::context_object * pcontextobject) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool on_action(const char * pszId) override;

      

      void defer_translate(const string & strUser, const string & strPass, const string & strOpen);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(on_message_create);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace account




