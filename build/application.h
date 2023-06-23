#pragma once


#include "core/platform/application.h"


namespace app_build
{


   class CLASS_DECL_APP_BUILD application :
      virtual public ::core::application
   {
   public:


      enum enum_type
      {

         type_normal,
         type_mili,

      };


      enum_type                              m_etype;
      string                                 m_strHelloMultiverse;
      string                                 m_strHelloMultiverseDefault;
      string                                 m_strAlternateHelloMultiverse;
      string                                 m_strAlternateHelloMultiverseDefault;

      bool                                   m_bMultiverseChat;

      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_impact *            m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseImpact;
      pane_impact *                          m_ppaneimpact;


      ::file::path_array                     m_pathaCommandLineSlide;


      application();
      ~application() override;


      void set_finish() override;


      virtual string preferred_experience() override;
      virtual void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::request * prequest) override;



   };


} // namespace app_build



