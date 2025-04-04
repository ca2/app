#pragma once


class message_queue;


#include "apex/handler/manager.h"
//#include "apex/handler/source.h"
//#include "acme/handler/hancontext.h"
#include "apex/message/channel.h"
#include "acme/parallelization/task.h"
#include "acme/operating_system/message.h"


namespace user
{

   using interaction_base_array = ::pointer_array < ::user::interaction_base >;

} // namespace user


///
/// a thread must be always allocated in the heap
///
class CLASS_DECL_APEX thread :
   virtual public ::task,
   virtual public ::channel,
   virtual public ::manager
//,
  // virtual public ::handler_context
{
public:


   class CLASS_DECL_APEX file_info :
      virtual public object
   {
   public:


      file_info();
      ~file_info();

      class ::time                             m_timeFileSharingViolationTimeout;

   };



   //bool                                               m_bBranchHandling : 1;
   ::pointer<message_queue>                           m_pmessagequeue;
   bool                                               m_bClosedMessageQueue;
   ::pointer < ::request >                            m_prequest;


   MESSAGE                                            m_message;
   bool                                               m_bLastingThread;
   //bool                                               m_bMessageThread;
   bool                                               m_bDedicated;
   bool                                               m_bPreferLessGraphicsParallelization;
   bool                                               m_bThreadToolsForIncreasedFps;
   ::pointer < ::user::interaction_base_array >       m_puserinteractionbaseaThread;
   ::pointer< ::mutex >                               m_pmutexThreadUiPtra;
   single_lock *                                      m_pslUser;
   static bool                                        s_bAllocReady;


   //pointer<manual_reset_happening>                      m_phappeningStarted;
   ::pointer<manual_reset_happening>                      m_phappeningSync;
   ::pointer<manual_reset_happening>                      m_phappeningReady;

   enum_id                                            m_atomContextReference;

   bool                                               m_bAuraMessageQueue;
   bool                                               m_bReady;
   //bool                                               m_bSimpleMessageLoop;
   bool                                               m_bZipIsDir2;

   ::pointer<file_info>                               m_pfileinfo;

   bool                                               m_bDupHandle;

   string                                             m_strDebugType;

   ::pointer<::task_pool>                            m_ptaskpool;

   unsigned int                                              m_nDisablePumpCount;

   unsigned int                                              m_dwFinishTimeout;
   //bool                                               m_bThreadClosed;


   ::pointer<manual_reset_happening>                      m_phappening1;
   enum_priority                                      m_epriority;


   string                                             m_strDebug;
   string                                             m_strFile;
   int                                                m_iLine;

   bool                                               m_bTemporary;
   ::pointer<::object>                                m_pobjectScript;

   ::pointer_array < ::message::message >             m_messagea;
   numeric_array < enum_message >                     m_emessageaGetLast;

#ifdef WINDOWS
   ::raw_array < MESSAGE >                            m_messageaInitialQueue;
   //bool                                               m_bCertainlyTheresWindowsMessageQueue;
   //::pointer < ::manual_reset_happening >                 m_phappeningMessageQueueReady;
#endif

//#ifdef MACOS
//
//   array < CFRunLoopSourceRef >                       m_runloopsourcea;
//   CFRunLoopRef                                       m_runloop;
//
//#endif
//
//#ifdef WINDOWS
//
//   bool                                               m_bCoInitialize;
//   HRESULT                                            m_hresultCoInitialize;
//
//#endif

   ::pointer < pointer_array < happening > >            m_phappeningaWait;

public:


   thread();
   ~thread() override;

   
#ifdef _DEBUG

   long long increment_reference_count() override;
   long long decrement_reference_count() override;
   long long release() override;

#endif


   // void assert_ok() const override;
   //// void dump(dump_context & dumpcontext) const override;

   
   //using task::fork;
   //using channel::fork;
   
   
   //bool on_init_task() override;
   //void on_term_task() override;

   
   void add_task(::object* pobjectTask) override;


   inline message_queue* get_message_queue() { return m_pmessagequeue ? m_pmessagequeue.m_p : _get_message_queue(); }
   message_queue* _get_message_queue();

   bool peek_message(MESSAGE * pMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, bool bRemoveMessage = false);
   void get_message(MESSAGE * pMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax);
   void post_message(oswindow oswindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam);


   ::user::interaction_base_array & userprimitivea();


   void destroy() override;
   //virtual void set_finish_composites(::property_object* ppropertyobjectFinish) override;


   //void update_task_ready_to_quit() override;


   void add_waiting_happening(happening * phappening);
   void erase_waiting_happening(happening * phappening);

   // file related stuff
   file_info * get_file_info();
   class ::time get_file_sharing_violation_timeout();
   class ::time set_file_sharing_violation_timeout(const class time & time);

   //virtual bool is_running() const override;


//   virtual void branch(
//      ::matter * pmatter,
//      ::enum_priority epriority = e_priority_normal,
//      unsigned int nStackSize = 0,
//      unsigned int dwCreateFlags = 0 ARG_SEC_ATTRS_DEF) override;


   virtual htask get_htask() const;
   virtual itask get_itask() const;


   //virtual bool task_active() const override;





   virtual htask get_os_handle() const;

   //virtual bool thread_active() const;
   virtual bool is_dedicated_thread() const;
   virtual bool is_thread() const override;
   virtual ::thread * get_thread() override;
   //virtual bool is_running() const override;

   //virtual void set_os_data(void * pvoidOsData);
   //virtual void set_os_int(itask iData);


   //static ::pointer<thread>start(
   //   ::matter* pmatter,
   //   ::enum_priority epriority = e_priority_normal,
   //   unsigned int nStackSize = 0,
   //   unsigned int dwCreateFlags = 0);



   friend bool __internal_pre_translate_message(MESSAGE * pMsg);


   void thread_common_construct();

   virtual void on_ping() override;
   virtual bool is_pinging() const override;

   virtual int get_x_window_count() const;

   //virtual synchronization_result wait(const class time & time);

   bool set_thread_priority(::enum_priority epriority);

   ::enum_priority thread_priority();

   //virtual void set_thread_run(bool bRun = true);

   //inline ::command::command * command() { return m_pcommand; }
   //inline ::command::command * command() const { return ((thread *)this)->m_pcommand; }
   //virtual ::command::command * get_command();

   virtual ::task_pool* taskpool() override;

   //inline bool has_property(const ::atom& atom) const;
   //inline ::payload command_value(const ::atom& atom) const;
   //inline bool command_value_is_true(const ::atom& atom) const;


   virtual void post_message(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {});

   virtual void send_message(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {}, const class time & timeTimeout = ::time::infinity());

   virtual void post_element(const ::enum_message & emessage, const ::wparam & wparam, ::particle * pparticle);

   virtual void send_element(const ::enum_message & emessage, const ::wparam & wparam, ::particle * pparticle, const class time & timeTimeout = ::time::infinity());


   DECLARE_MESSAGE_HANDLER(on_message_branch);


   ///virtual void relay_exception(::exception_pointer e, e_thread ethreadSource = thread_none);
   virtual int _GetMessage(MESSAGE * lpMsg, ::windowing::window * pwindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax);

   virtual bool has_step() const;
   //virtual bool has_raw_message() const;
   bool has_message() const override;

   // running and idle processing
   virtual void pre_translate_message(::message::message * pmessage);
   virtual void app_pre_translate_message(::message::message * pmessage);
   virtual void session_pre_translate_message(::message::message * pmessage);
   virtual void system_pre_translate_message(::message::message * pmessage);
   //virtual void thread_loop(); // low level thread loop
   bool handle_messages() override;     // low level step
   virtual bool handle_message(bool & bContinue);     // low level message pump
   //virtual bool pump_runnable();
   bool task_iteration() override;
   using channel::get_message;
   virtual bool get_message();     // low level message pump
   //virtual bool raw_handle_message();     // low level message pump
   //bool defer_pump_message() override;     // deferred message pump
   virtual bool process_message(::message::message * pmessage);
   ///virtual void process_base_message(::message::message * pmessage);
   virtual bool process_thread_message(::message::message * pmessage);
   // apex commented
   //virtual void process_window_message(::user::message * pusermessage);
   virtual bool process_message();     // route message
   virtual bool raw_process_message();     // route message
   // virtual bool on_idle(int lCount); // return true if more idle processing
   virtual void on_thread_on_idle(::thread * pthread, int lCount);
   virtual bool is_idle_message(::message::message * pmessage);  // checks for special messages
   virtual bool is_idle_message();  // checks for special messages

   //void init_task() override;
   //virtual void on_pre_run_task();

   void __task_init() override;
   void __task_term() override;


   virtual void run() override;
   //virtual void main() override;
   virtual bool on_idle() override;

   //virtual void on_pos_run_thread();
   //void term_task() override;

   virtual void process_window_procedure_exception(const ::exception & e, ::message::message * pmessage);

   virtual void process_message_filter(int code, ::message::message * pmessage);

   // virtual void add(::user::interaction_base * pinteraction);
   //virtual void erase(::user::interaction_base * pinteraction);
   //virtual ::collection::count get_ui_count();
   //virtual ::user::interaction_base * get_ui(::collection::index iIndex);
   //virtual void set_timer(::user::interaction_base * pinteraction, uptr uEvent, unsigned int nEllapse);
   //virtual void unset_timer(::user::interaction_base * pinteraction, uptr uEvent);
   //virtual void set_auto_delete(bool bAutoDelete = true);
//   virtual ::user::interaction_base * get_active_user_interaction_base();
//   virtual void set_active_user_interaction_base(::user::interaction_base * pinteraction);
   //virtual void step_timer();
   //virtual bool on_run_step();


   virtual void Delete();
   // 'delete this' only if m_bAutoDelete == true

   virtual void dispatch_thread_message(::message::message * pmessage);  // helper


   


   //virtual void wait();


   //virtual ::task_index item() const;

   bool _has_main_loop_happening_unlocked() override;

   virtual void verb();


   ::task_pointer calc_parent();


   //virtual bool register_dependent_thread(::thread * pthread);
   //virtual void unregister_dependent_thread(::thread * pthread);
   //virtual bool on_register_dependent_thread(::thread * pthread);
   //virtual void on_unregister_dependent_thread(::thread * pthread);
   //virtual void signal_close_dependent_threads();
   //virtual void wait_close_dependent_threads(const class time & time);
   //virtual bool register_at_required_threads();
   //virtual void unregister_from_required_threads();
   //virtual void close_dependent_threads(const class ::time & dur);

   //virtual bool pump_sleep(const class time & timeWait, ::particle * pparticleSynchronization = nullptr);

   //bool do_tasks() override;
   // virtual bool do_events(const time& time);

   virtual bool task_get_run() const override;
   //virtual bool set_run();
   //virtual void destroy() override;
   //virtual bool is_set_finish() const;
   //virtual void finish() override;
   virtual void kick_idle() override;
   virtual void post_quit() override;
   //virtual void on_finish() override;


   virtual bool post_quit_message(int nExitCode);


   //virtual ::collection::index task_add(::task * ptask) override;
   virtual void task_erase(::task * ptask) override;
   //virtual void wait_quit(class ::time timeTimeout) override;

   void kick_thread() override;

   //virtual void defer_add_thread_run_wait(synchronization_array & soa);

   virtual void message_queue_message_handler(::message::message * pmessage);

   //DECLARE_MESSAGE_HANDLER(_001OnSendThreadMessage);
   //DECLARE_MESSAGE_HANDLER(_001OnThreadMessage);


   virtual void shutdown(bool bPrompt = true);

   virtual bool on_before_shutdown();

   virtual bool is_application() const;
   virtual bool is_session() const;
   virtual bool is_system() const;

   ///// thread implementation
   //void __task_init() override;
   //void __task_term() override;
   ////virtual void     on_thread_end();
   ////virtual void thread_delete();
   operator htask() const;


   void initialize(::particle * pparticle) override;


   //virtual void run() override;


   // void task_osinit() override;
   // void __task_init() override;
   // //virtual void __thread_main() override;
   // void __task_term() override;
   // void task_osterm() override;


   void branch(enum_parallelization eparallelization = e_parallelization_asynchronous, const create_task_attributes_t & createtaskattributes = {}) override;

   void branch_synchronously(const create_task_attributes_t & createtaskattributes = {}) override;


   virtual void stop_task() override;

   // virtual void inline_init();
   // virtual void inline_term();
   
   using task::post;
   virtual void post(::message::message * pmessage);

   virtual void handle_posted_messages();

   virtual bool initialize_message_queue();

   void message_handler(::message::message * pmessage) override;

   virtual void post_request(::request* prequest) override;

   virtual void on_request_message(::request* prequest);

   void request(::request * prequest) override;

   virtual ::e_status get_result_status();

   void delete_this() override;


protected:


   virtual void __priority_and_affinity() override;
//   void __os_initialize() override;
////   virtual void __os_thread_start();
//   //void __set_thread_on() override;
//   void __os_finalize() override;
//  // virtual void __os_thread_end();

   // last called function for the thread lifetime.
   // after its call, the thread object must considered invalid/destroyed
   //void __set_thread_off() override;


};


