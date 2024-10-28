#include "framework.h"
#include "event.h"

////#include "acme/exception/exception.h"
#include "acme/prototype/time/timespec.h"
#include "acme/_operating_system.h"


#ifdef PARALLELIZATION_PTHREAD
#include "acme/operating_system/ansi/_pthread.h"
#endif

void printf_line(const ::ansi_character * pszFormat, ...);

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(__BSD__)
#include <sys/ipc.h>
#include <sys/time.h>
#include <time.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <string.h>

#if defined(LINUX) || defined(__APPLE__)
#include <sys/sem.h>
#endif
#include "acme/operating_system/ansi/_ansi.h"

#if defined(OPENBSD) || defined(NETBSD)

#include <stdio.h>

#endif


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


::i32 g_iEventSerialId = 1;

event::event(const ::scoped_string & scopedstrName, bool bInitiallyOwn, bool bManualReset, security_attributes * psecurityattributes)
{

   {

      critical_section_lock lock(::platform::get()->globals_critical_section());

      m_iEventSerialId = g_iEventSerialId++;

   }

#ifdef EVENT_EXTENDED_LOG

   printf_line("event(%d)::event", m_iEventSerialId);

#endif

#ifdef WINDOWS_DESKTOP

   m_handle = ::CreateEventW(
      (LPSECURITY_ATTRIBUTES)(psecurityattributes ? psecurityattributes->get_os_security_attributes() : nullptr),
      bManualReset, 
      bInitiallyOwn, scopedstrName.is_empty() ? nullptr : wstring(scopedstrName).c_str());

   if (m_handle == NULL)
   {

      throw ::exception(error_resource);

   }

#elif defined(UNIVERSAL_WINDOWS)

   u32 dwFlags = 0;

   if(bInitiallyOwn)
   {

      dwFlags |= CREATE_EVENT_INITIAL_SET;

   }

   if(bManualReset)
   {

      dwFlags |= CREATE_EVENT_MANUAL_RESET;

   }

   m_handle = ::CreateEventEx(
      (LPSECURITY_ATTRIBUTES)(psecurityattributes ? psecurityattributes->get_os_security_attributes() : nullptr),
      scopedstrName.is_empty() ? nullptr : wstring(scopedstrName).c_str(),
      dwFlags,
      DELETE | EVENT_MODIFY_STATE | SYNCHRONIZE);

   if (m_handle == nullptr)
   {

      throw ::exception(error_resource);

   }

#elif defined(ANDROID)

   m_sem = -1;

   m_pcond = ___new pthread_cond_t();

   pthread_cond_init((pthread_cond_t *) m_pcond, nullptr);

   m_bManualEvent = bManualReset;

   if(m_bManualEvent)
   {

      m_bSignaled = bInitiallyOwn;
      pthread_mutexattr_t  attr;
      pthread_mutexattr_init(&attr);
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      i32 rc;
      m_pmutex = ___new pthread_mutex_t();
      if((rc = pthread_mutex_init((pthread_mutex_t *) m_pmutex,&attr)))
      {
         throw ::exception(error_failed, "RC_OBJECT_NOT_CREATED");
      }

   }
   else
   {
      m_pmutex = nullptr;
   }

#else

   m_bManualEvent    = bManualReset;

   if(bManualReset)
   {

      //pthread_mutex m;

      //auto s1  = sizeof(pthread_mutex);
      //printf_line("MUTEX1 SIZE!!!! %llu", s1);
      pthread_mutex_t mt;

      //auto smt  = sizeof(mt);
      //printf_line("MUTEXMT SIZE!!!! %llu", smt);
      //m_pmutex = ___new pthread_mutex_t();
      m_pmutex = ::malloc(sizeof(pthread_mutex_t));

      //auto s  = sizeof(pthread_mutex_t);

      //printf_line("MUTEX SIZE!!!! %llu", s);

      ::memory_set(m_pmutex, 0, sizeof(pthread_mutex_t));

      m_pcond = ::malloc(sizeof(pthread_cond_t));

      ::memory_set(m_pcond, 0, sizeof(pthread_cond_t));

      //pthread_mutexattr_t attr;

      //pthread_mutexattr_init(&attr);

      //pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

      //auto rcMutex = pthread_mutex_init((pthread_mutex_t *) m_pmutex, &attr);

      auto rcMutex = pthread_mutex_init((pthread_mutex_t *) m_pmutex, nullptr);

#ifdef EVENT_EXTENDED_LOG

      printf_line("event(%d)::event pthread_mutex_init %d %llX", m_iEventSerialId, rcMutex, (::uptr) m_pmutex);

#endif

      auto rcCond = pthread_cond_init((pthread_cond_t *) m_pcond, nullptr);

#ifdef EVENT_EXTENDED_LOG

      printf_line("event(%d)::event pthread_cond_init %d %llX", m_iEventSerialId, rcCond, (::uptr) m_pcond);

#endif

      m_bSignaled = bInitiallyOwn;

      m_sem = -1;

   }
   else
   {

#ifdef EVENT_EXTENDED_LOG

      printf_line("AUTOMATIC EVENT");

#endif

      m_pmutex = nullptr;

      m_pcond = nullptr;

      if(scopedstrName.has_char())
      {

         string strPath = "/var/tmp/ca2/ftok/event/" + string(scopedstrName);

         m_sem = semget(ftok(strPath.c_str(), 0), 1, 0666 | IPC_CREAT);

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

// #if defined(LINUX)
//
//    semun ignored_argument{};
//
//    semctl(m_sem, 0, IPC_RMID, ignored_argument);
//
//    if(m_pcond != nullptr)
//    {
//       pthread_cond_destroy(m_pcond);
//       __call__delete((pthread_cond_t *)m_pcond);
//       m_pcond = nullptr;
//    }
//    if(m_pmutex != nullptr)
//    {
//       pthread_mutex_destroy((pthread_mutex_t *)m_pmutex);
//       __call__delete ((pthread_mutex_t *)m_pmutex);
//       m_pmutex = nullptr;
//    }
#if defined(ANDROID)

   if(m_pcond != nullptr)
   {
      pthread_cond_destroy(m_pcond);
      __call__delete((pthread_cond_t *)m_pcond);
      m_pcond = nullptr;
   }
   if(m_pmutex != nullptr)
   {
      pthread_mutex_destroy((pthread_mutex_t *)m_pmutex);
      __call__delete ((pthread_mutex_t *)m_pmutex);
      m_pmutex = nullptr;
   }

#elif !defined(WINDOWS)

   if(m_sem != -1)
   {

      semun ignored_argument{};

      auto rc = semctl(m_sem, 0, IPC_RMID, ignored_argument);

      m_sem = -1;

#ifdef EVENT_EXTENDED_LOG

      printf_line("semctl IPC_RMID %d", rc);

#endif

   }

   if(m_bManualEvent)
   {

      //try { throw "event being destroyed"; } catch(...){}

#ifdef EVENT_EXTENDED_LOG

      printf_line("event(%d)::~event Going to destroy a manual reset event", m_iEventSerialId);

#endif

      if(m_pmutex != nullptr && m_pcond != nullptr)
      {

         int rc1 = pthread_mutex_lock((pthread_mutex_t *)m_pmutex);

         set_finishing_flag();

         int rc2 = pthread_cond_broadcast((pthread_cond_t *)m_pcond);

         int rc3 = pthread_mutex_unlock((pthread_mutex_t *)m_pmutex);

         _wait();

         int rc4 = pthread_mutex_lock((pthread_mutex_t *)m_pmutex);

         int rc5 = pthread_cond_destroy((pthread_cond_t *)m_pcond);

         ::free((pthread_cond_t *)m_pcond);

         m_pcond = nullptr;

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::~event pthread_cond_destroy %d", m_iEventSerialId, rc5);

#endif

         int rc6 = pthread_mutex_unlock((pthread_mutex_t *)m_pmutex);

         int rc7 = pthread_mutex_destroy((pthread_mutex_t *)m_pmutex);

         ::free((pthread_mutex_t *)m_pmutex);

         m_pmutex = nullptr;

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::~event pthread_mutex_destroy %d", m_iEventSerialId, rc7);

#endif

      }
      else if(m_pcond != nullptr)
      {

         int rc5 = pthread_cond_destroy((pthread_cond_t *)m_pcond);

         ::free((pthread_cond_t *)m_pcond);

         m_pcond = nullptr;

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::~event pthread_cond_destroy (2) %d", m_iEventSerialId, rc5);

#endif

      }
      else if(m_pmutex != nullptr)
      {

         int rc7 = pthread_mutex_destroy((pthread_mutex_t *)m_pmutex);

         ::free((pthread_mutex_t *)m_pmutex);

         m_pmutex = nullptr;

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::~event pthread_mutex_destroy (2) %d", m_iEventSerialId, rc7);

#endif

      }

   }

#endif

}


#ifdef WINDOWS


hsynchronization event::get_synchronization_handle()
{

   return m_handle;

}


#endif


bool event::SetEvent()
{

#ifdef WINDOWS

   if (m_handle == nullptr)
   {

      ASSERT(false);

      return false;

   }

   try
   {

      return ::SetEvent((HANDLE)m_handle) != false;

   }
   catch(...)
   {
   }

   return false;

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

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

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   return true;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast((pthread_cond_t *) m_pcond);

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

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
//   ASSERT(m_hsynchronization != nullptr);
//
//   return ::PulseEvent(m_hsynchronization) != false;
//
//#else
//
//   sembuf sb;
//
//   sb.sem_op   = 1;
//   sb.sem_num  = 0;
//   sb.sem_flg  = SEM_UNDO;
//
//   return semop((i32) m_hsynchronization, &sb, 1) == 0;
//
//#endif
//
//}



bool event::ResetEvent()
{

#ifdef WINDOWS

   try
   {

      if(m_handle == NULL)
      {

         informationf("error reset event (1)");

         return false;

      }

      return ::ResetEvent((HANDLE)m_handle) != false;

   }
   catch(...)
   {

      informationf("error reset event (2)");

   }

   return false;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      m_bSignaled = false;

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

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

      int iResult = ::WaitForSingleObjectEx(m_handle, 300, false);

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

         auto u = ::GetLastError();

         throw ::exception(error_failed);

      }

   }

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   if(m_bManualEvent)
   {

      i32 iSignal = m_iSignalId;

      while(!has_finishing_flag() && !m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

      }

   }
   else
   {

      pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   if(has_finishing_flag())
   {

      throw ::exception(error_cancelled);

   }
   else if(!m_bSignaled)
   {

      throw ::exception(error_failed);

   }

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      int iSignal = m_iSignalId;

      while(!has_finishing_flag() && !m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

      }

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

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


bool event::_wait (const class time & timeWait)
{

   ::e_status estatus;

   //throw ::exception(todo("thread"));
   //if(timeTimeout > 1_s && m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->add_waiting_event(this);

   //   }

   //}


#ifdef WINDOWS

   DWORD dwResult = ::WaitForSingleObjectEx(m_handle, ::windows::wait(timeWait), false);

   estatus = ::windows::wait_result_status(dwResult, 1);

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

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   if(m_bManualEvent)
   {

      timespec end;

      clock_gettime(CLOCK_REALTIME, &end);

      end += timeWait;

      i32 iSignal = m_iSignalId;

      while(!has_finishing_flag() && !m_bSignaled && iSignal == m_iSignalId)
      {

         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &end))
            break;

      }

   }
   else
   {

      timespec delay;
      
      ::copy(delay, timeWait);

      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   return m_bSignaled;

#else

   if(m_bManualEvent)
   {

#ifdef EVENT_EXTENDED_LOG

      printf_line("event(%d)::_wait(timeWait(m_iSecond=%lld,m_iNanosecond=%lld,c=%llX,m=%llX))", m_iEventSerialId, timeWait.m_iSecond, timeWait.m_iNanosecond, m_pcond, m_pmutex);

#endif

      if(timeWait.is_infinite())
      {

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::_wait(infinite)", m_iEventSerialId);

#endif

         pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::_wait(infinite) mutex locked", m_iEventSerialId);

#endif

         int iSignal = m_iSignalId;

         //clock_gettime(CLOCK_REALTIME, &abstime);

         //try { throw "event::_wait(FINite) mutex locked 2"; } catch(...){}

         while(!has_finishing_flag() && !m_bSignaled && iSignal == m_iSignalId)
         {

            i32 error = pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

            if(error != 0)
            {

               printf_line("event(%d)::_wait(infinite) pthread_cond_wait returned error", m_iEventSerialId);

               break;

            }

         }

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::_wait(infinite) about to unlock mutex", m_iEventSerialId);

#endif

         pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

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

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::_wait(FINite)", m_iEventSerialId);

#endif

         auto iLock = pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::_wait(FINite) pthread_mutex_lock returned %d", m_iEventSerialId, iLock);

#endif

         int iSignal = m_iSignalId;

         timespec timespecNow{};

         clock_getrealtime(&timespecNow);

         timespec timespecWait{};

         copy(timespecWait, timeWait);

         timespec timespecFinal{};

         timespecFinal = timespecNow + timespecWait;

         ::i32 error = 0;

         //try { throw "event::_wait(FINite) mutex locked 2"; } catch(...){}

         while(true)
         {

            if(has_finishing_flag())
            {

               printf_line("event(%d)::_wait(FINite) has finishing flag", m_iEventSerialId);

               break;

            }

            if(m_bSignaled)
            {

#ifdef EVENT_EXTENDED_LOG

               printf_line("event(%d)::_wait(FINite) m_bSignaled", m_iEventSerialId);

#endif

               break;

            }

            if(iSignal != m_iSignalId)
            {

#ifdef EVENT_EXTENDED_LOG

               printf_line("event(%d)::_wait(FINite) iSignal != m_iSignalId", m_iEventSerialId);

#endif

               break;

            }
            
            clock_getrealtime(&timespecNow);

            if(timespecNow > timespecFinal)
            {
               
               error = ETIMEDOUT;

#ifdef EVENT_EXTENDED_LOG

               printf_line("event(%d)::_wait(FINite) timespecNow > timespecFinal", m_iEventSerialId);

#endif

               break;
               
            }

            error = pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &timespecFinal);
               
            if(error != 0)
            {

#ifdef EVENT_EXTENDED_LOG

               printf_line("event(%d)::_wait(FINite) pthread_cond_timedwait returned(%d, %s)", m_iEventSerialId, error, strerror(error));

#endif

               break;

            }

#ifdef EVENT_EXTENDED_LOG

            printf_line("event(%d)::_wait(FINite) pthread_cond_timedwait returned 0");

#endif

         }

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::_wait(FINite) going to unlock mutex", m_iEventSerialId);

#endif

         auto iUnlock = pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

#ifdef EVENT_EXTENDED_LOG

         printf_line("event(%d)::_wait(FINite) pthread_mutex_unlock returned(%d)", m_iEventSerialId, iUnlock);

#endif

         if(m_bSignaled)
         {

            return true;

         }
         else if(error == ETIMEDOUT)
         {

            return false;

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

      auto start = ::time::now();

      while(timeWait.is_infinite() || start.elapsed() < timeWait)
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
   //if(timeTimeout > 1_s && m_eobject & e_object_alertable_wait)
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

   return WAIT_OBJECT_0 == ::WaitForSingleObjectEx((HANDLE)m_handle,0,false);

#elif defined(ANDROID)

   if(m_bManualEvent)
   {

      return m_bSignaled;

   }
   else
   {

      return ((event *)this)->wait({ zero_t{} }).ok();

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

//bool event::lock(const class time & timeWait)
//{
//
//   return wait(timeTimeout).succeeded();
//
////#ifdef WINDOWS
////
////   u32 dwRet = ::WaitForSingleObjectEx((HANDLE)m_hsynchronization,timeTimeout.u32_millis(),false);
////
////   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
////      return true;
////   else
////      return false;
////
////#elif defined(ANDROID)
////
////   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);
////
////   ((time & ) timeTimeout).normalize();
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
////         delay.tv_sec = timeTimeout.m_i;
////         delay.tv_nsec = timeTimeout.m_i;
////         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay))
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
////      delay.tv_sec = timeTimeout.m_i;
////      delay.tv_nsec = timeTimeout.m_i;
////      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay);
////
////      return is_locked();
////
////   }
////
////   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);
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
////      wait(timeTimeout);
////
////      return m_bSignaled;
////
////   }
////   else
////   {
////
////      u32 timeout = timeTimeout.u32_millis();
////
////      u32 start= ::time::now();
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
////         i32 ret = semop((i32) m_hsynchronization, &sb, 1);
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
//   return m_hsynchronization;
//
//#else
//
//   return (event *) this;
//
//#endif
//
//}



