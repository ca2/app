#pragma once


#include "acme/_operating_system.h"


#include "condition_variable.h"


class CLASS_DECL_ACME condition :
   virtual public particle
{
public:

#if defined(LINUX) || defined(__APPLE__) || defined(SOLARIS) || defined(__BSD__)

   iptr           m_hsync;
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   int           m_iSignalId;  // meaningful only when m_bManualEvent

#elif defined(__ANDROID__)

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

   bool pulse_happening();
   bool set_happening();
   //bool set_happening() { return set_happening(); }
   //bool pulse_happening();
   bool reset_happening();


   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an happening forever
   ::e_status wait () override;

   ///  \brief		waits for an happening for a specified time
   ///  \lparam		time time period to wait for an happening
   ///  \return	waiting action result as WaitResult
   ::e_status wait (const class time & timeWait) override;

   bool is_signaled() const;

};

