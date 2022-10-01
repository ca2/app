#include "framework.h"
#include "acme/operating_system.h"



#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
#include <sys/ipc.h>
#include "acme/operating_system/ansi/_pthread.h"
#include <sys/time.h>
#include <time.h>
#include <sys/time.h>

#if defined(LINUX) || defined(__APPLE__)
#include <sys/sem.h>
#endif
#include "acme/operating_system/ansi/_ansi.h"

#ifdef __MACH__

#include <mach/clock.h>
#include <mach/mach.h>

struct mach_calendar_clock
{
   clock_serv_t m_clockserv;
   mach_timespec_t m_machtimespec;

   mach_calendar_clock()
   {
      
      host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &m_clockserv);

      
   }
   
   ~mach_calendar_clock()
   {

   mach_port_deallocate(mach_task_self(), m_clockserv);
      
   }
   
   
   void get_time(struct timespec * pts)
   {
      
      clock_get_time(m_clockserv, &m_machtimespec);
      pts->tv_sec = m_machtimespec.tv_sec;
      pts->tv_nsec = m_machtimespec.tv_nsec;

      
   }

   
} g_machcalendarclock;


#endif // __MACH__


void clock_getrealtime(struct timespec * pts)
{

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time

//   struct timeval timeval;
//   gettimeofday(&timeval, nullptr);
//   pts->tv_sec = timeval.tv_sec;
//   pts->tv_nsec = timeval.tv_usec * 1000;
   g_machcalendarclock.get_time(pts);

#else

   clock_gettime(CLOCK_REALTIME, pts);

#endif

}

#endif


//CLASS_DECL_ACME::layered* get_layered_thread();


event::event(char * sz, bool bInitiallyOwn, bool bManualReset, const char * pstrName ARG_SEC_ATTRS)
{

#ifdef WINDOWS_DESKTOP

   m_hsync = ::CreateEventW((LPSECURITY_ATTRIBUTES)PARAM_SEC_ATTRS, bManualReset, bInitiallyOwn, pstrName ? nullptr : wstring(pstrName).c_str());

   if (m_hsync == NULL)
   {

      throw ::exception(error_resource);

   }

#elif defined(_UWP)

   u32 dwFlags = 0;

   if(bInitiallyOwn)
   {

      dwFlags |= CREATE_EVENT_INITIAL_SET;

   }

   if(bManualReset)
   {

      dwFlags |= CREATE_EVENT_MANUAL_RESET;

   }

   m_hsync = ::CreateEventEx((LPSECURITY_ATTRIBUTES)PARAM_SEC_ATTRS, pstrName ? nullptr : wstring(pstrName).c_str(), dwFlags, DELETE | EVENT_MODIFY_STATE | SYNCHRONIZE);

   if (m_hsync == nullptr)
   {

      throw ::exception(error_resource);

   }

#elif defined(ANDROID)

   m_pcond = memory_new pthread_cond_t;

   pthread_cond_init((pthread_cond_t *) m_pcond, nullptr);

   m_bManualEvent = bManualReset;

   if(m_bManualEvent)
   {

      m_bSignaled = bInitiallyOwn;
      pthread_mutexattr_t  attr;
      pthread_mutexattr_init(&attr);
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      i32 rc;
      m_mutex = memory_new pthread_mutex_t;
      if((rc = pthread_mutex_init((pthread_mutex_t *) m_mutex,&attr)))
      {
         throw ::exception(::exception("RC_OBJECT_NOT_CREATED"));
      }


   }
   else
   {
      m_mutex = nullptr;
   }

#else

   m_bManualEvent    = bManualReset;

   if(bManualReset)
   {

      m_mutex = memory_new pthread_mutex_t;

      m_pcond = memory_new pthread_cond_t;

      pthread_mutex_init((pthread_mutex_t *) m_mutex, 0);

      pthread_cond_init((pthread_cond_t *) m_pcond, 0);

      m_bSignaled = bInitiallyOwn;

   }
   else
   {

      m_mutex = nullptr;

      m_pcond = nullptr;

      if(pstrName != nullptr && *pstrName != '\0')
      {

         string strPath = "/::payload/tmp/ca2/ftok/event/" + string(pstrName);

         m_sem = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);

      }
      else
      {

         m_sem = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

      }

      semun semctl_arg;

      if(bInitiallyOwn)
      {

         semctl_arg.val = 1;

      }
      else
      {

         semctl_arg.val = 0;

      }

      semctl((i32) m_sem, 0, SETVAL, semctl_arg);

   }


#endif


}


event::~event()
{

#if defined(LINUX)

   semun ignored_argument;

   semctl(m_sem, 0, IPC_RMID, ignored_argument);

   ::acme::del((pthread_mutex_t * &)m_mutex);

   ::acme::del((pthread_cond_t * &)m_pcond);

#elif defined(ANDROID)

   if(m_pcond != nullptr)
   {
      delete (pthread_cond_t *)m_pcond;
   }
   if(m_mutex != nullptr)
   {
      delete (pthread_mutex_t *)m_mutex;
   }

#endif

}



