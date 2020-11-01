#include "framework.h"
#include "apex/message.h"
#include "apex/update.h"
#include "apex/os/_c.h"
#include "apex/os/_.h"
#include "apex/os/_os.h"
#include "acme/multithreading/mq.h"



CLASS_DECL_ACME mq * get_mq(ITHREAD idthread, bool bCreate);


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

int SetThreadAffinityMask(HTHREAD h, unsigned int dwThreadAffinityMask);

#endif


struct send_thread_message :
   virtual public object
{

   MESSAGE                 m_message;

   manual_reset_event      m_ev;

   send_thread_message(::layered * pobjectContext);

   virtual ~send_thread_message();

};


send_thread_message::send_thread_message(::layered * pobjectContext) :
   ::object(pobjectContext)
{

   xxf_zero(m_message);

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

   set_layer(LAYERED_THREAD, this);

   m_bThreadClosed = false;

   m_bitIsPred = false;

   m_bAuraMessageQueue = false;

#ifdef APEX_MESSAGE_QUEUE

   m_bClosedMq = false;

#endif

   m_bLastingThread = true;

   m_bMessageThread = false;

   m_estatus = ::success_none;

#ifdef MACOS

   m_runloop = nullptr;

#endif

   m_epriority = priority_normal;

   //m_bFork = false;

   m_pmutexThreadUiPtra = nullptr;

   m_puiptraThread = nullptr;

   m_bThreadToolsForIncreasedFps = false;

   m_bTemporary = false;

   m_dwThreadAffinityMask = 0;

   m_tickHeartBeat.Now();

   defer_create_mutex();

   m_bReady = false;

   //m_bitRunThisThread = false;

   m_pevReady = nullptr;

   m_bZipIsDir2 = true;

   m_pslUser = nullptr;

   m_pfileinfo = nullptr;

   m_bDupHandle = false;

   //m_hthread = (HTHREAD) nullptr;

   //m_ithread = 0;

   m_nDisablePumpCount = 0;

   m_bSimpleMessageLoop = true;

#ifdef WINDOWS

   m_bCoInitialize = false;

#endif

   memcnts_inc(this);

}


//CLASS_DECL_APEX ::thread * get_thread_raw();


void thread::thread_common_construct()
{

   m_bDedicated = false;

   if (get_context_application() != nullptr && get_context_application()->get_context_session() != nullptr)
   {

      m_bZipIsDir2 = get_context_application()->get_context_session()->m_bZipIsDir2;

   }

   if (::get_thread() != nullptr)
   {

      m_bitAvoidProcFork = ::get_thread()->m_bitAvoidProcFork;

   }
   else
   {

      m_bitAvoidProcFork = false;

   }

}


thread::~thread()
{

   memcnts_dec(this);

   ::acme::del(m_puiptraThread);

   ::acme::del(m_pmutexThreadUiPtra);

}


