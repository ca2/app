#pragma once


#include "bred/platform/application.h"


namespace core
{


   class CLASS_DECL_CORE application :
      virtual public ::bred::application
   {
   public:


      ::pointer<::userex::pane_tab_impact>     m_ppaneimpactCore;
      ::pointer < ::filemanager::filemanager> m_pfilemanager;


      application();
      ~application() override;
      

      void common_construct();


      void on_set_platform() override;


      ::core::session* get_session();
      ::core::system* get_system();



      virtual void initialize(::particle * pparticle) override;
      ::pointer<::progress::real>show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::raw::count iProgressCount) override;


      virtual void initialize_rich_text_kit();

      //virtual void prepare_impact_menu(::user::menu * pmenu);


      virtual string prepare_impact_options();
      virtual string prepare_impact_options_header();
      virtual string prepare_impact_options_main_body();
      virtual string prepare_impact_options_footer();


      ::filemanager::filemanager * filemanager() const;


      void create_options_footer(::user::interaction * pparent) override;


      bool handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, property_set & propertyset) override;


      void create_auto_start_option(::user::interaction * pparent) override;


      void term_instance() override;
      
      void on_prompt_write_file(::user::controller * pusercontroller) override;
      void file_manager_save_as(::user::controller * pusercontroller) override;

   };


} // namespace core




