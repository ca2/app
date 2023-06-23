#include "framework.h"


namespace userstack
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
      UNREFERENCED_PARAMETER(ptopic);

   }


   void form_callback::handle(::topic * ptopic, ::context * pcontext)
   {

      UNREFERENCED_PARAMETER(pevent);

   }


} // namespace userstack


