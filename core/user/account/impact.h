#pragma once


#include "base/user/user/impact.h"


namespace account
{


   class CLASS_DECL_CORE impact :
      virtual public ::user::impact
   {
   public:

      
      ::pointer<::account::credentials>     m_pcredentials;
      ::mutex                                m_mutexResponse;
      manual_reset_event                     m_evSubmit;
      string                                 m_strResponse;
      ::user::still *                        m_pstillUser;
      ::user::plain_edit *                   m_peditUser;
      ::user::still*                         m_pstillPassword;
      ::user::plain_edit*                    m_peditPassword;
      ::user::button *                       m_pbutton;
      ::user::button *                       m_pbuttonClose;
      string                                 m_strRequestUrl;

      string                        m_strUsername;
      string                        m_strPassword;

      bool                          m_bSelfLayout;
      double                        m_dRateX;
      double                        m_dRateY;

      bool                          m_bCred;
      string                        m_strCred;

      draw2d::icon *                m_picon95; // the best size_i32 to fit current ca2 icon (as of 2014)


      impact();
      ~impact() override;


      void install_message_routing(::channel * pchannel) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      bool on_action(const ::string & pszId) override;

      void initialize();

      void defer_translate(const ::string & strUser, const ::string & strPass, const ::string & strOpen);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

      void interactive_credentials(::account::credentials * pcredentials);

   };


} // namespace account



