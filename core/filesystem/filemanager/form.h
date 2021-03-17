#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form :
      virtual public ::filemanager_show < ::user::form_view >
   {
   public:

      form();


      virtual void on_control_event(::user::control_event * pevent) override;


   };



} // namespace filemanager



















