#include "framework.h"
#include "task.h"
#include "manual_reset_event.h"
#include "acme/platform/scoped_restore.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/translator.h"
#include "acme/handler/request.h"
#include "acme/nano/nano.h"
#include "acme/windowing/window.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task_message_queue.h"
#include "acme/exception/_text_stream.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/parallelization.h"
///#include "acme/windowing/window_base.h"
#include "acme/windowing/windowing.h"


#ifdef WINDOWS


#include "acme/_operating_system.h"


CLASS_DECL_ACME HANDLE duplicate_handle(HANDLE h);

#elif defined(__BSD__)
#include <errno.h>


#endif



extern bool g_bIntermediateThreadReferencingDebugging;


CLASS_DECL_ACME void _do_tasks();


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


//CLASS_DECL_ACME void aaa_clear_message_queue(itask_t idthread);


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

   m_bKeepRunningPostedProcedures = false;

}


#undef TASK_DESTRUCTOR_REPORTING


task::~task()
{

#if defined(_DEBUG) && defined(TASK_DESTRUCTOR_REPORTING)

   auto strThreadName = ::task_get_name();
   auto itask = ::current_itask();

   informationf("Task destructor : " + strThreadName + " : (" + ::as_string(itask) + ")\n");

#endif

}



void task::on_initialize_particle()
{

   /*auto estatus =*/ ::object::on_initialize_particle();

   //m_pprintingformat);

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

   auto itaskCurrent = ::current_itask();

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

   auto prequestHold =  __retain prequest;

   post([this, prequestHold]
      {

         request(prequestHold);

      }
   );

}


