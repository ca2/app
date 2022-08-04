#include "framework.h"
#include "acme/operating_system.h"
#include "acme/filesystem/filesystem/acme_directory.h"


#ifdef MACOS
void utc_timespec(timespec * ptimespec);
#endif



#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#ifdef RASPBIAN
#define synchronization_object __unistd_sync
#include <sys/types.h>
#include <unistd.h>
#undef synchronization_object
#endif


#if defined(LINUX) || defined(SOLARIS) || defined(__APPLE__) || defined(FREEBSD)
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include "acme/operating_system/ansi/_pthread.h"
#undef USE_MISC


#elif defined(ANDROID)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "acme/operating_system/ansi/_pthread.h"
#endif

#if defined(FREEBSD)

#include	<sys/types.h>
#include	<sys/stat.h>
#include    <unistd.h>
#endif


static int g_iMutex = 0;



mutex::mutex(enum_create_new, bool bInitiallyOwn)
{

#ifdef _DEBUG
   m_itask = -1;
#endif

   m_bOwner = true;

   m_bAlreadyExists = false;

#ifdef WINDOWS

   m_hsync = ::CreateMutexExW(nullptr, nullptr, bInitiallyOwn ? CREATE_MUTEX_INITIAL_OWNER : 0, MUTEX_ALL_ACCESS);

   DWORD dwLastError = ::GetLastError();

   m_bAlreadyExists = dwLastError == ERROR_ALREADY_EXISTS;

#else

#if defined(MUTEX_NAMED_POSIX)

   m_psem = SEM_FAILED;

#elif defined(MUTEX_NAMED_FD)

   //m_count = 0;
   m_count = 0;

#elif defined(MUTEX_NAMED_POSIX)

   m_key = 0;

   m_semid = -1;

#endif

   {

      pthread_mutexattr_t attr;

      pthread_mutexattr_init(&attr);

      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

      pthread_mutex_init(&m_mutex, &attr);

#ifdef MUTEX_COND_TIMED

      pthread_cond_init(&m_cond, nullptr);

      m_count = 0;

      m_thread = 0;

#endif

   }

#endif

}


mutex::mutex(::object * pobject, bool bInitiallyOwn, const char * pstrName ARG_SEC_ATTRS)
{

#ifdef _DEBUG
   m_itask = -1;
#endif

   initialize(pobject);

   m_bAlreadyExists = false;

#ifdef WINDOWS

   wstring wstrName(pstrName);

   const unichar * pwszName = pstrName == nullptr ? nullptr : (const unichar *)wstrName;

   auto psa = (LPSECURITY_ATTRIBUTES)PARAM_SEC_ATTRS;

   m_hsync = ::CreateMutexExW(psa, pwszName, bInitiallyOwn ?  CREATE_MUTEX_INITIAL_OWNER : 0, MUTEX_ALL_ACCESS);

   DWORD dwLastError = ::GetLastError();

   m_bAlreadyExists = dwLastError == ERROR_ALREADY_EXISTS;

   if(m_hsync == nullptr)
   {

      DWORD dwError1 = ::GetLastError();

      if(pstrName != nullptr)
      {

         m_hsync = ::OpenMutexW(SYNCHRONIZE,false,utf8_to_unicode(pstrName));

      }

      if(m_hsync == nullptr)
      {

         DWORD dwError2 = ::GetLastError();

         throw ::exception(error_resource);

      }

   }

#else

#if defined(MUTEX_NAMED_POSIX)

   m_psem = SEM_FAILED;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      mutex() = nullptr;

      m_psem = nullptr;

      string strName(pstrName);

      strName.replace("/", "_");
      strName.replace(":", "_");
      strName.replace("/", "_");

      if(::str().begins_ci(pstrName, "Global"))
      {

#ifdef ANDROID

         strName = ::file::path(get_system()->m_pandroidinitdata->m_pszCacheDir) / "var/tmp" / strName;

#else

         strName = "/var/tmp" / strName;

#endif

      }
      else
      {

         strName = ::file::path(getenv("HOME")) / strName;

      }

               auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(::file::path(strName).folder());

      ::m_psystem->m_pacmefile->put_contents(strName, strName);

      string strTest = m_psystem->m_pacmefile->as_string(strName);

      //int isCreator = 0;

      if ((m_psem = sem_open(strName, O_CREAT|O_EXCL, 0644, 1)) != SEM_FAILED)
      {

         // We got here first

         //isCreator = 1;

      }
      else
      {

         int err = errno;

         if (err != EEXIST)
         {

            throw ::exception(error_resource);

         }

         // We're not first.  Try again

         m_psem = sem_open(strName, 0);

         if (m_psem == SEM_FAILED)
         {

            throw ::exception(resource_exception(););

         }

         m_pszName = strdup(strName);

      }

   }
   else

