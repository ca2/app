#include "framework.h"
//#include "berg/user/user/_component.h"


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

CLASS_DECL_AURA void message_box(::acme::windowing::window * pacmewindowingwindow, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::::user::e_message_box & emessagebox, ::callback callback)
{

   ::user::interaction_base* prototype = ::auraacmesystem()->ui_from_handle(oswindow);

   return ::auraacmesystem()->message_box(prototype, pszText, pszTitle, emessagebox, callback);

}
