#include "framework.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#else


#include "acme/_operating_system.h"


#endif


class CLASS_DECL_ACME critical_section_impl
{
public:


#ifdef PARALLELIZATION_PTHREAD

   pthread_mutex_t      m_mutex;

#else

   CRITICAL_SECTION     m_criticalsection;

#endif


   inline critical_section_impl();
   inline ~critical_section_impl();


   void lock();
   void unlock();


};


critical_section::critical_section()
{

   m_pimpl = (::critical_section_impl*)malloc(sizeof(critical_section_impl));

   ::new(&m_pimpl) ::critical_section_impl();

}


critical_section::~critical_section()
{

   m_pimpl->~critical_section_impl();

   free(m_pimpl);

}


void critical_section::lock()
{

   m_pimpl->lock();

}


void critical_section::unlock()
{

   m_pimpl->unlock();

}


#ifdef PARALLELIZATION_PTHREAD



   critical_section_impl::critical_section_impl() { ::pthread_recursive_mutex_init((pthread_mutex_t*)aligned_this()); }
   critical_section_impl::~critical_section_impl() { ::pthread_mutex_destroy((pthread_mutex_t*)aligned_this()); }


   void critical_section_impl::lock() { ::pthread_mutex_lock((pthread_mutex_t*)aligned_this()); }
   void critical_section_impl::unlock() { ::pthread_mutex_unlock((pthread_mutex_t*)aligned_this()); }




#else



critical_section_impl::critical_section_impl() { ::InitializeCriticalSection(&m_criticalsection); }
critical_section_impl::~critical_section_impl() { ::DeleteCriticalSection(&m_criticalsection); }


void critical_section_impl::lock() { ::EnterCriticalSection(&m_criticalsection);  }
void critical_section_impl::unlock() { ::LeaveCriticalSection(&m_criticalsection); }


#endif