#elif defined(MUTEX_NAMED_FD)

   //m_count = 0;
   m_count = 0;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      set_last_status(::success);

      ::file::path path;

      if(::str().begins_ci(pstrName, "Global"))
      {

#ifdef ANDROID

         path = m_psystem->m_pacmedirectory->system() / "::payload/tmp/ca2/lock/mutex" / string(pstrName);

#else

         path = ::file::path("/var/tmp/ca2/lock/mutex") / pstrName;

#endif

      }
      else
      {

#ifdef ANDROID

         path =  m_psystem->m_pacmedirectory->system() / "home/user/ca2/lock/mutex" / string(pstrName);

#elif defined __APPLE__

         path = getenv("HOME");

         path /= "Library/ca2/lock/mutex/named";

#else

         path = getenv("HOME");

         path /= ".config/ca2/lock/mutex/named";

#endif


      }

      path /= pstrName;

      m_psystem->m_pacmedirectory->create(path.folder());

      m_iFd = open(path, O_RDWR | O_CREAT, S_IRWXU);

      if(m_iFd < 0)
      {

         int iErr = errno;

         const char * pszError = strerror(iErr);

         throw ::exception(error_resource);

      }

      m_strName = path;

      pthread_mutexattr_t attr;

      pthread_mutexattr_init(&attr);

      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

      pthread_mutex_init(&m_mutex, &attr);

   }
   else

#elif defined(MUTEX_NAMED_POSIX)

   m_key = 0;

   m_semid = -1;

   if(pstrName != nullptr && *pstrName != '\0')
   {

      mutex() = nullptr;

      ::file::path path;

      if(::str().begins_ci(pstrName, "Global"))
      {

         path = "/::payload/lock/ca2/mutex/named";

      }
      else
      {

         path = getenv("HOME");

         path /= ".config/ca2/lock/mutex/named";

      }

      path /= pstrName;

               auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(path.folder());

      ::m_psystem->m_pacmefile->put_contents(path, m_pszName);

      m_key = ftok(path, 1); //Generate a unique key or supply a value

      bool bAlreadyExists;

get_existing:

      set_last_error(0);

      m_semid = semget(
                m_key, // a unique identifier to identify semaphore set
                1,  // number of semaphore in the semaphore set
                0// permissions (rwxrwxrwx) on the new
                //semaphore set and creation flag
                );

      if(m_semid >= 0)
      {

         m_bOwner = false;

         bAlreadyExists = true;

         if(bAlreadyExists)
         {
            set_last_error(ERROR_ALREADY_EXISTS);

         }

      }
      else
      {

         bAlreadyExists = false;

         m_semid = semget(
                   m_key, // a unique identifier to identify semaphore set
                   1,  // number of semaphore in the semaphore set
                   0777 | IPC_CREAT | IPC_EXCL// permissions (rwxrwxrwx) on the new
                   //semaphore set and creation flag
                   );

         if(m_semid == -1 && errno == EEXIST)
         {

            goto get_existing;

         }

      }

      if(m_semid < 0)
      {

         throw ::exception(error_resource);

      }

      m_pszName = strdup(path);

      semun semctl_arg;

      //set Initial value for the resource
      semctl_arg.val = 1; //Setting semval to 1

      semctl(m_semid, 0, SETVAL, semctl_arg);

   }
   else

#endif

   {

      pthread_mutexattr_t attr;

      pthread_mutexattr_init(&attr);

      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

      pthread_mutex_init(&m_mutex, &attr);

#ifdef MUTEX_COND_TIMED

      pthread_cond_init(&m_cond, nullptr);

      m_count = 0;

      m_thread = 0;

#endif

   }

