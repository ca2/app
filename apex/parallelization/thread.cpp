#include "framework.h"
#include "apex/operating_system.h"
#include "apex/message.h"
#include "acme/update.h"
#include "acme/parallelization/message_queue.h"
#include "apex/platform/node.h"


//HANDLE duplicate_handle(HANDLE h);
CLASS_DECL_ACME void TRACELASTERROR();


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


CLASS_DECL_ACME message_queue * get_message_queue(itask_t idthread, bool bCreate);


::mutex * g_pmutexThreadWaitClose = nullptr;


#ifdef WINDOWS_DESKTOP

index engine_fileline(DWORD_PTR dwAddress, char * psz, int nCount, u32 * pline, u32 * pdisplacement = 0);

#endif

#ifdef OS64BIT

#define STRFPTR "0x%016x"

#else

#define STRFPTR "0x%08x"

#endif


#ifdef LINUX

int SetThreadAffinityMask(htask_t h, unsigned int dwThreadAffinityMask);

#endif


struct send_thread_message :
   virtual public object
{

   MESSAGE                 m_message;

   manual_reset_event      m_ev;

   send_thread_message(::object * pobject);

   virtual ~send_thread_message();

};


send_thread_message::send_thread_message(::object * pobject)
{

   __zero(m_message);

   m_ev.ResetEvent();

}


send_thread_message::~send_thread_message()
{

   m_ev.SetEvent();

}


bool thread::s_bAllocReady = false;


thread::file_info::file_info()
{

   m_durationFileSharingViolationTimeout = seconds(2000);

}


thread::file_info::~file_info()
{

}


thread::thread()
{

   m_bBranchHandling = false;

   m_bMessageThread = true;
       
   //set_layer(LAYERED_THREAD, this);

   //m_pthread = this;

   m_bThreadClosed = false;

   m_bIsPredicate = false;

   m_bAuraMessageQueue = false;

#ifdef APEX_MESSAGE_QUEUE

   m_bClosedMq = false;

#endif

   m_bLastingThread = true;

   m_bMessageThread = false;

   m_estatus = ::success_none;

//#ifdef MACOS
//
//   m_runloop = nullptr;
//
//#endif

   m_epriority = priority_normal;

   m_pmutexThreadUiPtra = nullptr;

   m_puiptraThread = nullptr;

   m_bThreadToolsForIncreasedFps = false;

   m_bTemporary = false;

   m_uThreadAffinityMask = 0;

   m_millisHeartBeat.Now();

   defer_create_mutex();

   m_bReady = false;

   m_bZipIsDir2 = true;

   m_pslUser = nullptr;

   m_pfileinfo = nullptr;

   m_bDupHandle = false;

   m_nDisablePumpCount = 0;

   m_bSimpleMessageLoop = true;

#ifdef WINDOWS

   m_bCoInitialize = false;

#endif

   memory_counter_increment(this);

}


void thread::thread_common_construct()
{

   m_idContextReference = id_none;

   m_bDedicated = false;

   if (get_application() != nullptr && get_application()->get_session() != nullptr)
   {

      m_bZipIsDir2 = get_application()->get_session()->m_bZipIsDir2;

   }

   if (::get_task() != nullptr)
   {

      m_bAvoidProcedureFork = ::get_task()->m_bAvoidProcedureFork;

   }
   else
   {

      m_bAvoidProcedureFork = false;

   }

}


thread::~thread()
{

   memory_counter_decrement(this);

   ::acme::del(m_puiptraThread);

   ::acme::del(m_pmutexThreadUiPtra);

}


htask_t thread::get_os_handle() const
{

   return get_hthread();

}


bool thread::is_thread() const
{

   return true;

}


::thread * thread::get_thread()
{

   return this;

}


bool thread::is_dedicated_thread() const
{

   return m_bDedicated;

}


void thread::on_pos_run_thread()
{


}


void thread::term_thread()
{

   if (m_pcounter.is_set())
   {

      (*m_pcounter)++;

   }

   switch (m_idContextReference)
   {
   case id_application:
   {

      auto papplication = get_application();

      if (papplication)
      {

         papplication->release_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(papplication));

      }

   }
      break;

   case id_session:
   {

      auto pcontextsession = get_session();

      if (pcontextsession)
      {

         pcontextsession->release_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(pcontextsession));

      }

   }
   break;
   case id_system:
   {

      auto psystem = get_system()->m_papexsystem;

      if (psystem)
      {

         psystem->release_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(pcontextsystem));

      }

   }
   break;
   case id_thread:
   {

      auto pthread = get_task();
      
      if (pthread)
      {

         pthread->release_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(pcontextthread));

      }

   }
      break;
   default:
      break;

   }

//   channel::on_finish();

   term_task();

   //if (this)
   //{

     // this->release_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   //}


   if (get_session())
   {

      

   }

   //if (psystem)
   //{

   //   psystem->release_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   //}

   //if (get_context_thread())
   //{

   //   get_context_thread()->release_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   //}


   {

      synchronous_lock synchronouslock(mutex());

      for (auto & pmanualresetevent : m_eventaWait)
      {

         try
         {

            pmanualresetevent->set_event();

         }
         catch (...)
         {

         }

      }

   }

}


::e_status thread::osthread_term()
{

   ::task::osthread_term();

#ifndef WINDOWS_DESKTOP

   __release(m_pmq);

#endif

   {

      synchronous_lock synchronouslock(mutex());

      if (m_pevSleep.is_set())
      {

         m_pevSleep->SetEvent();

         m_pevSleep.release();

      }

   }

   try
   {

      m_handlermap.erase_all();

   }
   catch (...)
   {

   }

   __os_finalize();

   __set_thread_off();

   m_psystem->m_papexsystem->m_papexnode->thread_finalize(this);

   ::e_status estatus = m_result.m_estatus;

   return estatus;

}


void thread::on_keep_alive()
{

   m_millisHeartBeat.Now();

}


::task_pool* thread::taskpool()
{

   __defer_construct_new(m_ptaskpool);

   return m_ptaskpool;

}


bool thread::is_alive()
{

   //if (!m_bRun)
   //   return false;

   //if ((m_millisHeartBeat.elapsed()) > ((5000) * 91))
   // return false;

   return true;

}



//bool thread::is_auto_delete()
//{
//
//   return m_bAutoDelete;
//
//}




CLASS_DECL_APEX void thread_alloc_ready(bool bReady)
{

   thread::s_bAllocReady = bReady;

}


bool thread::has_step() const
{

   if (m_bSimpleMessageLoop)
   {

      return has_raw_message();

   }
   else
   {

      return has_message();

   }

}


bool thread::has_raw_message() const
{

   return has_message();

}


bool thread::has_message() const
{

   MESSAGE msg;

   return ((thread*)this)->peek_message(&msg, nullptr, 0, 0, PM_NOREMOVE) != false;

}


bool thread::thread_step()
{

   if (m_bSimpleMessageLoop)
   {

      return raw_pump_message();

   }
   else
   {

      return pump_message();

   }

}


::e_status thread::thread_loop()
{

   while (true)
   {

      if (!task_get_run())
      {

         string strType = type_name();

         if (strType.contains_ci("session"))
         {

            auto bShouldRun = task_get_run();

            if (!bShouldRun)
            {

               output_debug_string("session_shouldn't_run?");

            }

         }

         break;

      }

      try
      {

         if(!thread_step())
         {

            string strType = type_name();

            if (strType.contains_ci("session"))
            {

               auto bShouldRun = task_get_run();

               if (!bShouldRun)
               {

                  output_debug_string("session_shouldn't_run?");

               }

            }

            break;



//            if(strType.contains("wave_player"))
//            {
//
//               output_debug_string("!xxm_bSimpleMessageLoop !xxpump_message xxthread::run from wave_player");
//
//            }
//            else if(strType.ends_ci("out"))
//            {
//
//               output_debug_string("!xxm_bSimpleMessageLoop !xxpump_message xxthread::run from out");
//
//            }
//            else if(strType.contains("output_thread"))
//            {
//
//               output_debug_string("!xxm_bSimpleMessageLoop !xxpump_message xxthread::run from output_thread");
//
//            }

            break;

         }

      }
      catch (const ::exception::exception & e)
      {

         if (!handle_exception(e))
         {

            output_debug_string("exception occurred (2.1)");

            break;

         }

      }
      catch (...)
      {

         output_debug_string("exception occurred (2.2)");

         break;

      }

   }

   return m_estatus;

}

//::e_status thread::run()
//{
//
//   return ::success;
//
//}

