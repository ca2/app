// As happening by camilo on 2024-11-08 21:22 <3ThomasBorregaardSorensen!!
#pragma once


#if defined(LINUX) || defined(__APPLE__) || defined(__BSD__)
#include <sys/types.h>
#include <sys/sem.h>
#endif


//#include "acme/operating_system/security_attributes.h"
#include "acme/prototype/prototype/subparticle.h"

class notify_lock;

class notify_lock_notifier :
   virtual public ::subparticle
{
public:


   ::comparable_eq_list < ::pointer < ::notify_lock > > m_notifylocka;


   ~notify_lock_notifier() override;

   void add_notify_lock(::notify_lock * pnotifylock);
   void erase_notify_lock(::notify_lock * pnotifylock);

   void notify_lock_notify_all();

};


class CLASS_DECL_ACME happening :
   virtual public ::notify_lock_notifier
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

   //notify_lock_notifier m_notifylocknotifier;
   bool start_notify_lock(::notify_lock * pnotifylock) override;
   void end_notify_lock(::notify_lock * pnotifylock) override;


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
   bool reset_happening();

   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an happening forever
   void _wait () override;

   ///  \brief		waits for an happening for a specified time
   ///  \lparam		time time period to wait for an happening
   ///  \return	true if acquired lock, false timeout, exception on error
   bool _wait (const class time & timeWait) override;

   bool is_signaled() const;


};