#endif

}


#ifdef WINDOWS

mutex::mutex(enum_create_new, const char * pstrName, void * h, bool bOwner)
{

#ifdef _DEBUG
   m_itask = -1;
#endif

   m_bOwner = bOwner;
   m_hsync = h;

}

//mutexmutex(const mutex & m):
//   synchronization_object(m.m_pszName)
//{
//   m_bOwner = false;
//   m_hsync = m.m_hsync;
//
//}

#else

#if defined(MUTEX_NAMED_POSIX)

mutexmutex(const char * pstrName, sem_t * psem, bool bOwner) :
   ::matter(pobject),
   synchronization_object(pstrName)
{

   m_itask = -1;

   m_bOwner       = bOwner;
   m_pszName      = strdup(pstrName);

#ifdef ANDROID

   m_psem         = psem;

#endif

}

mutexmutex(const mutex & m):
   matter(m.get_app()),
   synchronization_object(m.m_pszName)
{

   m_bOwner       = false;

#ifdef ANDROID

   m_psem         = m.m_psem;

#endif

   m_mutex        = m.m_mutex;

}

#elif defined(MUTEX_NAMED_FD)


mutex::mutex(enum_create_new, const char * lpszName, int iFd, bool bOwner)
{
#ifdef _DEBUG
   m_itask = -1;
#endif

   m_strName = lpszName;
   m_bOwner = bOwner;
   m_iFd = iFd;

}

//mutexmutex(const mutex & m) :
//   matter(m.get_app()),
//   synchronization_object(m.m_pszName)
//{
//
//   m_bOwner = false;
//   m_iFd = m.m_iFd;
//   m_mutex = m.m_mutex;
//
//}



#elif defined(MUTEX_NAMED_VSEM)

mutexmutex(e_create_new enew, const char * pstrName, key_t key, i32 semid, bool bOwner):
   ::matter(pobject),
   synchronization_object(pstrName)
{

   m_bOwner       = bOwner;
   m_key          = key;
   m_semid        = semid;

}


//mutexmutex(const mutex & m):
//   matter(m.get_app()),
//   synchronization_object(m.m_pszName)
//{
//
//   m_bOwner       = false;
//   m_semid        = m.m_semid;
//   m_mutex        = m.m_mutex;
//
//}

#endif

#endif



mutex::~mutex()
{

#ifndef WINDOWS

#if defined(MUTEX_NAMED_POSIX)

   if (m_psem != SEM_FAILED)
   {

      //if(m_bOwner)
      {
         sem_close(m_psem);
         sem_unlink(m_pszName);

      }

   }

#elif defined(MUTEX_NAMED_FD)

   if(m_strName.has_char())
   {

      if(m_iFd >= 0)
      {

         close(m_iFd);

      }

      pthread_mutex_destroy(&m_mutex);

   }

#elif defined(MUTEX_NAMED_VSEM)

   if(m_semid >= 0)
   {

      if(m_bOwner)
      {

         semun ignored_argument;

         semctl(m_semid, 1, IPC_RMID, ignored_argument);

      }

   }

#endif

   else
   {

      pthread_mutex_destroy(&m_mutex);

#ifdef MUTEX_COND_TIMED

      pthread_cond_destroy(&m_cond);

#endif

   }

#endif

}


bool mutex::already_exists()
{

   return m_bAlreadyExists;

}

//      ANDROID
//      int irc = pthread_mutex_lock_timeout_np(&m_mutex, duration.get_total_milliseconds());
//
//      if (!irc)
//      {
//
//         return synchronization_result(synchronization_result::Event0);
//
//      }
//      else if (irc != EBUSY)
//      {
//
//         return synchronization_result(synchronization_result::Failure);
//
//      }
//


#if !defined(WINDOWS)


