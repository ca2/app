#include "framework.h"
#include "acme/parallelization/task.h"
#include "acme/operating_system/ansi/_pthread.h"
#include "acme/user/nano/display.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"


//::user::enum_desktop _get_edesktop();


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


int SetThreadAffinityMask(htask_t h, unsigned int dwThreadAffinityMask)
{

   cpu_set_t c;

   CPU_ZERO(&c);

   for(int i = 0; i < sizeof(dwThreadAffinityMask) * 8; i++)
   {

      if((1 << i) & dwThreadAffinityMask)
      {

         CPU_SET(i, &c);

      }

   }

   pthread_setaffinity_np((pthread_t) h, sizeof(c), &c);

   return 1;

}


//CLASS_DECL_ACME ::acme::system * acmesystem();


void main_asynchronous(const ::procedure & procedure)
{

   if(is_main_thread())
   {

      procedure();

      return;

   }

   auto predicate = [procedure]()
                            {

                               procedure();

                            };

   auto psystem = ::acme::acme::g_p->m_psubsystem->acmesystem();

   psystem->windowing_post(predicate);

}


namespace acme
{

   void system::windowing_post(const ::procedure &procedure)
   {

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



