#include "framework.h"
#include "task.h"
#include "manual_reset_event.h"
////#include "acme/exception/exception.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/translator.h"
#include "acme/parallelization/synchronous_lock.h"


#include "acme/exception/_text_stream.h"
#include "acme/_operating_system.h"


bool on_init_thread();

void on_term_thread();


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


CLASS_DECL_ACME void clear_message_queue(itask_t idthread);


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);


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
#ifdef WINDOWS
   m_bCoInitialize = false;
#endif
   m_bIsRunning = false;
   m_bIsPredicate = true;
   
#ifdef PARALLELIZATION_PTHREAD

   m_bJoinable = false;
   
#endif
   
   m_htask = null_htask;
   m_itask = 0;

}


#undef TASK_DESTRUCTOR_REPORTING


task::~task()
{

#if defined(_DEBUG) && defined(TASK_DESTRUCTOR_REPORTING)

   auto strThreadName = ::task_get_name();
   auto itask = ::get_current_itask();

   ::output_debug_string("Task destructor : " + strThreadName + " : (" + ::as_string(itask) + ")\n");

#endif

}



void task::on_initialize_particle()
{

   /*auto estatus =*/ ::object::on_initialize_particle();

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return ::success;

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

   return m_strTaskTag.c_str();

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

   auto itaskCurrent = ::get_current_itask();

   return itaskCurrent == m_itask;

}


//::object * task::calc_parent_thread()
//{
//
//   return ::get_task();
//
//}


void task::post_request(::request* prequest)
{

   ::pointer < ::request > prequestTransport;

   post_procedure([this, prequestTransport]
      {

         request(prequestTransport);

      }
   );

}


bool task::task_set_name(const ::scoped_string & scopedstrTaskName)
{
   
   if(::get_current_itask() == m_itask)
   {
      
      ::task_set_name(scopedstrTaskName);
      //{
      //   
      //   return false;
      //   
      //}
   }


   m_strTaskName = scopedstrTaskName;

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

   return !has_finishing_flag();

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

   if (has_finishing_flag())
   {

      update_task_ready_to_quit();

   }

   return b;

}


void task::update_task_ready_to_quit()
{


}


void task::kick_thread()
{

   // return false;

}


void task::on_pre_run_task()
{

   //return ::success;

}


bool task::on_init_task()
{

   if (!::on_init_thread())
   {

      return false;
    
   }

   return true;

}


void task::on_term_task()
{

   ::on_term_thread();

}


void task::main()
{

   __task_init();

   if(defer_implement(acmesystem()))
   {

      return;

   }

   if (m_procedure && m_procedure != this)
   {

      run_posted_procedures();

      m_procedure();

      run_posted_procedures();

   }

   on_pre_run_task();

   try
   {

      run();

   }
   catch(::exception & exception)
   {

      message_box_synchronous(this, exception.m_strMessage, acmeapplication()->m_strAppId, e_message_box_ok, exception.m_strDetails);

   }
   catch(...)
   {

   }

  __task_term();

}


void task::run()
{

   try
   {

      run_posted_procedures();

      if (defer_implement(m_pcontext))
      {

         return;

      }

   }
   catch(::exception & exception)
   {

      string strMoreDetails;

      strMoreDetails = "task::run";

      exception_message_box(exception, strMoreDetails);

   }


}


void task::stop_task()
{

   auto estatus = check_tasks_finished();

   // but it should wait for thread to finish...

   throw ::exception(todo);

   //return estatus;

}


void task::destroy()
{
   
   ::object::destroy();

#ifdef WINDOWS

   if (m_pexceptiontranslator)
   {

      m_pexceptiontranslator->detach();

      m_pexceptiontranslator.release();

   }

#endif

}


void task::__task_init()
{

   on_task_init();

   if (m_peventInitialization)
   {

      m_peventInitialization->set_event();

   }


}


void task::__task_term()
{

   on_task_term();

}


void task::on_task_init()
{

   init_task();

   m_estatus = ::success;

}



