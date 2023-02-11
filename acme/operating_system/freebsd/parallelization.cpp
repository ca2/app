#include "framework.h"
#include "acme/operating_system/ansi/_pthread.h"

#include "acme/user/nano/display.h"

#define bitset freebsd_bitset
#include <sys/_cpuset.h>
#include <sys/cpuset.h>
#undef bitset
#include <pthread_np.h>


#include <sys/time.h>
#define ITIMER_REAL      0
#define ITIMER_VIRTUAL   1
#define ITIMER_PROF      2


void task_set_name(htask_t htask, const char * psz)
{

//   string strName(psz);

  // thread_name_abbreviate(strName, 15);

   if(!pthread_setname_np((pthread_t) htask, psz))
   {

       output_debug_string("pthread_setname_np Failed\n");

   }

}


void task_set_name(const char * psz)
{

   return task_set_name((htask_t) pthread_self(), psz);

}


// void __node_init_cross_windows_threading()
// {

// }


// void __node_term_cross_windows_threading()
// {

// }


int SetThreadAffinityMask(htask_t h, unsigned int dwThreadAffinityMask)
{

   cpuset_t c;

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

      memset(&value, 0, sizeof value);
      value.it_value = timeout;

      memset(&sa, 0, sizeof sa);
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


CLASS_DECL_ACME ::acme::system * acmesystem();


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

    acmesystem()->windowing_post(predicate);

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



