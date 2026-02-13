#pragma once


#include "bred/platform/application.h"


namespace core
{


   class CLASS_DECL_CORE application :
      virtual public ::bred::application
   {
   public:

      //
      // ::pointer<::userex::pane_tab_impact>     m_ppaneimpactCore;
      // ::pointer < ::filemanager::filemanager> m_pfilemanager;


      application();
      ~application() override;
      

      void common_construct();


      void on_set_platform() override;


      //::core::session* get_session();
      //::core::system* get_system();



      virtual void initialize(::particle * pparticle) override;
      ::pointer<::progress::real>show_progress(::user::interaction* puiParent, const ::scoped_string & scopedstrTitle, ::collection::count iProgressCount) override;


      void initialize_rich_text_kit() override;

      //virtual void prepare_impact_menu(::user::menu * pmenu);


      string prepare_impact_options() override;
      string prepare_impact_options_header() override;
      string prepare_impact_options_main_body() override;
      string prepare_impact_options_footer() override;


      ::filemanager::filemanager * filemanager() override;


      void create_options_footer(const ::atom & atom, ::user::interaction * pparent) override;


      bool handle_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset) override;


      void create_auto_start_option(const ::atom &atom, ::user::interaction *pparent) override;


      void term_instance() override;
      
      void on_prompt_write_file(::user::controller * pusercontroller) override;
      void file_manager_save_as(::user::controller * pusercontroller) override;

   };


} // namespace core




