#pragma once

#include "simple_app.h"

namespace browser
{


   class CLASS_DECL_APP_BROWSER application :
      virtual public ::aura::application
   {
   public:


      enum enum_type
      {

         type_normal,
         type_mili,

      };

      enum_type                                 m_etype;
      string                                 m_strHelloBrowser;
      string                                 m_strHelloBrowserDefault;
      string                                 m_strAlternateHelloBrowser;
      string                                 m_strAlternateHelloBrowserDefault;

      bool                                   m_bBrowserChat;
      CefRefPtr<SimpleApp> get_app();
      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_impact *              m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloBrowserMain;
      ::user::single_document_template *     m_ptemplateHelloBrowserImpact;
      ::user::single_document_template *     m_ptemplateHelloBrowserSwitcher;
      pane_impact *                            m_ppaneimpact;


      application(::particle * pparticle);
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      virtual string preferred_experience() override;
      virtual void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::request * prequest) override;

      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;

   };


} // namespace browser



