#include "framework.h"
#include "acme/operating_system/ansi/_pthread.h"
#include "acme/platform/system.h"
#include "acme/nano/user/display.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/windowing/windowing_base.h"


//#if defined(FREEBSD)
//#define __XSI_VISIBLE 1
//#endif
#define bitset freebsd_bitset
#include <sys/_cpuset.h>
#include <sys/cpuset.h>
#undef bitset
#include <pthread_np.h>
#include <signal.h>
#include <sys/time.h>
#define ITIMER_REAL      0
#define ITIMER_VIRTUAL   1
#define ITIMER_PROF      2
#include <errno.h>
#include <stdio.h>

//void task_set_name(htask_t htask, const char * psz)
//{

//   string strName(psz);

  // thread_name_abbreviate(strName, 15);

  // if(!pthread_setname_np((pthread_t) htask, psz))
   //{

     //  informationf("pthread_setname_np Failed\n");

   //}

//}


//void task_set_name(const char * psz)
//{

  // return task_set_name((htask_t) pthread_self(), psz);

//}


// void __node_init_cross_windows_threading()
// {

// }


// void __node_term_cross_windows_threading()
// {

// }








//https://lists.freebsd.org/pipermail/freebsd-hackers/2008-July/025483.htmlhttps://lists.freebsd.org/pipermail/freebsd-hackers/2008-July/025483.html
void
_timeval_diff(struct timeval *tv1, struct timeval *tv2, struct timeval *tvd)
{
   tvd->tv_sec = tv1->tv_sec - tv2->tv_sec;
   tvd->tv_usec = tv1->tv_usec - tv2->tv_usec;
   if (tvd->tv_usec < 0) {
      tvd->tv_usec = 1000000 - tvd->tv_usec;
      tvd->tv_sec--;
   }
}
//https://lists.freebsd.org/pipermail/freebsd-hackers/2008-July/025483.html
void
signal_ignore(int s, siginfo_t *si, void *ctx)
{
}


//https://lists.freebsd.org/pipermail/freebsd-hackers/2008-July/025483.html
int
_semtimedop(int semid, struct sembuf *array, size_t nops, struct
   timespec *_timeout)
{
   struct timeval timeout, before, after;
   struct itimerval value, ovalue;
   struct sigaction sa, osa;
   int ret;

   if (_timeout) {
      timeout.tv_sec = _timeout->tv_sec;
      timeout.tv_usec = _timeout->tv_nsec / 1000;

      if (gettimeofday(&before, NULL) == -1) {
         errno = EFAULT;
         return -1;
      }

      if (timeout.tv_sec == 0 && timeout.tv_usec < 5000) {
         struct timeval tsleep, tend;
         struct sembuf wait;

         wait = *array;
         wait.sem_flg |= IPC_NOWAIT;

         tsleep.tv_sec = 0;
         tsleep.tv_usec = 1;

         timeradd(&before, &timeout, &tend);

         for ( ;; ) {
            struct timeval tnow, tleft;
            struct timespec ts;

            ret = semop(semid, &wait, nops);
            if (ret == 0) {
               return 0;
            } else if (errno != EAGAIN) {
               break;
            }

            if (gettimeofday(&tnow, NULL) == -1) {
               errno = EFAULT;
               break;
            }

            if (timercmp(&tnow, &tend, >=)) {
               errno = EAGAIN;
               break;
            }

            timersub(&tend, &tnow, &tleft);

            if (tsleep.tv_usec > tleft.tv_usec)
               tsleep.tv_usec = tleft.tv_usec;

            ts.tv_sec = 0;
            ts.tv_nsec = tsleep.tv_usec * 1000;
            nanosleep(&ts, NULL);

            tsleep.tv_usec *= 10;
         }

         return -1;
      }

      memory_set(&value, 0, sizeof value);
      value.it_value = timeout;

      memory_set(&sa, 0, sizeof sa);
      sa.sa_sigaction = signal_ignore;
      sa.sa_flags = SA_SIGINFO;
      sigemptyset(&sa.sa_mask);
      sigaction(SIGALRM, &sa, &osa);

      if (setitimer(ITIMER_REAL, &value, &ovalue) == -1) {
         sigaction(SIGALRM, &osa, NULL);
         return -1;
      }
   }

   ret = semop(semid, array, nops);

   if (_timeout) {
      ret = setitimer(ITIMER_REAL, &ovalue, NULL);
      if (ret < 0)
         errno = EFAULT;

      sigaction(SIGALRM, &osa, NULL);
   }

   if (ret == -1) {
      if (_timeout) {
         struct timeval elapsed;

         if (gettimeofday(&after, NULL) == -1) {
         } else {

            _timeval_diff(&after, &before, &elapsed);

            if (timercmp(&elapsed, &timeout, >=))
            errno = EAGAIN;
         }
      }

      return -1;
   }

   return 0;
}


CLASS_DECL_ACME ::acme::system * system();


//void main_asynchronous(const ::procedure & procedure)
//{
//
//    if(is_main_thread())
//    {
//
//        procedure();
//
//        return;
//
//    }
//
//    auto predicate = [procedure]()
//    {
//
//        procedure();
//
//    };
//
//    platform::get()->system()->windowing_post(predicate);
//
//}


//namespace acme
//{
//
//
//   void system::windowing_post(const ::procedure &procedure)
//   {
//
//      ::nano::user::display::g_p->display_post(procedure);
//
//   }
//
//
//} // namespace acme


bool __os_init_thread()
{

    return true;

}


bool __os_term_thread()
{

    //thread_shutdown();

    return true;

}






//void x11_process_messages();
//void xcb_process_messages();
//void wayland_process_messages();

//namespace x11{namespace nano { namespace user{void process_messages();}}}

//namespace xcb{namespace nano { namespace user{void process_messages();}}}

void _do_tasks()
{

//   auto psystem = ::platform::get()->system();
//
////   if(psystem->m_ewindowing == e_windowing_wayland)
////   {
////
////      wayland_process_messages();
////
////   }
////   else
//  if(psystem->m_ewindowing == e_windowing_xcb)
//   {
//
//      ::xcb::nano::user::process_messages();
//
//   }
//   else
//   {
//
//      ::x11::nano::user::process_messages();
//
//   }

   auto psystem = ::platform::get()->system();

   auto pwindowingsystem = psystem->windowing_system();

   if(::is_set(pwindowingsystem)) {

      pwindowingsystem->process_messages();

   }

   psystem->node()->defer_do_main_tasks();

}




namespace acme
{


   void node::user_post(const ::procedure &procedure)
   {

      information() << "acme::node::user_post going to display_post";

      nano()->user()->main_post(procedure);

   }


} // namespace acme





// http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
// http://stackoverflow.com/users/1275169/l3x
int get_proc_cpuinfo_core_count()
{

   char str[256];

   int procCount = 0;

   FILE *fp;

   if( (fp = fopen("/proc/cpuinfo", "r")) )
   {

      while(fgets(str, sizeof str, fp))
      {

         if(memory_order(str, "handler", 9) == 0)
         {

            procCount++;

         }

      }

   }

   if ( !procCount )
   {
      print_line("Unable to get proc count. Defaulting to 2");
      procCount=2;
   }

   printf_line("Proc Count:%d\n", procCount);
   return procCount;

}


int get_processor_count()
{

   return get_proc_cpuinfo_core_count();

}


