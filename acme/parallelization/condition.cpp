#include "framework.h"
#include "condition.h"
////#include "acme/exception/exception.h"
#include "acme/_operating_system.h"


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)

#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#endif

condition::condition()
{

#ifdef WINDOWS

#elif defined(ANDROID)

   pthread_mutex_init(m_pmutex, nullptr);

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

}


bool condition::SetEvent()
{
#ifdef WINDOWS

   WakeAllConditionVariable(&(CONDITION_VARIABLE&)m_conditionvariable);

   return true;

#elif defined(ANDROID)

   pthread_mutex_lock(m_pmutex);

   if (!m_bSignaled)
   {
      m_bSignaled = true;

      pthread_mutex_unlock(m_pmutex);

      pthread_cond_signal(&m_cond);
   }
   else
   {
      pthread_mutex_unlock(m_pmutex);
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

   WakeAllConditionVariable(&(CONDITION_VARIABLE &)m_conditionvariable);

   return true;

#elif defined(ANDROID)

   pthread_mutex_lock(m_pmutex);

   if (m_iHold > 0)
   {
      m_bSignaled = true;

      pthread_mutex_unlock(m_pmutex);

      pthread_cond_signal(&m_cond);

      pthread_mutex_lock(m_pmutex);

      while (m_iHold > 0)
      {
         
         preempt(1_ms);

      }

      m_bSignaled = false;

      pthread_mutex_unlock(m_pmutex);
   }
   else
   {
      pthread_mutex_unlock(m_pmutex);
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


::e_status condition::wait()
{


#ifdef WINDOWS

   SleepConditionVariableCS(
      &(CONDITION_VARIABLE &)m_conditionvariable,
      &(CRITICAL_SECTION&)m_criticalsection, 
      INFINITE);

#elif defined(ANDROID)

   pthread_mutex_lock(m_pmutex);

   m_iHold++;

   while (!m_bSignaled)
   {
      pthread_cond_wait(&m_cond, m_pmutex);
   }

   pthread_mutex_unlock(m_pmutex);

   pthread_mutex_lock(m_pmutex);

   m_iHold--;

   pthread_mutex_unlock(m_pmutex);

#else

   sembuf sb;

   sb.sem_op = -1;
   sb.sem_num = 0;
   sb.sem_flg = 0;

   int iError = semop((i32)m_hsync, &sb, 1);

   if(iError != 0)
   {

      return error_failed;

   }

#endif

   return ::success;

}


///  \brief		waits for an condition for a specified time
///  \lparam		duration time period to wait for an condition
///  \return	waiting action result as WaitResult
::e_status condition::wait(const class ::wait & wait)
{

#ifdef WINDOWS

   if (!SleepConditionVariableCS(
      &(CONDITION_VARIABLE &)m_conditionvariable,
      &(CRITICAL_SECTION &)m_criticalsection,
      wait))
   {

      DWORD dwLastError = ::GetLastError();

      if (dwLastError == ERROR_TIMEOUT)
      {

         return error_wait_timeout;

      }

      auto estatus = ::windows::last_error_status(dwLastError);

      return error_failed;

   }

   return ::success;

#elif defined(ANDROID)

   u32 timeout = wait;

   pthread_mutex_lock(m_pmutex);

   m_iHold++;

   ::duration start;

   start.Now();

   while (!m_bSignaled)
   {

      pthread_cond_wait(&m_cond, m_pmutex);

      if (start.elapsed() > wait)
      {

         m_iHold--;

         return error_wait_timeout;

      }

   }

   m_iHold--;

   pthread_mutex_unlock(m_pmutex);

   //return e_synchronization_result_signaled_base;
   return true;

#else

   auto start = ::duration::now();

   timespec delay;

   delay.tv_sec = 0;

   delay.tv_nsec = 1000000;

   while (wait.is_infinite() || start.elapsed() < wait)
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

            return error_failed;

         }

      }
      else
      {

         return ::success;

      }

   }

   return error_wait_timeout;

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

   throw ::exception(error_not_supported);

   return false;

}


////end**************************************************************************
////
////      Class:          manual_reset_event
////      Author:         Kenny Kerr
////      Date created:   10 April 2004
////      Description:    Notifies one or more waiting threads that an condition has
////                      occurred.
////
////end**************************************************************************
//
//bool condition::lock(const duration& durationTimeout)
//{
//#ifdef WINDOWS
//
//   if (SleepConditionVariableCS(
//      &(CONDITION_VARIABLE &)m_conditionvariable,
//      &(CRITICAL_SECTION &)m_criticalsection,
//      durationTimeout.u32_millis()) != false)
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      return false;
//
//   }
//
//#elif defined(ANDROID)
//
//   return wait(durationTimeout).succeeded();
//
//#else
//
//   u32 timeout = durationTimeout.u32_millis();
//
//   auto start = ::duration::now();
//
//   timespec delay;
//
//   delay.tv_sec = 0;
//   delay.tv_nsec = 1000000;
//
//   while (start.elapsed() < timeout)
//   {
//      sembuf sb;
//
//      sb.sem_op = -1;
//      sb.sem_num = 0;
//      sb.sem_flg = IPC_NOWAIT;
//
//      i32 ret = semop((i32)m_hsync, &sb, 1);
//
//      if (ret < 0)
//      {
//         if (ret == EPERM)
//         {
//            nanosleep(&delay, nullptr);
//         }
//         else
//         {
//            return false;
//         }
//      }
//      else
//      {
//         return true;
//      }
//   }
//
//   return false;
//
//#endif
//}

bool condition::ResetEvent()
{
#ifdef ANDROID

   pthread_mutex_lock(m_pmutex);

   m_iHold = 0;

   m_bSignaled = false;

   pthread_mutex_unlock(m_pmutex);

   pthread_cond_signal(&m_cond);

#endif

   return true;
}


void condition::unlock()
{

   //return ResetEvent();

   ResetEvent();

}


void* condition::get_os_data() const
{
   
   throw ::exception(error_not_supported);

   return nullptr;

}



