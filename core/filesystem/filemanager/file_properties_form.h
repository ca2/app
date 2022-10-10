#pragma once


#include "aura/user/user/form_callback.h"
#include "base/user/user/impact_host.h"
#include "base/user/form/impact.h"
#include "base/user/user/tab_callback.h"


namespace filemanager
{


   class CLASS_DECL_CORE file_properties_form :
      virtual public ::user::form_callback,
      virtual public ::user::impact_host,
      virtual public ::user::tab_callback
   {
   public:


      ::pointer<::user::single_document_template>     m_ptemplatePane;
      ::pointer<::user::document>                     m_pdocGeneral;
      ::pointer<::user::form_impact>                    m_pviewGeneral;
      ::pointer<::userex::pane_tab_impact>              m_ptabimpact;
      ::file::item_array                          m_itema;


      file_properties_form();
      ~file_properties_form() override;

      
      void initialize(::object * pobject) override;


      ::pointer<::user::interaction>open(::pointer<::user::interaction>uieParent, ::file::item_array & itema);

      void on_change_cur_sel() override;

      //::pointer<::user::impact_kit>get_impact_kit();
      
      void on_create_impact(::user::impact_data * pimpactdata) override;
      
      void page1();
      
      void page2();

      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      
      //virtual ::form_property_set * get_form_property_set() override;
      
      


   };


} // namespace filemanager