::e_status thread::run()
{

   ASSERT_VALID(this);

   INFO("thread::run");

   string strType = type_name();

   if (strType.contains("session"))
   {

      output_debug_string("session");

   }
   else if(strType.contains("wave_player"))
   {

      output_debug_string("xxthread::run from wave_player");

   }
   else if(strType.ends_ci("out"))
   {

      output_debug_string("xxthread::run from out");

   }
   else if(strType.contains("output_thread"))
   {

      output_debug_string("xxthread::run from output_thread");

   }

   if (m_pmatter && m_pmatter != this)
   {

      m_id = m_pmatter->type_name();

      task_set_name(m_id);

      return m_pmatter->run();

   }

   if (m_bSimpleMessageLoop)
   {

      TRACE("running thread with simple message loop");

      if(strType.contains("wave_player"))
      {

         output_debug_string("xxm_bSimpleMessageLoop xxthread::run from wave_player");

      }
      else if(strType.ends_ci("out"))
      {

         output_debug_string("xxm_bSimpleMessageLoop xxthread::run from out");

      }
      else if(strType.contains("output_thread"))
      {

         output_debug_string("xxm_bSimpleMessageLoop xxthread::run from output_thread");

      }


   }


   auto estatus = thread_loop();

   if(strType.contains("wave_player"))
   {

      output_debug_string("ending xxthread::run from wave_player");

   }
   else if(strType.ends_ci("out"))
   {

      output_debug_string("ending xxthread::run from out");

   }
   else if(strType.contains("output_thread"))
   {

      output_debug_string("ending xxthread::run from output_thread");

   }



   //   thisend << m_iErrorCode;

   //   return m_iErrorCode;



   return m_estatus;

}


bool thread::pump_runnable()
{

   synchronous_lock synchronouslock(mutex());

   while(task_get_run())
   {

      if (m_routinea.is_empty())
      {

         return false;

      }

      auto method = m_routinea.first();

      m_routinea.erase_at(0);

      if (method)
      {

         synchronouslock.unlock();

         method();

         return true;

      }

   }

   return false;

}


::e_status thread::post(const ::routine& routine)
{

   if (!m_bBranchHandling)
   {

      m_bBranchHandling = true;

      MESSAGE_LINK(e_message_branch, this, this, &::thread::on_message_branch);

   }

   post_message(e_message_branch, 0, routine.m_p);

   return ::success;

}

 
void thread::on_message_branch(::message::message* pmessage)
{

   ::routine routine(pmessage->m_lparam);

   if (pmessage->m_wparam == 0)
   {

      routine();

   }

}


//__pointer(::matter) thread::running(const char * pszTag) const
//{
//
//   auto pmatter = ::channel::running(pszTag);
//
//   if (pmatter)
//   {
//
//      return pmatter;
//
//   }
//
//   //synchronous_lock synchronouslock(mutex());
//
//   //for(auto & pcomposite : *m_pcompositea)
//   //{
//
//   //   try
//   //   {
//
//   //      const char * pszTaskTag = pcomposite->get_task_tag();
//
//   //      if (!strcmp(pszTaskTag, pszTag))
//   //      {
//
//   //         return pcomposite;
//
//   //      }
//
//   //   }
//   //   catch (...)
//   //   {
//
//
//   //   }
//
//   //}
//
//   return nullptr;
//
//
//}


int thread::_GetMessage(MESSAGE * pmessage, ::windowing::window * pwindow, ::u32 wMsgFilterMin,::u32 wMsgFilterMax)
{

   __throw(exception::exception());

   //__zero(pmessage);

   //return mq_get_message(pmessage, oswindow, wMsgFilterMin, wMsgFilterMax);
   return false;

}


bool thread::pump_message()
{

   try
   {

      if (pump_runnable())
      {

         return true;

      }

   }
   catch(...)
   {

      if (m_strDebugType.contains("filemanager"))
      {

         //INFO("filemanager");

      }

   }

   try
   {

      if(!get_message(&m_message,nullptr,0,0))
      {

         string strType = type_name();

         if (strType.contains_ci("session"))
         {

            auto bShouldRun = task_get_run();

            if (!bShouldRun)
            {

               output_debug_string("session_shouldn't_run?");

            }

         }

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

         TRACE(trace_category_appmsg, e_trace_level_information, string(type_name()) + " thread::pump_message - Received e_message_quit.\n");

         INFO("%s thread::pump_message - Received e_message_quit.\n", type_name());

         m_nDisablePumpCount++; // application must die
         // Note: prevents calling message loop things in 'exit_thread'
         // will never be decremented
         return false;

      }

      if (m_message.m_id == e_message_destroy_window && m_strDebugType.contains("notify_icon"))
      {

         INFO("notify_icon");

      }

      process_message();

      return true;

   }
   catch (const ::exception::exception & e)
   {

      if (m_strDebugType.contains("filemanager"))
      {

         //INFO("filemanager");

      }

      if (handle_exception(e))
      {

         return true;

      }

      //// get_application() may be it self, it is ok...
      //if (get_application()->final_handle_exception(e))
      //{

      //   return true;

      //}

   }
   catch(...)
   {

      INFO("... exception");

   }

   return false;

}


bool thread::get_message()
{

   MESSAGE message = {};

   int iResult = get_message(&message, NULL, 0, 0);

   if(iResult == -1)
   {

#ifdef WINDOWS_DESKTOP

      auto dwError = ::GetLastError();

      INFO("ERROR thread::get_message GetMessage %d", dwError);

#endif

      return true;

   }
   else if(iResult == 0)
   {

      return false;

   }

   m_message = message;

   return true;

}


bool thread::raw_pump_message()
{

   string strType = type_name();

   try
   {

      if(strType.contains("output_thread"))
      {

         //output_debug_string("\nOUTPUT_THREAD thread::raw_pump_message");

      }

      if (!get_message())
      {

         if(::str::begins(strType, "multimedia::"))
         {

            if(strType.contains("wave_player"))
            {

               output_debug_string("!xxGetMessage !xxpump_message xxthread::run from wave_player");

            }
            else if(strType.ends_ci("out"))
            {

               output_debug_string("!xxGetMessage !xxpump_message xxthread::run from out");

            }
            else if(strType.contains("output_thread"))
            {

               output_debug_string("!xxGetMessage !xxpump_message xxthread::run from output_thread");

            }
            else
            {

               output_debug_string("!xxGetMessage !xxpump_message xxthread::run from multimedia::*");

            }

         }

         TRACE(trace_category_appmsg, e_trace_level_information, "xx" + strType + " thread::raw_pump_message - Received e_message_quit");

         ::output_debug_string("xx" + strType + " thread::raw_pump_message - Received e_message_quit.\n");

         m_nDisablePumpCount++; // application must die
         // Note: prevents calling message loop things in 'exit_thread'
         // will never be decremented
         return false;

      }

      raw_process_message();

      return true;

   }
   catch (const ::exception::exception & e)
   {

      if (handle_exception(e))
      {

         return true;

      }

      //// get_application() may be it self, it is ok...
      //if (get_application()->final_handle_exception(e))
      //{

      //   return true;

      //}

   }
   catch (...)
   {

      output_debug_string("xxcatch... xx" + strType + "xxraw_pump_message");

   }

   return false;

}


::e_status thread::process_message(::message::message * pmessage)
{

   return process_thread_message(pmessage);

}


::e_status thread::process_thread_message(::message::message * pmessage)
{

   try
   {

      message_handler(pmessage);

      return ::success;

   }
   catch (const ::exception::exception & e)
   {

      if (!handle_exception(e))
      {

         post_quit_message(-1);

         pmessage->m_lresult = -1;

      }

      return e.m_estatus;

   }
   catch (...)
   {

      TRACE("application::process_thread_message : ::extended::status processing application thread message (...)");

   }

   return ::error_exception;

}


// apex commented
//void thread::process_window_message(::user::message * pusermessage)
//{
//
//   ASSERT(pusermessage->m_puserinteraction != nullptr);
//
//   if (pusermessage->m_puserinteraction == nullptr)
//   {
//
//      process_thread_message(pusermessage);
//
//      return;
//
//   }
//
//   try
//   {
//
//      pusermessage->m_puserinteraction->m_puiThis->message_handler(pusermessage);
//
//   }
//   catch (const ::exception::exception & e)
//   {
//
//      process_window_procedure_exception(pe, pusermessage);
//
//      TRACE("application::process_window_message : ::extended::status processing window message (const ::exception::exception & )");
//
//      if (!handle_exception(pe))
//      {
//
//         __post_quit_message(-1);
//
//         pusermessage->m_lresult = -1;
//
//      }
//
//   }
//   catch (...)
//   {
//
//      TRACE("application::process_window_message : ::extended::status processing window message (...)");
//
//   }
//
//}


