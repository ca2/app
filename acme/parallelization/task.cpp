#include "framework.h"
#include "task.h"
#include "waiting_call.h"
#include "manual_reset_happening.h"
#include "wait_for_end_of_sequence.h"
#include "acme/handler/sequence.h"
#include "acme/handler/task_handler.h"
#include "acme/platform/scoped_restore.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/translator.h"
#include "acme/handler/request.h"
#include "acme/nano/nano.h"
#include "acme/user/user/interaction.h"
#include "acme/windowing/window.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/multiple_lock.h"
#include "acme/parallelization/task_message_queue.h"
#include "acme/exception/_text_stream.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/parallelization.h"
///#include "acme/windowing/window_base.h"
#include "acme/windowing/windowing.h"


#ifdef LINUX

int SetThreadAffinityMask(htask h, unsigned int dwThreadAffinityMask);

#endif


#ifdef WINDOWS


#include "acme/_operating_system.h"


CLASS_DECL_ACME ::uptr duplicate_handle(const ::uptr & u);

#elif defined(__BSD__)
#include <errno.h>


#endif




extern bool g_bIntermediateThreadReferencingDebugging;


//CLASS_DECL_ACME void task_iteration(const class ::time & timeTimeout);


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


//CLASS_DECL_ACME void aaa_clear_message_queue(itask idthread);


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);


task::task()
{

   m_timeSample = 1_s;
   //m_bAutoRelease = false;

   m_pfnImplement = nullptr;
   m_iExitCode = 0;
   m_hnTaskFlag = 0;

   m_timeDefaultPostedProcedureTimeout = 500_ms;

   m_bHandlingMessages = false;
   //m_bTaskPending = true;

   //m_bSetFinish = false;
   //m_bTaskTerminated = false;
   //m_bTaskStarted = false;
//   m_bCheckingChildrenTask = false;
   //m_pthread = nullptr;
   m_bMessageThread = false;
#ifdef WINDOWS
   m_bCoInitialize = false;
#endif
   //m_bIsRunning = false;
   m_bIsPredicate = true;

#ifdef PARALLELIZATION_PTHREAD

   m_bJoinable = false;

#endif

   m_htask = nullptr;
   m_itask = nullptr;
   m_taskindex = 0;
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

   /*auto estatus =*/ 
   
   ::object::on_initialize_particle();

   ::handler::handler::on_initialize_particle();

   m_synchronizationaMainLoop.add(new_main_loop_happening());

   update_new_main_loop_happening();

   //m_pprintingformat);

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return ::success;

}


//bool task::has_main_loop_happening()
//{
//
//   if (m_bHandleRequest || m_requestaPosted.has_element())
//   {
//
//     // m_synchronizationaMainLoop.add_item(new_request_posted());
//
//      return true;
//
//   }
//
//   if (m_bHandleProcedure || m_procedurea.has_element())
//   {
//
//      //m_synchronizationaMainLoop.add_item(new_procedure_posted());
//
//      return true;
//
//   }
//
//   if (m_bHandleHappening || m_ehappeninga.has_element())
//   {
//
//      //m_synchronizationaMainLoop.add_item(new_happening());
//
//      return true;
//
//   }
//
//   return false;
//
//}


//::manual_reset_happening * task::new_procedure_posted()
//{
//
//   __defer_construct_new(m_pmanualresethappeningNewProcedurePosted);
//
//   return m_pmanualresethappeningNewProcedurePosted;
//
//}


//::manual_reset_happening* task::new_happening()
//{
//
//   __defer_construct_new(m_pmanualresethappeningHappening);
//
//   return m_pmanualresethappeningHappening;
//
//}


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


::acme::user::interaction * task::get_active_user_interaction()
{

   return m_pacmeuserinteractionActive;

}


void task::set_active_user_interaction(::acme::user::interaction * pacmeuserinteraction)
{

   m_pacmeuserinteractionActive = pacmeuserinteraction;

}




bool task::has_main_loop_happening()
{

   _synchronous_lock synchronouslock(this->synchronization());

   return _has_main_loop_happening_unlocked();

}


bool task::_has_main_loop_happening_unlocked()
{

   return m_requestaPosted.has_element()
      || m_procedurea2.has_element()
      || m_ehappeninga.has_element();

}


void task::add_task(::object * pobjectTask)
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

   //auto itaskCurrent = ::current_itask();

   //return itaskCurrent == m_itask;
   
   auto taskindexCurrent = ::current_task_index();
   
   return taskindexCurrent == m_taskindex;

}


//::object * task::calc_parent_thread()
//{
//
//   return ::get_task();
//
//}


void task::post_request(::request * prequest)
{

   ::handler::handler::post_request(prequest);


   //auto prequestHold =  __retain prequest;

   //post([this, prequestHold]
   //   {

   //      request(prequestHold);

   //   }
   //);

}


