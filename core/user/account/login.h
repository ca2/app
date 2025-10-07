#pragma once


#include "aura/user/user/interaction.h"


namespace account
{


   class CLASS_DECL_CORE login :
      virtual public ::user::interaction
   {
   public:


      ::pointer<::user::still>            m_pstillUser;
      ::pointer<::user::plain_edit>       m_peditUser;
      ::pointer<::user::still>            m_pstillPassword;
      ::pointer<::user::plain_edit>       m_peditPassword;
      ::pointer<::user::button>           m_pbutton;
      ::pointer<::user::button>           m_pbuttonClose;


      string                        m_strUsername;
      string                        m_strPassword;
      character_count                       m_iPasswordOriginalLength;
      
      bool                          m_bSubmitted;
      
      bool                          m_bSelfLayout;
      double                        m_dRateX;
      double                        m_dRateY;

      bool                          m_bCred;
      string                        m_strCred;

      
      /// the best int_size to fit current ca2 icon (as of 2014)
      ::image::icon *                m_picon95;
      ::image::image_pointer                         m_pimage;


      login();
      virtual ~login();


      virtual void initialize(::particle * pparticle) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool on_action(const ::scoped_string & scopedstrId) override;

      

      void defer_translate(const ::scoped_string & scopedstrUser, const ::scoped_string & scopedstrPass, const ::scoped_string & scopedstrOpen);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace account




