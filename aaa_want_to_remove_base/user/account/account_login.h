#pragma once


#include "base/user/simple_ui/simple_ui.h"


namespace account
{


   class CLASS_DECL_BASE login :
      virtual public ::user::interaction
   {
   public:


      __composite(::simple_ui::label)        m_plabelUser;
      __composite(::simple_ui::edit_box)     m_peditUser;
      __composite(::simple_ui::label)        m_plabelPassword;
      __composite(::simple_ui::password)     m_ppassword;
      __composite(::simple_ui::tap)          m_ptap;
      __composite(::simple_ui::tap)          m_ptapClose;


      string                        m_strUsername;
      string                        m_strPassword;
      strsize                       m_iPasswordOriginalLength;
      
      bool                          m_bSubmitted;
      
      bool                          m_bSelfLayout;
      double                        m_dRateX;
      double                        m_dRateY;

      bool                          m_bCred;
      string                        m_strCred;

      
      /// the best size to fit current ca2 icon (as of 2014)
      draw2d::icon *                m_picon95;
      ::image_pointer                         m_pimage;


      login();
      virtual ~login();


      virtual ::estatus initialize(::object * pobjectContext) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool on_action(const char * pszId) override;

      

      void defer_translate(const string & strUser, const string & strPass, const string & strOpen);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace account




