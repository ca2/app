#include "framework.h"


message_box::message_box()
{

}


message_box::~message_box()
{

}


void message_box::show(::object* pobject)
{

   if (::is_null(pobject))
   {

      pobject = ::aura::system::g_p;

   }

   pobject->message_box(m_puserprimitive, m_strMessage, m_strTitle, m_emessagebox, m_callback);

}

CLASS_DECL_AURA ::estatus message_box(oswindow oswindow, const char* pszText, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
{

   ::user::primitive* primitive = ::aura::system::g_p->ui_from_handle(oswindow);

   return ::aura::system::g_p->message_box(primitive, pszText, pszTitle, emessagebox, callback);

}