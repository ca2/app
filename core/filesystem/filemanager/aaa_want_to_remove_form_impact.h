#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form_impact:
      virtual public ::form_impact,
      virtual public ::filemanager_impact_base
   {
   public:
      
      
      form_impact();


      void on_update(::aura::impact * pSender,e_update eupdate,object* pupdate);
      virtual void handle(::topic * ptopic, ::context * pcontext);


   };



} // namespace filemanager



















