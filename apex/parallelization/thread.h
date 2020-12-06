#pragma once



class mq;


namespace user { class frame;  }

///
/// a thread must be always allocated in the heap
///
class CLASS_DECL_APEX thread :
   virtual public task,
   virtual public channel
   , virtual public promise::context
#ifdef WINDOWS
   ,virtual public ::exception::translator
#endif
{
public:


   class CLASS_DECL_APEX file_info :
      virtual public object
   {
   public:


      file_info();
      ~file_info();

      ::duration                             m_durationFileSharingViolationTimeout;

   };


   __composite(mq)                                    m_pmq;
   bool                                               m_bClosedMq;


   MESSAGE                                            m_message;
   bool                                               m_bLastingThread;
   bool                                               m_bMessageThread;
   bool                                               m_bDedicated;
   bool                                               m_bThreadToolsForIncreasedFps;
   ::estatus                                          m_estatus;
   user_interaction_ptr_array *                       m_puiptraThread;
   ::mutex *                                          m_pmutexThreadUiPtra;
   single_lock *                                      m_pslUser;
   static bool                                        s_bAllocReady;

#ifdef __DEBUG
   char *                                             m_pszDebug;
#endif

   __pointer(manual_reset_event)                      m_pevent;
   __pointer(manual_reset_event)                      m_pevStarted;
   __pointer(manual_reset_event)                      m_pevSync;
   __pointer(manual_reset_event)                      m_pevReady;

   bool                                               m_bAuraMessageQueue;
   ::millis                                           m_millisHeartBeat;
   bool                                               m_bReady;
   ::status::result                                   m_result;
   __pointer(::layered)                               m_puiMain1;           // Main interaction_impl (usually same System.m_puiMain)
   __pointer(::layered)                               m_puiActive;         // Active Main interaction_impl (may not be m_puiMain)
   bool                                               m_bSimpleMessageLoop;
   bool                                               m_bZipIsDir2;

   __pointer(file_info)                               m_pfileinfo;
   __pointer(counter)                                 m_pcounter;

   bool                                               m_bDupHandle;

   string                                             m_strDebugType;

   address_array < ::user::frame * >                  m_frameptra;

   __pointer(::task_pool)                             m_ptaskpool;

   ::u32                                              m_nDisablePumpCount;

   ::u32                                              m_dwFinishTimeout;
   bool                                               m_bThreadClosed;


   ::promise::routine_array                                    m_routinea;


   __pointer(manual_reset_event)                      m_pevent1;
   e_priority                                         m_epriority;


   string                                             m_strDebug;
   string                                             m_strFile;
   int                                                m_iLine;

   ::u64                                              m_uThreadAffinityMask;
   bool                                               m_bTemporary;
   __pointer(::object)                                m_pobjectScript;


#ifdef MACOS

   array < CFRunLoopSourceRef >                       m_runloopsourcea;
   CFRunLoopRef                                       m_runloop;

#endif

#ifdef WINDOWS

   bool                                               m_bCoInitialize;
   HRESULT                                            m_hresultCoInitialize;

#endif

   __pointer_array(event)                             m_eventaWait;

public:


   thread();
   virtual ~thread();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;

   
   //using task::fork;
   //using channel::fork;

   inline mq* get_mq() { return m_pmq ? m_pmq : _get_mq(); }
   mq* _get_mq();

   int_bool peek_message(LPMESSAGE pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);
   int_bool get_message(LPMESSAGE pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);
   int_bool post_message(oswindow oswindow, const ::id & id, WPARAM wParam, LPARAM lParam);

   user_interaction_ptr_array & uiptra();


   virtual ::estatus set_finish(::context_object * pcontextobjectFinish) override;
   virtual ::estatus set_finish_composites(::context_object * pcontextobjectFinish) override;


   //virtual context_object* calc_parent_thread() override;

//#ifdef WINDOWS_DESKTOP
//
//   virtual void associate_imc(::user::interaction* pinteraction);
//
//#endif

   void add_waiting_event(event * pevent);
   void remove_waiting_event(event * pevent);

   // file related stuff
   file_info * get_file_info();
   ::u32 get_file_sharing_violation_timeout_total_milliseconds();
   ::duration set_file_sharing_violation_timeout(::duration duration);

   virtual bool is_running() const;
   //virtual void dependant_add(::layered * pobjectContext) override;



   virtual ::estatus start(
      ::matter * pmatter,
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0) override;


   virtual hthread_t get_hthread() const;
   virtual ithread_t get_ithread() const;


   virtual bool task_active() const;


   virtual void set_current_handles();

   virtual hthread_t get_os_handle() const;

   //virtual bool thread_active() const;
   virtual bool is_dedicated_thread() const;
   virtual bool is_thread() const override;
   virtual ::thread * get_thread() override;
   //virtual bool is_running() const override;

   //virtual void set_os_data(void * pvoidOsData);
   //virtual void set_os_int(ithread_t iData);


   //static __pointer(thread) start(
   //   ::matter* pmatter,
   //   ::e_priority epriority = priority_normal,
   //   u32 nStackSize = 0,
   //   u32 dwCreateFlags = 0);



   friend bool __internal_pre_translate_message(MESSAGE * pMsg);


   void thread_common_construct();

   virtual void on_keep_alive() override;
   virtual bool is_alive() override;

   virtual int get_x_window_count() const;

   virtual sync_result wait(const duration & duration);

   bool set_thread_priority(::e_priority epriority);

   ::e_priority thread_priority();

   //virtual void set_thread_run(bool bRun = true);

   //inline ::command::command * command() { return m_pcommand; }
   //inline ::command::command * command() const { return ((thread *)this)->m_pcommand; }
   //virtual ::command::command * get_command();

   virtual ::task_pool* taskpool() override;

   //inline bool has_property(const ::id& id) const;
   //inline payload command_value(const ::id& id) const;
   //inline bool command_value_is_true(const ::id& id) const;


   ///virtual u32 ResumeThread();
   virtual bool post_message(const ::id & id, WPARAM wParam = 0, lparam lParam = 0);

   virtual bool send_message(const ::id & id,WPARAM wParam = 0,lparam lParam = 0, ::duration durationTimeout = ::duration::infinite());

   virtual bool post_object(const ::id & id, WPARAM wParam, ::matter * pmatter);

   virtual bool send_object(const ::id & id, WPARAM wParam, lparam lParam, ::duration durationTimeout = ::duration::infinite());

   virtual bool post_task(const ::promise::routine & routine);
   virtual bool send_task(const ::promise::routine & routine, ::duration durationTimeout = ::duration::infinite());

   template < typename PRED >
   bool pred(PRED pred)
   {
      return post_runnable(__runnable(pred));
   }

   template < typename PRED >
   bool post_pred(PRED pred)
   {
      return post_object(e_message_system, system_message_method, __routine(pred));
   }


   bool send_routine(const ::promise::routine & routine, ::duration durationTimeout = ::duration::infinite())
   {

      return send_object(e_message_system, system_message_method, routine, durationTimeout);

   }


   template < typename PRED >
   bool schedule_pred(PRED pred)
   {

      return post_pred(pred);

   }


   bool sync_procedure(const ::promise::routine & routine, ::duration durationTimeout = ::duration::infinite())
   {

      if (this == ::get_task())
      {

         routine();

         return true;

      }

      return send_routine(routine, durationTimeout);

   }


   //virtual bool final_handle_exception(::exception_pointer e);
   __pointer(::matter) running(const char * pszTag) const override;

   ///virtual void relay_exception(::exception_pointer e, e_thread ethreadSource = thread_none);
   virtual int _GetMessage(LPMESSAGE lpMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

   virtual bool has_step() const;
   virtual bool has_raw_message() const;
   virtual bool has_message() const;

   // running and idle processing
   virtual void pre_translate_message(::message::message * pmessage);
   virtual void app_pre_translate_message(::message::message * pmessage);
   virtual void session_pre_translate_message(::message::message * pmessage);
   virtual void system_pre_translate_message(::message::message * pmessage);
   virtual ::estatus thread_loop(); // low level thread loop
   virtual bool thread_step();     // low level step
   virtual bool pump_message();     // low level message pump
   virtual bool pump_runnable();
   virtual bool get_message();     // low level message pump
   virtual bool raw_pump_message();     // low level message pump
   virtual bool defer_pump_message();     // deferred message pump
   virtual void process_message(::message::base * pbase);
   virtual ::estatus process_base_message(::message::base * pbase);
   virtual void process_thread_message(::message::base * pbase);
   // apex commented
   //virtual void process_window_message(::message::base * pbase);
   virtual ::estatus process_message();     // route message
   virtual ::estatus raw_process_message();     // route message
   // virtual bool on_idle(::i32 lCount); // return TRUE if more idle processing
   virtual ::estatus on_thread_on_idle(::thread * pthread, ::i32 lCount);
   virtual bool is_idle_message(::message::message * pmessage);  // checks for special messages
   virtual bool is_idle_message();  // checks for special messages

   virtual ::estatus init_thread();
   virtual ::estatus on_pre_run_thread();

   virtual ::estatus run() override;

   virtual void on_pos_run_thread();
   virtual void term_thread();

   virtual void process_window_procedure_exception(::exception_pointer pe, ::message::message * pmessage);

   virtual void process_message_filter(i32 code, ::message::message * pmessage);

   // virtual void add(::user::primitive * pinteraction);
   //virtual void remove(::user::primitive * pinteraction);
   //virtual ::count get_ui_count();
   //virtual ::user::primitive * get_ui(index iIndex);
   //virtual void set_timer(::user::primitive * pinteraction, uptr uEvent, ::u32 nEllapse);
   //virtual void unset_timer(::user::primitive * pinteraction, uptr uEvent);
   //virtual void set_auto_delete(bool bAutoDelete = true);
   virtual ::user::primitive * get_active_ui();
   virtual ::user::primitive * set_active_ui(::layered * pinteraction);
   //virtual void step_timer();
   //virtual bool on_run_step();


   virtual void Delete();
   // 'delete this' only if m_bAutoDelete == TRUE

   virtual void dispatch_thread_message(::message::message * pmessage);  // helper


   virtual ::estatus     main();


   virtual void wait();


   virtual iptr item() const;



   virtual ::estatus verb();


   static void post_quit_to_all_threads();
   static void post_to_all_threads(const ::id & id, WPARAM wparam, LPARAM lparam);



   //virtual bool register_dependent_thread(::thread * pthread);
   //virtual void unregister_dependent_thread(::thread * pthread);
   //virtual bool on_register_dependent_thread(::thread * pthread);
   //virtual void on_unregister_dependent_thread(::thread * pthread);
   //virtual void signal_close_dependent_threads();
   //virtual void wait_close_dependent_threads(const duration & duration);
   //virtual bool register_at_required_threads();
   //virtual void unregister_from_required_threads();
   //virtual void close_dependent_threads(const ::duration & dur);


   virtual bool do_events();
   // virtual bool do_events(const duration& duration);

   virtual bool thread_get_run() const override;
   //virtual bool set_run();
   virtual void finalize() override;
   //virtual bool is_set_finish() const;
   //virtual void finish() override;
   virtual void kick_idle() override;
   virtual void post_quit() override;
   virtual void on_finish() override;

   //virtual ::index task_add(::task * ptask) override;
   virtual void task_remove(::task * ptask) override;
   //virtual void wait_quit(::duration durationTimeout) override;

   virtual bool kick_thread();

   //virtual void defer_add_thread_run_wait(sync_array & soa);

   virtual void message_queue_message_handler(::message::base * pmessage);

   //DECL_GEN_SIGNAL(_001OnSendThreadMessage);
   //DECL_GEN_SIGNAL(_001OnThreadMessage);


   virtual void shutdown(bool bPrompt = true);

   virtual bool on_before_shutdown();

   virtual bool is_application() const;
   virtual bool is_session() const;
   virtual bool is_system() const;

   //virtual void delete_this();

   /// thread implementation
   virtual ::estatus on_thread_init();
   virtual ::estatus on_thread_term();
   //virtual ::estatus     on_thread_end();
   //virtual void thread_delete();
   operator hthread_t() const;


   virtual ::estatus initialize(::layered * pobjectContext) override;


   virtual ::estatus do_task() override;


   virtual ::estatus osthread_init() override;
   virtual ::estatus __thread_init() override;
   virtual ::estatus __thread_main() override;
   virtual ::estatus __thread_term() override;
   virtual ::estatus osthread_term() override;


   virtual bool begin_thread(
   bool bSynchInitialization = false,
   ::e_priority epriority = ::priority_normal,
   ::u32 nStackSize = 0,
   u32 uiCreateFlags = 0,
   LPSECURITY_ATTRIBUTES psa = nullptr);



   virtual bool begin(
   ::e_priority epriority = ::priority_normal,
   ::u32 nStackSize = 0,
   u32 uiCreateFlags = 0,
   LPSECURITY_ATTRIBUTES psa = nullptr);


   virtual bool begin_synch(
   ::e_priority epriority = ::priority_normal,
   ::u32 nStackSize = 0,
   u32 uiCreateFlags = 0,
   LPSECURITY_ATTRIBUTES psa = nullptr);


   virtual ::estatus inline_init();
   virtual ::estatus inline_term();



   virtual bool initialize_message_queue();

   virtual void message_handler(::message::base * pbase);

   virtual ::estatus     do_request(::create * pcreate) override;

   virtual ::estatus     get_result_status();

   virtual void delete_this() override;


protected:


   virtual void __priority_and_affinity();
   virtual void __os_initialize();
//   virtual ::estatus __os_thread_start();
   virtual void __set_thread_on();
   virtual void __os_finalize();
  // virtual ::estatus __os_thread_end();

   // last called function for the thread lifetime.
   // after its call, the thread object must considered invalid/destroyed
   virtual void __set_thread_off();


};


namespace parallelization
{


   CLASS_DECL_APEX void finish();
   CLASS_DECL_APEX bool post_quit_and_wait(const duration & duration);


   CLASS_DECL_APEX void finish(::task * ptask);
   CLASS_DECL_APEX bool post_quit_and_wait(::thread * pthread, const duration & duration);


   template < typename THREAD >
   void finish(__pointer(THREAD) & spthread)
   {

      if (spthread.is_set())
      {

         ::parallelization::finish(spthread.m_p);

         spthread.release();

      }

   }


   template < typename THREAD >
   bool post_quit_and_wait(__pointer(THREAD) & spthread, const duration & duration)
   {

      if (spthread.is_set())
      {

         if (!::parallelization::post_quit_and_wait(spthread.m_p, duration))
         {

            return false;

         }

         spthread.release();

      }

      return true;

   }




} // namespace parallelization


using id_thread_map = id_map < __pointer(thread) >;


//CLASS_DECL_APEX void sleep(const duration& duration);


CLASS_DECL_APEX bool is_active(::thread * pthread);



CLASS_DECL_APEX bool is_thread_on(ithread_t id);
CLASS_DECL_APEX void set_thread_on(ithread_t id);
CLASS_DECL_APEX void set_thread_off(ithread_t id);




//CLASS_DECL_APEX bool apex_task_sleep(millis millis, sync* psync = nullptr);
CLASS_DECL_APEX bool thread_pump_sleep(millis millis, sync* psync = nullptr);
CLASS_DECL_APEX bool app_sleep(millis millis);



template < typename PRED >
inline ::sync_result while_pred_Sleep(int iTime, PRED pred)
{

   iTime += 99;

   iTime /= 100;

   for (index i = 0; i < iTime; i++)
   {

      sleep(100_ms);

      if (!pred())
      {

         return  ::sync_result::result_event0;

      }

      if (!::thread_get_run())
      {

         return ::sync_result::result_abandon0;

      }

   }

   return ::sync_result::result_timeout;

}


CLASS_DECL_APEX void defer_create_thread(::layered * pobjectContext);




template < typename PRED >
auto sync_pred(void (* pfnBranch )(::matter * pobjectTask, e_priority), PRED pred, ::duration durationTimeout, e_priority epriority);


