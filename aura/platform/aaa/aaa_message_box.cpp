#include "framework.h"
//#include "base/user/user/_component.h"


message_box::message_box()
{

}


message_box::~message_box()
{

}


void message_box::show(::object* pparticle)
{

   if (::is_null(pparticle))
   {

      pparticle = ::get_context_system();

   }

   return pparticle->message_box(m_puserprimitive, m_strMessage, m_strTitle, m_emessagebox, m_callback);

}

CLASS_DECL_AURA void message_box(oswindow oswindow, const ::string & pszText, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
{

   ::user::primitive* primitive = ::auraacmesystem()->ui_from_handle(oswindow);

   return ::auraacmesystem()->message_box(primitive, pszText, pszTitle, emessagebox, callback);

}
