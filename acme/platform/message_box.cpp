#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "acme/user/_user.h"
#endif


message_box::message_box()
{

}


message_box::~message_box()
{

}


//::estatus message_box::show(::matter* pobject)
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

CLASS_DECL_ACME ::estatus message_box(oswindow oswindow, const char* pszText, const char* pszTitle, ::emessagebox emessagebox, ::future future)
{

   __throw(todo("message_box"));
   //::user::primitive* primitive = System.ui_from_handle(oswindow);

   //return System.message_box(primitive, pszText, pszTitle, emessagebox, callback);

}