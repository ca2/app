#pragma once


#include "acid/_operating_system.h"


#include "condition_variable.h"


class CLASS_DECL_ACID condition :
   virtual public particle
{
public:

#if defined(LINUX) || defined(__APPLE__) || defined(SOLARIS) || defined(FREEBSD) || defined(OPENBSD)

   iptr           m_hsync;
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   i32           m_iSignalId;  // meaningful only when m_bManualEvent

#elif defined(ANDROID)

   bool              m_bSignaled;
   int               m_iHold;
   pthread_mutex_t   m_mutex;
   pthread_cond_t    m_cond;

#else

   CRITICAL_SECTION                    m_criticalsection;
   condition_variable                  m_conditionvariable;

#endif


   condition();
   ~condition() override;


   //using synchronization::lock;
   //virtual bool lock(const class time & timeWait);

   using particle::unlock;
   virtual void unlock() override;

   virtual void * get_os_data() const;

   bool pulse();
   bool SetEvent();
   bool set_event() { return SetEvent(); }
   //bool PulseEvent();
   bool ResetEvent();


   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an event forever
   ::e_status wait () override;

   ///  \brief		waits for an event for a specified time
   ///  \lparam		time time period to wait for an event
   ///  \return	waiting action result as WaitResult
   ::e_status wait (const class time & timeWait) override;

   bool is_signaled() const;

};

