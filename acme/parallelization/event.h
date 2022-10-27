#pragma once


#if defined(LINUX) || defined(__APPLE__) || defined(FREEBSD)
#include <sys/types.h>
#include <sys/sem.h>
#endif


//#include "synchronization_object.h"


class CLASS_DECL_ACME event :
   public particle
{
public:


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)

   /// Private Mutexes
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   i32               m_iSignalId;  // meaningful only when m_bManualEvent
   void *            m_pcond; // pthread_cond_t
   void *            m_pmutex; // pthread_mutex_t;


#endif


#if defined(LINUX) || defined(__APPLE__) || defined(FREEBSD)

   /// Named Mutexes
   int               m_sem;

#endif


   event(char * sz = nullptr,bool bInitiallyOwn = false, bool bManualReset = false, const char * pszNAme = nullptr ARG_SEC_ATTRS_DEF);

   ~event() override;

   // using event_base::lock;
   //bool lock(const ::wait & wait = wait::infinite()) override;

   using particle::unlock;
   void unlock() override;

   //virtual HSYNC hsync() const;

   bool SetEvent();
   bool set_event() {return SetEvent(); }
   //bool PulseEvent();
   bool ResetEvent();

   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an event forever
   void _wait () override;

   ///  \brief		waits for an event for a specified time
   ///  \lparam		duration time period to wait for an event
   ///  \return	true if acquired lock, false timeout, exception on error
   bool _wait (const class ::wait & wait) override;

   bool is_signaled() const;

};

