#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/message.h"
#include "interaction_thread.h"
#include "interaction_prodevian.h"


#ifdef WINDOWS_DESKTOP


int windows_desktop1_main(HINSTANCE hInstance, int       nCmdShow);


void verisimple_message_loop()
{

   MSG msg;

   while (::GetMessage(&msg, nullptr, 0, 0))
   {

      //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      {

         TranslateMessage(&msg);

         DispatchMessage(&msg);

      }

   }

}


#endif


namespace user
{


   thread::thread()
   {

      m_bMessageThread = true;

//#ifdef WINDOWS_DESKTOP
//
//      m_bCreateNativeWindowOnInteractionThread = true;
//
//#else
//
//      m_bCreateNativeWindowOnInteractionThread = false;
//
//#endif


   }

   thread::~thread()
   {

   }


   ::estatus thread::initialize_user_thread(interaction_impl * pimpl, __pointer(::user::create_struct) pcreatestruct)
   {

      auto estatus = initialize(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      m_pimpl = pimpl;

      //m_pcreatestruct = new ::user::create_struct(pcreatestruct);
      m_pcreatestruct = pcreatestruct;

      string strType = ::str::demangle(m_pimpl->m_puserinteraction->type_name());

      m_strDebugType = strType;

      m_bSimpleMessageLoop = false;

      return estatus;

   }


#ifdef DEBUG


   i64 thread::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::thread::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 thread::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::thread::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 thread::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::thread::release(OBJ_REF_DBG_ARGS);

   }


#endif


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

   HRESULT thread::initialize_tsf_thread()
   {

      HRESULT hr = S_OK;

      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr.CoCreateInstance(CLSID_TF_ThreadMgr, nullptr, CLSCTX_INPROC_SERVER);

      }

      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr.As(m_pthreadmgrex);

      }

      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgrex->ActivateEx(&m_tfClientID, TF_TMAE_UIELEMENTENABLEDONLY);

      }


      // get the keystroke manager interfce
      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr->QueryInterface(IID_ITfKeystrokeMgr, (void **)& m_pkeystrokemgr);

      }

      // get the message pump wrapper interface
      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr->QueryInterface(IID_ITfMessagePump, (void **)& m_pmessagepump);

      }


      return hr;

   }

#endif

   ::estatus thread::task_caller_on_init()
   {

      //if (!m_bCreateNativeWindowOnInteractionThread)
      //{

      //   if (!m_pimpl->_native_create_window_ex(*m_pcreatestruct))
      //   {

      //      //delete m_pcreatestruct;

      //      m_pcreatestruct = nullptr;

      //      m_estatus = error_failed;

      //      finish();

      //      return ::error_failed;

      //   }

      //}


      return ::success;

   }


   ::estatus thread::init_thread()
   {

      auto estatus = ::thread::init_thread();

      if (!estatus)
      {

         return estatus;

      }

#ifdef WINDOWS_DESKTOP

      HRESULT hr = CoInitialize(NULL);

#endif

      set_topic_text("window_thread_" + ::str::demangle(m_pimpl->m_puserinteraction->type_name()) + "> ");

      ::set_thread_name(::str::demangle(m_pimpl->m_puserinteraction->type_name()));

#ifdef WINDOWS_DESKTOP

      //attach_thread_input_to_main_thread();


#endif


      if (!m_pimpl->m_puserinteraction->is_system_message_window())
      {

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

         initialize_tsf_thread();

#endif

      }

      //__compose(m_pimpl->m_puserinteraction, m_pimpl->m_puserinteraction->m_pthreadUserInteraction);

      __keep_flag_on(m_pimpl->m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_creating);

      //fork([this]()
      //   {

      //      set_thread_name("test");

            //windows_desktop1_main(System.m_hinstance, SW_SHOWNORMAL);

      //  });

      //if (m_bCreateNativeWindowOnInteractionThread)
      //{

         if (!m_pimpl->_native_create_window_ex(m_pcreatestruct))
         {

            //delete m_pcreatestruct;

            m_pcreatestruct = nullptr;

            m_estatus = error_failed;

            finish();

            return false;

         }

      //}
      //else
      //{ 
      //
      //   __refer(m_pimpl->m_puserinteraction->m_pthreadUserInteraction, this);

      //   uiptra().add(m_pimpl->m_puserinteraction);

      //}

            //m_himc = ImmGetContext(m_pimpl->get_handle());

            __bind(this, m_pprodevian, m_pimpl->m_pprodevian);

            m_oswindow = m_pimpl->m_oswindow;

            //delete m_pcreatestruct;

            m_pcreatestruct = nullptr;

      return true;

   }

   bool thread::pump_runnable()
   {

      {

         sync_lock sl(mutex());

         if (m_messagebasea.has_elements())
         {

            auto pbase = m_messagebasea.first_pointer();

            m_messagebasea.remove_at(0);

            sl.unlock();

            m_pimpl->m_puserinteraction->message_handler(pbase);

            return true;

         }

      }

      return ::thread::pump_runnable();

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
      catch (...)
      {

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

      }

      try
      {

         if (!get_message(&m_message, nullptr, 0, 0))
         {

            if (m_strDebugType.contains("filemanager"))
            {

               //INFO("filemanager");

            }

            TRACE(trace_category_appmsg, trace_level_information, string(type_name()) + " thread::pump_message - Received e_message_quit.\n");

            ::output_debug_string(string(type_name()) + " thread::pump_message - Received e_message_quit.\n");

            m_nDisablePumpCount++; // application must die
            // Note: prevents calling message loop things in 'exit_thread'
            // will never be decremented
            return false;

         }

         if (m_message.message == e_message_quit)
         {

            if (m_pimpl 
               && m_pimpl->m_puserinteraction->m_ewindowflag & window_flag_is_window
               && ::thread::finish_bit())
            {

               m_pimpl->m_puserinteraction->DestroyWindow();

            }

         }


         if(m_message.message == e_message_left_button_down)
         {

            ::output_debug_string("::user::thread::LBUTTONDOWN\n");

         }
         else if(m_message.message == e_message_left_button_up)
         {

            ::output_debug_string("::user::thread::LBUTTONUP\n");

         }

         if (m_message.message != WM_KICKIDLE
            && m_message.message != e_message_quit)
         {

            if (m_message.message == e_message_destroy_window && m_strDebugType.contains("notify_icon"))
            {

               INFO("notify_icon");

            }

            process_message();

         }

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
      catch (...)
      {

         INFO("... exception");

      }

      return false;

   }


   ::estatus thread::process_message()
   {

   try
   {

      MESSAGE & msg = m_message;

      if (msg.message == ::e_message_redraw)
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

         //   INFO("e_message_redraw pinteraction == nullptr");

         }

         return true;

      }

}
catch(...)
{
}

      return ::thread::process_message();