bool task::task_set_name(const ::scoped_string & scopedstrTaskName)
{

   m_strTaskName = scopedstrTaskName;

   if (m_strTaskTag.is_empty() && m_strTaskName.has_character())
   {

      m_strTaskTag = m_strTaskName;

   }

   if (m_htask.is_set())
   {

      ::task_set_name(m_htask, m_strTaskName.c_str());

   }
   // //   {
   // //
   // //      return false;
   // //
   // //   }
   // //
   // if (::current_itask() != m_itask)
   // {
   //
   //    throw ::exception(error_wrong_state);
   //
   // }
   //
   // ::task_set_name(scopedstrTaskName);

   return true;

}


bool task::task_get_run() const
{

   if(!has_finishing_flag())
   {

      return true;

   }

   if (m_waitingcallstack.has_element())
   {

      return true;

   }

   if (m_procedurelistHandling.has_element())
   {

      return true;

   }

   if (m_procedurea2.has_element())
   {

      return true;

   }

   if (m_requestaPosted.has_element())
   {

      return true;

   }

   if(((::task *)this)->set_children_to_finish_and_check_them_finished())
   {

      return false;

   }

   return true;

}


bool task::is_ready_to_quit() const
{

   bool bShouldContinue = task_get_run();

   return !bShouldContinue;

}


//bool task::task_active() const
//{
//
//   return m_htask.is_set();
//
//}
//


bool task::is_task_set() const
{

   return has_flag(e_flag_running) && m_htask.is_set();

}


bool task::set_children_to_finish_and_check_them_finished()
{

   set_finishing_flag();

   auto b = ::object::set_children_to_finish_and_check_them_finished();

   update_task_ready_to_quit();

   return b;

}


void task::update_task_ready_to_quit()
{


}


void task::kick_thread()
{

   // return false;

}


//void task::on_pre_run_task()
//{
//
//   //return ::success;
//
//}



void task::set_finish()
{

   set_finishing_flag();

   set_happened(e_happening_finish);

   kick_idle();

}


void task::__priority_and_affinity()
{

   if (m_uThreadAffinityMask != 0)
   {

#if defined(WINDOWS_DESKTOP)

      int_bool bOk = ::SetThreadAffinityMask((HANDLE) m_htask.m_h, (unsigned int)m_uThreadAffinityMask) != 0;

      if (bOk)
      {

         //informationf("successfully set thread affinity mask");

      }
      else
      {

         informationf("failed to set thread affinity mask");

      }

#elif defined(LINUX)

      int_bool bOk = ::SetThreadAffinityMask(m_htask, (unsigned int)m_uThreadAffinityMask) != 0;

      if (bOk)
      {

         //informationf("successfully set thread affinity mask");

      }
      else
      {

         informationf("failed to set thread affinity mask");

      }

#endif

   }

}

//
//void task::__os_initialize()
//{
//
//   //#ifdef WINDOWS_DESKTOP
//   //
//   //   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &m_htask, 0, false, DUPLICATE_SAME_ACCESS);
//   //
//   //#else
//   //
//   //   m_htask = ::current_htask();
//   //
//   //#endif
//   //
//   //   m_uThread = ::current_itask();
//
//   try
//   {
//
//      __priority_and_affinity();
//
//   }
//   catch (...)
//   {
//
//      // affinity isn't critical
//
//   }
//
//   //#ifndef WINDOWS
//   //
//   //   information() << "init_thread : " << ::type(this).name();
//   //
//   //#endif
//
//   //system()->node_thread_initialize(this);
//
//}
//

//void task::__os_finalize()
//{
//
//
//}

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


//void task::on_task_quit()
//{
//
//
//}


//void task::task_osinit()
//{
//
//
//   set_current_handles();
//
//   if (has_finishing_flag())
//   {
//
//      clear_finishing_flag();
//
//   }
//
//
//
//   m_estatus = ::success;
//   __check_refdbg
//      set_task();
//   __check_refdbg
//      //{
//
//      //   auto pthreadParent = ::parallelization::calc_parent(this);
//
//      //   if (pthreadParent)
//      //   {
//
//      //      if (!pthreadParent->task_add(this))
//      //      {
//
//      //         if (pthreadParent->id().case_insensitive_begins("predicate_thread") && id().case_insensitive_begins("predicate_thread"))
//      //         {
//
//      //            pthreadParent->task_erase(this);
//
//      //            pthreadParent = ::parallelization::calc_parent(pthreadParent);
//
//      //            if (!pthreadParent->task_add(this))
//      //            {
//
//      //               return ::error_failed;
//
//      //            }
//
//      //         }
//      //         else
//      //         {
//
//      //            return ::error_failed;
//
//      //         }
//
//      //      }
//
//      //   }
//
//      //}
//
//   {
//
//      __check_refdbg
//      if (::_get_task() != this)
//      {
//         __check_refdbg
//         ::set_task(this);
//         __check_refdbg
//      }
//      __check_refdbg
//      processor_cache_oriented_set_thread_memory_pool(0);
//      // set default handler cache oriented thread memory pool index to 0 ("zero") (The First One)
//
//      //system()->parallelization_initialize();
//
//   }
//
//      //try
//      //{
//      __check_refdbg
//
//      __os_initialize();
//
//   __check_refdbg
//      //}
//      //catch (const ::exception & e)
//      //{
//
//      //   m_estatus = e.m_estatus;
//
//      //   if (succeeded(m_estatus))
//      //   {
//
//      //      m_estatus = error_failed;
//
//      //   }
//
//      //   m_result.add(e);
//
//      //   top_handle_exception(e);
//
//      //}
//      //catch (...)
//      //{
//
//      //   m_estatus = error_failed;
//
//      //   m_result.add(error_failed);
//
//      //}
//
//      //return m_estatus;
//
//}


