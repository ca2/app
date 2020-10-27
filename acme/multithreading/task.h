#pragma once


class CLASS_DECL_ACME task :
   virtual public context_object
{
protected:



public:


   int                              m_bitAvoidProcFork : 1;
   int                              m_bitIsRunning : 1;
   int                              m_bitIsPred : 1; // Is helper thread (as opposite to a "main" thread)
   int                              m_bitCoInitialize : 1;


   HTHREAD                          m_hthread;
   ITHREAD                          m_ithread;
   string                           m_strTaskName;
   string                           m_strTaskTag;
   __pointer(::context_object)      m_pobjectParent;

   __pointer(::matter)              m_pmatter;
   __pointer(manual_reset_event)    m_pevSleep;

   HRESULT                          m_hresultCoInitialize;



   task();
   virtual ~task();


   virtual string get_tag() const;
   virtual string thread_get_name() const;

   
   virtual ::task * get_task() override;
   virtual const char * get_task_tag() override;


   //virtual context_object * calc_parent_thread();

   virtual bool set_thread_name(const char* pszName);

   

#ifdef WINDOWS

   static DWORD WINAPI s_os_task(void* p);

#else

   static void* s_os_task(void* p);

#endif

   virtual void add_notify(::matter* pmatter);
   virtual void remove_notify(::matter* pmatter);


   virtual bool on_get_thread_name(string & strThreadName);


   virtual void init_task();
   virtual void term_task();
   virtual ::estatus do_task() override;
   virtual ::estatus on_task() override;


   virtual ::estatus fork(
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0);


   virtual ::estatus start(
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


   virtual bool is_thread() const;
   virtual bool thread_get_run() const;

   virtual bool task_active() const;
   virtual bool is_running() const;

   //virtual bool set_thread_name(const char* pszThreadName);

   virtual bool is_pred() const { return !m_pobjectContext || m_pobjectContext.get() == this; }
   
   //virtual void set_thread_run(bool bRun = true);

   //virtual void finish() override;

   virtual void kick_idle();


};


using task_array = __pointer_array(task);




