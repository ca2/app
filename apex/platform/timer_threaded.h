#pragma once


class CLASS_DECL_APEX threaded_timer :
   public timer,
   virtual public thread
{
public:


   __reference(::apex::timer_array)    m_ptimera;
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



   threaded_timer();
   virtual ~threaded_timer();


   virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 release(OBJ_REF_DBG_PARAMS);


   void impl_init();
   void impl_term();


   virtual ::estatus initialize_timer(::apex::timer_array* ptimera, uptr uiTimer = 0, PFN_TIMER pfnTimer = nullptr, void* pvoidData = nullptr, class sync* pmutex = nullptr);

   virtual ::estatus run() override;


   bool start(const ::duration& duration, bool bPeriodic);

   //void call_on_timer();

   virtual bool on_timer();

   virtual void finalize() override;

   //bool impl_start();
   //bool impl_restart();
   //void impl_stop();
   virtual void term_thread() override;

   inline bool is_timer_ok() const { return is_ok(); }


   virtual bool thread_active() const override;


   


};



