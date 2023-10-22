#pragma once


#include "acme/user/user/e_window_flag.h"
#include "axis/platform/application.h"
#include "aura/user/user/form_callback.h"
#include "base/user/user/impact_creator.h"
#include "base/user/user/document_manager_container.h"
#include "base/user/user/options_impact_handler.h"


namespace base
{


   enum e_end
   {

      end_close,
      end_app,
      end_session,
      end_system

   };


   class CLASS_DECL_BASE application :
      virtual public ::axis::application,
      virtual public ::user::form_callback,
      virtual public ::user::impact_creator,
      virtual public ::filemanager::callback,
      virtual public ::user::document_manager_container,
      virtual public ::user::options_impact_handler
   {
   public:


      //::pointer<::aura::application_menu>      m_pappmenu;

      ::pointer < ::user::tab_impact >          m_ptabimpactBase;


      application();
      ~application() override;
      

      virtual void initialize(::particle * pparticle) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      ::base::system* get_system();
      ::base::session* get_session();


      virtual ::pointer<::user::document>defer_create_impact(string strImpact, ::user::interaction* puiParent = nullptr, e_window_flag ewindowflag = ::e_window_flag(), const ::atom& atom = ::atom());

      virtual ::user::document * place_hold(::user::interaction * pinteraction);
      virtual void on_create_split_impact(::user::split_impact* pimpact);
      virtual void on_change_cur_sel(::user::tab* ptab);
      virtual void create_impact_system() override;
      virtual void on_create_impact(::user::impact_data* pimpactdata) override;

      virtual void close(::apex::enum_end eend) override;


      virtual void on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context) override;


      void create_options_impact(::user::interaction * pparent) override;
      virtual void create_options_header(::user::interaction * pparent);
      virtual void create_options_body(::user::interaction * pparent);
      virtual void create_options_footer(::user::interaction * pparent);

      virtual void create_auto_start_option(::user::interaction* pparent);

      virtual void create_about_option(::user::interaction * pparent);

      virtual void create_about_impact(::user::interaction * pparent);

      virtual void on_after_prepare_impact_menu(::user::menu * pmenu);


      void show_about_box() override;


   };


} // namespace base

