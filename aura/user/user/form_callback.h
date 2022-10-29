#pragma once


#include "apex/handler/source.h"


namespace user
{


   class CLASS_DECL_AURA form_callback :
      virtual public ::source
   {
   public:


      virtual void _001OnInitializeForm();
      virtual void _001OnInitializeControl(interaction * pinteraction);


      virtual void _001InitializeFormPreData(::user::form * pform);
      

   };


} // namespace user


