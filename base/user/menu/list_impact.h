#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_list_impact :
      virtual public ::user::show < ::user::menu_list_window >
   {
   public:


      typedef ::user::show <  ::user::menu_list_window  > BASE;


      menu_list_impact();
      ~menu_list_impact() override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      void install_message_routing(::channel * pchannel) override;

      virtual bool pre_create_window(::user::system * pusersystem) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;


      virtual void post_non_client_destroy() override;




   };


} // namespace user



