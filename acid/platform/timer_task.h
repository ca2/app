#pragma once


#include "timer.h"
#include "timer_array.h"
#include "acid/parallelization/task.h"


class CLASS_DECL_ACID timer_task :
   virtual public timer,
   virtual public task
{
public:


   ::pointer<::acid::timer_array>      m_ptimera;
   PFN_TIMER                           m_pfnTimer;
   void *                              m_pvoidData;
   bool                                m_bRunning;

   //
   //#ifdef UNIVERSAL_WINDOWS
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

   i64 increment_reference_count() override;
   i64 decrement_reference_count() override;
   i64 release() override;

#endif

   void impl_init();
   void impl_term();


   virtual void initialize_timer(::particle * pparticle, ::acid::timer_array * ptimera, uptr uiTimer = 0, PFN_TIMER pfnTimer = nullptr, void* pvoidData = nullptr, ::particle * pparticleSynchronization = nullptr);

   void run() override;


   virtual void start_timer_task(const class time & timeWait, bool bPeriodic);


   virtual void on_timer();

   virtual void destroy() override;

   virtual void stop_timer_task();

   //bool impl_start();
   //bool impl_restart();
   //void impl_stop();
   void term_task() override;

   inline bool is_timer_ok() const { return is_ok(); }


   bool task_active() const override;


};