bool mutex::_wait(const class ::wait & wait)
{

   if(wait.is_infinite())
   {

      _wait();

      return true;

   }

#if defined(MUTEX_NAMED_POSIX)

   if (m_psem != SEM_FAILED)
   {

      timespec delay;

      delay.tv_sec = duration.m_i;

      delay.tv_nsec = duration.m_i;

      i32 ret = sem_timedwait(m_psem, &delay);

      if(ret == 0)
      {

         return synchronization_result(synchronization_result::Event0);

      }
      else
      {

         if (errno == ETIMEDOUT)
         {

            return synchronization_result(synchronization_result::time_out);

         }

      }

      return synchronization_result(synchronization_result::Failure);


   }
   else

#elif defined(MUTEX_NAMED_FD)

   if (m_strName.has_char())
   {

      int rc = pthread_mutex_lock(&m_mutex);

      if (rc < 0)
      {

         return error_failed;

      }

      auto tickStart = ::duration::now();

      while (true)
      {

         if (m_count > 0)
         {

            if (pthread_equal(m_thread, pthread_self()))
            {

               m_count++;

               int iError = pthread_mutex_unlock(&m_mutex);

               ASSERT(iError == 0);

               return true;

            }

         }
         else
         {

            int rc = lockf(m_iFd, F_LOCK, 0);

            if (rc == 0)
            {

               m_count++;

               m_thread = pthread_self();

               int iError = pthread_mutex_unlock(&m_mutex);

               ASSERT(iError == 0);

               return true;

            }
            else
            {

               rc = errno;

               if (rc != EAGAIN && rc != EACCES)
               {

                  int iError = pthread_mutex_unlock(&m_mutex);

                  ASSERT(iError == 0);

                  return error_failed;

               }

            }

            int iError = pthread_mutex_unlock(&m_mutex);

            if (iError < 0)
            {

               ASSERT(false);

               return error_failed;

            }

            auto tickElapsed = tickStart.elapsed();

            if (tickElapsed >= wait)
            {

               return error_wait_timeout;

            }

            preempt((::duration)minimum_maximum((wait - tickElapsed) / 50, 1, 1000));

            rc = pthread_mutex_lock(&m_mutex);

            if (rc < 0)
            {

               return error_failed;

            }

         }

      }

//      int iError = pthread_mutex_unlock(&m_mutex);
//
//      ASSERT(iError == 0);
//
//      return synchronization_result(synchronization_result::Failure);

   }
   else

#elif defined(MUTEX_NAMED_VSEM)

   if(m_semid >= 0)
   {

      timespec timeout;

      timeout.tv_sec = duration.m_i;

      timeout.tv_nsec = duration.m_i;

      struct sembuf operation[1] ;

      operation[0].sem_op = -1; // Wait
      operation[0].sem_num = 0;
      operation[0].sem_flg = 0;

      i32 ret = semtimedop(m_semid, operation, 1, &timeout);

      if(ret == 0)
      {

         return synchronization_result(synchronization_result::Event0);

      }
      else if(ret == -1)
      {

         if(errno == EAGAIN)
         {

            return synchronization_result(synchronization_result::time_out);

         }

      }

      return synchronization_result(synchronization_result::Failure);

   }
   else

#endif

#if defined(MUTEX_COND_TIMED)
   {

      int iErrorLock = pthread_mutex_lock(&m_mutex);

      if(iErrorLock != 0)
      {

         throw ::exception(error_failed);

      }

      bool bFirst = true;

      timespec abs_time;

      while((m_thread != 0) && !pthread_equal(m_thread, pthread_self()))
      {

         if (bFirst)
         {

#ifdef ANDROID

            clock_gettime(CLOCK_MONOTONIC, &abs_time);

#elif defined(MACOS)

            if (__builtin_available(macOS 10.12, *))
            {

               clock_gettime(CLOCK_REALTIME, &abs_time);

            }
            else
            {

               struct timeval tm;

               gettimeofday(&tm, nullptr);

               abs_time.tv_sec = tm.tv_sec;

               abs_time.tv_nsec = tm.tv_usec * 1000;


            }


#elif defined(LINUX)

         clock_gettime(CLOCK_REALTIME, &abs_time);

#else

            struct timeval tm;

            gettimeofday(&tm, nullptr);

            abs_time.tv_sec = tm.tv_sec;

            abs_time.tv_nsec = tm.tv_usec * 1000;

#endif

            ::duration d;

            d.m_iSecond = abs_time.tv_sec + wait.m_d;

            d.m_iNanosecond = abs_time.tv_nsec + fmod(wait.m_d, 1.0) * 1'000'000'000;

            d.normalize();

            abs_time.tv_sec = d.m_iSecond;

            abs_time.tv_nsec = d.m_iNanosecond;

            bFirst = false;

         }

#ifdef ANDROID

         int iErrorCondTimedWait = pthread_cond_timedwait_monotonic_np(&m_cond, &m_mutex, &abs_time);

#else

         int iErrorCondTimedWait = pthread_cond_timedwait(&m_cond, &m_mutex, &abs_time);

#endif

         if(iErrorCondTimedWait == ETIMEDOUT)
         {

            int iErrorUnlock1 = pthread_mutex_unlock(&m_mutex);

            if(iErrorUnlock1 != 0)
            {

               throw ::exception(error_failed);

            }

            return false;

         }
         else if(iErrorCondTimedWait != 0)
         {

            int iErrorUnlock2 = pthread_mutex_unlock(&m_mutex);

            ASSERT(iErrorUnlock2 == 0);

            throw ::exception(error_failed);

         }

      }

      if (m_count == 0)
      {

         m_thread = pthread_self();

      }

      m_count++;

      int iErrorUnlock3 = pthread_mutex_unlock(&m_mutex);

      if(iErrorUnlock3 != 0)
      {

         throw ::exception(error_failed);

      }

      return true;

   }

#else

   {

      timespec abs_time;

      clock_gettime(CLOCK_REALTIME, &abs_time);

      ::duration d;

      d.m_iSecond = abs_time.tv_sec + (::i64) (wait.m_d);

      d.m_iNanosecond = abs_time.tv_nsec + (fmod(wait.m_d, 1.0) * 1'000'000'000);

      d.normalize();

      abs_time.tv_sec = d.m_iSecond;

      abs_time.tv_nsec = d.m_iNanosecond;

      int rc = pthread_mutex_timedlock (&m_mutex, &abs_time);

      if (!rc)
      {

         return signaled_base;

      }
      else if(rc == ETIMEDOUT)
      {

         return error_timeout;

      }
      else
      {

         return error_failed;

      }

   }

#endif

}


void mutex::_wait()
{

#if defined(MUTEX_NAMED_POSIX)

   if (m_psem != SEM_FAILED)
   {

      timespec delay;

      i32 ret = sem_wait(m_psem);

      if (ret == 0)
      {

         return true;

      }
      else
      {

         if (errno == ETIMEDOUT)
         {

            return false;

         }

      }

      return false;

   }
   else

#elif defined(MUTEX_NAMED_FD)

   if (m_strName.has_char())
   {

      int rc = pthread_mutex_lock(&m_mutex);

      if (rc < 0)
      {

         throw ::exception(error_failed);

      }

      if (m_count > 0 && pthread_equal(m_thread, pthread_self()))
      {

         m_count++;

         int rc = pthread_mutex_unlock(&m_mutex);

         if (rc < 0)
         {

            throw ::exception(error_failed);

         }

         //return ::success;

      }

      while (true)
      {

         if (m_count > 0)
         {

            if (pthread_equal(m_thread, pthread_self()))
            {

               m_count++;

               int rc = pthread_mutex_unlock(&m_mutex);

               if (rc < 0)
               {

                  throw ::exception(error_failed);

               }

               //return ::success;

            }

         }
         else
         {

            rc = lockf(m_iFd, F_LOCK, 0);

            if (rc == 0)
            {

               m_count++;

               m_thread = pthread_self();

               int rc = pthread_mutex_unlock(&m_mutex);

               if (rc < 0)
               {

                  throw ::exception(error_failed);

               }

               //return ::success;

            }
            else
            {

               rc = errno;

               if (rc != EAGAIN && rc != EACCES)
               {

                  int rc = pthread_mutex_unlock(&m_mutex);

                  if(rc < 0)
                  {

                     throw ::exception(error_failed);

                  }

                  throw ::exception(error_failed);

               }

            }

         }

         int rc = pthread_mutex_unlock(&m_mutex);

         if (rc < 0)
         {

            throw ::exception(error_failed);

         }

         preempt(100_ms);

         rc = pthread_mutex_lock(&m_mutex);

         if (rc < 0)
         {

            throw ::exception(error_failed);

         }

      }

      //return ::success;

   }
   else

#elif defined(MUTEX_NAMED_VSEM)

   if(m_semid >= 0)
   {

      struct sembuf operation[1] ;

      operation[0].sem_op = -1; // Wait
      operation[0].sem_num = 0;
      operation[0].sem_flg = 0;

      i32 ret = semop(m_semid, operation, 1);

      if(ret < 0)
      {

         return false;

      }

   }
   else

#endif

#ifdef MUTEX_COND_TIMED
   {

      int iErrorLock = pthread_mutex_lock(&m_mutex);

      if(iErrorLock != 0)
      {

         throw ::exception(error_failed);

      }

      while ((m_thread != 0) && !pthread_equal(m_thread, pthread_self()))
      {

         int iErrorCondWait = pthread_cond_wait(&m_cond, &m_mutex);

         if(iErrorCondWait != 0)
         {

            int iErrorUnlock1 = pthread_mutex_unlock(&m_mutex);

            throw ::exception(error_failed);

         }

      }

      if(m_count == 0)
      {

         m_thread = pthread_self();

      }

      m_count++;

      int iErrorUnlock2 = pthread_mutex_unlock(&m_mutex);

      if(iErrorUnlock2 != 0)
      {

         throw ::exception(error_failed);
         
      }

   }

#else

   {

      int irc = pthread_mutex_lock(&m_mutex);

      if (irc)
      {

         throw ::exception(error_failed);

      }

   }

#endif

}


#endif


void mutex::unlock()
{

#ifdef WINDOWS

#ifdef _DEBUG

   m_strThread.Empty();
   m_itask = -1;
   ::output_debug_string("");

#endif


   if (!::ReleaseMutex(m_hsync))
   {

      auto last_error = GetLastError();

      auto estatus = failed_errno_to_status(last_error);

      //throw ::exception(estatus);

   }

#else

#if defined(MUTEX_NAMED_POSIX)

   if (m_psem != SEM_FAILED)
   {

      return sem_post(m_psem) == 0;

   }
   else

#elif defined(MUTEX_NAMED_FD)

   if (m_strName.has_char())
   {

      int rc = pthread_mutex_lock(&m_mutex);

      if (rc < 0)
      {

         throw ::exception(error_failed);

      }

      if (!pthread_equal(m_thread, pthread_self()))
      {

         ASSERT(false);

         int iError = pthread_mutex_unlock(&m_mutex);

         ASSERT(iError == 0);

         throw ::exception(error_failed);

      }

      rc = 0;

      if (m_count > 1)
      {

         m_count--;

      }
      else if (m_count == 1)
      {

         rc = lockf(m_iFd, F_ULOCK, 0);

         if (rc == 0)
         {

            m_count = 0;

         }

      }

      int iError = pthread_mutex_unlock(&m_mutex);

      ASSERT(iError == 0);

      if(rc != 0)
      {

         throw ::exception(error_failed);

      }

   }
   else

#elif defined(NAMED_MUTEX_VSEM)

   if(m_semid >= 0)
   {

      struct sembuf operation[1] ;

      operation[0].sem_op = 1; //Release the resource
      operation[0].sem_num = 0;
      operation[0].sem_flg = SEM_UNDO;

      return semop(m_semid, operation, 1) == 0;

   }
   else

#endif

#ifdef MUTEX_COND_TIMED

   {

      int iErrorLock = pthread_mutex_lock(&m_mutex);

      if(iErrorLock != 0)
      {

         throw ::exception(error_failed);

      }

      if(!pthread_equal(m_thread, pthread_self()))
      {

         ASSERT(false);

         int iErrorUnlock1 = pthread_mutex_unlock(&m_mutex);

         ASSERT(iErrorUnlock1 == 0);

         throw ::exception(error_failed);

      }

      if(m_count > 1)
      {

         m_count--;

      }
      else if(m_count == 1)
      {

         int iErrorSignal = pthread_cond_signal(&m_cond);

         if(iErrorSignal != 0)
         {

            int iErrorUnlock2 = pthread_mutex_unlock(&m_mutex);

            throw ::exception(error_failed);

         }

         m_thread = 0;

         m_count = 0;

      }

      int iErrorUnlock3 = pthread_mutex_unlock(&m_mutex);

      if(iErrorUnlock3 != 0)
      {

         throw ::exception(error_failed);
         
      }

   }

#else

   {

      int iError = pthread_mutex_unlock(&m_mutex);

      if(iError != 0)
      {

         throw ::exception(error_failed);

      }

   }

#endif

#endif // _WIN32

}



__pointer(mutex) open_mutex(::matter * pmatter, const char * lpszName)
{

#ifdef WINDOWS

   HANDLE h = ::OpenMutexW(SYNCHRONIZE, false, utf8_to_unicode(lpszName));

   if (h == nullptr || h == INVALID_HANDLE_VALUE)
   {

      return nullptr;

   }

   auto pmutex  = __new(mutex(e_create_new, lpszName, h));

   return pmutex;

#elif defined(MUTEX_NAMED_POSIX)

   string strName = pstrName;

   sem_t * psem;

   int isCreator = 0;

   if ((psem = sem_open(strName, O_CREAT | O_EXCL, 0666, 1)) != SEM_FAILED)
   {

      isCreator = 1;

   }
   else
   {

      psem = sem_open(strName, 0);

      if (psem == SEM_FAILED)
      {

         //throw ::exception(resource_exception(papp,"failed to create named mutex"));
         throw ::exception(error_resource);

      }

   }

   auto pmutex = __new(mutex(strName, psem, isCreator));

   return pmutex;

#elif defined(MUTEX_NAMED_FD)

   if (lpszName == nullptr || *lpszName == '\0')
   {

      return nullptr;

   }

   set_last_status(::success);

   ::file::path path;

   if (::str().begins_ci(lpszName, "Global"))
   {

      path = "/payload/tmp/ca2/lock/mutex/named";

   }
   else
   {

#ifdef __APPLE__

      path = getenv("HOME");

      path /= "Library/ca2/lock/mutex/named";

#else

      path = getenv("HOME");

      path /= ".config/ca2/lock/mutex/named";

#endif

   }

   path /= lpszName;

   auto pacmedirectory = pmatter->m_psystem->m_pacmedirectory;

   pacmedirectory->create(path.folder());

   int iFd = open(path, O_RDWR, S_IRWXU);

   if (iFd < 0)
   {

      throw ::exception(error_resource);

   }

   //m_pszName = strdup(path);

   //pthread_mutexattr_t attr;

   //pthread_mutexattr_init(&attr);

   //pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

   //pthread_mutex_init(&m_mutex, &attr);

   auto pmutex = __new(mutex(e_create_new, lpszName, iFd, false));

   return pmutex;

#elif defined(POSIX_NAMED_VSEM)

   if(pstrName == nullptr || *pstrName == '\0')
      return nullptr;

   string strName = pstrName;

   key_t key = ftok(strName, 0); //Generate a unique key or supply a value

   i32 semid = semget(
               key, // a unique identifier to identify semaphore set
               1,  // number of semaphore in the semaphore set
               0666 // permissions (rwxrwxrwx) on the new
               //semaphore set and creation flag
               );
   if(semid < 0)
   {

      return nullptr;

   }

   auto pmutex = __new(mutex(strName, key, semid));

   return pmutex;

#endif

}


void wait_until_mutex_does_not_exist(::object * pobject,  const char * lpszName)
{

   __pointer(mutex) pmutex = __new(mutex(pobject, false, "Global\\::ca::account::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784"));

   if(::get_last_status() == ::error_already_exists)
   {

      while(::get_last_status() == ::error_already_exists && ::task_get_run())
      {

         pmutex.release();

         preempt(200_ms);

         pmutex = __new(mutex(pobject, false, "Global\\::ca::account::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784"));

      }

   }

}


mutex * g_pmutexUiDestroyed = nullptr;

CLASS_DECL_ACME mutex * get_ui_destroyed_mutex()
{

   return g_pmutexUiDestroyed;

}



