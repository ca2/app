#pragma once


#include "acme/primitive/primitive/function.h"
#include "acme/primitive/primitive/object.h"
#include "acme/primitive/collection/procedure_array.h"
#include "acme/platform/implementable.h"



typedef pointer_array < ::matter > object_array;
typedef map < itask_t, ::pointer<task >>task_map;
typedef map < task *, itask_t > task_id_map;


class CLASS_DECL_ACME task :
   virtual public object,
   //virtual public synchronization_object,
   virtual public acme::implementable
{
public:


   //Creatable(task);


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

   ::u64                                           m_uThreadAffinityMask;

#if defined(WINDOWS)

   ::pointer<::exception_translator>              m_pexceptiontranslator;

#endif


   htask_t                                         m_htask;
   itask_t                                         m_itask;
   string                                          m_strTaskName;
   string                                          m_strTaskTag;

   ::particle_array                                 m_particleaHold;
   ::pointer<manual_reset_event>                  m_peventInitialization;

   ::procedure                                     m_procedure;
   ::pointer<manual_reset_event>                  m_pevSleep;

#ifdef WINDOWS
   error_code                                      m_errorcodeHresultCoInitialize;
#endif

#ifdef __DEBUG
   char *                                          m_pszDebug;
#endif
   ::pointer<counter>                             m_pcounter;
   ::task_pointer                                  m_ptask;
   ::procedure                                     m_procedureNext;
   ::procedure_array                               m_procedurea;


   task();
   ~task() override;


   void on_initialize_particle() override;

   
   virtual void on_pre_run_task();


   string get_tag() const override;
   string task_get_name() const;


   ::task * get_task() override;
   const char * get_task_tag() override;

   
   void add_task(::object* pobjectTask) override;

   virtual bool is_current_task() const;
   //virtual object * calc_parent_thread();

   virtual bool task_set_name(const char* pszName);

#ifdef WINDOWS

   static ::u32 WINDOWS_API s_os_task(void* p);

#else

   static void* s_os_task(void* p);

#endif

   virtual bool is_task_registered() const;
   virtual void register_task();
   virtual void unregister_task();

   //virtual void add_notify(::matter* pmatter);
   //virtual void erase_notify(::matter* pmatter);

   virtual void post_procedure(const ::procedure & procedure);
   

   virtual void run_posted_procedures();

   virtual void task_caller_on_init();

   virtual bool on_get_task_name(string & strThreadName);


   void init_task() override;
   virtual void term_task();
   //virtual void do_task() override;
   //virtual void on_task() override;

   virtual bool do_events();
   virtual bool defer_pump_message();


   virtual bool has_message() const;

   ::pointer<::task>branch(const create_task_attributes & createtaskattributes = nullptr) override;

   ::pointer<::task>branch_synchronously(const create_task_attributes & createtaskattributes = nullptr) override;

   virtual bool task_sleep(const class ::wait & wait);

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
//      u32 nStackSize = 0,
//      u32 dwCreateFlags = 0);


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

   bool check_tasks_finished() override;

   virtual void update_task_ready_to_quit();

   virtual void kick_thread();

   virtual void main();

   void run() override;

   virtual void stop_task();


   void destroy() override;


   //virtual bool task_set_name(const char* pszThreadName);

   //virtual bool is_predicate() const { return !m_pobject || m_pobject.get() == this; }

   //virtual void set_thread_run(bool bRun = true);

   //virtual void finish() override;

   virtual void kick_idle() override;

   bool is_branch_current() const override;

};


using task_array = pointer_array < task >;






inline ::payload & task_property(const ::atom & atom) { return ::get_task()->payload(atom); }





class CLASS_DECL_ACME thread_local_particle :
   virtual public ::particle
{
public:


   thread_local_particle * m_pthreadlocalparticleNext;


   thread_local_particle();
   ~thread_local_particle() override;


};


template < typename TYPE >
class thread_local_pointer :
   public ::thread_local_particle,
   public pointer <TYPE >
{
public:


   using pointer < TYPE >::pointer;


   using pointer < TYPE >::operator = ;


};




bool on_init_thread();

void on_term_thread();


class task_guard
{
public:


   static thread_local thread_local_particle * t_pthreadlocalparticleList;


   task_guard();

   ~task_guard();


};


