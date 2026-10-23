#include "platform.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"
#include "acme/constant/windowing2.h"
#include "acme/operating_system/posix/termination_handler.h"
#include <OS.h>
#include <image.h>
#include <time.h>
#include <errno.h>

#if defined(__HAIKU__)
void __node_acme_pre_init() {}
void __node_acme_pos_init() {}
void __node_acme_pre_term() {}
void __node_acme_pos_term() {}
bool __os_init_thread() { return true; }
bool __os_term_thread() { return true; }
void _os_task_destroy(htask, itask) {}
void acme_quite_early_construct() { termination_handler::initialize(); }
::i32 __node_is_debugger_attached() { return 0; }

::i64 i64_nanosecond()
{
   struct timespec ts = {};
   if (::clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0;
   return (::i64)ts.tv_sec * 1000000000 + ts.tv_nsec;
}

::i32 get_processor_count()
{
   system_info info = {};
   if (::get_system_info(&info) != B_OK) return 1;
   return (::i32)info.cpu_count;
}

::file::path get_home_config_folder_path()
{
   return ::file::path(getenv("HOME")) / "config/settings";
}

::file::path get_module_path()
{
   int32 cookie = 0;
   image_info info = {};
   while (::get_next_image_info(B_CURRENT_TEAM, &cookie, &info) == B_OK)
      if (info.type == B_APP_IMAGE) return info.name;
   throw ::exception(error_failed);
}

void operating_system_factory(::factory::factory *)
{
   // Console factories are registered by acme_haiku and acme_posix.
}

namespace platform
{
   void node::user_post(const ::procedure &procedure)
   {
      system()->acme_windowing()->main_post(procedure);
   }
}

namespace windowing
{
   enum_operating_ambient get_eoperating_ambient() { return e_operating_ambient_unknown; }
   enum_toolkit get_etoolkit() { return e_toolkit_none; }
}
#endif
