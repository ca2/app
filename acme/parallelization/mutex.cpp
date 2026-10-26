#include "platform.h"
#include "mutex.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/system.h"

#if defined(PARALLELIZATION_PTHREAD)
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#elif defined(WINDOWS)
#include "acme/_operating_system.h"
#else
#error "not implemented by here/now in this era/epoch/age"
#endif


//class mutex_implementation
//{
//public:

#if defined(PARALLELIZATION_PTHREAD)

   //pthread_mutex_t m_mutex;
   //int m_iFd = -1;
   //unsigned int m_count = 0;

   pthread_mutex_t * new_pthread_mutex_t()
   {

      auto pmutex = new pthread_mutex_t;

      pthread_mutexattr_t attr;
      int iError = pthread_mutexattr_init(&attr);
      if (iError != 0)
      {
         throw ::exception(error_resource);
      }

      iError = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      if (iError == 0)
      {
         iError = pthread_mutex_init(pmutex, &attr);
      }
      pthread_mutexattr_destroy(&attr);

      if (iError != 0)
      {
         throw ::exception(error_resource);
      }
      return pmutex;
   }

   void delete_pthread_mutex_t(pthread_mutex_t * pmutex)
   {

      //if (m_iFd >= 0)
      //{
        // ::close(m_iFd);
      //}
      pthread_mutex_destroy(pmutex);
      delete pmutex;

   }

#elif defined(WINDOWS)

   //HANDLE m_handle;
  // bool m_bOwner = true;

   //mutex_implementation()
   //{

   //   m_handle = ::CreateMutexExW(nullptr, nullptr, 0, MUTEX_ALL_ACCESS);
   //   if (!m_handle)
   //   {
   //      throw ::exception(error_resource);
   //   }

   //}

   //~mutex_implementation()
   //{

   //   if (m_bOwner && m_handle)
   //   {
   //      ::CloseHandle(m_handle);
   //   }

   //}

#endif

//};


mutex::mutex() //:
   //m_pimplementation(___new mutex_implementation)
{

#if defined(WINDOWS)
   m_handle = ::CreateMutexExW(nullptr, nullptr, 0, MUTEX_ALL_ACCESS);
   if (!m_handle)
   {
      throw ::exception(error_resource);
   }

#elif defined(PARALLELIZATION_PTHREAD)
   m_pPthreadMutexT = new_pthread_mutex_t();
#endif

   set_own_synchronization_flag();

}


mutex::mutex(enum_create_new, bool bInitiallyOwn) :
   mutex()
{

   if (bInitiallyOwn)
   {
      _wait();
   }

}


mutex::mutex(::particle * pparticle, bool bInitiallyOwn, const_char_pointer pszName) :
   mutex()
{

   initialize(pparticle);

#if defined(PARALLELIZATION_PTHREAD)

   if (pszName && *pszName)
   {

      ::string strName(pszName);
      ::file::path path;
      if (strName.begins("Global"))
      {
#ifdef __ANDROID__
         path = directory_system()->roaming() / "tmp/ca2/lock/mutex";
#else
         path = "/var/tmp/ca2/lock/mutex";
#endif
      }
      else
      {
#ifdef __ANDROID__
         path = directory_system()->roaming() / "home/user/ca2/lock/mutex";
#elif defined(__APPLE__)
         path = ::file::path(getenv("HOME")) / "Library/ca2/lock/mutex/named";
#else
         path = ::file::path(getenv("HOME")) / ".config/ca2/lock/mutex/named";
#endif
      }

      path /= strName;
      directory_system()->create(path.folder());
      int iFd = ::open(path, O_RDWR | O_CREAT | O_CLOEXEC, S_IRWXU);
      if (iFd < 0)
      {
         throw ::exception(error_resource, "Failed to create named mutex");
      }
      //m_pimplementation->m_iFd = iFd;
      m_iFd = iFd;

   }

#elif defined(WINDOWS)

   ::wstring wstrName(pszName);
   HANDLE handle = ::CreateMutexExW(nullptr, pszName ? wstrName.c_str() : nullptr, 0, MUTEX_ALL_ACCESS);
   if (!handle)
   {
      throw ::exception(error_resource);
   }
   ::CloseHandle(m_handle);
   m_handle = handle;

#endif

   if (bInitiallyOwn)
   {
      _wait();
   }

}


#if defined(PARALLELIZATION_PTHREAD)

mutex::mutex(enum_create_new, const_char_pointer, int iFd, bool bOwner) :
   mutex()
{

   if (iFd < 0)
   {
      throw ::exception(error_resource);
   }
   m_iFd = iFd;
   set_own_synchronization_flag(bOwner);

}

#elif defined(WINDOWS)

mutex::mutex(enum_create_new, const_char_pointer, void * handle, bool bOwner) :
   mutex()
{

   if (!handle || handle == INVALID_HANDLE_VALUE)
   {
      throw ::exception(error_resource);
   }
   ::CloseHandle(m_handle);
   m_handle = handle;
   m_bOwner = bOwner;
   set_own_synchronization_flag(bOwner);

}

#endif


