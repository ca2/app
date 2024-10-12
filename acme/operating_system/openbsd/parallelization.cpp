#include "framework.h"
#include "acme/operating_system/ansi/_pthread.h"
#include "acme/windowing/windowing_base.h"
#include "acme/platform/system.h"
#include "acme/user/micro/display.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/_operating_system.h"
#include <sys/param.h>
#include <sys/sysctl.h>
// #if defined(OPENBSD)
// #define __XSI_VISIBLE 1
// #endif
#define bitset openbsd_bitset
//#include <sys/_cpuset.h>
//#include <sys/cpuset.h>
#undef bitset
#include <pthread_np.h>
#include <signal.h>
#include <sys/time.h>
#define ITIMER_REAL      0
#define ITIMER_VIRTUAL   1
#define ITIMER_PROF      2
#include <errno.h>


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








//https://lists.openbsd.org/pipermail/openbsd-hackers/2008-July/025483.htmlhttps://lists.openbsd.org/pipermail/openbsd-hackers/2008-July/025483.html
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
//https://lists.openbsd.org/pipermail/openbsd-hackers/2008-July/025483.html
void
signal_ignore(int s, siginfo_t *si, void *ctx)
{
}


//https://lists.openbsd.org/pipermail/openbsd-hackers/2008-July/025483.html
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
//      ::acme::windowing::display::g_p->display_post(procedure);
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
namespace x11{namespace nano { namespace user{void process_messages();}}}

namespace xcb{namespace nano { namespace user{void process_messages();}}}


void _do_tasks()
{

   auto psystem = system();

   auto pwindowingsystem = psystem->windowing_system();

   if(::is_set(pwindowingsystem))	
   {

      pwindowingsystem->process_messages();

   }


//   if(psystem->m_ewindowing == ::windowing::e_windowing_wayland)
//   {
//
//      wayland_process_messages();
//
//   }
//   else
//  if(psystem->m_ewindowing == ::windowing::e_windowing_xcb)
  // {

    //  xcb_process_messages();

  // }
  // else
  // {

//#if !defined(OPENBSD)

  //    x11_process_messages();

//#endif

  // }

   psystem->node()->defer_do_main_tasks();

}




namespace acme
{


   void node::user_post(const ::procedure &procedure)
   {

      information() << "acme::node::user_post going to display_post";

      ::acme::windowing::display::g_p->display_post(procedure);

   }


} // namespace acme


int get_processor_count()
{
	// On OpenBSD HW_NCPUONLINE tells the number of processor cores that
	// are online so it is preferred over HW_NCPU which also counts cores
	// that aren't currently available. The number of cores online is
	// often less than HW_NCPU because OpenBSD disables simultaneous
	// multi-threading (SMT) by default.
#	ifdef HW_NCPUONLINE
	int name[2] = { CTL_HW, HW_NCPUONLINE };
#	else
	int name[2] = { CTL_HW, HW_NCPU };
#	endif
	int cpus;
	size_t cpus_size = sizeof(cpus);
	if (sysctl(name, 2, &cpus, &cpus_size, NULL, 0) == -1)
	{

		return 1;

	}

	return cpus;
	

}
