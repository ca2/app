#pragma once


#include "acme/user/user/e_window_flag.h"
#include "axis/platform/application.h"
#include "aura/user/user/form_callback.h"
#include "berg/user/user/impact_creator.h"
#include "berg/user/user/document_manager_container.h"
#include "berg/user/user/options_impact_handler.h"


namespace berg
{



   class CLASS_DECL_BERG application :
      virtual public ::axis::application,
      virtual public ::user::form_callback,
      virtual public ::user::impact_creator,
      virtual public ::filemanager::callback,
      virtual public ::user::document_manager_container,
      virtual public ::user::options_impact_handler
   {
   public:

      //
      // //::pointer<::aura::application_menu>      m_pappmenu;
      //
      // ::pointer < ::user::tab_impact >                m_ptabimpactBase;
      // ::pointer < ::user::options_impact_handler >    m_poptionsimpacthandler;
      //

      application();
      ~application() override;


      void on_set_platform() override;

      void initialize(::particle * pparticle) override;

      void destroy() override;


      void process_term() override;
      
      ::pointer < ::data::data > create_default_new_document_data() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      // ::base::system* get_system();
      // ::base::session* get_session();


      ::pointer<::user::document>defer_create_impact(const ::scoped_string & scopedstrImpact, ::user::interaction* puiParent = nullptr, e_window_flag ewindowflag = ::e_window_flag(), const ::atom& atom = ::atom()) override;

      ::user::document * place_hold(::user::interaction * pinteraction) override;
      void on_create_split_impact(::user::split_impact* pimpact) override;
      void on_change_cur_sel(::user::tab* ptab) override;
      virtual void create_impact_system() override;
      virtual void on_create_impact(::user::impact_data* pimpactdata) override;

      virtual void close(::enum_exit eexit) override;


      virtual void on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context) override;


      void create_options_impact(::user::interaction * pparent) override;
      void create_options_header(::user::interaction * pparent) override;
      void create_options_body(::user::interaction * pparent) override;
      void create_options_footer(::user::interaction * pparent) override;

      void create_auto_start_option(::user::interaction* pparent) override;

      void create_about_option(::user::interaction * pparent) override;

      void create_about_impact(::user::interaction * pparent) override;

      void on_after_prepare_impact_menu(::user::menu * pmenu) override;


      void show_about_box(::user::activation_token * puseractivationtoken) override;

      
      void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem) override;
      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom) override;

      int track_popup_menu(::menu::track_popup * ptrackpopup) override;


   };


} // namespace berg

