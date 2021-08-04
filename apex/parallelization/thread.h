#pragma once


class message_queue;


///
/// a thread must be always allocated in the heap
///
class CLASS_DECL_APEX thread :
   virtual public task,
   virtual public channel
   , virtual public subject::context
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



   bool                                               m_bBranchHandling : 1;
   __composite(message_queue)                         m_pmq;
   bool                                               m_bClosedMq;


   MESSAGE                                            m_message;
   bool                                               m_bLastingThread;
   bool                                               m_bMessageThread;
   bool                                               m_bDedicated;
   bool                                               m_bPreferLessGraphicsParallelization;
   bool                                               m_bThreadToolsForIncreasedFps;
   ::e_status                                         m_estatus;
   user_interaction_ptr_array *                       m_puiptraThread;
   ::mutex *                                          m_pmutexThreadUiPtra;
   single_lock *                                      m_pslUser;
   static bool                                        s_bAllocReady;


   __pointer(manual_reset_event)                      m_peventInitialization;
   __pointer(manual_reset_event)                      m_peventStarted;
   __pointer(manual_reset_event)                      m_peventSync;
   __pointer(manual_reset_event)                      m_peventReady;
   __pointer(manual_reset_event)                      m_peventFinished;

   e_id                                               m_idContextReference;

   bool                                               m_bAuraMessageQueue;
   ::millis                                           m_millisHeartBeat;
   bool                                               m_bReady;
   ::extended::status                                 m_result;
   __pointer(::user::primitive)                       m_puserprimitiveMain;           // Main interaction_impl (usually same psystem->m_puiMain)
   __pointer(::user::primitive)                       m_puserprimitiveActive;         // Active Main interaction_impl (may not be m_puiMain)
   bool                                               m_bSimpleMessageLoop;
   bool                                               m_bZipIsDir2;

   __pointer(file_info)                               m_pfileinfo;

   bool                                               m_bDupHandle;

   string                                             m_strDebugType;

   __pointer(::task_pool)                             m_ptaskpool;

   ::u32                                              m_nDisablePumpCount;

   ::u32                                              m_dwFinishTimeout;
   bool                                               m_bThreadClosed;


   ::routine_array                                    m_routinea;


   __pointer(manual_reset_event)                      m_pevent1;
   e_priority                                         m_epriority;


   string                                             m_strDebug;
   string                                             m_strFile;
   int                                                m_iLine;

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
   ~thread() override;

   


   void assert_valid() const override;
   void dump(dump_context & dumpcontext) const override;

   
   //using task::fork;
   //using channel::fork;

   
   void add_task(::object* pobjectTask) override;


   inline message_queue* get_message_queue() { return m_pmq ? m_pmq : _get_mq(); }
   message_queue* _get_mq();

   int_bool peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);
   int_bool get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);
   int_bool post_message(oswindow oswindow, const ::id & id, wparam wParam, lparam lParam);

   user_interaction_ptr_array & uiptra();


   ::e_status destroy() override;
   //virtual ::e_status set_finish_composites(::property_object* ppropertyobjectFinish) override;


   //void update_task_ready_to_quit() override;


   void add_waiting_event(event * pevent);
   void erase_waiting_event(event * pevent);

   // file related stuff
   file_info * get_file_info();
   ::u32 get_file_sharing_violation_timeout_total_milliseconds();
   ::duration set_file_sharing_violation_timeout(::duration duration);

   virtual bool is_running() const override;


