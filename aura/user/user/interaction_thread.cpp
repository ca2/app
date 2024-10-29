#include "framework.h"
#include "frame_interaction.h"
#include "interaction_thread.h"
#include "interaction_graphics_thread.h"
#include "interaction.h"
#include "user.h"
#include "system.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/keep.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "apex/user/user/message.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/platform/session.h"


#ifdef WINDOWS_DESKTOP


//int windows_desktop1_main(HINSTANCE hInstance, int       nCmdShow);

//
//void verisimple_message_loop()
//{
//
//   MSG msg;
//
//   while (::GetMessage(&msg, nullptr, 0, 0))
//   {
//
//      //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//      {
//
//         TranslateMessage(&msg);
//
//         DispatchMessage(&msg);
//
//      }
//
//   }
//
//}


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


   void thread::initialize_user_thread(::user::interaction * puserinteraction)
   {

      initialize(puserinteraction);

      m_puserinteractionUserThread = puserinteraction;

      string strType = ::type(m_puserinteractionUserThread).name();

      m_strDebugType = strType;

      //m_bSimpleMessageLoop = false;

      //return estatus;

   }


#ifdef _DEBUG


   i64 thread::increment_reference_count()
   {

      return ::thread::increment_reference_count();

   }


   i64 thread::decrement_reference_count()
   {

      return ::thread::decrement_reference_count();

   }


   i64 thread::release()
   {

      return ::thread::release();

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

   void thread::task_caller_on_init()
   {

      //if (!m_bCreateNativeWindowOnInteractionThread)
      //{

      //   if (!m_puserinteractionUserThread->_native_create_window_ex(*m_pusersystem))
      //   {

      //      //delete m_pusersystem;

      //      m_pusersystem = nullptr;

      //      m_estatus = error_failed;

      //      finish();

      //      return ::error_failed;

      //   }

      //}


      //return ::success;

   }


   void thread::init_task()
   {

      //auto estatus = 
      
      ::thread::init_task();

   /*   if (!estatus)
      {

         return estatus;

      }*/

//#ifdef WINDOWS_DESKTOP
//
//      node()->defer_co_initialize_ex(false);
//
//#endif

      //set_topic_text("window_thread_" + ::type(m_puserinteractionUserThread).name()) + "> ";

      ::task_set_name(::type(m_puserinteractionUserThread).name());

#ifdef WINDOWS_DESKTOP

      //attach_thread_input_to_main_thread();

      attach_thread_input_to_main_thread(true);

#endif

      if (!m_puserinteractionUserThread->is_system_message_window())
      {

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

         initialize_tsf_thread();

#endif

      }

      //__construct(m_puserinteractionUserThread, m_puserinteractionUserThread->m_pthreadUserInteraction);
      
      m_eflagElement += e_flag_running;

      __keep_flag_on(m_puserinteractionUserThread->layout().m_eflag, ::user::interaction_layout::flag_creating);

      //fork([this]()
      //   {

      //      task_set_name("test");

            //windows_desktop1_main(psystem->m_hinstance, SW_SHOWNORMAL);

      //  });

      //if (m_bCreateNativeWindowOnInteractionThread)
      //{

      auto pwindowing = m_puserinteractionUserThread->windowing();

      //m_puserinteractionUserThread->windowing() = pwindowing;

      //estatus =
      
      //m_puserinteractionUserThread->operating_system_create_host(e_parallelization_asynchronous);

      //m_puserinteractionUserThread->create_window();

      ///*if(!estatus)
      //{*/

      //   m_puserinteractionUserThread->m_pusersystem->m_procedureFailure();

      //   if (is_debugger_attached())
      //   {

      //      output_error_message("Window not created", "Window not created", e_message_box_icon_warning);

      //   }

      //   //delete m_pusersystem;

      //   //m_pusersystem = nullptr;

      //   m_estatus = error_failed;

      //   destroy();

      //   return estatus;

      //}

//     auto pusersystem = m_puserinteractionUserThread->m_pusersystem;
//
//      if(pusersystem && pusersystem->m_procedureSuccess)
//      {
//
//         pusersystem->m_procedureSuccess();
//
//      }


      //}
      //else
      //{ 
      //
      //   __refer(m_puserinteractionUserThread->m_pthreadUserInteraction, this);

      //   uiptra().add(m_puserinteractionUserThread);

      //}

      //m_himc = ImmGetContext(m_puserinteractionUserThread->get_handle());

//      m_oswindow = m_puserinteractionUserThread->m_pwindow->oswindow();

//      if(m_puserinteractionUserThread->const_layout().sketch().is_screen_visible())
//      {
//
//         m_puserinteractionUserThread->set_reposition();
//
//         m_puserinteractionUserThread->set_need_layout();
//
//         m_puserinteractionUserThread->set_need_redraw();
//
//         m_puserinteractionUserThread->post_redraw();
//
//
//      }

      //delete m_pusersystem;

      //m_pusersystem = nullptr;

      //return true;

   }




   //bool thread::pump_runnable()
   //{

   //   return ::thread::pump_runnable();

   //}


   //bool thread::task_get_run() const
   //{

   //   


   //   return ::user::thread::task_get_run();

   //}

   void thread::on_task_quit()
   {

      if (m_puserinteractionUserThread
   && m_puserinteractionUserThread->m_ewindowflag & e_window_flag_is_window
   && ::thread::has_finishing_flag())
      {

         m_puserinteractionUserThread->destroy_window();

      }

      ::thread::on_task_quit();

   }


   //bool thread::task_iteration()
   //{

   //   try
   //   {

   //      //auto estatus =
   //      
   //      get_message(&m_message, nullptr, 0, 0);

   //      if(m_message.m_atom == e_message_quit)
   //      {

   //         if (m_strDebugType.contains("filemanager"))
   //         {

   //            //information() << "filemanager";

   //         }

   //         information()(e_trace_category_appmsg) << ::type(this).name() << " thread::pump_message - Received e_message_quit.\n";

   //         //::information(::type(this).name()) << " thread::pump_message - Received e_message_quit.\n");

   //         m_nDisablePumpCount++; // application must die
   //         // Note: prevents calling message loop things in 'exit_thread'
   //         // will never be decremented
   //         return false;

   //      }

   //      if(m_message.m_atom == e_message_left_button_down)
   //      {

   //         informationf("pump_message e_message_left_button_down");

   //      }

   //      if (m_message.m_atom == e_message_quit)
   //      {


   //      }

   //      if(m_message.m_atom == e_message_left_button_down)
   //      {

   //         informationf("::user::thread::LBUTTONDOWN");

   //      }
   //      else if(m_message.m_atom == e_message_left_button_up)
   //      {

   //         informationf("::user::thread::LBUTTONUP");

   //      }

   //      if (m_message.m_atom != e_message_kick_idle && m_message.m_atom != e_message_quit)
   //      {

   //         if (m_message.m_atom == e_message_destroy_window)
   //         {

   //            if (m_strDebugType.contains("notify_icon"))
   //            {

   //               information() << "notify_icon";

   //            }
   //            else if (m_strDebugType.contains("main_frame"))
   //            {

   //               information() << "main_frame";

   //            }

   //         }

   //         //if (estatus != status_kick_idle)
   //         {

   //            process_message();

   //         }

   //      }

   //      return true;

   //   }
   //   catch (const ::exception & e)
   //   {

   //      if (m_strDebugType.contains("filemanager"))
   //      {

   //         //information() << "filemanager";

   //      }

   //      handle_exception(e);

   //      //if (handle_exception(e))
   //      //{

   //      //   return true;

   //      //}

   //      //// get_app() may be it self, it is ok...
   //      //if (papp->final_handle_exception(e))
   //      //{

   //      //   return true;

   //      //}

   //   }
   //   catch (...)
   //   {

   //      information() << "... exception";

   //   }

   //   return false;

   //}


   bool thread::process_message()
   {

      try
      {

         MESSAGE & msg = m_message;

         if(msg.m_atom == e_message_mouse_move)
         {


         }
         else if(msg.m_atom == e_message_left_button_down)
         {

            informationf("e_message_left_button_down");

         }
         else if(msg.m_atom == e_message_left_button_up)
         {

            informationf("e_message_left_button_up");

         }

         auto oswindow = msg.oswindow;

         if(oswindow)
         {

            auto pwindow = system()->windowing()->window(oswindow);

            if (!pwindow)
            {

               informationf("What is going on? not going to redraw");

            }
            else
            {

               //informationf("is it going to redraw?");

               auto puserframe = pwindow->m_puserinteraction;


                  if (puserframe)
                  {

                     if (msg.m_atom == ::e_message_redraw)
                     {

                        throw ::exception(error_failed, "Please post e_message_redraw directly to the graphics thread");

                        //string strType = ::type(puserinteraction).name();

                        //if (strType.case_insensitive_contains("filemanager"))
                        //{

                        //   //information() << "filemanager";

                        //}

                        //puserinteraction->prodevian_redraw(msg.wParam & 1);

                        return true;

                     }

#if !defined(WINDOWS_DESKTOP)

                     else
                     {

                        if(msg.m_atom == e_message_left_button_down)
                        {

                           informationf("e_message_left_button_down");

                        }
                        else if(msg.m_atom == e_message_left_button_up)
                        {

                           informationf("e_message_left_button_up");

                        }

                        auto pmessage = puserframe->get_message(msg.m_atom, msg.wParam, msg.lParam);

                        if (pmessage)
                        {

                           if(pmessage->m_atom == e_message_left_button_down)
                           {

                              informationf("e_message_left_button_down");

                           }

                           pwindow->message_handler(pmessage);

                           return ::success;

                        }

                     }

#endif

               }

            }

         }

      }
      catch(const ::exception & exception)
      {
         
         error() <<"Exception Reached Thread Loop" << exception.m_strMessage << exception.m_strDetails;

      }
      catch(...)
      {
         
         error() <<"Exception Reached Thread Loop";

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
   //         lresult lresult = ::DispatchMessageW(&msg);
   //
   //         return true;
   //
   //      }
   //
   //#endif
   //
   //      return true;

   }


   bool thread::process_message(::message::message * pmessage)
   {

      if(pmessage->m_oswindow)
      {

         return process_user_message(pmessage);

      }
      else
      {

         return process_thread_message(pmessage);

      }

   }


   bool thread::process_user_message(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      if (::is_set(pusermessage))
      {

         auto puserinteraction = pusermessage->m_pwindow->m_puserinteraction;

         if (::is_set(puserinteraction))
         {

            ::i64 iMessage = pmessage->m_atom.as_i64();

            //throw ::exception(todo("interaction"));
            //throw ::exception(todo("thread"));

//            //short circuit for frequent messages
//            if (iMessage == e_message_apply_visual)
//            {
//
//               //throw ::exception(todo("interaction"));
//               //throw ::exception(todo("thread"));
//
//               if (puserinteraction->m_pinteractionimpl)
//               {
//
//                  puserinteraction->user->_001OnApplyVisual(pusermessage);
//
//                  return true;
//
//               }
//
//            }
//            else
               if (iMessage == e_message_update_notify_icon)
            {

               puserinteraction->route_message(pusermessage);

               return true;

            }
//            else if (iMessage == e_message_simple_command)
//            {
//
//               puserinteraction->m_pinteractionimpl->_001OnApplyVisual(pusermessage);
//
//               return true;
//
//            }

            //if (iMessage > e_message_midi_sequence_event)
            //{

            //   return true;

            //   ::i64 iApp = iMessage - WM_APP;

            //   pusermessage->m_puserinteractionUserThread->message_handler(pusermessage);

            //}
            //else
            //{

            //      //return true;
            //   //throw ::exception(todo("interaction"));
            //   //throw ::exception(todo("thread"));

            puserinteraction->message_handler(pusermessage);

            return true;

         }

      }

      return ::thread::process_message(pmessage);

   }


   void thread::on_destroy()
   {

      //auto estatus = 
      
      ::channel::on_destroy();

      //return estatus;

   }


   void thread::enumerate_composite(matter_array& a)
   {


   }


   //void thread::set_finish_composites(::property_object * pcontextobjectFinish)
   //{

   //   auto estatus = channel::set_finish_composites(pcontextobjectFinish);

   //   if (estatus == error_pending)
   //   {

   //      return estatus;

   //   }

   //   if (m_puserinteractionUserThread)
   //   {

   //      auto puserinteraction = m_puserinteractionUserThread;

   //      if (puserinteraction)
   //      {

   //         if (!m_puserinteractionUserThread->m_bDestroying)
   //         {

   //            puserinteraction->DestroyWindow();

   //         }

   //      }

   //      return error_pending;

   //   }

   //   if (task_active())
   //   {

   //      set_finish_bit();

   //      post_quit();

   //      return error_pending;

   //   }

   //   return ::success;

   //}


   void thread::run()
   {

      ::thread::run();

//      ASSERT_VALID(this);
//
//      ::string strType = ::type(m_puserinteractionUserThread.m_p).name();
//
//      information()
//         << "usrthrd " << strType << " : "
//         << "user::thread::run";
//
//      if (m_strDebugType.contains("main_frame"))
//      {
//
//         informationf("xxthread::run from main_frame");
//
//      }
//
//      // get the keystroke manager interfce
//      //if (SUCCEEDED(m_pthreadmgr->QueryInterface(IID_ITfKeystrokeMgr, (void**)& m_pKeyMgr)))
//      //{
//      //   // get the message pump wrapper interface
//      //   if (SUCCEEDED(m_pthreadmgr->QueryInterface(IID_ITfMessagePump, (void**)& m_pMsgPump)))
//      //   {
//
//      //   }
//      //}
//      int_bool    fResult = true;
//
//      //while (fResult)
//      //{
//      //   MSG     msg;
//      //   BOOL    fEaten;
//
//         /*
//         Get the next message in the queue. fResult receives false if e_message_quit is encountered
//         */
//         //            }
//
//               //}
//
//                     //if (FAILED(pMsgPump->GetMessage(&msg, NULL, 0, 0, &fResult)))
//                     //{
//                     //   fResult = false;
//                     //}
//                     //else if (e_message_key_down == msg.message)
//                     //{
//                     //   // does an ime want it?
//                     //   if (pKeyMgr->TestKeyDown(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten &&
//                     //      pKeyMgr->KeyDown(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten)
//                     //   {
//                     //      continue;
//                     //   }
//                     //}
//                     //else if (e_message_key_up == msg.message)
//                     //{
//                     //   // does an ime want it?
//                     //   if (pKeyMgr->TestKeyUp(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten &&
//                     //      pKeyMgr->KeyUp(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten)
//                     //   {
//                     //      continue;
//                     //   }
//                     //}
//
//                     //if (fResult)
//                     //{
//                     //   TranslateMessage(&msg);
//                     //   DispatchMessage(&msg);
//                     //}
//
//                     //if (e_message_quit == msg.message)
//                     //{
//                     //   nReturn = (int)msg.wParam;
//                     //}
//
//      if (m_bMessageThread)
//      {
//
//         bool bWindowSetFinish = false;
//
//         while (task_get_run())
//         {
//
//            if (has_finishing_flag())
//            {
//
//               if (m_puserinteractionUserThread && !m_puserinteractionUserThread->has_destroying_flag())
//               {
//
//                  m_puserinteractionUserThread->destroy_window();
//
//               }
//
//            }
//
//            if (m_puserinteractionUserThread && m_puserinteractionUserThread->m_pacmewindowingwindow)
//            {
//
//               m_puserinteractionUserThread->window()->process_messages();
//
//            }
//
//            if (!pump_message())
//            {
//
//               if (m_strDebugType.contains("filemanager"))
//               {
//
//                  //information() << "filemanager";
//
//               }
//
//               if (m_strDebugType.contains("main_frame"))
//               {
//
//                  informationf("!xxm_bSimpleMessageLoop !xxpump_message xxthread::run from main_frame");
//
//               }
//
//               break;
//
//            }
//
////            if (m_bSetFinish)
////            {
////
////               if (!bWindowSetFinish)
////               {
////
////                  bWindowSetFinish = true;
////
////                  if (m_puserinteractionUserThread)
////                  {
////
////                     auto puserinteraction = m_puserinteractionUserThread;
////
////                     if (puserinteraction)
////                     {
////
////                        puserinteraction->destroy_window();
////
////                     }
////
////                  }
////
////               }
////
////            }
//
//         }
//
//      }
//
//      //m_pMsgPump->Release();
//
//      //   m_pKeyMgr->Release();
//
//      if (m_strDebugType.contains("main_frame"))
//      {
//
//         informationf("ending xxthread::run from main_frame");
//
//      }
//
//      if (m_strDebugType.contains("filemanager"))
//      {
//
//         //information() << "filemanager";
//
//      }
//
//      //return m_estatus;

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   int thread::_GetMessage(MESSAGE * lpMsg, HWND hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
//   {
//
//#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
//
//      while (m_pmessagepump && m_pkeystrokemgr)
//      {
//
//         BOOL fResult = true;
//
//         if (FAILED(m_pmessagepump->GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, &fResult)))
//         {
//
//            return false;
//
//         }
//         else
//         {
//
//            BOOL    fEaten;
//
//            if (e_message_key_down == lpMsg->message)
//            {
//               // does an ime want it?
//               if (m_pkeystrokemgr->TestKeyDown(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten &&
//                  m_pkeystrokemgr->KeyDown(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten)
//               {
//                  continue;
//               }
//            }
//            else if (e_message_key_up == lpMsg->message)
//            {
//               // does an ime want it?
//               if (m_pkeystrokemgr->TestKeyUp(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten &&
//                  m_pkeystrokemgr->KeyUp(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten)
//               {
//                  continue;
//               }
//            }
//
//         }
//
//         return true;
//
//      }
//
//#endif
//
//      int iRet = ::thread::_GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
//
//      if (iRet <= 0)
//      {
//
//         return iRet;
//
//      }
//
//      return iRet;
//
//      //if (ImmIsUIMessageW(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam))
//      //{
//
//      //   return iRet;
//
//      //}
//
//      //return iRet;
//
//   }
//
//
//#endif


   bool thread::task_get_run() const
   {

      if (m_puserinteractionUserThread
         && !(m_puserinteractionUserThread->m_ewindowflag & e_window_flag_destroyed))
      {

         return true;

      }

      return ::thread::task_get_run();

   }


//   void thread::start_window_visual()
//   {
//
//      //m_evApplyVisual.ResetEvent();
//
//      m_puserinteractionUserThread->post_message(e_message_apply_visual);
//
//   }


   //void thread::destroy()
   //{

   //   return ::thread::destroy();

   //}


   void thread::destroy()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_puserinteractionUserThread)
      {

         if (m_puserinteractionUserThread->window()->m_bDestroyImplOnly)
         {

            m_puserinteractionUserThread->window()->destroy_impl_only();

         }
         else if (m_puserinteractionUserThread)
         {

            m_puserinteractionUserThread->destroy_window();

         }

      }
      else
      {

         //string strType = ::type(m_puserinteractionUserThread).name();

         if (m_strDebugType.contains("filemanager"))
         {

            //information() << "filemanager";

         }

         ::thread::destroy();

      }

      //return ::success;

   }


   void thread::set_finish()
   {

      ::thread::set_finish();

   }


   void thread::term_task()
   {

      if (m_puserinteractionUserThread && m_puserinteractionUserThread && m_puserinteractionUserThread->m_strName.contains("notify_icon"))
      {
         information() << "notify_icon";
      }

      _synchronous_lock synchronouslock(this->synchronization());

      m_puserinteractionUserThread.release();

      //if (m_pthreadmgr)
      //{
      //   m_pthreadmgr->Deactivate();

      //   m_pthreadmgr->Release();
      //   m_pthreadmgr = NULL;
      //}

      ::thread::term_task();

   }


} // namespace user