//void task::task_osterm()
//{
//
//   __os_finalize();
//
//   unset_task();
//
//}


void task::set_task()
{

   auto taskindex = ::current_task_index();

   auto itask = ::current_itask();

   auto htask = ::current_htask();

   m_taskindex = taskindex;

   m_itask = itask;

   m_htask = htask;

   ::set_task(this);


   //SetCurrentHandles();

   //auto atom = ::current_itask();

   //::parallelization::task_register(m_itask, this);

   //task_register();
   __check_refdbg
      //register_task();

   system()->set_task(this);

   __check_refdbg

      // apex commented
      //if (g_axisoninitthread)
      //{

      //   g_axisoninitthread();

      //}

      //   if (!os_on_init_task())
      //   {
      //
      //      m_estatus = error_failed;
      //
      //      return;
      //
      //   }


}


void task::unset_task()
{

   ////   try
   ////   {
   ////
   ////      // apex commented
   ////      //if (g_axisontermthread)
   ////      //{
   ////
   ////      //   g_axisontermthread();
   ////
   ////      //}
   ////
   ////      os_on_term_task();
   ////
   ////   }
   ////   catch (...)
   ////   {
   ////
   ////   }

   //::task * ptask = this;

   ////::parallelization::task_unregister(m_itask, pthread);

   ////unregister_task();

   //unregister_task();

   //auto atom = ::current_itask();

   //::system()->set_task_off(::current_task_index());

   system()->unset_task(this);

   //::set_task(nullptr);

}



void task::main()
{

   //m_estatus = ::success;

   //task_osinit();

   //__task_init();

   call_init_task();

   m_bReadyToAttendRequests = true;

   if (defer_implement(application()))
   {

      return;

   }

   if (m_procedure && m_procedure != this)
   {

      task_iteration();

      m_procedure();

      task_iteration();

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

   //on_pre_run_task();

   try
   {

      run();

   }
   catch (::exception & exception)
   {

      send(__initialize_new::message_box(exception, application()->m_strAppId, exception.m_strDetails));

   }
   catch (...)
   {

   }

   term_task();

   //on_task_quit();

   //__task_term();

   //task_osterm();

}


void task::run_loop()
{

   while (task_get_run())
   {

      task_run(m_timeSample);

   }

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

      task_iteration();

      bool b = m_bKeepRunningPostedProcedures;

      if (defer_implement(m_papplication))
      {

         return;

      }

      if (b)
      {

         run_loop();

      }

   }
   catch (::exception & exception)
   {

      string strMoreDetails;

      strMoreDetails = "task::run";

      send(__initialize_new::message_box(exception,  strMoreDetails));

   }


}


bool task::task_iteration()
{

   if (!is_current_task())
   {

      if (!is_current_task())
      {

         throw ::exception(error_failed);

      }

   }

   if (m_bMessageThread && !m_bHandlingMessages)
   {

      m_bHandlingMessages = true;

      at_end_of_scope
      {

         m_bHandlingMessages = false;

      };

      if (!handle_messages())
      {

         return false;

      }

   }

   handle_next_posted_request();

   handle_posted_procedures();

   return true;

}


bool task::task_run(const class ::time & time)
{

   if (!task_iteration())
   {

      return false;

   }

   class ::time timeStart(now_t{});

   auto remaining = time;

   while (true)
   {

      if(task_wait(remaining))
      {

         while(auto ehappening = pick_happening())
         {

            if(!on_happening(ehappening))
            {

               return false;

            }

         }

         if (!task_iteration())
         {

            return false;

         }

      }

      auto elapsed = timeStart.elapsed();

      if (elapsed >= time)
      {

         return true;

      }

      remaining = time - elapsed;

   }

}


bool task::task_wait(const class ::time & timeRemaining)
{

   ::multiple_lock multiplelock(m_synchronizationaMainLoop);

   auto estatus = multiplelock.lock(timeRemaining, false, QS_ALLINPUT);

   if (estatus == error_wait_timeout)
   {

      return false;

   }
   else if (estatus.failed())
   {

      throw ::exception(error_failed);

   }
   
   return true;

}


bool task::handle_messages()
{

   return true;

}


