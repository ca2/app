#pragma once


#include "bred/platform/application.h"


namespace core
{


   class CLASS_DECL_CORE application :
      virtual public ::bred::application
   {
   public:


      ::pointer<::userex::pane_tab_impact>     m_ppaneimpactCore;


      application();
      ~application() override;


      void common_construct();


      ::core::session* get_session();
      ::core::system* get_system();



      virtual void initialize(::particle * pparticle) override;
      ::pointer<::progress::real>show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount) override;


      //virtual void prepare_impact_menu(::user::menu * pmenu);


      virtual string prepare_impact_options();
      virtual string prepare_impact_options_header();
      virtual string prepare_impact_options_main_body();
      virtual string prepare_impact_options_footer();

      bool handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, property_set & propertyset) override;


   };


} // namespace core




