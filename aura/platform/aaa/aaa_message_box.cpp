#include "framework.h"
#include "base/user/user/_user.h"


message_box::message_box()
{

}


message_box::~message_box()
{

}


::e_status message_box::show(::object* pobject)
{

   if (::is_null(pobject))
   {

      pobject = ::get_context_system();

   }

   return pobject->message_box(m_puserprimitive, m_strMessage, m_strTitle, m_emessagebox, m_callback);

}

CLASS_DECL_AURA ::e_status message_box(oswindow oswindow, const ::string & pszText, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
{

   ::user::primitive* primitive = ::aura::get_system()->ui_from_handle(oswindow);

   return ::aura::get_system()->message_box(primitive, pszText, pszTitle, emessagebox, callback);

}