void task::on_task_term()
{

   term_task();

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

#if defined(WINDOWS)

      ptask->__defer_construct(ptask->m_pexceptiontranslator);

      ptask->m_pexceptiontranslator->attach();

#endif

      try
      {

         ptask->main();

      }
      catch (::exit_exception & exitexception)
      {

         _ERROR(ptask, "Exit Exception reached task procedure (1)");

         exitexception.finish(ptask);
         
      }
      catch (::exception& exception)
      {

         _ERROR(ptask, "Exception reached task procedure : " << exception);

      }
      catch(...)
      {

         _ERROR(ptask, "Exception reached task procedure (...)");

      }


      clear_message_queue(ptask->m_itask);

      ptask->set_flag(e_flag_task_terminated);

      ptask->destroy();

      ///ptask->release();


#if OBJECT_REFERENCE_COUNT_DEBUG

      if (ptask->m_countReference > 1)
      {

         __check_pending_releases(ptask);

      }

#endif

      try
      {

         ::pointer<::object>pparentTask = ptask->m_pobjectParentTask;

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

               pparentTask->erase_task_and_set_task_new_parent(ptask, nullptr);

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      ::task_release(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(ptask, ""));

   }
   catch (...)
   {

   }

   return 0;

}


bool task::is_task_registered() const
{
   
   auto pcontext = m_pcontext;

   return pcontext->acmesystem()->get_task_id(this) != 0;

}


void task::register_task()
{

   auto pcontext = m_pcontext;

   pcontext->acmesystem()->set_task(m_itask, this);

}


void task::unregister_task()
{

   auto pcontext = m_pcontext;

   pcontext->acmesystem()->unset_task(m_itask, this);

}


::locale * task::locale()
{
   
   return m_plocale;
   
}


void task::post_procedure(const ::procedure & procedure)
{

   if (!procedure)
   {

      return;

   }

   synchronous_lock synchronouslock(this->synchronization());

   m_procedurea.add(procedure);

   kick_idle();

}


void task::run_posted_procedures()
{

   synchronous_lock synchronouslock(this->synchronization());

   if (m_procedurea.has_element())
   {

      do
      {

         auto procedure = m_procedurea.pick_first();

         synchronouslock.unlock();

         /*auto estatus =*/ procedure();

         synchronouslock.lock();

      } while (m_procedurea.has_element());


      //return ::success;

   }

   //return ::success_none;

}


//void task::add_notify(::particle * pparticle)
//{
//
//   synchronous_lock synchronouslock(this->synchronization());
//
//   notify_array().add_item(pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);
//
//}
//
//
//void task::erase_notify(::particle * pparticle)
//{
//
//   synchronous_lock synchronouslock(this->synchronization());
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


