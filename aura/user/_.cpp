#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


CLASS_DECL_AURA::e_status message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process)
{

   ::e_status estatus = ::error_failed;

   auto psystem = &System;

   if(psystem)
   {

      psystem->message_box(pszMessage, pszTitle, emessagebox, process);

   }

   return estatus;

}






CLASS_DECL_AURA ::user::primitive * __user_primitive(oswindow oswindow)
{

   ::user::primitive * pprimitive = System.ui_from_handle(oswindow);

   return pprimitive;

}




