#pragma once

#include "simple_app.h"

namespace browser
{


   class CLASS_DECL_APP_BROWSER application :
      virtual public ::aura::application
   {
   public:


      enum e_type
      {

         type_normal,
         type_mili,

      };

      e_type                                 m_etype;
      string                                 m_strHelloBrowser;
      string                                 m_strHelloBrowserDefault;
      string                                 m_strAlternateHelloBrowser;
      string                                 m_strAlternateHelloBrowserDefault;

      bool                                   m_bBrowserChat;
      CefRefPtr<SimpleApp> get_context_application();
      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_view *              m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloBrowserMain;
      ::user::single_document_template *     m_ptemplateHelloBrowserView;
      ::user::single_document_template *     m_ptemplateHelloBrowserSwitcher;
      pane_view *                            m_ppaneview;


      application(::layered * pobjectContext);
      virtual ~application();


      virtual string preferred_experience() override;
      virtual ::estatus init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;

   };


} // namespace browser



