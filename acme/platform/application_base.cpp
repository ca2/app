//
// Created by camilo on 2022-12-01 08:42 <3ThomasBorregaardSorensen!!
// Recreated as layer by camilo on 2024-10-28 06:27 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application_base.h"
#include "acme.h"

//
//namespace acme
//{
//
//
//   application_base::application_base()
//   {
//
//      m_acme.acme_initialize(){}
//
//   }
//
//
//   application_base::~application_base()
//   {
//
//      //::acme::acme::g_pacme->acme_finalize(){}
//
//      //::acme::acme::g_pacme->~acme(){}
//
//   }
//
//
//} // namespace acme
//
//
//

//#pragma once

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
//      //::acme::acme         m_acme{}
//
//
//      application_base(){}
//      virtual ~application_base(){}
//
//
//   }{}
//
//
//} // namespace acme
//
//
//


namespace platform
{


   ::pointer < ::data::data > base_application_layer::create_default_new_document_data()
   {

return {};

   }


   //      // void assert_ok() const override{}
   //      // void dump(dump_context & dumpcontext) const override{}


   // ::base::system* get_system(){}
   // ::base::session* get_session(){}


   ::pointer<::user::document>base_application_layer::defer_create_impact(string strImpact, ::user::interaction* puiParent, e_window_flag ewindowflag, const ::atom& atom)
   {

      return {};

   }


   ::user::document * base_application_layer::place_hold(::user::interaction * pinteraction)
   {

return nullptr;

   }


   void base_application_layer::on_create_split_impact(::user::split_impact* pimpact){}
   void base_application_layer::on_change_cur_sel(::user::tab* ptab){}
   //virtual void create_impact_system() override{}
   //virtual void on_create_impact(::user::impact_data* pimpactdata) override{}

   //virtual void close(::enum_exit eexit) override{}


   //virtual void on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context) override{}


   //void create_options_impact(::user::interaction * pparent) override{}
   void base_application_layer::create_options_header(::user::interaction * pparent){}
   void base_application_layer::create_options_body(::user::interaction * pparent){}
   void base_application_layer::create_options_footer(::user::interaction * pparent){}

   void base_application_layer::create_auto_start_option(::user::interaction* pparent){}

   void base_application_layer::create_about_option(::user::interaction * pparent){}

   void base_application_layer::create_about_impact(::user::interaction * pparent){}

   void base_application_layer::on_after_prepare_impact_menu(::user::menu * pmenu){}


   //void show_about_box() override{}


   //void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem) override{}
   //virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom) override{}

   //int track_popup_menu(::menu::track_popup * ptrackpopup) override{}


} // namespace platform




