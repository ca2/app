#include "framework.h"
#include "acme/parallelization/task.h"
#include "acme/operating_system/ansi/_pthread.h"
#include "acme/windowing/display.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"


namespace platform
{


   void node::_user_post(const ::procedure &procedure)
   {

      //information() << "::platform::node::user_post going to display_post";

      auto pdisplay = system()->acme_windowing()->acme_display();

      pdisplay->display_post(procedure);

   }


} // namespace platform



bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}


//namespace x11{namespace nano { namespace user{void process_messages();}}}

//namespace xcb{namespace nano { namespace user{void process_messages();}}}

//namespace wayland{namespace nano { namespace user{void process_messages();}}}



void _do_tasks()
{

   if(!is_main_thread())
   {

      return;

   }

   auto psystem = system();

   auto pacmewindowing = psystem->m_pacmewindowing;

   if(::is_set(pacmewindowing))
   {

      pacmewindowing->process_messages();

   }

   if(psystem)
   {

      auto pnode = psystem->node();

      if(pnode)
      {

         pnode->defer_do_main_tasks();

      }

   }

}



CLASS_DECL_ACME void _os_task_destroy(htask htask, itask itask)
{



}