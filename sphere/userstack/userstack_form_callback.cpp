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

      __UNREFERENCED_PARAMETER(pform);
      __UNREFERENCED_PARAMETER(ptopic);

   }


   void form_callback::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(pevent);

   }


} // namespace userstack


