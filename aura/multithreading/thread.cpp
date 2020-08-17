#include "framework.h"
#include "aura/message.h"
#include "aura/update.h"
#include "aura/os/_c.h"
#include "aura/os/_.h"
#include "aura/os/_os.h"
#include "aura/platform/mq.h"


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

   send_thread_message(::object * pobject);

   virtual ~send_thread_message();

};


send_thread_message::send_thread_message(::object * pobject) :
   ::object(pobject)
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

   m_bThreadClosed = false;

   m_bAuraMessageQueue = false;

#ifdef AURA_MESSAGE_QUEUE

   m_bClosedMq = false;

#endif

   m_bLastingThread = true;

   m_bMessageThread = false;

   m_estatus = ::success_none;

#ifdef MACOS

   m_runloop = nullptr;

#endif

   m_epriority = priority_normal;

   m_bFork = false;

   m_pmutexThreadUiPtra = nullptr;

   m_puiptraThread = nullptr;

   m_bThreadToolsForIncreasedFps = false;

   m_bTemporary = false;

   m_dwThreadAffinityMask = 0;

   m_tickHeartBeat.Now();

   defer_create_mutex();

   m_bReady = false;

   m_bRunThisThread = false;

   m_pevReady = nullptr;

   m_bZipIsDir2 = true;

   m_pslUser = nullptr;

   m_pfileinfo = nullptr;

   m_bDupHandle = false;

   m_hthread1 = (HTHREAD) nullptr;

   m_ithread1 = 0;

   m_nDisablePumpCount = 0;

   m_bSimpleMessageLoop = true;

#ifdef WINDOWS

   m_bCoInitialize = false;

#endif

   memcnts_inc(this);

}


CLASS_DECL_AURA ::thread * get_thread_raw();


void thread::thread_common_construct()
{

   m_bDedicated = false;

   if (get_context_application() != nullptr && get_context_application()->get_context_session() != nullptr)
   {

      m_bZipIsDir2 = get_context_application()->get_context_session()->m_bZipIsDir2;

   }

   if (::get_thread_raw() != nullptr)
   {

      m_bAvoidProcFork = ::get_thread_raw()->m_bAvoidProcFork;

   }
   else
   {

      m_bAvoidProcFork = false;

   }

}


thread::~thread()
{

   memcnts_dec(this);

   ::aura::del(m_puiptraThread);

   ::aura::del(m_pmutexThreadUiPtra);

}


HTHREAD thread::get_os_handle() const
{

   return get_hthread();

}


string thread::get_tag() const
{

   return m_strThreadTag;

}


bool thread::thread_active() const
{

   return get_os_handle() != 0;

}


bool thread::is_thread() const
{

   return true;

}


bool thread::is_dedicated_thread() const
{

   return m_bDedicated;

}


bool thread::is_running() const
{

   return thread_active() && thread_get_run();

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

}


::estatus thread::osthread_term()
{

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

   ::thread_release();

   ::__term_thread();

   if (m_pthreadParent)
   {

      m_pthreadParent->thread_remove(this);

   }

   ::estatus estatus = m_result.m_estatus;

   finalize();

   return estatus;

}


