#pragma once


typedef __pointer_array(::matter) object_array;
typedef map < itask_t, __pointer(task) > task_map;
typedef map < task *, itask_t > task_id_map;


class CLASS_DECL_ACME task :
   virtual public object
{

public:


   int                                 m_bAvoidProcedureFork : 1;
   int                                 m_bitIsRunning : 1;
   int                                 m_bIsPredicate : 1; // Is helper thread (as opposite to a "main" thread)
   int                                 m_bitCoInitialize : 1;


   htask_t                           m_htask;
   itask_t                           m_itask;
   string                              m_strTaskName;
   string                              m_strTaskTag;
   __pointer(::object)    m_pobjectParent;

   __pointer(::matter)            m_pmatter;
   __pointer(manual_reset_event)       m_pevSleep;

#ifdef WINDOWS
   HRESULT                          m_hresultCoInitialize;
#endif


   task();
   virtual ~task();


   virtual string get_tag() const;
   virtual string thread_get_name() const;


   virtual ::task * get_task() override;
   virtual const char * get_task_tag() override;


   virtual bool set_thread_name(const char* pszName);


#ifdef WINDOWS


#else

   static void* s_os_task(void* p);

#endif

   virtual void add_notify(::matter* pmatter);
   virtual void remove_notify(::matter* pmatter);


   virtual ::e_status task_caller_on_init();

   virtual bool on_get_thread_name(string & strThreadName);


   virtual void init_task();
   virtual void term_task();
   virtual ::e_status do_task() override;
   virtual ::e_status on_task() override;


   virtual ::e_status begin_task(
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0);


   virtual ::e_status start(
      ::matter* pmatter,
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0);




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


   virtual ::object * thread_parent();


   virtual bool is_thread() const override;
   virtual bool task_get_run() const;

   virtual bool task_active() const;
   virtual bool is_running() const;

   //virtual bool set_thread_name(const char* pszThreadName);

   virtual bool is_predicate() const { return !m_pobject || m_pobject.get() == this; }

   //virtual void set_thread_run(bool bRun = true);

   //virtual void finish() override;

   virtual void kick_idle() override;


};


using task_array = __pointer_array(task);




