#pragma once


//#include "acme/operating_system/error_code.h"
//#include "acme/prototype/prototype/_u32hash.h"
//#include "acme/prototype/prototype/function.h"
//#include "acme/prototype/prototype/object.h"
//#include "acme/prototype/collection/procedure_array.h"
#include "counter.h"
#include "acme/constant/happening.h"
#include "acme/handler/handler.h"
#include "acme/handler/source.h"
#include "acme/parallelization/synchronization_array.h"
#include "acme/platform/implementable.h"
#include "acme/prototype/data/property_container.h"
#ifndef WINDOWS

/*
 * Queue status flags for GetQueueStatus() and MsgWaitForMultipleObjects()
 */
#define QS_KEY              0x0001
#define QS_MOUSEMOVE        0x0002
#define QS_MOUSEBUTTON      0x0004
#define QS_POSTMESSAGE      0x0008
#define QS_TIMER            0x0010
#define QS_PAINT            0x0020
#define QS_SENDMESSAGE      0x0040
#define QS_HOTKEY           0x0080
#define QS_ALLPOSTMESSAGE   0x0100

#if(_WIN32_WINNT >= 0x0501)
#define QS_RAWINPUT         0x0400
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0602)
#define QS_TOUCH            0x0800
#define QS_POINTER          0x1000

#endif /* _WIN32_WINNT >= 0x0602 */


#define QS_MOUSE           (QS_MOUSEMOVE     | \
                            QS_MOUSEBUTTON)

#if (_WIN32_WINNT >= 0x602)
#define QS_INPUT           (QS_MOUSE         | \
                            QS_KEY           | \
                            QS_RAWINPUT      | \
                            QS_TOUCH         | \
                            QS_POINTER)

#else
#if (_WIN32_WINNT >= 0x0501)
#define QS_INPUT           (QS_MOUSE         | \
                            QS_KEY           | \
                            QS_RAWINPUT)
#else
#define QS_INPUT           (QS_MOUSE         | \
                            QS_KEY)
#endif // (_WIN32_WINNT >= 0x0501)
#endif

#define QS_ALLEVENTS       (QS_INPUT         | \
                            QS_POSTMESSAGE   | \
                            QS_TIMER         | \
                            QS_PAINT         | \
                            QS_HOTKEY)

#define QS_ALLINPUT        (QS_INPUT         | \
                            QS_POSTMESSAGE   | \
                            QS_TIMER         | \
                            QS_PAINT         | \
                            QS_HOTKEY        | \
                            QS_SENDMESSAGE)

#endif

DECLARE_ENUMERATION(e_happening, enum_happening);


class locale;

typedef pointer_array < ::matter > object_array;
typedef map < itask_t, ::pointer<task >>task_map;
typedef map < task *, itask_t > task_id_map;


::collection::index task_index(itask_t itask);
::collection::index task_index();


