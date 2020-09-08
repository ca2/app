#pragma once



class CLASS_DECL_APEX nano_timer
{
public:

#ifdef WINDOWS

   HANDLE      m_hTimer;

#endif


   nano_timer()
   {

#ifdef WINDOWS

      m_hTimer = ::CreateWaitableTimer(nullptr, TRUE, nullptr);

#endif

   }


   void wait(u64 uWait)
   {

#ifdef WINDOWS

      LARGE_INTEGER li = {};

      li.QuadPart = - ((LONGLONG) uWait / 100LL);

      if (!SetWaitableTimer(m_hTimer, &li, 0, nullptr, nullptr, FALSE))
      {

         Sleep(DWORD(uWait / 1000000LL));

      }
      else
      {

         WaitForSingleObject(m_hTimer, INFINITE);

      }

#else

      struct timespec req;

      //struct timespec rem;

      req.tv_sec = uWait / 1'000'000'000ULL;

      req.tv_nsec = uWait % 1'000'000'000ULL;

      //rem.tv_sec = 0;

      //rem.tv_nsec = 0;

      //::nanosleep(&req, &rem);

      ::nanosleep(&req, nullptr);

#endif

   }

   void close_timer()
   {

#ifdef WINDOWS
      if (m_hTimer != NULL)
      {

         ::CloseHandle(m_hTimer);

         m_hTimer = NULL;

      }

#endif


   }


   ~nano_timer()
   {

      close_timer();

   }

};


class CLASS_DECL_APEX timer :
   virtual public thread
{
public:


   enum e
   {

      e_start = 1000000,

      hover = e_start,

      e_end

   };

   union
   {
      uptr                 m_nIDEvent;
      e_timer              m_etimer;
   };

   __reference(::apex::timer_array)    m_ptimera;
   PFN_TIMER                           m_pfnTimer;
   timer_callback *                    m_pcallback;
   bool                                m_bPeriodic;
   void *                              m_pvoidData;
   bool                                m_bRunning;
   DWORD                               m_dwMillis;
   ::user::interaction *               m_puserinteraction;
   bool                                m_bHandling;

   bool                                m_bRet; // for event handlers ( _001OnTimer() )

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
   //timer_t              m_timerid;
   //struct sigevent      m_sev;
   //struct itimerspec    m_its;

//#endif



   timer(::apex::timer_array * ptimera, uptr uiTimer = 0, PFN_TIMER pfnTimer = nullptr, void * pvoidData = nullptr, class sync * pmutex = nullptr);
   virtual ~timer();


   void impl_init();
   void impl_term();

   //#ifdef LINUX
   virtual ::estatus run() override;

   //#endif


   bool start(int millis, bool bPeriodic);

   //void stop();

   void call_on_timer();

   virtual bool on_timer();

   bool impl_start();
   bool impl_restart();
   void impl_stop();
   virtual void term_thread() override;

   inline bool is_timer_ok() const { return is_ok(); }


   virtual bool thread_active() const override;


   //virtual void __destroy() override;


   // virtual void finalize() override;


};



