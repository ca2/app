#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE form :
      virtual public ::filemanager_show < ::user::form_view >
   {
   public:

      form();


      virtual void handle(::subject * psubject, ::context * pcontext) override;


   };



} // namespace filemanager



















