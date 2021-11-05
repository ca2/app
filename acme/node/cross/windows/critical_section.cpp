#include "framework.h"

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
#include "acme/node/operating_system/ansi/_pthread.h"
#endif

#ifdef WINDOWS

bool critical_section::Init()
{
   __try
   {
//      ::InitializeCriticalSection(&m_sect);
      ::InitializeCriticalSectionEx(&m_sect, 4000, 0);
   }
   __except(STATUS_NO_MEMORY == GetExceptionCode())
   {
      return false;
   }

   return true;
}

critical_sectioncritical_section()
{
   bool bSuccess;

   bSuccess = Init();
   if (!bSuccess)
      __throw(error_no_memory);
}

critical_section::operator CRITICAL_SECTION*()
{
   return (CRITICAL_SECTION*) &m_sect;
}

critical_section::~critical_section()
{
   ::DeleteCriticalSection(&m_sect);
}



#else

bool critical_section::Init()
{
   try
   {

      pthread_mutexattr_t mutexattr;   // Mutex attribute variable

      pthread_mutexattr_init(&mutexattr);

      // set the ::mutex as a recursive ::mutex

#ifdef __APPLE__

      pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);


#else

      pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);

#endif

      // create the ::mutex with the attributes set
      pthread_mutex_init(&m_mutex, &mutexattr);

      //After initializing the ::mutex, the thread attribute can be destroyed
      pthread_mutexattr_destroy(&mutexattr);

   }
   catch(...)
   {
      return false;
   }

   return true;
}

critical_sectioncritical_section()
{
   bool bSuccess;

   bSuccess = Init();
   if (!bSuccess)
      __throw(error_no_memory);
}

critical_section::operator pthread_mutex_t()
{
   return m_mutex;
}

critical_section::~critical_section()
{
   // Destroy / close the ::mutex
   pthread_mutex_destroy (&m_mutex);


}

//void critical_section::lock()
//{
//
//   try
//   {
//
//      // Acquire the ::mutex to access the shared resource
//      pthread_mutex_lock ((pthread_mutex_t *) mutex());
//
//   }
//   catch(...)
//   {
//
//      __throw(error_no_memory);
//
//   }
//
//}
//
//
//bool critical_section::lock(const duration & durationTimeout)
//{
//   ASSERT(durationTimeout.is_pos_infinity());
//   (void)durationTimeout;
//   lock();
//   return true;
//
//}
//
//bool critical_section::unlock()
//{
//   // Release the ::mutex  and release the access to shared resource
//   pthread_mutex_unlock ((pthread_mutex_t *) mutex());
//   return true;
//}





#endif





