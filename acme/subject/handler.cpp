// From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 20:00 BRT
//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
#include "framework.h"


CLASS_DECL_ACME void __call(handler * phandler, const ::id & id, i64 iData, ::matter * pmatter)
{

   ::subject subject(id);

   if (iData != 0)
   {

      subject.m_payload = iData;

   }

   if (pmatter != nullptr)
   {

      subject.m_pmatter = pmatter;

   }

   phandler->handle(&subject, nullptr);

   if (!subject.m_estatus)
   {

      return subject.m_estatus;

   }

   return subject.m_estatus;

}


void handler::call(enum_message emessage, i64 iData, ::matter * pmatter)
{

   return __call(this, emessage, iData, pmatter);

}


void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
{

   return __call(this, eid, iData, pmatter);

}