mutex::~mutex()
{
#if defined(PARALLELIZATION_PTHREAD)
      if (m_pPthreadMutexT)
      {
         auto ppthreadmutext = (pthread_mutex_t*)m_pPthreadMutexT;
         m_pPthreadMutexT = nullptr;
      delete_pthread_mutex_t(ppthreadmutext);
      }
#endif
   //delete m_pimplementation;

}


hsynchronization mutex::get_synchronization_handle()
{

#if defined(PARALLELIZATION_PTHREAD)
   return this;
#else
   return m_handle;
#endif

}


void mutex::_wait()
{

#if defined(PARALLELIZATION_PTHREAD)

   auto ppthreadmutext = (pthread_mutex_t*)m_pPthreadMutexT;
   if (pthread_mutex_lock(ppthreadmutext) != 0)
   {
      throw ::exception(error_failed);
   }

   if (m_iFd >= 0)
   {

      if (m_uCount == 0)
      {
         int iResult;
         do
         {
            iResult = ::lockf(m_iFd, F_LOCK, 0);
         }
         while (iResult < 0 && errno == EINTR);

         if (iResult < 0)
         {
            pthread_mutex_unlock(ppthreadmutext);
            throw ::exception(error_failed);
         }
      }
      m_uCount++;

   }

#elif defined(WINDOWS)

   auto dwResult = ::WaitForSingleObject(m_handle, INFINITE);
   if (dwResult != WAIT_OBJECT_0 && dwResult != WAIT_ABANDONED)
   {
      throw ::exception(error_failed);
   }

#endif

}


bool mutex::_wait(const class ::time & timeWait)
{

   if (timeWait.is_infinite())
   {
      _wait();
      return true;
   }

#if defined(PARALLELIZATION_PTHREAD)

   //auto & implementation = *m_pimplementation;
      auto ppthreadmutext = (pthread_mutex_t*)m_pPthreadMutexT;
   auto timeStart = ::time::now();
   const timespec timespecSleep{0, 1'000'000};

#if defined(LINUX) || defined(__ANDROID__)

   int iError = pthread_mutex_trylock(ppthreadmutext);
   if (iError == EBUSY)
   {
      if (timeWait <= 0_s)
      {
         return false;
      }

      timespec deadline{};
      if (::clock_gettime(CLOCK_REALTIME, &deadline) != 0)
      {
         throw ::exception(error_failed);
      }
      deadline.tv_sec += timeWait.m_iSecond;
      deadline.tv_nsec += timeWait.m_iNanosecond;
      if (deadline.tv_nsec >= 1'000'000'000)
      {
         deadline.tv_sec++;
         deadline.tv_nsec -= 1'000'000'000;
      }
      iError = pthread_mutex_timedlock(ppthreadmutext, &deadline);
   }
   if (iError == ETIMEDOUT)
   {
      return false;
   }
   if (iError != 0)
   {
      throw ::exception(error_failed);
   }

#else

   // Some pthread platforms, including macOS, have no mutex_timedlock.
   while (true)
   {
      int iError = pthread_mutex_trylock(ppthreadmutext);
      if (iError == 0)
      {
         break;
      }
      if (iError != EBUSY)
      {
         throw ::exception(error_failed);
      }
      if (timeStart.elapsed() >= timeWait)
      {
         return false;
      }
      ::nanosleep(&timespecSleep, nullptr);
   }

#endif

   if (m_iFd >= 0)
   {

      if (m_uCount == 0)
      {
         while (::lockf(m_iFd, F_TLOCK, 0) < 0)
         {
            int iError = errno;
            if (iError != EACCES && iError != EAGAIN && iError != EINTR)
            {
               pthread_mutex_unlock(ppthreadmutext);
               throw ::exception(error_failed);
            }
            if (timeStart.elapsed() >= timeWait)
            {
               pthread_mutex_unlock(ppthreadmutext);
               return false;
            }
            ::nanosleep(&timespecSleep, nullptr);
         }
      }
      m_uCount++;

   }
   return true;

#elif defined(WINDOWS)

   auto milliseconds = timeWait.integral_millisecond();
   DWORD dwMilliseconds = milliseconds <= 0 ? 0 :
      (milliseconds >= INFINITE ? INFINITE - 1 : static_cast<DWORD>(milliseconds));
   auto dwResult = ::WaitForSingleObject(m_handle, dwMilliseconds);
   if (dwResult == WAIT_TIMEOUT)
   {
      return false;
   }
   if (dwResult != WAIT_OBJECT_0 && dwResult != WAIT_ABANDONED)
   {
      throw ::exception(error_failed);
   }
   return true;

#endif

}


void mutex::unlock()
{

#if defined(PARALLELIZATION_PTHREAD)

   //auto & implementation = *m_pimplementation;
      auto ppthreadmutext = (pthread_mutex_t*)m_pPthreadMutexT;
   if (m_iFd >= 0)
   {
      if (m_uCount == 0)
      {
         throw ::exception(error_wrong_state);
      }
      if (m_uCount == 1 && ::lockf(m_iFd, F_ULOCK, 0) < 0)
      {
         throw ::exception(error_failed);
      }
      m_uCount--;
   }

   if (pthread_mutex_unlock(ppthreadmutext) != 0)
   {
      throw ::exception(error_failed);
   }

#elif defined(WINDOWS)

   if (!::ReleaseMutex(m_handle))
   {
      throw ::exception(error_failed);
   }

#endif

}