bool thread::defer_pump_message()
{

   if (peek_message(&m_message, nullptr, 0, 0, PM_REMOVE))
   {

      if(m_message.m_id == e_message_quit)
      {

         ::output_debug_string("\n\n\nthread::defer_pump_message (1) quitting (wm_quit? {PeekMessage->message : " + __str(m_message.m_id == e_message_quit ? 1 : 0) + "!}) : " + string(type_name()) + " (" + __str((u64)::get_current_ithread()) + ")\n\n\n");

         return false;

      }

      process_message();

      return true;

   }

   return false;

}


::e_status thread::on_thread_on_idle(thread *pimpl, ::i32 lCount)
{

   return ::success;

}


::user::primitive * thread::get_active_user_primitive()
{

   return m_puserprimitiveActive;

}


void thread::set_active_user_primitive(::user::primitive * puserprimitive)
{

   m_puserprimitiveActive = puserprimitive;

}


void thread::Delete()
{


   release();

}


void thread::kick_idle()
{

   if(m_bThreadClosed)
   {

      return;

   }

   try
   {

      if (task_active())
      {

         if (m_pmq && !m_bClosedMq)
         {

            synchronous_lock synchronouslock(m_pmq->mutex());

            m_pmq->m_bKickIdle = true;

            m_pmq->m_eventNewMessage.SetEvent();

         }
#ifdef WINDOWS_DESKTOP
         else
         {

            ::PostThreadMessage((DWORD) m_itask, WM_KICKIDLE, 0, 0);

         }
#endif

      }

   }
   catch (...)
   {

   }

}


void thread::post_quit()
{

   if (string(type_name()).contains("output_thread"))
   {

      output_debug_string("output_thread ::thread::post_quit");

   }
   else if (string(type_name()).contains("synth_thread"))
   {

      output_debug_string("synth_thread ::thread::post_quit");

   }
   else if (string(type_name()).contains("audio::out"))
   {

      output_debug_string("out ::thread::post_quit");

   }

   if(m_bThreadClosed)
   {

      return;

   }

   if (m_pmq)
   {

      m_pmq->post_message(nullptr, e_message_quit, 0, 0);

   }

#ifdef WINDOWS_DESKTOP

   try
   {

      if (task_active() && !m_bAuraMessageQueue)
      {

         if (m_bMessageThread)
         {

            post_message(e_message_quit, 0, 0);

         }

      }

   }
   catch (...)
   {

   }

#endif

   // try
   // {

   //    /// this is quite dangerous
   //    synchronous_lock synchronouslock(mutex());

   //    __pointer(manual_reset_event) pev = m_pevSync;

   //    if (pev.is_set())
   //    {

   //       pev->SetEvent();

   //    }

   // }
   // catch (...)
   // {

   // }

   try
   {

      /// this is quite dangerous
      synchronous_lock synchronouslock(mutex());

      __pointer(manual_reset_event) pev = m_pevSleep;

      if (pev.is_set())
      {

         pev->SetEvent();

      }

   }
   catch (...)
   {

   }

}


//::e_status thread::on_finish()
//{
//
//   post_quit();
//
//   auto estatus = ::channel::on_finish();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}


bool thread::post_quit_message(int nExitCode)
{

#ifdef WINDOWS_DESKTOP
   
   ::PostQuitMessage(nExitCode);
   
#else
   
   destroy();
   
#endif

   return true;

}


//::index thread::task_add(::task * ptask)
//{
//
//   try
//   {
//
//      string strType = ptask->type_name();
//
//      if(strType == "user::shell::thread")
//      {
//
//         ::output_debug_string("user::shell::thread");
//
//      }
//
//      synchronous_lock synchronouslock(mutex());
//
//      if (ptask == this)
//      {
//
//         return false;
//
//      }
//
//      if (::is_null(ptask))
//      {
//
//         return false;
//
//      }
//
//      synchronous_lock slChild(ptask->mutex());
//
//      if (::parallelization::is_child(ptask) || ptask->m_pthreadParent)
//      {
//
//         return false;
//
//      }
//
//      if (finish_bit())
//      {
//
//         return false;
//
//      }
//
//      m_ptaska->add(ptask);
//
//      ptask->m_pthreadParent.reset(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(ptask, "thread::thread_add"));
//
//      return true;
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return false;
//
//}


void thread::task_erase(::task * ptask)
{

   try
   {

      string strThreadThis = type_name();

      string strThreadChild = ptask->type_name();

      synchronous_lock synchronouslock(mutex());

      if (::is_null(ptask))
      {

         __throw(error_invalid_argument);

      }

      //synchronous_lock slChild(ptask->mutex());

      //if (!m_pcompositea->contains(ptask) && ptask->thread_parent() != this)
      //{

      //   __throw(error_invalid_argument, "thread is no parent-child releationship between the threads");

      //}

      ///ptask->m_pobjectParent.release();

      //m_pcompositea->erase(ptask);

      if (finish_bit())
      {

         if (strThreadThis == "veriwell_keyboard::application")
         {

            output_debug_string("veriwell_keyboard::application");

         }

         destroy();

      }

   }
   catch (...)
   {


   }

}


::e_status thread::destroy()
{

   call_routine(DESTROY_ROUTINE);

   string strType = type_name();

   if (m_strTaskName.contains("main_frame"))
   {

      output_debug_string("I am main_frame xxpost_quit at " + strType + "\n");

   }

   if (::str::begins(strType, "user::"))
   {

      if (strType.contains("shell_thread"))
      {

         output_debug_string("I am shell_thread xxpost_quit at " + strType + "\n");

      }

   }
   else if (::str::begins(strType, "multimedia::"))
   {

      if (strType.contains("wave_player"))
      {

         output_debug_string("I am wave_player xxpost_quit from wave_player\n");

      }
      else if (strType.ends_ci("out"))
      {

         output_debug_string("I am out xxpost_quit from out\n");

      }
      else if (strType.contains("output_thread"))
      {

         output_debug_string("I am output xxpost_quit from output_thread\n");

      }
      else if (strType.contains("synth_thread"))
      {

         output_debug_string("I am synth_thread xxpost_quit from synth_thread\n");

      }
      else if (strType == "multimedia::audio_core_audio::out")
      {

         ::output_debug_string("I am audio_core_audio::out xxpost_quit from multimedia::audio_core_audio::out\n");

      }
      else if (strType == "multimedia::audio::out")
      {

         ::output_debug_string("I am audio::out xxpost_quit from multimedia::audio::out\n");

      }
      else if (strType == "multimedia::wave::player")
      {

         ::output_debug_string("I am wave::player xxpost_quit from multimedia::wave::player\n");

      }
      else
      {

         ::output_debug_string("I am multimedia:: xxpost_quit from multimedia::*\n");

      }

   }
   else if (strType == "::apex::system")
   {

      ::output_debug_string("I am system xxpost_quit from ::apex::system\n");

   }

   ::channel::destroy();

   auto pobject = this;

   if(pobject)
   {

      auto estatus = pobject->release_composite2(this);

      if(!estatus)
      {

         output_debug_string("release_composite2 failed");

      }

   }

   return ::success;

}


bool thread::task_get_run() const
{

   if (((::thread *) this)->check_tasks_finished())
   {

      return true;

   }

   if (m_bMessageThread)
   {

      if (m_pmq)
      {

         if (m_pmq->m_messagea.has_element())
         {

            return true;

         }

      }

      return !m_bSetFinish;

   }
   else
   {

      auto bSetFinish = m_bSetFinish;

      auto bDestroying = m_bDestroying;

      return !bSetFinish;

   }

}


void thread::message_queue_message_handler(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}


// if you do not want to allow shutdown, return false
// it is a good practice to prompt for an question related to shutdown or at least a excuse, or even a exception,
// otherwise, shutdown command will be silently ignored
// you can call this function if you will shutdown in other way, for example IDEE ::ExitProcess for Microsoft (TM) Corporation Windows (TM)
// besides thread(task) base defined, can be overriden, in application/session/system/platform
bool thread::on_before_shutdown()
{

   return true;

}


void thread::shutdown(bool bPrompt)
{

   if(bPrompt)
   {

      if(!on_before_shutdown())
      {

         return;

      }

   }

}


bool thread::is_application() const
{

   return false;

}


bool thread::is_session() const
{

   return false;

}


bool thread::is_system() const
{

   return false;

}


u32 __thread_entry(void * p);


