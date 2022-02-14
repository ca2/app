// Created on 2021-03-29 at 13:00 BRT <3TBS_, Mummi and bilbo!!
#pragma once


namespace aura
{


   class CLASS_DECL_AURA context :
      virtual public ::apex::context
   {
   public:


      __creatable(context);


      context();
      ~context() override;


      virtual void initialize_context() override;



   };


} // namespace apex