HTHREAD thread::get_os_handle() const
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

   channel::on_finish();

   term_task();

   //if (get_context_object())
   //{

     // get_context_object()->release_reference(this OBJ_REF_DBG_COMMA_THIS);

   //}

   if (get_context_application())
   {

      get_context_application()->release_reference(this OBJ_REF_DBG_COMMA_THIS);

   }

   if (get_context_session())
   {

      get_context_session()->release_reference(this OBJ_REF_DBG_COMMA_THIS);

   }

   if (get_context_system())
   {

      System.release_reference(this OBJ_REF_DBG_COMMA_THIS);

   }

   if (get_context_thread())
   {

      get_context_thread()->release_reference(this OBJ_REF_DBG_COMMA_THIS);

   }


   {

      sync_lock sl(mutex());

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


::estatus thread::osthread_term()
{

   ::task::osthread_term();

#ifndef WINDOWS_DESKTOP

   __release(m_pmq);

#endif

   {

      sync_lock sl(mutex());

      if (m_pevSleep.is_set())
      {

         m_pevSleep->SetEvent();

         m_pevSleep.release();

      }

   }

   try
   {

      m_idroute.remove_all();

   }
   catch (...)
   {

   }

   __os_finalize();

   __set_thread_off();

   ::__term_thread();

   ::estatus estatus = m_result.m_estatus;

   return estatus;

}


void thread::on_keep_alive()
{

   m_tickHeartBeat.Now();

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

   //if ((m_tickHeartBeat.elapsed()) > ((5000) * 91))
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

   return ((thread*)this)->peek_message(&msg, nullptr, 0, 0, PM_NOREMOVE) != FALSE;

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


::estatus thread::thread_loop()
{

   while (true)
   {

      if (!thread_get_run())
      {

         string strType = type_name();

         if (strType.contains_ci("session"))
         {

            auto bShouldRun = thread_get_run();

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

               auto bShouldRun = thread_get_run();

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
      catch (::exception_pointer pe)
      {

         if (!handle_exception(pe))
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


::estatus thread::run()
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

   if (m_pmatter)
   {

      m_id = m_pmatter->type_name();

      set_thread_name(m_id);

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

   sync_lock sl(mutex());

   while(thread_get_run())
   {

      if (m_methoda.isEmpty())
      {

         return false;

      }

      auto method = m_methoda.first();

      m_methoda.remove_at(0);

      if (method)
      {

         sl.unlock();

         method();

         return true;

      }

   }

   return false;

}


__pointer(::matter) thread::running(const char * pszTag) const
{

   auto pmatter = ::channel::running(pszTag);

   if (pmatter)
   {

      return pmatter;

   }

   sync_lock sl(mutex());

   for(auto & pcomposite : *m_pcompositea)
   {

      try
      {

         const char * pszTaskTag = pcomposite->get_task_tag();

         if (!strcmp(pszTaskTag, pszTag))
         {

            return pcomposite;

         }

      }
      catch (...)
      {


      }

   }

   return nullptr;


}


int thread::_GetMessage(LPMESSAGE pmessage, oswindow oswindow, UINT wMsgFilterMin,UINT wMsgFilterMax)
{

   __throw(exception::exception);

   //xxf_zerop(pmessage);

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

            auto bShouldRun = thread_get_run();

            if (!bShouldRun)
            {

               output_debug_string("session_shouldn't_run?");

            }

         }

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

         TRACE(trace_category_appmsg, trace_level_information, string(type_name()) + " thread::pump_message - Received e_message_quit.\n");

         INFO("%s thread::pump_message - Received e_message_quit.\n", type_name());

         m_nDisablePumpCount++; // application must die
         // Note: prevents calling message loop things in 'exit_thread'
         // will never be decremented
         return false;

      }


      if (m_message.message == e_message_destroy_window && m_strDebugType.contains("notify_icon"))
      {

         INFO("notify_icon");

      }

      process_message();

      return true;

   }
   catch (::exception_pointer pe)
   {

      if (m_strDebugType.contains("filemanager"))
      {

         //INFO("filemanager");

      }

      if (handle_exception(pe))
      {

         return true;

      }

      //// get_context_application() may be it self, it is ok...
      //if (Application.final_handle_exception(e))
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

         TRACE(trace_category_appmsg, trace_level_information, "xx" + strType + " thread::raw_pump_message - Received e_message_quit");

         ::output_debug_string("xx" + strType + " thread::raw_pump_message - Received e_message_quit.\n");

         m_nDisablePumpCount++; // application must die
         // Note: prevents calling message loop things in 'exit_thread'
         // will never be decremented
         return false;

      }

      raw_process_message();

      return true;

   }
   catch (::exception_pointer pe)
   {

      if (handle_exception(pe))
      {

         return true;

      }

      //// get_context_application() may be it self, it is ok...
      //if (Application.final_handle_exception(e))
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


void thread::process_message(::message::base * pbase)
{

   if (pbase->m_playeredUserPrimitive == nullptr)
   {

      process_thread_message(pbase);

   }
   else
   {

      __throw(todo("apex"));
      // apex commented
      //process_window_message(pbase);

   }

}


void thread::process_thread_message(::message::base * pbase)
{

   ASSERT(pbase->m_playeredUserPrimitive == nullptr);

   if (pbase->m_playeredUserPrimitive != nullptr)
   {

      __throw(todo("apex"));
      // apex commented

//      process_window_message(pbase);

      return;

   }

   try
   {

      message_handler(pbase);

   }
   catch (::exception_pointer pe)
   {

      if (!handle_exception(pe))
      {

         __post_quit_message(-1);

         pbase->m_lresult = -1;

      }

   }
   catch (...)
   {

      TRACE("application::process_thread_message : ::status::result processing application thread message (...)");

   }

}


// apex commented
//void thread::process_window_message(::message::base * pbase)
//{
//
//   ASSERT(pbase->m_puserinteraction != nullptr);
//
//   if (pbase->m_puserinteraction == nullptr)
//   {
//
//      process_thread_message(pbase);
//
//      return;
//
//   }
//
//   try
//   {
//
//      pbase->m_puserinteraction->m_puiThis->message_handler(pbase);
//
//   }
//   catch (::exception_pointer pe)
//   {
//
//      process_window_procedure_exception(pe, pbase);
//
//      TRACE("application::process_window_message : ::status::result processing window message (const ::exception::exception & )");
//
//      if (!handle_exception(pe))
//      {
//
//         __post_quit_message(-1);
//
//         pbase->m_lresult = -1;
//
//      }
//
//   }
//   catch (...)
//   {
//
//      TRACE("application::process_window_message : ::status::result processing window message (...)");
//
//   }
//
//}


bool thread::defer_pump_message()
{

   if (peek_message(&m_message, nullptr, 0, 0, PM_REMOVE))
   {

      if(m_message.message == e_message_quit)
      {

         ::output_debug_string("\n\n\nthread::defer_pump_message (1) quitting (wm_quit? {PeekMessage->message : " + __str(m_message.message == e_message_quit ? 1 : 0) + "!}) : " + string(type_name()) + " (" + __str((u64)::get_current_ithread()) + ")\n\n\n");

         return false;

      }

      process_message();

      return true;

   }

   return false;

}


::estatus thread::on_thread_on_idle(thread *pimpl, LONG lCount)
{

   return ::success;

}


::user::primitive * thread::get_active_ui()
{

   return __user_primitive(m_puiActive);

}


::user::primitive * thread::set_active_ui(::layered * pinteraction)
{

   return __user_primitive(m_puiActive = pinteraction);

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

#ifdef WINDOWS_DESKTOP

         ::PostThreadMessage(m_ithread, WM_KICKIDLE, 0, 0);

#else

         if (m_pmq && !m_bClosedMq)
         {

            sync_lock sl(m_pmq->mutex());

            m_pmq->m_bKickIdle = true;

            m_pmq->m_eventNewMessage.SetEvent();

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

      m_pmq->post_message(nullptr, (enum_message) e_message_quit, 0, 0);

   }

#ifdef WINDOWS_DESKTOP

   try
   {

      if (task_active() && !m_bAuraMessageQueue)
      {

         if (m_bMessageThread)
         {

            post_message((enum_message) e_message_quit, 0, 0);

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
   //    sync_lock sl(mutex());

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
      sync_lock sl(mutex());

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


void thread::on_finish()
{

//   channel::on_finish();

   post_quit();

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
//      sync_lock sl(mutex());
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
//      sync_lock slChild(ptask->mutex());
//
//      if (::multithreading::is_child(ptask) || ptask->m_pthreadParent)
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
//      ptask->m_pthreadParent.reset(this OBJ_REF_DBG_COMMA_P_NOTE(ptask, "thread::thread_add"));
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


void thread::task_remove(::task * ptask)
{

   try
   {

      string strThreadThis = type_name();

      string strThreadChild = ptask->type_name();

      sync_lock sl(mutex());

      if (::is_null(ptask))
      {

         __throw(invalid_argument_exception());

      }

      sync_lock slChild(ptask->mutex());

      if (!m_pcompositea->contains(ptask) && ptask->thread_parent() != this)
      {

         __throw(invalid_argument_exception("thread is no parent-child releationship between the threads"));

      }

      ptask->m_pobjectParent.release();

      m_pcompositea->remove(ptask);

      if (finish_bit())
      {

         if (strThreadThis == "veriwell_keyboard::application")
         {

            output_debug_string("veriwell_keyboard::application");

         }

         finish(this);

      }

   }
   catch (...)
   {


   }

}


void thread::finalize()
{

   call_method(DESTROY_METHOD);

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

   ::channel::finalize();

   auto pcontextobject = get_context_object();

   if(pcontextobject)
   {

      auto estatus = pcontextobject->release_composite2(this);

      if(!estatus)
      {

         output_debug_string("release_composite2 failed");

      }

   }


}


bool thread::thread_get_run() const
{

   if(m_pmq)
   {

      if(m_pmq->m_messagea.has_element())
      {

         return true;

      }

   }

   bool bSetFinish = m_bitSetFinish;

   bool bFinishing = m_bitFinishing;

   return !bSetFinish;

}


void thread::message_queue_message_handler(::message::base * pbase)
{

   UNREFERENCED_PARAMETER(pbase);

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


::estatus thread::initialize(::layered * pobjectContext)
{

   auto estatus = ::channel::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   if (::is_set(pobjectContext))
   {

      auto pthreadContext = dynamic_cast<::thread *>(pobjectContext);

      if (pthreadContext)
      {

         set_context_thread(pthreadContext);

      }

   }

   thread_common_construct();

   return estatus;

}


::estatus thread::do_task()
{

   ::u32 u = -1;

   ::estatus estatus = error_failed;

   ::estatus estatusOs = error_failed;

   ::estatus estatusStart = error_failed;

   {

      estatusOs = osthread_init();

      if (::succeeded(estatusOs))
      {

         estatusStart = __thread_init();

      }

   }

   if (::succeeded(estatusStart))
   {

      estatus = __thread_main();

   }

   if (::succeeded(estatusOs))
   {

      __thread_term();

      osthread_term();

   }

//#if OBJ_REF_DBG
//
//   //release(OBJ_REF_DBG_P_NOTE(this, nullptr));
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

   return estatus;

}


//void thread::construct(thread_procedure procedure, thread_parameter parameter)
//{
//
//   CommonConstruct();
//
//   m_procedure = procedure;
//
//   m_parameter = parameter;
//
//}






::estatus thread::init_thread()
{

   bool bAddReference = false;

   if (get_context_application() && get_context_application() != this)
   {

      try
      {

         get_context_application()->add_reference(this);

         bAddReference = true;

      }
      catch (...)
      {

      }

   }

   if(!bAddReference && get_context_session() && get_context_session() != this)
   {

      try
      {

         get_context_session()->add_reference(this);

         bAddReference = true;

      }
      catch (...)
      {

      }

   }

   if (!bAddReference && get_context_system() && &System != this)
   {

      try
      {

         System.add_reference(this);

         bAddReference = true;

      }
      catch (...)
      {

      }

   }

   return true;

}


::estatus thread::on_pre_run_thread()
{

   return true;

}


void thread::dispatch_thread_message(::message::message * pbase)
{

   route_message(pbase);

}


void thread::wait()
{

   wait(::duration::infinite());

}


sync_result thread::wait(const duration & duration)
{

   ITHREAD ithread = m_ithread;

   try
   {

#if defined(WINDOWS)

      DWORD timeout = duration.is_pos_infinity() ? INFINITE : static_cast<DWORD>(duration.total_milliseconds());

      HTHREAD hthread = m_hthread;

      if (hthread == NULL || hthread == INVALID_HANDLE_VALUE)
      {

         return sync_result(::sync_result::result_event0);

      }

      return sync_result((u32) ::WaitForSingleObject(hthread, timeout));

#else

      if(duration.is_pos_infinity())
      {

         while(is_thread_on(ithread))
         {

            Sleep(100);

         }

      }
      else
      {

         tick tickDelay = (DWORD) duration.total_milliseconds();

         auto dwStep = min(max(tickDelay / 10, 1), 100);

         while(is_thread_on(ithread))
         {

            Sleep(dwStep);

         }

      }

#endif

   }
   catch(...)
   {


   }

   return is_thread_on(ithread) ?
          sync_result(::sync_result::result_timeout) :
          sync_result(::sync_result::result_event0);

}


void thread::pre_translate_message(::message::message * pmessage)
{


}


void thread::app_pre_translate_message(::message::message * pmessage)
{

   try
   {

      if(get_context_application() != nullptr && !get_context_application()->is_system() && !get_context_application()->is_session())
      {

         get_context_application()->pre_translate_message(pmessage);

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

      if(get_context_application() != nullptr)
      {

         if(get_context_application()->get_context_session() != nullptr)
         {

            get_context_application()->get_context_session()->pre_translate_message(pmessage);

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

      if(get_context_system() != nullptr)
      {

         System.pre_translate_message(pmessage);

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


void thread::process_window_procedure_exception(::exception_pointer pe,::message::message * pmessage)
{

   SCAST_PTR(::message::base,pbase,pmessage);

   if(pbase->m_id == e_message_create)
   {

      pbase->m_lresult = -1;

   }
   else if(pbase->m_id == WM_PAINT)
   {

      // force validation of interaction_impl to prevent getting WM_PAINT again

#ifdef WIDOWSEX
      ValidateRect(pbase->m_puserinteraction->get_safe_handle(),nullptr);
#endif

      pbase->m_lresult = 0;

   }

}


namespace thread_util
{

   inline bool IsEnterKey(::message::message * pmessage)
   {
      SCAST_PTR(::message::base,pbase,pmessage);
      return pbase->m_id == WM_KEYDOWN && pbase->m_id == VK_RETURN;
   }

   inline bool IsButtonUp(::message::message * pmessage)
   {
      SCAST_PTR(::message::base,pbase,pmessage);
      return pbase->m_id == WM_LBUTTONUP;
   }

}

void thread::process_message_filter(i32 code,::message::message * pmessage)
{

   Application.process_message_filter(code,pmessage);

}





//thread_startup::thread_startup(::layered * pobjectContext) :
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
//   if(m_hthread != nullptr)
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


bool thread::begin_thread(bool bSynchInitialization, ::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, LPSECURITY_ATTRIBUTES psa)
{

   clear_finish_bit();

   ENSURE(m_hthread == (HTHREAD) nullptr);

   if(m_id.is_empty())
   {

      m_id = type_name();

   }

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

      UINT32 maxframes = sizeof(uia) / sizeof(uia[0]);

      ULONG BackTraceHash;

      int iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID*>(&uia), &BackTraceHash);

      char sz[1024];

      xxf_zerop(sz);

      engine_symbol(sz, sizeof(sz), &dwDisplacement, uia[5]);

      u32 uiLine = 0;

      {
         cslock csl(&::exception::engine().m_cs);

         engine_fileline(uia[5], 0, 0, &uiLine, nullptr);

      }

      strId =  string(sz) + "(" + __str(uiLine) + ") :: forking_thread";

#endif

#endif

   }

   m_pszDebug = strdup(strId);

#endif

   auto pobject = get_context_object();

   if (::is_set(pobject) && pobject != this)
   {

      pobject->add_composite(this OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   }

   if (bSynchInitialization)
   {

      m_pevent = __new(manual_reset_event());

   }

   auto estatus = begin_task(epriority, nStackSize, uiCreateFlags);

   if(m_hthread == 0)
   {

      if (::is_set(get_context_object()))
      {

         get_context_object()->release_reference(this);

      }

      dec_ref(OBJ_REF_DBG_THIS);

      return false;

   }

#ifndef WINDOWS

   if(m_hthread == m_ithread)
   {

      INFO("create_thread success");

   }

#endif

   if (m_pevent)
   {

      m_pevent->wait();

      ::estatus estatus = get_result_status();

      if (failed(estatus))
      {

         exception_pointer pexceptionRethrow = m_result.get_exception < ::exit_exception >();

         if (pexceptionRethrow.is_set())
         {

            __rethrow(pexceptionRethrow);

         }

         return false;

      }

   }

   return true;

}



bool thread::begin(::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, LPSECURITY_ATTRIBUTES psa)
{

   if(!begin_thread(false, epriority, nStackSize, uiCreateFlags, psa))
   {

      return false;

   }

   return true;

}


bool thread::begin_synch(::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, LPSECURITY_ATTRIBUTES psa)
{

   if(!begin_thread(true, epriority, nStackSize, uiCreateFlags, psa))
   {

      return false;

   }

   return true;

}


::estatus thread::inline_init()
{

   set_current_handles();

   ::estatus estatus = __thread_init();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::estatus thread::inline_term()
{

   ::estatus estatus = ::error_none;

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


HTHREAD thread::get_hthread() const
{

   return m_hthread;

}


ITHREAD thread::get_ithread() const
{

   return m_ithread;

}


bool thread::task_active() const
{

   return !m_bThreadClosed && m_hthread != (HTHREAD)0;

}


void thread::set_current_handles()
{

#ifdef WINDOWS_DESKTOP

   m_hthread = dup_handle(::get_current_hthread());

#else

   m_hthread = ::get_current_hthread();

#endif

   m_ithread = ::get_current_ithread();

}


iptr thread::item() const
{

   return (iptr)m_hthread;

}


void thread::__priority_and_affinity()
{

   if (m_dwThreadAffinityMask != 0)
   {

#if defined(WINDOWS_DESKTOP) || defined(LINUX)

      int_bool bOk = ::SetThreadAffinityMask(m_hthread, m_dwThreadAffinityMask) != 0;

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
//   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &m_hthread, 0, FALSE, DUPLICATE_SAME_ACCESS);
//
//#else
//
//   m_hthread = ::get_current_hthread();
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

   __node_init_thread(this);


}


void thread::__os_finalize()
{

   __node_term_thread(this);

}


//::context_object* thread::calc_parent_thread()
//{
//
//   return ::multithreading::calc_parent(this);
//
//}


::estatus thread::osthread_init()
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

      MESSAGE message = {};

      ::PeekMessage(&message, NULL, WM_USER, WM_USER, PM_NOREMOVE);

   }

#endif

   m_estatus = ::success;

   __set_thread_on();

   //{

   //   auto pthreadParent = ::multithreading::calc_parent(this);

   //   if (pthreadParent)
   //   {

   //      if (!pthreadParent->task_add(this))
   //      {

   //         if (pthreadParent->m_id.begins_ci("pred_thread") && m_id.begins_ci("pred_thread"))
   //         {

   //            pthreadParent->task_remove(this);

   //            pthreadParent = ::multithreading::calc_parent(pthreadParent);

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

      ::set_task(this OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      processor_cache_oriented_set_thread_memory_pool(0); // set default handler cache oriented thread memory pool index to 0 ("zero") (The First One)

      ::__init_thread();

   }

   try
   {

      __os_initialize();

   }
   catch (::exception_pointer pe)
   {

      m_estatus = pe->m_estatus;

      if (succeeded(m_estatus))
      {

         m_estatus = error_failed;

      }

      m_result.add(pe);

      top_handle_exception(pe);

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

   ::multithreading::task_register(m_ithread, this);


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

   ::multithreading::task_unregister(m_ithread, pthread);

   auto id = ::get_current_ithread();

   set_thread_off(::get_current_ithread());

   //::set_task(nullptr);

}


::estatus thread::__thread_main()
{

   if (m_pevStarted.is_set())
   {

      m_pevStarted->set_event();

      m_pevStarted.release();

   }

   auto estatus = main();

   m_bThreadClosed = true;

   try
   {

      if (m_pevReady)
      {

         m_pevReady->SetEvent();

      }

   }
   catch (...)
   {

   }

   return estatus;

}


bool thread::is_idle_message(::message::message * pmessage)
{

   return ::message::is_idle_message(pmessage);

}


bool thread::is_idle_message()
{

   return ::message::is_idle_message(&m_message);

}


void thread::post_quit_to_all_threads()
{

   ::multithreading::post_quit_to_all_threads();

}


void thread::post_to_all_threads(const ::id & id, WPARAM wparam, LPARAM lparam)
{

#ifdef DEBUG

   if (id == e_message_quit)
   {

      //!!for e_message_quit please use post_quit_to_all_threads;
      __throw(invalid_argument_exception);

   }

#endif

   //for e_message_quit please use post_quit_to_all_threads;
   //if(id == e_message_quit)
   //{

   //   ::multithreading::post_quit_to_all_threads();

   //   return;

   //}

   ::multithreading::post_to_all_threads(id, wparam, lparam);

}


bool thread::post_task(const ::method& method)
{

   if (!method)
   {

      return false;

   }

   sync_lock sl(mutex());

   m_methoda.add(method);

   kick_idle();

   return true;

}


bool thread::send_task(const ::method & method, ::duration durationTimeout)
{

   return send_object(e_message_system, system_message_method, method, durationTimeout);

}


bool thread::post_object(const ::id & id, WPARAM wParam, ::matter * pmatter)
{

   return post_message(id, wParam, pmatter);

}


bool thread::post_message(const ::id & id, WPARAM wParam, lparam lParam)
{

#ifdef WINDOWS_DESKTOP

   if (m_hthread && !m_bAuraMessageQueue && m_bMessageThread)
   {

      if (id.umessage() == e_message_quit)
      {

         string strType = type_name();

         if (strType.contains_ci("::application"))
         {

            output_debug_string("application_shouldn't_run?");

            auto bShouldRun = thread_get_run();

            if (!bShouldRun)
            {

               output_debug_string("application_shouldn't_run?");

            }

         }
         else if (strType.contains_ci("session"))
         {

            auto bShouldRun = thread_get_run();

            if (!bShouldRun)
            {

               output_debug_string("session_shouldn't_run?");

            }

         }
         else if (strType.contains_ci("system"))
         {

            auto bShouldRun = thread_get_run();

            if (!bShouldRun)
            {

               output_debug_string("session_shouldn't_run?");

            }

         }

      }

      int_bool bOk = ::PostThreadMessage(m_ithread, id.umessage(), wParam, lParam) != FALSE;

      if (!bOk)
      {

         TRACELASTERROR();

      }

      return bOk;

   }

#endif

   return get_mq()->post_message(nullptr, id, wParam, lParam);

}


bool thread::send_object(const ::id & id, WPARAM wParam, lparam lParam, ::duration durWaitStep)
{

   if (!id.is_message())
   {

      __throw(invalid_argument_exception);

   }

   if(m_bThreadClosed)
   {

      return false;

   }

   if (id == e_message_quit)
   {

      wait(durWaitStep);

      return true;

   }

   if (m_hthread == (HTHREAD)nullptr || !thread_get_run())
   {

      if (lParam != 0)
      {

         __pointer(object) spo((lparam)lParam);


      }

      return false;

   }

   send_message(id, wParam, lParam, durWaitStep);

   return true;

}


bool thread::send_message(const ::id & id, WPARAM wParam, lparam lParam, ::duration durWaitStep)
{

   if (!id.is_message())
   {

      __throw(invalid_argument_exception);

   }

   if(m_bThreadClosed)
   {

      return false;

   }

   if (id == e_message_quit)
   {

      wait(durWaitStep);

      return true;

   }

   auto pmessage = __new(::send_thread_message(get_context_object()));

   pmessage->m_message.message = id.u32();
   pmessage->m_message.wParam = wParam;
   pmessage->m_message.lParam = lParam;

   post_message(e_message_system, system_message_meta, pmessage);

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
//      if(m_hthread != nullptr)
//      {
//
//         ::CloseHandle(m_hthread);
//
//      }
//
//   }
//
//   m_hthread = nullptr;
//
//   if(pvoidOsData != nullptr)
//   {
//
//      if(::DuplicateHandle(::GetCurrentProcess(),(HANDLE)pvoidOsData,GetCurrentProcess(),&m_hthread,THREAD_ALL_ACCESS,TRUE,0))
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
//   m_hthread = (HTHREAD)pvoidOsData;
//
//#endif
//
//}


//void thread::set_os_int(ITHREAD ithread)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   m_uThread = (DWORD) ithread;
//
//#else
//
//   m_uThread = (ITHREAD) ithread;
//
//#endif
//
//}


::estatus thread::__thread_init()
{

   m_result = on_thread_init();

   if (m_pevent)
   {

      m_pevent->set_event();

   }

   return m_estatus;

}


::estatus thread::on_thread_init()
{

   init_task();

   install_message_routing(this);

   bool bError = false;

   try
   {

      if(!init_thread())
      {

         bError = true;

      }

   }
   catch (::exception_pointer pe)
   {

      handle_exception(pe);

      bError = true;

   }
   catch(...)
   {

      bError = true;

   }

   if (bError)
   {

      goto error;

   }

   try
   {

      if (!on_pre_run_thread())
      {

         bError = true;

      }

   }
   catch (...)
   {

      bError = true;

   }



error:;



   if(bError)
   {

      return false;

   }
   else
   {

      return true;

   }

}


::estatus thread::main()
{

   string strType = type_name();

   if(strType.contains("wave_player"))
   {

      output_debug_string("I am xxthread::main from wave_player");

   }
   else if(strType.ends_ci("out"))
   {

      output_debug_string("I am xxthread::main from out");

   }
   else if(strType.contains("output_thread"))
   {

      output_debug_string("I am xxthread::main from output_thread");

   }

   // first -- check for simple worker thread
   ::estatus estatus = ::success;

   // else check for thread with message loop
   ASSERT_VALID(this);

   try
   {

      m_bReady = true;

      run();

   }
   catch (::exit_exception* pe)
   {

      if (___thread(pe->m_pthreadExit) != this)
      {

         System.finish(::get_context_system());

      }

      ::release(pe);

   }
   catch (::exception::exception * pe)
   {

      top_handle_exception(pe);

      ::release(pe);

   }
   catch(...)
   {

      output_debug_string("exception occurred");

   }

   if(strType.contains("wave_player"))
   {

      output_debug_string("after run xxthread::main from wave_player");

   }
   else if(strType.ends_ci("out"))
   {

      output_debug_string("after run xxthread::main from out");

   }
   else if(strType.contains("output_thread"))
   {

      output_debug_string("after run xxthread::main from output_thread");

   }

   estatus = m_result.status();

   //clear_finish_bit();

   return estatus;

}


mq* thread::_get_mq()
{

   sync_lock sl(mutex());

   if(m_bitSetFinish || m_bThreadClosed)
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

   auto pmq = ::get_mq(m_ithread, true);

   auto estatus = __compose(m_pmq, pmq);

   if (!estatus)
   {

      return nullptr;

   }

   return m_pmq;

}

int_bool thread::peek_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{

   if (m_pmq)
   {

      if (m_pmq->peek_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
      {

         return TRUE;

      }

   }

#ifdef WINDOWS_DESKTOP

   if (m_hthread && !m_bAuraMessageQueue)
   {

      if (::PeekMessage(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
      {

         return TRUE;

      }

   }

#endif

   return false;

}


::estatus thread::set_finish(::context_object * pcontextobjectFinish)
{

   auto estatus = channel::set_finish(pcontextobjectFinish);

   if (estatus == error_pending)
   {

      return estatus;

   }

   //if (task_active())
   //{

   //   if (::is_set(pcontextobjectFinish))
   //   {

   //      notify_array().add_unique(pcontextobjectFinish);

   //   }

   //   post_quit();

   //   return error_pending;

   //}

   return estatus;

//   auto estatus = set_finish_composites();
//
//   if (estatus == error_pending)
//   {
//
//      return error_pending;
//
//   }
//
//   if (!finish_bit())
//   {
//
//      m_bitFinishing = true;
//
//      set_finish_bit();
//
//   }
//
//   if (m_bitFinishing)
//   {
//
//      string strTypeName = type_name();
//
//#ifdef ANDROID
//
//      demangle(strTypeName);
//
//#endif
//
//      if (strTypeName == "user::shell")
//      {
//
//         output_debug_string("user::shell::finish");
//
//      }
//      else if (strTypeName == "apex::system")
//      {
//
//         output_debug_string("apex::system::finish");
//
//      }
//
//      estatus = set_finish_composites();
//
//      if (strTypeName.contains_ci("app_app::window"))
//      {
//
//         output_debug_string("set_finish at app_window");
//
//      }
//
//      //if (m_ptaska)
//      //{
//
//      //task_set_finish:
//
//      //   ::count countTask = m_ptaska->get_count();
//
//      //   for (::index iTask = 0; m_ptaska && iTask < countTask; iTask++)
//      //   {
//
//      //      auto & ptask = m_ptaska->element_at(iTask);
//
//      //      sl.unlock();
//
//      //      auto estatus = ptask->finish();
//
//      //      if (estatus == ::error_pending)
//      //      {
//
//      //         bStillFinishingTasks = true;
//
//      //      }
//
//      //      sl.lock();
//
//      //      if (countTask != m_ptaska->get_count())
//      //      {
//
//      //         goto task_set_finish;
//
//      //      }
//
//      //   }
//
//      //}
//
//      //if (bStillFinishingComposites || bStillFinishingTasks)
//
//      if (estatus == ::error_pending)
//      {
//
//         if (m_pcompositea)
//         {
//
//            auto compositea = *m_pcompositea;
//
//            string strWaiting;
//
//            for (auto & pcomposite : compositea)
//            {
//
//               try
//               {
//
//                  string strThreadType;
//
//                  strThreadType = pcomposite->type_name();
//
//                  strWaiting += strThreadType;
//
//                  strWaiting += "\r\n";
//
//                  pcomposite->finish();
//
//               }
//               catch (...)
//               {
//
//               }
//
//            }
//
//            if (strWaiting.has_char())
//            {
//
//               TRACE("The thread %s is waiting for the following threads to finish:\r\n%s", type_name(), strWaiting.c_str());
//
//            }
//
//         }
//
//         kick_idle();
//
//      }
//      else
//      {
//
//
//         string strType = type_name();
//
//         if (strType.contains_ci("session"))
//         {
//
//            auto bShouldRun = thread_get_run();
//
//            if (!bShouldRun)
//            {
//
//               output_debug_string("session_shouldn't_run?");
//
//            }
//
//         }
//         else if (strType.contains_ci("application"))
//         {
//
//            auto bShouldRun = thread_get_run();
//
//            if (!bShouldRun)
//            {
//
//               output_debug_string("application_shouldn't_run?");
//
//            }
//
//
//         }
//
//         m_bitFinishing = false;
//
//      }
//
//}
//
//   return estatus;
//

}


::estatus thread::set_finish_composites(::context_object * pcontextobjectFinish)
{

   auto estatus = channel::set_finish_composites(pcontextobjectFinish);

   if (estatus == error_pending)
   {

      return estatus;

   }

   if (task_active())
   {

      set_finish_bit();

      if (m_bMessageThread)
      {

         post_quit();

         return error_pending;

      }
      else
      {

         ::output_debug_string("!m_bMessageThread");

      }

   }

   return ::success;

}


int_bool thread::get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{

   bool bQuit = false;

#ifdef WINDOWS_DESKTOP

   if (m_bAuraMessageQueue)
   {

      if (!get_mq()->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax))
      {

         if (!finish_bit())
         {

            finish(::get_context());

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

         bQuit = pMsg->message == e_message_quit;

         if (!bQuit)
         {

            return TRUE;

         }

         __release(m_pmq);

      }

   }

   if (m_hthread)
   {

      int iRet = ::GetMessage(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax);

      if (iRet == -1)
      {

         DWORD dwLastError = ::GetLastError();

         ::output_debug_string("Last Error : " + __str(dwLastError) + "\n");

      }
      else
      {

         bQuit = !iRet || pMsg->message == e_message_quit;

         if (bQuit)
         {

            ::output_debug_string("received e_message_quit");

         }
         else
         {

            return TRUE;

         }

      }

   }

#else

   auto pmq = get_mq();

   if (pmq->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax))
   {

      return TRUE;

   }

#endif

   if (bQuit)
   {

      if (!finish_bit())
      {

         finish(::get_context());

      }

   }

   return thread_get_run();

}


int_bool thread::post_message(oswindow oswindow, const ::id & id, WPARAM wParam, LPARAM lParam)
{

   if (!id.is_message())
   {

      __throw(invalid_argument_exception);

   }

   if(m_bThreadClosed)
   {

      return false;

   }

#ifdef WINDOWS_DESKTOP

   if (m_hthread && !m_bAuraMessageQueue)
   {

      if (::PostMessage(oswindow, id.u32(), wParam, lParam))
      {

         return TRUE;

      }

   }

#endif

   return get_mq()->post_message(oswindow, id, wParam, lParam);

}


void thread::assert_valid() const
{

   channel::assert_valid();

}


void thread::dump(dump_context & dumpcontext) const
{

   channel::dump(dumpcontext);

}


::estatus thread::__thread_term()
{

   return on_thread_term();

}


::estatus thread::on_thread_term()
{

   {

      sync_lock sl(m_pmutexThreadUiPtra);

      if (::is_set(m_puiptraThread))
      {

         m_puiptraThread->remove_all();

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


thread::operator HTHREAD() const
{

   return is_null(this) ? (HTHREAD) nullptr : m_hthread;

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


   //single_lock sl(&m_sptimera->m_mutex,TRUE);

   //i32 iMin = 100;

   //for(i32 i = 0; i < m_sptimera->m_timera.get_count(); i++)
   //{

   //   if(m_sptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
   //   {

   //      iMin = m_sptimera->m_timera.element_at(i)->m_uiElapse;

   //   }

   //}

   //sl.unlock();

   //m_spqueue->message_queue_set_timer((uptr)-2,iMin);

   return true;

}


void thread::message_handler(::message::base * pbase)
{

   pre_translate_message(pbase);

   route_message(pbase);

}


::estatus thread::process_message()
{

   try
   {

      MESSAGE & msg = m_message;

#ifdef WINDOWS_DESKTOP

      if (msg.hwnd != nullptr || msg.message == WM_TIMER)
      {

         ::TranslateMessage(&msg);

         ::DispatchMessage(&msg);

         return true;

      }

#endif

      if (msg.message == e_message_event2)
      {

         //if(msg.lParam)
         {

            auto paction = System.new_action(msg);

            apply(paction);

         }
         //else
         //{

         //   apply((const __id &)(::iptr) msg.wParam);

         //}

      }
      else if (msg.message == e_message_system)
      {

         if (msg.wParam == system_message_create)
         {

            __pointer(::create) pcreate((lparam)msg.lParam);

            if (pcreate.is_set())
            {

               call_request(pcreate);

            }

         }
         else if (msg.wParam == system_message_method)
         {

            ::method method(msg.lParam);

            method();

         }
         //else if (msg.wParam == system_message_runnable)
         //{

         //   __pointer(::context_object) pobjectTask((lparam)msg.lParam);

         //   pobjectTask->call();

         //}
         else if (msg.wParam == system_message_meta)
         {

            __pointer(::send_thread_message) pmessage(msg.lParam);

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

         TRACE(trace_category_appmsg, trace_level_error,"Error: thread::pump_message called when not permitted.\n");

      }

      if(msg.message == WM_KICKIDLE)
      {

         return true;

      }

      __pointer(::message::base) pbase;

      if (get_context_application())
      {

         pbase = get_context_application()->get_message_base(&msg);

      }
      else if(get_context_session())
      {

         pbase = get_context_session()->get_message_base(&msg);

      }

      if(pbase.is_set())
      {

         process_base_message(pbase);

      }

      return true;

   }
   catch (::exception_pointer pe)
   {

      if (handle_exception(pe))
      {

         return true;

      }

   }
   catch(...)
   {

   }

   return false;

}


::estatus thread::process_base_message(::message::base * pbase)
{

   message_handler(pbase);

   return true;

}


::estatus thread::raw_process_message()
{

   try
   {

      ___pointer < ::message::message > spbase;

      spbase = get_message_base(&m_message);

      if (spbase.is_set())
      {

         route_message(spbase);

      }

      return true;

   }
   catch (::exception_pointer pe)
   {

      if (handle_exception(pe))
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

   bool bOk = ::SetThreadPriority(m_hthread, nPriority) != FALSE;

   if (!bOk)
   {

      u32 dwLastError = ::get_last_error();

      output_debug_string("thread::SetThreadPriority LastError = " + __str(dwLastError));

   }

   m_epriority = thread_priority();

   return bOk;

}


::e_priority thread::thread_priority()
{

   ASSERT(m_hthread != NULL_HTHREAD);

   i32 nPriority = ::GetThreadPriority(m_hthread);

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
//   ::ResumeThread(m_hthread);
//
//#endif
//
//}


//u32 thread::ResumeThread()
//{
//
//   ASSERT(m_hthread != NULL_HTHREAD);
//
//#if defined (WINDOWS_DESKTOP)
//
//   return ::ResumeThread(m_hthread);
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

   while(peek_message(&msg,nullptr,0,0,PM_NOREMOVE) != FALSE)
   {

      if (msg.message == e_message_quit) // do not pump, otherwise main loop will not process the message
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
//   SCAST_PTR(::message::base, pbase, pmessage);
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


::estatus thread::verb()
{

   return success;

}


::estatus thread::do_request(::create * pcreate)
{

   post_object(e_message_system, system_message_create, pcreate);

   return ::success;

}


//::mutex * g_pmutexThreadOn = nullptr;

//map < ITHREAD, ITHREAD, ITHREAD, ITHREAD > * g_pmapThreadOn = nullptr;

CLASS_DECL_APEX bool is_thread_on(ITHREAD id)
{

   sync_lock sl(&System.m_mutexTaskOn);

   return System.m_mapTaskOn.plookup(id) != nullptr;

}


CLASS_DECL_APEX bool is_active(::thread * pthread)
{

   if (::is_null(pthread))
   {

      return false;

   }

   return is_thread_on(pthread->m_ithread);

}

CLASS_DECL_APEX void set_thread_on(ITHREAD id)
{

   sync_lock sl(&System.m_mutexTaskOn);

   System.m_mapTaskOn.set_at(id, id);

}


CLASS_DECL_APEX void set_thread_off(ITHREAD id)
{

   sync_lock sl(&System.m_mutexTaskOn);

   System.m_mapTaskOn.remove_key(id);

}




CLASS_DECL_APEX void forking_count_thread_null_end(int iOrder)
{


}


user_interaction_ptr_array & thread::uiptra()
{

   {

      sync_lock sl(mutex());

      if (m_pmutexThreadUiPtra == nullptr)
      {

         m_pmutexThreadUiPtra = new ::mutex();

      }

   }

   sync_lock sl(m_pmutexThreadUiPtra);

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

CLASS_DECL_APEX bool thread_pump_sleep(DWORD dwMillis, sync * psync)
{

   int iTenths = dwMillis / 100;

   int iMillis = dwMillis % 100;

   while (true)
   {

      ::count cMessage = 0;

      try
      {

         while (::get_thread() != nullptr && ::get_thread()->has_message())
         {

            while (::get_thread()->defer_pump_message());

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

         Sleep(100);

      }

      if (::is_set(psync))
      {

         sync_lock sl(psync);

         if (sl.wait(millis(0)).succeeded())
         {

            break;

         }

      }

      iTenths--;

   }

   Sleep(iMillis);

   return ::thread_get_run();

}


CLASS_DECL_APEX bool app_sleep(tick tick)
{

   ::thread * pthread = ::get_thread();

   try
   {

      if (::is_set(pthread))
      {


         __pointer(manual_reset_event) spev;

         {

            sync_lock sl(pthread->mutex());

            if (pthread->m_pevSleep.is_null())
            {

               pthread->m_pevSleep = __new(manual_reset_event());

               pthread->m_pevSleep->ResetEvent();

            }

            spev = pthread->m_pevSleep;

         }

         if (get_context_application() && get_context_application()->finish_bit())
         {

            return false;

         }

         if (spev.is_set())
         {

            pthread->m_pevSleep->wait(tick);

            return ::thread_get_run();

         }

      }

   }
   catch (...)
   {

   }

   auto iTenths = __i64(tick) / 100;

   auto iMillis = __i64(tick) % 100;

   while(iTenths > 0)
   {

      if (get_context_application() && get_context_application()->finish_bit())
      {

         return false;

      }

      iTenths--;

      Sleep(100);

   }

   Sleep((u32) iMillis);

   return !get_context_application() || !get_context_application()->finish_bit();

}


::estatus     thread::get_result_status()
{

   return m_result.status();

}


::mutex * g_pmutexThreadDeferredCreation = nullptr;


::array < __pointer(thread) > * g_pthreadaDeferredCreate = nullptr;


CLASS_DECL_APEX void defer_create_thread(::layered* pobjectContext)
{

   auto pthread = ::get_task();

   if (::is_null(pthread))
   {

      auto pthreadNew = __object(pobjectContext)->__create_new < ::thread > ();

      pthreadNew->add_ref(OBJ_REF_DBG_P_NOTE(pobjectContext, nullptr));

      pthreadNew->clear_finish_bit();

      set_task(pthreadNew);

      sync_lock sl(g_pmutexThreadDeferredCreation);

      g_pthreadaDeferredCreate->add(pthreadNew);

   }

}


void thread::add_waiting_event(event * pevent)
{

   if(::is_null(pevent))
   {

      return;

   }

   sync_lock sl(mutex());

   m_eventaWait.add(pevent);

}


void thread::remove_waiting_event(event * pevent)
{

   sync_lock sl(mutex());

   m_eventaWait.remove(pevent);

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


DWORD thread::get_file_sharing_violation_timeout_total_milliseconds()
{

   return (DWORD)get_file_info()->m_durationFileSharingViolationTimeout.get_total_milliseconds();

}


bool thread::is_running() const
{

   return ::task::is_running();

}


::estatus thread::start(
   ::matter * pmatter,
   ::e_priority epriority,
   u32 nStackSize,
   u32 dwCreateFlags)
{

   return ::task::start(pmatter, epriority, nStackSize, dwCreateFlags);

}


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

   context_object::delete_this();

}


