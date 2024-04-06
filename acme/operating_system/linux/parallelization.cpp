#include "framework.h"
#include "acme/parallelization/task.h"
#include "acme/operating_system/ansi/_pthread.h"
#include "acme/user/nano/display.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"


//::user::enum_desktop get_edesktop();


//void x11_asynchronous(::procedure function);
//void xcb_asynchronous(::procedure function);


//void task_set_name(htask_t htask, const char * psz)
//{
//
//   string strName(psz);
//
//   thread_name_abbreviate(strName, 15);
//
//   if(pthread_setname_np((pthread_t) htask, strName))
//   {
//
//      throw exception(error_failed);
//
//   }
//
//}
//
//
//void task_set_name(const char * psz)
//{
//
//   return task_set_name((htask_t) pthread_self(), psz);
//
//}
//

// void __node_init_cross_windows_threading()
// {

// }


// void __node_term_cross_windows_threading()
// {

// }



//CLASS_DECL_ACME ::acme::system * system();


//void main_asynchronous(const ::procedure & procedure)
//{
//
//   if(is_main_thread())
//   {
//
//      procedure();
//
//      return;
//
//   }
//
//   auto predicate = [procedure]()
//                            {
//
//                               procedure();
//
//                            };
//
//   auto psystem = this->platform()->system();
//
//   psystem->windowing_post(predicate);
//
//}


namespace acme
{


   void node::user_post(const ::procedure &procedure)
   {

      information() << "acme::node::user_post going to display_post";

      ::nano::display::g_p->display_post(procedure);

   }


} // namespace acme



bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}


void x11_process_messages();
void xcb_process_messages();
void wayland_process_messages();


void _do_tasks()
{

   if(!is_main_thread())
   {

      return;

   }

   auto psystem = ::platform::get()->system();

   if(psystem->m_ewindowing == e_windowing_wayland)
   {

      wayland_process_messages();

   }
   else if(psystem->m_ewindowing == e_windowing_xcb)
   {

      xcb_process_messages();

   }
   else
   {

      x11_process_messages();

   }

   psystem->node()->defer_do_main_tasks();

}