void thread::on_keep_alive()
{

   m_tickHeartBeat.Now();

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




CLASS_DECL_AURA void thread_alloc_ready(bool bReady)
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

   while (thread_get_run())
   {

      try
      {

         if(!thread_step())
         {


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

   if(strType.contains("wave_player"))
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

      if (m_objectaTask.isEmpty())
      {

         return false;

      }

      auto pobjectTask = m_objectaTask.first_pointer();

      m_objectaTask.remove_at(0);

      if (pobjectTask)
      {

         sl.unlock();

         pobjectTask->call();

         return true;

      }

   }

   return false;

}


__pointer(::object) thread::running(const char * pszTag) const
{

   auto pobject = ::channel::running(pszTag);

   if (pobject)
   {

      return pobject;

   }

   sync_lock sl(mutex());

   for(auto pthread : m_threada)
   {

      try
      {

         if (pthread->m_strThreadTag == pszTag)
         {

            return pthread;

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

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

         TRACE(trace_category_appmsg, trace_level_information, string(type_name()) + " thread::pump_message - Received WM_QUIT.\n");

         INFO("%s thread::pump_message - Received WM_QUIT.\n", type_name());

         m_nDisablePumpCount++; // application must die
         // Note: prevents calling message loop things in 'exit_thread'
         // will never be decremented
         return false;

      }


      if (m_message.message == message_destroy_window && m_strDebugType.contains("notify_icon"))
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

         TRACE(trace_category_appmsg, trace_level_information, "xx" + strType + " thread::raw_pump_message - Received WM_QUIT");

         ::output_debug_string("xx" + strType + " thread::raw_pump_message - Received WM_QUIT.\n");

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

   if (pbase->m_puserinteraction == nullptr)
   {

      process_thread_message(pbase);

   }
   else
   {

      process_window_message(pbase);

   }

}


void thread::process_thread_message(::message::base * pbase)
{

   ASSERT(pbase->m_puserinteraction == nullptr);

   if (pbase->m_puserinteraction != nullptr)
   {

      process_window_message(pbase);

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


void thread::process_window_message(::message::base * pbase)
{

   ASSERT(pbase->m_puserinteraction != nullptr);

   if (pbase->m_puserinteraction == nullptr)
   {

      process_thread_message(pbase);

      return;

   }

   try
   {

      pbase->m_puserinteraction->m_puiThis->message_handler(pbase);

   }
   catch (::exception_pointer pe)
   {

      process_window_procedure_exception(pe, pbase);

      TRACE("application::process_window_message : ::status::result processing window message (const ::exception::exception & )");

      if (!handle_exception(pe))
      {

         __post_quit_message(-1);

         pbase->m_lresult = -1;

      }

   }
   catch (...)
   {

      TRACE("application::process_window_message : ::status::result processing window message (...)");

   }

}


bool thread::defer_pump_message()
{

   if (peek_message(&m_message, nullptr, 0, 0, PM_REMOVE))
   {

      if(m_message.message == WM_QUIT)
      {

         ::output_debug_string("\n\n\nthread::defer_pump_message (1) quitting (wm_quit? {PeekMessage->message : " + __str(m_message.message == WM_QUIT ? 1 : 0) + "!}) : " + string(type_name()) + " (" + __str((u64)::get_current_ithread()) + ")\n\n\n");

         return false;

      }

      process_message();

      return true;

   }

   return false;

}


bool thread::on_thread_on_idle(thread *pimpl, LONG lCount)
{

   return true;

}


::user::primitive * thread::get_active_ui()
{

   return m_puiActive;

}


::user::primitive * thread::set_active_ui(::user::primitive * pinteraction)
{

   return m_puiActive = pinteraction;

}


void thread::Delete()
{


   release();

}


//void thread::do_events(const duration & duration)
//{
//
//   auto tickStart = ::tick::now();
//
//   i64 dwSpan = duration.get_total_milliseconds();
//
//   DWORD dwSleep = (DWORD) MIN(884, dwSpan / 20);
//
//   do
//   {
//
//      do_events();
//
//      Sleep(dwSleep);
//
//   }
//   while(tickStart.elapsed() < dwSpan);
//
//}


bool thread::set_run()
{

   m_bRunThisThread = true;

   return true;

}


bool thread::set_thread_name(const char * pszThreadName)
{

   m_strThreadName = pszThreadName;

   if (m_strThreadTag.is_empty() && m_strThreadName.has_char())
   {

      m_strThreadTag = m_strThreadName;

   }

   return true;

}


bool thread::is_set_finish() const
{

   return !m_bRunThisThread;

}


void thread::set_finish()
{

   if (strstr(type_name(), "audio::out"))
   {

      output_debug_string("out ::thread::set_finish");

   }

   try
   {

      sync_lock sl(mutex());

      try
      {

         m_bRunThisThread = false;

      }
      catch (...)
      {

      }

      set_finish_composites();

      for(auto & pmanualresetevent : m_eventaWait)
      {

         try
         {

            pmanualresetevent->set_event();

         }
         catch(...)
         {

         }

      }

      string strWaiting;

      for (auto & pthread : m_threada)
      {

         try
         {

            string strThreadType;

            strThreadType = pthread->type_name();

            strWaiting += strThreadType;

            strWaiting += "\r\n";

            pthread->set_finish();

         }
         catch (...)
         {

         }

      }

      if (strWaiting.has_char())
      {

         TRACE("The thread %s is waiting for the following threads to finish:\r\n%s", type_name(), strWaiting.c_str());

      }

      //__finalize_composites();

      if (m_threada.has_element())
      {

         kick_idle();

      }
      else
      {

         post_quit();

      }

   }
   catch (...)
   {

   }

}


void thread::kick_idle()
{

   if(m_bThreadClosed)
   {

      return;

   }

   try
   {

      if (thread_active())
      {

#ifdef WINDOWS_DESKTOP

         ::PostThreadMessage(m_ithread1, WM_KICKIDLE, 0, 0);

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

      m_pmq->post_message(nullptr, WM_QUIT, 0, 0);

   }

#ifdef WINDOWS_DESKTOP

   try
   {

      if (thread_active() && !m_bAuraMessageQueue)
      {

         post_message(WM_QUIT, 0, 0);

      }

   }
   catch (...)
   {

   }

#endif

   try
   {

      /// this is quite dangerous
      sync_lock sl(mutex());

      __pointer(manual_reset_event) pev = m_pevSync;

      if (pev.is_set())
      {

         pev->SetEvent();

      }

   }
   catch (...)
   {

   }

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


bool thread::thread_add(::thread * pthread)
{

   try
   {

      string strType = pthread->type_name();

      if(strType == "user::shell::thread")
      {

         ::output_debug_string("user::shell::thread");

      }


      sync_lock sl(mutex());

      if (pthread == this)
      {

         return false;

      }

      if (::is_null(pthread))
      {

         return false;

      }

      sync_lock slChild(pthread->mutex());

      if (::multithreading::is_child(pthread) || pthread->m_pthreadParent)
      {

         return false;

      }

      if (is_set_finish())
      {

         return false;

      }

      m_threada.add(pthread);

      pthread->m_pthreadParent.reset(this OBJ_REF_DBG_ADD_P_NOTE(pthread, "thread::thread_add"));

      return true;

   }
   catch (...)
   {

   }

   return false;

}


void thread::thread_remove(::thread * pthread)
{

   try
   {

      string strThreadThis = type_name();

      string strThreadChild = pthread->type_name();

      sync_lock sl(mutex());

      if (::is_null(pthread))
      {

         __throw(invalid_argument_exception());

      }

      sync_lock slChild(pthread->mutex());

      if (!m_threada.contains(pthread) && pthread->m_pthreadParent != this)
      {

         __throw(invalid_argument_exception("thread is no parent-child releationship between the threads"));

      }

      pthread->m_pthreadParent.release();

      m_threada.remove(pthread);

      if (is_set_finish() && m_threada.is_empty())
      {

         if (strThreadThis == "albertopibiri_keyboard::application")
         {

            output_debug_string("albertopibiri_keyboard::application");

         }

         post_quit();

      }
      else
      {

         kick_idle();

      }

   }
   catch (...)
   {


   }

}


void thread::finalize()
{

   ::object::finalize();

   string strType = type_name();

   if(m_strThreadName.contains("main_frame"))
   {

      output_debug_string("I am main_frame xxpost_quit at " + strType + "\n");

   }

   if (::str::begins(strType, "user::"))
   {

      if (strType.contains("shell_thread"))
      {

         output_debug_string("I am shell_thread xxpost_quit at "+strType+"\n");

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
   else if (strType == "::aura::system")
   {

      ::output_debug_string("I am system xxpost_quit from ::aura::system\n");

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

   return m_bRunThisThread || m_threada.has_element();

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


::estatus thread::initialize(::object * pobjectContext)
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

   if (!bAddReference && get_context_system() && get_context_system() != this)
   {

      try
      {

         get_context_system()->add_reference(this);

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

   //LRESULT lresult;

   //sync_lock sl(mutex());
   //int i = 0;
   //Signal * pSignal;
   //while((pSignal = m_signala.GetSignal(pbase->m_id,0,0, i)) != nullptr)
   //{
   //   class signal * psignal = pSignal->m_psignal;
   //   message::e_prototype eprototype = pSignal->m_eprototype;
   //   if(eprototype == message::PrototypeNone)
   //   {
   //      //::message::base aura(get_object());
   //      pbase->m_psignal = psignal;
   //      //lresult = 0;
   //      //aura.set(pmsg->message, pmsg->wParam, pmsg->lParam, lresult);
   //      psignal->emit(pbase);
   //      if(pbase->m_bRet)
   //         return;
   //   }
   //   break;
   //   pbase->m_bRet = true;
   //}


}


void thread::wait()
{

   wait(::duration::infinite());

}


sync_result thread::wait(const duration & duration)
{

   ITHREAD ithread = m_ithread1;

   try
   {

#if defined(WINDOWS)

      DWORD timeout = duration.is_pos_infinity() ? INFINITE : static_cast<DWORD>(duration.total_milliseconds());

      HTHREAD hthread = m_hthread1;

      if (hthread == NULL || hthread == INVALID_HANDLE_VALUE)
      {

         return sync_result(::sync_result::result_event0);

      }

      return sync_result((u32) ::WaitForSingleObject(hthread, timeout));

#else

      if(duration.is_pos_infinity())
      {

         while(is_thread_on(uThread))
         {

            Sleep(100);

         }

      }
      else
      {

         tick tickDelay = (DWORD) duration.total_milliseconds();

         auto dwStep = MIN(MAX(tickDelay / 10, 1), 100);

         while(is_thread_on(uThread))
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

//   try
//   {
//
//      if(get_context_application()->get_context_session() != nullptr)
//      {
//
//         get_context_application()->get_context_session()->frame_pre_translate_message(pmessage);
//
//      }
//
//   }
//   catch(::exception_pointer pe)
//   {
//
//      __rethrow(e);
//
//   }
//   catch(...)
//   {
//   }

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

      if(get_context_application() != nullptr)
      {

         if(get_context_application()->get_context_system() != nullptr)
         {

            get_context_application()->get_context_system()->pre_translate_message(pmessage);

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


void thread::process_window_procedure_exception(::exception_pointer pe,::message::message * pmessage)
{

   SCAST_PTR(::message::base,pbase,pmessage);

   if(pbase->m_id == WM_CREATE)
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

   m_bRunThisThread = true;

   ENSURE(m_hthread1 == (HTHREAD) nullptr);

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

   if (::is_set(get_context_object()) && get_context_object() != this)
   {

      get_context_object()->add_reference(this);

   }

   if (bSynchInitialization)
   {

      m_pevent = __new(manual_reset_event());

   }

   auto estatus = os_fork(epriority, nStackSize, uiCreateFlags, psa, &m_ithread1, &m_hthread1);

   if(m_hthread1 == 0)
   {

      if (::is_set(get_context_object()))
      {

         get_context_object()->release_reference(this);

      }

      dec_ref(OBJ_REF_DBG_THIS);

      return false;

   }

#ifndef WINDOWS

   if(m_hthread == m_uThread)
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

   return m_hthread1;

}


ITHREAD thread::get_ithread() const
{

   return m_ithread1;

}


void thread::set_current_handles()
{

#ifdef WINDOWS_DESKTOP

   m_hthread1 = dup_handle(::get_current_hthread());

#else

   m_hthread1 = ::get_current_hthread();

#endif

   m_ithread1 = ::get_current_ithread();

}


iptr thread::item() const
{

   return (iptr)m_hthread1;

}


void thread::__priority_and_affinity()
{

   if (m_dwThreadAffinityMask != 0)
   {

#if defined(WINDOWS_DESKTOP) || defined(LINUX)

      WINBOOL bOk = ::SetThreadAffinityMask(m_hthread1, m_dwThreadAffinityMask) != 0;

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

   //if (::is_set(get_context_application()))
   //{

   //   get_context_application()->add_reference(this);

   //}

}


void thread::__os_finalize()
{


   m_pappContext.release();

   m_psessionContext.release();

   m_psystemContext.release();

   //if (::is_set(get_context_application()))
   //{

   //   get_context_application()->release_reference(this);

   //}

   //if (::is_set(get_context_session()))
   //{

   //   get_context_session()->release_reference(this);

   //}

   //if (::is_set(get_context_system()))
   //{

   //   get_context_system()->release_reference(this);

   //}

   __node_term_thread(this);

   //set_os_data(nullptr);

}


::estatus thread::osthread_init()
{

   m_bDedicated = true;

   if (!m_bRunThisThread)
   {

      m_bRunThisThread = true;

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

   {

      auto pthreadParent = ::multithreading::calc_parent(this);

      if (pthreadParent)
      {

         if (!pthreadParent->thread_add(this))
         {

            if (pthreadParent->m_id.begins_ci("pred_thread") && m_id.begins_ci("pred_thread"))
            {

               pthreadParent->thread_remove(this);

               pthreadParent = ::multithreading::calc_parent(pthreadParent);

               if (!pthreadParent->thread_add(this))
               {

                  return ::error_failed;

               }

            }
            else
            {

               return ::error_failed;

            }

         }

      }

   }

   {

      ::set_thread(this);

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

   ::multithreading::thread_register(m_ithread1, this);

   if (g_axisoninitthread)
   {

      g_axisoninitthread();

   }

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

      if (g_axisontermthread)
      {

         g_axisontermthread();

      }

      on_term_thread();

   }
   catch (...)
   {

   }

   ::thread * pthread = this;

   if (get_context_object())
   {

      get_context_object()->release_reference(this);

   }

   //release(OBJ_REF_DBG_THIS);

   ::multithreading::thread_unregister(m_ithread1, pthread);

   auto id = ::get_current_ithread();

   set_thread_off(::get_current_ithread());

   //::aura::system::g_p->unset_thread(::get_current_ithread());

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


void thread::post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam)
{

   if(message == WM_QUIT)
   {

      ::multithreading::post_quit_to_all_threads();

      return;

   }

   ::multithreading::post_to_all_threads(message, wparam, lparam);

}


//thread* thread::thread_get(ITHREAD idthread)
//{
//
//   sync_lock sl(g_pmutex);
//
//   return g_pthreadmap->operator[](idthread);
//
//}




bool thread::post_task(::generic_object * pobjectTask)
{

   if (::is_null(pobjectTask))
   {

      return false;

   }

   sync_lock sl(mutex());

   m_objectaTask.add(pobjectTask);

   kick_idle();

   return true;

}


bool thread::send_task(::generic_object * pobjectTask, ::duration durationTimeout)
{

   return send_object(message_system, system_message_runnable, pobjectTask, durationTimeout);

}


bool thread::post_object(UINT message, WPARAM wParam, lparam lParam)
{

   if (message == WM_QUIT)
   {

      return true;

   }

   if (!thread_get_run())
   {

      if (lParam != 0)
      {

         __pointer(object) spo((lparam)lParam);


      }

      return false;

   }

   return post_message(message, wParam, lParam);

}


bool thread::post_message(UINT message,WPARAM wParam,lparam lParam)
{

   if(m_bThreadClosed)
   {

      return false;

   }

#ifdef WINDOWS_DESKTOP

   if (m_hthread1 && !m_bAuraMessageQueue)
   {

      WINBOOL bOk = ::PostThreadMessage(m_ithread1, message, wParam, lParam) != FALSE;

      if (!bOk)
      {

         TRACELASTERROR();

      }

      return bOk;

   }

#endif

   return get_mq()->post_message(nullptr, message, wParam, lParam);

}


bool thread::send_object(UINT message, WPARAM wParam, lparam lParam, ::duration durWaitStep)
{

   if(m_bThreadClosed)
   {

      return false;

   }

   if (message == WM_QUIT)
   {

      wait(durWaitStep);

      return true;

   }

   if (m_hthread1 == (HTHREAD)nullptr || !thread_get_run())
   {

      if (lParam != 0)
      {

         __pointer(object) spo((lparam)lParam);


      }

      return false;

   }

   send_message(message, wParam, lParam, durWaitStep);

   return true;

}


bool thread::send_message(UINT message, WPARAM wParam, lparam lParam, ::duration durWaitStep)
{

   if(m_bThreadClosed)
   {

      return false;

   }

   if (message == WM_QUIT)
   {

      wait(durWaitStep);

      return true;

   }

   auto pmessage = __new(::send_thread_message(get_context_object()));

   pmessage->m_message.message = message;
   pmessage->m_message.wParam = wParam;
   pmessage->m_message.lParam = lParam;

   post_message(message_system, system_message_meta, pmessage);

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


bool thread::on_get_thread_name(string& strThreadName)
{

   if (m_strThreadTag.has_char())
   {

      ::thread_set_name(m_strThreadTag);

   }
   else
   {

      ::thread_set_name(type_name());

   }

   return true;

}


::estatus thread::__thread_init()
{

   auto estatus = on_thread_init();

   if (m_pevent)
   {

      m_pevent->set_event();

   }

   return estatus;

}


::estatus thread::on_thread_init()
{

   string strThreadName;

   if (on_get_thread_name(strThreadName))
   {

      set_thread_name(strThreadName);

   }

   if (string(type_name()).contains("synth_thread"))
   {

      output_debug_string("synth_thread thread::thread_proc");

   }
   else if (string(type_name()).ends_ci("out"))
   {

      output_debug_string("synth_thread thread::out");

   }

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


::estatus     thread::main()
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
   ::estatus     estatus = ::success;

   // else check for thread with message loop
   ASSERT_VALID(this);

   try
   {

      m_bReady = true;

      run();

   }
   catch (::exception_pointer pe)
   {

      top_handle_exception(pe);

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

   try
   {

      m_bRunThisThread = false;

   }
   catch (...)
   {

   }

   return estatus;

}


mq* thread::_get_mq()
{

   sync_lock sl(mutex());

   if(!m_bRunThisThread || m_bThreadClosed)
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

   auto estatus = __compose_new(m_pmq);

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

   if (m_hthread1 && !m_bAuraMessageQueue)
   {

      if (::PeekMessage(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
      {

         return TRUE;

      }

   }

#endif

   return false;

}


int_bool thread::get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{

   bool bQuit = false;

#ifdef WINDOWS_DESKTOP

   if (m_bAuraMessageQueue)
   {

      if (!get_mq()->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax))
      {

         if (!is_set_finish())
         {

            set_finish();

         }

         return false;

      }

      return true;

   }

   if (m_pmq)
   {

      if (m_pmq->peek_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax, true))
      {

         m_bRunThisThread = false;

         bQuit = pMsg->message == WM_QUIT;

         if (!bQuit)
         {

            return TRUE;

         }

         __release(m_pmq);

      }

   }

   if (m_hthread1)
   {

      int iRet = ::GetMessage(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax);

      if (iRet == -1)
      {

         DWORD dwLastError = ::GetLastError();

         ::output_debug_string("Last Error : " + __str(dwLastError) + "\n");

      }
      else
      {

         bQuit = !iRet || pMsg->message == WM_QUIT;

         if (!bQuit)
         {

            return TRUE;

         }

      }

   }

#else

   if (get_mq()->get_message(pMsg, oswindow, wMsgFilterMin, wMsgFilterMax))
   {

      return TRUE;

   }

#endif

   if (bQuit)
   {

      if (!is_set_finish())
      {

         set_finish();

      }

   }

   return bQuit;

}


int_bool thread::post_message(oswindow oswindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

   if(m_bThreadClosed)
   {

      return false;

   }

#ifdef WINDOWS_DESKTOP

   if (m_hthread1 && !m_bAuraMessageQueue)
   {

      if (::PostMessage(oswindow, uMessage, wParam, lParam))
      {

         return TRUE;

      }

   }

#endif

   return get_mq()->post_message(oswindow, uMessage, wParam, lParam);

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

   return is_null(this) ? (HTHREAD) nullptr : m_hthread1;

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


bool thread::process_message()
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

      if (msg.message == message_event2)
      {

         if(msg.lParam)
         {

            auto pupdate = new_update();

            pupdate->m_id = (::iptr) msg.wParam;

            pupdate->m_pobjectTopic = (::object *) msg.lParam;

            call_update(pupdate);

         }
         else
         {

            call_update((::iptr) msg.wParam);

         }

      }
      else if (msg.message == message_system)
      {

         if (msg.wParam == system_message_create)
         {

            __pointer(::create) pcreate((lparam)msg.lParam);

            if (pcreate.is_set())
            {

               call_request(pcreate);

            }

         }
         else if (msg.wParam == system_message_pred)
         {

            __pointer(::pred_holder_base) ppred(msg.lParam);

            ppred->call();

         }
         else if (msg.wParam == system_message_runnable)
         {

            __pointer(::context_object) pobjectTask((lparam)msg.lParam);

            pobjectTask->call();

         }
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

      if (msg.message == ::message_redraw)
      {

         auto pinteraction = System.ui_from_handle(msg.hwnd);

         if(::is_set(pinteraction))
         {

            string strType = ::str::demangle(pinteraction->type_name());

            if(strType.contains_ci("filemanager"))
            {

               //INFO("filemanager");

            }

            pinteraction->prodevian_redraw(msg.wParam & 1);

         }
         else
         {

            INFO("message_redraw pinteraction == nullptr");

         }

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

         if(::is_set(pbase->m_puserinteraction))
         {

            auto iMessage = pbase->m_id;

            // short circuit for frequent messages
            if (iMessage == message_apply_visual)
            {

               __pointer(::user::interaction) pinteraction = pbase->m_puserinteraction;

               if(pinteraction)
               {

                  pinteraction->m_pimpl2->_001OnApplyVisual(pbase);

                  return true;

               }

            }
            //else if (iMessage == message_update_notify_icon)
            //{

            //   pbase->m_puserinteraction->route_message(pbase);

            //   pinteraction->m_pimpl2->_001OnApplyVisual(pbase);

            //   return true;

            //}
            //else if (iMessage == message_simple_command)
            //{

            //   __pointer(::user::interaction) pinteraction = pbase->m_puserinteraction;

            //   pinteraction->m_pimpl2->_001OnApplyVisual(pbase);

            //   return true;

            //}


            //if (iMessage > message_midi_sequence_event)
            //{

            //   return true;

            //   int iApp = iMessage - WM_APP;

            //   pbase->m_puserinteraction->message_handler(pbase);

            //}
            //else
            //{

//               return true;

               pbase->m_puserinteraction->message_handler(pbase);

  //          }


         }
         else
         {

            message_handler(pbase);

         }

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


bool thread::raw_process_message()
{

   try
   {

      pointer < ::message::message > spbase;

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

   bool bOk = ::SetThreadPriority(m_hthread1, nPriority) != FALSE;

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

   ASSERT(m_hthread1 != NULL_HTHREAD);

   i32 nPriority = ::GetThreadPriority(m_hthread1);

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





void thread::start()
{

#if defined (WINDOWS_DESKTOP)

   ::ResumeThread(m_hthread1);

#endif

}


u32 thread::ResumeThread()
{

   ASSERT(m_hthread1 != NULL_HTHREAD);

#if defined (WINDOWS_DESKTOP)

   return ::ResumeThread(m_hthread1);

#else

   return 0;

#endif

}


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

      if (msg.message == WM_QUIT) // do not pump, otherwise main loop will not process the message
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

   if (!post_message(::message_null))
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

   post_object(message_system, system_message_create, pcreate);

   return ::success;

}


//::mutex * g_pmutexThreadOn = nullptr;

//map < ITHREAD, ITHREAD, ITHREAD, ITHREAD > * g_pmapThreadOn = nullptr;

CLASS_DECL_AURA bool is_thread_on(ITHREAD id)
{

   sync_lock sl(&::aura::system::g_p->m_mutexThreadOn);

   return ::aura::system::g_p->m_mapThreadOn.plookup(id) != nullptr;

}


CLASS_DECL_AURA bool is_active(::thread * pthread)
{

   if (::is_null(pthread))
   {

      return false;

   }

   return is_thread_on(pthread->m_ithread1);

}

CLASS_DECL_AURA void set_thread_on(ITHREAD id)
{

   sync_lock sl(&::aura::system::g_p->m_mutexThreadOn);

   ::aura::system::g_p->m_mapThreadOn.set_at(id, id);

}


CLASS_DECL_AURA void set_thread_off(ITHREAD id)
{

   sync_lock sl(&::aura::system::g_p->m_mutexThreadOn);

   ::aura::system::g_p->m_mapThreadOn.remove_key(id);

}




CLASS_DECL_AURA void forking_count_thread_null_end(int iOrder)
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

CLASS_DECL_AURA u32 random_processor_index_generator()
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


bool __thread_sleep(thread * pthread)
{

   while (pthread->thread_get_run())
   {

      Sleep(100);

   }

   return false;

}


bool __thread_sleep(thread * pthread, tick tick)
{

   if (tick.m_i < 1000)
   {

      if (!pthread->thread_get_run())
      {

         return false;

      }

      Sleep(tick);

      return pthread->thread_get_run();

   }

   auto iTenths = tick.m_i / 100;

   auto iMillis = tick.m_i % 100;

   try
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

      if(!pthread->thread_get_run())
      {

         return false;

      }

      while(iTenths > 0)
      {

         pthread->m_pevSleep->wait(100_ms);

         if (!pthread->thread_get_run())
         {

            return false;

         }

         iTenths--;

      }

   }
   catch (...)
   {

   }

   return pthread->thread_get_run();

}


bool __thread_sleep(::thread* pthread, sync* psync)
{

   try
   {

      while(pthread->thread_get_run())
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

   return pthread->thread_get_run();

}


bool __thread_sleep(thread * pthread, tick tick, sync* psync)
{

   if (tick.m_i < 1000)
   {

      if (!pthread->thread_get_run())
      {

         return false;

      }

      psync->wait(tick);

      return pthread->thread_get_run();

   }

   auto iTenths = tick.m_i / 100;

   auto iMillis = tick.m_i % 100;

   try
   {

      {

         pthread->m_pevSleep->wait(100);

         if (!pthread->thread_get_run())
         {

            return false;

         }

         iTenths--;

      }

   }
   catch (...)
   {

   }

   return pthread->thread_get_run();

}


CLASS_DECL_AURA bool thread_sleep(tick tick, sync * psync)
{

   auto pthread = ::get_thread();

   if (::is_null(pthread))
   {

      if (::is_null(psync))
      {

         if (__os(tick) == INFINITE)
         {

         }
         else
         {

            ::Sleep(tick);

         }

      }
      else
      {

         if (__os(tick) == INFINITE)
         {

            return psync->lock();

         }
         else
         {

            return psync->lock(tick);

         }

      }

      return true;

   }

   if (::is_null(psync))
   {

      if (__os(tick) == INFINITE)
      {

         return __thread_sleep(pthread);

      }
      else
      {

         return __thread_sleep(pthread, tick);

      }

   }
   else
   {

      if (__os(tick) == INFINITE)
      {

         return __thread_sleep(pthread, psync);

      }
      else
      {

         return __thread_sleep(pthread, tick, psync);

      }

   }
}


CLASS_DECL_AURA bool thread_pump_sleep(DWORD dwMillis, sync * psync)
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


CLASS_DECL_AURA bool app_sleep(tick tick)
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

         if (get_context_application() && get_context_application()->is_set_finish())
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

      if (get_context_application() && get_context_application()->is_set_finish())
      {

         return false;

      }

      iTenths--;

      Sleep(100);

   }

   Sleep((u32) iMillis);

   return !get_context_application() || !get_context_application()->is_set_finish();

}



//int ::status::result::get_exit_code()
//{
//
//   if(m_iaErrorCode2.get_count() <= 0)
//   {
//
//      return 0;
//
//   }
//
//   if(m_iaErrorCode2.get_count() == 1)
//   {
//
//      return m_iaErrorCode2[0];
//
//   }
//
//   return -100000 - (int) m_iaErrorCode2.get_count();
//
//}


::estatus     thread::get_result_status()
{

   return m_result.status();

}


//void thread::on_event(::u64 u, ::object * pobject)
//{
//
//}



CLASS_DECL_AURA void defer_create_thread(::object* pobjectContext)
{

   auto pthread = ::get_thread();

   if (::is_null(pthread))
   {

      auto pthreadNew = pobjectContext->__create_new < ::thread > ();

      pthreadNew->add_ref(OBJ_REF_DBG_P_NOTE(pobjectContext, nullptr));

      set_thread(pthreadNew);

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


::duration thread::set_file_sharing_violation_timeout(::duration duration)
{

   return get_file_info()->m_durationFileSharingViolationTimeout = duration;

}


// please refer to object::set_finish verses/documentation
// ::user::interaction implements custom/dedicated set_finish protocol/feature/function
// this is why default set_finish isn't/(and shouldn't be) called here
// (like is done for a regular object instance of *object* class)
// (look at ::object::delete_this implementation to confirm/study the default set_finish call)
void thread::delete_this()
{

   context_object::delete_this();

}