bool event::SetEvent()
{

#ifdef WINDOWS

   if (m_hsync == nullptr)
   {

      ASSERT(false);

      return false;

   }

   try
   {

      return ::SetEvent((HANDLE)m_hsync) != false;

   }
   catch(...)
   {
   }

   return false;

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_mutex);

   if(m_bManualEvent)
   {

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast((pthread_cond_t *) m_pcond);

   }
   else
   {

      pthread_cond_signal((pthread_cond_t *) m_pcond);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

   return true;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_mutex);

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast((pthread_cond_t *) m_pcond);

      pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

   }
   else
   {

      sembuf sb;

      sb.sem_op   = 1;
      sb.sem_num  = 0;
      sb.sem_flg  = m_bManualEvent ? 0 : SEM_UNDO;

      return semop((i32) m_sem, &sb, 1) == 0;

   }

   return true;

#endif

}


//bool event::PulseEvent()
//{
//
//#ifdef WINDOWS_DESKTOP
//
//
//   ASSERT(m_hsync != nullptr);
//
//   return ::PulseEvent(m_hsync) != false;
//
//#else
//
//   sembuf sb;
//
//   sb.sem_op   = 1;
//   sb.sem_num  = 0;
//   sb.sem_flg  = SEM_UNDO;
//
//   return semop((i32) m_hsync, &sb, 1) == 0;
//
//#endif
//
//}



bool event::ResetEvent()
{

#ifdef WINDOWS

   try
   {

      if(m_hsync == NULL)
      {

         ::output_debug_string(L"error reset event (1)");

         return false;

      }

      return ::ResetEvent((HANDLE)m_hsync) != false;

   }
   catch(...)
   {

      ::output_debug_string(L"error reset event (2)");

   }

   return false;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_mutex);

      m_bSignaled = false;

      pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

   }
   else
   {

      throw ::exception(error_failed,"It does not make sense to Reset a Event that is Automatic. It can be only Pulsed/Broadcasted.");

   }

   return true;

#endif

}


void event::_wait ()
{

   //throw ::exception(todo("thread"));
   //if(m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->add_waiting_event(this);

   //   }

   //}

#ifdef WINDOWS

   while (true)
   {

      int iResult = ::WaitForSingleObjectEx(hsync(), 300, false);

      if(iResult == WAIT_OBJECT_0)
      {

         return;

      }
      else if (iResult == WAIT_TIMEOUT)
      {

         if (!task_get_run())
         {

            throw ::exception(abandoned_base);

         }

      }
      else
      {

         throw ::exception(error_failed);

      }

   }

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_mutex);

   if(m_bManualEvent)
   {

      i32 iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex);

      }

   }
   else
   {

      pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_mutex);

      int iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex);

      }

      pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

   }
   else
   {

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = 0;

      semop((i32) m_sem, &sb, 1);

   }

#endif

   //throw ::exception(todo("thread"));
   //if(m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->add_waiting_event(this);

   //   }

   //}

   //return signaled_base;

}


bool event::_wait (const class ::wait & wait)
{

   ::e_status estatus;

   //throw ::exception(todo("thread"));
   //if(durationTimeout > 1_s && m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->add_waiting_event(this);

   //   }

   //}


#ifdef WINDOWS

   auto hsync = this->hsync();

   DWORD dwResult = ::WaitForSingleObjectEx(hsync, wait, false);

   estatus = windows_wait_result_to_status(dwResult);

   if (estatus == error_wait_timeout)
   {

      return false;

   }
   else if (estatus == signaled_base)
   {

      return true;

   }
   else
   {

      throw ::exception(estatus);

      return false;

   }

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_mutex);

   ::duration duration(wait);

   if(m_bManualEvent)
   {

      timespec end;
      clock_gettime(CLOCK_REALTIME, &end);

      end.tv_sec += duration.m_iSecond;
      end.tv_nsec += duration.m_iNanosecond;

      end.tv_sec += end.tv_nsec / (1000 * 1000 * 1000);
      end.tv_nsec %= 1000 * 1000 * 1000;

      i32 iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex, &end))
            break;

      }

   }
   else
   {

      timespec delay;
      delay.tv_sec = duration.m_iSecond;
      delay.tv_nsec = duration.m_iNanosecond;
      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex, &delay);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

   return m_bSignaled;

