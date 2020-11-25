#include "framework.h"

namespace prompt
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   
   void form_callback::update(::user::form * pform, ::update & update)
   {
      
      UNREFERENCED_PARAMETER(pform);
      UNREFERENCED_PARAMETER(psubject);

   }


   void form_callback::on_control_event(::user::control_event * pevent)
   {

      __pointer(::user::interaction) pinteraction =  (this);

      if(pinteraction != nullptr && pinteraction->GetParent() != nullptr)
      {

         return pinteraction->GetParent()->on_control_event(pevent);

      }

   }


} // namespace prompt



