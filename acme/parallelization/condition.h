#pragma once


class CLASS_DECL_ACME condition :
   virtual public synchronization_object
{
public:

#if defined(LINUX) || defined(APPLEOS) || defined(SOLARIS)

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

   critical_section     m_criticalsection;
   condition_variable   m_conditionvariable;

#endif


   condition();
   virtual ~condition();


   using synchronization_object::lock;
   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using synchronization_object::unlock;
   virtual bool unlock();

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
   virtual synchronization_result wait ();

   ///  \brief		waits for an event for a specified time
   ///  \lparam		duration time period to wait for an event
   ///  \return	waiting action result as WaitResult
   virtual synchronization_result wait (const duration & duration);

   bool is_signaled() const;

};

