#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form_view:
      virtual public ::form_view,
      virtual public ::filemanager_impact_base
   {
   public:
      
      
      form_view();


      void on_update(::aura::impact * pSender,e_update eupdate,object* pupdate);
      virtual void handle(::topic * psubject, ::context * pcontext);


   };



} // namespace filemanager



















