#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form :
      virtual public ::user::form_view,
      virtual public ::filemanager::impact
   {
   public:

            form();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void on_apply(::action * paction) override;
      virtual void on_control_event(::user::control_event * pevent) override;


   };



} // namespace filemanager



