bool task::task_set_name(const ::scoped_string & scopedstrTaskName)
{
   
   if(::current_itask() == m_itask)
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


//bool task::os_on_init_task()
//{
//
//   if (!::os_on_init_thread())
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
//
//void task::os_on_term_task()
//{
//
//   ::os_on_term_thread();
//
//}


void task::main()
{

   task_osinit();



   __task_init();

   if(defer_implement(application()))
   {

      return;

   }

   if (m_procedure && m_procedure != this)
   {

      run_posted_procedures();

      m_procedure();

      run_posted_procedures();

      //// ITCN?   Is This Code Needed?

      //auto windowa = system()->acme_windowing()->m_windowa;

      ////while (::acme::windowing::window::nanowindowimplementationa().has_element())
      //{

      //   //for (auto & pimplementation : ::acme::windowing::window::nanowindowimplementationa())
      //   for (auto & pwindowbase : windowa)
      //   {

      //      //pwindowbase->implementation_message_loop_step();

      //   }

      //}

      //// ITCN?-END   Is This Code Needed? -end

   }

   on_pre_run_task();

   try
   {

      run();

   }
   catch(::exception & exception)
   {

      send(__initialize_new ::message_box(exception, application()->m_strAppId, exception.m_strDetails));

   }
   catch(...)
   {

   }

  __task_term();

}


void task::run()
{

   at_end_of_scope
   {

      m_eflagElement -= e_flag_running;

   };

   m_eflagElement += e_flag_running;

   try
   {

      run_posted_procedures();

      if (defer_implement(m_papplication))
      {

         return;

      }

      if(m_bKeepRunningPostedProcedures)
      {

         while(task_get_run())
         {

            run_posted_procedures();

            preempt(100_ms);

         }

      }

   }
   catch(::exception & exception)
   {

      string strMoreDetails;

      strMoreDetails = "task::run";

      send(__initialize_new ::message_box(exception, strMoreDetails));

   }


}


void task::stop_task()
{

   if (!m_htask || !m_itask)
   {

      return;

   }

   manual_reset_event ev;

   ::procedure procedure = [&ev]()
      {

         ev.set_event();

      };

   m_procedureTaskEnded = procedure;

   //__defer_construct_new(m_peventFinished2);

   //auto peventFinished = m_peventFinished2;

   set_finish();

   while (true)
   {

      auto bWaitFinished = ev._wait(1_s);

      if (bWaitFinished)
      {

         break;

      }

      auto bTasksFinished = check_tasks_finished();

      if (!bTasksFinished)
      {
         
         informationf("tasks still not finished for task : %s", m_strTaskName.c_str());

      }

   }

   //return estatus;

}


void task::destroy()
{

   if (m_peventFinished2)
   {

      m_peventFinished2->set_event();

   }

   ::object::destroy();

   ::data::property_container::destroy();

#ifdef WINDOWS

   if (m_pexceptiontranslator)
   {

      m_pexceptiontranslator->detach();

      m_pexceptiontranslator.release();

   }

#endif

   m_peventInitialization.release();

   m_particleaHold.clear();

   m_procedure.m_pbase.release();

   m_pevSleep.release();

   m_pcounter.release();

   m_ptask.release();

   m_procedureNext.m_pbase.release();

   m_procedurea.clear();

   m_plocale.release();

   m_peventFinished2.release();

}


void task::__task_init()
{

   __check_refdbg

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

   __check_refdbg

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

   ::procedure procedureTaskEnded;

   {

      ::pointer < ::task > ptask((::task *)p);

      ptask->_os_task(procedureTaskEnded);

   }

   if (procedureTaskEnded)
   {

      procedureTaskEnded();

   }

   return 0;

}


void task::_os_task(::procedure & procedureTaskEnded)
{

   ::pointer < manual_reset_event > pmanualresethappeningFinished;

   try
   {

      __check_refdbg

      os_task_init_term ostaskinitterm;

      __check_refdbg

      ::set_task(this);

      __check_refdbg

//      ptask->_os_task();

#if 0

      information() << "s_os_task current_itask : " << current_itask();

#endif

      //ptask->release(REFERENCING_DEBUGGING_P_FUNCTION_LINE(ptask));

#if defined(WINDOWS)

      {

         REFDBG_THIS(this);

         __defer_construct(m_pexceptiontranslator);

         m_pexceptiontranslator->attach();

      }

#endif

      try
      {

         main();

      }
      catch (::exit_exception & exitexception)
      {

         error() << "Exit Exception reached task procedure (1)";

         exitexception.finish(this);
         
      }
      catch (::exception& exception)
      {

         error() << "Exception reached task procedure : " << exception;

      }
      catch(...)
      {

         error() << "Exception reached task procedure (...)";

      }

      auto pacme = ::acme::get();

      if(pacme)
      {

         auto ptaskmessagequeue = pacme->m_ptaskmessagequeue;

         if(ptaskmessagequeue)
         {

            ptaskmessagequeue->clear_message_queue(m_itask);

         }

      }

      ///release();

      //::task_release(REFERENCING_DEBUGGING_P_FUNCTION_FILE_LINE(ptask));

#if REFERENCING_DEBUGGING

      if (g_bIntermediateThreadReferencingDebugging)
      {

         if (m_countReference > 1)
         {

            check_pending_releases();

         }

      }

#endif

      try
      {

         ::pointer<::object>pparentTask = m_pobjectParentTask;

         if (::is_set(pparentTask))
         {

            try
            {

               pparentTask->transfer_tasks_from(this);

            }
            catch (...)
            {

            }

            try
            {

               pparentTask->erase_task_and_set_task_new_parent(this, nullptr);

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      destroy();

   }
   catch (...)
   {

   }

   m_htask = nullptr;

   m_itask = 0;

   ::task_release();

   procedureTaskEnded = ::transfer(m_procedureTaskEnded);

}


bool task::is_task_registered() const
{
   
   return ::platform::get()->get_task_id(this) != 0;

}


void task::register_task()
{

   ::platform::get()->set_task(m_itask, this);

}


void task::unregister_task()
{

   ::platform::get()->unset_task(m_itask, this);

}


::locale * task::locale()
{
   
   return m_plocale;
   
}


void task::_post(const ::procedure & procedure)
{

   if (!procedure)
   {

      return;

   }

   //if (is_current_task())
   //{

   //   procedure();

   //   return;

   //}

   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_procedurea.add(procedure);

   }

   kick_idle();

}


//void task::_post(::subparticle * p)
//{
//
//   if (!p)
//   {
//
//      return;
//
//   }
//
//   //if (is_current_task())
//   //{
//
//   //   procedure();
//
//   //   return;
//
//   //}
//
//   {
//
//      _synchronous_lock synchronouslock(this->synchronization());
//
//      m_procedurea.add([p]()
//         {
//
//            p->call_run();
//
//         });
//
//   }
//
//   kick_idle();
//
//}

 
void task::_send(const ::procedure & procedure)
{

   if (is_current_task())
   {

      procedure();

      return;

   }

   auto pevent = __create_new < manual_reset_event>();

   post([procedure, pevent]()
      {

         procedure();

         pevent->set_event();

         });

   pevent->wait(procedure.timeout());

}


void task::run_posted_procedures()
{

   _synchronous_lock synchronouslock(this->synchronization());

   if (m_procedurea.has_element())
   {

      do
      {

         //information() << "run_posted_procedures reference_count before_pick : " << (::iptr) m_procedurea.m_begin[0].m_pbase->m_countReference;

         auto procedure = ::transfer(m_procedurea.pick_first());

         //information() << "run_posted_procedures reference_count : " << (::iptr) procedure->m_countReference;

         synchronouslock.unlock();

         /*auto estatus =*/ procedure();

         synchronouslock._lock();

      } while (m_procedurea.has_element());


      //return ::success;

   }

   //return ::success_none;

}


//void task::add_notify(::particle * pparticle)
//{
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   notify_array().add_item(pelement REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);
//
//}
//
//
//void task::erase_notify(::particle * pparticle)
//{
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   if (m_pnotifya)
//   {
//
//      m_pnotifya->erase_item(pelement REFERENCING_DEBUGGING_COMMA_THIS);
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

      //::task_set_name(::type(this).name());

      strTaskName = ::type(this).name();

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

   if (::type(this).name().contains("synth_thread"))
   {

      informationf("synth_thread thread::thread_proc");

   }
   else if (::type(this).name().case_insensitive_ends("out"))
   {

      informationf("synth_thread thread::out");

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

   //_synchronous_lock synchronouslock(this->synchronization());

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
//   //      _synchronous_lock synchronouslock(this->synchronization());
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
//   //      m_atom = ::type(pelement).name();
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


bool task::do_tasks()
{
   
   //throw ::interface_only("tasks don't have message queue, threads do (1)");

   _do_tasks();

   if (platform()->m_bConsole || (m_eflagElement & e_flag_running))
   {

      run_posted_procedures();

   }

   return true;

}


bool task::defer_pump_message()
{

   throw ::interface_only("tasks don't have message queue, threads do (2)");

   return false;

}


bool task::has_message() const
{

   throw ::interface_only("tasks don't have message queue, threads do (3)");

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
//   m_atom = ::type(pelement).name();
//
//   return branch(epriority, nStackSize, uCreateFlags ADD_PARAM_SEC_ATTRS);
//
//}


::pointer<::task>task::branch(enum_parallelization eparallelization, const ::create_task_attributes & createtaskattributes)
{

   if(eparallelization == e_parallelization_synchronous)
   {

      return branch_synchronously(createtaskattributes);

   }

   if (m_atom.is_empty())
   {

      if (m_procedure)
      {

         m_atom = ::type(m_procedure).name();

      }
      else
      {

         m_atom = ::type(this).name();

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

   string strId = m_atom.as_string();

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

   //m_pszDebug = strdup(strId.c_str());

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
   //increment_reference_count(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);

   m_bIsRunning = true;

   set_flag(e_flag_task_started);

   if (::is_null(m_pobjectParentTask))
   {

      auto pobjectParentTask = ::get_task();

      if (::is_null(pobjectParentTask))
      {

         pobjectParentTask = m_papplication;

      }

      if (::is_null(pobjectParentTask))
      {

         pobjectParentTask = m_papplication;

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

   int iError = pthread_create(
      (pthread_t *) &m_htask,
      &taskAttr,
      &task::s_os_task,
      this);


   if(iError != 0)
   {

      if(iError == EAGAIN)
      {
         // EAGAIN Insufficient resources to create another thread.
         //
         // EAGAIN A system-imposed limit on the number of threads was
         //        encountered.  There are a number of limits that may
         //        trigger this error: the RLIMIT_NPROC soft resource limit
         //        (set via setrlimit(2)), which limits the number of
         //        processes and threads for a real user ID, was reached; the
         //        kernel's system-wide limit on the number of processes and
         //        threads, /proc/sys/kernel/threads-max, was reached (see
         //        proc(5)); or the maximum number of PIDs,
         //        /proc/sys/kernel/pid_max, was reached (see proc(5)).

         throw ::exception(error_resource);
      }
      else if(iError == EINVAL)
      {
         //EINVAL Invalid settings in attr.
         throw ::exception(error_bad_argument);

      }
      else if(iError == EPERM)
      {
         //EPERM  No permission to set the scheduling policy and parameters
         //     specified in attr.
         throw ::exception(error_failed);
      }

   }

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

   //   m_atom = ::type(this).name();

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

   //   pparticle->add_composite(this REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);

   //}

   //if (bSynchInitialization)
   {

      m_peventInitialization = __allocate manual_reset_event();

   }

   //auto estatus = branch(epriority, nStackSize, uiCreateFlags);

   branch(e_parallelization_asynchronous, createtaskattributes);

   if (m_htask == 0)
   {

      //if (::is_set(this))
      //{

      //   this->release_reference(this);

      //}

      decrement_reference_count();

      throw ::exception(error_resource);

   }

#ifndef WINDOWS

   if (pthread_equal((pthread_t)m_htask, (pthread_t)m_itask))
   {

      information() << "create_thread success";

   }

#endif

   if (m_peventInitialization)
   {

      {

         auto peventProtectionWhileWaiting = m_peventInitialization;

         peventProtectionWhileWaiting->wait();

      }

      ::e_status estatus = m_estatus;

      if (estatus.failed())
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
//         m_atom = ::type(m_pelement).name();
//
//      }
//      else
//      {
//
//         m_atom = ::type(this).name();
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
//   //increment_reference_count(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);
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
//         pobjectParentTask = m_papplication;
//
//      }
//
//      if (::is_null(pobjectParentTask))
//      {
//
//         pobjectParentTask = system();
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
//   auto ptask = __allocate task();
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


void task::set_current_handles()
{

#ifdef WINDOWS_DESKTOP

   m_htask = duplicate_handle(::current_htask());

#else

   m_htask = ::current_htask();

#endif

   m_itask = ::current_itask();

}


void task::kick_idle()
{


}


bool task::is_branch_current() const
{

   return ::current_itask() == m_itask;

}



void task::synchronous_procedure(bool bAtAnotherThread, const procedure & procedure, const class ::time & timeTimeout)
{

   if (!bAtAnotherThread)
   {

      procedure();

      return;

   }

   auto pmanualresetevent = __create_new < manual_reset_event >();

   post([this, procedure, pmanualresetevent]()
      {

         procedure();

         pmanualresetevent->SetEvent();

      });

   auto timeout = timeTimeout;

   if (timeout.is_null())
   {

      timeout = get_default_run_timeout();

   }

   auto estatus = pmanualresetevent->wait(timeout);

   if (estatus.failed())
   {

      throw ::exception(estatus);

   }

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

         _synchronous_lock synchronouslock(ptask->synchronization());

         if (ptask->m_pevSleep.is_null())
         {

            ptask->m_pevSleep = __allocate manual_reset_event();

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


//CLASS_DECL_ACME void set_main_itask(itask_t itask);
//
//
//CLASS_DECL_ACME void set_main_htask(htask_t htask);


//CLASS_DECL_ACME itask_t main_user_itask();


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

      for (::collection::index i = 0; i < iTime; i++)
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


//trace_statement information() { return ::get_task()->information(); }
//trace_statement warning() { return ::get_task()->warning(); }
//trace_statement error() { return ::get_task()->error(); }
//trace_statement fatal() { return ::get_task()->fatal(); }
//





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



//::factory::factory_pointer & get_system_factory()
//{
//
//   return ::system()->m_pplatform->m_pfactory;
//
//}


namespace platform
{

   
   ::collection::index platform::task_index(itask_t itask, bool bAddIfNotInList)
   {

      critical_section_lock sl(&m_criticalsectionTask);

      auto iTaskIndex = m_iaTaskIndex.find_first(itask);

      if (bAddIfNotInList && iTaskIndex < 0)
      {

         iTaskIndex = m_iaTaskIndex.add(itask);

      }

      return iTaskIndex;

   }

}


::collection::index task_index(itask_t itask)
{

   return ::system()->task_index(itask);

}


::collection::index task_index()
{

   return task_index(::current_itask());

}


void do_tasks()
{

   _do_tasks();

   auto ptask = ::get_task();

   if (ptask)
   {

      ptask->do_tasks();

   }

   if (::platform::get()->m_bConsole)
   {

      system()->application()->do_tasks();

      system()->do_tasks();

   }

}





CLASS_DECL_ACME::string get_task_object_name()
{

   return ::type(::get_task()).name();

}

#ifdef _DEBUG

CLASS_DECL_ACME::string get_task_object_debug()
{

   return ::get_task()->m_pszDebug;

}

#endif






static htask_t g_htaskMain = (htask_t) nullptr;

static itask_t g_itaskMain = (itask_t) 0;


CLASS_DECL_ACME void set_main_htask(htask_t htask)
{

   // MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_htaskMain = htask;

}


CLASS_DECL_ACME void set_main_itask(itask_t itask)
{

   //   MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_itaskMain = itask;

}


CLASS_DECL_ACME htask_t main_htask()
{

   return g_htaskMain;

}


CLASS_DECL_ACME itask_t main_itask()
{

   return g_itaskMain;

}


//CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach)
//{
//
//}


CLASS_DECL_ACME void set_main_thread()
{

   set_main_htask(current_htask());

   set_main_itask(current_itask());

}


CLASS_DECL_ACME void set_main_thread(htask_t htask)
{

   set_main_itask(::as_itask(htask));

   set_main_htask(htask);

}


CLASS_DECL_ACME bool is_main_thread()
{

   return current_itask() == main_itask();

}