void task::stop_task()
{

   if (!m_htask || !m_itask)
   {

      return;

   }

   auto taskindexThis = m_taskindex;

   if (!taskindexThis)
   {

      return;

   }

   // manual_reset_happening ev;
   //
   // ::procedure procedure = [&ev]()
   //    {
   //
   //       ev.set_happening();
   //
   //    };
   //
   //m_procedureTaskEnded = procedure;

   //__defer_construct_new(m_phappeningFinished2);

   //auto phappeningFinished = m_phappeningFinished2;

   set_finish();

   while (true)
   {

      // auto bWaitFinished = ev._wait(1_s);
      //
      // if (bWaitFinished)
      // {
      //
      //    break;
      //
      // }

      auto bTasksFinished = set_children_to_finish_and_check_them_finished();

      if (bTasksFinished)
      {

         break;

      }
      else
      {

         informationf("tasks still not finished for task : %s", m_strTaskName.c_str());

      }

      if (!::system()->is_task_set(taskindexThis))
      {

         break;

      }

      preempt(50_ms);

   }

   //return estatus;

}


void task::destroy()
{

   if (m_phappeningFinished2)
   {

      m_phappeningFinished2->set_happening();

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

   m_phappeningInitialization.release();

   m_particleaHold.clear();

   m_procedure.m_pbase.release();

   m_pevSleep.release();

   m_pcounter.release();

   m_ptask.release();

   //m_procedureNext.m_pbase.release();

   m_procedurea2.clear();

   m_procedurelistHandling.clear();

   m_plocale.release();

   m_phappeningFinished2.release();
   
   m_pacmeuserinteractionActive.release();
   
   m_pacmeuserinteractionMain.release();

   //m_pmanualresethappeningNewProcedurePosted.release();

   //m_pmanualresethappeningNewRequestPosted.release();

   //m_pmanualresethappeningHappening.release();

}


// void task::__task_init()
// {
//
//    __check_refdbg
//
//       on_task_init();
//
//    if (m_phappeningInitialization)
//    {
//
//       m_phappeningInitialization->set_happening();
//
//    }
//
//
// }


// void task::__task_term()
// {
//
//    on_task_term();
//
// }


// void task::on_task_init()
// {
//
//    __check_refdbg
//
//       init_task();
//
//    m_estatus = ::success;
//
// }



// void task::on_task_term()
// {
//
//    term_task();
//
// }



bool task::is_thread() const
{

   return false;

}


#ifdef WINDOWS
unsigned int WINAPI task::s_os_task(void * p)
#else
void * task::s_os_task(void * p)
#endif
{

   {

      auto ptaskhandler = ::transfer_as_pointer((::task_handler *)p);

      ptaskhandler->__task_handle();

   }

   return 0;

}


void task::__task_init()
{

   m_estatus = ::success;

   set_flag(e_flag_running);

   //if (has_finishing_flag())
   //{

   //   clear_finishing_flag();

   //}

   __check_refdbg

      set_task();

   __check_refdbg

      //set_current_handles();


#if defined(WINDOWS)

   {

      REFDBG_THIS(this);

      __defer_construct(m_pexceptiontranslator);

      m_pexceptiontranslator->attach();

   }

#endif


   //#ifdef WINDOWS_DESKTOP
//
//   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &m_htask, 0, false, DUPLICATE_SAME_ACCESS);
//
//#else
//
//   m_htask = ::current_htask();
//
//#endif
//
//   m_uThread = ::current_itask();

   try
   {

      __priority_and_affinity();

   }
   catch (...)
   {

      // affinity isn't critical

   }

   //#ifndef WINDOWS
   //
   //   information() << "init_thread : " << ::type(this).name();
   //
   //#endif

   //system()->node_thread_initialize(this);



      //{

      //   auto pthreadParent = ::parallelization::calc_parent(this);

      //   if (pthreadParent)
      //   {

      //      if (!pthreadParent->task_add(this))
      //      {

      //         if (pthreadParent->id().case_insensitive_begins("predicate_thread") && id().case_insensitive_begins("predicate_thread"))
      //         {

      //            pthreadParent->task_erase(this);

      //            pthreadParent = ::parallelization::calc_parent(pthreadParent);

      //            if (!pthreadParent->task_add(this))
      //            {

      //               return ::error_failed;

      //            }

      //         }
      //         else
      //         {

      //            return ::error_failed;

      //         }

      //      }

      //   }

      //}

   {


         processor_cache_oriented_set_thread_memory_pool(0);
      // set default handler cache oriented thread memory pool index to 0 ("zero") (The First One)

      //system()->parallelization_initialize();

   }

   //   //try
   //   //{
   //   __check_refdbg

   //   __os_initialize();

   //__check_refdbg
   //   //}
   //   //catch (const ::exception & e)
   //   //{

   //   //   m_estatus = e.m_estatus;

   //   //   if (succeeded(m_estatus))
   //   //   {

   //   //      m_estatus = error_failed;

   //   //   }

   //   //   m_result.add(e);

   //   //   top_handle_exception(e);

   //   //}
   //   //catch (...)
   //   //{

   //   //   m_estatus = error_failed;

   //   //   m_result.add(error_failed);

   //   //}

   //   //return m_estatus;



   //__check_refdbg

   //   init_task();

   if (m_strTaskName.has_character())
   {

      ::task_set_name(m_htask, m_strTaskName);

   }

}


CLASS_DECL_ACME bool os_on_init_thread();
CLASS_DECL_ACME void os_on_term_thread();


void task::__task_main()
//void task::__task_main(::procedure & procedureTaskEnded)
//void task::__task_main()
{

   //::pointer < manual_reset_happening > pmanualresethappeningFinished;
   ::os_on_init_thread();

   try
   {

      __check_refdbg

      //os_task_init_term ostaskinitterm;
      
      __task_init();
         
      //__check_refdbg

         //::set_task(this);

      //__check_refdbg

         //      ptask->_os_task();

#if 0

         information() << "s_os_task current_itask : " << current_itask();

#endif

      //ptask->release(REFERENCING_DEBUGGING_P_FUNCTION_LINE(ptask));

      try
      {

         main();

      }
      catch (::exit_exception & exitexception)
      {

         error() << "Exit Exception reached task procedure (1)";

         exitexception.finish(this);

      }
      catch (::exception & exception)
      {

         error() << "Exception reached task procedure : " << exception;

      }
      catch (...)
      {

         error() << "Exception reached task procedure (...)";

      }

      //auto psystem = system();

      //if (psystem)
      //{

      //   auto ptaskmessagequeue = psystem->m_ptaskmessagequeue;

      //   if (ptaskmessagequeue)
      //   {

      //      ptaskmessagequeue->clear_message_queue(m_taskindex);

      //   }

      //}

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

      //try
      //{

      //   on_before_destroy_task();

      //}
      //catch (...)
      //{

      //}

      //procedureTaskEnded = ::transfer(m_procedureTaskEnded);

      __task_term();

   }
   catch (...)
   {

   }
   
   ::os_on_term_thread();

}


void task::__task_term()
{

   auto psystem = system();

   if (psystem)
   {

      auto ptaskmessagequeue = psystem->m_ptaskmessagequeue;

      if (ptaskmessagequeue)
      {

         ptaskmessagequeue->clear_message_queue(m_taskindex);

      }

   }

   //term_task();

   //__os_finalize();

   unset_task();

   ::pointer<::object>pparentTask = m_pobjectParentTask;

   if (::is_set(pparentTask) && pparentTask != this)
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

   destroy();

   m_htask = nullptr;

   m_itask = nullptr;

   ::task_release();

}



//bool task::is_task_set() const
//{
//
//   //return system()->is_task_set(m_taskindex);
//
//   return m_htask.is_set() && has_flag(e_flag_running);
//
//}


//void task::register_task()
//{
//
//   ::system()->set_task(m_taskindex, this);
//
//}
//
//
//void task::unregister_task()
//{
//
//   ::system()->unset_task(m_taskindex, this);
//
//}


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

      m_procedurea2.add(procedure);

      new_main_loop_happening()->set_happening();

      //update_new_main_loop_happening();

   }

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

   ::cast < ::sequence > psequence = procedure.m_pbase;

   if (is_current_task())
   {

      procedure();

      return;

   }

   ::pointer < ::manual_reset_happening > pmanualresethappeningOnEndOfSequence;

   ::pointer < ::manual_reset_happening > pmanualresethappeningOnEndOfSequenceToSetInProcedure;
   
   if (psequence)
   {

      __defer_construct_new(psequence->m_pmanualresethappeningOnEndOfSequence);

      pmanualresethappeningOnEndOfSequence = psequence->m_pmanualresethappeningOnEndOfSequence;

   }
   else
   {

      __construct_new(pmanualresethappeningOnEndOfSequence);

      pmanualresethappeningOnEndOfSequenceToSetInProcedure = pmanualresethappeningOnEndOfSequence;

   }

   auto pwaitingcall = ::as_waiting_call(procedure);

   wait_for_end_of_sequence waitforendofsequence(pmanualresethappeningOnEndOfSequence, psequence, pwaitingcall);

   ::pointer < ::exception > pexception;

   if (pmanualresethappeningOnEndOfSequenceToSetInProcedure)
   {

      post([this, procedure, pmanualresethappeningOnEndOfSequenceToSetInProcedure, &pexception]()
         {

               try
               {

                  procedure();

               }
               catch (::exception& e)
               {

                  pexception = e.clone();

               }
               catch (...)
               {

                  pexception = __allocate::exception(error_catch_all_exception);

               }


               if (pmanualresethappeningOnEndOfSequenceToSetInProcedure)
               {

                  pmanualresethappeningOnEndOfSequenceToSetInProcedure->set_happening();

               }

         });

   }
   else
   {

      post([this, procedure, &pexception]()
         {

            try
            {

            procedure();


         }
         catch (::exception& e)
      {

         pexception = e.clone();

      }
      catch (...)
      {

         pexception = __allocate::exception(error_catch_all_exception);

      }


            });
   }

   if (!waitforendofsequence.lock(procedure.timeout()))
   {

#ifdef _DEBUG

      warning() << "waitforendofsequence timeout";

      debug_break();

#endif

      procedure.m_pbase->on_timed_out();

   }

   if (pexception)
   {

      throw* pexception;

   }

}


