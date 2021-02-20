#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/_user.h"
#endif


message_box::message_box()
{

}


message_box::message_box(const ::payload & payload)
{

   if (payload.get_type() == e_type_string)
   {

      m_strMessage = payload;

   }
   else if (payload.has_property("message") && payload["message"].has_char())
   {

      m_strMessage = payload["message"];

   }
   else if (payload.has_property("format") && payload["format"].has_char())
   {

      m_strMessage = payload.propset().format(payload["format"]);

   }

   m_puserprimitive = payload["parent"].cast < ::layered >();
   m_strTitle = payload["title"];
   m_emessagebox = (enum_message_box)payload["flags"].i64();

   //if (m_puserprimitive)
   //{

   //   //m_oswindow = m_puserinteractionParent->get_safe_handle();

   //}

}



message_box::~message_box()
{

}


//::e_status message_box::show(::matter* pobject)
//{
//
//   //if (::is_null(pobject))
//   //{
//
//   //   pobject = ::get_context_system();
//
//   //}
//
//   return pobject->message_box(m_playereUserPrimitive, m_strMessage, m_strTitle, m_emessagebox, m_callback);
//
//}


CLASS_DECL_ACME ::e_status message_box(::windowing::window * pwindow, const char* pszText, const char* pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process)
{

   __throw(todo("message_box"));
   //::user::primitive* primitive = System.ui_from_handle(oswindow);

   //return System.message_box(primitive, pszText, pszTitle, emessagebox, callback);

}