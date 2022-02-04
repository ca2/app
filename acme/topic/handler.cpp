// From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 20:00 BRT
//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
#include "framework.h"


CLASS_DECL_ACME void __call(handler * phandler, enum_topic etopic, const ::id & id, i64 iData, ::matter * pmatter)
{

   ::extended_topic topic(etopic, id);

   if (iData != 0)
   {

      topic.m_payload = iData;

   }

   if (pmatter != nullptr)
   {

      topic.m_pmatter = pmatter;

   }

   phandler->handle(&topic, nullptr);

}


void handler::call(enum_message emessage, i64 iData, ::matter * pmatter)
{

   return __call(this, id_call_message, emessage, iData, pmatter);

}


void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
{

   return __call(this, id_trigger_id, eid, iData, pmatter);

}