bool task::pick_next_posted_procedure()
{

   ASSERT(is_current_task());

   _synchronous_lock synchronouslock(this->synchronization());

   while (true)
   {

      if (m_procedurea2.is_empty())
      {

         return false;

      }

      auto procedure = ::transfer(m_procedurea2.pick_first());

      defer_reset_main_loop_happening();

      if (!procedure)
      {

         continue;

      }

      //if (m_procedurea.is_empty())
      //{

      //   new_procedure_posted()->reset_happening();

      //}

      m_procedurelistHandling.transfer_tail(::transfer(procedure));

      return true;

   }

}


e_happening task::pick_happening()
{

   _synchronous_lock synchronouslock(this->synchronization());

   if (m_ehappeninga.is_empty())
   {

      return {};

   }

   auto ehappening = ::transfer(m_ehappeninga.pick_first());

   defer_reset_main_loop_happening();

   return ehappening;

}


void task::handle_posted_procedures()
{

   ASSERT(is_current_task());

   while (pick_next_posted_procedure())
   {

      try
      {

         m_procedurelistHandling.tail()();

      }
      catch (...)
      {


      }

      m_procedurelistHandling.erase_tail();

   }

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

   if (m_strTaskTag.has_character())
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


void task::set_happened(e_happening ehappening)
{

   _synchronous_lock synchronouslock(this->synchronization());

   m_ehappeninga.add(ehappening);

   new_main_loop_happening()->set_happening();

   //update_new_main_loop_happening();

}


bool task::on_happening(e_happening ehappening)
{

   if(ehappening == e_happening_finish)
   {

      return false;

   }

   return true;

}


void task::task_caller_on_init()
{

   //return ::success;

}


void task::call_init_task()
{

   init_task();

   if (m_phappeningInitialization)
   {

      m_phappeningInitialization->set_happening();

   }

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

   if (m_procedure)
   {

      if (m_procedure != this)
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
//   //      id() = ::type(pelement).name();
//
//   //      task_set_name(id());
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


//bool task::do_tasks()
//{
//   
//   //throw ::interface_only("tasks don't have message queue, threads do (1)");
//
//   _do_tasks();
//
//   if (::system()->m_bConsole || (m_eflagElement & e_flag_running))
//   {
//
//      run_posted_procedures();
//
//   }
//
//   return true;
//
//}


//bool task::defer_pump_message()
//{
//
//   throw ::interface_only("tasks don't have message queue, threads do (2)");
//
//   return false;
//
//}
//

bool task::has_message() const
{

   throw ::interface_only("tasks don't have message queue, threads do (3)");

   return false;

}


//void task::branch(
//   ::particle * pparticle,
//   ::enum_priority epriority,
//   unsigned int nStackSize,
//   unsigned int uCreateFlags ARG_SEC_ATTRS)
//{
//
//   m_pelement = pelement;
//
//   id() = ::type(pelement).name();
//
//   return branch(epriority, nStackSize, uCreateFlags ADD_PARAM_SEC_ATTRS);
//
//}


void task::on_before_branch()
{

   if (::is_null(m_pobjectParentTask))
   {

      if (this == ::system())
      {

      }
      else
      {

         if (this == (::task *)session())
         {

            m_pobjectParentTask = system();

         }
         else
         {

            m_pobjectParentTask = ::get_task();

            if (::is_null(m_pobjectParentTask))
            {

               m_pobjectParentTask = m_papplication;

            }

         }

         if (m_pobjectParentTask)
         {

            if (m_pobjectParentTask != this)
            {

               m_pobjectParentTask->add_task(this);

            }

         }
         else
         {

            throw ::exception(error_invalid_usage);

         }

      }

   }

}


void task::branch(enum_parallelization eparallelization, const ::create_task_attributes_t & createtaskattributes)
{

   if (eparallelization == e_parallelization_synchronous)
   {

      return branch_synchronously(createtaskattributes);

   }

   if (id().is_empty())
   {

      if (m_procedure)
      {

         id() = ::type(m_procedure).name();

      }
      else
      {

         id() = ::type(this).name();

      }

   }

   if (id().is_empty() || id() == "task" || id() == "thread")
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

#ifdef _DEBUG

   string strId = id().as_string();

   if (strId.case_insensitive_contains("forking_thread"))
   {

#if 0

#ifdef WINDOWS_DESKTOP

      ::exception_engine().reset();

      OS_DWORD                dwDisplacement;

      OS_DWORD                uia[4096];

      dwDisplacement = 0;

      unsigned int maxframes = sizeof(uia) / sizeof(uia[0]);

      ULONG BackTraceHash;

      int iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID *>(&uia), &BackTraceHash);

      char sz[1024];

      zero(sz);

      engine_symbol(sz, sizeof(sz), &dwDisplacement, uia[5]);

      unsigned int uiLine = 0;

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

   //m_bIsRunning = true;

   set_flag(e_flag_task_started);

   on_before_branch();

#if REFERENCING_DEBUGGING

   m_prefererTransfer2 = __refdbg_add_referer

#endif

   increment_reference_count();

   if (m_taskindex)
   {

      throw ::exception(error_wrong_state);

   }

   if (m_htask.is_set())
   {

      throw ::exception(error_wrong_state);

   }

   if (m_itask.is_set())
   {

      throw ::exception(error_wrong_state);

   }

   auto ptaskhandler = createtaskattributes.m_ptaskhandler;

   if (::is_null(ptaskhandler))
   {

      ptaskhandler = __raw_new task_handler;

   }
   else
   {

      ptaskhandler->increment_reference_count();

   }

   ptaskhandler->m_ptask = this;

#ifdef WINDOWS

   DWORD dwThread = 0;

   m_htask = (::uptr) ::CreateThread(
      (LPSECURITY_ATTRIBUTES)(createtaskattributes.m_psecurityattributes ? createtaskattributes.m_psecurityattributes->get_os_security_attributes() : nullptr),
      createtaskattributes.m_uStackSize,
      (LPTHREAD_START_ROUTINE) & ::task::s_os_task,
      (LPVOID)(::task_handler *)ptaskhandler,
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

   if (!m_bJoinable)
   {

      pthread_attr_setdetachstate(&taskAttr, PTHREAD_CREATE_DETACHED); // Set task to detached state. No need for pthread_join

   }

   int iError = pthread_create(
      (pthread_t *)&m_htask,
      &taskAttr,
      &task::s_os_task,
      ptaskhandler);

   if (iError != 0)
   {

      if (iError == EAGAIN)
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
      else if (iError == EINVAL)
      {
         //EINVAL Invalid settings in attr.
         throw ::exception(error_bad_argument);

      }
      else if (iError == EPERM)
      {
         //EPERM  No permission to set the scheduling policy and parameters
         //     specified in attr.
         throw ::exception(error_failed);
      }

   }

#endif

//   if (!m_htask)
//   {
//
//      release();
//
//      m_bIsRunning = false;
//
//      throw ::exception(error_wrong_state);
//
//      //return ::error_failed;
//
//   }

   //return ::success;
   //return this;

}


void task::branch_synchronously(const ::create_task_attributes_t & createtaskattributes)
{

   clear_finishing_flag();

   ENSURE(!m_htask);

   //if(id().is_empty())
   //{

   //   id() = ::type(this).name();

   //}

//#ifdef _DEBUG
//
//   string strId = id();
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
//      unsigned int maxframes = sizeof(uia) / sizeof(uia[0]);
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
//      unsigned int uiLine = 0;
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

      m_phappeningInitialization = __allocate manual_reset_happening();

   }

   //auto estatus = branch(epriority, nStackSize, uiCreateFlags);

   branch(e_parallelization_asynchronous, createtaskattributes);

   if (!m_htask)
   {

      //if (::is_set(this))
      //{

      //   this->release_reference(this);

      //}

      decrement_reference_count();

      throw ::exception(error_resource);

   }

//#ifndef WINDOWS

  // if (pthread_equal((pthread_t)m_htask, (pthread_t)m_itask))
   //{

     // information() << "create_thread success";

   //}

//#endif

   if (m_phappeningInitialization)
   {

      {

         auto phappeningProtectionWhileWaiting = m_phappeningInitialization;

         phappeningProtectionWhileWaiting->wait();

      }

      ::e_status estatus = m_estatus;

      if (estatus.failed())
      {

         ::e_status estatusExit = m_estatus;

         throw ::exception(estatusExit);

      }

   }

   //   if (id().is_empty())
   //   {
   //
   //      if (m_pelement)
   //      {
   //
   //         id() = ::type(m_pelement).name();
   //
   //      }
   //      else
   //      {
   //
   //         id() = ::type(this).name();
   //
   //      }
   //
   //   }
   //
   //   if (id().is_empty() || id() == "task" || id() == "thread")
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
   //#ifdef _DEBUG
   //
   //   string strId = id();
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
   //      unsigned int maxframes = sizeof(uia) / sizeof(uia[0]);
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
   //      unsigned int uiLine = 0;
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

   //return this;

}


bool task::task_sleep(const class time & timeWait)
{

   auto waitStart = ::time::now();

   while (task_get_run())
   {

      auto waitStep = minimum(timeWait - waitStart.elapsed(), 100_ms);

      if (waitStep <= 0_s)
      {

         return true;

      }

      task_iteration();

      auto waitStep2 = minimum(timeWait - waitStart.elapsed(), 100_ms);

      if (waitStep2 <= 0_s)
      {

         return true;

      }

      ::preempt(waitStep2);

   }

   return false;

}


//void task::on_before_destroy_task()
//{
//
//   ::pointer<::object>pparentTask = m_pobjectParentTask;
//
//   if (::is_set(pparentTask))
//   {
//
//      try
//      {
//
//         pparentTask->transfer_tasks_from(this);
//
//      }
//      catch (...)
//      {
//
//      }
//
//      try
//      {
//
//         pparentTask->erase_task_and_set_task_new_parent(this, nullptr);
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//}


//void task::branch(::particle * pparticle, ::enum_priority epriority, unsigned int nStackSize, unsigned int uCreateFlags ARG_SEC_ATTRS)
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


//void task::set_current_handles()
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   m_htask = (::uptr) duplicate_handle(::current_htask().m_h);
//
//#else
//
//   m_htask = ::current_htask();
//
//#endif
//
//   m_itask = ::current_itask();
//
//}


void task::kick_idle()
{

   _post([]() {});

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

   auto pmanualresethappening = __create_new < manual_reset_happening >();

   post([this, procedure, pmanualresethappening]()
      {

         procedure();

         pmanualresethappening->set_happening();

      });

   auto timeout = timeTimeout;

   if (timeout.is_null())
   {

      timeout = get_default_run_timeout();

   }

   auto estatus = pmanualresethappening->wait(timeout);

   if (estatus.failed())
   {

      throw ::exception(estatus);

   }

}



CLASS_DECL_ACME bool __task_sleep(task * task)
{

   while (task->task_get_run())
   {

      preempt(100_ms);

   }

   return false;

}


CLASS_DECL_ACME bool __task_sleep(task * ptask, const class time & timeWait)
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

      ::pointer<manual_reset_happening>spev;

      {

         _synchronous_lock synchronouslock(ptask->synchronization());

         if (ptask->m_pevSleep.is_null())
         {

            ptask->m_pevSleep = __allocate manual_reset_happening();

            ptask->m_pevSleep->reset_happening();

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


CLASS_DECL_ACME bool __task_sleep(::task * ptask, ::particle * pparticle)
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


CLASS_DECL_ACME bool __task_sleep(task * ptask, const class time & timeWait, ::particle * pparticle)
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

   auto iTenths = (int)(timeWait.integral_millisecond() / 100);

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

   if (::is_null(ptask))
   {

      ::preempt(timeWait);

      return true;

   }

   if (!ptask->task_sleep(timeWait))
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


//CLASS_DECL_ACME void set_main_itask(itask itask);
//
//
//CLASS_DECL_ACME void set_main_htask(htask htask);


//CLASS_DECL_ACME itask main_user_itask();


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
//   return ::system()->m_pfactory;
//
//}

/*
namespace platform
{


   ::collection::index platform::new_task_index()
   {
	   
	  return m_iNewTaskIndex++;

//      critical_section_lock sl(&m_criticalsectionTask);

//      auto iTaskIndex = m_itaska.find_first(itask);

//      if (bAddIfNotInList && iTaskIndex < 0)
//      {

//         iTaskIndex = m_itaska.add(itask);

//      }

//      return iTaskIndex;

   }

}
*/


::interlocked_long_long g_iNewTaskIndex = 1;


static ::task_index new_task_index()
{

   auto iNewTaskIndex = g_iNewTaskIndex++;

   return iNewTaskIndex;

}


thread_local ::task_index t_taskindex = new_task_index();


::task_index current_task_index()
{

	return t_taskindex;

}


//::collection::index task_index()
//{

//   return task_index(::current_itask());

//}


void task_iteration()
{

   auto ptask = ::get_task();

   if (ptask)
   {

      ptask->task_iteration();

   }

}



void task_run(const class ::time & time)
{

   auto ptask = ::get_task();

   if (ptask)
   {

      ptask->task_run(time);

   }

   //if (::platform::get()->m_bConsole)
   //{

   //   system()->application()->do_tasks();

   //   system()->do_tasks();

   //}

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






static htask g_htaskMain;

static itask g_itaskMain;

static ::task_index g_taskindexMain;


CLASS_DECL_ACME void set_main_htask(htask htask)
{

   // MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_htaskMain = htask;

}


CLASS_DECL_ACME void set_main_itask(itask itask)
{

   //   MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_itaskMain = itask;

}


CLASS_DECL_ACME void set_main_task_index(const ::task_index & taskindex)
{

   //   MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_taskindexMain = taskindex;

}


CLASS_DECL_ACME htask main_htask()
{

   return g_htaskMain;

}


CLASS_DECL_ACME itask main_itask()
{

   return g_itaskMain;

}


CLASS_DECL_ACME ::task_index main_task_index()
{

   return g_taskindexMain;

}


CLASS_DECL_ACME ::task * main_task()
{
	
	auto pthreadstorage = ::system()->thread_storage(main_task_index());
	
	if(::is_null(pthreadstorage))
	{
		
		return nullptr;
		
	}
	
	auto ptask = pthreadstorage->m_ptask;
	
	if(::is_null(ptask))
	{
		
		return nullptr;
		
	}
	
	return ptask;
	
}


//CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach)
//{
//
//}


CLASS_DECL_ACME void set_main_thread()
{

   set_main_htask(current_htask());

   set_main_itask(current_itask());
   
   set_main_task_index(task_index());

}


//CLASS_DECL_ACME void set_main_thread(htask htask)
//{

//   set_main_itask(::as_itask(htask));

//   set_main_htask(htask);

//}


CLASS_DECL_ACME bool is_main_thread()
{

	return task_index() == main_task_index();

//   return current_itask() == main_itask();

}



