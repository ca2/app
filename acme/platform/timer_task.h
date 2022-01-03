#pragma once


#include "timer.h"
#include "timer_array.h"


class CLASS_DECL_ACME timer_task :
   virtual public timer,
   virtual public task
{
public:


   __pointer(::acme::timer_array)      m_ptimera;
   PFN_TIMER                           m_pfnTimer;
   void *                              m_pvoidData;
   bool                                m_bRunning;

   //
   //#ifdef _UWP
   //
   //
   //   ThreadPoolTimer ^    m_timer;
   //   timer *              m_ptimer;
   //
   //#elif defined(WINDOWS)
   //
   //   HANDLE               m_hTimerQueue;
   //   HANDLE               m_hTimer;
   //
   //#elif defined(__APPLE__)
   //
   //   void *               m_timer;
   //   void *               m_queue;
   //
   //#else

   bool                 m_bInit;
   //e_timer_t              m_timerid;
   //struct sigevent      m_sev;
   //struct itimerspec    m_its;

//#endif



   timer_task();
   ~timer_task() override;


#ifdef _DEBUG

   i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif

   void impl_init();
   void impl_term();


   virtual ::e_status initialize_timer(::object * pobject, ::acme::timer_array * ptimera, uptr uiTimer = 0, PFN_TIMER pfnTimer = nullptr, void* pvoidData = nullptr, class synchronization_object* pmutex = nullptr);

   ::e_status run() override;


   bool start(const class ::wait & wait, bool bPeriodic);


   virtual bool on_timer();

   //virtual ::e_status destroy() override;

   ::e_status destroy() override;

   //bool impl_start();
   //bool impl_restart();
   //void impl_stop();
   void term_task() override;

   inline bool is_timer_ok() const { return is_ok(); }


   bool task_active() const override;


};



