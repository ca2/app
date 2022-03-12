// From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 20:00 BRT
//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
#include "framework.h"


extern class ::system * g_psystem;


CLASS_DECL_ACME void __call(handler * phandler, const ::atom & atom, i64 iData, ::matter * pmatter)
{

   if (::is_null(pmatter))
   {

      auto ptopic = g_psystem->create_topic(atom);

      if(iData != 0)
      {

         ptopic->payload("iptr_data") = iData;

      }

      phandler->handle(ptopic, nullptr);

   }
   else
   {

      auto pextendedtopic = pmatter->m_psystem->create_extended_topic(atom);

      if (iData != 0)
      {

         pextendedtopic->payload("iptr_data") = iData;

      }

      pextendedtopic->m_pmatter = pmatter;

      phandler->handle(pextendedtopic, nullptr);

   }

}



//
//
//void handler::call(enum_message emessage, i64 iData, ::matter * pmatter)
//{
//
//   return __call(this, emessage, iData, pmatter);
//
//}
//
//
//void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
//{
//
//   return __call(this, eid, iData, pmatter);
//
//}
//


void handler::call(const ::atom & atom, i64 iData, ::matter * pmatter)
{

   return __call(this, atom, iData, pmatter);

}


//
//void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
//{
//
//   return __call(this, eid, iData, pmatter);
//
//}



