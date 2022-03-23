#include "framework.h"
#include "acme/operating_system.h"
#include "acme/filesystem/filesystem/acme_directory.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#if defined(LINUX) || defined(__APPLE__) || defined(FREEBSD)
#include <sys/ipc.h>
#include <sys/sem.h>
#include "acme/operating_system/ansi/_ansi.h"
#elif defined(ANDROID)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "acme/operating_system/ansi/_ansi.h"
#endif


semaphore::semaphore(::i32 lInitialCount, ::i32 lMaxCount, const char * pstrName ARG_SEC_ATTRS)
{

   ASSERT(lMaxCount > 0);
   ASSERT(lInitialCount <= lMaxCount);

#ifdef WINDOWS

   m_hsync = ::CreateSemaphoreExW((LPSECURITY_ATTRIBUTES)PARAM_SEC_ATTRS, lInitialCount, lMaxCount, pstrName == nullptr ? nullptr : (const wchar_t *)  ::str::international::utf8_to_unicode(pstrName), 0, SEMAPHORE_MODIFY_STATE | DELETE | SYNCHRONIZE);

   if (m_hsync == nullptr)
   {

      throw ::exception(error_resource);

   }

#elif defined(ANDROID)


   m_lMaxCount    = lMaxCount;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      m_strName = "/acme/time/ftok/event/" + string(pstrName);


      if((m_psem= sem_open(m_strName,O_CREAT | O_EXCL,0666,lInitialCount)) != SEM_FAILED)
      {

         // We got here first

      }
      else
      {

         if (errno != EEXIST)
            throw ::exception(error_resource);

         // We're not first.  Try again

         m_psem = sem_open(m_strName,0);

         if (m_psem == SEM_FAILED)
            throw ::exception(error_resource);

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

      auto psystem = m_psystem;

      auto pacmedirectory = psystem->m_pacmedirectory;

      if(str::begins_ci(pstrName, "Local\\") || str::begins_ci(pstrName, "Local\\"))
      {

         strPath = pacmedirectory->home() / ".ca2/ftok/semaphore/" + string(pstrName);

      }
      else
      {

         strPath = "/::payload/tmp/ca2/ftok/semaphore/" + string(pstrName);

      }

      pacmedirectory->create(::file::path(strPath).folder());

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


#ifdef FREEBSD

int
_semtimedop(int semid, struct sembuf *array, size_t nops, struct
   timespec *_timeout);


#endif

#if defined(ANDROID)

synchronization_result semaphore::wait(const duration & durationTimeout)
{

   timespec ts;

   ((duration &)durationTimeout).normalize();

   ts.tv_nsec = durationTimeout.m_nanos.m_i;
   ts.tv_sec = durationTimeout.m_secs.m_i;

   sem_timedwait(m_psem, &ts);

   return synchronization_result(e_synchronization_result_signaled_base);


}

#elif defined(LINUX) || defined(SOLARIS) || defined(FREEBSD)

bool semaphore::wait(const class ::wait & wait)
{

   int iRet = 0;
   sembuf sb;

   sb.sem_num = 0;
   sb.sem_op = -1;
   sb.sem_flg = 0;

   if(wait.is_infinite())
   {

      iRet = semop(static_cast < i32 > (m_hsync), &sb, 1);
   }
   else
   {

      timespec timespec;

      timespec += wait;

#ifdef FREEBSD
      iRet = _semtimedop(static_cast < i32 > (m_hsync), &sb, 1, &timespec);
#else
      iRet = semtimedop(static_cast < i32 > (m_hsync), &sb, 1, &timespec);

#endif

      if(iRet == EINTR || iRet == EAGAIN)
      {

         return error_wait_timeout;

      }

   }

   if(iRet == 0)
   {

      return signaled_base;

   }
   else
   {

      return error_failed;

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
//   synchronous_lock synchronouslock(g_pmutexSemaphore);
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


bool semaphore::wait(const class ::wait & wait)
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
   if(wait.is_infinite())
   {

      struct sembuf sb;

      sb.sem_num  = 0;
      sb.sem_op   = -1;
      sb.sem_flg  = 0;

      int i = semop(static_cast < i32 > (m_hsync), &sb, 1);
      
      if(i != 0)
      {
         
         throw ::exception(error_exception);
         
      }

      return true;

   }

   ::duration tStart;

   tStart = ::duration::now();

   struct sembuf sb;

   sb.sem_num  = 0;
   sb.sem_op   = -1;
   sb.sem_flg  = IPC_NOWAIT;

   while(true)
   {

      int i = semop(static_cast < i32 > (m_hsync), &sb, 1);

      if(i == 0)
      {

         return true;

      }

      if(errno == EAGAIN)
      {

         //task_sleep(100_ms);

         preempt(100_ms);

         ::duration tRemaining = wait - tStart.elapsed();

         if(tRemaining > wait)
         {

            return false;

         }

      }
      else
      {

         throw ::exception(error_exception);

      }

   }

}


#endif



void semaphore::unlock(::i32 lCount, ::i32 * pPrevCount)
{

#ifdef WINDOWS

   /*return */ ::ReleaseSemaphore(m_hsync, lCount, (LPLONG)pPrevCount) /*  != false */;

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

      throw ::exception(error_failed);

   }

   semctl_arg.val += lCount;

   semctl(static_cast < i32 > (m_hsync), 0, SETVAL, semctl_arg);

   //return true;

#endif

}


void semaphore::unlock()
{

   /*return*/ unlock(1, nullptr);

}

