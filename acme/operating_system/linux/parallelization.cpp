#include "framework.h"
#include "acme/operating_system/ansi/_pthread.h"


#include "acme/user/nano/display.h"

//::user::enum_desktop _get_edesktop();


//void x11_asynchronous(::function < void() > function);
//void xcb_asynchronous(::function < void() > function);


void task_set_name(htask_t htask, const char * psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   if(pthread_setname_np((pthread_t) htask, strName))
   {

      throw exception(error_failed);

   }

}


//void task_set_name(const char * psz)
//{
//
//   return task_set_name((htask_t) pthread_self(), psz);
//
//}


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


extern class ::system * g_psystem;


void main_asynchronous( ::function < void () > function)
{

   if(is_main_thread())
   {

      function();

      return;

   }

   auto routine = __routine([function]()
                            {

                               function();

                            });

   g_psystem->windowing_post(routine);

}



void system::windowing_post(const ::function < void() > & function)
{

   ::nano::display::g_p->display_post(function);

//   if(m_ewindowing == e_windowing_xcb)
//   {
//
//      xcb_asynchronous([routine]()
//                       {
//
//                          routine();
//
//                       });
//   }
//   else if(m_ewindowing == e_windowing_x11)
//   {
//
//      x11_asynchronous([routine]()
//                       {
//
//                          routine();
//
//                       });
//
//   }
//   else
//   {
//
//      throw exception(error_wrong_state);
//
//   }

}