::e_status thread::initialize(::object * pobject)
{

   auto estatus = ::channel::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   //if (::is_set(pobject))
   //{

   //   auto pthreadContext = dynamic_cast<::thread *>(pobject);

   //   if (pthreadContext)
   //   {

   //      set_context_thread(pthreadContext);

   //   }

   //}

   thread_common_construct();

   return estatus;

}


::e_status thread::main()
{

   ::u32 u = -1;

   ::e_status estatus = error_failed;

   ::e_status estatusOs = error_failed;

   ::e_status estatusStart = error_failed;

   {

      estatusOs = osthread_init();

      if (::succeeded(estatusOs))
      {

         estatusStart = __thread_init();

      }

   }

   if (::succeeded(estatusStart))
   {

      if (m_peventStarted.is_set())
      {

         m_peventStarted->set_event();

         m_peventStarted.release();

      }

      estatus = run();

      m_bThreadClosed = true;

      try
      {

         if (m_peventReady)
         {

            m_peventReady->SetEvent();

         }

      }
      catch (...)
      {

      }

   }

   if (::succeeded(estatusOs))
   {

      destroy_tasks();

      __thread_term();

      osthread_term();

   }

//#if OBJECT_REFERENCE_COUNT_DEBUG
//
//   //release(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, nullptr));
//
//   //try
//   //{
//
//   //   if (m_countReference > 1)
//   //   {
//
//   //      __check_pending_releases(this);
//
//   //   }
//
//   //}
//   //catch (...)
//   //{
//
//   //}
//
//#endif

   m_htask = nullptr;

   m_bIsRunning = false;

   return estatus;

}


//void thread::construct(thread_procedure routine, thread_parameter parameter)
//{
//
//   CommonConstruct();
//
//   m_routine = routine;
//
//   m_parameter = parameter;
//
//}






::e_status thread::init_thread()
{

   if (get_application() && get_application() != this)
   {

      try
      {

         get_application()->add_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(get_application()));

         m_idContextReference = id_application;

      }
      catch (...)
      {

      }

   }

   if(m_idContextReference == id_none && get_session() && get_session() != this)
   {

      try
      {

         get_session()->add_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(get_session()));

         m_idContextReference = id_session;

      }
      catch (...)
      {

      }

   }

   auto psystem = get_system()->m_papexsystem;

   if (m_idContextReference == id_none && psystem && psystem != this)
   {

      try
      {

         psystem->add_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(psystem));

         m_idContextReference = id_system;

      }
      catch (...)
      {

      }

   }

   if (m_idContextReference == id_none && get_task() && get_task() != this)
   {

      try
      {

         get_task()->add_reference(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(get_context_thread()));

         m_idContextReference = id_thread;

      }
      catch (...)
      {

      }

   }

   return true;

}


::e_status thread::on_pre_run_thread()
{

   return true;

}


void thread::dispatch_thread_message(::message::message * pusermessage)
{

   route_message(pusermessage);

}

//
//void thread::wait()
//{
//
//   wait(::duration::infinite());
//
//}


//synchronization_result thread::wait(const duration & duration)
//{
//
//   itask_t itask = m_itask;
//
//   try
//   {
//
//#if defined(WINDOWS)
//
//      ::u32 timeout = duration.u32_millis();
//
//      htask_t htask = m_htask;
//
//      if (htask == NULL || htask == INVALID_HANDLE_VALUE)
//      {
//
//         return e_synchronization_result_error;
//
//      }
//
//      auto windowsWaitResult = ::WaitForSingleObject(htask, timeout);
//
//      return windows_wait_result_to_synchronization_result(windowsWaitResult);
//
//#else
//
//      if(duration.is_pos_infinity())
//      {
//
//         while(is_task_on(itask))
//         {
//
//            sleep(100_ms);
//
//         }
//
//      }
//      else
//      {
//
//         auto millisDelay = duration.millis();
//
//         auto dwStep = minimum(maximum(millisDelay / 10, 1), 100);
//
//         while(is_thread_on(itask))
//         {
//
//            sleep(dwStep);
//
//         }
//
//      }
//
//#endif
//
//   }
//   catch(...)
//   {
//
//
//   }
//
//   return get_system()->is_task_on(itask) ?
//          synchronization_result(e_synchronization_result_timed_out) :
//          synchronization_result(e_synchronization_result_signaled_base);
//
//}


void thread::pre_translate_message(::message::message * pmessage)
{


}


void thread::app_pre_translate_message(::message::message * pmessage)
{

   try
   {

      if(get_application() != nullptr && !get_application()->is_system() && !get_application()->is_session())
      {

         get_application()->pre_translate_message(pmessage);

         if(pmessage->m_bRet)
         {

            return;

         }

      }

   }
   catch(...)
   {

   }

}


void thread::session_pre_translate_message(::message::message * pmessage)
{

   try
   {

      if(get_application() != nullptr)
      {

         if(get_application()->get_session() != nullptr)
         {

            get_application()->get_session()->pre_translate_message(pmessage);

            if(pmessage->m_bRet)
            {

               return;

            }

         }

      }

   }
   catch(...)
   {

   }

}


void thread::system_pre_translate_message(::message::message * pmessage)
{

   try
   {

      auto psystem = get_system()->m_papexsystem;

      if(psystem != nullptr)
      {

         psystem->pre_translate_message(pmessage);

         if(pmessage->m_bRet)
         {

            return;

         }

      }

   }
   catch(...)
   {

   }

}


void thread::process_window_procedure_exception(const ::exception::exception & e,::message::message * pmessage)
{

   if(pmessage->m_id == e_message_create)
   {

      pmessage->m_lresult = -1;

   }
   else if(pmessage->m_id == e_message_paint)
   {

      // force validation of interaction_impl to prevent getting e_message_paint again

#ifdef WIDOWSEX
      ValidateRect(pusermessage->m_puserinteraction->get_safe_handle(),nullptr);
#endif

      pmessage->m_lresult = 0;

   }

}


void thread::process_message_filter(i32 code,::message::message * pmessage)
{

   get_application()->process_message_filter(code,pmessage);

}





//thread_startup::thread_startup(::object * pobject) :
//   ::object(pobject)
//{
//
//}
//
//
//thread_startup::~thread_startup()
//{
//
//}


#ifdef WINDOWS_DESKTOP

size_t engine_symbol(char * sz, int n, DWORD_PTR * pdisplacement, DWORD_PTR dwAddress);

#endif

//thread_startup * thread::startup()
//{
//
//   if(m_htask != nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   if (m_pstartup.is_null())
//   {
//
//      m_pstartup = __new(thread_startup);
//
//   }
//
//   return m_pstartup;
//
//}


