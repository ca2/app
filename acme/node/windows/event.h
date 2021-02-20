#pragma once


class CLASS_DECL_ACME event :
   public ::event
{
public:


   HANDLE m_hsync;


   event(char * sz = nullptr, bool bInitiallyOwn = false, bool bManualReset = false, const char * pszNAme = nullptr, sync_options * psyncoptions = nullptr);

   virtual ~event();

   // using event_base::lock;
   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using synchronization_object::unlock;
   virtual bool unlock();

   //virtual HSYNC hsync() const;

   bool SetEvent();
   bool set_event() { return SetEvent(); }
   //bool PulseEvent();
   bool ResetEvent();

   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an event forever
   virtual synchronization_result wait();

   ///  \brief		waits for an event for a specified time
   ///  \lparam		duration time period to wait for an event
   ///  \return	waiting action result as WaitResult
   virtual synchronization_result wait(const duration & duration);

   bool is_signaled() const;

};