void task::task_caller_on_init()
{

   //return ::success;

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
   else if (__type_name(this).case_insensitive_ends("out"))
   {

      output_debug_string("synth_thread thread::out");

   }

   if(m_procedure)
   {

      if(m_procedure != this)
      {

         m_procedure->init_task();

      }

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

   //synchronous_lock synchronouslock(this->synchronization());

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


//void task::do_task()
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
//void task::on_task()
//{
//
//   //::e_status estatus = ::success;
//
//   //while (!m_bSetFinish)
//   //{
//
//   //   ::particle * pparticle;
//
//   //   {
//
//   //      synchronous_lock synchronouslock(this->synchronization());
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
//   //      m_atom = __type_name(pelement);
//
//   //      task_set_name(m_atom);
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
   
   throw ::interface_only("tasks don't have message queue, threads do");

   return true;

}


bool task::defer_pump_message()
{

   throw ::interface_only("tasks don't have message queue, threads do");

   return false;

}


bool task::has_message() const
{

   throw ::interface_only("tasks don't have message queue, threads do");

   return false;

}


//void task::branch(
//   ::particle * pparticle,
//   ::enum_priority epriority,
//   u32 nStackSize,
//   u32 uCreateFlags ARG_SEC_ATTRS)
//{
//
//   m_pelement = pelement;
//
//   m_atom = __type_name(pelement);
//
//   return branch(epriority, nStackSize, uCreateFlags ADD_PARAM_SEC_ATTRS);
//
//}


::pointer<::task>task::branch(const ::create_task_attributes & createtaskattributes)
{

   if (m_atom.is_empty())
   {

      if (m_procedure)
      {

         m_atom = __type_name(m_procedure);

      }
      else
      {

         m_atom = __type_name(*this);

      }

   }

   if (m_atom.is_empty() || m_atom == "task" || m_atom == "thread")
   {

      throw ::exception(error_bad_argument);

      ///return ::error_failed;

   }

//   if (::is_null(m_pelement))
//   {
//
//      m_pelement = this;
//
//   }

#ifdef __DEBUG

   string strId = m_atom;

   if (strId.case_insensitive_contains("forking_thread"))
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

      zero(sz);

      engine_symbol(sz, sizeof(sz), &dwDisplacement, uia[5]);

      u32 uiLine = 0;

      {
         critical_section_lock csl(&::exception_engine().m_criticalsection);

         engine_fileline(uia[5], 0, 0, &uiLine, nullptr);

      }

      strId = string(sz) + "(" + as_string(uiLine) + ") :: forking_thread";

#endif

#endif

   }

   m_pszDebug = strdup(strId.c_str());

#endif

   /*auto estatus =*/ task_caller_on_init();

   //if (!estatus)
   //{

   //   return estatus;

   //}

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

   set_flag(e_flag_task_started);

   if (::is_null(m_pobjectParentTask))
   {

      auto pobjectParentTask = ::get_task();

      if (::is_null(pobjectParentTask))
      {

         pobjectParentTask = m_pcontext;

      }

      if (::is_null(pobjectParentTask))
      {

         pobjectParentTask = m_pcontext;

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

         throw ::exception(error_invalid_usage);

      }

   }

#ifdef WINDOWS

   DWORD dwThread = 0;

   m_htask = ::CreateThread(
      (LPSECURITY_ATTRIBUTES)(createtaskattributes.m_psecurityattributes ? createtaskattributes.m_psecurityattributes->get_os_security_attributes() : nullptr),
      createtaskattributes.m_uStackSize, 
      (LPTHREAD_START_ROUTINE) & ::task::s_os_task, 
      (LPVOID)(task *)this,
      createtaskattributes.m_uCreateFlags,
      &dwThread);

   m_itask = dwThread;

#else

   pthread_attr_t taskAttr;

   pthread_attr_init(&taskAttr);

   if (createtaskattributes.m_uStackSize > 0)
   {

      pthread_attr_setstacksize(&taskAttr, createtaskattributes.m_uStackSize); // Set the stack size of the task

   }

   if(!m_bJoinable)
   {
      
      pthread_attr_setdetachstate(&taskAttr, PTHREAD_CREATE_DETACHED); // Set task to detached state. No need for pthread_join
      
   }

   pthread_create(
      (pthread_t *) &m_htask,
      &taskAttr,
      &task::s_os_task,
      this);

#endif

   if (!m_htask)
   {

      m_bIsRunning = false;

      throw ::exception(error_wrong_state);

      //return ::error_failed;

   }

   //return ::success;
   return this;

}


