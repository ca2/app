//
// Created by camilo on 2022-12-01 08:40 <3ThomasBorregaardSorensen!!
// Recreated as layer by camilo on 2024-10-28 06:08 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/user/e_window_flag.h"

//
//#include "acme.h"
//
//
//namespace acme
//{
//
//
//   class CLASS_DECL_ACME application_base
//   {
//   public:
//
//
//      //::acme::acme         m_acme;
//
//
//      application_base();
//      virtual ~application_base();
//
//
//   };
//
//
//} // namespace acme
//
//
//


namespace platform
{


   struct CLASS_DECL_ACME base_application_layer_t
   {


      //::pointer<::aura::application_menu>      m_pappmenu;

      ::pointer < ::user::tab_impact >                m_ptabimpactBase;
      ::pointer < ::user::options_impact_handler >    m_poptionsimpacthandler;


   };


   class CLASS_DECL_ACME base_application_layer
   {
   public:


      virtual ::pointer < ::data::data > create_default_new_document_data();


      //      // void assert_ok() const override;
      //      // void dump(dump_context & dumpcontext) const override;


      // ::base::system* get_system();
      // ::base::session* get_session();


      virtual ::pointer<::user::document>defer_create_impact(string strImpact, ::user::interaction* puiParent, e_window_flag ewindowflag, const ::atom& atom);
      virtual ::user::document * place_hold(::user::interaction * pinteraction);
      virtual void on_create_split_impact(::user::split_impact* pimpact);
      virtual void on_change_cur_sel(::user::tab* ptab);
      //virtual void create_impact_system() override;
      //virtual void on_create_impact(::user::impact_data* pimpactdata) override;

      //virtual void close(::enum_exit eexit) override;


      //virtual void on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context) override;


      //void create_options_impact(::user::interaction * pparent) override;
      virtual void create_options_header(::user::interaction * pparent);
      virtual void create_options_body(::user::interaction * pparent);
      virtual void create_options_footer(::user::interaction * pparent);

      virtual void create_auto_start_option(::user::interaction* pparent);

      virtual void create_about_option(::user::interaction * pparent);

      virtual void create_about_impact(::user::interaction * pparent);

      virtual void on_after_prepare_impact_menu(::user::menu * pmenu);


      //void show_about_box() override;


      //void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem) override;
      //virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom) override;

      //i32 track_popup_menu(::menu::track_popup * ptrackpopup) override;

   };


} // namespace platform




