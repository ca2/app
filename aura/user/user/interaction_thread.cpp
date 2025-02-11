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


   void thread::initialize_user_thread(::windowing::window * pwindow)
   {

      initialize(pwindow);

      //add_task(puserinteraction);

      //m_pwindow->m_puserinteraction = puserinteraction;

      m_pwindow = pwindow;

      string strType = ::type(m_pwindow->m_pacmeuserinteraction).name();

      m_strDebugType = strType;

      //m_bSimpleMessageLoop = false;

      //return estatus;

   }


#ifdef _DEBUG


   long long thread::increment_reference_count()
   {

      return ::thread::increment_reference_count();

   }


   long long thread::decrement_reference_count()
   {

      return ::thread::decrement_reference_count();

   }


   long long thread::release()
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

         hr = m_pthreadmgr->QueryInterface(IID_ITfKeystrokeMgr, (void **)&m_pkeystrokemgr);

      }

      // get the message pump wrapper interface
      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr->QueryInterface(IID_ITfMessagePump, (void **)&m_pmessagepump);

      }


      return hr;

   }

#endif

   void thread::task_caller_on_init()
   {

      //if (!m_bCreateNativeWindowOnInteractionThread)
      //{

      //   if (!m_pwindow->m_puserinteraction->_native_create_window_ex(*m_pusersystem))
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


   void thread::on_before_branch()
   {

      ::thread::on_before_branch();

   }


   void thread::init_task()
   {

      //auto estatus = 

      if (!system()->is_task_set(m_taskindex))
      {

         throw ::exception(error_wrong_state);

      }

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

               //set_topic_text("window_thread_" + ::type(m_pwindow->m_puserinteraction).name()) + "> ";

      ::task_set_name(::type(m_pwindow->m_pacmeuserinteraction).name());

#ifdef WINDOWS_DESKTOP

      //attach_thread_input_to_main_thread();

      attach_thread_input_to_main_thread(true);

#endif

      auto puserinteraction = m_pwindow->user_interaction();

      if (!puserinteraction->is_system_message_window())
      {

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

         initialize_tsf_thread();

#endif

      }

      //__øconstruct(m_pwindow->m_puserinteraction, m_pwindow->m_puserinteraction->m_pthreadUserInteraction);

      m_eflagElement += e_flag_running;

      //auto puserinteraction = m_pwindow->user_interaction();

      __keep_flag_on(puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_creating);

      //fork([this]()
      //   {

      //      task_set_name("test");

            //windows_desktop1_main(psystem->m_hinstance, SW_SHOWNORMAL);

      //  });

      //if (m_bCreateNativeWindowOnInteractionThread)
      //{

      auto pwindowing = puserinteraction->windowing();

      //puserinteraction->windowing() = pwindowing;

      //estatus =

      //puserinteraction->operating_system_create_host(e_parallelization_asynchronous);

      //puserinteraction->create_window();

      ///*if(!estatus)
      //{*/

      //   puserinteraction->m_pusersystem->m_procedureFailure();

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

//     auto pusersystem = puserinteraction->m_pusersystem;
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
      //   __refer(puserinteraction->m_pthreadUserInteraction, this);

      //   uiptra().add(puserinteraction);

      //}

      //m_himc = ImmGetContext(puserinteraction->get_handle());

//      m_oswindow = puserinteraction->m_pwindow->oswindow();

//      if(puserinteraction->const_layout().sketch().is_screen_visible())
//      {
//
//         puserinteraction->set_reposition();
//
//         puserinteraction->set_need_layout();
//
//         puserinteraction->set_need_redraw();
//
//         puserinteraction->post_redraw();
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


   void thread::term_task()
   {

      {

         auto pwindow = ::transfer(m_pwindow);

         if (pwindow)
         {
            auto puserinteraction = pwindow->user_interaction();

            if (puserinteraction
         && puserinteraction->m_ewindowflag & e_window_flag_is_window
         && ::thread::has_finishing_flag())
            {

               puserinteraction->destroy_window();

            }

         }

      }

      ::thread::term_task();

   }


   //bool thread::task_iteration()
   //{

   //   try
   //   {

   //      //auto estatus =
   //      
   //      get_message(&m_message, nullptr, 0, 0);

   //      if(m_message.m_emessage == e_message_quit)
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

   //      if(m_message.m_emessage == e_message_left_button_down)
   //      {

   //         informationf("pump_message e_message_left_button_down");

   //      }

   //      if (m_message.m_emessage == e_message_quit)
   //      {


   //      }

   //      if(m_message.m_emessage == e_message_left_button_down)
   //      {

   //         informationf("::user::thread::LBUTTONDOWN");

   //      }
   //      else if(m_message.m_emessage == e_message_left_button_up)
   //      {

   //         informationf("::user::thread::LBUTTONUP");

   //      }

   //      if (m_message.m_emessage != e_message_kick_idle && m_message.m_emessage != e_message_quit)
   //      {

   //         if (m_message.m_emessage == e_message_destroy_window)
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

         auto & message = m_message;

         if (message.m_emessage == e_message_mouse_move)
         {


         }
         else if (message.m_emessage == e_message_left_button_down)
         {

            informationf("e_message_left_button_down");

         }
         else if (message.m_emessage == e_message_left_button_up)
         {

            informationf("e_message_left_button_up");

         }

         auto oswindow = message.m_oswindow;

         if (oswindow)
         {

            auto pwindow = system()->windowing()->window(oswindow);

            if (!pwindow)
            {

#ifdef EXTRA_DEBUG

               informationf("What is going on? not going to redraw");

#endif

            }
            else
            {

               //informationf("is it going to redraw?");

               auto puserframe = pwindow->m_pacmeuserinteraction;

               if (puserframe)
               {

                  if (message.m_emessage == ::e_message_redraw)
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

                     if (message.m_emessage == e_message_left_button_down)
                     {

                        informationf("e_message_left_button_down");

                     }
                     else if (message.m_emessage == e_message_left_button_up)
                     {

                        informationf("e_message_left_button_up");

                     }

                     ::cast < ::user::interaction > puserinteractionFrame = puserframe;

                     auto pmessage = puserinteractionFrame->get_message(message.m_emessage, message.m_wparam, message.m_lparam);

                     if (pmessage)
                     {

                        if (pmessage->m_emessage == e_message_left_button_down)
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
      catch (const ::exception & exception)
      {

         error() << "Exception Reached Thread Loop" << exception.m_strMessage << exception.m_strDetails;

      }
      catch (...)
      {

         error() << "Exception Reached Thread Loop";

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

      if (pmessage->m_oswindow)
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

         auto puserinteraction = pusermessage->m_pwindow->user_interaction();

         if (::is_set(puserinteraction))
         {

            auto emessage = pmessage->m_emessage;

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
            if (emessage == e_message_update_notify_icon)
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

                        //   long long iApp = iMessage - WM_APP;

                        //   pusermessage->m_pwindow->m_puserinteraction->message_handler(pusermessage);

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

      ::manager::on_destroy();

      //return estatus;

   }


   void thread::enumerate_composite(matter_array & a)
   {


   }


   //void thread::set_finish_composites(::property_object * pcontextobjectFinish)
   //{

   //   auto estatus = channel::set_finish_composites(pcontextobjectFinish);

   //   if (estatus == error_pending)
   //   {

   //      return estatus;

   //   }

   //   if (m_pwindow->m_puserinteraction)
   //   {

   //      auto puserinteraction = m_pwindow->m_puserinteraction;

   //      if (puserinteraction)
   //      {

   //         if (!m_pwindow->m_puserinteraction->m_bDestroying)
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

      print_line("A user::thread finished");

   }


   //#ifdef WINDOWS_DESKTOP
   //
   //
   //   int thread::_GetMessage(MESSAGE * lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax)
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

      return ::thread::task_get_run();

   }


   //   void thread::start_window_visual()
   //   {
   //
   //      //m_happeningApplyVisual.reset_happening();
   //
   //      m_pwindow->m_puserinteraction->post_message(e_message_apply_visual);
   //
   //   }


      //void thread::destroy()
      //{

      //   return ::thread::destroy();

      //}


   void thread::destroy()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_pwindow.defer_destroy();

      //if (m_pwindow)
      {

         //if (m_pwindow->m_bDestroyImplOnly)
         //{

         //   m_pwindow->destroy_impl_only();

         //}
         //else
         //{

         //   m_pwindow->destroy_window();

         //}

      }
      //else
      //{

         //string strType = ::type(m_pwindow->m_puserinteraction).name();

      if (m_strDebugType.contains("filemanager"))
      {

         //information() << "filemanager";

      }

      ::thread::destroy();

      //}

      //return ::success;

   }


   void thread::set_finish()
   {

      ::thread::set_finish();

   }


   //void thread::term_task()
   //{

   //   //if(m_p)

   //   //auto puserinteraction = m_pwindow->user_interaction();

   //   //if (puserinteraction && puserinteraction->m_strName.contains("notify_icon"))
   //   //{
   //   //   information() << "notify_icon";
   //   //}

   //   //_synchronous_lock synchronouslock(this->synchronization());

   //   //m_pwindow->m_puserinteraction.release();

   //   //if (m_pthreadmgr)
   //   //{
   //   //   m_pthreadmgr->Deactivate();

   //   //   m_pthreadmgr->Release();
   //   //   m_pthreadmgr = NULL;
   //   //}

   //   ::thread::term_task();

   //}


} // namespace user