class CLASS_DECL_ACME task :
   virtual public object,
   //virtual public synchronization_object,
   virtual public acme::implementable,
   virtual public ::handler::handler,
   virtual public tracer,
   virtual public ::source,
   virtual public ::data::property_container
{
public:



   //Creatable(task);

   //bool                                            m_bAutoRelease : 1;
   bool                                            m_bAvoidProcedureFork : 1;
   bool                                            m_bIsRunning : 1;
   bool                                            m_bIsPredicate : 1; // Is helper thread (as opposite to a "main" thread)
#ifdef WINDOWS
   bool                                            m_bCoInitialize : 1;
#endif
   bool                                            m_bMessageThread : 1;
   bool                                            m_bTaskToolsForIncreasedFps : 1;
#ifdef PARALLELIZATION_PTHREAD
   bool                                            m_bJoinable : 1;
#endif
   bool                                            m_bKeepRunningPostedProcedures : 1;

   huge_natural                                           m_uThreadAffinityMask;

#if defined(WINDOWS)

   ::pointer<::exception_translator>               m_pexceptiontranslator;

#endif

   ::pointer<::manual_reset_event>                 m_pmanualreseteventNewProcedurePosted;

   ::synchronization_array                         m_synchronizationaMainLoop;
   htask_t                                         m_htask;
   itask_t                                         m_itask;
   string                                          m_strTaskName;
   string                                          m_strTaskTag;

   ::particle_array                                m_particleaHold;
   ::pointer<manual_reset_event>                   m_peventInitialization;

   ::procedure                                     m_procedure;
   ::pointer<manual_reset_event>                   m_pevSleep;
   ::pointer<manual_reset_event>                   m_peventFinished2;
   ::pointer<manual_reset_event>                   m_pmanualreseteventHappening;
   ::comparable_array<e_happening>                 m_ehappeninga;


#ifdef WINDOWS
   error_code                                      m_errorcodeHresultCoInitialize;
#endif

#ifdef __DEBUG
   char *                                          m_pszDebug;
#endif
   ::pointer < ::parallelization::counter >        m_pcounter;
   ::task_pointer                                  m_ptask;
   ::procedure                                     m_procedureNext;
   ::procedure_array                               m_procedurea;
   
   ::pointer < ::locale >                          m_plocale;

   class ::time                                    m_timeHeartBeat;
   ::procedure                                     m_procedureTaskEnded;

int m_iExitCode;

   task();
   ~task() override;


   void on_initialize_particle() override;

   
   virtual void on_pre_run_task();

   virtual void __priority_and_affinity();
   void set_finish() override;
   virtual void __os_initialize();
   //   virtual void __os_thread_start();
   virtual void __set_thread_on();
   virtual void __os_finalize();
   virtual void __set_thread_off();

   void task_osinit() override;

   //virtual bool os_on_init_task();
   //virtual void os_on_term_task();
   virtual ::manual_reset_event * new_procedure_posted_event();

   virtual procedure pick_next_posted_procedure();

   virtual e_happening pick_happening();

   string get_tag() const override;
   string task_get_name() const;


   ::task * get_task() override;
   const char * get_task_tag() override;

   
   void add_task(::object* pobjectTask) override;

   virtual bool is_current_task() const;
   //virtual object * calc_parent_thread();

   virtual void post_request(::request* prequest) override;

   virtual bool task_set_name(const ::scoped_string & scopedstrName);

#ifdef WINDOWS

   static unsigned int WINDOWS_API s_os_task(void* p);

#else

   static void* s_os_task(void* p);

#endif


   void _os_task(::procedure & procedureTaskEnded);

   virtual bool is_task_registered() const;
   virtual void register_task();
   virtual void unregister_task();
   
   
   virtual ::locale * locale();

   //virtual void add_notify(::matter* pmatter);
   //virtual void erase_notify(::matter* pmatter);

   void _post(const ::procedure & procedure) override;
   void _send(const ::procedure & procedure) override;

   //void _post(::subparticle * p) override;
   //void _send(::subparticle * p) override;

   //virtual v do_synchronously(sequence * psequence);


   virtual void handle_posted_procedures();

   virtual void task_caller_on_init();

   virtual bool on_get_task_name(string & strThreadName);

   virtual void set_happened(e_happening ehappening);

   virtual bool on_happening(e_happening ehappening);

   void init_task() override;
   virtual void term_task();
   //virtual void do_task() override;
   //virtual void on_task() override;

   //virtual bool do_tasks();
   //virtual bool defer_pump_message();


   virtual bool has_message() const;

   virtual void on_before_branch();

   virtual ::pointer<::task>branch(enum_parallelization eparallelization = e_parallelization_asynchronous, const create_task_attributes & createtaskattributes = nullptr);

   virtual ::pointer<::task>branch_synchronously(const create_task_attributes & createtaskattributes = nullptr);

   virtual bool task_sleep(const class time & timeWait);

   virtual void on_before_destroy_task();


   //template < typename METHOD >
   //inline static ::task_pointer __task(METHOD method)
   //{

   //   auto pmethod = method(method);

   //   auto ptask = start(pmethod);

   //   return ptask;

   //}


//   static ::task_pointer launch(
//      ::matter* pmatter,
//      ::enum_priority epriority = e_priority_normal,
//      unsigned int nStackSize = 0,
//      unsigned int dwCreateFlags = 0);


   //virtual ::property_object * thread_parent();

   void __task_init() override;
   void __task_term() override;


   virtual void on_task_init();
   virtual void on_task_term();


   virtual bool is_thread() const override;
   virtual bool task_get_run() const override;

   bool is_ready_to_quit() const override;

   virtual bool task_active() const;
   virtual bool is_running() const override;

   bool set_children_to_finish_and_check_them_finished() override;

   virtual void update_task_ready_to_quit();

   virtual void on_task_quit();

   virtual void kick_thread();

   virtual void main();

   void run() override;

   virtual bool task_run(const class ::time & time = 0_s);

   virtual bool task_iteration();

   virtual bool handle_messages();

   virtual void stop_task();


   void destroy() override;


   //virtual bool task_set_name(const ::scoped_string & scopedstrThreadName);

   //virtual bool is_predicate() const { return !m_pobject || m_pobject.get() == this; }

   //virtual void set_thread_run(bool bRun = true);

   //virtual void finish() override;

   virtual void set_current_handles();

   void kick_idle() override;

   bool is_branch_current() const override;


   virtual void synchronous_procedure(bool bAtAnotherThread, const procedure & procedure, const class ::time & timeTimeout = 0_s);


};