::pointer<::task>task::branch_synchronously(const ::create_task_attributes & createtaskattributes)
{

   clear_finishing_flag();

   ENSURE(m_htask == (htask_t) nullptr);

   //if(m_atom.is_empty())
   //{

   //   m_atom = __type_name(this);

   //}

//#ifdef __DEBUG
//
//   string strId = m_atom;
//
//   if (strId.case_insensitive_contains("forking_thread"))
//   {
//
//#if 0
//
//#ifdef WINDOWS_DESKTOP
//
//      ::exception_engine().reset();
//
//      OS_DWORD                dwDisplacement;
//
//      OS_DWORD                uia[4096];
//
//      dwDisplacement = 0;
//
//      ::u32 maxframes = sizeof(uia) / sizeof(uia[0]);
//
//      ULONG BackTraceHash;
//
//      int iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID*>(&uia), &BackTraceHash);
//
//      char sz[1024];
//
//      zero(sz);
//
//      engine_symbol(sz, sizeof(sz), &dwDisplacement, uia[5]);
//
//      u32 uiLine = 0;
//
//      {
//         critical_section_lock csl(&::exception_engine().m_criticalsection);
//
//         engine_fileline(uia[5], 0, 0, &uiLine, nullptr);
//
//      }
//
//      strId =  string(sz) + "(" + as_string(uiLine) + ") :: forking_thread";
//
//#endif
//
//#endif
//
//   }
//
//   m_pszDebug = strdup(strId);
//
//#endif
//
   //auto pparticle = this;

   //if (::is_set(pparticle) && pparticle != this)
   //{

   //   pparticle->add_composite(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

   //}

   //if (bSynchInitialization)
   {

      m_peventInitialization = __new(manual_reset_event());

   }

   //auto estatus = branch(epriority, nStackSize, uiCreateFlags);

   branch(createtaskattributes);

   if (m_htask == 0)
   {

      //if (::is_set(this))
      //{

      //   this->release_reference(this);

      //}

      decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

      throw ::exception(error_resource);

   }

#ifndef WINDOWS

   if (pthread_equal((pthread_t)m_htask, (pthread_t)m_itask))
   {

      INFORMATION("create_thread success");

   }

#endif

   if (m_peventInitialization)
   {

      m_peventInitialization->wait();

      ::e_status estatus = m_estatus;

      if (failed(estatus))
      {

         ::e_status estatusExit = m_estatus;

         throw ::exception(estatusExit);

      }

   }

//   if (m_atom.is_empty())
//   {
//
//      if (m_pelement)
//      {
//
//         m_atom = __type_name(m_pelement);
//
//      }
//      else
//      {
//
//         m_atom = __type_name(this);
//
//      }
//
//   }
//
//   if (m_atom.is_empty() || m_atom == "task" || m_atom == "thread")
//   {
//
//      throw ::exception(error_bad_argument);
//
//      ///return ::error_failed;
//
//   }
//
//   //   if (::is_null(m_pelement))
//   //   {
//   //
//   //      m_pelement = this;
//   //
//   //   }
//
//#ifdef __DEBUG
//
//   string strId = m_atom;
//
//   if (strId.case_insensitive_contains("forking_thread"))
//   {
//
//#if 0
//
//#ifdef WINDOWS_DESKTOP
//
//      ::exception_engine().reset();
//
//      OS_DWORD                dwDisplacement;
//
//      OS_DWORD                uia[4096];
//
//      dwDisplacement = 0;
//
//      ::u32 maxframes = sizeof(uia) / sizeof(uia[0]);
//
//      ULONG BackTraceHash;
//
//      int iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID *>(&uia), &BackTraceHash);
//
//      char sz[1024];
//
//      zero(sz);
//
//      engine_symbol(sz, sizeof(sz), &dwDisplacement, uia[5]);
//
//      u32 uiLine = 0;
//
//      {
//         critical_section_lock csl(&::exception_engine().m_criticalsection);
//
//         engine_fileline(uia[5], 0, 0, &uiLine, nullptr);
//
//      }
//
//      strId = string(sz) + "(" + as_string(uiLine) + ") :: forking_thread";
//
//#endif
//
//#endif
//
//   }
//
//   m_pszDebug = strdup(strId);
//
//#endif
//
//   /*auto estatus =*/ task_caller_on_init();
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   //if (m_pobjectParent && m_bIsPredicate)
//   //{
//
//   //   //auto pthreadParent = calc_parent_thread();
//
//   //   m_pobjectParent->task_add(this);
//
//
//   //   if (pthreadParent)
//   //   {
//
//   //
//
//   //   }
//
//   //}
//
//   // __task_procedure() should release this (pelement)
//   //increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);
//
//   m_bIsRunning = true;
//
//   set(e_flag_task_started);
//
//   if (::is_null(m_pobjectParentTask))
//   {
//
//      auto pobjectParentTask = ::get_task();
//
//      if (::is_null(pobjectParentTask))
//      {
//
//         pobjectParentTask = m_pcontext;
//
//      }
//
//      if (::is_null(pobjectParentTask))
//      {
//
//         pobjectParentTask = acmesystem();
//
//      }
//
//      if (pobjectParentTask)
//      {
//
//         if (pobjectParentTask != this)
//         {
//
//            pobjectParentTask->add_task(this);
//
//         }
//
//      }
//      else
//      {
//
//         throw ::exception(error_invalid_usage);
//
//      }
//
//   }
//
//#ifdef WINDOWS
//
//   DWORD dwThread = 0;
//
//   m_htask = ::CreateThread((LPSECURITY_ATTRIBUTES)PARAM_SEC_ATTRS, nStackSize, (LPTHREAD_START_ROUTINE) & ::task::s_os_task, (LPVOID)(task *)this, uCreateFlags, &dwThread);
//
//   m_itask = dwThread;
//
//#else
//
//   pthread_attr_t taskAttr;
//
//   pthread_attr_init(&taskAttr);
//
//   if (nStackSize > 0)
//   {
//
//      pthread_attr_setstacksize(&taskAttr, nStackSize); // Set the stack size of the task
//
//   }
//
//   if (!m_bJoinable)
//   {
//
//      pthread_attr_setdetachstate(&taskAttr, PTHREAD_CREATE_DETACHED); // Set task to detached state. No need for pthread_join
//
//   }
//
//   pthread_create(
//      (pthread_t *)&m_htask,
//      &taskAttr,
//      &task::s_os_task,
//      this);
//
//#endif
//
//   if (!m_htask)
//   {
//
//      m_bIsRunning = false;
//
//      throw ::exception(error_wrong_state);
//
//      //return ::error_failed;
//
//   }
//
//   //return ::success;

   return this;

}