e_status thread::begin_thread(bool bSynchInitialization, ::e_priority epriority, ::u32 nStackSize, u32 uiCreateFlags ARG_SEC_ATTRS)
{

   clear_finish_bit();

   ENSURE(m_htask == (htask_t) nullptr);

   //if(m_id.is_empty())
   //{

   //   m_id = type_name();

   //}

//#ifdef __DEBUG
//
//   string strId = m_id;
//
//   if (strId.contains_ci("forking_thread"))
//   {
//
//#if 0
//
//#ifdef WINDOWS_DESKTOP
//
//      ::exception::engine().reset();
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
//      __zero(sz);
//
//      engine_symbol(sz, sizeof(sz), &dwDisplacement, uia[5]);
//
//      u32 uiLine = 0;
//
//      {
//         critical_section_lock csl(&::exception::engine().m_criticalsection);
//
//         engine_fileline(uia[5], 0, 0, &uiLine, nullptr);
//
//      }
//
//      strId =  string(sz) + "(" + __str(uiLine) + ") :: forking_thread";
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
   auto pobject = this;

   if (::is_set(pobject) && pobject != this)
   {

      pobject->add_composite(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

   }

   if (bSynchInitialization)
   {

      m_peventInitialization = __new(manual_reset_event());

   }

   auto estatus = branch(epriority, nStackSize, uiCreateFlags);

   if(m_htask == 0)
   {

      if (::is_set(this))
      {

         this->release_reference(this);

      }

      decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

      return estatus;

   }

#ifndef WINDOWS

   if(pthread_equal((pthread_t) m_htask, (pthread_t) m_itask))
   {

      INFO("create_thread success");

   }

#endif

   if (m_peventInitialization)
   {

      m_peventInitialization->wait();

      ::e_status estatus = get_result_status();

      if (failed(estatus))
      {

         ::e_status estatusExit;

         if(m_result.get_exit_status(estatusExit))
         {

            __rethrow(estatusExit);

         }

         return estatus;

      }

   }

   return ::success;

}



::e_status thread::branch(::e_priority epriority, ::u32 nStackSize, u32 uiCreateFlags ARG_SEC_ATTRS)
{

   auto estatus = task::branch(epriority, nStackSize, uiCreateFlags ADD_PARAM_SEC_ATTRS);

   if(!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status thread::begin_synch(::e_priority epriority, ::u32 nStackSize, u32 uiCreateFlags ARG_SEC_ATTRS)
{

   auto estatus = begin_thread(true, epriority, nStackSize, uiCreateFlags ADD_PARAM_SEC_ATTRS);

   if(!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status thread::inline_init()
{

   set_current_handles();

   ::e_status estatus = __thread_init();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status thread::inline_term()
{

   ::e_status estatus = ::error_none;

   try
   {

      estatus = __thread_term();

   }
   catch (...)
   {

      estatus = ::error_exception;

   }

   return estatus;

}


htask_t thread::get_hthread() const
{

   return m_htask;

}


itask_t thread::get_ithread() const
{

   return m_itask;

}


bool thread::task_active() const
{

   return !m_bThreadClosed && m_htask != (htask_t)0;

}


void thread::set_current_handles()
{

#ifdef WINDOWS_DESKTOP

   m_htask = duplicate_handle(::get_current_hthread());

#else

   m_htask = ::get_current_hthread();

#endif

   m_itask = ::get_current_ithread();

}


iptr thread::item() const
{

   return (iptr)m_htask;

}


void thread::__priority_and_affinity()
{

   if (m_uThreadAffinityMask != 0)
   {

#if defined(WINDOWS_DESKTOP) || defined(LINUX)

      int_bool bOk = ::SetThreadAffinityMask(m_htask, (unsigned int) m_uThreadAffinityMask) != 0;

      if (bOk)
      {

         //output_debug_string("successfully set thread affinity mask");

      }
      else
      {

         output_debug_string("failed to set thread affinity mask");

      }

#endif

   }

   if (m_epriority != priority_normal)
   {

      set_thread_priority(m_epriority);

   }

}


void thread::__os_initialize()
{

//#ifdef WINDOWS_DESKTOP
//
//   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &m_htask, 0, false, DUPLICATE_SAME_ACCESS);
//
//#else
//
//   m_htask = ::get_current_hthread();
//
//#endif
//
//   m_uThread = ::get_current_ithread();

   try
   {

      __priority_and_affinity();

   }
   catch (...)
   {

      // affinity isn't critical

   }

#ifndef WINDOWS

   INFO("init_thread : %s", type_name());

#endif

   //m_psystem->m_papexsystem->m_papexnode->node_thread_initialize(this);


}


void thread::__os_finalize()
{

   //m_psystem->m_papexsystem->m_papexnode->node_thread_finalize(this);

}


//::object* thread::calc_parent_thread()
//{
//
//   return ::parallelization::calc_parent(this);
//
//}


::e_status thread::osthread_init()
{

   set_current_handles();

   m_bDedicated = true;

   if (finish_bit())
   {

      clear_finish_bit();

   }

#ifdef WINDOWS_DESKTOP

   if (m_bMessageThread)
   {

      if (string(type_name()).contains_ci("out"))
      {

         output_debug_string("out");

      }

      MSG message = {};

      ::PeekMessage(&message, NULL, WM_USER, WM_USER, PM_NOREMOVE);

   }

#endif

   m_estatus = ::success;

   __set_thread_on();

   //{

   //   auto pthreadParent = ::parallelization::calc_parent(this);

   //   if (pthreadParent)
   //   {

   //      if (!pthreadParent->task_add(this))
   //      {

   //         if (pthreadParent->m_id.begins_ci("predicate_thread") && m_id.begins_ci("predicate_thread"))
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

      ::set_task(this OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      processor_cache_oriented_set_thread_memory_pool(0); // set default handler cache oriented thread memory pool index to 0 ("zero") (The First One)

      //m_psystem->m_papexsystem->m_papexnode->parallelization_initialize();

   }

   try
   {

      __os_initialize();

   }
   catch (const ::exception::exception & e)
   {

      m_estatus = e.m_estatus;

      if (succeeded(m_estatus))
      {

         m_estatus = error_failed;

      }

      m_result.add(e);

      top_handle_exception(e);

   }
   catch (...)
   {

      m_estatus = error_failed;

      m_result.add(error_failed);

   }

   return m_estatus;

}


void thread::__set_thread_on()
{

   //SetCurrentHandles();

   //auto id = ::get_current_ithread();

   //::parallelization::task_register(m_itask, this);

   //task_register();

   register_task();


   // apex commented
   //if (g_axisoninitthread)
   //{

   //   g_axisoninitthread();

   //}

   if (!on_init_thread())
   {

      m_estatus = error_failed;

      return;

   }


}


void thread::__set_thread_off()
{

   try
   {

      // apex commented
      //if (g_axisontermthread)
      //{

      //   g_axisontermthread();

      //}

      on_term_thread();

   }
   catch (...)
   {

   }

   ::thread * pthread = this;

   //::parallelization::task_unregister(m_itask, pthread);

   //unregister_task();

   unregister_task();

   auto id = ::get_current_ithread();

   get_system()->set_task_off(::get_current_ithread());

   //::set_task(nullptr);

}

//
//::e_status thread::__thread_main()
//{
//
//   auto estatus = main();
//
//
//}


bool thread::is_idle_message(::message::message * pmessage)
{

   return ::message::is_idle_message(pmessage);

}


bool thread::is_idle_message()
{

   return ::message::is_idle_message(&m_message);

}


namespace apex
{


   void system::post_quit_to_all_threads()
   {

      //::parallelization::post_quit_to_all_threads();

   }



   void system::post_to_all_threads(const ::id& id, wparam wparam, lparam lparam)
   {

//#ifdef _DEBUG
//
//      if (id == e_message_quit)
//      {
//
//         //!!for e_message_quit please use post_quit_to_all_threads;
//         __throw(error_invalid_argument);
//
//      }
//
//#endif

      //for e_message_quit please use post_quit_to_all_threads;
      //if(id == e_message_quit)
      //{

      //   ::parallelization::post_quit_to_all_threads();

      //   return;

      //}

//      auto psystem = m_psystem->m_papexsystem;
//
//      psystem->m_papexsystem->post_to_all_threads(id, wparam, lparam);

   }


} // namespace apex


bool thread::post_task(const ::routine & routine)
{

   if (!routine)
   {

      return false;

   }

   synchronous_lock synchronouslock(mutex());

   m_routinea.add(routine);

   kick_idle();

   return true;

}


bool thread::send_task(const ::routine & routine, ::duration durationTimeout)
{

   return send_object(e_message_system, e_system_message_method, routine, durationTimeout);

}


bool thread::post_object(const ::id & id, wparam wparam, ::matter * pmatter)
{

   return post_message(id, wparam, pmatter);

}


bool thread::post_message(const ::id & id, wparam wparam, lparam lparam)
{

   if (id.umessage() == e_message_close)
   {

      output_debug_string("thread::post_message e_message_close");

   }

#ifdef WINDOWS_DESKTOP

   if (m_htask && !m_bAuraMessageQueue && m_bMessageThread)
   {

      if (id.umessage() == e_message_quit)
      {

         string strType = type_name();

         if (strType.contains_ci("::application"))
         {

            output_debug_string("application_shouldn't_run?");

            auto bShouldRun = task_get_run();

            if (!bShouldRun)
            {

               output_debug_string("application_shouldn't_run?");

            }

         }
         else if (strType.contains_ci("session"))
         {

            auto bShouldRun = task_get_run();

            if (!bShouldRun)
            {

               output_debug_string("session_shouldn't_run?");

            }

         }
         else if (strType.contains_ci("system"))
         {

            auto bShouldRun = task_get_run();

            if (!bShouldRun)
            {

               output_debug_string("session_shouldn't_run?");

            }

         }

      }

      int_bool bOk = ::PostThreadMessage((DWORD) m_itask, id.umessage(), wparam, lparam) != false;

      if (!bOk)
      {

         TRACELASTERROR();

      }

      return bOk;

   }

#endif

   auto pmessagequeue = get_message_queue();

   if(!pmessagequeue)
   {

      return false;

   }

   return pmessagequeue->post_message(nullptr, id, wparam, lparam);

}


bool thread::send_object(const ::id & id, wparam wparam, ::matter * pmatter, ::duration durWaitStep)
{

   if (!id.is_message())
   {

      __throw(error_invalid_argument);

   }

   if(m_bThreadClosed)
   {

      return false;

   }

   if (id == e_message_quit)
   {

      return false;

   }

   if (m_htask == (htask_t)nullptr || !task_get_run())
   {


      return false;

   }

   send_message(id, wparam, pmatter, durWaitStep);

   return true;

}


bool thread::send_message(const ::id & id, wparam wparam, lparam lparam, ::duration durWaitStep)
{

   if (!id.is_message())
   {

      __throw(error_invalid_argument);

   }

   if(m_bThreadClosed)
   {

      return false;

   }

   if (id == e_message_quit)
   {

      ///wait(durWaitStep);

      return true;

   }

   auto pmessage = __new(::send_thread_message(this));

   pmessage->m_message.m_id = id;
   pmessage->m_message.wParam = wparam;
   pmessage->m_message.lParam = lparam;

   post_message(e_message_system, e_system_message_meta, pmessage);

   pmessage->m_ev.wait(durWaitStep);

   return true;

}


//void thread::set_os_data(void * pvoidOsData)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if(m_bDupHandle)
//   {
//
//      if(m_htask != nullptr)
//      {
//
//         ::CloseHandle(m_htask);
//
//      }
//
//   }
//
//   m_htask = nullptr;
//
//   if(pvoidOsData != nullptr)
//   {
//
//      if(::DuplicateHandle(::GetCurrentProcess(),(HANDLE)pvoidOsData,GetCurrentProcess(),&m_htask,THREAD_ALL_ACCESS,true,0))
//      {
//
//         m_bDupHandle = true;
//
//      }
//      else
//      {
//
//         TRACE("thread::set_os_data failed to duplicate handle");
//
//      }
//
//   }
//
//#else
//
//   m_htask = (htask_t)pvoidOsData;
//
//#endif
//
//}


//void thread::set_os_int(itask_t itask)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   m_uThread = (::u32) itask;
//
//#else
//
//   m_uThread = (itask_t) itask;
//
//#endif
//
//}


::e_status thread::__thread_init()
{

   m_estatus = on_thread_init();

   if (m_peventInitialization)
   {

      m_peventInitialization->set_event();

   }
   
   m_result = m_estatus;

   return m_estatus;

}


::e_status thread::on_thread_init()
{

   init_task();

   install_message_routing(this);

   ::e_status estatus = ::success;

   try
   {

      estatus = init_thread();
      
      if(!estatus)
      {

         if (m_peventStarted)
         {

            m_peventStarted.release();

         }

         return estatus;

      }

   }
   catch (const ::exception::exception & e)
   {

      handle_exception(e);

      return e.m_estatus;

   }
   catch(...)
   {

      return error_exception;

   }

   try
   {

      estatus = on_pre_run_thread();
      
      if(!estatus)
      {

         return estatus;

      }

   }
   catch (const ::exception::exception & e)
   {

      handle_exception(e);

      return e.m_estatus;

   }
   catch (...)
   {

      return error_exception;

   }

   return estatus;
   
}


//::e_status thread::main()
//{
//
//   string strType = type_name();
//
//   if(strType.contains("wave_player"))
//   {
//
//      output_debug_string("I am xxthread::main from wave_player");
//
//   }
//   else if(strType.ends_ci("out"))
//   {
//
//      output_debug_string("I am xxthread::main from out");
//
//   }
//   else if(strType.contains("output_thread"))
//   {
//
//      output_debug_string("I am xxthread::main from output_thread");
//
//   }
//
//   // first -- check for simple worker thread
//   ::e_status estatus = ::success;
//
//   // else check for thread with message loop
//   ASSERT_VALID(this);
//
//   try
//   {
//
//      m_bReady = true;
//
//      run();
//
//   }
//   catch (const ::exit_exception & e)
//   {
//
//      e.m_ptaskExit->finish();
//      //if (___thread(e.m_pthreadExit) != this)
//      //{
//
//      //   psystem->finish(psystem);
//
//      //}
//
//      //::release(pe);
//
//   }
//   catch (const ::exception::exception & e)
//   {
//
//      top_handle_exception(e);
//
//   }
//   catch(...)
//   {
//
//      output_debug_string("exception occurred");
//
//   }
//
//   if(strType.contains("wave_player"))
//   {
//
//      output_debug_string("after run xxthread::main from wave_player");
//
//   }
//   else if(strType.ends_ci("out"))
//   {
//
//      output_debug_string("after run xxthread::main from out");
//
//   }
//   else if(strType.contains("output_thread"))
//   {
//
//      output_debug_string("after run xxthread::main from output_thread");
//
//   }
//
//   estatus = m_result.estatus();
//
//   //clear_finish_bit();
//
//   return estatus;
//
//}


message_queue* thread::_get_mq()
{

   synchronous_lock synchronouslock(mutex());

   if(m_bSetFinish || m_bThreadClosed)
   {

      if (m_pmq)
      {

         __release(m_pmq);

      }

      return nullptr;

   }

   if (m_pmq)
   {

      return m_pmq;

   }
   
   if(m_itask == 0)
   {
      
      return nullptr;
      
   }

   auto pmq = ::get_message_queue(m_itask, true);

   if(pmq->m_bQuit)
   {

      output_debug_string("WHAT?!?!WHAT?!?!WHAT?!?!BornQuitting?!?!");

   }

   auto estatus = __compose(m_pmq, pmq);

   if (!estatus)
   {

      return nullptr;

   }

   return m_pmq;

}


int_bool thread::peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg)
{

   if (m_pmq)
   {

      if (m_pmq->peek_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
      {

         return true;

      }

   }

#ifdef WINDOWS_DESKTOP

   if (m_htask && !m_bAuraMessageQueue)
   {
      
      MSG msg;

      if (::PeekMessage(&msg, __hwnd(oswindow), wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
      {

         return true;

      }

      copy(pMsg, &msg);

   }

#endif

   return false;

}


//::e_status thread::finish()
//{
//
//
//   //set_finish_bit();
//
//   //auto estatus = channel::set_finish();
//
//   //if (!estatus)
//   //{
//
//   //   return false;
//
//   //}
//
//   //if (task_active())
//   //{
//
//   //   if (::is_set(pcontextobjectFinish))
//   //   {
//
//   //      notify_array().add_unique(pcontextobjectFinish);
//
//   //   }
//
//   //   post_quit();
//
//   //   return error_pending;
//
//   //}
//
//   //return success;
//
////   auto estatus = set_finish_composites();
////
////   if (estatus == error_pending)
////   {
////
////      return error_pending;
////
////   }
////
////   if (!finish_bit())
////   {
////
////      m_bitFinishing = true;
////
////      set_finish_bit();
////
////   }
////
////   if (m_bitFinishing)
////   {
////
////      string strTypeName = type_name();
////
////#ifdef ANDROID
////
////      demangle(strTypeName);
////
////#endif
////
////      if (strTypeName == "user::shell")
////      {
////
////         output_debug_string("user::shell::finish");
////
////      }
////      else if (strTypeName == "apex::system")
////      {
////
////         output_debug_string("apex::system::finish");
////
////      }
////
////      estatus = set_finish_composites();
////
////      if (strTypeName.contains_ci("app_app::window"))
////      {
////
////         output_debug_string("set_finish at app_window");
////
////      }
////
////      //if (m_ptaska)
////      //{
////
////      //task_set_finish:
////
////      //   ::count countTask = m_ptaska->get_count();
////
////      //   for (::index iTask = 0; m_ptaska && iTask < countTask; iTask++)
////      //   {
////
////      //      auto & ptask = m_ptaska->element_at(iTask);
////
////      //      synchronouslock.unlock();
////
////      //      auto estatus = ptask->finish();
////
////      //      if (estatus == ::error_pending)
////      //      {
////
////      //         bStillFinishingTasks = true;
////
////      //      }
////
////      //      synchronouslock.lock();
////
////      //      if (countTask != m_ptaska->get_count())
////      //      {
////
////      //         goto task_set_finish;
////
////      //      }
////
////      //   }
////
////      //}
////
////      //if (bStillFinishingComposites || bStillFinishingTasks)
////
////      if (estatus == ::error_pending)
////      {
////
////         if (m_pcompositea)
////         {
////
////            auto compositea = *m_pcompositea;
////
////            string strWaiting;
////
////            for (auto & pcomposite : compositea)
////            {
////
////               try
////               {
////
////                  string strThreadType;
////
////                  strThreadType = pcomposite->type_name();
////
////                  strWaiting += strThreadType;
////
////                  strWaiting += "\r\n";
////
////                  pcomposite->finish();
////
////               }
////               catch (...)
////               {
////
////               }
////
////            }
////
////            if (strWaiting.has_char())
////            {
////
////               TRACE("The thread %s is waiting for the following threads to finish:\r\n%s", type_name(), strWaiting.c_str());
////
////            }
////
////         }
////
////         kick_idle();
////
////      }
////      else
////      {
////
////
////         string strType = type_name();
////
////         if (strType.contains_ci("session"))
////         {
////
////            auto bShouldRun = task_get_run();
////
////            if (!bShouldRun)
////            {
////
////               output_debug_string("session_shouldn't_run?");
////
////            }
////
////         }
////         else if (strType.contains_ci("application"))
////         {
////
////            auto bShouldRun = task_get_run();
////
////            if (!bShouldRun)
////            {
////
////               output_debug_string("application_shouldn't_run?");
////
////            }
////
////
////         }
////
////         m_bitFinishing = false;
////
////      }
////
////}
////
////   return estatus;
////
//
//}


//void thread::update_task_ready_to_quit()
//{
//
//   ::e_status estatus = ::success;
//
//   synchronous_lock synchronouslock(mutex());
//
//   string strTypeName = type_name();
//
//   bool bReadyToQuit = true;
//
//   if (m_pcompositea)
//   {
//
//      for (auto& pmatter : *m_pcompositea)
//      {
//
//         if (pmatter->m_bTaskPending)
//         {
//
//            bReadyToQuit = false;
//
//         }
//
//      }
//
//   }
//
//   if (bReadyToQuit)
//   {
//
//      m_bTaskPending = false;
//
//   }
//
//   //return estatus;
//
//}


//::e_status thread::set_finish_composites(::property_object * pcontextobjectFinish)
//{
//
//   auto estatus = channel::set_finish_composites(pcontextobjectFinish);
//
//   if (estatus == error_pending)
//   {
//
//      return estatus;
//
//   }
//
//   if (task_active())
//   {
//
//      set_finish_bit();
//
//      if (m_bMessageThread)
//      {
//
//         post_quit();
//
//         return error_pending;
//
//      }
//      else
//      {
//
//         ::output_debug_string("!m_bMessageThread");
//
//      }
//
//   }
//
//   return ::success;
//
//}





int_bool thread::get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
{

   bool bQuit = false;

#ifdef WINDOWS_DESKTOP

   if (m_bAuraMessageQueue)
   {

      if (!get_message_queue()->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax))
      {

         if (!finish_bit())
         {

            destroy();

         }

         return false;

      }

      return true;

   }

   if (m_pmq)
   {

      if (m_pmq->peek_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, true))
      {

         set_finish_bit();

         bQuit = pMsg->m_id == e_message_quit;

         if (!bQuit)
         {

            return true;

         }

         __release(m_pmq);

      }

   }

   if (m_htask)
   {

      MSG msg;

      int iRet = -1;
      
      //if (m_bSetFinish)
      //{

      //   while(iRet = ::PeekMessage(&msg, __hwnd(oswindow), wMsgFilterMin, wMsgFilterMax, TRUE))
      //   {

      //      if (msg.message == e_message_quit)
      //      {

      //         break;

      //      }

      //      if (!task_get_run())
      //      {

      //         return false;

      //      }

      //      update_task_ready_to_quit();

      //   }

      //}
      //else
      //{

      if (m_bSetFinish)
      {

         DWORD timeout = 100; // 100 milliseconds;

         while (MsgWaitForMultipleObjects(0, NULL, FALSE, timeout, QS_ALLINPUT) != WAIT_OBJECT_0)
         {

            if (is_ready_to_quit())
            {

               bQuit = true;

               break;

            }

         }

      }

      if(!bQuit)
      {

         iRet = ::GetMessage(&msg, __hwnd(oswindow), wMsgFilterMin, wMsgFilterMax);

         //}

         if (msg.message == e_message_quit)
         {

            ::output_debug_string("e_message_quit");

         }

         copy(pMsg, &msg);

         if (iRet == -1)
         {

            ::u32 dwLastError = ::GetLastError();

            ::output_debug_string("Last Error : " + __str(dwLastError) + "\n");

         }
         else
         {

            bQuit = !iRet || pMsg->m_id == e_message_quit;

            if (bQuit)
            {

               ::output_debug_string("received e_message_quit");

            }
            else
            {

               return true;

            }

         }

      }

   }

#else

   auto pmq = get_message_queue();

   ::duration duration;

   if(m_bSetFinish)
   {

      duration = 100_ms;

   }
   else
   {

      duration = duration::infinite();

   }

   int iRet;

   while((iRet = pmq->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, duration)) != 0)
   {

      if (iRet > 0)
      {

         return true;

      }

      if(is_ready_to_quit())
      {

         break;

      }

   }

#endif

   return false;

}


int_bool thread::post_message(oswindow oswindow, const ::id & id, wparam wparam, lparam lparam)
{

   if (!id.is_message())
   {

      __throw(error_invalid_argument);

   }

   if(m_bThreadClosed)
   {

      return false;

   }

#ifdef WINDOWS_DESKTOP

   if (m_htask && !m_bAuraMessageQueue)
   {

      if (::PostMessage(__hwnd(oswindow), id.u32(), wparam, lparam))
      {

         return true;

      }

   }

#endif

   return get_message_queue()->post_message(oswindow, id, wparam, lparam);

}


void thread::assert_valid() const
{

   channel::assert_valid();

}


void thread::dump(dump_context & dumpcontext) const
{

   channel::dump(dumpcontext);

}


void thread::add_task(::object* pobjectTask)
{

   ::object::add_task(pobjectTask);

}


::e_status thread::__thread_term()
{

   return on_thread_term();

}


::e_status thread::on_thread_term()
{

   {

      synchronous_lock synchronouslock(m_pmutexThreadUiPtra);

      if (::is_set(m_puiptraThread))
      {

         m_puiptraThread->erase_all();

      }

   }

   try
   {

      on_pos_run_thread();

   }
   catch (...)
   {

      m_result.add(error_failed);

   }

   try
   {

      term_thread();

   }
   catch (...)
   {

      m_result.add(error_failed);

   }

   return ::error_failed;

}


thread::operator htask_t() const
{

   return is_null(this) ? (htask_t) nullptr : m_htask;

}


bool thread::initialize_message_queue()
{

   //if(m_spuiptra.is_null())
   //{

   //   m_spuiptra = __new(ref_array < ::user::primitive >);

   //}

   //if(m_spqueue.is_null())
   //{

   //   m_spqueue.create(this);

   //}

   //if(m_spqueue.is_null())
   //{

   //   return false;

   //}

   //if(!m_spqueue->message_queue_is_initialized())
   //{

   //   try
   //   {

   //      if(!m_spqueue->create_message_queue("",this))
   //      {

   //         return false;

   //      }

   //   }
   //   catch(...)
   //   {

   //      return false;

   //   }

   //}


   //single_lock synchronouslock(&m_sptimera->m_mutex,true);

   //i32 iMin = 100;

   //for(i32 i = 0; i < m_sptimera->m_timera.get_count(); i++)
   //{

   //   if(m_sptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
   //   {

   //      iMin = m_sptimera->m_timera.element_at(i)->m_uiElapse;

   //   }

   //}

   //synchronouslock.unlock();

   //m_spqueue->message_queue_set_timer((uptr)-2,iMin);

   return true;

}


void thread::message_handler(::message::message * pmessage)
{

   pre_translate_message(pmessage);

   route_message(pmessage);

}


::e_status thread::process_message()
{

   try
   {

      MESSAGE & message = m_message;

#ifdef WINDOWS_DESKTOP

      if (message.oswindow != nullptr || message.m_id == e_message_timer)
      {

         MSG msg;

         copy(&msg, &message);

         ::TranslateMessage(&msg);

         ::DispatchMessage(&msg);

         return true;

      }

#endif

      if (message.m_id == e_message_event2)
      {

         //if(msg.lParam)
         {

            auto psystem = m_psystem->m_papexsystem;

            auto psubject = psystem->new_subject(message);

            handle_subject(psubject);

         }
         //else
         //{

         //   apply((const __id &)(::iptr) msg.wParam);

         //}

      }
      else if (message.m_id == e_message_system)
      {

         if (message.wParam == e_system_message_create)
         {

            __pointer(::create) pcreate((lparam)message.lParam);

            if (pcreate.is_set())
            {

               call_request(pcreate);

            }

         }
         else if (message.wParam == e_system_message_method)
         {

            const ::routine & routine(message.lParam);

            routine();

         }
         //else if (msg.wParam == system_message_runnable)
         //{

         //   __pointer(::object) pobjectTask((lparam)msg.lParam);

         //   pobjectTask->call();

         //}
         else if (message.wParam == e_system_message_meta)
         {

            __pointer(::send_thread_message) pmessage(message.lParam);

            m_message = pmessage->m_message;

            process_message();

            pmessage->m_ev.set_event();

         }
         else
         {

         }

         return true;

      }

      if(m_nDisablePumpCount != 0)
      {

         TRACE(trace_category_appmsg, e_trace_level_error,"Error: thread::pump_message called when not permitted.\n");

      }

      if(message.m_id == WM_KICKIDLE)
      {

         return true;

      }

      __pointer(::message::message) pmessage;

      if (get_application())
      {

         pmessage = get_application()->get_message(&message);

      }
      else if(get_session())
      {

         pmessage = get_session()->get_message(&message);

      }

      if(pmessage)
      {

         process_message(pmessage);

      }

      return true;

   }
   catch (const ::exception::exception & e)
   {

      if (handle_exception(e))
      {

         return true;

      }

   }
   catch(...)
   {

   }

   return false;

}


//::e_status thread::process_base_message(::message::message * pmessage)
//{
//
//   message_handler(pmessage);
//
//   return true;
//
//}


::e_status thread::raw_process_message()
{

   try
   {

      ___pointer < ::message::message > pmessage;

      pmessage = get_message(&m_message);

      if (pmessage)
      {

         route_message(pmessage);

      }

      return true;

   }
   catch (const ::exception::exception & e)
   {

      if (handle_exception(e))
      {

         return true;

      }

   }
   catch (...)
   {

   }

   return false;

}



bool thread::set_thread_priority(::e_priority epriority)
{

   i32 nPriority = get_os_thread_priority(epriority);

   bool bOk = ::SetThreadPriority(m_htask, nPriority) != false;

   if (!bOk)
   {

      ::e_status estatus = ::get_last_status();

      output_debug_string("thread::SetThreadPriority LastError = " + __str(estatus));

   }

   m_epriority = thread_priority();

   return bOk;

}


::e_priority thread::thread_priority()
{

   ASSERT(m_htask != null_hthread);

   i32 nPriority = ::GetThreadPriority(m_htask);

   ::e_priority epriority = ::get_os_thread_scheduling_priority(nPriority);

   return epriority;

}


//void thread::thread_delete()
//{
//
//   try
//   {
//
//      if(m_pevReady != nullptr)
//      {
//
//         m_pevReady->SetEvent();
//
//      }
//
//   }
//   catch(...)
//   {
//
//   }
//
//   set_os_data(nullptr);
//
//}





//void thread::start()
//{
//
//#if defined (WINDOWS_DESKTOP)
//
//   ::ResumeThread(m_htask);
//
//#endif
//
//}


//u32 thread::ResumeThread()
//{
//
//   ASSERT(m_htask != null_hthread);
//
//#if defined (WINDOWS_DESKTOP)
//
//   return ::ResumeThread(m_htask);
//
//#else
//
//   return 0;
//
//#endif
//
//}


int thread::get_x_window_count() const
{

   return 0;

}


bool thread::do_events()
{

   MESSAGE msg;

   bool bProcessed = false;

   while(peek_message(&msg,nullptr,0,0,PM_NOREMOVE) != false)
   {

      if (msg.m_id == e_message_quit) // do not pump, otherwise main loop will not process the message
      {

         break;

      }

      bProcessed = true;

      if (!pump_message())
      {

         break;

      }

   }

   return bProcessed;

}



///
/// Single step the thread message queue.
/// \author tst Camilo Sasuke Tsumanuma
///

bool thread::kick_thread()
{

   if(m_bThreadClosed)
   {

      return false;

   }

   if (!post_message(e_message_null))
   {

      return false;

   }

   return true;

}







//void thread::_001OnThreadMessage(::message::message * pmessage)
//{
//
//   __pointer(::user::message) pusermessage(pmessage);
//
//
//
//}

//
//::handler * thread::handler()
//{
//
//   return m_phandler;
//
//}


::e_status thread::verb()
{

   return success;

}


void thread::do_request(::create * pcreate)
{

   post_object(e_message_system, e_system_message_create, pcreate);

   //return ::success;

}


//::mutex * g_pmutexThreadOn = nullptr;

//map < itask_t, itask_t, itask_t, itask_t > * g_pmapThreadOn = nullptr;




CLASS_DECL_APEX void forking_count_thread_null_end(int iOrder)
{


}


user_interaction_ptr_array & thread::uiptra()
{

   {

      synchronous_lock synchronouslock(mutex());

      if (m_pmutexThreadUiPtra == nullptr)
      {

         m_pmutexThreadUiPtra = new ::mutex();

      }

   }

   synchronous_lock synchronouslock(m_pmutexThreadUiPtra);

   if (m_puiptraThread == nullptr)
   {

      m_puiptraThread = new ::user_interaction_ptr_array();

   }

   return *m_puiptraThread;

}






u32 g_uiRandomProcessorIndexGenerator = -1;

CLASS_DECL_APEX u32 random_processor_index_generator()
{

   g_uiRandomProcessorIndexGenerator++;

   return g_uiRandomProcessorIndexGenerator;

}




thread_ptra::thread_ptra()
{

}




thread_ptra::~thread_ptra()
{


}


bool thread::pump_sleep(const millis & millis, synchronization_object * psync)
{

   auto iTenths = millis / 100_ms;

   auto millisRemaining = millis % 100_ms;

   while (true)
   {

      ::count cMessage = 0;

      try
      {

         while (has_message())
         {

            while (defer_pump_message());

            cMessage++;

         }

      }
      catch (...)
      {

      }

      if (iTenths <= 0)
      {

         break;

      }

      if (cMessage <= 0)
      {

         sleep(100_ms);

      }

      if (::is_set(psync))
      {

         synchronous_lock synchronouslock(psync);

         if (synchronouslock.wait(::millis()).succeeded())
         {

            break;

         }

      }

      iTenths--;

   }

   sleep(millisRemaining);

   return ::task_get_run();

}




::e_status thread::get_result_status()
{

   return m_result.estatus();

}


//::mutex * g_pmutexThreadDeferredCreation = nullptr;
//
//
//::array < __pointer(thread) > * g_pthreadaDeferredCreate = nullptr;
//
//
//CLASS_DECL_APEX void defer_create_thread(::object * pobject)
//{
//
//   auto pthread = ::get_task();
//
//   if (::is_null(pthread))
//   {
//
//      auto pthreadNew = __object(pobject)->__create_new < ::thread > ();
//
//      pthreadNew->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(pobject, nullptr));
//
//      pthreadNew->clear_finish_bit();
//
//      set_task(pthreadNew);
//
//      synchronous_lock synchronouslock(g_pmutexThreadDeferredCreation);
//
//      g_pthreadaDeferredCreate->add(pthreadNew);
//
//   }
//
//}


void thread::add_waiting_event(event * pevent)
{

   if(::is_null(pevent))
   {

      return;

   }

   synchronous_lock synchronouslock(mutex());

   m_eventaWait.add(pevent);

}


void thread::erase_waiting_event(event * pevent)
{

   synchronous_lock synchronouslock(mutex());

   m_eventaWait.erase(pevent);

}


thread::file_info* thread::get_file_info()
{

   if (m_pfileinfo != nullptr)
   {

      return m_pfileinfo;

   }

   m_pfileinfo = __new(file_info());

   return m_pfileinfo;

}


::u32 thread::get_file_sharing_violation_timeout_total_milliseconds()
{

   return get_file_info()->m_durationFileSharingViolationTimeout.u32_millis();

}


bool thread::is_running() const
{

   return ::task::is_running();

}


//__transport(::task) thread::branch(
//   ::matter * pmatter,
//   ::e_priority epriority,
//   u32 nStackSize,
//   u32 dwCreateFlags ARG_SEC_ATTRS)
//{
//
//   return ::task::branch(pmatter, epriority, nStackSize, dwCreateFlags ADD_PARAM_SEC_ATTRS);
//
//}


::duration thread::set_file_sharing_violation_timeout(::duration duration)
{

   return get_file_info()->m_durationFileSharingViolationTimeout = duration;

}


// please refer to object::finish verses/documentation
// ::user::interaction implements custom/dedicated finish protocol/feature/function
// this is why default finish isn't/(and shouldn't be) called here
// (like is done for a regular object instance of *object* class)
// (look at ::object::delete_this implementation to confirm/study the default finish call)
void thread::delete_this()
{

   object::delete_this();

}




//::e_status thread::destroy()
//{
//
//   auto estatus = set_finish();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   if (::get_task() == this)
//   {
//
//      return ::success;
//
//   }
//
////   while (check_children_task())
////   {
////
////      sleep(100_ms);
////
////      kick_idle();
////
////   }
//
//   return ::success;
//
//}
