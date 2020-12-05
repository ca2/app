#include "framework.h"

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#endif

condition::condition()
{
#ifdef WINDOWS

   //    ::InitializeCriticalSection(&m_sect);

   ::InitializeCriticalSectionEx(&m_sect, 4000, 0);

   ::InitializeConditionVariable(&m_var);
#elif defined(ANDROID)

   pthread_mutex_init(&m_mutex, nullptr);

   pthread_cond_init(&m_cond, nullptr);

   m_iHold = 0;

   m_bSignaled = false;

#else

   /*
      if(pstrName != nullptr && *pstrName != '\0')
      {
         string strPath = "/acme/time/ftok/condition/" + string(pstrName);

         m_hsync = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);
      }
      else
   */
   {
      m_hsync = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
   }

   /*

      semun semctl_arg;

      if(bSet)
      {
         semctl_arg.val = 1;
      }
      else
      {
         semctl_arg.val = 0;
      }

      semctl((i32) m_hsync, 0, SETVAL, semctl_arg);

   */

#endif
}

condition::~condition()
{
#ifdef WINDOWS

   ::DeleteCriticalSection(&m_sect);

#endif
}

bool condition::SetEvent()
{
#ifdef WINDOWS

   WakeAllConditionVariable(&m_var);

   return true;

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   if (!m_bSignaled)
   {
      m_bSignaled = true;

      pthread_mutex_unlock(&m_mutex);

      pthread_cond_signal(&m_cond);
   }
   else
   {
      pthread_mutex_unlock(&m_mutex);
   }

   return true;

#else

   sembuf sb;

   sb.sem_op = 1;
   sb.sem_num = 0;
   sb.sem_flg = SEM_UNDO;

   return semop((i32)m_hsync, &sb, 1) == 0;

#endif
}

bool condition::pulse()
{
#ifdef WINDOWS

   WakeAllConditionVariable(&m_var);

   return true;

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   if (m_iHold > 0)
   {
      m_bSignaled = true;

      pthread_mutex_unlock(&m_mutex);

      pthread_cond_signal(&m_cond);

      pthread_mutex_lock(&m_mutex);

      while (m_iHold > 0)
      {
         sleep(1);
      }

      m_bSignaled = false;

      pthread_mutex_unlock(&m_mutex);
   }
   else
   {
      pthread_mutex_unlock(&m_mutex);
   }

   return true;

#else

   sembuf sb;

   sb.sem_op = 1;
   sb.sem_num = 0;
   sb.sem_flg = SEM_UNDO;

   return semop((i32)m_hsync, &sb, 1) == 0;

#endif
}

sync_result condition::wait()
{
#ifdef WINDOWS

   SleepConditionVariableCS(&m_var, &m_sect, U32_INFINITE_TIMEOUT);

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   m_iHold++;

   while (!m_bSignaled)
   {
      pthread_cond_wait(&m_cond, &m_mutex);
   }

   pthread_mutex_unlock(&m_mutex);

   pthread_mutex_lock(&m_mutex);

   m_iHold--;

   pthread_mutex_unlock(&m_mutex);

#else

   sembuf sb;

   sb.sem_op = -1;
   sb.sem_num = 0;
   sb.sem_flg = 0;

   semop((i32)m_hsync, &sb, 1);

#endif

   return sync_result(sync_result::result_event0);
}

///  \brief		waits for an condition for a specified time
///  \lparam		duration time period to wait for an condition
///  \return	waiting action result as WaitResult
sync_result condition::wait(const duration& duration)
{

#ifdef WINDOWS

   u32 timeout = duration.u32_millis();

   return sync_result(SleepConditionVariableCS(&m_var, &m_sect, timeout));

#elif defined(ANDROID)

   u32 timeout = duration.u32_millis();

   pthread_mutex_lock(&m_mutex);

   m_iHold++;

   millis start;

   start.Now();

   while (!m_bSignaled)
   {

      pthread_cond_wait(&m_cond, &m_mutex);

      if (start.elapsed() > duration)
      {

         m_iHold--;

         return ::sync_result(::sync_result::result_timeout);

      }

   }

   m_iHold--;

   pthread_mutex_unlock(&m_mutex);

   return ::sync_result(::sync_result::result_event0);

#else

   auto start = ::millis::now();

   timespec delay;

   delay.tv_sec = 0;

   delay.tv_nsec = 1000000;

   while (duration.is_pos_infinity() || start.elapsed() < duration)
   {

      sembuf sb;

      sb.sem_op = -1;
      sb.sem_num = 0;
      sb.sem_flg = IPC_NOWAIT;

      i32 ret = semop((i32)m_hsync, &sb, 1);

      if (ret < 0)
      {

         if (ret == EPERM)
         {

            nanosleep(&delay, nullptr);

         }
         else
         {

            return ::sync_result::result_error;

         }

      }
      else
      {

         return ::sync_result::result_event0;

      }

   }

   return sync_result(sync_result::result_timeout);

#endif

}


//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an condition has
//                      occurred.
//
//*****************************************************************************
//*****************************************************************************
//
//      Name:           Signaled
//      Description:    Determines whether the condition is currently signaled.
//
//*****************************************************************************
bool condition::is_signaled() const
{
#ifdef ANDROID

   return m_bSignaled;

#endif

   __throw(not_supported_exception());
}

//end**************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an condition has
//                      occurred.
//
//end**************************************************************************

bool condition::lock(const duration& durationTimeout)
{
#ifdef WINDOWS

   if (SleepConditionVariableCS(&m_var, &m_sect, durationTimeout.u32_millis()) != FALSE)
      return true;
   else
      return false;

#elif defined(ANDROID)

   return wait(durationTimeout).succeeded();

#else

   u32 timeout = durationTimeout.u32_millis();

   auto start = ::millis::now();

   timespec delay;

   delay.tv_sec = 0;
   delay.tv_nsec = 1000000;

   while (start.elapsed() < timeout)
   {
      sembuf sb;

      sb.sem_op = -1;
      sb.sem_num = 0;
      sb.sem_flg = IPC_NOWAIT;

      i32 ret = semop((i32)m_hsync, &sb, 1);

      if (ret < 0)
      {
         if (ret == EPERM)
         {
            nanosleep(&delay, nullptr);
         }
         else
         {
            return false;
         }
      }
      else
      {
         return true;
      }
   }

   return false;

#endif
}

bool condition::ResetEvent()
{
#ifdef ANDROID

   pthread_mutex_lock(&m_mutex);

   m_iHold = 0;

   m_bSignaled = false;

   pthread_mutex_unlock(&m_mutex);

   pthread_cond_signal(&m_cond);

#endif

   return true;
}

bool condition::unlock()
{
   return ResetEvent();
}

void* condition::get_os_data() const
{
   __throw(not_supported_exception());
}
