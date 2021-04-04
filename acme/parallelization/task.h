#pragma once


typedef __pointer_array(::matter) object_array;
typedef map < itask_t, __pointer(task) > task_map;
typedef map < task *, itask_t > task_id_map;


class CLASS_DECL_ACME task :
   virtual public object
{

public:


   bool                                            m_bAvoidProcedureFork : 1;
   bool                                            m_bIsRunning : 1;
   bool                                            m_bIsPredicate : 1; // Is helper thread (as opposite to a "main" thread)
   bool                                            m_bCoInitialize : 1;
   bool                                            m_bMessageThread : 1;


   ::u64                                           m_uThreadAffinityMask;


   htask_t                                         m_htask;
   itask_t                                         m_itask;
   string                                          m_strTaskName;
   string                                          m_strTaskTag;
   __pointer(::property_object)                    m_pobjectParent;

   __pointer(::matter)                             m_pmatter;
   __pointer(manual_reset_event)                   m_pevSleep;

#ifdef WINDOWS
   HRESULT                                         m_hresultCoInitialize;
#endif

#ifdef __DEBUG
   char *                                          m_pszDebug;
#endif
   __pointer(counter<::i32>)                       m_pcounter;
   ::thread *                                      m_pthread;
   ::routine                                       m_routineNext;


   task();
   virtual ~task();


   virtual string get_tag() const;
   virtual string thread_get_name() const;


   virtual ::task * get_task() override;
   virtual const char * get_task_tag() override;


   //virtual object * calc_parent_thread();

   virtual bool set_thread_name(const char* pszName);

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


   virtual ::e_status task_caller_on_init();

   virtual bool on_get_thread_name(string & strThreadName);


   virtual void init_task();
   virtual void term_task();
   //virtual ::e_status do_task() override;
   //virtual ::e_status on_task() override;

   virtual bool do_events();
   virtual bool defer_pump_message();

   virtual bool has_message() const;

   virtual ::e_status begin(
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);


   virtual ::e_status start(
      ::matter* pmatter,
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);




   //template < typename METHOD >
   //inline static ::task_pointer __task(METHOD method)
   //{

   //   auto pmethod = method(method);

   //   auto ptask = start(pmethod);

   //   return ptask;

   //}


   static ::task_pointer launch(
      ::matter* pmatter,
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0);


   virtual ::property_object * thread_parent();


   virtual bool is_thread() const override;
   virtual bool task_get_run() const;

   virtual bool task_active() const;
   virtual bool is_running() const;


   virtual ::e_status main();


   //virtual bool set_thread_name(const char* pszThreadName);

   //virtual bool is_predicate() const { return !m_pobject || m_pobject.get() == this; }

   //virtual void set_thread_run(bool bRun = true);

   //virtual void finish() override;

   virtual void kick_idle() override;


};


using task_array = __pointer_array(task);




