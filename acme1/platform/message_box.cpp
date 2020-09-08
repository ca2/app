#include "framework.h"


message_box::message_box()
{

}


message_box::~message_box()
{

}


::estatus message_box::show(::generic* pobject)
{

   //if (::is_null(pobject))
   //{

   //   pobject = ::get_context_system();

   //}

   //return pobject->message_box(m_puserprimitive, m_strMessage, m_strTitle, m_emessagebox, m_callback);

   return ::success;

}


CLASS_DECL_ACME ::estatus message_box(oswindow oswindow, const char* pszText, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
{

   //::user::primitive* primitive = ::get_context_system()->ui_from_handle(oswindow);

   //return ::get_context_system()->message_box(primitive, pszText, pszTitle, emessagebox, callback);

   return ::success;

}