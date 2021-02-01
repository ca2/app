#pragma once


namespace account
{


   class CLASS_DECL_CORE view :
      virtual public ::user::impact
   {
   public:

      
      __pointer(::account::credentials)    m_pcredentials;
      ::mutex                         m_mutexResponse;
      manual_reset_event            m_evSubmit;
      string                        m_strResponse;
      ::simple_ui::label *          m_plabelUser;
      ::simple_ui::edit_box *       m_peditUser;
      ::simple_ui::label *          m_plabelPassword;
      ::simple_ui::password *       m_ppassword;
      ::simple_ui::tap *            m_ptap;
      ::simple_ui::tap *            m_ptapClose;
      string                        m_strRequestUrl;

      string                        m_strUsername;
      string                        m_strPassword;

      bool                          m_bSelfLayout;
      double                        m_dRateX;
      double                        m_dRateY;

      bool                          m_bCred;
      string                        m_strCred;

      draw2d::icon *                m_picon95; // the best size_i32 to fit current ca2 icon (as of 2014)


      view();
      virtual ~view();


      virtual void install_message_routing(::channel * pchannel);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool on_action(const char * pszId);

      void initialize();

      void defer_translate(const string & strUser, const string & strPass, const string & strOpen);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics);

      void interactive_credentials(::account::credentials * pcredentials);

   };


} // namespace account



