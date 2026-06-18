// Deep Refactoring timer_handler by camilo on 2026-05-28 10:33 <3ThomasBorregaardSørensen!! Mummi!! Bilbo
#pragma once


//#include "timer.h"
//#include "timer_array.h"
//#include "acme/parallelization/task.h"
#include "acme/constant/timer.h"


DECLARE_ENUMERATION(e_timer, enum_timer);


class timer :
   virtual public ::timer_callback::base,
   virtual public ::particle
{
public:


   ::pointer<::timer_handler> m_ptimerhandler;
   ::pointer<::timer_dispatch> m_ptimerdispatch;
   ::e_timer m_etimer;
   class ::time m_time;
   ::timer_callback m_callback;
   class ::time m_timeStart;
   ::i64 m_iCall = 0;
   bool m_bRet = false;
   ::pointer < ::particle > m_pcarrier1;


   void cancel(){m_bRet=true;}

   void restart() { m_timeStart.Now(); }

   bool should_call() const { return m_timeStart.elapsed() >= m_time; }

   void operator()(::timer *ptimer) override
   {

      m_iCall++;

      if (m_callback)
      {

         m_callback(ptimer);

      }

   }


};


using timer_map = ø<::map<::e_timer, ::pointer<::timer>>>;


using timer_dispatch_map = ::map<::timer_dispatch *, ::timer_map >;


/// Maybe a "very lazy" timer, yet simple ("KISS")
/// cross platform, with "reasonable" resolution (not high precision), 
/// and with "reasonable" performance (not high performance, but not bad either)
class CLASS_DECL_ACME timer_handler :
   virtual public ::particle
{
public:


   class ::time m_timeResolution;
   ::timer_dispatch_map m_timermap;

   //::pointer < manual_reset_happening > m_pmanualresethappeningWait;

   //::pointer<::acme::timer_array> m_ptimera;
   //PFN_TIMER                           m_pfnTimer;
   //void *                              m_pvoidData;
   //::procedure                         m_procedure;
   //bool                                m_bRunning;

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

   //bool                 m_bInit;
   //e_timer_t              m_timerid;
   //struct sigevent      m_sev;
   //struct itimerspec    m_its;

//#endif



   timer_handler();
   ~timer_handler() override;


   //void on_initialize_particle() override;


   virtual ::timer * add_timer(::timer_dispatch * ptimerdispatch, const ::e_timer & etimer, const class ::time & time, const ::timer_callback &callback);
   virtual void erase_timer(::timer_dispatch * ptimerdispatch, const ::e_timer & etimer);
   //virtual void add_timer_dispatch(::timer_dispatch * ptimerdispatch);
   virtual void erase_timer_dispatch(::timer_dispatch * ptimerdispatch);
   //virtual void erase_key_particle(::particle * pparticleKey);

   bool are_there_timers_to_handle() const {return m_timermap.count() > 0;}

   virtual void on_start_timers_handling_hint();
   virtual void on_stop_timers_handling_hint();
   //void impl_init();
   //void impl_term();


   //virtual void initialize_timer(::particle* pparticle, ::acme::timer_array* ptimera, uptr uiTimer = 0, const ::timer_callback & callback = {}, ::particle* pparticleSynchronization = nullptr);

   virtual void handle_timers();

   virtual void _handle_timers(::timer_map * ptimermap);




   //virtual void start_timer_handler(const class time & timeWait, bool bPeriodic);


   //virtual void on_timer();

   //virtual void destroy() override;

   //virtual void stop_timer_handler();

   ////bool impl_start();
   ////bool impl_restart();
   ////void impl_stop();
   //void term_task() override;

   //inline bool is_timer_ok() const { return is_ok(); }


   //bool is_task_set() const override;


};


//class CLASS_DECL_ACME timer_notify_sink :
class CLASS_DECL_ACME timer_dispatch :
   virtual public ::timer_callback::base,
   virtual public ::particle
{
public:


   ::pointer < ::timer_map >            m_ptimermap;
   ::pointer_array<::timer_handler>     m_timerhandlera;


   timer_dispatch();
   ~timer_dispatch() override;


   virtual ::timer_map * get_timer_map();

   virtual ::timer_handler * get_timer_handler(const class ::time &time);
   //virtual void add_timer_dispatch(const ::e_timer & etimer, const class ::time & time, const ::timer_callback &callback);
   //virtual void erase_timer(const ::e_timer & etimer);
   //virtual void erase_key_particle(::particle * pparticleKey);

   bool are_there_timers_to_handle() const {return m_ptimermap && m_ptimermap->count() >0;}

   virtual ::timer * set_timer(const ::e_timer & etimer, const class ::time &time, const ::timer_callback &callback = {},
                          ::timer_handler *ptimerhandler = nullptr);
   virtual void kill_timer(const ::e_timer & etimer);

   virtual ::comparable_array_base < ::e_timer > all_timers_ids();

   virtual void erase_all_timers();

   virtual void erase_timers(const ::comparable_array_base < ::e_timer > & etimera);



};