//namespace parallelization
//{
//
//
//   //CLASS_DECL_APEX void finish();
//   //CLASS_DECL_APEX bool post_quit_and_wait(const class time & time);
//
//
//   //CLASS_DECL_APEX void finish(::task * ptask);
//   //CLASS_DECL_APEX bool post_quit_and_wait(::thread * pthread, const class time & time);
//
//
//   //template < typename THREAD >
//   //void finish(::pointer<THREAD>& spthread)
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
//   //bool post_quit_and_wait(::pointer<THREAD>& spthread, const class time & time)
//   //{
//
//   //   if (spthread.is_set())
//   //   {
//
//   //      if (!::parallelization::post_quit_and_wait(spthread.m_p, time))
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



using id_thread_map = atom_map < ::pointer<thread > >;


//CLASS_DECL_APEX void sleep(const time& time);


//CLASS_DECL_APEX bool is_active(::thread * pthread);



//CLASS_DECL_APEX bool is_thread_on(itask atom);
//CLASS_DECL_APEX void set_thread_on(itask atom);
//CLASS_DECL_APEX void set_thread_off(itask atom);




//CLASS_DECL_APEX bool apex_task_sleep(const class time & time, synchronization* psync = nullptr);
CLASS_DECL_APEX bool thread_pump_sleep(const class time & timeWait, ::particle * pparticleSynchronization = nullptr);
CLASS_DECL_APEX bool app_sleep(::apex::application * papp, const class time & timeWait);




CLASS_DECL_APEX void defer_create_thread(::particle * pparticle);


template < typename PRED >
auto sync_predicate(void (* pfnBranch )(::particle * pparticleTask, enum_priority), PRED pred, const class time & timeWait, enum_priority epriority);




class CLASS_DECL_APEX thread_ptra :
   virtual public pointer_array < thread >
{
public:


   thread_ptra();
   thread_ptra(const thread_ptra & ptra):pointer_array < thread >(ptra) {}
   thread_ptra(thread_ptra && ptra) :pointer_array < thread >(::transfer(ptra)) {}
   virtual ~thread_ptra();

   virtual ::collection::count get_count_except_current_thread();
   //virtual void finish(::property_object * pcontextobjectFinish = nullptr) override;
   virtual void destroy() override;
   virtual void wait(const class time & timeWait, ::particle & particleSynchronousLock);

   thread_ptra & operator = (const thread_ptra & ptra) { pointer_array < thread >::operator =(ptra); return *this; }
   thread_ptra & operator = (thread_ptra && ptra) { pointer_array < thread >::operator =(::transfer(ptra)); return *this; }

};





