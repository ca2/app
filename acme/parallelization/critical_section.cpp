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
   
   int iSize = sizeof(critical_section_impl);

   auto p = ::malloc(iSize);

   ::new(&p) ::critical_section_impl();
   
   m_pimpl = (::critical_section_impl *) p;

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



