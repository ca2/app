#pragma once


class CLASS_DECL_ACME timer_task :
   public timer,
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
   //#elif defined(APPLEOS)
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
   virtual ~timer_task();


#ifdef DEBUG

   virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
   virtual i64 release(OBJ_REF_DBG_PARAMS) override;

#endif

   void impl_init();
   void impl_term();


   virtual ::e_status initialize_timer(::acme::timer_array * ptimera, uptr uiTimer = 0, PFN_TIMER pfnTimer = nullptr, void* pvoidData = nullptr, class synchronization_object* pmutex = nullptr);

   virtual ::e_status run() override;


   bool start(const ::duration& duration, bool bPeriodic);

   virtual bool on_timer();

   virtual ::e_status finalize() override;

   //bool impl_start();
   //bool impl_restart();
   //void impl_stop();
   virtual void term_task() override;

   inline bool is_timer_ok() const { return is_ok(); }


   virtual bool task_active() const override;


   


};



