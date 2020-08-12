#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form_view:
      virtual public ::form_view,
      virtual public ::filemanager::impact
   {
   public:
      
      
      form_view();


      void on_update(::aura::impact * pSender,e_update eupdate,object* pupdate);
      virtual void on_control_event(::user::control_event * pevent);


   };



} // namespace filemanager



















