// From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 20:00 BRT
//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/handler/topic.h"
#include "acme/handler/extended_topic.h"
#include "acme/platform/system.h"


//handler::~handler()
//{
//
//
//
//}
//

//CLASS_DECL_ACME void __call(handler * phandler, const ::atom & atom, i64 wParam, i64 lParam, ::matter * pmatter)
//{
//
//   if (::is_null(pmatter))
//   {
//
//      auto psystem = acmesystem();
//
//      auto ptopic = psystem->create_topic(atom);
//
//      if(wParam != 0 || lParam != 0)
//      {
//
//         ptopic->payload("wparam") = wParam;
//         ptopic->payload("lparam") = lParam;
//
//      }
//
//      phandler->handle(ptopic, nullptr);
//
//   }
//   else
//   {
//
//      auto pextendedtopic = pmatter->create_extended_topic(atom);
//
//      if(wParam != 0 || lParam != 0)
//      {
//
//         pextendedtopic->payload("wparam") = wParam;
//         pextendedtopic->payload("lparam") = lParam;
//
//      }
//
//      pextendedtopic->m_pmatter = pmatter;
//
//      phandler->handle(pextendedtopic, nullptr);
//
//   }
//
//}
//
//
//
////
////
////void handler::call(enum_message emessage, i64 iData, ::matter * pmatter)
////{
////
////   return __call(this, emessage, iData, pmatter);
////
////}
////
////
////void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
////{
////
////   return __call(this, eid, iData, pmatter);
////
////}
////
//
//
//void handler::call(const ::atom & atom, i64 wParam, i64 lParam, ::matter * pmatter)
//{
//
//   return __call(this, atom, wParam, lParam, pmatter);
//
//}
//
//
//void handler::handle(::topic * ptopic, ::context * pcontext)
//{
//
//
//}
//
//
//void handler::handle(::message::message * pmessage)
//{
//
//
//}
//
//
//bool handler::_handle_uri(const block & blockUri)
//{
//
//   return false;
//
//}
//
//
//bool handler::_handle_call(::payload & payload, const ::block & blockObject, const ::block & blockMember, ::property_set & propertyset)
//{
//
//   return false;
//
//}
//
//
////bool handler::_handle_call(::payload & payload, const ::block & blockMember, ::property_set & propertyset)
////{
////
////   return false;
////
////}
//
////bool handler::handle_text_command(const ::block & blockTextCommand)
////{
////
////   return false;
////
////}
//
//
////
////void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
////{
////
////   return __call(this, eid, iData, pmatter);
////
////}
//
//
////bool handler::on_interprocess_handle(::interprocess::target * ptarget, const ::block & blockUri)
////{
////
////   return handle_uri(blockUri);
////
////}
//
//
//
