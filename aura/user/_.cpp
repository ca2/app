#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


CLASS_DECL_AURA::estatus message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, const ::futurevar & futurevar)
{

   ::estatus estatus = ::error_failed;

   auto psystem = &System;

   if(psystem)
   {

      psystem->message_box(puiOwner, pszMessage, pszTitle, emessagebox, futurevar);

   }

   return estatus;

}






CLASS_DECL_AURA ::user::primitive * __user_primitive(oswindow oswindow)
{

   ::user::primitive * pprimitive = System.ui_from_handle(oswindow);

   return pprimitive;

}




