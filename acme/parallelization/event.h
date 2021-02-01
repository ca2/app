#pragma once

#if defined(LINUX) || defined(APPLEOS)
#include <sys/types.h>
#include <sys/sem.h>
#endif



class CLASS_DECL_ACME event :
   public sync
{
public:


#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

   /// Private Mutexes
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   i32               m_iSignalId;  // meaningful only when m_bManualEvent
   void *            m_pcond; // pthread_cond_t
   void *            m_mutex; // pthread_mutex_t;


#endif


#if defined(LINUX) || defined(APPLEOS)

   /// Named Mutexes
   int               m_sem;

#endif


   event(char * sz = nullptr,bool bInitiallyOwn = false, bool bManualReset = false, const char * pszNAme = nullptr ARG_SEC_ATTRS_DEF);

   virtual ~event();

   // using event_base::lock;
   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using sync::unlock;
   virtual bool unlock();

   //virtual HSYNC hsync() const;

   bool SetEvent();
   bool set_event() {return SetEvent(); }
   //bool PulseEvent();
   bool ResetEvent();

   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an event forever
   virtual sync_result wait ();

   ///  \brief		waits for an event for a specified time
   ///  \lparam		duration time period to wait for an event
   ///  \return	waiting action result as WaitResult
   virtual sync_result wait (const duration & duration);

   bool is_signaled() const;

};

