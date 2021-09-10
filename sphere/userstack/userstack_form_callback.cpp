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
      __UNREFERENCED_PARAMETER(psubject);

   }


   void form_callback::on_control_event(::user::control_event * pevent)
   {

      __UNREFERENCED_PARAMETER(pevent);

   }


} // namespace userstack


