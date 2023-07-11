#include "framework.h"
//#include "base/user/user/_component.h"
#include "aura/update.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#endif
#include "trace_category.h"





void debug_object_event_promisse_predicate()
{

   //::object o;

   //::object * po = memory_new object();

   //// 2 arguments
   //o.treat(ok, po, [&](auto & result) { information("o += ok..."); return success; } };

   //// 3 arguments
   //o += { ok, id_text, [&](auto & result) { information("o += ok, id_text ..."); return ::success; } };


   //::pointer<::object>pparticle;

   //KEEP(pparticle, nullptr);
   ////   // 4 arguments
   ////   o += { ok, id_text, [&](auto pparticle) { ASSERT(pparticle == &o); information("o += ok, id_text, &o ...");  } };


}


void system_call_update_wallpaper_changed()
{

   ::auraacmesystem()->call_subject(id_wallpaper_changed);

}


void system_call_update_app_activated()
{

   ::auraacmesystem()->call_subject(id_app_activated);

}


void system_call_update_app_changed_occlusion_state()
{

   ::auraacmesystem()->call_subject(id_app_changed_occlusion_state);

}







void debug_id_eid()
{

   auto pupdate = new_update();

   ptopic->payload(id_filter) = "*.jpg";

}





