#pragma once


#include "aura/user/user/form_callback.h"
#include "berg/user/user/impact_creator.h"
#include "berg/user/user/tab_callback.h"
#include "aura/user/user/style.h"


namespace hi5
{


   namespace twitter
   {


      class CLASS_DECL_CORE authorization :
         virtual public ::user::form_callback,
         virtual public ::user::impact_creator,
         virtual public ::user::tab_callback,
         virtual public ::user::style
      {
      public:


         string                                    m_strPin;
         string                                    m_strAuthorizationUrl;
         int                                   m_iImpact;
         ::pointer<::user::single_document_template>     m_ptemplatePane;
         ::pointer<::user::document>                     m_pdocument;
         ::pointer<::user::tab_impact>                     m_ptabimpact;
         ::pointer<::form_document>                      m_pformdocumentAuth;
         ::pointer<::form_document>                      m_pformdocumentMessage;
         ::pointer<::user::form_impact>                    m_pviewAuth;
         bool                                      m_bAuth;
         string                                    m_strForm;
         string                                    m_strLicense;
         bool                                      m_bLicense;
         bool                                      m_bInteractive;

         authorization();
         virtual ~authorization();


         virtual void initialize_twitter_authorization(::object* pparticle, const ::scoped_string & scopedstrAuthorizationUrl, const ::scoped_string & scopedstrForm, bool bAuth, bool bInteractive);

         void ensure_main_document();
         void display_main_frame();
         void page1();
         void pageMessage(const ::scoped_string & scopedstrMatter, ::property_set & set);

         string get_pin();

         void on_create_impact(::user::impact_data * pimpactdata) override;
         virtual void on_change_cur_sel();


         void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

         virtual bool style_translucency(::user::enum_translucency & etranslucency, ::enum_element);


      };


   } // namespace twitter


} // namespace hi5




