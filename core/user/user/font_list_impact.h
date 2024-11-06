// Created by camilo on 2023-08-28 00:49 <3ThomasBorregaardSorensen!!
#pragma once


#include "font_list.h"
#include "base/user/user/show.h"


namespace user
{


   class CLASS_DECL_CORE font_list_impact :
      virtual public ::user::show < font_list >
   {
   public:


      font_list_impact();
      ~font_list_impact() override;


      void initialize(::particle * pparticle) override;


      //::core::application * get_app();
      //::core::session * get_session();
      //::core::system * get_system();
      //::base::user * user() override;


      //      // void assert_ok() const override;
      //      // void dump(dump_context & dumpcontext) const override;

      //virtual bool pre_create_window(::user::system * pusersystem) override;

      void install_message_routing(::channel * pchannel) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnTimer(::timer * ptime) override;

      //void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
      //virtual void on_command(::message::command * pcommand) override;
      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void set_context_offset(::draw2d::graphics_pointer & pgraphics, int, int) override;
      //virtual ::int_point get_context_offset() override;
      //::double_size get_total_size() override;

      //void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void OnActivateImpact(bool bActivate, ::pointer<::user::impact>pActivateImpact, ::pointer<::user::impact>viewDeactivate) override;

      //virtual ::collection::index _001GetCurItem() override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace user





