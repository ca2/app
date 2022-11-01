#pragma once


#include "apex/handler/source.h"
#include "aura/user/user/form_callback.h"


namespace user
{


   class CLASS_DECL_AURA form_callback :
      virtual public ::source
   {
   public:


      form_callback();
      ~form_callback() override;

      virtual void _001OnInitializeForm();
      virtual void _001OnInitializeControl(interaction * pinteraction);


      virtual void _001InitializeFormPreData(::user::form * pform);
      

   };


} // namespace user


