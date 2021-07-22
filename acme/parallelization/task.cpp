#include "framework.h"
#include "acme/operating_system.h"
#include "task.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/os/ansios/_pthread.h"


#endif


CLASS_DECL_ACME void clear_message_queue(itask_t idthread);


task::task()
{

   m_pobjectParentTask = ::get_task();

   if (m_pobjectParentTask)
   {

      m_pobjectParentTask->add_child_task(this);

   }

   m_bSetFinish = false;
   m_bTaskTerminated = false;
   m_bTaskStarted = false;
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


void task::add_child_task(::object* pobjectTask)
{

   if (m_pobjectParentTask)
   {

      // tasks tend to be ephemeral
      // let a parent that maybe more stable
      // to have the pobjectTask as child

      m_pobjectParentTask->add_child_task(pobjectTask);

   }
   else
   {

      ::object::add_child_task(pobjectTask);

   }

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

   return !m_bSetFinish;

}


bool task::is_ready_to_quit() const
{

   bool bShouldContinue = task_get_run();

   return !bShouldContinue && m_bTaskReady;

}


bool task::task_active() const
{

   return m_htask != (htask_t) 0;

}


bool task::is_running() const
{

   return m_bIsRunning;

}


bool task::check_children_task()
{

   auto b = ::object::check_children_task();

   if (m_bSetFinish)
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


::e_status task::main()
{

   if (m_pmatter != this)
   {

      run_posted_routines();

      auto estatus = m_pmatter->run();

      run_posted_routines();

      return estatus;

   }

   auto estatus = run();

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

   return estatus;

}





::e_status task::stop_task()
{

   auto estatus = finish();

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

      ::task* pthread = (::task*)p;

      ::set_task(pthread OBJ_REF_DBG_COMMA_P_FUNCTION_LINE(pthread));

      pthread->release(OBJ_REF_DBG_P_FUNCTION_LINE(pthread));

      try
      {

         pthread->main();


      }
      catch (...)
      {

      }

      clear_message_queue(pthread->m_itask);

      pthread->m_bTaskTerminated = true;

      //pthread->m_ptaskParent.release();

#if OBJ_REF_DBG

      if (pthread->m_countReference > 1)
      {

         __check_pending_releases(pthread);

      }

#endif

      ::thread_release(OBJ_REF_DBG_P_NOTE(pthread, ""));

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


::e_status task::post(const ::routine& routine)
{

   synchronous_lock synchronouslock(mutex());

   m_routineaPost.add(routine);

   return ::success;

}


::e_status task::run_posted_routines()
{

   synchronous_lock synchronouslock(mutex());

   if (m_routineaPost.has_element())
   {

      while (auto routine = m_routineaPost.pick_first())
      {

         synchronouslock.unlock();

         auto estatus = routine();

         synchronouslock.lock();

      }

   }

   return ::success;

}


//void task::add_notify(::matter* pmatter)
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   notify_array().add_item(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);
//
//}
//
//
//void task::erase_notify(::matter* pmatter)
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   if (m_pnotifya)
//   {
//
//      m_pnotifya->erase_item(pmatter OBJ_REF_DBG_COMMA_THIS);
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

      //::task_set_name(type_name());

      strTaskName = type_name();

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

   if (string(type_name()).contains("synth_thread"))
   {

      output_debug_string("synth_thread thread::thread_proc");

   }
   else if (string(type_name()).ends_ci("out"))
   {

      output_debug_string("synth_thread thread::out");

   }

}


void task::term_task()
{

   try
   {

      finalize();

   }
   catch (...)
   {

   }

   synchronous_lock synchronouslock(mutex());

   //if (m_pnotifya)
   //{

   //   auto notifya = *m_pnotifya;

   //   synchronouslock.unlock();

   //   for (auto & pmatter : notifya)
   //   {

   //      pmatter->task_erase(this);

   //      pmatter->task_on_term(this);

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
//   //   ::matter* pmatter;
//
//   //   {
//
//   //      synchronous_lock synchronouslock(mutex());
//
//   //      pmatter = m_pmatter.m_p;
//
//   //      m_bitIsRunning = pmatter != nullptr;
//
//   //      if (!m_bitIsRunning)
//   //      {
//
//   //         break;
//
//   //      }
//
//   //      m_id = pmatter->type_name();
//
//   //      task_set_name(m_id);
//
//   //      m_pmatter.m_p = nullptr;
//
//   //   }
//
//   //   pmatter->on_task();
//
//   //}
//
//   //return estatus;
//
//}


bool task::do_events()
{
   
   __throw(error_interface_only, "tasks don't have message queue, threads do");

   return true;

}


bool task::defer_pump_message()
{

   __throw(error_interface_only, "tasks don't have message queue, threads do");

   return false;

}


bool task::has_message() const
{

   __throw(error_interface_only, "tasks don't have message queue, threads do");

   return false;

}


//::e_status task::branch(
//   ::matter* pmatter,
//   ::e_priority epriority,
//   u32 nStackSize,
//   u32 uCreateFlags ARG_SEC_ATTRS)
//{
//
//   m_pmatter = pmatter;
//
//   m_id = pmatter->type_name();
//
//   return branch(epriority, nStackSize, uCreateFlags ADD_PARAM_SEC_ATTRS);
//
//}


::e_status task::branch(
   ::e_priority epriority,
   u32 nStackSize,
   u32 uCreateFlags ARG_SEC_ATTRS)
{

   if (m_id.is_empty())
   {

      if (m_pmatter)
      {

         m_id = m_pmatter->type_name();

      }
      else
      {

         m_id = type_name();

      }

   }

   if (m_id.is_empty() || m_id == "task" || m_id == "thread")
   {

      __throw(error_invalid_argument);

      return ::error_failed;

   }

//   if (::is_null(m_pmatter))
//   {
//
//      m_pmatter = this;
//
//   }

#ifdef __DEBUG

   string strId = m_id;

   if (strId.contains_ci("forking_thread"))
   {

#if 0

#ifdef WINDOWS_DESKTOP

      ::exception::engine().reset();

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
         critical_section_lock csl(&::exception::engine().m_criticalsection);

         engine_fileline(uia[5], 0, 0, &uiLine, nullptr);

      }

      strId = string(sz) + "(" + __str(uiLine) + ") :: forking_thread";

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

   // __task_procedure() should release this (pmatter)
   add_ref(OBJ_REF_DBG_THIS_FUNCTION_LINE);

   m_bIsRunning = true;

#ifdef WINDOWS

   DWORD dwThread = 0;

   m_bTaskStarted = true;

   m_htask = ::CreateThread(PARAM_SEC_ATTRS, nStackSize, (LPTHREAD_START_ROUTINE) &::task::s_os_task, (LPVOID)(task*)this, uCreateFlags, &dwThread);

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


//::e_status task::branch(::matter * pmatter, ::e_priority epriority, ::u32 nStackSize, u32 uCreateFlags ARG_SEC_ATTRS)
//{
//
//   auto ptask = __new(task);
//
//   ptask->branch(pmatter, epriority, nStackSize, uCreateFlags ADD_PARAM_SEC_ATTRS);
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







CLASS_DECL_ACME bool __task_sleep(task* task)
{

   while (task->task_get_run())
   {

      sleep(100_ms);

   }

   return false;

}


CLASS_DECL_ACME bool __task_sleep(task* pthread, millis millis)
{

   if (millis.m_i < 1000)
   {

      if (!pthread->task_get_run())
      {

         return false;

      }

      sleep(millis);

      return pthread->task_get_run();

   }

   auto iTenths = millis.m_i / 10;

   auto iMillis = millis.m_i % 10;

   try
   {

      __pointer(manual_reset_event) spev;

      {

         synchronous_lock synchronouslock(pthread->mutex());

         if (pthread->m_pevSleep.is_null())
         {

            pthread->m_pevSleep = __new(manual_reset_event());

            pthread->m_pevSleep->ResetEvent();

         }

         spev = pthread->m_pevSleep;

      }

      if (!pthread->task_get_run())
      {

         return false;

      }

      //while(iTenths > 0)
      //{

      pthread->m_pevSleep->wait(millis);

      if (!pthread->task_get_run())
      {

         return false;

      }

      //iTenths--;

   //}

   }
   catch (...)
   {

   }

   return pthread->task_get_run();

}


CLASS_DECL_ACME bool __task_sleep(::task* pthread, synchronization_object* psync)
{

   try
   {

      while (pthread->task_get_run())
      {

         if (psync->wait(100).succeeded())
         {

            break;

         }

      }

   }
   catch (...)
   {

   }

   return pthread->task_get_run();

}


CLASS_DECL_ACME bool __task_sleep(task* pthread, millis millis, synchronization_object* psync)
{

   if (millis.m_i < 1000)
   {

      if (!pthread->task_get_run())
      {

         return false;

      }

      psync->wait(millis);

      return pthread->task_get_run();

   }

   auto iTenths = millis.m_i / 100;

   auto iMillis = millis.m_i % 100;

   try
   {

      {

         pthread->m_pevSleep->wait(100);

         if (!pthread->task_get_run())
         {

            return false;

         }

         iTenths--;

      }

   }
   catch (...)
   {

   }

   return pthread->task_get_run();

}


CLASS_DECL_ACME bool task_sleep(millis millis, synchronization_object* psync)
{

   auto pthread = ::get_task();

   if (::is_null(pthread))
   {

      if (::is_null(psync))
      {

         if (__os(millis) == U32_INFINITE_TIMEOUT)
         {

         }
         else
         {

            ::sleep(millis);

         }

      }
      else
      {

         if (__os(millis) == U32_INFINITE_TIMEOUT)
         {

            return psync->lock();

         }
         else
         {

            return psync->lock(millis);

         }

      }

      return true;

   }

   if (::is_null(psync))
   {

      if (__os(millis) == U32_INFINITE_TIMEOUT)
      {

         return __task_sleep(pthread);

      }
      else
      {

         return __task_sleep(pthread, millis);

      }

   }
   else
   {

      if (__os(millis) == U32_INFINITE_TIMEOUT)
      {

         return __task_sleep(pthread, psync);

      }
      else
      {

         return __task_sleep(pthread, millis, psync);

      }

   }
}



