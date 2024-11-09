// As happening by camilo on 2024-11-08 21:22 <3ThomasBorregaardSorensen!!
#pragma once


#if defined(LINUX) || defined(__APPLE__) || defined(__BSD__)
#include <sys/types.h>
#include <sys/sem.h>
#endif


#include "acme/operating_system/security_attributes.h"


class CLASS_DECL_ACME happening :
   virtual public ::subparticle
{
public:


   int m_iEventSerialId;

#ifdef WINDOWS

   hsynchronization     m_handle;

#endif


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(__BSD__)

   /// Private Mutexes
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   int               m_iSignalId;  // meaningful only when m_bManualEvent
   void *            m_pcond; // pthread_cond_t
   void *            m_pmutex; // pthread_mutex_t;


#endif


#if defined(LINUX) || defined(__APPLE__) || defined(__BSD__)

   /// Named Mutexes
   int               m_sem;

#endif


   happening(const ::scoped_string & scopedstrName = nullptr, bool bInitiallyOwn = false, bool bManualReset = false, security_attributes * psecurityattributes = nullptr);
   ~happening() override;

   // using event_base::lock;
   //bool lock(const ::wait & wait = wait::infinite()) override;


   hsynchronization get_synchronization_handle() override;


   using subparticle::unlock;
   void unlock() override;

   //virtual hsynchronization hsynchronization() const;

   //bool SetHappening();
   bool set_happening();
   //bool pulse_happening();
   bool reset_happappening();

   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an event forever
   void _wait () override;

   ///  \brief		waits for an event for a specified time
   ///  \lparam		time time period to wait for an event
   ///  \return	true if acquired lock, false timeout, exception on error
   bool _wait (const class time & timeWait) override;

   bool is_signaled() const;

};

