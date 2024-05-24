#include "framework.h"
#include "acid/parallelization/task.h"
#include "acid/operating_system/ansi/_pthread.h"
#include "acid/nano/user/display.h"
#include "acid/platform/acid.h"
#include "acid/platform/node.h"
#include "acid/platform/platform.h"
#include "acid/platform/system.h"


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



//CLASS_DECL_ACID ::acid::system * system();


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


namespace acid
{


   void node::user_post(const ::procedure &procedure)
   {

      information() << "acid::node::user_post going to display_post";

      ::nano::user::display::g_p->display_post(procedure);

   }


} // namespace acid



bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}


namespace x11{namespace nano { namespace user{void process_messages();}}}

namespace xcb{namespace nano { namespace user{void process_messages();}}}

namespace wayland{namespace nano { namespace user{void process_messages();}}}



void _do_tasks()
{

   if(!is_main_thread())
   {

      return;

   }

   auto psystem = ::platform::get()->system();

#ifdef HAS_WAYLAND
   if(psystem->m_ewindowing == e_windowing_wayland)
   {

      ::wayland::nano::user::process_messages();

   }
   else
#endif
   if(psystem->m_ewindowing == e_windowing_xcb)
   {

      ::xcb::nano::user::process_messages();

   }
   else
   {

      ::x11::nano::user::process_messages();

   }

   psystem->node()->defer_do_main_tasks();

}



