#include "framework.h"
#include "acme/operating_system.h"
//#include "task.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


CLASS_DECL_ACME void clear_message_queue(itask_t idthread);


task::task()
{

   m_pfnImplement = nullptr;

   //m_bTaskPending = true;

   //m_bSetFinish = false;
   //m_bTaskTerminated = false;
   //m_bTaskStarted = false;
   m_bCheckingChildrenTask = false;
   //m_pthread = nullptr;
   m_bMessageThread = false;
   m_bCoInitialize = false;
   m_bIsRunning = false;
   m_bIsPredicate = true;
   m_htask = null_hthread;
   m_itask = 0;

}


task::~task()
{


}



::e_status task::on_initialize_object()
{

   auto estatus = ::object::on_initialize_object();

   if(!estatus)
   {

      return estatus;

   }

   return ::success;

}


string task::get_tag() const
{

   return m_strTaskTag;

}



string task::task_get_name() const
{

   return m_strTaskName;

}


::task * task::get_task()
{

   return this;

}


const char * task::get_task_tag()
{

   return m_strTaskTag;

}


void task::add_task(::object* pobjectTask)
{

   if (m_pobjectParentTask)
   {

      // tasks tend to be ephemeral
      // let a parent that maybe more stable
      // to have the pobjectTask as child

      m_pobjectParentTask->add_task(pobjectTask);

   }
   else
   {

      ::object::add_task(pobjectTask);

   }

}


bool task::is_current_task() const
{

   auto itaskCurrent = ::get_current_ithread();

   return itaskCurrent == m_itask;

}


//::object * task::calc_parent_thread()
//{
//
//   return ::get_task();
//
//}


bool task::task_set_name(const char* pszTaskName)
{
   
   if(::get_current_ithread() == m_itask)
   {
      if (!::task_set_name(pszTaskName))
      {
         
         return false;
         
      }
   }


   m_strTaskName = pszTaskName;

   if (m_strTaskTag.is_empty() && m_strTaskName.has_char())
   {

      m_strTaskTag = m_strTaskName;

   }
//   if (!::task_set_name(m_htask, pszTaskName))
//   {
//
//      return false;
//
//   }
//
   return true;

}


bool task::task_get_run() const
{

   return !is_finishing();

}


bool task::is_ready_to_quit() const
{

   bool bShouldContinue = task_get_run();

   return !bShouldContinue;

}


bool task::task_active() const
{

   return m_htask != (htask_t) 0;

}


bool task::is_running() const
{

   return m_bIsRunning;

}


bool task::check_tasks_finished()
{

   auto b = ::object::check_tasks_finished();

   if (is_finishing())
   {

      update_task_ready_to_quit();

   }

   return b;

}


void task::update_task_ready_to_quit()
{


}


bool task::kick_thread()
{

   return false;

}


::e_status task::on_pre_run_task()
{

   return ::success;

}