#else

   if(m_bManualEvent)
   {

      if(wait.is_infinite())
      {

         pthread_mutex_lock((pthread_mutex_t *) m_mutex);

         int iSignal = m_iSignalId;

         //clock_gettime(CLOCK_REALTIME, &abstime);

         while(!m_bSignaled && iSignal == m_iSignalId)
         {

            i32 error = pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex);

            if(error != 0)
            {

               break;

            }

         }

         pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

         if(m_bSignaled)
         {

            estatus = signaled_base;

         }
         else
         {

            estatus = error_failed;

         }

      }
      else
      {

         timespec abstime;
         
         timespec timeNow;

         pthread_mutex_lock((pthread_mutex_t *) m_mutex);

         int iSignal = m_iSignalId;

         //clock_gettime(CLOCK_REALTIME, &abstime);

         clock_getrealtime(&abstime);

         abstime += wait;

         while(abstime.tv_nsec > 1000 * 1000 * 1000)
         {

            abstime.tv_nsec -= 1000 * 1000 * 1000;

            abstime.tv_sec++;

         }

         while(!m_bSignaled && iSignal == m_iSignalId)
         {
            
            clock_getrealtime(&timeNow);
            ::i32 error;
            if(timeNow.tv_sec > abstime.tv_sec||
               (timeNow.tv_sec == abstime.tv_sec &&
                timeNow.tv_nsec > abstime.tv_nsec))
               {
               
               error = ETIMEDOUT;
               
            }
               else
               {

            error = pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex, &abstime);
               
            }

            if(error == EBUSY || error == ETIMEDOUT)
            {

               pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

               return false;

            }

         }

         pthread_mutex_unlock((pthread_mutex_t *) m_mutex);

         if(m_bSignaled)
         {

            return true;

         }
         else
         {

            throw ::exception(error_failed);

         }

      }

   }
   else
   {

      timespec delay;

      delay.tv_sec = 0;

      delay.tv_nsec = 1000 * 1000;

      auto start = ::duration::now();

      while(wait.is_infinite() || start.elapsed() < wait)
      {

         sembuf sb;

         sb.sem_op   = -1;
         sb.sem_num  = 0;
         sb.sem_flg  = IPC_NOWAIT;

         i32 ret = semop((i32) m_sem, &sb, 1);

         if(ret < 0)
         {

            if(ret == EPERM || ret == EBUSY)
            {

               nanosleep(&delay, nullptr);

            }
            else
            {

               throw ::exception(error_failed);

            }

         }
         else
         {

            return true;

         }

      }

      return false;

   }


#endif

   ////throw ::exception(todo("thread"));
   //if(durationTimeout > 1_s && m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->erase_waiting_event(this);

   //   }

   //}

   //return estatus;

   return true;

}


//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//*****************************************************************************
//*****************************************************************************
//
//      Name:           Signaled
//      Description:    Determines whether the event is currently signaled.
//
//*****************************************************************************
bool event::is_signaled() const
{

#ifdef WINDOWS

   return WAIT_OBJECT_0 == ::WaitForSingleObjectEx((HANDLE)m_hsync,0,false);

#elif defined(ANDROID)

   if(m_bManualEvent)
   {

      return m_bSignaled;

   }
   else
   {

      return ((event *)this)->wait({ e_zero });

   }


#else

   if(m_bManualEvent)
   {

      return m_bSignaled;

   }
   else
   {

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = IPC_NOWAIT;

      i32 ret = semop((i32) m_sem, &sb, 1);

      if(ret < 0)
      {
         if(ret == EPERM)
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }

   }

#endif

}
//end**************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//end**************************************************************************

//bool event::lock(const class ::wait & wait)
//{
//
//   return wait(durationTimeout).succeeded();
//
////#ifdef WINDOWS
////
////   u32 dwRet = ::WaitForSingleObjectEx((HANDLE)m_hsync,durationTimeout.u32_millis(),false);
////
////   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
////      return true;
////   else
////      return false;
////
////#elif defined(ANDROID)
////
////   pthread_mutex_lock((pthread_mutex_t *) m_mutex);
////
////   ((duration & ) durationTimeout).normalize();
////
////
////   if(m_bManualEvent)
////   {
////
////      i32 iSignal = m_iSignalId;
////
////      while(!m_bSignaled && iSignal == m_iSignalId)
////      {
////
////         timespec delay;
////         delay.tv_sec = durationTimeout.m_i;
////         delay.tv_nsec = durationTimeout.m_i;
////         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex, &delay))
////            break;
////
////      }
////
////      return m_bSignaled;
////
////   }
////   else
////   {
////
////      timespec delay;
////      delay.tv_sec = durationTimeout.m_i;
////      delay.tv_nsec = durationTimeout.m_i;
////      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_mutex, &delay);
////
////      return is_locked();
////
////   }
////
////   pthread_mutex_unlock((pthread_mutex_t *) m_mutex);
////
////#else
////
////
////   timespec delay;
////
////
////   if(m_bManualEvent)
////   {
////
////      wait(durationTimeout);
////
////      return m_bSignaled;
////
////   }
////   else
////   {
////
////      u32 timeout = durationTimeout.u32_millis();
////
////      u32 start= ::duration::now();
////
////      while(start.elapsed() < timeout)
////      {
////
////         sembuf sb;
////
////         sb.sem_op   = -1;
////         sb.sem_num  = 0;
////         sb.sem_flg  = IPC_NOWAIT;
////
////         i32 ret = semop((i32) m_hsync, &sb, 1);
////
////         if(ret < 0)
////         {
////            if(ret == EPERM)
////            {
////               nanosleep(&delay, nullptr);
////            }
////            else
////            {
////               return false;
////            }
////         }
////         else
////         {
////            return true;
////         }
////
////      }
////
////   }
////
////   return false;
////
////#endif
//
//}


void event::unlock()
{

   //return true;

}


//HSYNC event::hsync() const
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   return m_hsync;
//
//#else
//
//   return (event *) this;
//
//#endif
//
//}