//   virtual ::e_status branch(
//      ::matter * pmatter,
//      ::e_priority epriority = priority_normal,
//      u32 nStackSize = 0,
//      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF) override;


   virtual htask_t get_hthread() const;
   virtual itask_t get_ithread() const;


   virtual bool task_active() const override;


   virtual void set_current_handles();

   virtual htask_t get_os_handle() const;

   //virtual bool thread_active() const;
   virtual bool is_dedicated_thread() const;
   virtual bool is_thread() const override;
   virtual ::thread * get_thread() override;
   //virtual bool is_running() const override;

   //virtual void set_os_data(void * pvoidOsData);
   //virtual void set_os_int(itask_t iData);


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

   //virtual synchronization_result wait(const duration & duration);

   bool set_thread_priority(::e_priority epriority);

   ::e_priority thread_priority();

   //virtual void set_thread_run(bool bRun = true);

   //inline ::command::command * command() { return m_pcommand; }
   //inline ::command::command * command() const { return ((thread *)this)->m_pcommand; }
   //virtual ::command::command * get_command();

   virtual ::task_pool* taskpool() override;

   //inline bool has_property(const ::id& id) const;
   //inline ::payload command_value(const ::id& id) const;
   //inline bool command_value_is_true(const ::id& id) const;


   ///virtual u32 ResumeThread();
   virtual bool post_message(const ::id & id, wparam wParam = 0, lparam lParam = 0);

   virtual bool send_message(const ::id & id, wparam wParam = 0,lparam lParam = 0, ::duration durationTimeout = ::duration::infinite());

   virtual bool post_object(const ::id & id, wparam wParam, ::matter * pmatter);

   virtual bool send_object(const ::id & id, wparam wParam, ::matter * pmatter, ::duration durationTimeout = ::duration::infinite());

   virtual bool post_task(const ::routine & routine);
   virtual bool send_task(const ::routine & routine, ::duration durationTimeout = ::duration::infinite());

   template < typename PRED >
   bool pred(PRED pred)
   {
      return post_runnable(__runnable(pred));
   }

   template < typename PRED >
   bool post_predicate(PRED pred)
   {
      return post_object(e_message_system, e_system_message_method, __routine(pred));
   }


   bool send_routine(const ::routine & routine, ::duration durationTimeout = ::duration::infinite())
   {

      return send_object(e_message_system, e_system_message_method, routine, durationTimeout);

   }


   template < typename PRED >
   bool schedule_predicate(PRED pred)
   {

      return post_predicate(pred);

   }


   bool sync_procedure(const ::routine & routine, ::duration durationTimeout = ::duration::infinite())
   {

      if (this == ::get_task())
      {

         routine();

         return true;

      }

      return send_routine(routine, durationTimeout);

   }

   ::e_status post(const ::routine& routine) override;

   DECLARE_MESSAGE_HANDLER(on_message_branch);


   //virtual bool final_handle_exceptionconst ::exception::exception & e;
   //__pointer(::matter) running(const char * pszTag) const override;

   ///virtual void relay_exception(::exception_pointer e, e_thread ethreadSource = thread_none);
   virtual int _GetMessage(MESSAGE * lpMsg, ::windowing::window * pwindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

   virtual bool has_step() const;
   virtual bool has_raw_message() const;
   bool has_message() const override;

   // running and idle processing
   virtual void pre_translate_message(::message::message * pmessage);
   virtual void app_pre_translate_message(::message::message * pmessage);
   virtual void session_pre_translate_message(::message::message * pmessage);
   virtual void system_pre_translate_message(::message::message * pmessage);
   virtual ::e_status thread_loop(); // low level thread loop
   virtual bool thread_step();     // low level step
   virtual bool pump_message();     // low level message pump
   virtual bool pump_runnable();
   using channel::get_message;
   virtual bool get_message();     // low level message pump
   virtual bool raw_pump_message();     // low level message pump
   bool defer_pump_message() override;     // deferred message pump
   virtual ::e_status process_message(::message::message * pmessage);
   ///virtual ::e_status process_base_message(::message::message * pmessage);
   virtual ::e_status process_thread_message(::message::message * pmessage);
   // apex commented
   //virtual void process_window_message(::user::message * pusermessage);
   virtual ::e_status process_message();     // route message
   virtual ::e_status raw_process_message();     // route message
   // virtual bool on_idle(::i32 lCount); // return true if more idle processing
   virtual ::e_status on_thread_on_idle(::thread * pthread, ::i32 lCount);
   virtual bool is_idle_message(::message::message * pmessage);  // checks for special messages
   virtual bool is_idle_message();  // checks for special messages

   virtual ::e_status init_thread();
   virtual ::e_status on_pre_run_thread();

   virtual ::e_status run() override;
   virtual ::e_status main() override;

   virtual void on_pos_run_thread();
   virtual void term_thread();

   virtual void process_window_procedure_exception(const ::exception::exception & e, ::message::message * pmessage);

   virtual void process_message_filter(i32 code, ::message::message * pmessage);

   // virtual void add(::user::primitive * pinteraction);
   //virtual void erase(::user::primitive * pinteraction);
   //virtual ::count get_ui_count();
   //virtual ::user::primitive * get_ui(index iIndex);
   //virtual void set_timer(::user::primitive * pinteraction, uptr uEvent, ::u32 nEllapse);
   //virtual void unset_timer(::user::primitive * pinteraction, uptr uEvent);
   //virtual void set_auto_delete(bool bAutoDelete = true);
   virtual ::user::primitive * get_active_user_primitive();
   virtual void set_active_user_primitive(::user::primitive * pinteraction);
   //virtual void step_timer();
   //virtual bool on_run_step();


   virtual void Delete();
   // 'delete this' only if m_bAutoDelete == true

   virtual void dispatch_thread_message(::message::message * pmessage);  // helper


   


   //virtual void wait();


   virtual iptr item() const;



   virtual ::e_status verb();


   ::task_pointer calc_parent();


   //virtual bool register_dependent_thread(::thread * pthread);
   //virtual void unregister_dependent_thread(::thread * pthread);
   //virtual bool on_register_dependent_thread(::thread * pthread);
   //virtual void on_unregister_dependent_thread(::thread * pthread);
   //virtual void signal_close_dependent_threads();
   //virtual void wait_close_dependent_threads(const duration & duration);
   //virtual bool register_at_required_threads();
   //virtual void unregister_from_required_threads();
   //virtual void close_dependent_threads(const ::duration & dur);

   virtual bool pump_sleep(const millis & millis, synchronization_object * psync);

   bool do_events() override;
   // virtual bool do_events(const duration& duration);

   virtual bool task_get_run() const override;
   //virtual bool set_run();
   //virtual ::e_status destroy() override;
   //virtual bool is_set_finish() const;
   //virtual void finish() override;
   virtual void kick_idle() override;
   virtual void post_quit() override;
   //virtual ::e_status on_finish() override;


   virtual bool post_quit_message(int nExitCode);


   //virtual ::index task_add(::task * ptask) override;
   virtual void task_erase(::task * ptask) override;
   //virtual void wait_quit(::duration durationTimeout) override;

   bool kick_thread() override;

   //virtual void defer_add_thread_run_wait(synchronization_array & soa);

   virtual void message_queue_message_handler(::message::message * pmessage);

   //DECLARE_MESSAGE_HANDLER(_001OnSendThreadMessage);
   //DECLARE_MESSAGE_HANDLER(_001OnThreadMessage);


   virtual void shutdown(bool bPrompt = true);

   virtual bool on_before_shutdown();

   virtual bool is_application() const;
   virtual bool is_session() const;
   virtual bool is_system() const;

   //virtual void delete_this();

   /// thread implementation
   virtual ::e_status on_thread_init();
   virtual ::e_status on_thread_term();
   //virtual ::e_status     on_thread_end();
   //virtual void thread_delete();
   operator htask_t() const;


   virtual ::e_status initialize(::object * pobject) override;


   //virtual ::e_status run() override;


   virtual ::e_status osthread_init() override;
   virtual ::e_status __thread_init() override;
   //virtual ::e_status __thread_main() override;
   virtual ::e_status __thread_term() override;
   virtual ::e_status osthread_term() override;


   virtual e_status begin_thread(
   bool bSynchInitialization = false,
   ::e_priority epriority = ::priority_normal,
   ::u32 nStackSize = 0,
   u32 uiCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   using task::branch;
   using object::branch;

   virtual ::e_status branch(
   ::e_priority epriority = ::priority_normal,
   ::u32 nStackSize = 0,
   u32 uiCreateFlags = 0 ARG_SEC_ATTRS_DEF) override;


   virtual ::e_status begin_synch(
   ::e_priority epriority = ::priority_normal,
   ::u32 nStackSize = 0,
   u32 uiCreateFlags = 0 ARG_SEC_ATTRS_DEF);


   virtual ::e_status inline_init();
   virtual ::e_status inline_term();



   virtual bool initialize_message_queue();

   virtual void message_handler(::message::message * pmessage);

   virtual void do_request(::create * pcreate) override;

   virtual ::e_status get_result_status();

   virtual void delete_this() override;


protected:


   virtual void __priority_and_affinity();
   virtual void __os_initialize();
//   virtual ::e_status __os_thread_start();
   virtual void __set_thread_on();
   virtual void __os_finalize();
  // virtual ::e_status __os_thread_end();

   // last called function for the thread lifetime.
   // after its call, the thread object must considered invalid/destroyed
   virtual void __set_thread_off();


};


//namespace parallelization
//{
//
//
//   //CLASS_DECL_APEX void finish();
//   //CLASS_DECL_APEX bool post_quit_and_wait(const duration & duration);
//
//
//   //CLASS_DECL_APEX void finish(::task * ptask);
//   //CLASS_DECL_APEX bool post_quit_and_wait(::thread * pthread, const duration & duration);
//
//
//   //template < typename THREAD >
//   //void finish(__pointer(THREAD) & spthread)
//   //{
//
//   //   if (spthread.is_set())
//   //   {
//
//   //      ::parallelization::finish(spthread.m_p);
//
//   //      spthread.release();
//
//   //   }
//
//   //}
//
//
//   //template < typename THREAD >
//   //bool post_quit_and_wait(__pointer(THREAD) & spthread, const duration & duration)
//   //{
//
//   //   if (spthread.is_set())
//   //   {
//
//   //      if (!::parallelization::post_quit_and_wait(spthread.m_p, duration))
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      spthread.release();
//
//   //   }
//
//   //   return true;
//
//   //}
//
//
//
//
//} // namespace parallelization



using id_thread_map = id_map < __pointer(thread) >;


//CLASS_DECL_APEX void sleep(const duration& duration);


//CLASS_DECL_APEX bool is_active(::thread * pthread);



//CLASS_DECL_APEX bool is_thread_on(itask_t id);
//CLASS_DECL_APEX void set_thread_on(itask_t id);
//CLASS_DECL_APEX void set_thread_off(itask_t id);




//CLASS_DECL_APEX bool apex_task_sleep(millis millis, synchronization_object* psync = nullptr);
CLASS_DECL_APEX bool thread_pump_sleep(millis millis, synchronization_object* psync = nullptr);
CLASS_DECL_APEX bool app_sleep(::application * papplication, millis millis);



template < typename PRED >
inline ::synchronization_result while_predicateicate_Sleep(int iTime, PRED pred)
{

   iTime += 99;

   iTime /= 100;

   for (index i = 0; i < iTime; i++)
   {

      sleep(100_ms);

      if (!pred())
      {

         return  ::e_synchronization_result_signaled_base;

      }

      if (!::task_get_run())
      {

         return ::e_synchronization_result_abandoned_base;

      }

   }

   return ::e_synchronization_result_timed_out;

}


CLASS_DECL_APEX void defer_create_thread(::object * pobject);




template < typename PRED >
auto sync_predicate(void (* pfnBranch )(::matter * pobjectTask, e_priority), PRED pred, ::duration durationTimeout, e_priority epriority);


