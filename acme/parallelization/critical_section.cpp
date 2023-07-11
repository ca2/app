#include "framework.h"




#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#else


#include "acme/_operating_system.h"


#endif


class critical_section_impl
{
public:


   inline void* operator new(size_t s)
   {

      return ::malloc(s);

   }


   inline void operator delete(void * p)
   {

      return ::free(p);

   }


#ifdef PARALLELIZATION_PTHREAD

   pthread_mutex_t m_mutex;

   critical_section_impl()
   {

       ::pthread_recursive_mutex_init(&m_mutex);

   }


   ~critical_section_impl()
   {

      ::pthread_mutex_destroy(&m_mutex);

   }


   void lock()
   {

      ::pthread_mutex_lock(&m_mutex);

   }


   void unlock()
   {

      ::pthread_mutex_unlock(&m_mutex);

   }


#else

   CRITICAL_SECTION m_criticalsection;


   critical_section_impl()
   {

      ::InitializeCriticalSection(&m_criticalsection);

   }


   ~critical_section_impl()
   {

      ::DeleteCriticalSection(&m_criticalsection);

   }


   void lock()
   {

      ::EnterCriticalSection(&m_criticalsection);

   }


   void unlock()
   {

      ::LeaveCriticalSection(&m_criticalsection);

   }


#endif


};


critical_section::critical_section()
{

   m_pimpl = new ::critical_section_impl();

}


critical_section::~critical_section()
{

   delete m_pimpl;

}


void critical_section::lock()
{

   m_pimpl->lock();

}


void critical_section::unlock()
{

   m_pimpl->unlock();

}