bool task::task_sleep(const class time & timeWait)
{
   
   auto waitStart = ::time::now();
   
   while(task_get_run())
   {

      auto waitStep = minimum(timeWait - waitStart.elapsed(), 100_ms);

      if (waitStep <= 0_s)
      {

         return true;

      }
      
      ::preempt(waitStep);
      
   }
   
   return false;

}

//void task::branch(::particle * pparticle, ::enum_priority epriority, ::u32 nStackSize, u32 uCreateFlags ARG_SEC_ATTRS)
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
//bool task::task_set_name(const ::scoped_string & scopedstrThreadName)
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

   return ::get_current_itask() == m_itask;

}




CLASS_DECL_ACME bool __task_sleep(task* task)
{

   while (task->task_get_run())
   {

      preempt(100_ms);

   }

   return false;

}


CLASS_DECL_ACME bool __task_sleep(task* ptask, const class time & timeWait)
{

   if (timeWait < 1000_ms)
   {

      if (!ptask->task_get_run())
      {

         return false;

      }

      preempt(timeWait);

      return ptask->task_get_run();

   }

   try
   {

      ::pointer<manual_reset_event>spev;

      {

         synchronous_lock synchronouslock(ptask->synchronization());

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

      ptask->m_pevSleep->wait(timeWait);

      if (!ptask->task_get_run())
      {

         return false;

      }

   }
   catch (...)
   {

   }

   return ptask->task_get_run();

}


CLASS_DECL_ACME bool __task_sleep(::task* ptask, ::particle * pparticle)
{

   try
   {

      while (ptask->task_get_run())
      {

         pparticle->_wait(100_ms);

      }

   }
   catch (...)
   {

   }

   return ptask->task_get_run();

}


CLASS_DECL_ACME bool __task_sleep(task* ptask, const class time & timeWait, ::particle * pparticle)
{

   if (timeWait < 1000_ms)
   {

      if (!ptask->task_get_run())
      {

         return false;

      }

      pparticle->_wait(timeWait);

      return ptask->task_get_run();

   }

   auto iTenths = (::i32) (timeWait.integral_millisecond() / 100);

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


//CLASS_DECL_ACME bool task_sleep(const class time & time)
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
//         if (__os(::time) == U32_INFINITE_TIMEOUT)
//         {
//
//         }
//         else
//         {
//
//            ::preempt(::time);
//
//         }
//
//      }
//      else
//      {
//
//         if (__os(::time) == U32_INFINITE_TIMEOUT)
//         {
//
//            return psync->lock();
//
//         }
//         else
//         {
//
//            return psync->lock(::time);
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
//      if (__os(::time) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __task_sleep(ptask);
//
//      }
//      else
//      {
//
//         return __task_sleep(ptask, ::time);
//
//      }
//
//   }
//   else
//   {
//
//      if (__os(::time) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __task_sleep(ptask, psync);
//
//      }
//      else
//      {
//
//         return __task_sleep(ptask, ::time, psync);
//
//      }
//
//   }
//}
//




CLASS_DECL_ACME bool task_sleep(const class time & timeWait)
{
   
   auto ptask = ::get_task();
   
   if(::is_null(ptask))
   {
    
      ::preempt(timeWait);
      
      return true;
      
   }
   
   if(!ptask->task_sleep(timeWait))
   {
      
      return false;
      
   }
      
   return true;
   
}






#include "framework.h"


CLASS_DECL_ACME bool __simple_task_sleep()
{

   while (task_get_run())
   {

      preempt(300_ms);

   }

   return false;

}


//CLASS_DECL_ACME bool __simple_task_sleep(class ::wait wait)
//{
//
//   auto waitStart = class ::time::now();
//
//   while (waitStart > 300)
//   {
//
//      if (!task_get_run())
//      {
//
//         return false;
//
//      }
//
//      preempt(300_ms);
//
//      iMillisecond -= 300;
//
//   }
//
//   if (!task_get_run())
//   {
//
//      return false;
//
//   }
//
//   preempt((::time)iMillisecond);
//
//   return ::task_get_run();
//
//}
//
//
//CLASS_DECL_ACME bool __simple_task_sleep(synchronization* psync)
//{
//
//   while (task_get_run())
//   {
//
//      if (psync->wait(300_ms).succeeded())
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//CLASS_DECL_ACME bool __simple_task_sleep(class ::wait wait, synchronization* psync)
//{
//
//   auto iMillisecond = wait.m_iMillisecond;
//
//   while (iMillisecond > 300)
//   {
//
//      if (!task_get_run())
//      {
//
//         return false;
//
//      }
//
//      if (psync->wait(300_ms).succeeded())
//      {
//
//         return true;
//
//      }
//
//      iMillisecond -= 300;
//
//   }
//
//   if (!task_get_run())
//   {
//
//      return false;
//
//   }
//
//   if (psync->wait(::time(iMillisecond)).succeeded())
//   {
//
//      return true;
//
//   }
//
//   return ::task_get_run();
//
//}
//

//CLASS_DECL_ACME bool acme_task_sleep(::time ::time, synchronization* psync)
//{
//
//   if (::is_null(psync))
//   {
//
//      if (__os(::time) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __simple_task_sleep();
//
//      }
//      else
//      {
//
//         return __simple_task_sleep(::time);
//
//      }
//
//   }
//   else
//   {
//
//      if (__os(::time) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __simple_task_sleep(psync);
//
//      }
//      else
//      {
//
//         return __simple_task_sleep(::time, psync);
//
//      }
//
//   }
//}


//PFN_task_sleep g_pfnThreadSleep = acme_task_sleep;

//CLASS_DECL_ACME bool tas_sleep(::time ::time, synchronization* psync)
//{
//
//   return g_pfnThreadSleep(::time, psync);
//
//}

//
//CLASS_DECL_ACME void set_task_sleep(PFN_task_sleep pfnThreadSleep)
//{
//
//   g_pfnThreadSleep = pfnThreadSleep;
//
//}
//


CLASS_DECL_ACME void set_main_user_itask(itask_t itask);


CLASS_DECL_ACME void set_main_user_htask(htask_t htask);


CLASS_DECL_ACME itask_t get_main_user_itask();


CLASS_DECL_ACME void set_main_user_thread()
{

   set_main_user_itask(get_current_itask());

   set_main_user_htask(get_current_htask());

}


CLASS_DECL_ACME bool is_main_thread()
{

   return get_current_itask() == get_main_user_itask();

}


CLASS_DECL_ACME bool predicate_Sleep(int iTime, ::function < bool(void) > functionOkToSleep)
{

   if (iTime < 100)
   {

      preempt(100_ms);

   }
   else
   {

      iTime += 99;

      iTime /= 100;

      for (index i = 0; i < iTime; i++)
      {

         preempt(100_ms);

         if (!::task_get_run() || !functionOkToSleep())
         {

            break;

         }

      }

   }

   return ::task_get_run();

}






void preempt()
{

   if (!::task_get_run())
   {

      auto ptask = ::get_task();

      throw ::exit_exception(error_exit_thread, ptask);

   }

}


tracer trace_log_information() { return ::get_task()->trace_log_information(); }
tracer trace_log_warning() { return ::get_task()->trace_log_warning(); }
tracer trace_log_error() { return ::get_task()->trace_log_error(); }
tracer trace_log_fatal() { return ::get_task()->trace_log_fatal(); }






//thread_local thread_local_particle * task_guard::t_pthreadlocalparticleList = nullptr;
//
//
//
//thread_local_particle::thread_local_particle()
//{
//
//   m_pthreadlocalparticleNext = task_guard::t_pthreadlocalparticleList;
//
//
//   task_guard::t_pthreadlocalparticleList = this;
//
//
//}
//
//
//thread_local_particle::~thread_local_particle()
//{
//
//   //// todo removed
//
//}


task_guard::task_guard()
{

   on_init_thread();

}


task_guard::~task_guard()
{

   //auto p = t_pthreadlocalparticleList;

   //while(p)
   //{

   //   auto pNext = t_pthreadlocalparticleList->m_pthreadlocalparticleNext;

   //   ::release(p);

   //   p = pNext;

   //}

   on_term_thread();

}


//::factory::factory_pointer & get_system_factory()
//{
//
//   return ::acme::get()->m_psubsystem->m_pfactory;
//
//}



