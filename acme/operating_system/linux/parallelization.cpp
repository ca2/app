#include "framework.h"
#include "acme/operating_system/ansi/_pthread.h"


void x11_asynchronous(::function < void() > function);


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

   auto routine = __routine([function]()
                            {

                               function();

                            });

   g_psystem->windowing_post(routine);


}



void system::windowing_post(const ::routine & routine)
{

   x11_asynchronous([routine]()
                    {

                       routine();

                    });


}