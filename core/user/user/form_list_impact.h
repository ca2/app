#pragma once


#include "form_list.h"
#include "list_impact.h"
#include "base/user/form/impact.h"


namespace user
{


   class CLASS_DECL_CORE form_list_impact:
      virtual public ::user::form_list,
      virtual public ::user::form_impact,
      virtual public ::user::list_impact
   {
   public:


      form_list_impact();
      virtual ~form_list_impact();


      virtual void initialize(::particle * pparticle) override;


      ::core::application* get_app();
      ::core::session* get_session();
      ::core::system* get_system();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual bool pre_create_window(::user::system * pusersystem) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnTimer(::timer * ptime) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
      virtual void on_command(::message::command* pcommand) override;
      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void set_context_offset(::draw2d::graphics_pointer & pgraphics, int, int) override;
      virtual ::point_i32 get_context_offset() override;
      virtual ::size_f64 get_total_size() override;

      //void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void OnActivateImpact(bool bActivate, ::pointer<::user::impact>pActivateImpact, ::pointer<::user::impact>viewDeactivate) override;

      virtual index _001GetCurItem() override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace user





