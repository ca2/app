#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE form_callback :
      virtual public ::user::form_callback
   {
   public:
      form_callback();
      virtual ~form_callback();

      void update(::user::form * pform, ::update & update);
      virtual void handle(::subject * psubject, ::context * pcontext);
   };


} // namespace userstack