//      MESSAGE & msg = m_message;
//
//#ifdef WINDOWS_DESKTOP
//
//      if (msg.hwnd != nullptr)
//      {
//
//         ::TranslateMessage(&msg);
//
//         ::DispatchMessage(&msg);
//
//         return true;
//
//      }
//      else
//      {
//
//         ::TranslateMessage(&msg);
//
//         LRESULT lresult = ::DispatchMessageW(&msg);
//
//         return true;
//
//      }
//
//#endif
//
//      return true;

   }


   ::estatus thread::process_base_message(::message::base * pbase)
   {

      if(::is_set(pbase->userinteraction()))
      {

         ::i64 iMessage = pbase->m_id;
            //__throw(todo("interaction"));
            //__throw(todo("thread"));

             //short circuit for frequent messages
         if (iMessage == e_message_apply_visual)
         {

               //__throw(todo("interaction"));
               //__throw(todo("thread"));

            auto pinteraction = pbase->userinteraction();

            if(pinteraction)
            {

               pinteraction->m_pimpl2->_001OnApplyVisual(pbase);

               return true;

            }

         }
         else if (iMessage == e_message_update_notify_icon)
         {

            pbase->userinteraction()->route_message(pbase);

            return true;

         }
         else if (iMessage == e_message_simple_command)
         {

            auto pinteraction = pbase->userinteraction();

            pinteraction->m_pimpl2->_001OnApplyVisual(pbase);

            return true;

         }

         //if (iMessage > e_message_midi_sequence_event)
         //{

         //   return true;

         //   ::i64 iApp = iMessage - WM_APP;

         //   pbase->m_puserinteraction->message_handler(pbase);

         //}
         //else
         //{

         //      //return true;
         //   //__throw(todo("interaction"));
         //   //__throw(todo("thread"));

            pbase->userinteraction()->message_handler(pbase);

         //}

         return true;

      }

      return ::thread::process_base_message(pbase);

   }


   ::estatus thread::set_finish_composites(::context_object * pcontextobjectFinish)
   {

      auto estatus = channel::set_finish_composites(pcontextobjectFinish);

      if (estatus == error_pending)
      {

         return estatus;

      }

      if (m_pimpl)
      {

         auto puserinteraction = m_pimpl->m_puserinteraction;

         if (puserinteraction)
         {

            if (!m_pimpl->m_bDestroying)
            {

               puserinteraction->DestroyWindow();

            }

         }

         return error_pending;

      }

      if (task_active())
      {

         set_finish_bit();

         post_quit();

         return error_pending;

      }

      return ::success;

   }


   ::estatus thread::run()
   {

      ASSERT_VALID(this);

      INFO("user::thread::run");

      if (m_strDebugType.contains("main_frame"))
      {

         output_debug_string("xxthread::run from main_frame");

      }

      // get the keystroke manager interfce
      //if (SUCCEEDED(m_pthreadmgr->QueryInterface(IID_ITfKeystrokeMgr, (void**)& m_pKeyMgr)))
      //{
      //   // get the message pump wrapper interface
      //   if (SUCCEEDED(m_pthreadmgr->QueryInterface(IID_ITfMessagePump, (void**)& m_pMsgPump)))
      //   {

      //   }
      //}
            int_bool    fResult = TRUE;

            //while (fResult)
            //{
            //   MSG     msg;
            //   BOOL    fEaten;

               /*
               Get the next message in the queue. fResult receives FALSE if e_message_quit is encountered
               */
//            }

      //}

            //if (FAILED(pMsgPump->GetMessage(&msg, NULL, 0, 0, &fResult)))
            //{
            //   fResult = FALSE;
            //}
            //else if (e_message_key_down == msg.message)
            //{
            //   // does an ime want it?
            //   if (pKeyMgr->TestKeyDown(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten &&
            //      pKeyMgr->KeyDown(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten)
            //   {
            //      continue;
            //   }
            //}
            //else if (e_message_key_up == msg.message)
            //{
            //   // does an ime want it?
            //   if (pKeyMgr->TestKeyUp(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten &&
            //      pKeyMgr->KeyUp(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten)
            //   {
            //      continue;
            //   }
            //}

            //if (fResult)
            //{
            //   TranslateMessage(&msg);
            //   DispatchMessage(&msg);
            //}

            //if (e_message_quit == msg.message)
            //{
            //   nReturn = (int)msg.wParam;
            //}

      while (thread_get_run())
      {

         if (!pump_message())
         {

            if (m_strDebugType.contains("filemanager"))
            {

               //INFO("filemanager");

            }

            if (m_strDebugType.contains("main_frame"))
            {

               output_debug_string("!xxm_bSimpleMessageLoop !xxpump_message xxthread::run from main_frame");

            }

            break;

         }


      }
      //m_pMsgPump->Release();

      //   m_pKeyMgr->Release();

      if (m_strDebugType.contains("main_frame"))
      {

         output_debug_string("ending xxthread::run from main_frame");

      }

      if (m_strDebugType.contains("filemanager"))
      {

         //INFO("filemanager");

      }

      return m_estatus;

   }


