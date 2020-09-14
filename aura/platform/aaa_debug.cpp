#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/update.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#endif
#include "trace_category.h"





void debug_object_event_promisse_pred()
{

   //::object o;

   //::context_object * po = new context_object();

   //// 2 arguments
   //o.treat(ok, po, [&](auto & result) { output_debug_string("o += ok..."); return success; } };

   //// 3 arguments
   //o += { ok, id_text, [&](auto & result) { output_debug_string("o += ok, id_text ..."); return ::success; } };


   //__pointer(::object) pobject;

   //__keep(pobject, nullptr);
   ////   // 4 arguments
   ////   o += { ok, id_text, [&](auto pobject) { ASSERT(pobject == &o); output_debug_string("o += ok, id_text, &o ...");  } };


}


void system_call_update_wallpaper_changed()
{

   ::get_context_system()->call_update(id_wallpaper_changed);

}


void system_call_update_app_activated()
{

   ::get_context_system()->call_update(id_app_activated);

}


void system_call_update_app_changed_occlusion_state()
{

   ::get_context_system()->call_update(id_app_changed_occlusion_state);

}







void debug_id_eid()
{

   auto pupdate = new_update();

   pupdate->value(id_filter) = "*.jpg";

}





