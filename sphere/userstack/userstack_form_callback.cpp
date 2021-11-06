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


   void form_callback::handle(::subject * psubject, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(pevent);

   }


} // namespace userstack


