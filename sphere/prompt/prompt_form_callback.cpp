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
      
      __UNREFERENCED_PARAMETER(pform);
      __UNREFERENCED_PARAMETER(ptopic);

   }


   void form_callback::handle(::topic * ptopic, ::context * pcontext)
   {

      __pointer(::user::interaction) pinteraction =  (this);

      if(pinteraction != nullptr && pinteraction->get_parent() != nullptr)
      {

         return pinteraction->get_parent()->handle(ptopic, pcontext);

      }

   }


} // namespace prompt