#ifdef WINDOWS_DESKTOP


   int thread::_GetMessage(LPMESSAGE lpMsg, HWND hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
   {

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

      while (m_pmessagepump && m_pkeystrokemgr)
      {

         BOOL fResult = TRUE;

         if (FAILED(m_pmessagepump->GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, &fResult)))
         {

            return FALSE;

         }
         else
         {

            BOOL    fEaten;

            if (e_message_key_down == lpMsg->message)
            {
               // does an ime want it?
               if (m_pkeystrokemgr->TestKeyDown(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten &&
                  m_pkeystrokemgr->KeyDown(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten)
               {
                  continue;
               }
            }
            else if (e_message_key_up == lpMsg->message)
            {
               // does an ime want it?
               if (m_pkeystrokemgr->TestKeyUp(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten &&
                  m_pkeystrokemgr->KeyUp(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten)
               {
                  continue;
               }
            }

         }

         return TRUE;

      }

#endif

      int iRet = ::thread::_GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);

      if (iRet <= 0)
      {

         return iRet;

      }

      return iRet;

      //if (ImmIsUIMessageW(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam))
      //{

      //   return iRet;

      //}

      //return iRet;

   }


#endif


   bool thread::thread_get_run() const
   {

      if (m_pimpl)
      {

         return true;

      }

      return ::thread::thread_get_run();

   }


   void thread::start_window_visual()
   {

      m_evApplyVisual.ResetEvent();

      m_pimpl->m_puserinteraction->post_message(e_message_apply_visual);

   }


   ::estatus thread::finish(::context_object * pcontextobjectFinish)
   {

      return ::thread::finish(pcontextobjectFinish);

   }


   void thread::finalize()
   {

      sync_lock sl(mutex());

      if (m_pimpl)
      {

         if (m_pimpl->m_bDestroyImplOnly)
         {

            m_pimpl->destroy_impl_only();

         }
         else if (m_pimpl->m_puserinteraction)
         {

            m_pimpl->m_puserinteraction->DestroyWindow();

         }

      }
      else
      {

         //string strType = m_puserinteraction->type_name();

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

         ::thread::finalize();

      }

   }


   void thread::term_thread()
   {

      if (m_pimpl && m_pimpl->m_puserinteraction && m_pimpl->m_puserinteraction->m_strName.contains("notify_icon"))
      {
         INFO("notify_icon");
      }

      sync_lock sl(mutex());

      m_pimpl.release();

      //if (m_pthreadmgr)
      //{
      //   m_pthreadmgr->Deactivate();

      //   m_pthreadmgr->Release();
      //   m_pthreadmgr = NULL;
      //}

      ::thread::term_thread();

   }


} // namespace user