using task_array = pointer_array < task >;






inline ::payload & task_property(const ::atom & atom) { return ::get_task()->payload(atom); }




//
//class CLASS_DECL_ACME thread_local_particle :
//   virtual public ::particle
//{
//public:
//
//
//   thread_local_particle * m_pthreadlocalparticleNext;
//
//
//   thread_local_particle();
//   ~thread_local_particle() override;
//
//
//};
//
//
//template < typename TYPE >
//class thread_local_pointer :
//   public ::thread_local_particle,
//   public pointer <TYPE >
//{
//public:
//
//
//   using pointer < TYPE >::pointer;
//
//
//   using pointer < TYPE >::operator = ;
//
//
//};






typedef string GET_TASK_NAME(::task * ptask);
using LPFN_GET_TASK_NAME = GET_TASK_NAME *;


CLASS_DECL_ACME string get_task_name(htask_t htask);

CLASS_DECL_ACME void set_get_task_name(LPFN_GET_TASK_NAME);

CLASS_DECL_ACME void task_set_name(const char * pszName);
CLASS_DECL_ACME void task_set_name(htask_t htask, const char * pszName);


CLASS_DECL_ACME string task_get_name();
CLASS_DECL_ACME string task_get_name(htask_t htask);


CLASS_DECL_ACME void thread_name_abbreviate(string & strName, int len);


CLASS_DECL_ACME ::task * _get_task();


CLASS_DECL_ACME ::task * get_task();


//CLASS_DECL_ACME::task* get_task();
CLASS_DECL_ACME void set_task(task * ptask);

CLASS_DECL_ACME string get_task_name(::task * ptask);

CLASS_DECL_ACME string current_task_name();


template<typename THREAD_POINTER>
class ___task_pool;


using task_pointer = ::pointer<::task>;


class task_pool;








template < typename PRED >
inline void while_predicateicate_Sleep(int iTime, PRED pred)
{

   iTime += 99;

   iTime /= 100;

   for (::collection::index i = 0; i < iTime; i++)
   {

      preempt(100_ms);

      if (!pred())
      {

         return;

      }

      preempt();

   }

   throw ::exception(error_timeout);

}


CLASS_DECL_ACME void task_release();
CLASS_DECL_ACME void task_iteration();
CLASS_DECL_ACME void task_run(const class ::time & time = 0_s);



