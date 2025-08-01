#include "framework.h"
#include "semaphore.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/directory_system.h"
//#include "acme/prototype/time/time.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/time/timespec.h"
#include "acme/_operating_system.h"


#ifdef PARALLELIZATION_PTHREAD
#include "acme/operating_system/ansi/_pthread.h"
#endif


#if defined(LINUX) || defined(__APPLE__) || defined(__BSD__)
#include <sys/ipc.h>
#include <sys/sem.h>
#include "acme/operating_system/ansi/_ansi.h"
#include <errno.h>
#elif defined(__ANDROID__)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "acme/operating_system/ansi/_ansi.h"
#endif


semaphore::semaphore(int lInitialCount, int lMaxCount, const_char_pointer pstrName, security_attributes * psecurityattributes)
{

   ASSERT(lMaxCount > 0);
   ASSERT(lInitialCount <= lMaxCount);

#ifdef WINDOWS

   wstring wstrName(pstrName);

   m_handleSemaphore = ::CreateSemaphoreExW(
      (LPSECURITY_ATTRIBUTES)(psecurityattributes ? psecurityattributes->get_os_security_attributes() : nullptr),
      lInitialCount,
      lMaxCount,
      pstrName == nullptr ? nullptr : (const wchar_t *)  wstrName, 
      0,
      SEMAPHORE_MODIFY_STATE | DELETE | SYNCHRONIZE);

   if (m_handleSemaphore == nullptr)
   {

      throw ::exception(error_resource);

   }

#elif defined(__ANDROID__)


   m_lMaxCount    = lMaxCount;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      m_strName = "/acme/time/ftok/happening/" + string(pstrName);


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

      m_psem = ___new sem_t();

      sem_init(m_psem, 0, lInitialCount);

   }

#else

   m_lMaxCount    = lMaxCount;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      string strPath;

      auto psystem = system();

      auto pdirectorysystem = psystem->m_pdirectorysystem;

      string strName(pstrName);

      if(strName.case_insensitive_begins("Local\\") || strName.case_insensitive_begins("Local\\"))
      {

         strPath = pdirectorysystem->home() / (".ca2/ftok/semaphore/" + strName);

      }
      else
      {

         strPath = "/var/tmp/ca2/ftok/semaphore/" + strName;

      }

      pdirectorysystem->create(::file::path(strPath).folder());

      m_hsync = semget(ftok(strPath.c_str(), 0), 1, 0666 | IPC_CREAT);

   }
   else
   {

      m_hsync = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

   }

   semun semctl_arg;

   semctl_arg.val = lInitialCount;

   semctl(static_cast < int > (m_hsync), 0, SETVAL, semctl_arg);

#endif

}

semaphore::~semaphore()
{
}


#if defined(__BSD__)

int
_semtimedop(int semid, struct sembuf *array, size_t nops, struct
   timespec *_timeout);


#endif
#if defined(WINDOWS)

CLASS_DECL_ACME bool _hsynchronization_wait(::hsynchronization h, const class ::time& timeWait);

bool semaphore::_wait(const class time& timeWait)
{

   return _hsynchronization_wait(m_handleSemaphore, timeWait);

}

#elif defined(__ANDROID__)

bool semaphore::_wait(const class time & timeWait)
{

   timespec timespec;

   ::copy(timespec, timeWait);

   auto iRet = sem_timedwait(m_psem, &timespec);

   if (iRet == ETIMEDOUT)
   {

      return false;

   }
   else if (iRet)
   {

      throw ::exception(::error_failed);

   }

   return true;


}

#elif defined(LINUX) || defined(SOLARIS) || defined(__BSD__)

bool semaphore::_wait(const class time & timeWait)
{

   int iRet = 0;
   sembuf sb;

   sb.sem_num = 0;
   sb.sem_op = -1;
   sb.sem_flg = 0;

   if(timeWait.is_infinite())
   {

      iRet = semop(static_cast < int > (m_hsync), &sb, 1);

   }
   else
   {

      timespec timespec;

      timespec += timeWait;

#if defined(__BSD__)
      iRet = _semtimedop(static_cast < int > (m_hsync), &sb, 1, &timespec);
#else
      iRet = semtimedop(static_cast < int > (m_hsync), &sb, 1, &timespec);

#endif

      if(iRet == EINTR || iRet == EAGAIN)
      {

         return false;

      }

   }

   if(iRet == 0)
   {

      return true;

   }
   else
   {

      throw ::exception(error_failed);

   }

}


#elif defined(__APPLE__)

//::pointer< ::mutex > g_pmutexSemaphore = nullptr;
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
//      for(::collection::index i = 0; i < g_pthreadaSemaphore->get_count() ; i++)
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


bool semaphore::_wait(const class time & timeWait)
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
   if(timeWait.is_infinite())
   {

      struct sembuf sb;

      sb.sem_num  = 0;
      sb.sem_op   = -1;
      sb.sem_flg  = 0;

      int i = semop(static_cast < int > (m_hsync), &sb, 1);
      
      if(i != 0)
      {
         
         throw ::exception(error_exception);
         
      }

      return true;

   }

   class ::time tStart;

   tStart = ::time::now();

   struct sembuf sb;

   sb.sem_num  = 0;
   sb.sem_op   = -1;
   sb.sem_flg  = IPC_NOWAIT;

   while(true)
   {

      int i = semop(static_cast < int > (m_hsync), &sb, 1);

      if(i == 0)
      {

         return true;

      }

      if(errno == EAGAIN)
      {

         //task_sleep(100_ms);

         preempt(100_ms);

         class ::time tRemaining = timeWait - tStart.elapsed();

         if(tRemaining > timeWait)
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


void semaphore::unlock(int lCount, int * pPrevCount)
{

#ifdef WINDOWS

   /*return */ ::ReleaseSemaphore(m_handleSemaphore, lCount, (LPLONG)pPrevCount) /*  != false */;

#elif defined(__ANDROID__)

   int val;

   if (sem_getvalue(m_psem, &val) != 0)
   {

      throw ::exception(error_failed);

   }

   if(pPrevCount !=  nullptr)
   {

      *pPrevCount = val;

   }

   if(lCount + val > m_lMaxCount)
   {

      throw ::exception(::error_failed);

   }

   while (lCount > 0)
   {

      sem_post(m_psem);

      lCount--;

   }



   //return true;

#elif defined(__APPLE__)

   struct sembuf sb;

   sb.sem_num  = 0;
   sb.sem_op   = 1;
   sb.sem_flg  = 0;

   int i = semop(static_cast < int > (m_hsync), &sb, 1);

   return i == 0 ? true : false;

#else

   semun semctl_arg;

   semctl(static_cast < int > (m_hsync), 0, GETVAL, semctl_arg);

   if(pPrevCount !=  nullptr)

   {

      *pPrevCount = semctl_arg.val;


   }

   if(lCount + semctl_arg.val > m_lMaxCount)
   {

      throw ::exception(error_failed);

   }

   semctl_arg.val += lCount;

   semctl(static_cast < int > (m_hsync), 0, SETVAL, semctl_arg);

   //return true;

#endif

}


void semaphore::unlock()
{

   /*return*/ unlock(1, nullptr);

}

