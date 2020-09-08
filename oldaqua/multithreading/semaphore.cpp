#include "framework.h"


#if defined(LINUX) || defined(__APPLE__)
#include <sys/ipc.h>
#include <sys/sem.h>
#include "aqua/os/ansios/_ansios.h"
#elif defined(ANDROID)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "aqua/os/ansios/_ansios.h"
#endif


semaphore::semaphore(LONG lInitialCount, LONG lMaxCount, const char * pstrName, LPSECURITY_ATTRIBUTES psaAttributes)
{

   ASSERT(lMaxCount > 0);
   ASSERT(lInitialCount <= lMaxCount);

#ifdef WINDOWS

   m_hsync = ::CreateSemaphoreExW(psaAttributes, lInitialCount, lMaxCount, pstrName == nullptr ? nullptr : (const wchar_t *)  ::str::international::utf8_to_unicode(pstrName), 0, SEMAPHORE_MODIFY_STATE | DELETE | SYNCHRONIZE);

   if (m_hsync == nullptr)
      __throw(resource_exception());

#elif defined(ANDROID)


   m_lMaxCount    = lMaxCount;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      m_strName = "/aqua/time/ftok/event/" + string(pstrName);


      if((m_psem= sem_open(m_strName,O_CREAT | O_EXCL,0666,lInitialCount)) != SEM_FAILED)
      {

         // We got here first

      }
      else
      {

         if (errno != EEXIST)
            __throw(resource_exception());

         // We're not first.  Try again

         m_psem = sem_open(m_strName,0);

         if (m_psem == SEM_FAILED)
            __throw(resource_exception());

      }

   }
   else
   {

      m_psem = new sem_t;

      sem_init(m_psem, 0, lInitialCount);

   }

#else


   m_lMaxCount    = lMaxCount;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      string strPath;

      if(str::begins_ci(pstrName, "Local\\") || str::begins_ci(pstrName, "Local\\"))
      {
         strPath = Context.dir().home() / ".ca2/ftok/semaphore/" + string(pstrName);
      }
      else
      {
         strPath = "/var/tmp/ca2/ftok/semaphore/" + string(pstrName);
      }

      dir::mk(::file::path(strPath).folder());

      m_hsync = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);



   }
   else
   {

      m_hsync = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

   }

   semun semctl_arg;

   semctl_arg.val = lInitialCount;

   semctl(static_cast < i32 > (m_hsync), 0, SETVAL, semctl_arg);


#endif

}

semaphore::~semaphore()
{
}


#if defined(ANDROID)

sync_result semaphore::wait(const duration & durationTimeout)
{

   timespec ts;

   ((duration &)durationTimeout).normalize();

   ts.tv_nsec = durationTimeout.m_iNanoseconds;
   ts.tv_sec = durationTimeout.m_iSeconds;

   sem_timedwait(m_psem, &ts);

   return sync_result(sync_result::result_event0);


}

#elif defined(LINUX) || defined(SOLARIS)

sync_result semaphore::wait(const duration & durationTimeout)
{

   int iRet = 0;
   sembuf sb;

   sb.sem_num = 0;
   sb.sem_op = -1;
   sb.sem_flg = 0;

   if(durationTimeout.is_infinite())
   {

      iRet = semop(static_cast < i32 > (m_hsync), &sb, 1);
   }
   else
   {

      timespec ts;

      ((duration &)durationTimeout).normalize();

      ts.tv_nsec = durationTimeout.m_iNanoseconds;
      ts.tv_sec = durationTimeout.m_iSeconds;

      iRet = semtimedop(static_cast < i32 > (m_hsync), &sb, 1, &ts);

      if(iRet == EINTR || iRet == EAGAIN)
      {

         return sync_result::result_timeout;

      }

   }

   if(iRet == 0)
   {

      return sync_result::result_event0;

   }
   else
   {

      return sync_result::result_error;

   }

}


#elif defined(__APPLE__)

//::mutex * g_pmutexSemaphore = nullptr;
//
//comparable_array < pthread_t > * g_pthreadaSemaphore = nullptr;
//
//void semaphore_timer_handler (int signum)
//{
//
//   sync_lock sl(g_pmutexSemaphore);
//
//   if(g_pthreadaSemaphore != nullptr)
//   {
//
//      for(index i = 0; i < g_pthreadaSemaphore->get_count() ; i++)
//      {
//
//         signal(SIGALRM, SIG_DFL);
//
//         pthread_kill(g_pthreadaSemaphore->element_at(i), SIGALRM);
//
//      }
//
//   }
//
//}

//void semaphore_user1_handler (int signum)
//{
//
//}


sync_result semaphore::wait(const duration & durationTimeout)
{

//   struct sigaction alarm;
//
//   struct sigaction alarmPrevious;
//
//   struct sigaction user1;
//
//   struct sigaction user1Previous;
//
//   struct itimerval timer;
//
   if(durationTimeout.is_infinite())
   {

      struct sembuf sb;

      sb.sem_num  = 0;
      sb.sem_op   = -1;
      sb.sem_flg  = 0;

      int i = semop(static_cast < i32 > (m_hsync), &sb, 1);

      return i == 0 ? sync_result::result_event0 : sync_result::result_error;

   }


   tick tStart;

   tStart = tick::now();

   struct sembuf sb;

   sb.sem_num  = 0;
   sb.sem_op   = -1;
   sb.sem_flg  = IPC_NOWAIT;

   while(true)
   {

      int i = semop(static_cast < i32 > (m_hsync), &sb, 1);

      if(i == 0)
      {

         return sync_result::result_event0;

      }

      if(errno == EAGAIN)
      {

         thread_sleep(100);

         tick tRemaining = durationTimeout - tStart.elapsed();

         if(tRemaining > durationTimeout)
         {

            return sync_result::result_timeout;

         }

      }
      else
      {

         return sync_result::result_error;

      }

   }

}


#endif



bool semaphore::unlock(LONG lCount, LPLONG pPrevCount)

{

#ifdef WINDOWS

   return ::ReleaseSemaphore(m_hsync, lCount, pPrevCount) != FALSE;


#elif defined(ANDROID)

   int val;

   if (sem_getvalue(m_psem, &val) != 0)
   {

      return false;

   }

   if(pPrevCount !=  nullptr)

   {

      *pPrevCount = val;


   }

   if(lCount + val > m_lMaxCount)
   {

      return false;

   }

   while (lCount > 0)
   {

      sem_post(m_psem);

      lCount--;

   }



   return true;

#elif defined(__APPLE__)

   struct sembuf sb;

   sb.sem_num  = 0;
   sb.sem_op   = 1;
   sb.sem_flg  = 0;

   int i = semop(static_cast < i32 > (m_hsync), &sb, 1);

   return i == 0 ? true : false;

#else

   semun semctl_arg;

   semctl(static_cast < i32 > (m_hsync), 0, GETVAL, semctl_arg);

   if(pPrevCount !=  nullptr)

   {

      *pPrevCount = semctl_arg.val;


   }

   if(lCount + semctl_arg.val > m_lMaxCount)
   {

      return false;

   }

   semctl_arg.val += lCount;

   semctl(static_cast < i32 > (m_hsync), 0, SETVAL, semctl_arg);

   return true;

#endif

}

bool semaphore::unlock()
{

   return unlock(1, nullptr);

}