::e_status task::main()
{

   if(defer_implement(m_psystem))
   {

      return m_psystem->m_estatus;

   }

   if (::is_set(m_pelement) && m_pelement != this)
   {

      run_posted_routines();

      auto estatus = m_pelement->run();

      run_posted_routines();

      return estatus;

   }

   auto estatus = on_pre_run_task();

   if (!estatus)
   {

      return estatus;

   }

   estatus = run();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status task::run()
{

   auto estatus = run_posted_routines();

   if (!estatus)
   {

      return estatus;

   }

   if (defer_implement(m_psystem))
   {

      return m_psystem->m_estatus;


   }

   return estatus;

}


::e_status task::stop_task()
{

   auto estatus = check_tasks_finished();

   // but it should wait for thread to finish...

   __throw(todo);

   return estatus;

}



bool task::is_thread() const
{

   return false;

}


#ifdef WINDOWS
::u32 WINAPI task::s_os_task(void* p)
#else
void* task::s_os_task(void* p)
#endif
{

   try
   {

      ::task * ptask = (::task*)p;

      ::set_task(ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(ptask));

      //ptask->release(OBJECT_REFERENCE_COUNT_DEBUG_P_FUNCTION_LINE(ptask));

      try
      {

         ptask->main();


      }
      catch (...)
      {

         _ERROR(ptask, "Exception reached task procedure");

      }

      clear_message_queue(ptask->m_itask);

      ptask->set(e_flag_task_terminated);

#if OBJECT_REFERENCE_COUNT_DEBUG

      if (ptask->m_countReference > 1)
      {

         __check_pending_releases(ptask);

      }

#endif

      try
      {

         __pointer(::object) pparentTask = ptask->m_pobjectParentTask;

         if (::is_set(pparentTask))
         {

            try
            {

               pparentTask->transfer_tasks_from(ptask);

            }
            catch (...)
            {

            }

            try
            {

               pparentTask->erase_task(ptask);

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      ::thread_release(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(ptask, ""));

   }
   catch (...)
   {

   }

   return 0;

}


bool task::is_task_registered() const
{
   
   auto psystem = m_psystem;

   return psystem->get_task_id(this) != 0;

}


void task::register_task()
{

   auto psystem = m_psystem;

   psystem->set_task(m_itask, this);

}


void task::unregister_task()
{

   auto psystem = m_psystem;

   psystem->unset_task(m_itask, this);

}


::e_status task::post_routine(const ::routine& routine)
{

   if (!routine)
   {

      return false;

   }

   synchronous_lock synchronouslock(mutex());

   m_routinea.add(routine);

   kick_idle();

   return ::success;

}



::e_status task::run_posted_routines()
{

   synchronous_lock synchronouslock(mutex());

   if (m_routinea.has_element())
   {

      do
      {

         auto routine = m_routinea.pick_first();

         synchronouslock.unlock();

         auto estatus = routine();

         synchronouslock.lock();

      } while (m_routinea.has_element());


      return ::success;

   }

   return ::success_none;

}


//void task::add_notify(::element* pelement)
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   notify_array().add_item(pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);
//
//}
//
//
//void task::erase_notify(::element* pelement)
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   if (m_pnotifya)
//   {
//
//      m_pnotifya->erase_item(pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);
//
//   }
//
//}


bool task::on_get_task_name(string & strTaskName)
{

   if (m_strTaskTag.has_char())
   {

      //::task_set_name(m_strTaskTag);

      strTaskName = m_strTaskTag;

   }
   else
   {

      //::task_set_name(__type_name(this));

      strTaskName = __type_name(this);

   }

   return true;

}


::e_status task::task_caller_on_init()
{

   return ::success;

}


void task::init_task()
{

   string strTaskName;

   if (on_get_task_name(strTaskName))
   {

      task_set_name(strTaskName);

   }

   if (__type_name(this).contains("synth_thread"))
   {

      output_debug_string("synth_thread thread::thread_proc");

   }
   else if (__type_name(this).ends_ci("out"))
   {

      output_debug_string("synth_thread thread::out");

   }

}


void task::term_task()
{

   //try
   //{

   //   destroy();

   //}
   //catch (...)
   //{

   //}

   synchronous_lock synchronouslock(mutex());

   //if (m_pnotifya)
   //{

   //   auto notifya = *m_pnotifya;

   //   synchronouslock.unlock();

   //   for (auto & pelement : notifya)
   //   {

   //      pelement->task_erase(this);

   //      pelement->task_on_term(this);

   //   }

   //   synchronouslock.lock();

   //}

   //if (m_pthreadParent)
   //{

   //   m_pthreadParent->task_on_term(this);

   //   m_pthreadParent->task_erase(this);

   //   //m_pthreadParent->kick_idle();

   //}

}


//::e_status task::do_task()
//{
//
//   init_task();
//
//   auto estatus = on_task();
//
//   term_task();
//
//   return estatus;
//
//}
//
//
//::e_status task::on_task()
//{
//
//   //::e_status estatus = ::success;
//
//   //while (!m_bSetFinish)
//   //{
//
//   //   ::element* pelement;
//
//   //   {
//
//   //      synchronous_lock synchronouslock(mutex());
//
//   //      pelement = m_pelement.m_p;
//
//   //      m_bitIsRunning = pelement != nullptr;
//
//   //      if (!m_bitIsRunning)
//   //      {
//
//   //         break;
//
//   //      }
//
//   //      m_id = __type_name(pelement);
//
//   //      task_set_name(m_id);
//
//   //      m_pelement.m_p = nullptr;
//
//   //   }
//
//   //   pelement->on_task();
//
//   //}
//
//   //return estatus;
//
//}


bool task::do_events()
{
   
   throw interface_only_exception("tasks don't have message queue, threads do");

   return true;

}


bool task::defer_pump_message()
{

   throw interface_only_exception("tasks don't have message queue, threads do");

   return false;

}


bool task::has_message() const
{

   throw interface_only_exception("tasks don't have message queue, threads do");

   return false;

}


//::e_status task::branch(
//   ::element* pelement,
//   ::enum_priority epriority,
//   u32 nStackSize,
//   u32 uCreateFlags ARG_SEC_ATTRS)
//{
//
//   m_pelement = pelement;
//
//   m_id = __type_name(pelement);
//
//   return branch(epriority, nStackSize, uCreateFlags ADD_PARAM_SEC_ATTRS);
//
//}


::e_status task::branch(::enum_priority epriority, u32 nStackSize, u32 uCreateFlags ARG_SEC_ATTRS)
{

   if (m_id.is_empty())
   {

      if (m_pelement)
      {

         m_id = __type_name(m_pelement);

      }
      else
      {

         m_id = __type_name(this);

      }

   }

   if (m_id.is_empty() || m_id == "task" || m_id == "thread")
   {

      __throw(error_invalid_argument);

      return ::error_failed;

   }

//   if (::is_null(m_pelement))
//   {
//
//      m_pelement = this;
//
//   }

#ifdef __DEBUG

   string strId = m_id;

   if (strId.contains_ci("forking_thread"))
   {

#if 0

#ifdef WINDOWS_DESKTOP

      ::exception_engine().reset();

      OS_DWORD                dwDisplacement;

      OS_DWORD                uia[4096];

      dwDisplacement = 0;

      ::u32 maxframes = sizeof(uia) / sizeof(uia[0]);

      ULONG BackTraceHash;

      int iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID *>(&uia), &BackTraceHash);

      char sz[1024];

      __zero(sz);

      engine_symbol(sz, sizeof(sz), &dwDisplacement, uia[5]);

      u32 uiLine = 0;

      {
         critical_section_lock csl(&::exception_engine().m_criticalsection);

         engine_fileline(uia[5], 0, 0, &uiLine, nullptr);

      }

      strId = string(sz) + "(" + __string(uiLine) + ") :: forking_thread";

#endif

#endif

   }

   m_pszDebug = strdup(strId);

#endif

   auto estatus = task_caller_on_init();

   if (!estatus)
   {

      return estatus;

   }

   //if (m_pobjectParent && m_bIsPredicate)
   //{

   //   //auto pthreadParent = calc_parent_thread();

   //   m_pobjectParent->task_add(this);


   //   if (pthreadParent)
   //   {

   //

   //   }

   //}

   // __task_procedure() should release this (pelement)
   //increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);

   m_bIsRunning = true;

   set(e_flag_task_started);

   if (::is_null(m_pobjectParentTask))
   {

      auto pobjectParentTask = ::get_task();

      if (::is_null(pobjectParentTask))
      {

         pobjectParentTask = m_pcontext;

      }

      if (::is_null(pobjectParentTask))
      {

         pobjectParentTask = m_psystem;

      }

      if (pobjectParentTask)
      {

         if (pobjectParentTask != this)
         {

            pobjectParentTask->add_task(this);

         }

      }
      else
      {

         __throw(error_invalid_usage);

      }

   }

#ifdef WINDOWS

   DWORD dwThread = 0;

   m_htask = ::CreateThread((LPSECURITY_ATTRIBUTES)PARAM_SEC_ATTRS, nStackSize, (LPTHREAD_START_ROUTINE) &::task::s_os_task, (LPVOID)(task*)this, uCreateFlags, &dwThread);

   m_itask = dwThread;

#else

   pthread_attr_t taskAttr;

   pthread_attr_init(&taskAttr);

   if (nStackSize > 0)
   {

      pthread_attr_setstacksize(&taskAttr, nStackSize); // Set the stack size of the task

   }

   pthread_attr_setdetachstate(&taskAttr, PTHREAD_CREATE_DETACHED); // Set task to detached state. No need for pthread_join

   pthread_create(
      (pthread_t *) &m_htask,
      &taskAttr,
      &task::s_os_task,
      this);

#endif

   if (!m_htask)
   {

      m_bIsRunning = false;

      return ::error_failed;

   }

   return ::success;

}


bool task::task_sleep(const class ::wait & wait)
{
   
   auto waitStart = ::wait::now();
   
   while(task_get_run())
   {

      auto waitStep = minimum(wait - waitStart.elapsed(), 100_ms);

      if (!waitStep)
      {

         return true;

      }
      
      ::preempt(waitStep);
      
   }
   
   return false;

}

//::e_status task::branch(::element * pelement, ::enum_priority epriority, ::u32 nStackSize, u32 uCreateFlags ARG_SEC_ATTRS)
//{
//
//   auto ptask = __new(task);
//
//   ptask->branch(pelement, epriority, nStackSize, uCreateFlags ADD_PARAM_SEC_ATTRS);
//
//   return ptask;
//
//}





//
//bool task::task_set_name(const char* pszThreadName)
//{
//
//   if (!::task_set_name(m_htask, pszThreadName))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}

//
//void task::set_task_run(bool bRun)
//{
//
//   m_bRunThisThread = bRun;
//
//}


void task::kick_idle()
{


}


bool task::is_branch_current() const
{

   return ::get_current_ithread() == m_itask;

}




CLASS_DECL_ACME bool __task_sleep(task* task)
{

   while (task->task_get_run())
   {

      preempt(100_ms);

   }

   return false;

}


CLASS_DECL_ACME bool __task_sleep(task* ptask, const class ::wait & wait)
{

   if (wait < 1000_ms)
   {

      if (!ptask->task_get_run())
      {

         return false;

      }

      preempt(wait);

      return ptask->task_get_run();

   }

   auto iTenths = wait.m_i / 10;

   auto iMillis = wait.m_i % 10;

   try
   {

      __pointer(manual_reset_event) spev;

      {

         synchronous_lock synchronouslock(ptask->mutex());

         if (ptask->m_pevSleep.is_null())
         {

            ptask->m_pevSleep = __new(manual_reset_event());

            ptask->m_pevSleep->ResetEvent();

         }

         spev = ptask->m_pevSleep;

      }

      if (!ptask->task_get_run())
      {

         return false;

      }

      //while(iTenths > 0)
      //{

      ptask->m_pevSleep->wait(wait);

      if (!ptask->task_get_run())
      {

         return false;

      }

      //iTenths--;

   //}

   }
   catch (...)
   {

   }

   return ptask->task_get_run();

}


CLASS_DECL_ACME bool __task_sleep(::task* ptask, synchronization_object* psync)
{

   try
   {

      while (ptask->task_get_run())
      {

         if (psync->wait(100_ms).succeeded())
         {

            break;

         }

      }

   }
   catch (...)
   {

   }

   return ptask->task_get_run();

}


CLASS_DECL_ACME bool __task_sleep(task* ptask, const class ::wait & wait, synchronization_object* psync)
{

   if (wait < 1000_ms)
   {

      if (!ptask->task_get_run())
      {

         return false;

      }

      psync->_wait(wait);

      return ptask->task_get_run();

   }

   auto iTenths = wait.m_i / 100;

   auto iMillis = wait.m_i % 100;

   try
   {

      {

         ptask->m_pevSleep->_wait(100_ms);

         if (!ptask->task_get_run())
         {

            return false;

         }

         iTenths--;

      }

   }
   catch (...)
   {

   }

   return ptask->task_get_run();

}


//CLASS_DECL_ACME bool task_sleep(const ::duration & duration)
//{
//
//   auto ptask = ::get_task();
//
//   if (::is_null(ptask))
//   {
//
//      if (::is_null(psync))
//      {
//
//         if (__os(::duration) == U32_INFINITE_TIMEOUT)
//         {
//
//         }
//         else
//         {
//
//            ::preempt(::duration);
//
//         }
//
//      }
//      else
//      {
//
//         if (__os(::duration) == U32_INFINITE_TIMEOUT)
//         {
//
//            return psync->lock();
//
//         }
//         else
//         {
//
//            return psync->lock(::duration);
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//   if (::is_null(psync))
//   {
//
//      if (__os(::duration) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __task_sleep(ptask);
//
//      }
//      else
//      {
//
//         return __task_sleep(ptask, ::duration);
//
//      }
//
//   }
//   else
//   {
//
//      if (__os(::duration) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __task_sleep(ptask, psync);
//
//      }
//      else
//      {
//
//         return __task_sleep(ptask, ::duration, psync);
//
//      }
//
//   }
//}
//




CLASS_DECL_ACME bool task_sleep(const class ::wait & wait)
{
   
   auto ptask = ::get_task();
   
   if(::is_null(ptask))
   {
    
      ::preempt(wait);
      
      return true;
      
   }
   
   if(!ptask->task_sleep(wait))
   {
      
      return false;
      
   }
      
   return true;
   
}



