// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "cursor.h"
#include "display.h"
#include "aura/user/user/frame_interaction.h"
#include "placement_log.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/graphics/output_purpose.h"
#include "acme/handler/request.h"
#include "acme/windowing/display.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/parallelization/message_queue.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
//#include "acme/platform/procedure_sequence.h"
#include "acme/platform/scoped_restore.h"
//#include "acme/handler/sequence.h"
#include "acme/constant/timer.h"
#include "acme/platform/system.h"
#include "acme/platform/timer_array.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/prototype/prototype/sequence_continuation.h"
#include "acme/user/user/_text_stream.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction_scaler.h"
#include "aura/user/user/interaction_thread.h"
#include "aura/user/user/redraw.h"
#include "aura/user/user/system.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/icon.h"
#include "aura/user/user/user.h"
#include "aura/message/timer.h"
#include "aura/message/user.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/copydesk.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/desktop_environment.h"
#include "aura/windowing/text_editor_interface.h"


namespace windowing
{


   window::window()
   {

      m_psandboxwindowingwindow = nullptr;

      //m_pWindow4 = nullptr;

      //set_oswindow(nullptr);

      m_bMessageOnlyWindow = false;

      m_bUpdateScreenSynchronously = true;

      m_bActiveWindow = false;

      m_bKeyboardFocus = false;



      user_common_construct();

   }


   window::~window()
   {

   }



   void window::user_common_construct()
   {
      m_bUserImplCreated = false;
      //m_pinteractionimpl = nullptr;
      //m_pinteractionchild = nullptr;
      //m_bDestroying = false;
      m_bDestroyImplOnly = false;
      m_iPendingRectMatch = -1;
      m_bPendingRedraw = false;
      //user_interaction() = nullptr;
      m_bIgnoreSizeEvent = false;
      m_bIgnoreMoveEvent = false;
      //m_bUserElementOk = true;
      m_uOnHide = false;
      //m_bQuitGraphicsOnHide = false;
      //m_bTryCloseApplicationOnHide = false;
      //m_pImpl2 = nullptr;

      //m_pinteractionimpl = this;

      //m_bOfflineRender = false;

      m_iState1 = 0;

      m_uCodePage = 0;

      m_iLangId = 0;

      m_bPendingRedraw = false;

      m_bEatMoveEvent = false;

      m_bEatSizeEvent = false;

      m_bOkToUpdateScreen = true;
      m_bUpdatingBuffer = false;
      m_bCursorRedraw = false;

      m_bScreenRelativeMouseMessagePosition = true;
      m_bTranslateMouseMessageCursor = true;
      m_bComposite = true;
      m_bUpdateGraphics = false;
      m_bPendingRedraw = false;
      m_bTransparentMouseEvents = false;

      m_bDoingGraphics = false;

#if defined(APPLE_IOS) || defined(__ANDROID__)

      set_per_second(12.0);

#elif defined(UNIVERSAL_WINDOWS)

      set_per_second(60.0);

#else

      set_per_second(60.0);

#endif

      m_bUpdateBufferPending = false;


   }


   void window::on_initialize_particle()
   {

      ::channel::on_initialize_particle();

   }


   void window::initialize_window(::acme::user::interaction* pacmeuserinteraction)
   {

      ::acme::windowing::window::initialize_window(pacmeuserinteraction);

      auto puser = user();

      puser->on_initialize_window_object(this);

      defer_create_synchronization();

      m_pparticleChildrenSynchronization = node()->create_mutex();

      m_pmutexGraphics = node()->create_mutex();

   }


   void window::destroy()
   {

      if (::is_set(m_puserthread))
      {

         auto puserthread = m_puserthread.cast<::user::thread>();

         if (puserthread->m_pwindow == this)
         {

            puserthread->set_finish();

         }

         puserthread->m_pwindow.release();

         if (::is_set(puserthread->m_puserinteractionbaseaThread))
         {

            puserthread->m_puserinteractionbaseaThread->erase(user_interaction());

         }

         m_puserthread.release();

      }

      string strType = ::type(user_interaction()).name();

      m_pplacementlog.release();
      m_pparticleChildrenSynchronization.release();
      m_pcursor.release();
      m_pcopydesk.release();
      m_picon.release();
      //m_pwindowParent.release();
      m_pmessagequeue.release();
      m_pdisplay.release();
      m_redrawitema.destroy();

      //::channel::destroy();

      detach_window();

      //user_interaction().release();

      //m_pacmeuserinteractionKeyboardFocus.release();

      //m_pacmeuserinteractionKeyboardFocusRequest.release();

      //m_pacmeuserinteractionKeyboardGainingFocusIfAny.release();

      m_pacmeuserinteractionMouseCapture.release();

      //m_pacmeuserinteractionToKillKeyboardFocus.release();

      m_puserthread.release();

      m_pgraphicsgraphics.release();

      m_pgraphicsthread.release();

      //this->windowing().release();

      m_graphicaloutputpurposea.clear();

      if (m_pthreadMouseLeave)
      {

         m_pthreadMouseLeave->set_finish();

      }

      //m_pthreadMouseLeave.release();

      //m_messagelist.clear();

      m_pelementSoftwareKeyboard.release();

      m_pdraw2dgraphics.release();

      //::channel::destroy();

      ::windowing::window_base::destroy();


   }


   void window::window_set_keyboard_focus()
   {


   }


   void window::window_kill_keyboard_focus()
   {


   }


   void window::window_on_activate()
   {

      m_bActiveWindow = true;

   }


   void window::window_on_deactivate()
   {

      m_bActiveWindow = false;

   }


   void window::window_on_set_keyboard_focus()
   {

      m_bKeyboardFocus = true;

   }


   void window::window_on_kill_keyboard_focus()
   {

      m_bKeyboardFocus = false;

   }



   //   void window::assert_ok() const
   //   {
   //
   //
   //   }
   //
   //
   //   void window::dump(dump_context & dumpcontext) const
   //   {
   //
   //
   //   }


      //void window::install_message_routing(channel * pchannel)
      //{


      //}


   void window::message_handler(::message::message* pmessage)
   {

      if (pmessage->m_emessage == e_message_post_user)
      {

         auto pparticle = pmessage->m_union.m_pparticle;

         ::pointer<::message::message> pmessagePost = pparticle->m_pparticle;

         if (::is_null(pmessagePost))
         {

            return;

         }

         if (pmessagePost->m_emessage == e_message_scroll_y)
         {

            informationf("e_message_scroll_y");


         }
         else if (pmessagePost->m_emessage == e_message_text_composition)
         {

            informationf("message text composition");

         }

         user_interaction()->message_handler(pmessagePost);

         return;

      }

      ::cast < ::user::message > pusermessage = pmessage;

      if (pusermessage)
      {

         if (pusermessage->user_interaction())
         {

            if (pusermessage->user_interaction()->is_message_only_window())
            {

               pusermessage->user_interaction()->message_handler(pmessage);

               return;

            }


         }

      }

      //user_interaction()->message_handler(pmessage);

      bool bKeyMessage = false;

      ::message::key* pkey = nullptr;

      if (::is_null(user_interaction()))
      {

         return;

      }

      if (user_interaction()->pre_message_handler(pkey, bKeyMessage, pmessage))
      {

         information() << "returning on pre_message_handler";

         return;

      }

      if (pmessage->m_emessage == e_message_timer)
      {

         //m_pthread->step_timer();

      }
      else if (pmessage->m_emessage == e_message_left_button_down)
      {

         informationf("linux::interaction_impl::e_message_left_button_down");

      }
      else if (pmessage->m_emessage == e_message_left_button_up)
      {

         informationf("linux::interaction_impl::e_message_left_button_up");

      }
      else if (pmessage->m_emessage == e_message_mouse_move)
      {

         //g_iMouseMove++;

         //informationf("interaction_impl::message_handler e_message_mouse_move");
         //printf("g_iMouseMove = %d\n", g_iMouseMove);

      }
      else if (pmessage->m_emessage == e_message_paint)
      {

      }
      else if (pmessage->m_emessage == e_message_left_button_up)
      {

         informationf("e_message_left_button_up (0)");

      }

      //      if(::is_set(user_interaction()))
      //      {
      //
      //         user_interaction()->pre_translate_message(pmessage);
      //
      //      }

      //      if(tickDebugmessage_handlerTime.timeout(1))
      //      {
      //
      //         iDebugmessage_handlerTime = 0;
      //
      //      }
      //      else
      //      {
      //
      //         if(iDebugmessage_handlerTime > 20)
      //         {
      //
      //            informationf("interaction_impl::message handler flooded?\n");
      //
      //         }
      //         else
      //         {
      //
      //            iDebugmessage_handlerTime++;
      //
      //         }
      //
      //      }

      if (user_interaction() != nullptr)
      {

         if (user_interaction()->layout().is_moving())
         {
            //informationf("moving: skip pre translate message");
         }
         else if (user_interaction()->layout().is_sizing())
         {
            //informationf("sizing: skip pre translate message");
         }
         else
         {

            //user_interaction()->pre_translate_message(pmessage);

            //if (pmessage->m_bRet)
            //{

            // return;

            //}

            //pmessage->m_uiMessageFlags |= 1;

         }

      }



      //      if(bKeyMessage)
      //      {
      //
      //         auto psession = session();
      //
      //         auto puser = user();
      //
      //         auto pwindowing = system()->windowing();
      //
      //         ::pointer<::message::key>pkey = pmessage;
      //
      //         //pwindowing->set(pkey, get_oswindow(), m_pwindow, pkey->m_emessage, pkey->m_wparam, pkey->m_lparam);
      //
      ////         if(pmessage->m_emessage == e_message_key_down)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, true);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      ////         else if(pmessage->m_emessage == e_message_key_up)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, false);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      //
      //      }

      pmessage->m_lresult = 0;

      if (pmessage->m_emessage == e_message_mouse_leave)
      {

         _000OnMouseLeave(pmessage);

      }

      if (pmessage->m_emessage == e_message_left_button_down ||
         pmessage->m_emessage == e_message_left_button_up ||
         pmessage->m_emessage == e_message_middle_button_down ||
         pmessage->m_emessage == e_message_middle_button_up ||
         pmessage->m_emessage == e_message_right_button_down ||
         pmessage->m_emessage == e_message_right_button_up ||
         pmessage->m_emessage == e_message_left_button_double_click ||
         pmessage->m_emessage == e_message_mouse_move ||
         pmessage->m_emessage == e_message_mouse_wheel)
      {

         auto pmouse = pmessage->m_union.m_pmouse;

         //information() << "msghdl pwnd : " << (::iptr) pmouse->m_pwindow.m_p;

         on_mouse_message(pmouse);

         return;

      }
      /*      else if(pmessage->m_emessage == e_message_key_down ||
                    pmessage->m_emessage == e_message_key_up ||
                    pmessage->m_emessage == e_message_char)*/
      else if (bKeyMessage)
      {

         if (::is_set(pkey))
         {

            information() << "key message";

            ::pointer<::user::interaction> puiKeyboardFocus = m_pacmeuserinteractionKeyboardFocus;

            if (puiKeyboardFocus)
            {

               information() << "key message control with keyboard focus : " << ::string(::type(puiKeyboardFocus.m_p));

               puiKeyboardFocus->route_message(pkey);

            }
            else
            {

               user_interaction()->route_message(pkey);

            }

         }

         if (pmessage->m_bRet)
         {

            return;

         }

         default_window_procedure(pmessage);

         return;

      }

      if (pmessage->m_emessage == e_message_subject)
      {

         if (user_interaction() != nullptr)
         {

            user_interaction()->handle((::topic*)pmessage->m_lparam.m_lparam, nullptr);

         }
         //         else
         //         {
         //
         //            on_control_event((::user::control_event *) pmessage->m_lparam.m_lparam);
         //
         //         }

         return;

      }

      if (::is_set(user_interaction()))
      {

         user_interaction()->route_message(pmessage);

      }
      else
      {

         route_message(pmessage);

      }

      if (!pmessage->m_bRet)
      {

         default_window_procedure(pmessage);

      }

      if (pmessage->m_emessage == e_message_create)
      {

         //if (user_interaction()->m_procedureOnAfterCreate)
         //{

         //   user_interaction()->post_message(e_message_after_create);

         //}

//         if(has_screen_output_purpose())
//         {
//
//            user_interaction()->set_need_layout();
//
//            user_interaction()->set_need_redraw();
//
//            user_interaction()->post_redraw();
//
//         }

         //if(user_interaction()->m_setneedredrawa.has_element())
         //{

         //   user_interaction()->post_redraw();

         //}

      }



   }


   void window::create_window()
   {

      //      if(!user_interaction())
      //      {
      //
      ////user_interaction() = m_pacmeuserinteraction;
      //
      //      }
      //
            //if (::is_window(get_handle()))
            //{

            //   DestroyWindow();

            //}

            //      ASSERT(lpszClassName == nullptr || __is_valid_string(lpszClassName) ||
            //       __is_valid_atom(lpszClassName));
            //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));

            // allow modification of several common create parameters
            //::user::system createstruct;
            //      pusersystem->m_createstruct.hwndParent = hWndParent;
            //   pusersystem->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;

            //auto puserinteraction = user_interaction();

      auto pusersystem = user_interaction()->m_pusersystem;

      //pusersystem->m_createstruct.hMenu = nullptr;
      //      pusersystem->m_createstruct.hInstance = ::aura::get_system()->m_hInstance;
      //pusersystem->m_createstruct.lpCreateParams = lpParam;

      //hook_window_create(puserinteraction);

      //CGRect int_rectangle;

      //      int_rectangle rectParam;

      //      rectParam.left = m_pusersystem->m_createstruct.x;
      //      rectParam.top = pusersystem->m_createstruct.y;
      //      rectParam.right = pusersystem->m_createstruct.x + pusersystem->m_createstruct.cx();
      //      rectParam.bottom = pusersystem->m_createstruct.y + pusersystem->m_createstruct.cy();

      //      copy(rectangle, rectParam);
      //
      //      if (pusersystem->m_createstruct.hwndParent == MESSAGE_WINDOW_PARENT)
      //      {
      //
      //         return true;
      //
      //      }
      //      else
      //      {

      unsigned uStyle = 0;

      //      if(puserinteraction->m_ewindowflag & ::e_window_flag_miniaturizable)
      //      {
      //         
      //#define NSWindowStyleMaskMiniaturizable (1 << 2)
      //         
      //         uStyle |= NSWindowStyleMaskMiniaturizable;
      //         
      //      }
      //      
      //      auto rectangle = puserinteraction-> const_layout().sketch().parent_raw_rectangle();
      //      
      //      CGRect cgrect;
      //      
      //      copy(cgrect, rectangle);

            //__todo?
            //windowing()->copy(cgrect, rectangle);
            //or
            //display()->copy(cgrect, rectangle);
            //because rectangle origin is top-left
            //and because cgrect origin is bottom-left and,
            //the origin of screen is at bottom.

            //m_pwindow = pwindow;

            //puserinteraction->m_puserinteractionTopLevel = puserinteraction;

      //user_interaction()->m_pwindow = this;

      //pwindow->m_pwindow = this;

      auto puserinteraction = user_interaction();

      int x = puserinteraction->const_layout().sketch().origin().x();

      int y = puserinteraction->const_layout().sketch().origin().y();

      int cx = puserinteraction->const_layout().sketch().width();

      int cy = puserinteraction->const_layout().sketch().height();

      m_pointWindow.x() = x;

      m_pointWindow.y() = y;

      m_sizeWindow.cx() = cx;

      m_sizeWindow.cy() = cy;

      install_message_routing(user_interaction());

      auto pwindowing = (::windowing::windowing*)system()->windowing();
      //      
      //      m_pmacoswindowing = dynamic_cast < class windowing * >(pwindowing);

      //this->windowing() = pwindowing;

      //pwindow->this->windowing() = pwindowing;
      //try
      //{
      main_send([this]()
         {

            _create_window();

         });

      //}
      //catch (::exception& e)
      //{

      //   pexception = e.clone();

      //}
      //catch (...)
      //{

      //   pexception = __allocate::exception(error_catch_all_exception);

      //}

      user_interaction()->m_ewindowflag |= e_window_flag_window_created;

      m_bUserImplCreated = true;

      user_interaction()->set_flag(e_flag_task_started);

      on_finished_window_creation();

   }


   void window::_create_window()
   {

      create_graphics_thread();

   }


   void window::create_graphics_thread()
   {

      //__øconstruct(m_pgraphicsthread);

      m_pgraphicsthread->branch_synchronously();

   }


   //void window::create_window(::windowing::window * pwindow)
   //void window::_create_window()
   //{

   //   //__UNREFERENCED_PARAMETER(pwindow);

   //   throw ::interface_only();

   //}


   void window::on_finished_window_creation()
   {

      auto puserinteraction = user_interaction();

      puserinteraction->send_message(e_message_after_create, 0, 0);

   }


   void window::set_context_org(draw2d::graphics_pointer& pgraphics)
   {


   }



   //   void window::set_cursor_position(const ::int_point & pointCursor)
   //   {
   //
   //      m_pointCursor = pointCursor;
   //
   //   }
   //
   //
   //   void window::get_cursor_position(::int_point * ppointCursor)
   //   {
   //
   //      *ppointCursor = m_pointCursor;
   //
   //   }


      //bool window::defer_set_icon()
      //{

      //   return false;

      //}


   class placement_log* window::placement_log()
   {

      __defer_construct_new(m_pplacementlog);

      return m_pplacementlog;

   }


   double window::get_top_margin()
   {

      return 0.;

   }


   // bool window::has_mouse_capture() const
   // {
   //
   //    return false;
   //
   // }


   bool window::has_keyboard_focus()
   {

      return m_bKeyboardFocus;

   }


   //::color::color window::screen_pixel(int x, int y)
   //{

   //   return screen_pixel(x, y);

   //}


   bool window::is_full_screen()
   {

      return false;

   }


   ::windowing::display* window::display()
   {

      if(!m_pdisplay)
      {

         auto psystem = ::system();

         auto pwindowing = psystem->acme_windowing();

         m_pdisplay = pwindowing->acme_display();

      }

      return m_pdisplay.cast < ::windowing::display>();

   }


   ::user::copydesk* window::copydesk()
   {

      if (!m_pcopydesk)
      {

         __raw_construct(m_pcopydesk);

         if (m_pcopydesk)
         {

            m_pcopydesk->initialize_copydesk(this);

         }

      }

      return m_pcopydesk;

   }


   // implementation foreseeing Windows with its mouse capture state per thread and
   // also providing fallback default internal (own process state) implementation.
   void window::set_mouse_capture()
   {

      auto pthread = m_puserthread;

      windowing()->set_mouse_capture(pthread, this);

   }

   //       //::pointer < ::windowing_wayland::display > pwaylanddisplay = m_pdisplay;
   //
   //       //pwaylanddisplay->__capture_mouse(this, pwaylanddisplay->m_uLastButtonSerial);
   //
   //
   // //      this->windowing()->windowing_post([this]()
   // //                                   {
   // //
   // //                                      synchronous_lock synchronouslock(user_synchronization());
   // //
   // ////                                      display_lock displaylock(x11_display()->Display());
   // //
   // //                                      information() << "XGrabPointer";
   // ////
   // ////                                      auto grabStatus = XGrabPointer(Display(), Window(), False,
   // ////                                                                     ButtonPressMask | ButtonReleaseMask |
   // ////                                                                     PointerMotionMask,
   // ////                                                                     GrabModeAsync, GrabModeAsync, None, None,
   // ////                                                                     CurrentTime);
   // //
   // ////                                      if (grabStatus != GrabSuccess)
   // ////                                      {
   // ////
   // ////                                         windowing_output_debug_string("\noswindow_data::SetCapture 2.1");
   // ////
   // ////                                         return;
   // ////
   // ////                                      }
   // //
   // ////                                      auto pdisplay = x11_display();
   // ////
   // ////                                      if (pdisplay)
   // ////                                      {
   // ////
   // ////                                         pdisplay->_on_capture_changed_to(this);
   // ////
   // ////                                      }
   // //
   // //                                      windowing_output_debug_string("\noswindow_data::SetCapture 2");
   // //
   // //                                   });
   // //
   // //      //return ::success;
   //
   //    }


      // implementation foreseeing Windows with its mouse capture state per thread and
      // also providing fallback default internal (own process state) implementation.
   bool window::has_mouse_capture()
   {

      auto pthread = m_puserthread;

      if (!windowing()->has_mouse_capture(pthread, this))
      {

         return false;

      }

      return true;

   }


   // implementation foreseeing Windows with its mouse capture state per thread and
   // also providing fallback default internal (own process state) implementation.
   bool window::is_mouse_captured()
   {

      auto pthread = m_puserthread;

      if (!windowing()->is_mouse_captured(pthread, this))
      {

         return false;

      }

      return true;

   }


   // implementation foreseeing Windows with its mouse capture state per thread and
   // also providing fallback default internal (own process state) implementation.
   void window::release_mouse_capture()
   {

      auto pthread = m_puserthread;

      windowing()->release_mouse_capture(pthread, this);

   }


   // implementation foreseeing Windows with its mouse capture state per thread and
   // also providing fallback default internal (own process state) implementation.
   bool window::defer_release_mouse_capture()
   {

      auto pthread = m_puserthread;

      auto pwindowing = windowing();

      return pwindowing->defer_release_mouse_capture(pthread, this);

   }


   void window::destroy_window()
   {

      auto strType = ::type(user_interaction()).name();

      if (strType.contains("main_frame"))
      {

         informationf("main_frame windowing::window::destroy_window");

      }

      if (user_interaction())
      {

         if (!user_interaction()->has_destroying_flag())
         {

            user_interaction()->set_flag(e_flag_destroying);

         }

      }

      ::pointer<::windowing::window>pimplThis = this;

      ::pointer<::user::interaction>puiThis = user_interaction();

      if (puiThis)
      {

         try
         {

            puiThis->send_message(e_message_destroy);

         }
         catch (...)
         {

         }

         try
         {

            puiThis->send_message(e_message_non_client_destroy);

         }
         catch (...)
         {

         }

      }

      //return true;


      //user_interaction()->m_ewindowflag -= e_window_flag_window_created;

      //::destroy_window(get_handle());

//      destroy_window();


      if (::is_set(this->windowing()))
      {

         this->windowing()->erase_window(this);

      }

      //m_pwindowParent.release();

   }


   void window::on_destroy()
   {

      try
      {

         if (m_pcopydesk.is_set())
         {

            m_pcopydesk->destroy();

            m_pcopydesk.release();

         }

      }
      catch (...)
      {

      }

   }


   //void window::set_user_interaction(::user::interaction * pinteraction)
   //{

   //   ::windowing::window_base::set_user_interaction(pintera)

   //}


   void window::on_a_system_menu_item(::operating_system::a_system_menu_item* psystemmenuitem, ::user::activation_token* puseractivationtoken)
   {

      ::string strActionName(psystemmenuitem->m_strAtom);

      if (strActionName == "minimize")
      {

         window_minimize();

      }
      else if (strActionName == "maximize")
      {

         window_maximize();

      }
      else if (strActionName == "maximize")
      {

         window_maximize();

      }
      else if (strActionName == "about_box")
      {

         application()->show_about_box(puseractivationtoken);

      }
      else if (strActionName == "close")
      {

         user_interaction()->post_message(e_message_close);

      }
      else if (strActionName == "")
      {

         print_line("reaching here?!");
         //defer_perform_entire_reposition_process(nullptr);

      }
      else if (strActionName == "")
      {

         print_line("also here");

         //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

      }


   }


   void window::activate_top_parent()
   {


   }




   //   void window::on_visual_applied()
   //   {
   //
   //      throw ::interface_only();
   //
   //   }


      // bool window::is_window_zoomed()
      // {
      //
      //    return false;
      //
      // }


   void window::on_window_configuration_change()
   {

      auto r = ::int_rectangle(m_pointWindow, m_sizeWindow);

      user_interaction()->_on_configure_notify_unlocked(r);

   }


   void window::_on_configure_notify_unlocked(const ::int_rectangle& rectangle)
   {

      m_pointWindow = rectangle.top_left();

      m_sizeWindow = rectangle.size();

      user_interaction()->_on_configure_notify_unlocked(rectangle);

   }


   void window::_on_reposition_notify_unlocked(const ::int_point& point)
   {

      m_pointWindow = point;

      user_interaction()->_on_reposition_notify_unlocked(point);

   }


   void window::_on_reposition(int x, int y)
   {

      //::int_point p(x, y);

      //if (m_pointWindow != p)
      //{

        // m_pointWindow = p;

      auto preposition = __create_new<::message::reposition>();

      preposition->m_oswindow = this->oswindow();

      preposition->m_pwindow = this;

      preposition->m_emessage = e_message_reposition;

      preposition->m_point.x() = x;

      preposition->m_point.y() = y;

      message_handler(preposition);

      //         on_window_configuration_change();

               //on_window_configure_unlocked();

               // {
               //
               //    auto r = ::int_rectangle(m_pointWindow, m_sizeWindow);
               //
               //    _on_configure_notify_unlocked(r);
               //
               // }

               // auto puserinteraction = user_interaction();
               //
               // puserinteraction->layout().m_statea[::user::e_layout_sketch].m_point2 = p;
               // puserinteraction->layout().m_statea[::user::e_layout_lading].m_point2 = p;
               // puserinteraction->layout().m_statea[::user::e_layout_layout].m_point2 = p;
               // puserinteraction->layout().m_statea[::user::e_layout_design].m_point2 = p;
               // puserinteraction->layout().m_statea[::user::e_layout_window].m_point2 = p;
               //
               // puserinteraction->on_reposition();

               // puserinteraction->post([puserinteraction]()
               //                    {
               //
               //                       puserinteraction->defer_save_window_placement();
               //
               //                    });

               //on_window_configure_unlocked();

            //}

   }


   void window::_on_size(int cx, int cy)
   {

      auto psize = __create_new<::message::size>();

      psize->m_oswindow = this->oswindow();

      psize->m_pwindow = this;

      psize->m_emessage = e_message_size;

      psize->m_size.cx() = cx;

      psize->m_size.cy() = cy;

      message_handler(psize);

      // ::int_size s(cx, cy);
      //
      // informationf("::windowing_q6::window::_on_size(%d, %d)", cx, cy);
      // informationf("::windowing_q6::window::_on_size this->m_sizeWindow (%d, %d)", m_sizeWindow.cx(), m_sizeWindow.cy());
      //
      // if (m_sizeWindow != s)
      // {
      //
      //    //gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (m_pdrawingarea), cx);
      //    //gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (m_pdrawingarea), cy);
      //
      //    m_sizeWindow = s;
      //
      //    on_window_configuration_change();
      //
      //    // //on_window_configure_unlocked();
      //    //
      //    // // {
      //    // //
      //    // //    auto r = ::int_rectangle(m_pointWindow, m_sizeWindow);
      //    // //
      //    // //    _on_configure_notify_unlocked(r);
      //    // //
      //    // // }
      //    // //
      //    //
      //    // //on_window_configure_unlocked();
      //    //
      //    // auto puserinteraction = user_interaction();
      //    //
      //    // puserinteraction->set_size(s);
      //    //
      //    // puserinteraction->layout().m_statea[::user::e_layout_window].m_size = s;
      //    //
      //    // puserinteraction->set_need_layout();
      //    //
      //    // puserinteraction->set_need_redraw();
      //    //
      //    // puserinteraction->post_redraw();
      //
      // }

   }



   void window::win_update_graphics()
   {

      throw ::interface_only();

   }


   lresult window::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      return 0;

   }


   //void window::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   //{

   //   //return false;

   //}


   void window::set_window_text(const ::scoped_string& scopedstr)
   {

      throw ::interface_only();

   }


   //   ::string window::get_window_text()
   //   {
   //
   //      return {};
   //
   //   }


   //   character_count window::get_window_text(char * pszStringBuf, character_count nMaxCount)
   //   {
   //
   //      throw ::interface_only();
   //
   //      return 0;
   //
   //   }
   //
   //
   //   void window::get_window_text(string & rectangleString)
   //   {
   //
   //      throw ::interface_only();
   //
   //   }
   //
   //
   //   character_count window::get_window_text_length()
   //   {
   //
   //      throw ::interface_only();
   //
   //      return 0;
   //
   //   }


   void window::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      throw ::interface_only();

   }


   bool window::is_zoomed()
   {

      throw ::interface_only();

      return false;

   }


   unsigned int window::ArrangeIconicWindows()
   {

      throw ::interface_only();

      return 0;

   }


   void window::rects_from_os()
   {


   }


   bool window::window_rect_from_os(::int_rectangle* prectangle)
   {

      return false;

   }


   bool window::client_rect_from_os(::int_rectangle* prectangle)
   {

      return false;

   }


   void window::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      throw ::interface_only();

   }


   void window::present()
   {

      throw ::interface_only();

   }


   //   bool window::presentation_complete()
   //   {
   //
   //      return true;
   //
   //   }


   ::oswindow window::oswindow() const
   {

      throw interface_only();

      return nullptr;

   }


   void window::set_oswindow(::oswindow oswindow)
   {

      _set_oswindow(oswindow);

      //auto pwindow = m_pwindow;

      //if (pwindow)
      //{

      //   auto puserinteraction = user_interaction();

      //   if (puserinteraction)
      //   {

      //      puserinteraction->m_oswindow = oswindow;

      //   }

      //}

   }


   void window::_set_oswindow(::oswindow oswindow)
   {

      throw interface_only();

   }


   void window::UpdateWindow()
   {


   }


   void window::SetRedraw(bool)
   {


   }


   bool window::GetUpdateRect(::int_rectangle* prectangle, bool bErase)
   {

      throw ::interface_only();

      return false;

   }


   int window::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {

      return 0;

   }


   void window::Invalidate(bool bErase)
   {


   }


   void window::InvalidateRect(const ::int_rectangle* rectangle, bool bErase)
   {


   }


   void window::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {


   }


   void window::ValidateRect(const ::int_rectangle* prectangle)
   {


   }


   void window::ValidateRgn(::draw2d::region* pRgn)
   {


   }


   void window::ShowOwnedPopups(bool)
   {

   }


   bool window::LockWindowUpdate()
   {

      throw ::interface_only();

      return false;

   }


   void window::UnlockWindowUpdate()
   {


   }


   //bool window::RedrawWindow(const ::int_rectangle & rectangleUpdate, ::draw2d::region * prgnUpdate, unsigned int flags)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool window::is_this_enabled()
   {

      throw ::interface_only();

      return false;

   }


   //void window::enable_window(bool bEnable)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   // the active interaction_impl applies only to top-level (frame windows)
   ::user::interaction* window::get_active_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   void window::set_active_window()
   {

      throw ::interface_only();

      //return nullptr;

   }


   void window::_set_active_window_unlocked()
   {

      throw ::interface_only();

      //return nullptr;

   }


   // the foreground interaction_impl applies only to top-level windows (frame windows)
   void window::set_foreground_window(::user::activation_token* puseractivationtoken)
   {

      throw ::interface_only();

   }


   void window::_set_foreground_window_unlocked(::user::activation_token* puseractivationtoken)
   {

      throw ::interface_only();

   }


   ::user::interaction* window::get_foreground_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   bool window::is_active_window()
   {

      return m_bActiveWindow;

      //      if(this->windowing()->get_active_window(m_puserthread) != this)
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      return true;

   }


   ::user::interaction* window::get_desktop_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window* window::get_next_window(unsigned int nFlag)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window* window::get_top_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window* window::get_window(unsigned int nCmd)
   {

      throw ::interface_only();

      return nullptr;

   }


   ::windowing::window* window::get_last_active_popup()
   {

      throw ::interface_only();

      return nullptr;

   }


   //::windowing::window * window::get_parent() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //oswindow window::get_parent_oswindow() const
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void window::set_parent(::windowing::window* pwindowNewParent)
   {

      throw ::interface_only();

   }


   ::windowing::window* window::window_get_owner()
   {

      throw ::interface_only();

      return nullptr;

   }


   oswindow window::get_owner_oswindow()
   {

      throw ::interface_only();

      return nullptr;

   }


   void window::set_owner(::windowing::window* pwindowNewOwner)
   {

      throw ::interface_only();

   }


   int_point window::GetCaretPos()
   {

      throw ::interface_only();

      return {};

   }


   void window::SetCaretPos(const ::int_point& point)
   {

      throw ::interface_only();

   }


   void window::HideCaret()
   {

      throw ::interface_only();

   }


   void window::ShowCaret()
   {

      throw ::interface_only();

   }


   void window::DragAcceptFiles(bool bAccept)
   {

      throw ::interface_only();

   }


   ::pointer<::windowing::icon> window::load_icon(const ::payload& payloadFile)
   {

      auto picon = __øcreate<icon>();

      if (!picon)
      {

         return nullptr;

      }

      picon->load_file(payloadFile);

      return picon;

   }


   void window::set_icon(::windowing::icon* picon)
   {

      m_picon = picon;

   }


   ::pointer<::windowing::icon> window::get_icon() const
   {

      return m_picon;

   }


   //void window::set_mouse_cursor(::windowing::cursor * pcursor)
   //{

   //   m_pcursor = pcursor;

   //}


   ::windowing::cursor* window::get_mouse_cursor()
   {

      return m_pcursor;

   }


   //   ::int_point window::get_mouse_cursor_host_position()
   //   {
   //
   //      return ::int_point(0, 0);
   //
   //   }
   //
   //
   //   ::int_point window::get_mouse_cursor_absolute_position()
   //   {
   //
   //      return ::int_point(0, 0);
   //
   //   }


   void window::set_tool_window(bool bSet)
   {

      throw ::interface_only();

   }


   void window::on_set_parent(::user::interaction* pinteraction)
   {

      throw ::interface_only();

   }


   bool window::get_rect_normal(::int_rectangle* prectangle)
   {

      throw ::interface_only();

      return false;

   }


   void window::show_task(bool bShow)
   {

      throw ::interface_only();

   }


   bool window::is_tool_window()
   {

      return false;

   }


   void window::_window_show_change_visibility(::e_display edisplay, const ::user::activation& useractivation)
   {

      throw ::interface_only();

   }


   //void window::non_top_most_upper_window_rects(::int_rectangle_array & recta)
   //{

   //   throw ::interface_only();

   //}


   //void window::post_non_client_destroy()
   //{

   //   m_pplacementlog.release();
   //   m_pparticleChildrenSynchronization.release();
   //   m_pcursor.release();
   //   m_pcopydesk.release();
   //   this->windowing().release();
   //   m_picon.release();
   //   m_pwindowParent.release();
   //   m_pmessagequeue.release();
   //   //m_pwindow.release();
   //   m_pdisplay.release();

   //   ::channel::destroy();

   //}


   //void window::default_message_handler(::message::message * pmessage)
   //{

   //}


   //void window::track_mouse_hover()
   //{

   //}


   //void window::_task_transparent_mouse_event()
   //{

   //}


   float window::get_dpi_for_window()
   {

      return 96.0f;

   }


   float window::get_density_for_window()
   {

      return 1.0f;

   }


   float window::dpiy(float y)
   {

      float fDpi = get_dpi_for_window();

      return y * fDpi / 96.f;

   }


   float window::dpix(float x)
   {

      float fDpi = get_dpi_for_window();

      return x * fDpi / 96.f;

   }


   float window::point_dpi(float points)
   {

      float fDpi = get_dpi_for_window();

      return points * fDpi / 72.f;

   }


   float window::y_dpi(float y)
   {

      float fDpi = get_dpi_for_window();

      return y / fDpi;

   }


   float window::x_dpi(float x)
   {

      float fDpi = get_dpi_for_window();

      return x / fDpi;

   }


   void window::on_redraw_window(unsigned int flags)
   {

   }


   bool window::is_child_of(const ::windowing::window* pwindowAscendantCandidate) const
   {

      return false;

   }


   //   /// this function should be called in user/main thread
   //   void window::show_window(const ::e_display & edisplay, const ::user::e_activation & useractivation)
   //   {
   //
   //      windowing_output_debug_string("::window::show_window 1");
   //
   //   }
   //
   //
   //   void window::_show_window_unlocked(const ::e_display & edisplay, const ::user::e_activation & useractivation)
   //   {
   //
   //
   //   }


   void window::full_screen(const ::int_rectangle& rectangle)
   {

   }


   ::windowing::windowing* window::windowing()
   {

      return system()->windowing();

   }


   void window::exit_iconify()
   {

   }


   void window::exit_full_screen()
   {

   }


   void window::exit_zoomed()
   {

   }


   void window::set_keyboard_focus()
   {

      throw ::interface_only();

   }


   void window::_set_keyboard_focus_unlocked()
   {

      throw ::interface_only();

   }


   /*void window::set_active_window()
   {

      throw ::interface_only();

   }*/


   void window::bring_to_front()
   {

      throw ::interface_only();

   }


   void window::switch_to_this_window(bool b)
   {

      throw ::interface_only();

   }


   void window::graphics_lock()
   {


   }


   void window::graphics_unlock()
   {


   }


   bool window::client_to_screen(::int_point* ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::int_point* ppoint)
   {

      return true;

   }


   bool window::is_iconic()
   {

      return false;

   }


   bool window::is_window()
   {

      return false;

   }


   bool window::is_window_visible()
   {

      windowing_output_debug_string("::window::is_window_visible 1");

      return false;

   }


   bool window::_is_iconic_unlocked()
   {

      windowing_output_debug_string("::window::_is_iconic_unlocked 1");

      return false;

   }


   bool window::_is_window_visible_unlocked()
   {

      windowing_output_debug_string("::window::_is_window_visible_unlocked 1");

      return false;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

      auto puserinteraction = user_interaction();

      if (!puserinteraction)
      {

         return true;

      }

      if (!puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


   bool window::on_set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy,
      const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
      ::e_display edisplay)
   {

      return set_window_position(zorder, x, y, cx, cy, useractivation, bNoZorder, bNoMove, bNoSize, edisplay);

   }


   bool window::set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy,
      const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
      ::e_display edisplay)
   {

      bool bOk = false;

      return bOk;

   }


   bool window::_set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy,
      const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
      ::e_display edisplay, unsigned int nOverrideFlags)
   {

      return true;

   }


   bool window::configure_window_unlocked()
   {

      // Request / Incoming changes / Prepare Internal Buffer
      auto& stateOutput = user_interaction()->layout().m_statea[::user::e_layout_design];

      // Current/Previous Window State
      auto& stateWindow = user_interaction()->layout().m_statea[::user::e_layout_window];

      //bool bSetWindowPosition = true;

      //if (stateOutput == stateWindow)
      //{

      //   bSetWindowPosition = false;

      //}

      auto activationOutput = stateOutput.activation();

      auto activationWindow = stateWindow.activation();

      auto edisplayOutput = stateOutput.display();

      auto edisplayWindow = stateWindow.display();

      auto zOutput = stateOutput.zorder();

      auto zWindow = stateWindow.zorder();

      bool bVisibilityChange = edisplayOutput != edisplayWindow;

      bool bZ = zOutput.is_change_request();

      if (bVisibilityChange || bZ || activationOutput.is_change_request())
      {

         informationf("::windowing::window::configure_window_unlocked bVisibilityChange(%d) bZ(%d) bActivation(%d)",
            (int)bVisibilityChange,
            (int)bZ,
            (int)(activationOutput.is_change_request()));

         information() << "::windowing::window::configure_window_unlocked displayRequest : " << edisplayOutput;

         if (_configure_window_unlocked(
            zOutput,
            activationOutput,
            !bZ,
            edisplayOutput))
         {

            stateWindow.display() = stateOutput.display();

            stateOutput.m_activation.clear();

            stateOutput.m_zorder.clear_request();

         }

      }

      return true;

   }


   bool window::strict_set_window_position_unlocked(bool& bChangedPosition, bool& bChangedSize)
   {

      if (!user_interaction())
      {

         return false;

      }

      auto rectangle = user_interaction()->const_layout().parent_raw_rectangle(::user::e_layout_design);

      return strict_set_window_position_unlocked(bChangedPosition, bChangedSize, rectangle);

   }


   bool window::strict_set_window_position_unlocked(bool& bChangedPosition, bool& bChangedSize, const ::int_rectangle& rectangle)
   {

      auto pointOutput = rectangle.origin();

      auto pointWindow = m_pointWindow;

      bChangedPosition = pointWindow != pointOutput;

      if (bChangedPosition)
      {

         //information() << "Design.point != Window.point " << pointDesign << ", " << pointWindow;

      }

      auto sizeOutput = rectangle.size();

      auto sizeWindow = m_sizeWindow;

      bChangedSize = sizeWindow != sizeOutput;

      if (bChangedSize)
      {

         //information() << "Design.size != Window.size " << sizeOutput << ", " << sizeWindow;

      }

      if (bChangedPosition || bChangedSize)
      {

         ::int_rectangle rectangleOutput(pointOutput, sizeOutput);

         //information() << "::windowing::window::_set_window_position_unlocked l:" << r.left() << ", t:" << r.top()
         //              << ", r:" << r.right() << ", b:" << r.bottom() << ", thrd:" << ::current_task_index();

         static ::int_point s_pointInitialTopRight;

         if (s_pointInitialTopRight.is_null())
         {

            s_pointInitialTopRight = rectangleOutput.top_right();

         }

         auto offset = rectangleOutput.top_right() - s_pointInitialTopRight;

         //information() << "TopRightOffsetFromInitial : " << offset;

         if (offset.cx() != 0 || offset.cy() != 0)
         {

            //            information() << "Offset is Not Null";

         }

         _strict_set_window_position_unlocked(
            pointOutput.x(),
            pointOutput.y(),
            sizeOutput.cx(),
            sizeOutput.cy(),
            !bChangedPosition, !bChangedSize);

         //stateWindow = stateDesign;

      }

      return true;

   }


   bool window::set_window_position_unlocked()
   {

      auto& stateSketch = user_interaction()->layout().m_statea[::user::e_layout_sketch];

      auto& stateDesign = user_interaction()->layout().m_statea[::user::e_layout_design];

      if (stateSketch.m_size != stateDesign.m_size || stateSketch.origin() != stateDesign.origin())
      {

         return false;

      }

      auto pointDesign = stateDesign.origin();

      auto pointWindow = m_pointWindow;

      bool bMove = pointWindow != pointDesign;

      if (bMove)
      {

         if (system()->acme_windowing()->get_ewindowing() == ::windowing::e_windowing_wayland)
         {

            bMove = false;

         }

         //information() << "Design.point != Window.point " << pointDesign << ", " << pointWindow;

      }

      auto sizeOutput = stateDesign.size();

      auto sizeWindow = m_sizeWindow;

      bool bSize = sizeWindow != sizeOutput;

      if (bSize)
      {

         if (system()->acme_windowing()->get_ewindowing() == ::windowing::e_windowing_wayland)
         {

            bSize = false;

         }


         //information() << "Design.size != Window.size " << sizeOutput << ", " << sizeWindow;

      }

      // Request / Incoming changes / Prepare Internal Buffer
      auto& stateOutput = user_interaction()->layout().m_statea[::user::e_layout_design];

      // Current/Previous Window State
      auto& stateWindow = user_interaction()->layout().m_statea[::user::e_layout_window];

      //bool bSetWindowPosition = true;

      //if (stateOutput == stateWindow)
      //{

      //   bSetWindowPosition = false;

      //}

      auto activationOutput = stateOutput.activation();

      auto activationWindow = stateWindow.activation();

      auto edisplayOutput = stateOutput.display();

      auto edisplayWindow = stateWindow.display();

      auto zOutput = stateOutput.zorder();

      auto zWindow = stateWindow.zorder();

      bool bVisibilityChange = edisplayOutput != edisplayWindow;

      bool bZ = zOutput.is_change_request();

      ::string strType = ::type(user_interaction()).name();

      if (strType.contains("list_box"))
      {

         ::output_debug_string("list_box");

      }

      bool bActivate = activationOutput.is_change_request();

      if (bMove || bSize
         || bVisibilityChange || bZ || bActivate)
      {

         debug() << "windowing::window::set_window_position_unlocked";

         ::int_rectangle r(pointDesign, sizeOutput);

         debug() << "bMove : " << bMove
            << ", bSize : " << bSize
            << ", bVisibilityChange : " << bVisibilityChange
            << ", bZ : " << bZ
            << ", bActivate : " << bActivate;


         //information() << "::windowing::window::_set_window_position_unlocked l:" << r.left() << ", t:" << r.top()
         //              << ", r:" << r.right() << ", b:" << r.bottom() << ", thrd:" << ::current_task_index();

         static ::int_point s_pointInitialTopRight;

         if (s_pointInitialTopRight.is_null())
         {

            s_pointInitialTopRight = r.top_right();

         }

         auto offset = r.top_right() - s_pointInitialTopRight;

         //information() << "TopRightOffsetFromInitial : " << offset;

         if (offset.cx() != 0 || offset.cy() != 0)
         {

            //            information() << "Offset is Not Null";

         }

         _set_window_position_unlocked(
            zOutput,
            pointDesign.x(),
            pointDesign.y(),
            sizeOutput.cx(),
            sizeOutput.cy(),
            activationOutput,
            !bZ, !bMove, !bSize,
            edisplayOutput);

         bool bConsiderPositionAsSetOnConfigure = true;

         if (bConsiderPositionAsSetOnConfigure)
         {

            stateWindow.m_point2 = stateOutput.m_point2;

            stateWindow.m_size = stateOutput.m_size;

         }

         stateWindow.display() = stateOutput.display();

         stateOutput.m_activation.clear();

         stateOutput.m_zorder.clear_request();

      }
      else
      {

         _set_window_position_unchanged();

      }

      return true;

   }



   bool window::_set_window_position_unlocked(const class ::zorder& zorder, int x, int y, int cx, int cy,
      const ::user::activation& useractivation, bool bNoZorder, bool bNoMove,
      bool bNoSize, ::e_display edisplay)
   {

      bool bOk1 = _configure_window_unlocked(zorder, useractivation, bNoZorder, edisplay);

      bool bOk2 = _strict_set_window_position_unlocked(x, y, cx, cy, bNoMove, bNoSize);

      return bOk1 && bOk2;

   }


   void window::_set_window_position_unchanged()
   {


   }


   bool
      window::_configure_window_unlocked(const class ::zorder& zorder, const ::user::activation& useractivation, bool bNoZorder,
         ::e_display edisplay)
   {

      bool bOk = false;

      return bOk;

   }


   bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
   {

      if (!is_window_zoomed() && !is_full_screen())
      {
         bool bMove = !bNoMove;

         bool bSize = !bNoSize;

         if (bMove)
         {

            if (bSize)
            {

               set_rectangle_unlocked(::int_rectangle_dimension(x, y, cx, cy));

            }
            else
            {

               set_position_unlocked({ x, y });

            }

         }
         else if (bSize)
         {

            set_size_unlocked({ cx, cy });

         }

      }

      return true;

   }


   void window::__update_graphics_buffer()
   {

   }


   //   void window::window_request_presentation()
   //   {
   //
   //      this->windowing()->windowing_post([this]()
   //                                   { _window_request_presentation_locked(); });
   //
   ////      auto window_show = [this]()
   ////      {
   ////
   ////         auto pwindow = m_pwindow;
   ////
   ////         if (::is_set(pwindow))
   ////         {
   ////
   ////            auto puserinteraction = user_interaction();
   ////
   ////            if (::is_set(puserinteraction))
   ////            {
   ////
   ////               auto pwindow2 = puserinteraction->m_pinteractionimpl;
   ////
   ////               if (::is_set(pwindow2))
   ////               {
   ////
   ////                  pwindow2->window_show();
   ////
   ////               }
   ////
   ////            }
   ////
   ////         }
   ////
   ////      };
   ////
   ////      this->windowing()->windowing_post(window_show);
   //
   //   }


      //void window::_window_request_presentation_locked()
      //{


      //}


   //   void window::_window_request_presentation_set_window_position_unlocked(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::e_activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
   //   {
   //
   //
   //   }


   void window::frame_toggle_restore(::user::activation_token* puseractivationtoken)
   {

      user_interaction()->frame_toggle_restore(puseractivationtoken);

   }


   //void window::user_send(const ::procedure & procedure)
   //{

   //   //auto pwindow = m_pwindow;

   //   //if (pwindow)
   //   {

   //      auto puserinteraction = user_interaction();

   //      if (puserinteraction)
   //      {

   //         puserinteraction->user_send(procedure);

   //         return;

   //         //            auto pthread = m_puserthread;
   //         //
   //         //            if (pthread)
   //         //            {
   //         //
   //         //               pthread->post_procedure(procedure);
   //         //
   //         //               return;
   //         //
   //         //            }

   //      }

   //   }

   //   throw ::exception(error_failed);

   //}


   //void window::user_post(const ::procedure & procedure)
   //{

   //   //auto pwindow = m_pwindow;

   //   //if (pwindow)
   //   {

   //      auto puserinteraction = user_interaction();

   //      if (puserinteraction)
   //      {

   //         puserinteraction->user_post(procedure);

   //         return;

   //         //            auto pthread = m_puserthread;
   //         //
   //         //            if (pthread)
   //         //            {
   //         //
   //         //               pthread->post_procedure(procedure);
   //         //
   //         //               return;
   //         //
   //         //            }

   //      }

   //   }

   //   throw ::exception(error_failed);

   //}


//   void window::main_send(const ::procedure & procedure)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      user_send(procedure);
//
//#else
//
//      node()->main_send(procedure);
//
//#endif
//
//   }


//   void window::main_post(const ::procedure & procedure)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      user_post(procedure);
//
//#else
//
//      node()->main_post(procedure);
//
//#endif
//
//   }




   bool window::is_branch_current() const
   {

      return false;

   }


   itask window::get_itask() const
   {

      itask itask = nullptr;

      if (m_puserthread)
      {

         itask = m_puserthread->get_itask();

      }
      else
      {

         itask = current_itask();

      }

      return itask;

   }


   void window::on_touch_down(int xHost, int yHost, int xAbsolute, int yAbsolute)
   {

      ::lparam lparam(xHost, yHost);

      m_pointCursor2.x() = xHost;

      m_pointCursor2.y() = yHost;

      auto pdisplay = this->display();

      pdisplay->m_pointCursor2.x() = xAbsolute;

      pdisplay->m_pointCursor2.y() = yAbsolute;

      user_interaction()->post_message(e_message_left_button_down, 0, lparam);

   }


   void window::on_touch_drag(int xHost, int yHost, int xAbsolute, int yAbsolute)
   {

      ::lparam lparam(xHost, yHost);

      m_pointCursor2.x() = xHost;

      m_pointCursor2.y() = yHost;

      m_pdisplay->m_pointCursor2.x() = xAbsolute;

      m_pdisplay->m_pointCursor2.y() = yAbsolute;

      user_interaction()->post_message(e_message_mouse_move, 0, lparam);

   }


   void window::on_touch_up(int xHost, int yHost, int xAbsolute, int yAbsolute)
   {

      ::lparam lparam(xHost, yHost);

      m_pointCursor2.x() = xHost;

      m_pointCursor2.y() = yHost;

      m_pdisplay->m_pointCursor2.x() = xAbsolute;

      m_pdisplay->m_pointCursor2.y() = yAbsolute;

      user_interaction()->post_message(e_message_left_button_up, 0, lparam);

   }


   void window::on_size(int w, int h)
   {

      ::lparam lparam(w, h);

      user_interaction()->post_message(e_message_size, 1024, lparam);

   }


   void window::on_text(const ::ansi_character* pansisz, character_count length)

   {

      ::string strTextToInsert(pansisz, length);

      if (m_pacmeuserinteractionKeyboardFocus)
      {

         m_pacmeuserinteractionKeyboardFocus->insert_text(strTextToInsert, true, ::e_source_user);

      }

   }


   void window::on_text(const ::wd16_character* pwd16sz, character_count length)
   {


   }


   void window::on_text(const ::wd32_character* pwd32sz, character_count length)
   {


   }

   //
   // ::aura::application * window::get_app()
   // {
   //
   //    return m_papplication && m_papplication->m_papplication ? m_papplication->m_papplication
   //       : nullptr;
   //
   // }
   //
   //
   // ::aura::session * window::session()
   // {
   //
   //    return m_papplication && m_papplication->m_psession ? m_papplication->m_psession : nullptr;
   //
   // }


   //::aura::system* windowacmesystem()
   //{

   //   return system() ? system() : nullptr;

   //}


   void window::window_update_screen()
   {

      auto puserinteraction = user_interaction();

      if (!(puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update))
      {

         //#ifdef LINUX

         //if (bStartWindowVisual)
         //{

         //puserinteraction->_window_request_presentation_locked();

         //m_pimpl->window_show();

         //}

         //#endif
         ////END IFDEF LINUX

      }

      // if (m_bVisualUpdated)
      // {

      //    m_bVisualUpdated = false;

      //    if (::is_set(m_pimpl->m_puserthread))
      //    {

      //       m_pimpl->m_puserthread->m_happeningApplyVisual.wait(15_s);

      //    }

      // }

      if (!this->task_get_run())
      {

         //return false;
         return;

      }

      bool bWindowsApplyVisual = true;

      auto& edisplayOutput = puserinteraction->const_layout().output().m_edisplay;

      auto& edisplayDesign = puserinteraction->const_layout().design().m_edisplay;

      if (edisplayOutput != edisplayDesign)
      {

         puserinteraction->send_message(e_message_show_window, ::is_screen_visible(edisplayDesign) ? 1 : 0);

      }


#if TIME_REPORTING

      auto e1 = g_timeBetweenUpdateBufferAndUpdateScreen.elapsed();

      ::time timeUpdateScreenPost;

      timeUpdateScreenPost.Now();

      informationf("timeBetweenUpdateBufferAndUpdateScreen " + as_string(e1.floating_millisecond().m_d) + "ms\n");

#endif

      //if (m_bUpdateScreen && (bWindowsApplyVisual || !bStartWindowVisual))
      {


         m_pgraphicsthread->graphics_thread_update_screen();

      }
      //else
      //{

      //   information() << "no update screen";

      //}

#if TIME_REPORTING

      auto e2 = timeUpdateScreenPost.elapsed();

      informationf("timeUpdateScreenPost " + as_string(e2.floating_millisecond().m_d) + "ms\n");

#endif

      puserinteraction->set_display(edisplayDesign, ::user::e_layout_output);

      if (!puserinteraction)
      {

         return;

      }

      if ((puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update))
      {
         // IFDEF WINDOWS
         //if (bStartWindowVisual)
         //{

         //puserinteraction->_window_request_presentation_locked();

         //m_pimpl->window_show();
         //user_interaction()->post_procedure(m_procedureWindowShow);

         //}
         // ENDIF WINDOWS
      }


   }


   bool window::defer_perform_entire_reposition_process(::user::mouse* pmouse)
   {

      return false;

   }


   bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse* pmouse)
   {

      return false;

   }


   void window::final_mouse_message_handling(::message::mouse* pmouse)
   {

      //information() << "pmouse set";

      try
      {

         ::windowing::cursor* pcursor = nullptr;

         //if(::is_set(pimpl))
         {

            __check_refdbg;

            auto puserinteraction = user_interaction();

            __check_refdbg;

            if (::is_set(puserinteraction))
            {

               __check_refdbg;

               pcursor = puserinteraction->user_mouse_get_cursor(pmouse);

               __check_refdbg;

            }

         }

         if (!pcursor)
         {

            __check_refdbg;

            pcursor = get_mouse_cursor();

            __check_refdbg;

            if (pcursor)
            {

               //information() << "got window cursor : " << pcursor->m_ecursor;

            }

         }
         else
         {

            //information() << "got mouse cursor : " << pcursor->m_ecursor;

         }

         if (pcursor)
         {

            __check_refdbg;

            set_mouse_cursor(pcursor);

            __check_refdbg;

         }


      }
      catch (...)
      {


      }


      //      if(::is_null(pmouse))
      //      {
      //
      //         return;
      //
      //      }
      //
      //      try
      //      {
      //
      //         aaaset_mouse_cursor(pmouse->m_pcursor);
      //
      //      }
      //      catch(...)
      //      {
      //
      //      }

   }


   ::user::interaction* window::user_interaction()
   {

      ::cast < ::user::interaction > puserinteraction = m_pacmeuserinteraction;

      if (!puserinteraction)
      {

         return nullptr;

      }

      return puserinteraction;

   }



   ::user::interaction* window::user_interaction() const
   {

      return const_cast <window*>(this)->user_interaction();

   }


   ::user::interaction* window::owner_interaction()
   {

      ::cast < ::user::interaction > pinteraction = user_interaction();

      if (!pinteraction)
      {

         return nullptr;

      }

      auto pwindowingwindow = pinteraction->owner_window();

      if (!pwindowingwindow)
      {
         return nullptr;
      }

      return pwindowingwindow->user_interaction();

   }


   ::trace_statement& window::trace_statement_prefix(::trace_statement& statement) const
   {

      statement << "window  ";

      //if(m_pwindow)
      {

         if (user_interaction())
         {

            user_interaction()->raw_trace_statement_prefix(statement);

         }

      }

      return statement;

   }


   bool window::is_windowing_popup()
   {

      return ::is_set(owner_interaction());

   }


   ::int_point window::windowing_popup_origin()
   {

      auto p = user_interaction()->const_layout().sketch().origin();

      if (user_interaction())
      {

         if (user_interaction()->get_parent())
         {

            user_interaction()->get_parent()->client_to_host()(p);

         }

      }

      return p;

   }


   ::int_size window::windowing_popup_size()
   {

      auto s = user_interaction()->const_layout().sketch().size();

      return s;

   }


   void window::_on_windowing_close_window()
   {

      user_interaction()->post_message(e_message_close);

   }


   bool window::is_satellite_window()
   {

      return user_interaction()->m_ewindowflag & e_window_flag_satellite_window;

   }


   ::windowing::window* window::owner_window()
   {

      ::cast < ::windowing::window  > pwindowingwindow = user_interaction()->owner_window();

      if (!pwindowingwindow)
      {

         return nullptr;

      }

      return pwindowingwindow;

   }


   ::string window::get_window_text()
   {

      return user_interaction()->get_window_text();

   }


   void window::defer_show_system_menu(::user::mouse* pmouse)
   {

   }


   //   ::message_queue * window::get_message_queue()
   //   {
   //
   //      return m_pmessagequeue;
   //
   //   }
   void window::pick_browse(const ::function < void(const ::file::path& path) >& callback)
   {
   }
   void window::pick_media(const_char_pointer pszMediaType)
   {
   }
   void window::on_prompt_write_file(::user::controller* pusercontroller)
   {

   }

   void window::set_opacity(double dOpacity)
   {


   }

   void window::window_restore()
   {


   }


   void window::window_minimize()
   {


   }


   void window::window_maximize()
   {


   }


   //window::interaction_impl()
   //{

   //   user_common_construct();

   //}


   //window::~interaction_impl()
   //{

   //}




   //void window::on_initialize_particle()
   //{

   //   defer_create_synchronization();

   //}


   void window::on_tsf_activate(bool bActivate)
   {

   }


   //void window::sketch_to_layout(::graphics::buffer_item * pbufferitem)
   //{

   //   user_interaction()->sketch_to_layout();

   //   pbufferitem->m_point = user_interaction()->const_layout().layout().origin();

   //   pbufferitem->m_size = user_interaction()->const_layout().layout().size();

   //}


   ::pointer<::mutex> window::draw_mutex()
   {

      if (m_pmutexDraw == nullptr)
      {

#if REFERENCING_DEBUGGING

         refdbg_top_track refdbgtoptrack(this);

#endif

         __øconstruct(m_pmutexDraw);

      }

      return m_pmutexDraw;

   }


   //::windowing::window * window::get_user_interaction_impl()
   //{

   //   return this;

   //}


   bool window::has_pending_redraw_flags()
   {

      return ::windowing::window_base::has_pending_redraw_flags();

   }


   //void window::set_need_layout()
   //{

   //   user_interaction()->set_need_layout();

   //}


   bool window::has_pending_focus()
   {

      auto psession = session();

      if (::is_null(psession))
      {

         return false;

      }

      if (::is_null(psession->m_puserinteractionPendingFocus2))
      {

         return false;

      }

      if (psession->m_puserinteractionPendingFocus2 != this)
      {

         return false;

      }

      return true;

   }


   bool window::clear_pending_focus()
   {

      auto psession = session();

      if (::is_null(psession))
      {

         return false;

      }

      if (::is_null(psession->m_puserinteractionPendingFocus2))
      {

         return false;

      }

      if (psession->m_puserinteractionPendingFocus2 != this)
      {

         return false;

      }

      psession->m_puserinteractionPendingFocus2 = nullptr;

      return true;

   }


   bool window::set_pending_focus()
   {

      auto psession = session();

      if (::is_null(psession))
      {

         return false;

      }

      psession->m_puserinteractionPendingFocus2 = this;

      return true;

   }


   void window::create_message_queue(::user::interaction* pinteraction, const ::scoped_string & scopedstrName)
   {

      if (_is_window())
      {

         auto puserinteraction = user_interaction();

         if (puserinteraction)
         {

            user_interaction()->set_window_text(scopedstrName);

         }

      }
      else
      {

         pinteraction->m_bMessageOnlyWindow = true;

         m_pacmeuserinteraction = pinteraction;

         //user_interaction() = pinteraction;

         //create_host(pinteraction, e_parallelization_synchronous);
         //create_host(pinteraction);
         create_window();

      }

   }



   //void window::create_native_window(::user::native_window_initialize* pinitialize)
   //{

   //   __UNREFERENCED_PARAMETER(pinitialize);
   //   throw ::interface_only();

   //   return false;

   //}

//#ifdef WINDOWS_DESKTOP
//
//
//   void window::GetWindowInfo(PWINDOWINFO pwi) const
//   {
//      __UNREFERENCED_PARAMETER(pwi);
//      throw ::interface_only();
//      return false;
//   }
//
//   void window::GetScrollBarInfo(int idObject,PSCROLLBARINFO psbi) const
//   {
//      __UNREFERENCED_PARAMETER(idObject);
//      __UNREFERENCED_PARAMETER(psbi);
//      throw ::interface_only();
//      return false;
//   }
//
//   void window::GetTitleBarInfo(PTITLEBARINFO pti) const
//   {
//      __UNREFERENCED_PARAMETER(pti);
//      throw ::interface_only();
//      return false;
//   }
//
//#endif

//#if !defined(LINUX) && !defined(__APPLE__) && !defined(__ANDROID__) && !defined(__BSD__)
//
//
//    ::windowing::window * window::GetAncestor(unsigned int gaFlags) const
//    {
//
//       __UNREFERENCED_PARAMETER(gaFlags);
//
//       throw ::interface_only();
//
//       return nullptr;
//
//    }
//
//
//    //void window::AnimateWindow(::time ::time,unsigned int dwFlags)
//    //{
//    //   __UNREFERENCED_PARAMETER(::time);
//    //   __UNREFERENCED_PARAMETER(dwFlags);
//    //   throw ::interface_only();
//    //   return false;
//    //}
//
//    //void window::FlashWindowEx(unsigned int dwFlags,unsigned int uCount,::time tickTimeout)
//    //{
//    //   __UNREFERENCED_PARAMETER(dwFlags);
//    //   __UNREFERENCED_PARAMETER(uCount);
//    //   __UNREFERENCED_PARAMETER(tickTimeout);
//    //   throw ::interface_only();
//    //   return false;
//    //}
//
//    //void window::SetLayeredWindowAttributes(::color::color crKey,unsigned char bAlpha,unsigned int dwFlags)
//    //{
//    //   __UNREFERENCED_PARAMETER(crKey);
//    //   __UNREFERENCED_PARAMETER(bAlpha);
//    //   __UNREFERENCED_PARAMETER(dwFlags);
//    //   throw ::interface_only();
//    //   return false;
//    //}
//
//    //void window::UpdateLayeredWindow(::draw2d::graphics * pDCDst,::int_point * pptDst,::int_size * psize,
//    //      ::draw2d::graphics * pDCSrc,::int_point * pptSrc,::color::color crKey,BLENDFUNCTION * pblend,unsigned int dwFlags)
//    //{
//    //   __UNREFERENCED_PARAMETER(pDCDst);
//    //   __UNREFERENCED_PARAMETER(pptDst);
//    //   __UNREFERENCED_PARAMETER(psize);
//    //   __UNREFERENCED_PARAMETER(pDCSrc);
//    //   __UNREFERENCED_PARAMETER(pptSrc);
//    //   __UNREFERENCED_PARAMETER(crKey);
//    //   __UNREFERENCED_PARAMETER(pblend);
//    //   __UNREFERENCED_PARAMETER(dwFlags);
//    //   throw ::interface_only();
//
//    //   return false;
//    //}
//
//
//    //void window::GetLayeredWindowAttributes(::color::color * pcrKey,unsigned char * pbAlpha,unsigned int * pdwFlags) const
//    //{
//    //   __UNREFERENCED_PARAMETER(pcrKey);
//    //   __UNREFERENCED_PARAMETER(pbAlpha);
//    //   __UNREFERENCED_PARAMETER(pdwFlags);
//    //   throw ::interface_only();
//
//    //   return false;
//    //}
//
//    //void window::PrintWindow(::draw2d::graphics_pointer & pgraphics,unsigned int nFlags) const
//    //{
//    //   __UNREFERENCED_PARAMETER(pgraphics);
//    //   __UNREFERENCED_PARAMETER(nFlags);
//    //   throw ::interface_only();
//
//    //   return false;
//    //}
//
//#endif


   //lresult window::default_window_procedure()
   //{
   //
   //   return default_window_procedure(m_uiMessage, m_wparam, m_lparam);

   //}


   void window::pre_subclass_window()
   {

      throw ::interface_only();

   }


   ::windowing::window* window::from_os_data(void* pdata)
   {

      __UNREFERENCED_PARAMETER(pdata);

      throw ::interface_only();

      return nullptr;

   }


   void* window::get_os_data() const
   {

      throw ::interface_only();

      return nullptr;

   }


   //void window::create_host(::user::interaction * pinteraction, ::user::interaction_base * pprimitiveParent)
   //{

   //   //if (!pparent)
   //   {

   //      if (!native_create_window())
   //      {

   //         return false;

   //      }

   //   }
   //   //else
   //   //{

   //   //   if (!native_create_window_ex(pinteraction, pusersystem, puiParent->get_safe_handle(), atom))
   //   //   {

   //   //      return false;

   //   //   }

   //   //}

   //   return true;

   //}


   // for child windows
   bool window::pre_create_window(::user::system* pusersystem)
   {

      __UNREFERENCED_PARAMETER(pusersystem);

      return true;

   }


   //void window::operating_system_create_host(enum_parallelization eparallelization)
   void window::operating_system_create_host()
   {

      //      auto pwindowMain = system()->m_pwindowMain;
      //
      //      if (pwindowMain && !pwindowMain->m_pwindow)
      //      {
      //
      //         m_pwindow = system()->m_pwindowMain;
      //
      //         m_pwindow = this;
      //
      //         user_interaction()->m_pinteractionimpl = this;
      //
      //      }
      //      else
      //      {
      //
      //         //auto estatus =
      //
      //         __øconstruct(m_pwindow);
      //
      //         //if (!estatus)
      //         //{
      //
      //         //   return estatus;
      //
      //         //}
      //
      //         if (!system()->m_pwindowMain)
      //         {
      //
      //            system()->m_pwindowMain = m_pwindow;
      //
      //         }
      //
      //      }
      //
      //      //auto estatus =
      //
      //      create_window(this);
      //
      //      //if (!estatus)
      //      //{
      //
      //      //   return estatus;
      //
      //      //}
      //
      //      //return true;

      ::pointer<::user::system> pusersystem;

      if (!user_interaction()->is_system_message_window())
      {

         if (user_interaction()->m_pusersystem)
         {

            pusersystem = user_interaction()->m_pusersystem;

         }
         else
         {

            pusersystem = __allocate::user::system();

         }

      }

      //      //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || is_string_ok(pusersystem->m_createstruct.lpszName));
      //      //
      //      if (!user_interaction()->pre_create_window(pusersystem))
      //      {
      //
      //         //return false;
      //
      //         throw ::exception(error_failed);
      //
      //      }

            //m_puserthread = ::get_task();

            //m_pthreadUserImpl = m_puserthread;

            //install_message_routing(user_interaction());

            //bool bOk = true;

            //      if(pusersystem->m_createstruct.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
            //      {
            //
            //         auto pwindowing = m_pwindowwindowing();
            //
            //         m_oswindow = pwindowing->new_message_window(this);
            //
            //         user_interaction()->m_bMessageWindow = true;
            //
            //         //send_message(e_message_create, 0, (LPARAM) &cs);
            //
            //      }
            //      else

            //_create_window(eparallelization);

      auto puserinteraction = user_interaction();

      int x = puserinteraction->const_layout().sketch().origin().x();

      int y = puserinteraction->const_layout().sketch().origin().y();

      int cx = puserinteraction->const_layout().sketch().width();

      int cy = puserinteraction->const_layout().sketch().height();

      m_pointWindow.x() = x;

      m_pointWindow.y() = y;

      m_sizeWindow.cx() = cx;

      m_sizeWindow.cy() = cy;

      _create_window();

      //      if(bOk)
      //      {
      //
      //         user_interaction()->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);
      //
      //         user_interaction()->m_ewindowflag |= e_window_flag_window_created;
      //
      //      }

      //if (!bOk)
      //{

      //   throw ::exception(error_failed);

      //}


   }


   ////void window::_create_window(::enum_parallelization eparallelization)
   //void window::_create_window()
   //{

   //   ////{

   //   //user_interaction()->m_bMessageWindow = false;


   //   ////         auto procedure = [&]()
   //   ////         {

   //   //auto psession = session();

   //   //auto puser = user();

   //   //auto pwindowing = system()->windowing();

   //   ////      auto psession = session();

   //   ////      auto puser = user();

   //   ////      auto pwindowing = system()->windowing();

   //   ////pwindowing->new_window();

   //   //if (m_pwindow)
   //   //{

   //   //   information() << "operating_system_create_host window created";

   //   //}
   //   //else
   //   //{

   //   //   informationf("operating_system_create_host window not created");

   //   //}

   //   ////         };
   //   ////
   //   ////
   //   ////         //if (eparallelization == e_parallelization_asynchronous)
   //   ////         //{
   //   ////
   //   ////         ///user_post(procedure);
   //   ////
   //   ////         //}
   //   ////         //else
   //   ////         //{
   //   ////
   //   ////         main_send(procedure);
   //   ////
   //   ////         //}
   //   ////
   //   ////
   //   ////         //});

   //   //      }

   //}


   void window::native_create_host_alternate()
   {

      //      auto pwindowMain = system()->m_pwindowMain;
      //
      //      if (pwindowMain && !pwindowMain->m_pwindow)
      //      {
      //
      //         m_pwindow = system()->m_pwindowMain;
      //
      //         m_pwindow = this;
      //
      //         user_interaction()->m_pinteractionimpl = this;
      //
      //      }
      //      else
      //      {
      //
      //         //auto estatus =
      //
      //         __øconstruct(m_pwindow);
      //
      //         //if (!estatus)
      //         //{
      //
      //         //   return estatus;
      //
      //         //}
      //
      //         if (!system()->m_pwindowMain)
      //         {
      //
      //            system()->m_pwindowMain = m_pwindow;
      //
      //         }
      //
      //      }
      //
      //      //auto estatus =
      //
      //      create_window(this);
      //
      //      //if (!estatus)
      //      //{
      //
      //      //   return estatus;
      //
      //      //}
      //
      //      //return true;

      ::pointer<::user::system> pusersystem;

      if (user_interaction()->m_pusersystem)
      {

         pusersystem = user_interaction()->m_pusersystem;

      }
      else
      {

         pusersystem = __allocate::user::system();

      }

      //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || is_string_ok(pusersystem->m_createstruct.lpszName));
      //
      if (!user_interaction()->pre_create_window(pusersystem))
      {

         //return false;

         throw ::exception(error_failed);

      }

      //m_puserthread = ::get_task();

      //m_pthreadUserImpl = m_puserthread;

      install_message_routing(user_interaction());

      bool bOk = true;

      //      if(pusersystem->m_createstruct.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
      //      {
      //
      //         auto pwindowing = m_pwindowwindowing();
      //
      //         m_oswindow = pwindowing->new_message_window(this);
      //
      //         user_interaction()->m_bMessageWindow = true;
      //
      //         //send_message(e_message_create, 0, (LPARAM) &cs);
      //
      //      }
      //      else
      {

         user_interaction()->m_bMessageOnlyWindow = false;

         //auto pwindowing = windowing();
         user_send([&]()
            {

               auto pwindowing = windowing();

               //pwindowing->new_window(this);

               //if (m_pwindow)
               //{

               //   informationf("window created");

               //}
               //else
               //{

               //   informationf("window not created");

               //}

            });

      }

      //      if(bOk)
      //      {
      //
      //         user_interaction()->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);
      //
      //         user_interaction()->m_ewindowflag |= e_window_flag_window_created;
      //
      //      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   //    //void window::create_host(::user::interaction * puserinteraction, enum_parallelization eparallelization)
   //    void window::create_host(::user::interaction * puserinteraction)
   //    {
   //
   //       user_interaction() = puserinteraction;
   //
   //#if REFERENCING_DEBUGGING
   //
   //       ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });
   //
   //#endif
   //
   //       user_interaction()->m_pwindow = this;
   //
   //#if REFERENCING_DEBUGGING
   //
   //       ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });
   //
   //#endif
   //
   //       //user_interaction()->m_pinteractionimpl = this;
   //
   //#if !defined(UNIVERSAL_WINDOWS) && !defined(WINDOWS_DESKTOP)
   //
   //       user_interaction()->m_ewindowflag |= e_window_flag_postpone_visual_update;
   //
   //#endif
   //
   //       //      auto pusersystem = puserinteraction->m_pusersystem;
   //       //
   //       //      if(pusersystem)
   //       //      {
   //       //
   //       //         add(pusersystem->m_prequest);
   //       //
   //       //         for(auto & poutputpurpose : pusersystem->m_graphicsoutputpurposea)
   //       //         {
   //       //
   //       //            information() << "adding graphical output_purpose from user::system";
   //       //
   //       //            add(poutputpurpose);
   //       //
   //       //         }
   //       //
   //       //      }
   //
   //       bool bNewOwnThread = true;
   //
   //       bool bProdevianThread = true;
   //
   //       //if (user_interaction()->GetStyle() & WS_CHILD)
   //       //{
   //
   //       //   // if child, uses parent window thread,
   //
   //       //   bNewOwnThread = false;
   //
   //       //   bProdevianThread = false;
   //
   //       //}
   //
   //       if (user_interaction()->m_bMessageWindow)
   //       {
   //
   //          // except if "message"-only-window, in which casen it will have own thread
   //
   //          bNewOwnThread = true;
   //
   //          bProdevianThread = false;
   //
   //       }
   //
   //       if (user_interaction()->m_ewindowflag & e_window_flag_satellite_window)
   //       {
   //
   //          if (user_interaction()->m_puserinteractionOwner)
   //          {
   //
   //             auto pthread = user_interaction()->m_puserinteractionOwner->user_thread();
   //
   //             //m_puserthread = pthread;
   //
   //             m_puserthread = pthread;
   //
   //          }
   //
   //          // all except if satellite window it will use calling thread/parent window thread
   //
   //          bNewOwnThread = false;
   //
   //       }
   //
   //       if (!user_interaction()->is_graphical())
   //       {
   //
   //          bProdevianThread = false;
   //
   //       }
   //
   //       //user_interaction()->place(int_rectangle_dimension(
   //       //                      pusersystem->m_createstruct.x(),
   //       //                      pusersystem->m_createstruct.y(),
   //       //                      pusersystem->m_createstruct.cx(),
   //       //                      pusersystem->m_createstruct.cy()));
   //
   //       //auto psynca = __allocate synchronization_array();
   //
   //       //::pointer<manual_reset_happening>phappeningStartedUser;
   //
   //       //::pointer<manual_reset_happening>phappeningStartedProdevian;
   //
   //       ::pointer<::user::thread> puserthread;
   //
   //       if (bNewOwnThread)
   //       {
   //
   //          puserthread = __create_new<::user::thread>();
   //
   //          m_puserthread = puserthread;
   //
   //          auto papp = get_app();
   //
   //          if (::is_set(papp))
   //          {
   //
   //             papp->add_task(m_puserthread);
   //
   //          }
   //
   //          m_puserthread->initialize_user_thread(this);
   //
   //          m_puserthread = m_puserthread;
   //
   //          //phappeningStartedUser = __allocate manual_reset_happening();
   //
   //          //m_puserthread->m_phappeningStarted = phappeningStartedUser;
   //
   //       }
   //
   //#if REFERENCING_DEBUGGING
   //
   //       ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });
   //
   //#endif
   //
   //       m_puserthread->add_task(user_interaction());
   //
   //       ::pointer<::user::graphics_thread> pgraphicsthread;
   //
   //       if (bProdevianThread && user_interaction()->is_graphical())
   //       {
   //
   //          pgraphicsthread = __create_new<::user::graphics_thread>();
   //
   //          m_pgraphicsthread = pgraphicsthread;
   //
   //          //auto pusersystem = user_interaction()->m_pusersystem;
   //
   //          //if (pusersystem)
   //          //{
   //
   //          //   auto prequest = pusersystem->m_prequest;
   //
   //          //   if (prequest)
   //          //   {
   //
   //          //      information() << "pgraphicsthread->m_happeningReady.reset_happening();";
   //
   //          //      pgraphicsthread->m_happeningReady.reset_happening();
   //
   //          //      prequest->m_procedureaOnFinishRequest.add(
   //          //         [this, pgraphicsthread]()
   //          //         {
   //
   //          //            information() << "pgraphicsthread->m_happeningReady.set_happening();";
   //
   //          //            pgraphicsthread->m_happeningReady.set_happening();
   //
   //          //         });
   //
   //          //   }
   //
   //          //}
   //
   //          m_pgraphicsthread->initialize_graphics_thread(this);
   //
   //          user_interaction()->add_task(m_pgraphicsthread);
   //
   //          m_pgraphicsthread->m_puserthread = m_puserthread;
   //
   //       }
   //
   //       if (bNewOwnThread)
   //       {
   //
   //          information() << "window::create_host user thread branch";
   //
   //          //if (!m_puserthread->begin_synch())
   //          //m_puserthread->branch(eparallelization);
   //          // m_puserthread->branch(e_parallelization_synchronous);
   //          m_puserthread->branch(e_parallelization_synchronous);
   //          //{
   //
   //          //   __release(m_pgraphicsthread);
   //
   //          //   __release(m_puserthread);
   //
   //          //   user_interaction()->__release(m_puserthread);
   //
   //          //   return false;
   //
   //          //}
   //
   // //         psynca->add(phappeningStartedUser);
   // //
   // //         auto proutine = __routine([this, psynca]()
   // //            {
   // //
   // //               if (!user_interaction() ||
   // //                  //(m_puserthread->m_bCreateNativeWindowOnInteractionThread
   // //                     //&&
   // //                  !user_interaction()->is_window())
   // //                  //)
   // //               {
   // //
   // //                  return;
   // //
   // //               }
   // //
   // //               if (m_puserthread->m_result.failed())
   // //               {
   // //
   // //                  if (user_interaction())
   // //                  {
   // //
   // //                     user_interaction()->__release(m_puserthread);
   // //
   // //                  }
   // //
   // //                  __release(m_pgraphicsthread);
   // //
   // //                  __release(m_puserthread);
   // //
   // //                  return;
   // //
   // //               }
   // //
   // //               //phappeningStartedUser.release();
   // //
   // //               if (::is_set(m_pgraphicsthread))
   // //               {
   // //
   // //                  if (m_pgraphicsthread->m_result.failed())
   // //                  {
   // //
   // //                     if (user_interaction())
   // //                     {
   // //
   // //                        user_interaction()->__release(m_puserthread);
   // //
   // //                     }
   // //
   // //                     __release(m_pgraphicsthread);
   // //
   // //                     __release(m_puserthread);
   // //
   // //                     return;
   // //
   // //                  }
   // //
   // //                 // phappeningStartedProdevian.release();
   // //
   // //               }
   // //
   // //            });
   //
   //          //if (pusersystem->m_procedureSuccess)
   //          //{
   //
   //          //   fork([psynca, proutine, pusersystem]()
   //          //   {
   //
   //          //      psynca->wait();
   //
   //          //      (*proutine)();
   //
   //          //      pusersystem->m_procedureSuccess();
   //
   //          //   });
   //
   //          //}
   //          //else
   //          //{
   //
   //          ///psynca->wait();
   //
   //          //   (*proutine)();
   //
   //          //}
   //
   //       }
   //       else
   //       {
   //
   //          //psynca->wait(true, one_minute());
   //
   //          //if (::is_set(m_pgraphicsthread))
   //          //{
   //
   //          // phappeningStartedProdevian.release();
   //
   //          //}
   //
   //          //operating_system_create_host(eparallelization);
   //
   //          operating_system_create_host();
   //
   //          ////if (!native_create_host())
   //          //{
   //
   //          //   return false;
   //
   //          //}
   //
   //       }
   //
   //       //if (m_puserthread && !m_puserthread->m_bCreateNativeWindowOnInteractionThread)
   //       //{
   //
   //       //   send_message(e_message_create, 0, (lparam)&pusersystem);
   //
   //       //   //user_interaction()->set_dim(pusersystem->m_createstruct.x(), pusersystem->m_createstruct.cy(), pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy());
   //
   //       //   send_message(e_message_size, 0, MAKELPARAM(pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy()));
   //
   //       //   user_interaction()->increment_reference_count(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);
   //
   //       //   user_interaction()->m_ewindowflag |= ::e_window_flag_is_window;
   //
   //       //   user_interaction()->m_ewindowflag |= ::e_window_flag_window_created;
   //
   //       //}
   //
   //       //return true;
   //
   //    }


   ::color::color window::screen_pixel(int x, int y)
   {

      if (::is_null(m_pgraphicsgraphics))
      {

         return color::transparent;

      }

      auto origin = user_interaction()->const_layout().window().origin();

      //information() << "screen_pixel window().origin() : " << origin;

      return m_pgraphicsgraphics->get_screen_item()->m_pimage2->pixel(x - origin.x(), y - origin.y());

   }


   //void window::native_create_window()
   //{
   //   return false;
   //}


//   void window::create_host(::user::interaction * puserinteraction)
//   {
//
//      user_interaction() = puserinteraction;
//      // can't use for desktop or pop-up windows (use create_window_ex instead)
//      //ASSERT(puiParent != nullptr);
//      //ASSERT((uStyle & WS_POPUP) == 0);
//
//      //auto pusersystem = __allocate ::user::system();
//
//      //pusersystem->m_createstruct.dwExStyle = 0;
//
////#ifdef WINDOWS
////
////      wstring wstrClassName(scopedstrClassName);
////      pusersystem->m_createstruct.lpszClass = wstrClassName;
////      wstring wstrWindowName(scopedstrWindowName);
////      pusersystem->m_createstruct.lpszName = wstrWindowName;
////
////#else
////
////      pusersystem->m_createstruct.lpszClass = pszClassName;
////      pusersystem->m_createstruct.lpszName = pszWindowName;
////
////#endif
//
//      //pusersystem->m_createstruct.style = uStyle | WS_CHILD;
//      //pusersystem->m_createstruct.x() = rectangle.left();
//      //pusersystem->m_createstruct.y() = rectangle.top();
//      //pusersystem->m_createstruct.cx() = rectangle.width();
//      //pusersystem->m_createstruct.cy() = rectangle.height();
//      //pusersystem->m_createstruct.hwndParent = puiParent->get_safe_handle();
//      //pusersystem->m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (LPVOID)pcreate;
//
//      return native_create_window();
//
//   }


   //void window::prio_install_message_routing(::channel * pchannel)
   //{

   //   //::windowing::window_base::prio_install_message_routing(pchannel);

   //   MESSAGE_LINK(e_message_create, pchannel, this, &window::_001OnPrioCreate);
   //   MESSAGE_LINK(e_message_set_focus, pchannel, this, &window::on_prio_message_set_focus);

   //}


   void window::last_install_message_routing(::channel* pchannel)
   {

      ///MESSAGE_LINK(e_message_create, pchannel, this, &window::on_message_create);

      //::windowing::window_base::last_install_message_routing(pchannel);

      if (!user_interaction()->m_bMessageOnlyWindow)
      {

         //MESSAGE_LINK(e_message_redraw, pchannel, this, &window::_001OnRedraw);
         //MESSAGE_LINK(e_message_apply_visual, pchannel, this, &window::_001OnApplyVisual);


         //#ifndef LINUX
         MESSAGE_LINK(e_message_reposition, pchannel, this, &window::on_message_reposition);
         MESSAGE_LINK(e_message_size, pchannel, this, &window::on_message_size);
         //MESSAGE_LINK(e_message_window_position_changed, pchannel, this, &window::on_message_window_position_changed);
         //#endif

         MESSAGE_LINK(e_message_show_window, pchannel, this, &window::on_message_show_window);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &window::on_message_set_focus);
         MESSAGE_LINK(e_message_kill_focus, pchannel, this, &window::on_message_kill_focus);

      }

      MESSAGE_LINK(e_message_destroy_window, pchannel, this, &window::_001OnDestroyWindow);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &window::on_message_destroy);

   }


   void window::_000OnMouseLeave(::message::message* pmessage)
   {

      if (m_bDestroyImplOnly)
      {

         return;

      }

      //user_interaction()->m_pitemHover = nullptr;

#ifdef WINDOWS_DESKTOP
      if (!m_bTransparentMouseEvents)
#endif
      {

         ::int_point pointInvalid; // For long future hope still : Invalid

         minimum(pointInvalid.x());
         minimum(pointInvalid.y());

         _on_mouse_move_step(pointInvalid, true);

         //::pointer<::user::interaction>pinteraction;

         //::int_rectangle rectangleUi;

         //auto psession = session();

         //auto puser = user();

         //auto pwindowing = system()->windowing();

         //auto pointCursor = pwindowing->get_cursor_position();

         //::user::interaction_array uia;

         //{

         //   _synchronous_lock synchronouslock(this->synchronization());

         //   uia = m_uiptraMouseHover;

         //   m_uiptraMouseHover.erase_all();

         //}

         //for(auto & pinteraction : uia.interactiona())
         //{

         //   try
         //   {

         //      pinteraction->send_message(e_message_mouse_leave);

         //   }
         //   catch (...)
         //   {

         //   }

         //}

      }

   }


   //   void window::_001OnTriggerMouseInside()
   //   {
   //
   //      //user_interaction()->m_bMouseHover = true;
   //
   //   }


   //void window::_008OnMouse(::message::mouse * pmouse)
   //{

   //   if(!user_interaction())
   //   {

   //      return;

   //   }

   //   bool bPointInside;

   //   bPointInside = user_interaction()->_001IsPointInside(pmouse->m_point);

   //   if (!bPointInside)
   //   {

   //      if (pmouse->userinteraction() == user_interaction())
   //      {

   //         bPointInside = true;

   //      }

   //   }

   //   if (pmouse->m_emessage == e_message_left_button_up)
   //   {

   //      informationf("lbutton_up");

   //   }

   //   if(pmouse->m_emessage == ::e_message_left_button_down)
   //   {

   //      on_configuration_change(user_interaction());

   //   }

   //   {

   //      ::user::interaction_array uia;

   //      {

   //         _synchronous_lock synchronouslock(this->synchronization());

   //         for(auto & pinteraction : m_uiptraMouseHover)
   //         {

   //            try
   //            {

   //               if (!pinteraction->_001IsPointInside(pmouse->m_point))
   //               {

   //                  uia.add_interaction(pinteraction);

   //               }

   //            }
   //            catch(...)
   //            {

   //            }

   //         }

   //         ::papaya::array::erase_array(m_uiptraMouseHover, uia.interactiona());

   //      }

   //      for(auto & pinteraction : uia.interactiona())
   //      {

   //         pinteraction->send_message(e_message_mouse_leave);

   //      }

   //   }

   //   auto psession = session();

   //   if (!user_interaction()->m_bMouseHover && bPointInside)
   //   {

   //      user_interaction()->_001OnTriggerMouseInside();

   //   }

   //   if(has_mouse_capture())
   //   {

   //      if (pmouse->m_emessage == e_message_left_button_up)
   //      {

   //         informationf("lbutton_up");

   //      }

   //      ::user::interaction * puiCapture = m_puserinteractionCapture;

   //      if (puiCapture == nullptr)
   //      {

   //         puiCapture = user_interaction();

   //      }

   //      try
   //      {

   //         puiCapture->message_handler(pmouse);

   //      }
   //      catch (...)
   //      {

   //      }

   //      return;

   //   }

   //   if (user_interaction() != nullptr)
   //   {


   //      if (pmouse->m_emessage == e_message_left_button_up)
   //      {

   //         informationf("lbutton_up");

   //      }

   //      //_synchronous_lock synchronouslock(mutex_children());

   //      auto puserinteraction = user_interaction()->child_from_point(pmouse->m_point);

   //      if (!puserinteraction)
   //      {

   //         puserinteraction = user_interaction();

   //      }

   //      puserinteraction->message_handler(pmouse);



   //   }

   //   if (pmouse->m_bRet)
   //   {

   //      return;

   //   }

   //}


   void window::add(::graphics::output_purpose* pgraphicaloutputpurpose)
   {

      if (::is_null(pgraphicaloutputpurpose))
      {

         return;

      }

      if (pgraphicaloutputpurpose->m_egraphicsoutputpurpose == ::graphics::e_output_purpose_none)
      {

         return;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      bool bHadNoInterest = !has_graphical_output_purpose();

      bool bAdded = m_graphicaloutputpurposea.add_unique(pgraphicaloutputpurpose);

      if (bAdded && bHadNoInterest)
      {

         user_interaction()->set_need_redraw();

         user_interaction()->post_redraw();

      }

   }


   void window::erase(::graphics::output_purpose* pgraphicaloutputpurpose)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_graphicaloutputpurposea.erase(pgraphicaloutputpurpose);

   }


   void window::add_graphical_output_purpose(::particle* pparticleGraphicalOutputPurposeOriginator,
      ::graphics::enum_output_purpose epurpose)
   {

      if (::is_null(pparticleGraphicalOutputPurposeOriginator))
      {

         return;

      }

      if (epurpose == ::graphics::e_output_purpose_none)
      {

         return;

      }

      auto poutputpurpose = __allocate::graphics::output_purpose(pparticleGraphicalOutputPurposeOriginator, epurpose);

      bool bHadGraphicalOutputPurpose = user_interaction()->has_graphical_output_purpose();

      this->add(poutputpurpose);

      bool bHasGraphicalOutputPurpose = user_interaction()->has_graphical_output_purpose();

      if (bHasGraphicalOutputPurpose && !bHadGraphicalOutputPurpose)
      {

         user_interaction()->set_need_redraw();

         user_interaction()->post_redraw();

      }

   }


   void window::erase_graphical_output_purpose(::particle* pparticleGraphicalOutputPurposeOriginator)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_graphicaloutputpurposea.predicate_erase([pparticleGraphicalOutputPurposeOriginator](auto ppurpose)
         {

            return ppurpose->get_graphical_output_purpose_originator() ==
               pparticleGraphicalOutputPurposeOriginator;

         });

   }


   bool window::has_particle_fps_purpose(::particle* pparticleGraphicalOutputPurposeOriginator)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      return m_graphicaloutputpurposea.predicate_contains([pparticleGraphicalOutputPurposeOriginator](auto ppurpose)
         {

            return ppurpose->get_graphical_output_purpose_originator() ==
               pparticleGraphicalOutputPurposeOriginator
               && ppurpose->m_egraphicsoutputpurpose &
               ::graphics::e_output_purpose_fps;

         });

   }


   void window::mouse_hover_add(::user::interaction* pinterface)
   {

      if (pinterface == nullptr)
      {

         return;

      }

      bool bWasEmpty = false;

      {

         _synchronous_lock synchronouslock(this->synchronization());

         bWasEmpty = m_userinteractionaMouseHover.is_empty();

         m_userinteractionaMouseHover.add_unique(pinterface);

         if (bWasEmpty)
         {

            track_mouse_hover();

         }

      }

   }


   void window::track_mouse_hover()
   {

      //track_mouse_hover();

   }


   void window::track_mouse_leave()
   {

      //__defer_fork(MouseLeave);

   }


   void window::_on_mouse_move_step(const ::int_point& pointCursor, bool bMouseLeave)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (::collection::index i = 0; i < m_userinteractionaMouseHover.get_count();)
      {

         auto pinteraction = m_userinteractionaMouseHover[i];

         //if (pinteraction == m_puserinteractionMouseCapture)
         //{

         // i++;

         //}
         if (!bMouseLeave && pinteraction->_001IsPointInsideInline(pointCursor))
         {

            i++;

         }
         else
         {


            m_userinteractionaMouseHover.erase_at(i);

            ///pinteraction->m_bTrackMouseLeave = false;

            synchronouslock.unlock();

            if (pinteraction != user_interaction())
            {

               pinteraction->message_handler(e_message_mouse_leave);

            }

            synchronouslock._lock();

         }

      }

   }


   //   void window::mouse_hover_step(const __status < ::int_point > & statusPointCursor)
   //   {
   //
   //      decltype(m_uiptraMouseHover) uia;
   //
   //      {
   //
   //         _synchronous_lock synchronouslock(this->synchronization());
   //
   //         if (statusPointCursor.m_estatus != success)
   //         {
   //
   //            uia = ::transfer(m_uiptraMouseHover);
   //
   //         }
   //         else
   //         {
   //
   //            for (::collection::index i = 0; i < m_uiptraMouseHover.get_count();)
   //            {
   //
   //               auto pinteraction = m_uiptraMouseHover[i];
   //
   //               try
   //               {
   //
   //                  if (pinteraction->_001IsPointInside(statusPointCursor))
   //                  {
   //
   //                     i++;
   //
   //                  }
   //                  else
   //                  {
   //
   //                     uia.add(pinteraction);
   //
   //                     m_uiptraMouseHover.erase_at(i);
   //
   //                  }
   //
   //               }
   //               catch (...)
   //               {
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      for (auto & pinteraction : uia)
   //      {
   //
   //         pinteraction->send_message((enum_message)e_message_mouse_leave);
   //
   //      }
   //
   //   }


   bool window::mouse_hover_erase(::user::interaction* pinterface)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      return m_userinteractionaMouseHover.erase(pinterface) >= 0;

   }


   // void window::_on_mouse_move_step(const ::int_point & pointCursor, ::user::enum_layout elayoutChild, bool bMouseLeave)
   // {


   // }


   void window::defer_check_mouse_leave(::user::enum_layout elayoutWindow, ::user::enum_layout elayoutChild)
   {


   }



   void window::_task_transparent_mouse_event()
   {

      //_task_transparent_mouse_event();

   }


   void window::_001OnCaptureChanged(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      m_pacmeuserinteractionMouseCapture.release();

   }


   bool
      window::__windows_message_bypass(::windowing::window* pwindow, unsigned int message, wparam wparam, lparam lparam,
         lresult& lresult)
   {

      return false;

   }


   void window::install_message_routing(::channel* pchannel)
   {

      last_install_message_routing(pchannel);

      ::windowing::window_base::install_message_routing(pchannel);

      user_interaction()->install_message_routing(pchannel);

      //#ifdef WINDOWS

      if (!user_interaction()->m_bMessageOnlyWindow)
      {

         MESSAGE_LINK(e_message_capture_changed, pchannel, this, &window::_001OnCaptureChanged);

      }

      //#endif

      MESSAGE_LINK(e_message_destroy, pchannel, this, &window::on_message_destroy);

      prio_install_message_routing(pchannel);

   }


   void window::default_message_handler(::message::message* pmessage)
   {

      //default_message_handler(pmessage);

   }


   void window::on_message_destroy(::message::message* pmessage)
   {

      if (user_interaction() && ::type(user_interaction()).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

      m_pgraphicsgraphics.defer_destroy();

      __UNREFERENCED_PARAMETER(pmessage);

      {

         auto psync = synchronization();

         _synchronous_lock synchronouslock(this->synchronization());

         m_userinteractionaMouseHover.erase_all();

      }


   }


   //void window::post_non_client_destroy()
   //{

   //   if (::is_set(m_puserthread))
   //   {

   //      auto puserthread = m_puserthread.cast<::user::thread>();

   //      if (puserthread->m_puserinteractionUserThread == user_interaction())
   //      {

   //         puserthread->set_finish();

   //      }

   //      if (::is_set(puserthread))
   //      {

   //         puserthread->m_puserinteractionUserThread.release();

   //      }

   //      if (::is_set(m_puserthread->m_puserinteractionbaseaThread))
   //      {

   //         m_puserthread->m_puserinteractionbaseaThread->erase(user_interaction());

   //      }

   //      m_puserthread.release();

   //   }

   //   string strType = ::type(user_interaction()).name();

   //   m_pplacementlog.release();
   //   m_pparticleChildrenSynchronization.release();
   //   m_pcursor.release();
   //   m_pcopydesk.release();
   //   m_picon.release();
   //   m_pwindowParent.release();
   //   m_pmessagequeue.release();
   //   m_pdisplay.release();

   //   ::channel::destroy();

   //   detach_window();

   //   user_interaction().release();

   //   aaa_m_pacmeuserinteractionKeyboardFocus.release();

   //   m_pacmeuserinteractionKeyboardFocusRequest.release();

   //   m_puserinteractionKeyboardGainingFocusIfAny.release();

   //   m_puserinteractionMouseCapture.release();

   //   m_pacmeuserinteractionToKillKeyboardFocus.release();

   //   m_puserthread.release();

   //   m_pgraphicsgraphics.release();

   //   m_pgraphicsthread.release();

   //   //this->windowing().release();

   //   m_graphicaloutputpurposea.clear();

   //   if (m_pthreadMouseLeave)
   //   {

   //      m_pthreadMouseLeave->set_finish();

   //   }

   //   //m_pthreadMouseLeave.release();

   //   m_messagelist.clear();

   //   m_pelementSoftwareKeyboard.release();

   //   m_pdraw2dgraphics.release();

   //}


   void window::on_final_release()
   {

   }



   //   void window::assert_ok() const
   //   {
   //
   //      ::windowing::window_base::assert_ok();
   //
   //   }
   //
   //
   //   void window::dump(dump_context & dumpcontext) const
   //   {
   //
   //      ::windowing::window_base::dump(dumpcontext);
   //
   //   }




   void window::destroy_impl_only()
   {

      if (!m_bDestroyImplOnly)
      {

         m_bDestroyImplOnly = true;

         m_pgraphicsthread->set_finish();

         if (::is_set(user_interaction()))
         {

            information() << ::type(user_interaction()).name() << "::destroy_impl_only";

            user_interaction()->transfer_handler(this, this);

         }

         //user_interaction()->m_pprimitiveimpl.release();

         //user_interaction()->m_pinteractionimpl.release();

         //user_interaction().release();

         post_message(e_message_destroy_window, 0, 0);

         //return true;

      }
      else if (m_bUserImplCreated)
      {

         if (user_interaction())
         {

            information() << ::type(user_interaction()).name() << "::destroy_impl_only ( 2)";

         }

         m_bUserImplCreated = false;

         //return ::DestroyWindow((HWND)get_handle());
         //return false;

      }
      else
      {

         //return false;

      }

   }
   //
   //
   //    void window::post_non_client_destroy()
   //    {
   //
   //       if (::is_set(m_puserthread))
   //{
   //
   //   auto pthread = m_puserthread.cast<thread>();
   //
   //   if (pthread->m_pimpl == windowing_window())
   //   {
   //
   //      pthread->set_finish();
   //
   //   }
   //
   //   if (::is_set(m_puserthread->m_puserinteractionbaseaThread))
   //   {
   //
   //      m_puserthread->m_puserinteractionbaseaThread->erase(this);
   //
   //   }
   //
   //   m_puserthread.release();
   //
   //}


   //    }

   //void window::start_destroying_window()
   //{

   //   if (has_destroying_flag())
   //   {

   //      //return true;

   //      return;

   //   }

   //   if (!has_destroying_flag())
   //   {

   //      if (m_pgraphicsthread && m_pgraphicsthread->task_active())
   //      {

   //         m_pgraphicsthread->set_finish();

   //      }

   //      set_destroying_flag();

   //      user_interaction()->post_message(e_message_destroy_window);

   //      return;

   //   }

   //   //bool bResult = 
   //   ::windowing::window_base::start_destroying_window();

   //   //return bResult;

   //}


   //void window::destroy_window()
   //{

   //   auto strType = ::type(user_interaction()).name();

   //   if (strType.contains("main_frame"))
   //   {

   //      informationf("main_frame windowing::window::destroy_window");

   //   }

   //   if (!user_interaction()->has_destroying_flag())
   //   {

   //      user_interaction()->set_flag(e_flag_destroying);

   //   }

   //   //user_interaction()->m_ewindowflag -= e_window_flag_window_created;

   //   //::destroy_window(get_handle());

   //   destroy_window();

   //}


   //void window::default_window_procedure(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


   void window::pre_translate_message(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

   }


   //void window::GetWindowText(string & rectangleString)
   //{

   //   __UNREFERENCED_PARAMETER(rectangleString);

   //   throw ::interface_only();

   //}


   //int window::GetChildByIdText(int nID,string & rectangleString) const
   //{

   //   __UNREFERENCED_PARAMETER(nID);

   //   __UNREFERENCED_PARAMETER(rectangleString);

   //   throw ::interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   void window::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
//
//   {
//
//      __UNREFERENCED_PARAMETER(puserinteractionpl);
//
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   void window::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
//   {
//
//      __UNREFERENCED_PARAMETER(puserinteractionpl);
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//#endif


   //void window::PrepareForHelp()
   //{

   //   throw ::interface_only();

   //}


   /*void window::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      __UNREFERENCED_PARAMETER(pcommand);

      throw ::interface_only();

   }*/


   void window::_002OnDraw(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

   }


   void window::do_message_handler(::message::message* pmessage)
   {

      bool bKeyMessage = false;

      ::message::key* pkey = nullptr;

      if (::is_null(user_interaction()))
      {

         return;

      }

      if (user_interaction()->pre_message_handler(pkey, bKeyMessage, pmessage))
      {

         information() << "returning on pre_message_handler";

         return;

      }

      if (pmessage->m_emessage == e_message_timer)
      {

         //m_pthread->step_timer();

      }
      else if (pmessage->m_emessage == e_message_left_button_down)
      {

         informationf("linux::window::e_message_left_button_down");

      }
      else if (pmessage->m_emessage == e_message_left_button_up)
      {

         informationf("linux::window::e_message_left_button_up");

      }
      else if (pmessage->m_emessage == e_message_mouse_move)
      {

         //g_iMouseMove++;

         //informationf("window::message_handler e_message_mouse_move");
         //printf("g_iMouseMove = %d\n", g_iMouseMove);

      }
      else if (pmessage->m_emessage == e_message_paint)
      {

      }
      else if (pmessage->m_emessage == e_message_left_button_up)
      {

         informationf("e_message_left_button_up (0)");

      }

      //      if(::is_set(user_interaction()))
      //      {
      //
      //         user_interaction()->pre_translate_message(pmessage);
      //
      //      }

      //      if(tickDebugmessage_handlerTime.timeout(1))
      //      {
      //
      //         iDebugmessage_handlerTime = 0;
      //
      //      }
      //      else
      //      {
      //
      //         if(iDebugmessage_handlerTime > 20)
      //         {
      //
      //            informationf("window::message handler flooded?\n");
      //
      //         }
      //         else
      //         {
      //
      //            iDebugmessage_handlerTime++;
      //
      //         }
      //
      //      }

      if (user_interaction() != nullptr)
      {

         if (user_interaction()->layout().is_moving())
         {
            //informationf("moving: skip pre translate message");
         }
         else if (user_interaction()->layout().is_sizing())
         {
            //informationf("sizing: skip pre translate message");
         }
         else
         {

            //user_interaction()->pre_translate_message(pmessage);

            //if (pmessage->m_bRet)
            //{

            // return;

            //}

            //pmessage->m_uiMessageFlags |= 1;

         }

      }



      //      if(bKeyMessage)
      //      {
      //
      //         auto psession = session();
      //
      //         auto puser = user();
      //
      //         auto pwindowing = system()->windowing();
      //
      //         ::pointer<::message::key>pkey = pmessage;
      //
      //         //pwindowing->set(pkey, get_oswindow(), m_pwindow, pkey->m_emessage, pkey->m_wparam, pkey->m_lparam);
      //
      ////         if(pmessage->m_emessage == e_message_key_down)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, true);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      ////         else if(pmessage->m_emessage == e_message_key_up)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, false);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      //
      //      }

      pmessage->m_lresult = 0;

      if (pmessage->m_emessage == e_message_mouse_leave)
      {

         _000OnMouseLeave(pmessage);

         return;

      }

      if (pmessage->m_emessage == e_message_left_button_down ||
         pmessage->m_emessage == e_message_left_button_up ||
         pmessage->m_emessage == e_message_middle_button_down ||
         pmessage->m_emessage == e_message_middle_button_up ||
         pmessage->m_emessage == e_message_right_button_down ||
         pmessage->m_emessage == e_message_right_button_up ||
         pmessage->m_emessage == e_message_left_button_double_click ||
         pmessage->m_emessage == e_message_mouse_move ||
         pmessage->m_emessage == e_message_mouse_wheel)
      {

         ::pointer<::message::mouse> pmouse = pmessage;

         //information() << "msghdl pwnd : " << (::iptr) pmouse->m_pwindow.m_p;

         on_mouse_message(pmouse);

         return;

      }
      /*      else if(pmessage->m_emessage == e_message_key_down ||
                    pmessage->m_emessage == e_message_key_up ||
                    pmessage->m_emessage == e_message_char)*/
      else if (bKeyMessage)
      {

         if (::is_set(pkey))
         {

            information() << "key message";

            ::pointer<::user::interaction> puiKeyboardFocus = m_pacmeuserinteractionKeyboardFocus;

            if (puiKeyboardFocus)
            {

               information() << "key message control with keyboard focus : " << ::string(::type(puiKeyboardFocus.m_p));

               puiKeyboardFocus->route_message(pkey);

            }
            else
            {

               user_interaction()->route_message(pkey);

            }

         }

         if (pmessage->m_bRet)
         {

            return;

         }

         default_window_procedure(pmessage);

         return;

      }

      if (pmessage->m_emessage == e_message_subject)
      {

         if (user_interaction() != nullptr)
         {

            user_interaction()->handle((::topic*)pmessage->m_lparam.m_lparam, nullptr);

         }
         //         else
         //         {
         //
         //            on_control_event((::user::control_event *) pmessage->m_lparam.m_lparam);
         //
         //         }

         return;

      }

      if (::is_set(user_interaction()))
      {

         user_interaction()->route_message(pmessage);

      }
      else
      {

         route_message(pmessage);

      }

      if (!pmessage->m_bRet)
      {

         default_window_procedure(pmessage);

      }

      if (pmessage->m_emessage == e_message_create)
      {

         //if (user_interaction()->m_procedureOnAfterCreate)
         //{

         //   user_interaction()->post_message(e_message_after_create);

         //}

//         if(has_screen_output_purpose())
//         {
//
//            user_interaction()->set_need_layout();
//
//            user_interaction()->set_need_redraw();
//
//            user_interaction()->post_redraw();
//
//         }

         //if(user_interaction()->m_setneedredrawa.has_element())
         //{

         //   user_interaction()->post_redraw();

         //}

      }

   }


   void window::_message_handler(::message::message* pmessage)
   {

      auto puserinteraction = user_interaction();

      if (puserinteraction)
      {

         m_bDestroyImplOnly ? route_message(pmessage) : puserinteraction->route_message(pmessage);

      }

   }


   void window::default_window_procedure(::message::message* pmessage)
   {

   }


   bool window::on_mouse_message(::message::mouse* pmouse)
   {

      m_pointCursor2 = pmouse->m_pointHost;

      if (pmouse->m_emessage == e_message_left_button_double_click)
      {

         information() << "e_message_left_button_double_click";

      }
      else if (pmouse->m_emessage == e_message_left_button_down)
      {

         information() << "e_message_left_button_down";

      }
      else if (pmouse->m_emessage == e_message_mouse_move)
      {

         //information() << "e_message_mouse_move : " << pmouse->m_pointAbsolute;

      }
      else if (pmouse->m_emessage == e_message_left_button_up)
      {

         information() << "e_message_left_button_up";

      }

      if (::is_set(user_interaction()) && !user_interaction()->m_bUserElementOk)
      {

         return false;

      }

      auto psession = session();

      //if (pmouse)
      //{

      if (psession != nullptr)
      {

         psession->on_ui_mouse_message(pmouse);

         psession->m_pointCursor = pmouse->m_pointAbsolute;

      }

      //         if(user_interaction() != nullptr && user_interaction()->session()  != nullptr && user_interaction()->session() != get_session())
      //         {
      //
      //            auto psystem = system();
      //
      //            auto psession = psystem->node();
      //
      //            psession->m_pointCursor = pmouse->m_point;
      //
      //         }


      //   if (m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
      //   {
      //      pmouse->m_bTranslated = true;
      //      ::int_rectangle rectWindow;
      //      //            if(m_bScreenRelativeMouseMessagePosition)
      //      //            {
      //      //
      //      //               INFO("Screen Relative Mouse Message Position");
      //      //
      //      //               ::int_rectangle rectWindow32;
      //      //
      //      //               ::window_rectangle((oswindow) get_handle(), &rectWindow32);
      //      //
      //      //               ::copy(rectWindow, rectWindow32);
      //      //
      //      //            }
      //      //            else
      //      {
      //         user_interaction()->window_rectangle(rectWindow);
      //      }

      //      //auto pwindowing = windowing();

      //      //auto pdisplay = pwindowing->display();

      //      //if (pdisplay->get_monitor_count() > 0)
      //      //{

      //      //   ::int_rectangle rcMonitor;

      //      //   pdisplay->get_monitor_rectangle(0, rcMonitor);

      //      //   if (rectWindow.left() >= rcMonitor.left())
      //      //   {

      //      //      pmouse->m_point.x() += (int)rcMonitor.left();

      //      //   }

      //      //   if (rectWindow.top() >= rcMonitor.top())
      //      //   {

      //      //      //pmouse->m_point.y() += (int)rectWindow.top();
      //      //      pmouse->m_point.y() += (int)rcMonitor.top();

      //      //   }

      //      //}
      //      //else
      //      {

      //         if (rectWindow.left() >= 0)
      //         {

      //            pmouse->m_point.x() += (int)rectWindow.left();

      //         }

      //         if (rectWindow.top() >= 0)
      //         {

      //            pmouse->m_point.y() += (int)rectWindow.top();

      //         }

      //      }

      //   }

      //}

      auto pwindowing = windowing();

      pwindowing->set(pmouse, oswindow(), this, pmouse->m_emessage, pmouse->m_wparam, pmouse->m_lparam);

      //information() << "omousemsg pwnd : " << (::iptr) pmouse->m_pwindow.m_p;

      if (pmouse->m_emessage == e_message_mouse_move)
      {

         // We are at the message handler routine.
         // mouse messages originated from message handler and that are mouse transfer happenings should end up with the correct cursor.
         // So the routine starts by setting to the default cursor,
         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
         // handler has set it to another one.

         //user_interaction()->_on_mouse_move_step(pmouse->m_pointHost);

         _on_mouse_move_step(pmouse->m_pointHost, false);

         //information() << "e_message_mouse_move (2): " << pmouse->m_pointAbsolute;

      }



      //_008OnMouse(pmouse);

      ::user::interaction* puserinteractionMouse = nullptr;

      //if (m_puserinteractionMouseCapture)
      //{

      //   //            if(g_puserinteractionMouseCapture123 == nullptr)
      //   //            {
      //   //
      //   //               g_puserinteractionMouseCapture123 = m_puserinteractionCapture;
      //   //
      //   //            }
      //   //            else if(g_puserinteractionMouseCapture123 != m_puserinteractionCapture)
      //   //            {
      //   //
      //   //               informationf("different capture (1)");
      //   //
      //   //            }

      //   puserinteractionMouse = m_puserinteractionMouseCapture;

      //}

      //         if(g_puserinteractionMouseCapture123 != nullptr)
      //         {
      //
      //            if(g_puserinteractionMouseCapture123 != puserinteractionMouse)
      //            {
      //
      //               informationf("different capture (2)");
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //
      //
      //         }

      if (pmouse->m_emessage == e_message_left_button_down)
      {


         informationf("left_button_down (A)");

      }

      pmouse->m_puserinteractionHit = user_interaction()->child_from_point(pmouse->m_pointHost);

      if (!puserinteractionMouse)
      {

         puserinteractionMouse = pmouse->m_puserinteractionHit;

      }

      if (pmouse->m_emessage == e_message_left_button_down)
      {


         informationf("left_button_down");

      }
      else if (pmouse->m_emessage == e_message_left_button_up)
      {


         informationf("left_button_up");

      }

      if (m_pacmeuserinteractionMouseCapture)
      {

         //::string strType = ::type(m_puserinteractionMouseCapture).name();

         //information() << "on_mouse_message CAPTURED to object of type : " << strType;

         //information() << "omousemsg pwnd (B) : " << (::iptr) pmouse->m_pwindow.m_p;

         ::cast < ::user::interaction > puserinteractionMouseCapture = m_pacmeuserinteractionMouseCapture;

         if (puserinteractionMouseCapture)
         {

            puserinteractionMouseCapture->route_as_parent_mouse_message(pmouse);

            //information() << "on_mouse_message (capture): " << pmouse->m_pointAbsolute;

            if (!pmouse->m_bRet && puserinteractionMouseCapture)
            {

               puserinteractionMouseCapture->on_child_from_point_mouse_message_routing(pmouse);

            }

         }

      }
      else
      {

         //::string strType = ::type(user_interaction()).name();

         //information() << "on_mouse_message type : " << strType;

         //information() << "omousemsg this (F) : " << (::iptr) (::user::message *)pmouse;
         //information() << "omousemsg pwnd (F) : " << (::iptr) pmouse->m_pwindow.m_p;

         user_interaction()->on_mouse_message(pmouse);

         //information() << "omousemsg this (Q) : " << (::iptr) (::user::message *)pmouse;
         //information() << "omousemsg pwnd (Q) : " << (::iptr) pmouse->m_pwindow.m_p;

      }

      //         string strUserInteractionType(::is_null(puserinteractionMouse) ? "(null)" : ::type(puserinteractionMouse).name());
      //
      //         if(pmouse->m_emessage == e_message_mouse_move)
      //         {
      //
      //            static int s_iMotionNotify = 0;
      //
      //            s_iMotionNotify++;
      //
      //            if (strUserInteractionType.case_insensitive_contains("button"))
      //            {
      //
      //               informationf("mouse_move::userinteraction=button");
      //
      //            }
      //            else
      //            {
      //
      //
      //               puserinteractionMouse = user_interaction()->child_from_point(pmouse->m_point);
      //
      //
      //
      //            }
      //
      //         }

      //if (puserinteractionMouse)
      //{

      //   //            if(pmouse->m_emessage == ::e_message_left_button_double_click && puserinteractionMouse->m_bEatsDoubleClick)
      //   //            {
      //   //
      //   //               pmouse->m_bRet = true;
      //   //
      //   //               return;
      //   //
      //   //            }

      //   auto puserinteractionItem = puserinteractionMouse;

      //   do
      //   {

      //      puserinteractionItem->route_message(pmouse);

      //      if (pmouse->m_bRet)
      //      {

      //         break;

      //      }

      //      puserinteractionItem = puserinteractionItem->get_parent();

      //   } while (puserinteractionItem != nullptr);

      //}

      auto pwindow = pmouse->m_pwindow;

      //auto pwindowimpl = pwindow->m_pwindow;

      if (::is_set(pwindow))
      {

         if (pmouse->m_emessage == e_message_left_button_up)
         {
            if (::is_set(pwindow->m_puiLastLButtonDown))
            {

               pwindow->m_puiLastLButtonDown = nullptr;

            }

            if (::is_set(pwindow->m_pitemLButtonDown))
            {

               pwindow->m_pitemLButtonDown = nullptr;

            }
         }

         pwindow->final_mouse_message_handling(pmouse);



      }

      return true;

      //      if (pmouse->m_emessage == e_message_left_button_down)
      //      {
      //
      //         informationf("e_message_left_button_down");
      //
      //         string strType = ::type(user_interaction()).name();
      //
      //         if (strType.case_insensitive_contains("list_box"))
      //         {
      //
      //            informationf("list_box e_message_left_button_down");
      //
      //         }
      //
      //      }
      //      else if (pmouse->m_emessage == e_message_left_button_up)
      //      {
      //
      //         informationf("e_message_left_button_up");
      //
      //      }
      //      else if (pmouse->m_emessage == e_message_non_client_left_button_up)
      //      {
      //
      //         informationf("e_message_non_client_left_button_up");
      //
      //      }
      //      else if (pmouse->m_emessage == e_message_non_client_left_button_down)
      //      {
      //
      //         informationf("e_message_non_client_left_button_down");
      //
      //         string strType;
      //
      //         if (strType.case_insensitive_contains("list_box"))
      //         {
      //
      //            informationf("list_box e_message_non_client_left_button_down");
      //
      //         }
      //
      //      }
      //
      //      auto psession = session();
      //
      //      if (psession)
      //      {
      //
      //         psession->on_ui_mouse_message(pmouse);
      //
      //      }
      //
      //      if (pmouse->m_emessage == e_message_mouse_move)
      //      {
      //         string strType = ::type(user_interaction()).name();
      //
      //         // We are at the message handler procedure.
      //         // mouse messages originated from message handler and that are mouse transfer happenings should end up with the correct cursor.
      //         // So the procedure starts by setting to the default cursor,
      //         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
      //         // handler has set it to another one.
      //         auto pwindowing = windowing();
      //         auto pcursor = pwindowing->get_cursor(e_cursor_default);
      //
      //         pmouse->m_pcursor = pcursor;
      //
      //         //informationf("windows::e_message_mouse_move(%d,%d)", pmouse->m_point.x(), pmouse->m_point.y());
      //
      //         //string strType;
      //
      //         if (user_interaction())
      //         {
      //
      //            strType = ::type(user_interaction()).name();
      //
      //            if (strType.case_insensitive_contains("list_box"))
      //            {
      //
      //               //informationf("list_box e_message_mouse_move");
      //
      //            }
      //
      //         }
      //
      //      }
      //      else if (pmouse->m_emessage == e_message_non_client_mouse_move)
      //      {
      //         // We are at the message handler procedure.
      //         // mouse messages originated from message handler and that are mouse transfer happenings should end up with the correct cursor.
      //         // So the procedure starts by setting to the default cursor,
      //         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
      //         // handler has set it to another one.
      //         auto pwindowing = windowing();
      //         auto pcursor = pwindowing->get_cursor(e_cursor_default);
      //
      //         pmouse->m_pcursor = pcursor;
      //
      //      }
      //
      //      _on_mouse_move_step(pmouse->m_point);
      //
      //      auto puserinteractionMouseCapture = m_puserinteractionMouseCapture;
      //
      //      if (::is_set(puserinteractionMouseCapture))
      //      {
      //
      //         ::string strType = ::type(puserinteractionMouseCapture).name();
      //
      //         information() << "on_mouse_message capture type : " << strType;
      //
      //         puserinteractionMouseCapture->route_message(pmouse);
      //
      //         return true;
      //
      //      }
      //
      //      //auto pchild = user_interaction()->child_from_point(pmouse->m_point);
      //
      //      //if (pchild)
      //      //{
      //
      //      //   string strType = ::type(pchild).name();
      //
      //      //   if (strType.case_insensitive_contains("button"))
      //      //   {
      //
      //      //      informationf("mouse transfer on button");
      //
      //      //   }
      //      //   else if (strType.case_insensitive_contains("tab"))
      //      //   {
      //
      //      //      informationf("mouse transfer on tab");
      //
      //      //   }
      //
      //      //   auto puserinteraction = pchild;
      //
      //      //   ::user::interaction_array interactionaHandled;
      //
      //      //   while (::is_set(puserinteraction))
      //      //   {
      //
      //      //      puserinteraction->route_message(pmouse);
      //
      //      //      interactionaHandled.add_interaction(puserinteraction);
      //
      //      //      if (pmouse->m_bRet)
      //      //      {
      //
      //      //         break;
      //
      //      //      }
      //
      //      //      puserinteraction = puserinteraction->get_parent();
      //
      //      //      if (::is_set(puserinteraction))
      //      //      {
      //
      //      //         auto pchild = puserinteraction->child_from_point(pmouse->m_point, -1, &interactionaHandled);
      //
      //      //         if (::is_set(pchild))
      //      //         {
      //
      //      //            pchild->route_message(pmouse);
      //
      //      //            if (pmouse->m_bRet)
      //      //            {
      //
      //      //               break;
      //
      //      //            }
      //
      //      //         }
      //
      //      //      }
      //
      //      //   }
      //
      //      //}
      //      //else
      //      //{
      //
      //      //   user_interaction()->route_message(pmouse);
      //
      //      //}
      //
      //
      //      user_interaction()->on_mouse_message(pmouse);
      //
      //      //if (pchild)
      //      //{
      //
      //      //   string strType = ::type(pchild).name();
      //
      //      //   if (strType.case_insensitive_contains("button"))
      //      //   {
      //
      //      //      informationf("mouse transfer on button");
      //
      //      //   }
      //      //   else if (strType.case_insensitive_contains("tab"))
      //      //   {
      //
      //      //      informationf("mouse transfer on tab");
      //
      //      //   }
      //
      //      //   auto puserinteraction = pchild;
      //
      //      //   ::user::interaction_array interactionaHandled;
      //
      //      //   while (::is_set(puserinteraction))
      //      //   {
      //
      //      //      puserinteraction->route_message(pmouse);
      //
      //      //      interactionaHandled.add_interaction(puserinteraction);
      //
      //      //      if (pmouse->m_bRet)
      //      //      {
      //
      //      //         break;
      //
      //      //      }
      //
      //      //      puserinteraction = puserinteraction->get_parent();
      //
      //      //      if (::is_set(puserinteraction))
      //      //      {
      //
      //      //         auto pchild = puserinteraction->child_from_point(pmouse->m_point, -1, &interactionaHandled);
      //
      //      //         if (::is_set(pchild))
      //      //         {
      //
      //      //            pchild->route_message(pmouse);
      //
      //      //            if (pmouse->m_bRet)
      //      //            {
      //
      //      //               break;
      //
      //      //            }
      //
      //      //         }
      //
      //      //      }
      //
      //      //   }
      //
      //      //}
      //      //else
      //      //{
      //
      //      //   user_interaction()->route_message(pmouse);
      //
      //      //}
      //
      //      return true;

   }


   bool window::IsTopParentActive()
   {

      return is_active_window();

      //return false;

   }


   void window::ActivateTopParent()
   {

      throw ::interface_only();

   }


   //int window::message_box(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrCaption,unsigned int nType)

   //{
   //   __UNREFERENCED_PARAMETER(scopedstrText);

   //   __UNREFERENCED_PARAMETER(scopedstrCaption);

   //   __UNREFERENCED_PARAMETER(nType);
   //   throw ::interface_only();

   //   return 0;
   //}

   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for interaction_impl functions
   //    only works for derived class (eg: ::user::impact) that override 'GetScrollBarCtrl'
   // if the interaction_impl doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID

   /*   CScrollBar* window::GetScrollBarCtrl(int) const
   {
   throw ::interface_only();
   }*/

   //int window::SetScrollPos(int nBar,int nPos,bool bRedraw)
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(nPos);
   //   __UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();

   //   return 0;
   //}

   //int window::GetScrollPos(int nBar) const
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   throw ::interface_only();

   //   return 0;
   //}

   //void window::SetScrollRange(int nBar,int nMinPos,int nMaxPos,bool bRedraw)
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(nMinPos);
   //   __UNREFERENCED_PARAMETER(nMaxPos);
   //   __UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();


   //}


   //void window::GetScrollRange(int nBar,LPINT pMinPos,LPINT pMaxPos) const

   //{

   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(pMinPos);
   //   __UNREFERENCED_PARAMETER(pMaxPos);

   //   throw ::interface_only();

   //}


   //// Turn on/off non-control scrollbars
   ////   for WS_?SCROLL scrollbars - show/hide them
   ////   for control scrollbar - enable/disable them
   //void window::EnableScrollBarCtrl(int nBar,bool bEnable)
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(bEnable);
   //   throw ::interface_only();
   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   void window::SetScrollInfo(int nBar,LPSCROLLINFO pScrollInfo,bool bRedraw)
//
//   {
//
//      __UNREFERENCED_PARAMETER(nBar);
//      __UNREFERENCED_PARAMETER(pScrollInfo);
//
//      __UNREFERENCED_PARAMETER(bRedraw);
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   void window::GetScrollInfo(int nBar,LPSCROLLINFO pScrollInfo,unsigned int nMask)
//
//   {
//
//      __UNREFERENCED_PARAMETER(nBar);
//      __UNREFERENCED_PARAMETER(pScrollInfo);
//
//      __UNREFERENCED_PARAMETER(nMask);
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//#endif


   //int window::GetScrollLimit(int nBar)
   //{
   //   
   //   __UNREFERENCED_PARAMETER(nBar);
   //   
   //   throw ::interface_only();

   //   return 0;

   //}


   //void window::ScrollWindow(int xAmount,int yAmount, const ::int_rectangle * pcrect, const ::int_rectangle * pcrectClip)
   //{

   //   __UNREFERENCED_PARAMETER(xAmount);
   //   __UNREFERENCED_PARAMETER(yAmount);
   //   __UNREFERENCED_PARAMETER(pcrect);
   //   __UNREFERENCED_PARAMETER(pcrectClip);

   //   throw ::interface_only();

   //}


   //void window::CalcWindowRect(::int_rectangle * pClientRect,unsigned int nAdjustType)
   //{

   //   __UNREFERENCED_PARAMETER(pClientRect);
   //   __UNREFERENCED_PARAMETER(nAdjustType);

   //   throw ::interface_only();

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool window::HandleFloatingSysCommand(unsigned int nID, lparam lParam)
   {

      __UNREFERENCED_PARAMETER(nID);
      __UNREFERENCED_PARAMETER(lParam);

      throw ::interface_only();

      return false;

   }


   bool window::OnChildNotify(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

      return false;

   }


   bool window::ReflectChildNotify(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

      return false;

   }


   //   void window::OnParentNotify(const ::atom & atom,lparam lParam)
   //   {
   //      __UNREFERENCED_PARAMETER(message);
   //      __UNREFERENCED_PARAMETER(lParam);
   //      throw ::interface_only();
   //   }
   //
   //   void window::OnSetFocus(::windowing::window *)
   //   {
   //      throw ::interface_only();
   //   }
   //
   //   lresult window::OnActivateTopLevel(wparam wParam,lparam)
   //   {
   //      __UNREFERENCED_PARAMETER(wParam);
   //      throw ::interface_only();
   //   }
   //
   //   void window::OnSysColorChange()
   //   {
   //      throw ::interface_only();
   //   }
   //
   //   void window::OnSettingChange(unsigned int uFlags, const ::scoped_string & scopedstrSection)

   //   {
   //      __UNREFERENCED_PARAMETER(uFlags);
   //      __UNREFERENCED_PARAMETER(scopedstrSection);

   //      throw ::interface_only();
   //   }
   //
   //#ifdef WINDOWS
   //   void window::OnDevModeChange(__in char * pDeviceName)

   //   {
   //      __UNREFERENCED_PARAMETER(pDeviceName);

   //      throw ::interface_only();
   //   }
   //
   //#ifdef WINDOWS_DESKTOP
   //   void window::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   //   {
   //      throw ::interface_only();
   //   }
   //#endif
   //#endif
   //
   //   lresult window::OnDisplayChange(wparam,lparam)
   //   {
   //      //   throw ::interface_only();
   //
   //      return 0;
   //
   //   }
   //
   //   lresult window::OnDragList(wparam,lparam lParam)
   //   {
   //      __UNREFERENCED_PARAMETER(lParam);
   //      throw ::interface_only();
   //   }

   /*   void window::OnHScroll(unsigned int, unsigned int, CScrollBar* pScrollBar)
   {
   __UNREFERENCED_PARAMETER(pScrollBar);
   throw ::interface_only();
   }

   void window::OnVScroll(unsigned int, unsigned int, CScrollBar* pScrollBar)
   {
   __UNREFERENCED_PARAMETER(pScrollBar);
   throw ::interface_only();
   }
   */

   void window::_001OnDeferPaintLayeredWindowBackground(::image::image* pimage)
   {
      __UNREFERENCED_PARAMETER(pimage);
      throw ::interface_only();
   }

   void window::_001DeferPaintLayeredWindowBackground(::image::image* pimage)
   {
      __UNREFERENCED_PARAMETER(pimage);
      throw ::interface_only();
   }

   void window::_001OnPaint(::message::message* pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      throw ::interface_only();
   }

   void window::_001OnPrint(::message::message* pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      throw ::interface_only();
   }

   //void window::OnEnterIdle(unsigned int /*nWhy*/,::windowing::window * /*pWho*/)
   //{
   //   throw ::interface_only();
   //}

   //void * window::OnCtlColor(::draw2d::graphics *,::windowing::window * pwindow,unsigned int)
   //{
   //   __UNREFERENCED_PARAMETER(pwindow);
   //   throw ::interface_only();
   //}


   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support

   void window::update_data(bool bSaveAndValidate)
   {

      __UNREFERENCED_PARAMETER(bSaveAndValidate);

      throw ::interface_only();

      //return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child interaction_impl)

   void window::CenterWindow(::user::interaction* pAlternateOwner)
   {

      __UNREFERENCED_PARAMETER(pAlternateOwner);

      throw ::interface_only();

   }


   //void window::CheckAutoCenter()
   //{
   //   throw ::interface_only();

   //   return false;

   //}

//   /////////////////////////////////////////////////////////////////////////////
//   // Dialog initialization support
//
//   void window::ExecuteDlgInit(const ::scoped_string & scopedstrResourceName)
//
//   {
//      __UNREFERENCED_PARAMETER(scopedstrResourceName);
//
//      throw ::interface_only();
//
//      return false;
//
//   }

//   void window::ExecuteDlgInit(LPVOID pResource)
//
//   {
//      __UNREFERENCED_PARAMETER(pResource);
//
//      throw ::interface_only();
//
//      return false;
//
//   }

   void window::UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler)
   {
      __UNREFERENCED_PARAMETER(pTarget);
      __UNREFERENCED_PARAMETER(bDisableIfNoHndler);

      throw ::interface_only();

   }



   //void window::subclass_window(::windowing::window * pwindow)
   //{
   //   __UNREFERENCED_PARAMETER(oswindow);
   //   throw ::interface_only();

   //   return false;

   //}

   //void window::SubclassDlgItem(unsigned int nID,::windowing::window * pParent)
   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pParent);
   //   throw ::interface_only();

   //   return false;

   //}

   //oswindow window::unsubclass_window()
   //{
   //   throw ::interface_only();
   //   return nullptr;
   //}

   //void window::IsChild(::user::interaction * pinteraction) const
   //{
   //   __UNREFERENCED_PARAMETER(pinteraction);
   //   throw ::interface_only();

   //   return false;

   //}


   //bool window::_is_window()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //atom window::SetDlgCtrlId(atom atom)
   //{

   //   __UNREFERENCED_PARAMETER(atom);

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom window::GetDlgCtrlId() const
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   // void window::SetWindowDisplayChanged()
   // {

   //    if (user_interaction()->is_this_visible() && user_interaction()->window_state3().m_edisplay3 != ::e_display_iconic)
   //    {

   //       if (user_interaction()->get_parent() == nullptr)
   //       {

   //          user_interaction()->check_transparent_mouse_events();

   //       }

   //    }
   //    else
   //    {

   //       //stop_fps_interest();
   //       //child_post_quit("fps_interest");

   //    }

   // }


   //void window::layout().is_iconic()
   //{

   //   //throw ::interface_only();

   //   return false;

   //}


   //void window::IsZoomed()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::interaction * window::get_parent() const
   //{

   //   return nullptr;

   //}


//   int window::get_window_long(int nIndex) const
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return (int) ::GetWindowLongPtr(get_handle(), nIndex);
//
//#else
//
//      return (int) get_window_long_ptr(nIndex);
//
//#endif
//
//   }


//   int window::set_window_long(int nIndex,int lValue)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return (int) ::SetWindowLongPtr(get_handle(), nIndex, lValue);
//
//#else
//
//      return (int) set_window_long_ptr(nIndex, lValue);
//
//#endif
//
//   }


//   iptr window::get_window_long_ptr(int nIndex) const
//   {
//
//      return get_window_long_ptr(nIndex);
//
//   }
//
//
//   iptr window::set_window_long_ptr(int nIndex, iptr lValue)
//   {
//
//      return set_window_long_ptr(nIndex, lValue);
//
//   }


   //void window::ReleaseCapture()
   //{

   //   auto psession = session();

   //   auto pwindowing = psession->windowing();

   //   pwindowing->release_mouse_capture();

   //   psession->m_puiCapture = nullptr;

   //   return true;

   //}


   //::user::interaction * window::get_capture()
   //{

   //   if (!has_mouse_capture())
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteractionCapture;

   //}


   //void window::SetCapture(::user::interaction * pinteraction)
   //{

   //   if (pinteraction == nullptr)
   //   {

   //      pinteraction = user_interaction();

   //   }

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   oswindow w = ::set_mouse_capture(get_handle());

   //   informationf("\nSet Capture: oswindow=0x" + ::hex::lower_from((iptr) w));

   //   auto psession = session();

   //   psession->m_puiCapture = pinteraction;

   //   return true;

   //}


   //// interaction_impl
   ///* window::operator oswindow() const
   //{ return this == nullptr ? nullptr : get_handle(); }*/
   //void window::operator==(const interaction_impl& wnd) const
   //{
   //   __UNREFERENCED_PARAMETER(wnd);
   //   throw ::interface_only();
   //   return false;
   //}

   //void window::operator!=(const interaction_impl& wnd) const
   //{
   //   __UNREFERENCED_PARAMETER(wnd);
   //   throw ::interface_only();
   //   return false;
   //}


   //unsigned int window::GetStyle() const
   //{

   //   return ::windowing::window_base::GetStyle();

   //}


   //unsigned int window::GetExStyle() const
   //{

   //   return ::windowing::window_base::GetExStyle();

   //}


   //void window::ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   unsigned int dw = get_window_long(GWL_STYLE);

   //   dw &= ~dwRemove;

   //   dw |= dwAdd;

   //   set_window_long(GWL_STYLE, dw);

   //   return false;

   //}


   //void window::ModifyStyleEx(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags)
   //{

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   unsigned int dw = get_window_long(GWL_EXSTYLE);

   //   dw &= ~dwRemove;

   //   dw |= dwAdd;

   //   set_window_long(GWL_EXSTYLE, dw);

   //   return false;

   //}


   ::user::interaction_base* window::set_owner(::user::interaction_base* pprimitiveOwner)
   {

      __UNREFERENCED_PARAMETER(pprimitiveOwner);

      //throw ::interface_only();

      return nullptr;

   }


   lresult window::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point& point)
   {

      auto pmessage = user_interaction()->get_message(emessage, wparam, lparam);

      auto lresult = send_message(pmessage);

      return lresult;

   }


   lresult window::send_message(::message::message* pmessage)
   {

      user_interaction()->on_message(pmessage);

      return pmessage->m_lresult;

   }


   //#ifdef LINUX
   //
   //
   //   lresult window::send_x11_event(void * phappening)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(phappening);
   //
   //      throw ::interface_only();
   //
   //      return 0;
   //
   //   }
   //
   //
   //#endif


//   void window::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
//   {
//
//      if (!user_interaction())
//      {
//
//         //return false;
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      if (!m_puserthread)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//#ifdef REPORT_OFFSET
//
//      printf("(14) m_pwindow.m_p (0x%x)\n", m_pwindow.m_p);
//      printf("(14) m_pwindow.m_pelement (0x%x)\n", m_pwindow.m_pelement);
//      printf("(14) offset of m_pImpl2 in ::windowing::window = %d\n", offsetof(::windowing::window, m_pImpl2));
//      printf("(14) offset of m_timeLastExposureAddUp in ::windowing::window = %d\n", offsetof(::windowing::window, m_timeLastExposureAddUp));
//      printf("(14) offset of m_strBitmapSource in ::windowing::window = %d\n", offsetof(::windowing::window, m_strBitmapSource));
//      printf("(14) offset of m_bCursorRedraw in ::windowing::window = %d\n", offsetof(::windowing::window, m_bCursorRedraw));
//      printf("(14) offset of m_bLockWindowUpdate in ::windowing::window = %d\n", offsetof(::windowing::window, m_bLockWindowUpdate));
//      printf("(14) offset of m_bOkToUpdateScreen in ::windowing::window = %d\n", offsetof(::windowing::window, m_bOkToUpdateScreen));
//      printf("(14) offset of m_sizeDrawn in ::windowing::window = %d\n", offsetof(::windowing::window, m_sizeDrawn));
//      printf("(14) offset of m_pthreadMouseLeave in ::windowing::window = %d\n", offsetof(::windowing::window, m_pthreadMouseLeave));
//      printf("(14) offset of m_bPointInside in ::windowing::window = %d\n", offsetof(::windowing::window, m_bPointInside));
//      printf("(14) offset of m_pwindow in ::windowing::window = %d\n", offsetof(::windowing::window, m_pwindow));
//
//#endif
//
//      //auto pwindow = m_pwindow;
//
//      //if (!pwindow)
//      //{
//
//      //   throw ::exception(error_wrong_state);
//
//      //}
//
//      auto oswindow = this->oswindow();
//
//      if (!oswindow)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      auto puserinteraction = user_interaction();
//
//      auto pthread = m_puserthread;
//
//      if (atom == e_message_redraw)
//      {
//
//         if (m_pgraphicsthread)
//         {
//
//            //puserinteraction->graphics_thread_redraw(wParam & 1);
//
//            m_pgraphicsthread->post_redraw();
//
//            return;
//
//         }
//
//      }
//
//      MESSAGE message = {};
//
//      message.oswindow = oswindow;
//
//      message.m_emessage = atom;
//
//      message.wParam = wParam;
//
//      message.lParam = lParam;
//
//      auto pmessagequeue = pthread->get_message_queue();
//
//      if (::is_null(pmessagequeue))
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      //auto estatus = 
//      pmessagequeue->post_message(message);
//
//      //return estatus;
//
//   }


   //void window::DragDetect(const ::int_point & point) const
   //{
   //   __UNREFERENCED_PARAMETER(point);
   //   throw ::interface_only();
   //   return false;
   //}


   void window::on_set_window_text()
   {

      //auto pwindow = m_pwindow;

      //if (pwindow)
      //{

      ::string strWindowText = user_interaction()->get_window_text();

      set_window_text(strWindowText);

      //       }

   }


   //   void window::set_window_text(const ::scoped_string & scopedstrString)
   //
   //   {
   //
   //      __UNREFERENCED_PARAMETER(scopedstrString);
   //
   //
   //      throw ::interface_only();
   //
   //   }


   //character_count window::GetWindowText(char * pszString,int nMaxCount)
   //{

   //   __UNREFERENCED_PARAMETER(scopedstrString);
   //   __UNREFERENCED_PARAMETER(nMaxCount);
   //   throw ::interface_only();

   //   return 0;
   //}


   //character_count window::GetWindowTextLength()
   //{

   //   throw ::interface_only();
   //   return 0;

   //}


   //void window::DragAcceptFiles(bool bAccept)
   //{

   //   __UNREFERENCED_PARAMETER(bAccept);

   //   throw ::interface_only();

   //}


   bool window::window_is_iconic()
   {

      if (!user_interaction())
      {

         return false;

      }

      return user_interaction()->const_layout().sketch().display() == ::e_display_iconic;

   }


   bool window::window_is_zoomed()
   {

      if (!user_interaction())
      {

         return false;

      }

      return user_interaction()->const_layout().sketch().display() == ::e_display_zoomed;

   }


   //unsigned int window::ArrangeIconicWindows()
   //{

   //   throw ::interface_only();

   //   return 0;

   //}


   void
      window::MapWindowPoints(::windowing::window* puserinteractionTo, ::int_point* pPoint, unsigned int nCount)
   {

      __UNREFERENCED_PARAMETER(puserinteractionTo);
      __UNREFERENCED_PARAMETER(pPoint);
      __UNREFERENCED_PARAMETER(nCount);

      throw ::interface_only();

   }


   void window::MapWindowPoints(::windowing::window* puserinteractionTo, ::int_rectangle* prectangle)
   {
      __UNREFERENCED_PARAMETER(puserinteractionTo);
      __UNREFERENCED_PARAMETER(prectangle);

      throw ::interface_only();
   }

   //void window::UpdateWindow()
   //{
   //   throw ::interface_only();
   //}

   //void window::SetRedraw(bool bRedraw)
   //{
   //   __UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();
   //}

   //void window::GetUpdateRect(::int_rectangle * prectangle,bool bErase)

   //{
   //   __UNREFERENCED_PARAMETER(prectangle);

   //   __UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();

   //   return false;
   //}

   //int window::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{
   //   __UNREFERENCED_PARAMETER(pRgn);
   //   __UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();

   //   return 0;
   //}


   //void window::Invalidate(bool bErase)
   //{

   //   __UNREFERENCED_PARAMETER(bErase);

   //   throw ::interface_only();

   //}


   //void window::InvalidateRect(const ::int_rectangle & rectangle, bool bErase)
   //{

   //   __UNREFERENCED_PARAMETER(rectangle);
   //   __UNREFERENCED_PARAMETER(bErase);

   //   throw ::interface_only();

   //}


   //void window::InvalidateRgn(::draw2d::region * pRgn, bool bErase)
   //{
   //   __UNREFERENCED_PARAMETER(pRgn);
   //   __UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();
   //}


   //void window::ValidateRect(const ::int_rectangle & rectangle)
   //{

   //   __UNREFERENCED_PARAMETER(rectangle);

   //   throw ::interface_only();

   //}


   //void window::ValidateRgn(::draw2d::region * pRgn)
   //{

   //   __UNREFERENCED_PARAMETER(pRgn);

   //   throw ::interface_only();

   //}


   ////void window::_is_window_visible()
   ////{

   ////   throw ::interface_only();

   ////   return false;

   ////}


   //void window::ShowOwnedPopups(bool bShow)
   //{
   //   __UNREFERENCED_PARAMETER(bShow);
   //   throw ::interface_only();
   //}


   /*::draw2d::graphics * window::GetDCEx(::draw2d::region * prgnClip,unsigned int flags)
   {
      __UNREFERENCED_PARAMETER(prgnClip);
      __UNREFERENCED_PARAMETER(flags);
      throw ::interface_only();


      return nullptr;
   }*/

   //void window::LockWindowUpdate()
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   //void window::UnlockWindowUpdate()
   //{

   //   throw ::interface_only();

   //}


   void
      window::set_need_redraw(const ::int_rectangle_array& rectangleaHostNeedRedraw, function<void()> function,
         bool bAscendants)
   {

      _synchronous_lock synchronouslock(synchronization());

      if (rectangleaHostNeedRedraw.is_empty())
      {

         return;

      }

#ifdef EXTRA_LOGGING

      for (auto& rectangle : rectangleaHostNeedRedraw)
      {

         if (rectangle.is_empty())
         {

            information() << "window::set_need_redraw empty rectangle : " << rectangle;

         }
         else
         {

            information() << "window::set_need_redraw : " << rectangle;

         }

      }

#endif

      bool bFullRedraw = false;

      for (auto& predraw : m_redrawitema)
      {

         if (predraw->m_rectanglea.is_empty())
         {

            return;

         }

         bool bContainsAll = true;

         //int_rectangle_array rectangleaUnion;

         for (auto& rectangle : rectangleaHostNeedRedraw)
         {

            if (rectangle.is_null())
            {

               bFullRedraw = true;

               break;

            }

            bool bContainsAny = false;

            for (auto& rectangleRedraw : predraw->m_rectanglea)
            {

               if (rectangleRedraw.contains(rectangle))
               {

                  bContainsAny = true;

                  break;

               }

               //auto rectangleUnion = rectangleRedraw.get_union(rectangle);

               //if (rectangleUnion.area() <= (rectangleRedraw.area() + 4 * rectangle.area()))
               //{

               //   rectangleaUnion.add(rectangleUnion);

               //   information() << "set_need_redraw::merged rectangle " << rectangleUnion;

               //}

            }

            if (!bContainsAny)
            {

               bContainsAll = false;

               break;

            }

         }

         if (bFullRedraw)
         {

            break;

         }
         else if (bContainsAll)
         {

            if (function)
            {

               predraw->m_functiona.add(function);

            }

            return;

         }

         //else if (rectangleaUnion.size() == rectangleaHostNeedRedraw.size())
         //{

         //   information() << "set_need_redraw::merged rectangle count " << rectangleaUnion.size();

         //   predraw->m_rectanglea = ::transfer(rectangleaUnion);

         //   if (function)
         //   {

         //      predraw->m_functiona.add(function);

         //   }

         //   return;

         //}

      }

      if (m_bDoingGraphics)
      {

         //informationf("set_need_redraw on doing graphics");

      }

      if (bFullRedraw)
      {

         if (m_redrawitema.is_empty())
         {

            auto predrawitem = __create_new<::user::redraw_item>();

            if (function)
            {

               predrawitem->m_functiona.add(function);

            }

            m_redrawitema.add(predrawitem);

         }
         else
         {

            for (::collection::index i = m_redrawitema.get_upper_bound(); i >= 1; i--)
            {

               m_redrawitema.first()->m_functiona.append(m_redrawitema[i]->m_functiona);

               m_redrawitema.erase_at(i);

            }

            m_redrawitema.first()->m_rectanglea.clear();

            if (function)
            {

               m_redrawitema.first()->m_functiona.add(function);

            }

         }

         return;

      }

      auto predrawitem = __create_new<::user::redraw_item>();

      predrawitem->m_rectanglea.append(rectangleaHostNeedRedraw);

      if (function)
      {

         predrawitem->m_functiona.add(function);

      }

      m_redrawitema.add(predrawitem);

      //information() << node()->get_callstack();

   }


   //bool window::needs_to_draw(const ::int_rectangle & rectangleHostNeedsToDraw, ::draw2d::graphics_pointer & pgraphics)
   //{

   //   _synchronous_lock synchronouslock(synchronization());

   //   if (!m_pgraphics->is_single_buffer_mode())
   //   {

   //      return true;

   //   }

   //   if (pgraphics->m_rectangleaNeedRedraw.is_empty())
   //   {

   //      return true;

   //   }

   //   for (auto & rectangleRedraw : pgraphics->m_rectangleaNeedRedraw)
   //   {

   //      if (rectangleRedraw.intersects(rectangleHostNeedsToDraw))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   void window::post_redraw(bool bAscendants)
   {

      if (has_destroying_flag())
      {

         return;

      }

      if (::is_null(m_pgraphicsthread))
      {

         return;

      }

      if (!user_interaction())
      {

         return;

      }

      //bool bForceUpdateBuffer = false;

      if (!m_pgraphicsthread->is_task_set2())
      {

         warning() << "graphics thread is not a thread but posting redraw";

         return;

      }

      if (m_pgraphicsthread->m_bFps)
      {

         warning() << "graphics thread is going to ignore post redraw as it should be doing Fps drawing";

         return;

      }

      m_pgraphicsthread->post_redraw();

      //user_interaction()->post_message(::e_message_redraw, bForceUpdateBuffer);

//      m_pgraphicsthread->graphics_thread_redraw();

   }


   bool
      window::RedrawWindow(const ::int_rectangle& rectangleUpdate, ::draw2d::region* prgnUpdate, unsigned int flags)
   {

      user_interaction()->set_need_redraw();

      return true;

   }


   //void window::EnableScrollBar(int nSBFlags,unsigned int nArrowFlags)
   //{

   //   __UNREFERENCED_PARAMETER(nSBFlags);

   //   __UNREFERENCED_PARAMETER(nArrowFlags);

   //   throw ::interface_only();

   //   return false;

   //}


   //::int_point window::get_cursor_position() const
   //{

   //   auto psession = session();

   //   if (!psession)
   //   {

   //      return ::int_point();

   //   }

   //   return psession->get_cursor_position();

   //}


   void window::set_mouse_cursor(::windowing::cursor* pcursor)
   {

      //if (::is_null(m_pwindow))
      //{

      //   //return ::error_failed;

      //   return;

      //}

      //auto estatus = 

      //set_mouse_cursor(pcursor);
      m_pcursor = pcursor;

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //::windowing::window * window::get_window() const
   //{

   //   return m_pwindow;

   //}


   //void window::aaa_set_mouse_cursor(enum_cursor ecursor)
   //{

   //   auto psession = session();

   //   auto puser = user();

   //   auto pwindowing = system()->windowing();

   //   auto pcursor = pwindowing->get_cursor(ecursor);

   //   auto pwindow = get_window();

   //   auto estatus = pwindow->set_cursor(pcursor);

   //   return estatus;

   //}


   //void window::DrawCaption(::draw2d::graphics_pointer & pgraphics,const int_rectangle & prc,unsigned int uFlags)
   //{

   //   __UNREFERENCED_PARAMETER(pgraphics);
   //   __UNREFERENCED_PARAMETER(prc);
   //   __UNREFERENCED_PARAMETER(uFlags);

   //   throw ::interface_only();

   //   //return false;

   //}


   //void window::is_window_enabled() const
   //{

   //   return user_interaction()->m_ewindowflag & e_window_flag_enable;

   //}


   void window::enable_window(bool bEnable)
   {

      user_interaction()->m_ewindowflag.set(e_window_flag_enable, bEnable);

      //return true;

   }


   //::user::interaction * window::GetActiveWindow()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * window::set_active_window()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void window::set_keyboard_focus()
   //{

   //   return false;

   //}


   //void window::CheckDlgButton(int nIDButton,unsigned int nCheck)
   //{
   //   __UNREFERENCED_PARAMETER(nIDButton);
   //   __UNREFERENCED_PARAMETER(nCheck);
   //   throw ::interface_only();
   //}

   //void window::CheckRadioButton(int nIDFirstButton,int nIDLastButton,int nIDCheckButton)
   //{
   //   __UNREFERENCED_PARAMETER(nIDFirstButton);
   //   __UNREFERENCED_PARAMETER(nIDLastButton);
   //   __UNREFERENCED_PARAMETER(nIDCheckButton);
   //   throw ::interface_only();
   //}

   //int window::DlgDirList(char * pPathSpec,int nIDListBox,int nIDStaticPath,unsigned int nFileType)

   //{
   //   __UNREFERENCED_PARAMETER(pPathSpec);

   //   __UNREFERENCED_PARAMETER(nIDListBox);
   //   __UNREFERENCED_PARAMETER(nIDStaticPath);
   //   __UNREFERENCED_PARAMETER(nFileType);
   //   throw ::interface_only();
   //   return 0;
   //}

   //int window::DlgDirListComboBox(char * pPathSpec,int nIDComboBox,int nIDStaticPath,unsigned int nFileType)

   //{
   //   __UNREFERENCED_PARAMETER(pPathSpec);

   //   __UNREFERENCED_PARAMETER(nIDComboBox);
   //   __UNREFERENCED_PARAMETER(nIDStaticPath);
   //   __UNREFERENCED_PARAMETER(nFileType);
   //   throw ::interface_only();

   //   return 0;
   //}

   //void window::DlgDirSelect(char * pString,int nSize,int nIDListBox)

   //{
   //   __UNREFERENCED_PARAMETER(pString);

   //   __UNREFERENCED_PARAMETER(nSize);
   //   __UNREFERENCED_PARAMETER(nIDListBox);
   //   throw ::interface_only();

   //   return false;
   //}

   //void window::DlgDirSelectComboBox(char * pString,int nSize,int nIDComboBox)

   //{
   //   __UNREFERENCED_PARAMETER(pString);

   //   __UNREFERENCED_PARAMETER(nSize);
   //   __UNREFERENCED_PARAMETER(nIDComboBox);
   //   throw ::interface_only();

   //   return false;
   //}

   //unsigned int window::GetChildByIdInt(int nID,bool* pTrans,bool bSigned) const

   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pTrans);

   //   __UNREFERENCED_PARAMETER(bSigned);
   //   throw ::interface_only();

   //   return 0;
   //}

   //int window::GetChildByIdText(int nID,char * pStr,int nMaxCount) const

   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pStr);

   //   __UNREFERENCED_PARAMETER(nMaxCount);
   //   throw ::interface_only();

   //   return 0;
   //}


   //::windowing::window * window::GetNextDlgGroupItem(::windowing::window * pWndCtl,bool bPrevious) const
   //{

   //   __UNREFERENCED_PARAMETER(pWndCtl);
   //   __UNREFERENCED_PARAMETER(bPrevious);

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::windowing::window * window::GetNextDlgTabItem(::windowing::window * pWndCtl,bool bPrevious) const
   //{

   //   __UNREFERENCED_PARAMETER(pWndCtl);
   //   __UNREFERENCED_PARAMETER(bPrevious);

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //unsigned int window::IsDlgButtonChecked(int nIDButton) const
   //{
   //   __UNREFERENCED_PARAMETER(nIDButton);
   //   throw ::interface_only();

   //   return 0;
   //}


   //lparam window::SendDlgItemMessage(int nID, unsigned int message, wparam wParam,lparam lParam)
   //{

   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(message);
   //   __UNREFERENCED_PARAMETER(wParam);
   //   __UNREFERENCED_PARAMETER(lParam);
   //   throw ::interface_only();

   //   return 0;

   //}


   //void window::SetDlgItemInt(int nID,unsigned int nValue,bool bSigned)
   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(nValue);
   //   __UNREFERENCED_PARAMETER(bSigned);
   //   throw ::interface_only();
   //}

   //void window::SetDlgItemText(int nID, const ::scoped_string & scopedstrString)

   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(scopedstrString);

   //   throw ::interface_only();
   //}


   //int window::ScrollWindowEx(int Δx,int Δy,
   //                                     const ::int_rectangle * prectScroll,
   //                                       const ::int_rectangle * prectClip,
   //                                     ::draw2d::region* prgnUpdate,::int_rectangle * pRectUpdate,unsigned int flags)
   //{

   //   __UNREFERENCED_PARAMETER(Δx);
   //   __UNREFERENCED_PARAMETER(Δy);
   //   __UNREFERENCED_PARAMETER(prectScroll);
   //   __UNREFERENCED_PARAMETER(prectClip);
   //   __UNREFERENCED_PARAMETER(prgnUpdate);
   //   __UNREFERENCED_PARAMETER(pRectUpdate);
   //   __UNREFERENCED_PARAMETER(flags);

   //   throw ::interface_only();

   //   return 0;

   //}


   //void window::ShowScrollBar(unsigned int nBar,bool bShow)
   //{

   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(bShow);

   //   throw ::interface_only();

   //}


   ::user::interaction* window::ChildWindowFromPoint(const ::int_point& point)
   {

      __UNREFERENCED_PARAMETER(point);

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction* window::ChildWindowFromPoint(const ::int_point& point, unsigned int nFlags)
   {

      __UNREFERENCED_PARAMETER(point);

      __UNREFERENCED_PARAMETER(nFlags);

      throw ::interface_only();

      return nullptr;

   }


   //   ::user::interaction * window::get_next_window(unsigned int nFlag)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(nFlag);
   //
   //      throw ::interface_only();
   //
   //      return nullptr;
   //
   //   }


   ::user::interaction* window::GetTopWindow()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction* window::GetLastActivePopup()
   {

      throw ::interface_only();

      return nullptr;

   }


   //void window::FlashWindow(bool bInvert)
   //{

   //   __UNREFERENCED_PARAMETER(bInvert);

   //   throw ::interface_only();

   //   return false;

   //}


   //void window::ChangeClipboardChain(::windowing::window * pwindow_Next)
   //{

   //   __UNREFERENCED_PARAMETER(oswindow_Next);

   //   throw ::interface_only();

   //   return false;

   //}


   //oswindow window::SetClipboardImpacter()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void window::OpenClipboard()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void window::user_interaction_on_hide()
   {

      decltype(m_userinteractionaMouseHover) userinteractiona;

      {

         auto psync = synchronization();

         _synchronous_lock synchronouslock(this->synchronization());

         userinteractiona = m_userinteractionaMouseHover;

         m_userinteractionaMouseHover.erase_all();

      }

      for (auto& pinteraction : userinteractiona)
      {

         pinteraction->post_message(e_message_mouse_leave);

      }

   }


   //void window::HideCaret()
   //{

   //   throw ::interface_only();

   //}


   //void window::ShowCaret()
   //{

   //   throw ::interface_only();

   //}


   //void window::set_foreground_window()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void window::SendNotifyMessage(unsigned int message,wparam wParam,lparam lParam)
   //{

   //   __UNREFERENCED_PARAMETER(message);
   //   __UNREFERENCED_PARAMETER(wParam);
   //   __UNREFERENCED_PARAMETER(lParam);

   //   throw ::interface_only();

   //   return false;

   //}


   void window::Print(::draw2d::graphics_pointer& pgraphics, unsigned int dwFlags) const
   {

      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(dwFlags);

      throw ::interface_only();

   }


   void window::PrintClient(::draw2d::graphics_pointer& pgraphics, unsigned int dwFlags) const
   {

      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(dwFlags);

      throw ::interface_only();

   }


   //void window::SetWindowContextHelpId(unsigned int dwContextHelpId)
   //{

   //   __UNREFERENCED_PARAMETER(dwContextHelpId);

   //   throw ::interface_only();

   //   return false;

   //}


   //unsigned int window::GetWindowContextHelpId() const
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   //void window::on_message_create(::message::message * pmessage)
   //{


   //}


   void window::_001OnPrioAfterCreate(::message::message* pmessage)
   {

      if (user_interaction())
      {

         user_interaction()->m_ewindowflag |= e_window_flag_window_created;

      }

      information() << "on_message_after_create";

      if (m_pgraphicsthread)
      {

         information() << "m_pgraphicsthread->m_bGraphicsThreadEnabled = true";

         //m_pgraphicsthread->m_happeningReady.set_happening();

         m_pgraphicsthread->m_bGraphicsThreadEnabled = true;

      }

      auto pusersystem = user_interaction()->m_pusersystem;

      if (pusersystem)
      {

         add(pusersystem->m_prequest);

         for (auto& poutputpurpose : pusersystem->m_graphicsoutputpurposea)
         {

            information() << "adding graphical output_purpose from user::system";

            add(poutputpurpose);

         }

         user_interaction()->set_need_redraw();

         user_interaction()->post_redraw();

      }

   }


   void window::_001OnPrioCreate(::message::message* pmessage)
   {

      if (user_interaction()->is_graphical())
      {

         if (::is_null(m_papplication->m_pacmeuserinteractionMain))
         {

            m_papplication->m_pacmeuserinteractionMain = user_interaction();

         }

         //draw2d()->on_create_window(this);

         user_interaction()->defer_set_icon();

      }

      user_interaction()->on_after_set_parent();

      // // https://stackoverflow.com/questions/23367775/pragma-packshow-with-gcc - Morten Jensen
      //       /*
      //    The static_assert macro will generate an error at compile-time, if the predicate is false
      //    but will only work for predicates that are resolvable at compile-time!

      //    E.g.: to assert the size of a data structure, static_assert(sizeof(struct_t) == 10)
      // */
      // #define STATIC_ASSERT(COND,MSG)      typedef char static_assertion_##MSG[(!!(COND))*2-1]
      // /* token pasting madness: */
      // #define COMPILE_TIME_ASSERT3(X,L)     STATIC_ASSERT(X,at_line_##L)             /* add line-number to error message for better warnings, especially GCC will tell the name of the variable as well */
      // #define COMPILE_TIME_ASSERT2(X,L)     COMPILE_TIME_ASSERT3(X, L)               /* expand line-number */
      // #define static_assert(X)              COMPILE_TIME_ASSERT2(X, __LINE__)        /* call with line-number macro */

      // #define PACKED  __attribute__ ((gcc_struct, __packed__))

      //   typedef struct
      //   {
      //      uint8_t bytes[3];
      //      uint32_t looong;
      //   } struct_t1;
      //   // static_assert(sizeof(struct_t) == 8);
      //
      //      printf("sizeof(struct_t1) = %" PRIuPTR "\n", sizeof(struct_t1));
      //
      //      #ifdef _DEBUG
      //      printf("_DEBUG defined\n");
      //      #else
      //      printf("_DEBUG not defined\n");
      //      #endif
      //
      //      #ifdef RASPBERRYPIOS
      //      printf("RASPBERRYPIOS defined\n");
      //      #else
      //      printf("RASPBERRYPIOS not defined\n");
      //      #endif

#ifdef REPORT_OFFSET

      printf("(11.0) offset of m_timeFocusStart in ::user::interaction_base = %d\n", offsetof(::user::interaction_base, m_timeFocusStart));
      printf("(11.0) offset of m_uUserInteractionFlags in ::user::interaction = %d\n", offsetof(::user::interaction, m_bExtendOnParent));
      printf("(11.0) offset of m_pwindow in ::user::interaction = %d\n", offsetof(::user::interaction, m_pwindow));

      if (::is_null(user_interaction()->m_pwindow))
      {

         printf("user_interaction()->m_pwindow is null!! (11.1) (0x%x)\n", user_interaction()->m_pwindow);
         printf("user_interaction() (11.1) (0x%x)\n", user_interaction().m_p);
         printf("&m_pwindow(0x%x)\n", &user_interaction()->m_pwindow);

      }
      else
      {

         printf("user_interaction()->m_pwindow is set!! (11.1) (0x%x)\n", user_interaction()->m_pwindow);
         printf("user_interaction() (11.1) (0x%x)\n", user_interaction().m_p);
         printf("&m_pwindow(0x%x)\n", &user_interaction()->m_pwindow);

      }

      fflush(stdout);

#endif

      if (::is_null(user_interaction()->m_pinteractionScaler))
      {

         user_interaction()->m_pinteractionScaler = __allocate::user::interaction_scaler();

      }

#ifdef REPORT_OFFSET

      if (::is_null(user_interaction()->m_pwindow))
      {

         printf("user_interaction()->m_pwindow is null!! (11) (0x%x)\n", user_interaction()->m_pwindow);
         printf("user_interaction() (11) (0x%x)\n", user_interaction().m_p);

      }
      else
      {

         printf("user_interaction()->m_pwindow is set!! (11) (0x%x)\n", user_interaction()->m_pwindow);
         printf("user_interaction() (11) (0x%x)\n", user_interaction().m_p);

      }

      fflush(stdout);

#endif

      user_interaction()->m_pinteractionScaler->on_display_change(user_interaction());

#ifdef REPORT_OFFSET

      if (::is_null(user_interaction()->m_pwindow))
      {

         printf("user_interaction()->m_pwindow is null!! (12) (0x%x)\n", user_interaction()->m_pwindow);
         printf("user_interaction() (12) (0x%x)\n", user_interaction().m_p);

      }
      else
      {

         printf("user_interaction()->m_pwindow is set!! (12) (0x%x)\n", user_interaction()->m_pwindow);
         printf("user_interaction() (12) (0x%x)\n", user_interaction().m_p);

      }

      fflush(stdout);

#endif

      string strType = ::type(user_interaction()).name();

      if (user_interaction()->is_graphical())
      {

         if (::is_set(m_pgraphicsthread))
         {

            m_pgraphicsthread->set_fps_interest_frames_per_second(get_prodevian_frames_per_second());

            m_pgraphicsthread->set_nominal_frames_per_second(get_nominal_frames_per_second());

            pmessage->previous();

         }

         m_pcsDisplay = __raw_new critical_section();

         information() << "interaction_impl m_pgraphics alloc : " << strType;

         //update_graphics_resources();

         information() << "interaction_impl on _create_window : " << strType;

         if (m_pgraphicsthread)
         {

            m_pgraphicsthread->graphics_thread_reset(user_interaction());

            m_pgraphicsthread->defer_create_graphics_thread();

         }

      }


   }


   void window::on_message_show_window(::message::message* pmessage)
   {

      ::pointer<::message::show_window> pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         information() << "windowing::window::on_message_show_window bShow = true";

         if (user_interaction()->const_layout().design().display() != ::e_display_iconic)
         {

            if (user_interaction()->get_parent() == nullptr)
            {

               user_interaction()->check_transparent_mouse_events();

            }

         }
         else
         {

            //stop_prodevian();
            //child_post_quit("prodevian");

         }

         if (user_interaction())
         {

            user_interaction()->check_transparent_mouse_events();

            set_need_redraw();

         }

      }
      else
      {

         information() << "windowing::window::on_message_show_window bShow = false";

         {

            decltype(m_userinteractionaMouseHover) userinteractiona;

            {

               _synchronous_lock synchronouslock(this->synchronization());

               userinteractiona = m_userinteractionaMouseHover;

               m_userinteractionaMouseHover.erase_all();

            }

            for (auto& pinteraction : userinteractiona)
            {

               try
               {

                  pinteraction->send_message(e_message_mouse_leave);

               }
               catch (...)
               {

               }

            }

         }

         {

            //auto children = user_interaction()->synchronized_get_children();

            // auto puserinteractionpointeraChild = user_interaction()->m_puserinteractionpointeraChild;

            // if (puserinteractionpointeraChild)
            for_user_interaction_children(puserinteraction, this)
            {

               //{

               //   _synchronous_lock synchronouslock(this->synchronization());

               //   if(!user_interaction())
               //   {

               //      return;

               //   }

               //   uia = user_interaction()->m_puserinteractionpointeraChild;

               //}

               //for (auto & pinteraction : children)
               {

                  //synchronouslock.unlock();

                  try
                  {

                     puserinteraction->send_message(e_message_show_window, 0, (long long)e_show_window_parent_closing);

                  }
                  catch (...)
                  {

                  }

                  //synchronouslock.lock();

               }

            }

         }

         //auto psequencer = __create_new < sequencer<sequence<window>>>();

         if (m_uOnHide)
         {

            post_continuation continuation(this);

            if (m_bQuitGraphicsOnHide)
            {

               continuation <<
                  [this]()
                  {

                     m_pgraphicsthread->stop_task();

                  };

            }

            if (m_bDestroyWindowOnHide)
            {

               continuation <<
                  [this]()
                  {

                     user_interaction()->destroy_window();

                  };

            }

            if (m_bTryCloseApplicationOnHide)
            {

               auto papp = get_app();

               continuation <<
                  [papp]()
                  {

                     papp->_001TryCloseApplication();

                  };

            }

         }

         //pmessagebox->async();

         return;

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

   }


#ifdef WINDOWS_DESKTOP


   void window::_001OnWindowPosChanged(::message::message* pmessage)
   {

      throw ::interface_only();

   }


#endif


   void window::BeginModalState()
   {

      throw ::interface_only();

   }


   void window::EndModalState()
   {

      throw ::interface_only();

   }


   void window::do_graphics()
   {

      m_bDoingGraphics = true;

      at_end_of_scope
      {

         m_bDoingGraphics = false;

      };

      windowing_output_debug_string("windowing::window::do_graphics");

      string strType = ::type(user_interaction()).name();

#ifdef MORE_LOG

      debug() << "do_graphics(A)";

#endif

      update_graphics_resources();

      if (m_pgraphicsgraphics.is_null())
      {

         information() << "do_graphics exit(A1)";

         return;

      }

      ::draw2d::graphics_pointer pgraphics;

      user_interaction()->defer_do_graphics(pgraphics);

   }


   void window::top_down_prefix()
   {

      user_interaction()->top_down_prefix();

   }


   //void window::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   //{

   //   //::windowing::window_base::_001OnNcClip(pgraphics);

   //}


   void window::defer_do_graphics(::draw2d::graphics_pointer& pgraphics)
   {

      debug() << "windowing::window::defer_do_graphics";

      //{

      //user_interaction()->top_down_prefix();

      //user_interaction()->layout_to_design();


      {
         
         //::draw2d::lock draw2dlock(this);

         auto pbuffer = m_pgraphicsgraphics;

         _synchronous_lock slGraphics(pbuffer->synchronization());

         //windowing::graphics_lock graphicslock(m_pwindow);

         //m_pgraphics->update_buffer(rectangleWindow.size());

#ifdef MORE_LOG

         debug() << "intrimpl::defer_do_graphics on_begin_draw";

#endif

         auto pbufferitem = pbuffer->on_begin_draw(e_graphics_layout);
         //auto pparticleSynchronization = m_pgraphics->get_buffer_item()->m_pmutex;

         if (!pbufferitem)
         {

#ifdef MORE_LOG

            information() << "intrimpl::defer_do_graphics !pbufferitem";

#endif

            return;

         }

#ifdef MORE_LOG

         debug() << "intrimpl::defer_do_graphics on_begin_draw END";

#endif


         _synchronous_lock synchronouslock(pbufferitem->m_pmutex);


         //information() << "graphics::on_begin_draw";

         slGraphics.unlock();

         windowing_output_debug_string("\n_001UpdateBuffer : after on_begin_draw");

         if (has_destroying_flag())
         {

#ifdef MORE_LOG

            information() << "intrimpl::defer_do_graphics has_destroying_flag";

#endif

            return;

         }

         //::pointer < ::draw2d::graphics > pgraphics = pbufferitem->g();

         pgraphics = pbufferitem->g();

#ifdef MORE_LOG

         debug() << "intrimpl::defer_do_graphics got graphics g";

#endif

         //#ifdef UNIVERSAL_WINDOWS
         if (::is_null(pgraphics) || pgraphics->nok())
         {

            //#define SEVERITY_HIGH 5

            //int iSeverity = SEVERITY_HIGH;

            //for(::collection::index i = 0; i < iSeverity * 20; i++)
            //{

            informationf("m_pgraphics->on_begin_draw FAILED (1)\n");

            //}

            return;

         }

         pgraphics->m_puserinteraction = m_pacmeuserinteraction;

         //draw2dlock.unlock();

         pgraphics->do_on_context([this, pbuffer, &pgraphics, &pbufferitem]()
            {

               _synchronous_lock synchronous_lock(m_pmutexGraphics);

               {

                  //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
                  //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
                  //#endif

                  pgraphics->payload("set_transparent") = "";

                  pgraphics->m_pgraphicsgraphics = pbuffer;

                  pgraphics->m_pgraphicsbufferitem = pbufferitem;

#ifdef MORE_LOG

                  debug() << "intrimpl::defer_do_graphics Going to call pgraphics->on_begin_draw";

#endif



                  pgraphics->on_begin_draw();

                  pgraphics->reset_clip();

                  pgraphics->reset_impact_area();

                  //{

                  //   _synchronous_lock synchronouslock(synchronization());

                  //   pgraphics->__construct_new(pgraphics->m_puserredraw);

                  //   pgraphics->user_redraw()->m_pgraphics = pgraphics;

                  //   pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

                  //   if (m_redrawitema.has_element())
                  //   {

                  //      throw "what?!?!";

                  //   }

                  //}



                  //pgraphics->m_egraphics = e_graphics_layout;

                  //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
                  //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
                  //#endif

                  //pgraphics->payload("set_transparent") = "";

                  //pgraphics->m_pgraphicsgraphics = m_pgraphics;

                  //pgraphics->m_pgraphicsbufferitem = pbufferitem;

                  //pgraphics->on_begin_draw();

                  //pgraphics->reset_clip();

                  //pgraphics->set_origin(0., 0.);


                  {

                     _synchronous_lock synchronouslock(synchronization());

                     if (pgraphics->__defer_construct_new(pgraphics->m_puserredraw))
                     {

                        if (system()->draw2d()->graphics_context_does_full_redraw())
                        {

                           pgraphics->m_puserredraw->m_bEnabled = false;

                        }

                     }

                     if (pgraphics->m_puserredraw->m_bEnabled)
                     {

                        pgraphics->user_redraw()->m_pgraphics = pgraphics;

                        pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

                        if (m_redrawitema.has_element())
                        {

#ifdef MORE_LOG

                           information() << "intrimpl::defer_do_graphics what?!?!";

#endif

                           throw "what?!?!";

                        }

                     }

                  }



                  //if (!bDraw)
                  //{

                  //   if (pgraphics->m_rectangleaNeedRedraw.has_element())
                  //   {

                  //      bDraw = true;

                  //   }

                  //}

                  pgraphics->m_pdraw2dhost = user_interaction();

                  pgraphics->m_puserstyleGraphics.release();

                  if (pgraphics->m_pimage)
                  {

                     pgraphics->m_pimage->m_rectangleTag.Null();

                     //sizeDrawn = pgraphics->m_pimage->m_size;

                     ///sizeDrawn = user_interaction()->const_layout().design().size();

                  }

                  string strBitmapSource = payload("bitmap-source");

                  if (strBitmapSource.has_character())
                  {

                     //            ::pointer < ::graphics::bitmap_source_buffer > pbitmapsourcebuffer = pgraphics;
                     //
                     //            if(pbitmapsourcebuffer)
                     //            {
                     //
                     //
                     //
                     //
                     //            }

                  }

                  if (user_interaction())
                  {

                     //auto r = user_interaction()->screen_rect();

                     if (user_interaction()->has_finishing_flag())
                     {

                        informationf("::windowing::window set_finish");

                     }
                     else
                     {

                        //pgraphics->m_bDraw = bDraw;

                        pgraphics->m_bDraw = false;

                        pgraphics->m_bInheritDraw = false;

                        //            pgraphics->fill_solid_rectangle({ 0, 0, 200, 200 }, ::color::green);
#ifdef MORE_LOG
                        debug() << "defer_do_graphics _000TopCallOnLayout";
#endif
                        user_interaction()->_000TopCallOnLayout(pgraphics);

                        //user_interaction()->_000CallOnDraw(pgraphics);

                        //                  if (!bDraw && m_redrawa.has_element())
                        //                  {
                        //
                        //                     synchronouslock.unlock();
                        //
                        //                     bDraw = true;
                        //
                        //                     pgraphics->m_bDraw = bDraw;
                        //
                        //                     user_interaction()->_000CallOnDraw(pgraphics);
                        //
                        //                  }

                     }

                     //m_rectangleUpdateBuffer = r;

                     //informationf("PrintBuffer (%d, %d)",  r.right(), r.bottom());

                     //if (!m_pgraphics)
                     //{

                     //   return;

                     //}

                     //m_pgraphics->m_bNewBuffer = true;

                  }

                  ////if (pgraphics->m_pimage.ok())
                  ////{

                  ////   //pgraphics->m_pimage->m_rectangleTag = m_rectangleUpdateBuffer;

                  ////   //m_sizeDrawn = sizeDrawn;

                  ////   pgraphics->m_sizeDrawnAnnotation = sizeDrawn;

                  ////}

                  //m_sizeLastBuffer = pbufferitem->m_size;

                  ////}

                  //if (m_pgraphics)
                  //{

                  //   m_pgraphics->on_end_draw();

                  //}

               }

            });

      }

      auto pbuffer = m_pgraphicsgraphics;

      if (pbuffer)
      {

         //::draw2d::lock draw2dlock(this);

         _synchronous_lock slGraphics(pbuffer->synchronization());

         //windowing::graphics_lock graphicslock(m_pwindow);

         //m_pgraphics->update_buffer(rectangleWindow.size());



         auto pbufferitem = pbuffer->on_begin_draw(e_graphics_draw);
         //auto pparticleSynchronization = m_pgraphics->get_buffer_item()->m_pmutex;

         if (!pbufferitem)
         {

            information() << "defer_do_graphics !pbufferitem (2)";

            return;

         }

         _synchronous_lock synchronouslock(pbufferitem->m_pmutex);


         //information() << "graphics::on_begin_draw";

         slGraphics.unlock();

         windowing_output_debug_string("\n_001UpdateBuffer : after on_begin_draw");

         if (has_destroying_flag())
         {

            information() << "defer_do_graphics has_destroying_flag()";

            return;

         }

         //::pointer < ::draw2d::graphics > pgraphics = pbufferitem->g();

         pgraphics = pbufferitem->g();



         //#ifdef UNIVERSAL_WINDOWS
         if (::is_null(pgraphics) || pgraphics->nok())
         {

            //#define SEVERITY_HIGH 5

            //int iSeverity = SEVERITY_HIGH;

            //for(::collection::index i = 0; i < iSeverity * 20; i++)
            //{

            information() << "m_pgraphics->on_begin_draw FAILED (1)";

            //}

            return;

         }

         //draw2dlock.unlock();

         pgraphics->do_on_context([this, &pgraphics, &pbufferitem]()
            {

               _synchronous_lock synchronous_lock(m_pmutexGraphics);



               {

                  //pgraphics->m_egraphics = e_graphics_draw;

                  //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
                  //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
                  //#endif

                  pgraphics->payload("set_transparent") = "";

                  pgraphics->m_pgraphicsgraphics = m_pgraphicsgraphics;

                  pgraphics->m_pgraphicsbufferitem = pbufferitem;

                  ::string strType = type(m_pacmeuserinteraction).name();

                  if (strType.case_insensitive_contains("menu"))
                  {

                     printf_line("menu");

                  }

                  pgraphics->on_begin_draw();

                  //pgraphics->reset_clip();

                  //pgraphics->reset_impact_area();

                  //{

                  //   _synchronous_lock synchronouslock(synchronization());

                  //   pgraphics->__construct_new(pgraphics->m_puserredraw);

                  //   pgraphics->user_redraw()->m_pgraphics = pgraphics;

                  //   pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

                  //   if (m_redrawitema.has_element())
                  //   {

                  //      throw "what?!?!";

                  //   }

                  //}



                  //pgraphics->m_egraphics = e_graphics_layout;

                  //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
                  //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
                  ////#endif

                  //pgraphics->payload("set_transparent") = "";

                  //pgraphics->m_pgraphicsgraphics = m_pgraphics;

                  //pgraphics->m_pgraphicsbufferitem = pbufferitem;

                  //pgraphics->on_begin_draw();

                  //pgraphics->reset_clip();

                  //pgraphics->set_origin(0., 0.);

                  //{

                  //   _synchronous_lock synchronouslock(synchronization());

                  //   pgraphics->__construct_new(pgraphics->m_puserredraw);

                  //   pgraphics->user_redraw()->m_pgraphics = pgraphics;

                  //   pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

                  //   if (m_redrawitema.has_element())
                  //   {

                  //      throw "what?!?!";

                  //   }

                  //}



                  //if (!bDraw)
                  //{

                  //   if (pgraphics->m_rectangleaNeedRedraw.has_element())
                  //   {

                  //      bDraw = true;

                  //   }

                  //}

                  //pgraphics->m_pdraw2dhost = user_interaction();

                  //pgraphics->m_puserstyle.release();

                  //if (pgraphics->m_pimage)
                  //{

                  //   pgraphics->m_pimage->m_rectangleTag.Null();

                  //   //sizeDrawn = pgraphics->m_pimage->m_size;

                  //   ///sizeDrawn = user_interaction()->const_layout().design().size();

                  //}

                  //string strBitmapSource = payload("bitmap-source");

                  //if (strBitmapSource.has_character())
                  //{

                  //   //            ::pointer < ::graphics::bitmap_source_buffer > pbitmapsourcebuffer = pgraphics;
                  //   //
                  //   //            if(pbitmapsourcebuffer)
                  //   //            {
                  //   //
                  //   //
                  //   //
                  //   //
                  //   //            }

                  //}

                  if (user_interaction())
                  {

                     //auto r = user_interaction()->screen_rect();

                     if (user_interaction()->has_finishing_flag())
                     {

                        informationf("::windowing::window set_finish");

                     }
                     else
                     {

                        //pgraphics->m_bDraw = bDraw;

                        pgraphics->m_bDraw = true;

                        pgraphics->m_bInheritDraw = true;

                        //            pgraphics->fill_solid_rectangle({ 0, 0, 200, 200 }, ::color::green);


#ifdef MORE_LOG
                        debug() << "defer_do_graphics _000TopCallOnDraw";
#endif
                        ///xxxopengl  user_interaction()->_000TopCallOnDraw(pgraphics);

                        //xxxdirectx user_interaction()->_000TopCallOnDraw(pgraphics);
                        user_interaction()->_000TopCallOnDraw(pgraphics);

                        //pgraphics->fill_solid_rectangle({ 0., 0., 100., 100. }, ::argb(0.5, 0.5, 0.8, 0.75));

                        ////user_interaction()->_000CallOnDraw(pgraphics);

                        //                  if (!bDraw && m_redrawa.has_element())
                        //                  {
                        //
                        //                     synchronouslock.unlock();
                        //
                        //                     bDraw = true;
                        //
                        //                     pgraphics->m_bDraw = bDraw;
                        //
                        //                     user_interaction()->_000CallOnDraw(pgraphics);
                        //
                        //                  }

                     }

                     //m_rectangleUpdateBuffer = r;

                     //informationf("PrintBuffer (%d, %d)",  r.right(), r.bottom());

                     if (!m_pgraphicsgraphics)
                     {

                        return;

                     }

                     m_pgraphicsgraphics->m_bNewBuffer = true;

                  }
                  else
                  {


                     information() << "defer_do_graphics !user_interaction()";

                  }

                  //if (pgraphics->m_pimage.ok())
                  //{

                  //   //pgraphics->m_pimage->m_rectangleTag = m_rectangleUpdateBuffer;

                  //   //m_sizeDrawn = sizeDrawn;

                  //   pgraphics->m_sizeDrawnAnnotation = sizeDrawn;

                  //}

                  m_sizeLastBuffer = pbufferitem->m_sizeBufferItemDraw;

                  //}

                  pgraphics->on_end_draw();

                  if (m_pgraphicsgraphics)
                  {

#ifndef LINUX
                     m_pgraphicsgraphics->on_end_draw();
#endif

                  }

               }

            });

      }

   }


   //void window::_000CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   m_bUpdateBuffer = false;

   //   m_bUpdateWindow = false;

   //   if (user_interaction()->should_perform_layout(pgraphics))
   //   {

   //      user_interaction()->perform_layout(pgraphics);

   //   }

   //}


   //void window::_defer_start_prodevian()
   //{

   //   defer_fork("prodevian", [&]() { _thread_prodevian(); });

   //}


   void window::set_prodevian_frames_per_second(::frequency frequencyProdevianFramesPerSecond)
   {

      m_frequencyProdevianFramesPerSecond = frequencyProdevianFramesPerSecond;

      if (::is_set(m_pgraphicsthread))
      {

         if (::is_set(user_interaction()) && user_interaction()->is_graphical())
         {

            m_pgraphicsthread->set_fps_interest_frames_per_second(m_frequencyProdevianFramesPerSecond);

         }

      }

   }


   void window::set_nominal_frames_per_second(::frequency frequencyNominalFramesPerSecond)
   {

      m_frequencyNominalFramesPerSecond = frequencyNominalFramesPerSecond;

      if (::is_set(m_pgraphicsthread))
      {

         if (::is_set(user_interaction()) && user_interaction()->is_graphical())
         {

            m_pgraphicsthread->set_nominal_frames_per_second(m_frequencyNominalFramesPerSecond);

         }

      }

   }


   void window::set_per_second(::frequency frequencyFramesPerSecond)
   {

      m_frequencyNominalFramesPerSecond = frequencyFramesPerSecond;

      m_frequencyProdevianFramesPerSecond = frequencyFramesPerSecond;

      if (::is_set(m_pgraphicsthread))
      {

         if (::is_set(user_interaction()) && user_interaction()->is_graphical())
         {

            m_pgraphicsthread->set_per_second(frequencyFramesPerSecond);

         }

      }

   }


   ::frequency window::get_prodevian_frames_per_second()
   {

      return m_frequencyProdevianFramesPerSecond;

   }


   ::frequency window::get_nominal_frames_per_second()
   {

      return m_frequencyNominalFramesPerSecond;

   }


   ::frequency window::get_output_per_second()
   {

      return m_frequencyOutputFramesPerSecond;

   }


   //   void window::start_window_visual()
   //   {
   //
   //      if (m_puserthread)
   //      {
   //
   //         m_puserthread->start_window_visual();
   //
   //      }
   //      else
   //      {
   //
   //         user_interaction()->post_message(e_message_apply_visual);
   //
   //      }
   //
   //      //return true;
   //
   //   }


   void window::_001UpdateWindow()
   {

   }


   //   void window::_001UpdateScreen()
   //   {
   //
   //      _synchronous_lock synchronouslock(this->synchronization());
   //
   //      if (!user_interaction())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      if (m_bOfflineRender)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      string strType = ::type(user_interaction()).name();
   //
   //      if (strType.case_insensitive_contains("list_box"))
   //      {
   //
   //         auto edisplay = user_interaction()->const_layout().state(e_layout_design).display();
   //
   //         bool bGraphicsSet = m_pgraphics.is_set();
   //
   //         informationf("_001UpdateScreen list_box");
   //
   //      }
   //
   //      if (m_pgraphics.is_set())
   //      {
   //
   //         if (user_interaction()->layout().is_this_screen_visible())
   //         {
   //
   //            //            //CINFO(prodevian)("going to update_window (1)");
   //            //
   //            //            auto puserinteraction = user_interaction().m_p;
   //            //
   //            //            int* pi = (int*)puserinteraction;
   //            //
   //            //            auto& i = *pi;
   //            //
   //            //            //monitor_pointer(puserinteraction);
   //            //
   //            //            auto& iStateCount = user_interaction()->layout().m_iStateCount;
   //            //
   //            //            monitor_pointer(&iStateCount);
   //            //
   //            //            m_pgraphics->update_screen();
   //
   //            window_update_screen_buffer();
   //
   //            //user_interaction()->set_layout_state(user_interaction()->const_layout().design(), ::user::e_layout_window);
   //
   //         }
   //
   //      }
   //
   //   }


   //void window::process_message()
   //{

   //   while (true)
   //   {

   //      ::pointer<::message::message> pmessage;

   //      {

   //         _synchronous_lock synchronouslock(this->synchronization());

   //         if (m_messagelist.is_empty())
   //         {

   //            return;

   //         }

   //         pmessage = ::transfer(m_messagelist.pick_head());

   //      }

   //      message_handler(pmessage);

   //   }

   //}


   //void window::queue_message_handler(::message::message * pmessage)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   bool bWasEmpty = m_messagelist.is_empty();

   //   m_messagelist.add_tail(pmessage);

   //   if (bWasEmpty)
   //   {

   //      m_puserthread->kick_idle();

   //   }

   //}


   void window::set_bitmap_source(const ::scoped_string & scopedstrBitmapSource)
   {

      m_strBitmapSource = scopedstrBitmapSource;

      if (m_pgraphicsgraphics)
      {

         m_pgraphicsgraphics->set_bitmap_source(scopedstrBitmapSource);

      }

      //return ::success;

   }


   void window::clear_bitmap_source()
   {

      m_strBitmapSource.empty();

      if (m_pgraphicsgraphics)
      {

         m_pgraphicsgraphics->clear_bitmap_source();

      }

      //return ::success;

   }


   void window::update_graphics_resources()
   {

      single_lock synchronouslock(this->synchronization());

      if (m_pgraphicsgraphics.is_null())
      {

         __øconstruct(m_pgraphicsgraphics);

         if (m_pgraphicsgraphics)
         {

            m_pgraphicsgraphics->initialize_graphics_graphics(this);

         }

      }

   }


   void window::interaction_post(const ::procedure& procedure)
   {

      auto puserinteraction = user_interaction();

      if (::is_null(puserinteraction))
      {

         //return error_failed;

         throw ::exception(error_wrong_state);

      }

      auto puserthread = m_puserthread;

      if (::is_null(puserthread))
      {

         throw ::exception(error_wrong_state);

      }

      puserthread->post(procedure);

   }


   //guie_message_wnd::guie_message_wnd(::property_object * pparticle)
   //{

   //   m_puiForward = nullptr;

   //}


   //void guie_message_wnd::message_handler(::message::message * pmessage)
   //{

   //   if (m_puiForward != nullptr)
   //   {

   //      return m_puiForward->message_handler(pmessage);

   //   }

   //}


   //CLASS_DECL_AURA void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction,const ::int_rectangle & rectangle)
   //{

   //   ASSERT(::is_set(pinteraction));

   //   ::pointer<::user::interaction>puiParent = pinteraction->get_parent();

   //   ASSERT(puiParent != nullptr);

   //   ::int_rectangle rectangleOld;

   //   pinteraction->window_rectangle(rectangleOld);

   //   rectangleOld += puiParent->screen_to_client();

   //   pinteraction->place(rectangle);

   //   pinteraction->display(e_display_normal, ::user::e_activation_no_activate);

   //}


   //   void window::prodevian_redraw(bool bUpdateBuffer)
   //   {
   //
   //      if (!m_pgraphicsthread)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      if (user_interaction()->m_ewindowflag & e_window_flag_embedded_prodevian)
   //      {
   //
   //         m_pgraphicsthread->m_message.wParam |= 1;
   //
   //         m_pgraphicsthread->prodevian_iteration();
   //
   //      }
   //      else
   //      {
   //
   //         m_pgraphicsthread->post_message(e_message_redraw, bUpdateBuffer ? 1 : 0);
   //
   //      }
   //
   //   }


   void window::set_finish()
   {

      if (!has_destroying_flag())
      {

         if (m_pgraphicsgraphics)
         {

            _synchronous_lock slGraphics(m_pgraphicsgraphics->synchronization());

            auto pbufferitem = m_pgraphicsgraphics->get_buffer_item();

            _synchronous_lock synchronouslock(pbufferitem->m_pmutex);

            slGraphics.unlock();

            set_destroying_flag();

         }

      }

      //return 

      ::windowing::window_base::set_finish();

   }


   //   void window::prodevian_stop()
   //   {
   //
   //      auto pgraphicsthread = m_pgraphicsthread;
   //
   //      if (::is_set(pgraphicsthread) && ::is_set(m_pgraphics))
   //      {
   //
   //         {
   //
   //            _synchronous_lock slGraphics(m_pgraphics->synchronization());
   //
   //            auto pbufferitem = m_pgraphics->get_buffer_item();
   //
   //            _synchronous_lock synchronouslock(pbufferitem->m_pmutex);
   //
   //            slGraphics.unlock();
   //
   //            //pgraphicsthread->user_interaction() = nullptr;
   //
   //            //pgraphicsthread->m_pimpl = nullptr;
   //
   //            pgraphicsthread->set_finish();
   //
   //         }
   //
   //         //{
   //
   //         //   _synchronous_lock synchronouslock(this->synchronization());
   //
   //         //   _synchronous_lock slGraphics(m_pgraphics->synchronization());
   //
   //         //   m_pgraphicsthread);
   //
   //         //}
   //
   //      }
   //
   //   }


   //   void window::prodevian_update_screen()
   //   {
   //
   //
   //      //_001UpdateScreen();
   //
   //      //return true;
   //
   //   }


      //void window::set_handle(::windowing::window * pwindow)
      //{

      //   //if (get_handle() != nullptr)
      //   //{

      //   //   oswindow_erase(get_handle());

      //   //   oswindow_erase_impl(this);

      //   //}

      //   //get_handle() = oswindow;

      //   //if (oswindow != nullptr)
      //   //{

      //   //   oswindow_assign(oswindow, this);

      //   //   _001BaseWndInterfaceMap();

      //   //}

      //}


      //void window::attach(::windowing::window * pwindowNew)
      //{

      //   ASSERT(get_handle() == nullptr);

      //   ASSERT(oswindow_interaction(oswindowNew) == nullptr);

      //   if(oswindowNew == nullptr)
      //   {

      //      return false;

      //   }

      //   //set_handle(oswindowNew);

      //   ASSERT(psystem->ui_from_handle(get_handle()) == user_interaction());

      //   return true;

      //}


   //void window::destroy()
   //{

   //   //return ::windowing::window_base::destroy();

   //}


   //oswindow window::detach()
   //{

   //   ::windowing::window * pwindow = get_handle();

   //   if(oswindow != nullptr)
   //   {

   //      set_handle(nullptr);

   //   }

   //   return oswindow;

   //}


   //oswindow window::get_oswindow() const
   //{
   //    
   //   if(!m_pwindow)
   //   {
   //      
   //      return nullptr;
   //      
   //   }

   //   return (oswindow) oswindow();

   //}


   bool window::is_composite()
   {

      return user_interaction()->m_ewindowflag & e_window_flag_composite;

   }


   ::graphics::graphics* window::get_window_graphics()
   {

      return m_pgraphicsgraphics;

   }


   ::user::element* window::get_keyboard_focus()
   {

      if (!has_keyboard_focus())
      {

         return nullptr;

      }

      return m_pacmeuserinteractionKeyboardFocus;

   }


   void window::on_prio_message_set_focus(::message::message* pmessage)
   {

      ::pointer<::message::set_keyboard_focus> psetkeyboardfocus(pmessage);

      //      on_final_set_keyboard_focus();
      //
      //if (user_interaction()->m_ewindowflag & e_window_flag_focus)
      //{
      //   
      //   return;
      //
      //}
      //
      //user_interaction()->m_ewindowflag |= e_window_flag_focus;

      ::cast < ::user::interaction > puserinteractionFocus = m_pacmeuserinteractionKeyboardFocus;

      if (puserinteractionFocus)
      {

         puserinteractionFocus->on_set_keyboard_focus();

      }

      //on_final_set_keyboard_focus();

   }


   void window::set_mouse_capture(::user::interaction* puserinteraction)
   {

      this->set_mouse_capture();

      m_pacmeuserinteractionMouseCapture = puserinteraction;

   }


   bool window::defer_release_mouse_capture(::user::interaction* puserinteraction)
   {

      //if (puserinteraction != m_puserinteractionMouseCapture)
      //{

      //   return false;

      //}

      this->defer_release_mouse_capture();

      //if (!this->defer_release_mouse_capture())
      //{

      //   return false;

      //}

      m_pacmeuserinteractionMouseCapture.release();

      return true;

   }


   bool window::on_keyboard_focus(::user::interaction_base* pfocus)
   {

      auto pwindowing = windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         character_count iBeg = 0;

         character_count iEnd = 0;

         pfocus->get_text_selection(iBeg, iEnd);

         string strText;

         strText = pfocus->m_textproperty.as_text();

         auto pwindowing = windowing();

         auto ptexteditorinterface = pwindowing->get_text_editor_interface();

         ptexteditorinterface->set_editor_selection(iBeg, iEnd);

         ptexteditorinterface->set_editor_text(strText);

         ptexteditorinterface->show_software_keyboard();

      }

      return true;

   }


   ////   void window::on_final_set_keyboard_focus(::message::set_keyboard_focus * psetkeyboardfocus)
   //void window::on_final_set_keyboard_focus()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   //if (m_pacmeuserinteractionKeyboardFocusRequest)
   //   //{

   //   //   if (m_pacmeuserinteractionKeyboardFocusRequest == m_pacmeuserinteractionToKillKeyboardFocus)
   //   //   {

   //   //      m_pacmeuserinteractionToKillKeyboardFocus.release();

   //   //   }

   //      information() << "on_final_set_keyboard_focus : "
   //         << ::string(::type(m_pacmeuserinteractionKeyboardFocusRequest.m_p));

   //      if (m_pacmeuserinteractionKeyboardFocusRequest != m_pacmeuserinteractionKeyboardFocus)
   //      {

   //         information() << "on_final_set_keyboard_focus : (2)";

   //         auto puserinteractionKeyboardFocusOld = m_pacmeuserinteractionKeyboardFocus;

   //         m_pacmeuserinteractionKeyboardFocus = m_pacmeuserinteractionKeyboardFocusRequest;

   //         m_pacmeuserinteractionKeyboardFocusRequest = nullptr;

   //         auto puserinteractionKeyboardFocus = m_pacmeuserinteractionKeyboardFocus;

   //         if (puserinteractionKeyboardFocusOld)
   //         {

   //            puserinteractionKeyboardFocusOld->on_kill_keyboard_focus();

   //         }

   //         if (puserinteractionKeyboardFocus)
   //         {

   //            synchronouslock.unlock();

   //            puserinteractionKeyboardFocus->on_set_keyboard_focus();

   //         }

   //         on_set_focus_to_child();

   //      }
   //      //         else if(aaa_m_pacmeuserinteractionKeyboardFocus)
   //      //         {
   //      //
   //      //            synchronouslock.unlock();
   //      //
   //      //            aaa_m_pacmeuserinteractionKeyboardFocus->on_set_keyboard_focus();
   //      //
   //      //         }

   //   }
   //   //      else
   //   //      {
   //   //
   //   //         m_pacmeuserinteractionToKillKeyboardFocus = aaa_m_pacmeuserinteractionKeyboardFocus;
   //   //
   //   //         synchronouslock.unlock();
   //   //
   //   //         aaa_on_final_kill_keyboard_focus();
   //   //
   //   //      }

   //}


   bool window::keyboard_focus_OnKillFocus(::oswindow oswindowNew)
   {

      informationf("::android::window::keyboard_focus_OnKillFocus() (1) \n");

      //      auto pwindowing = windowing();
      //
      //      auto ptexteditorinterface = pwindowing->get_text_editor_interface();
      //
      //      if (::is_set(ptexteditorinterface))
      //      {
      //
      //         ptexteditorinterface->hide_software_keyboard();
      //
      //      }


      //      _synchronous_lock synchronouslock(this->synchronization());
      //
      //      auto puserinteractionKeyboardFocus = aaa_m_pacmeuserinteractionKeyboardFocus;
      //
      //      if (puserinteractionKeyboardFocus)
      //      {
      //
      //         aaa_m_pacmeuserinteractionKeyboardFocus.release();
      //
      //         synchronouslock.unlock();
      //
      //         puserinteractionKeyboardFocus->on_kill_keyboard_focus();
      //
      //      }

      return true;

   }

   bool window::keyboard_focus_OnChildKillFocus()
   {

      informationf("::android::window::keyboard_focus_OnChildKillFocus() (2) \n");

      auto pwindowing = windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         ptexteditorinterface->hide_software_keyboard();

      }

      return true;

   }


   //void window::on_message_set_focus(::message::message * pmessage)
   //{

   //   ::pointer<::message::set_keyboard_focus> psetkeyboardfocus(pmessage);

   //   //if (!(user_interaction()->m_ewindowflag & e_window_flag_focus))
   //   //{

   //   //   return;

   //   //}

   //   //user_interaction()->m_ewindowflag -= e_window_flag_focus;

   //   if (psetkeyboardfocus->m_oswindow != oswindow())
   //   {

   //      psetkeyboardfocus->m_bRet = true;

   //      ::output_debug_string("set keyboard focus isn't setting keyboard focus to this windows");

   //      return;

   //   }

   //   //on_final_set_keyboard_focus();

   //   ::cast < ::user::interaction > puserinteractionFocus = m_pacmeuserinteractionKeyboardFocus;

   //   if (puserinteractionFocus)
   //   {

   //      puserinteractionFocus->on_set_keyboard_focus();

   //   }

   //}


   void window::on_message_kill_focus(::message::message* pmessage)
   {

      ::pointer<::message::kill_keyboard_focus> pkillkeyboardfocus(pmessage);

      //if (!(user_interaction()->m_ewindowflag & e_window_flag_focus))
      //{

      //   return;

      //}

      //user_interaction()->m_ewindowflag -= e_window_flag_focus;

      if (pkillkeyboardfocus->m_oswindowNew
         == pkillkeyboardfocus->m_oswindow)
      {

         pkillkeyboardfocus->m_bRet = true;

         ::output_debug_string("kill keyboard focus that isn't killing keyboard focus");

         return;

      }

      ::cast < ::user::interaction > puserinteractionFocus = m_pacmeuserinteractionKeyboardFocus;

      if (puserinteractionFocus)
      {

         puserinteractionFocus->on_kill_keyboard_focus();

      }

      //on_final_kill_keyboard_focus();

   }

   //void window::aaa_on_final_kill_keyboard_focus(::message::kill_keyboard_focus * pkillkeyboardfocus)

   //void window::on_final_kill_keyboard_focus()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   information() << "on_final_kill_keyboard_focus";

   //   auto puserinteractionKeyboardFocus = m_pacmeuserinteractionKeyboardFocus;

   //   m_pacmeuserinteractionKeyboardFocusRequest.release();

   //   //aaa_m_pacmeuserinteractionKeyboardFocus.release();

   //   synchronouslock.unlock();

   //   if (puserinteractionKeyboardFocus)
   //   {

   //      puserinteractionKeyboardFocus->on_kill_keyboard_focus();

   //   }

   //}


   //void window::impl_set_keyboard_focus(::user::interaction * puserinteractionFocusNew)
   //{

   //   ::cast < ::user::interaction > puserinteractionFocusOld = m_pacmeuserinteractionKeyboardFocus;

   //   if (puserinteractionFocusOld == puserinteractionFocusNew)
   //   {

   //      return;

   //   }

   //   //auto oswindow = get_handle();

   //   //auto oswindowPrevious = ::set_keyboard_focus(oswindow);

   //   window_set_keyboard_focus();

   //   m_pacmeuserinteractionKeyboardFocus = puserinteractionFocusNew;

   //   try
   //   {

   //      if (::is_set(puserinteractionFocusOld))
   //      {

   //         if (puserinteractionFocusOld->m_bFocus)
   //         {

   //            puserinteractionFocusOld->send_message(e_message_kill_focus);

   //         }

   //         puserinteractionFocusOld->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      if (::is_set(puserinteractionFocusOld))
   //      {

   //         if (!puserinteractionFocusOld->m_bFocus)
   //         {

   //            puserinteractionFocusOld->send_message(e_message_set_focus);

   //         }

   //         puserinteractionFocusOld->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   //return true;

   //}


   //void window::impl_erase_keyboard_focus(::user::interaction * puserinteractionFocusErase)
   //{

   //   if (::is_null(puserinteractionFocusErase))
   //   {

   //      return;

   //   }

   //   ::cast < ::user::interaction > puserinteractionFocusKillFocus = m_pacmeuserinteractionKeyboardFocus;

   //   if (puserinteractionFocusKillFocus != puserinteractionFocusErase)
   //   {

   //      return;

   //   }

   //   m_pacmeuserinteractionKeyboardFocus = nullptr;

   //   try
   //   {

   //      if (::is_set(puserinteractionFocusKillFocus))
   //      {

   //         if (puserinteractionFocusKillFocus->m_bFocus)
   //         {

   //            puserinteractionFocusKillFocus->send_message(e_message_kill_focus);

   //         }

   //         puserinteractionFocusKillFocus->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   //return true;

   //}


   // void window::aaa_impl_clear_keyboard_focus()
   // {

   //    ::user::interaction * puserinteractionFocusKillFocus = aaa_m_pacmeuserinteractionKeyboardFocus;

   //    aaa_m_pacmeuserinteractionKeyboardFocus = nullptr;

   //    try
   //    {

   //       if (::is_set(puserinteractionFocusKillFocus))
   //       {

   //          if (puserinteractionFocusKillFocus->m_bFocus)
   //          {

   //             puserinteractionFocusKillFocus->send_message(e_message_kill_focus);

   //          }

   //          puserinteractionFocusKillFocus->set_need_redraw();

   //       }

   //    }
   //    catch (...)
   //    {

   //    }

   //    //return true;

   // }


   void window::set_keyboard_focus(::acme::user::interaction* pacmeuserinteraction)
   {

      ::cast < ::user::interaction > puserinteraction = pacmeuserinteraction;

      if (!puserinteraction)
      {

         ::windowing::window_base::set_keyboard_focus(pacmeuserinteraction);

         return;

      }

      //if (::is_null(puserinteraction))
      //{

      //   //aaa_impl_clear_keyboard_focus();

      //   clear_keyboard_focus();

      //   return;

      //}

      auto pinteraction = user_interaction();

      if (::is_null(pinteraction))
      {

         return;

      }

      if (!pinteraction->is_ascendant_of(puserinteraction, true))
      {

         return;

      }

      ::cast < ::user::interaction > puserinteractionKeyboardFocusOld = m_pacmeuserinteractionKeyboardFocus;

      if (puserinteractionKeyboardFocusOld != puserinteraction)
      {

         ::acme::windowing::window::set_keyboard_focus(puserinteraction);

         if (::is_set(puserinteractionKeyboardFocusOld))
         {

            puserinteractionKeyboardFocusOld->on_kill_keyboard_focus();

         }

         if (::is_set(puserinteraction))
         {


            if (has_keyboard_focus())
            {

               puserinteraction->on_set_keyboard_focus();

            }
            else
            {

               set_keyboard_focus();

            }

         }

      }

      // impl_set_keyboard_focus(puserinteraction);

   }


   //void window::erase_keyboard_focus(::user::interaction * puserinteraction)
   //{

   //   if (puserinteraction == nullptr)
   //   {

   //      impl_erase_keyboard_focus(nullptr);

   //      return;

   //   }

   //   if (puserinteraction == user_interaction())
   //   {

   //      impl_erase_keyboard_focus(puserinteraction);

   //      return;

   //   }

   //   ::user::interaction * pinteraction = user_interaction();

   //   if (pinteraction == nullptr)
   //   {

   //      return;

   //   }

   //   if (!user_interaction()->is_ascendant_of(puserinteraction, true))
   //   {

   //      return;

   //   }

   //   impl_erase_keyboard_focus(puserinteraction);

   //   //return true;

   //}


   //void window::clear_keyboard_focus(::user::interaction * puserinteractionGainingFocusIfAny)
   //{

   //   auto puserinteraction = user_interaction();

   //   if (!puserinteraction)
   //   {

   //      throw ::exception(error_failed);

   //   }

   //   auto pwindow = puserinteraction->window();

   //   if (!pwindow)
   //   {

   //      throw ::exception(error_failed);

   //   }

   //   auto pwindowing = pwindow->windowing();

   //   if (!pwindowing)
   //   {

   //      throw ::exception(error_failed);

   //   }

   //   //::windowing::window* pwindowGainingFocusIfAny = nullptr;

   //   //if (pprimitiveimplGainingFocusIfAny)
   //   //{

   //   //   pwindowGainingFocusIfAny = pprimitiveimplGainingFocusIfAny->window();

   //   //}

   //   if (m_pacmeuserinteractionKeyboardFocusRequest == m_pacmeuserinteractionKeyboardFocus)
   //   {

   //      m_pacmeuserinteractionKeyboardFocusRequest.release();

   //   }

   //   m_pacmeuserinteractionToKillKeyboardFocus = m_pacmeuserinteractionKeyboardFocus;

   //   on_final_kill_keyboard_focus();

   //   //pwindowing->aaa_clear_keyboard_focus(pwindowGainingFocusIfAny);

   //   //auto puserinteraction = user_interaction();

   //   //if (::is_null(puserinteraction))
   //   //{

   //   //   return false;

   //   //}

   //   //::user::interaction * pinteractionHost = puserinteraction->get_host_user_interaction();

   //   //if (::is_null(pinteractionHost))
   //   //{

   //   //   return false;

   //   //}

   //   //auto pimplHost = pinteractionHost->m_pimpl;

   //   //if (::is_null(pimplHost))
   //   //{

   //   //   return false;

   //   //}

   //   //pimplHost->aaa_impl_clear_keyboard_focus();

   //   //return false;

   //}


   //void window::post_message(::message::message * pmessage)
   //{

   //   //if (m_puserthread)
   //   //{

   //   //   _synchronous_lock synchronouslock(m_puserthread->synchronization());

   //   //   m_puserthread->m_messagebasea.add(pmessage);

   //   //   m_puserthread->kick_idle();

   //   //   return true;

   //   //}

   //   //user_interaction()->post_procedure(__routine([this, pmessage]()
   //   //{

   //   // return user_interaction()->message_handler(pmessage);

   //   //}));


   //   //return 

   //   user_interaction()->post_message(pmessage);

   //   //return true;

   //}


   void window::redraw_add(::particle* pparticle)
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      m_particleaRedraw.add(pparticle);

   }


   void window::redraw_erase(::particle* pparticle)
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      m_particleaRedraw.erase(pparticle);

   }


   bool window::has_redraw()
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      return m_particleaRedraw.has_elements();

   }


   ::particle* window::mutex_redraw()
   {

      if (m_pmutexRedraw == nullptr)
      {

         __øconstruct(m_pmutexRedraw);

      }

      return m_pmutexRedraw;

   }


   bool window::has_pending_graphical_update()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_particleaRedraw.has_elements())
         {

            return true;

         }

      }

      return false;

   }


   void window::on_after_graphical_update()
   {


      //#ifdef __ANDROID__
      //
      //      operating_system_driver::get()->m_bRedraw = true;
      //
      //#endif


   }


   //   void window::_window_request_presentation_locked()
   //   {
   //
   //      _window_request_presentation_locked();
   //
   //   }
   //
   //
   //   void window::_window_request_presentation_unlocked()
   //   {
   //
   //      if (::is_null(user_interaction()))
   //      {
   //
   //         return;
   //
   //      }
   //
   //      // Request / Incoming changes / Prepare Internal Buffer
   //      auto & stateOutput = user_interaction()->const_layout().design();
   //
   //      // Current/Previous Window State
   //      auto & stateWindow = user_interaction()->const_layout().window();
   //
   //      if (stateOutput == stateWindow)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      //information() << "Design.state != Window.state";
   //
   //      auto eactivationOutput = stateOutput.activation();
   //
   //      auto eactivationWindow = stateWindow.activation();
   //
   //      ::string_stream stringstreamUnchanged;
   //
   //      if (eactivationOutput != eactivationWindow)
   //      {
   //
   //         //information() << "Design.activation != Window.activation " << (iptr) eactivationOutput.m_eenum << ", " << (iptr) eactivationWindow.m_eenum;
   //
   //      }
   //      else
   //      {
   //
   //         stringstreamUnchanged << ".activation:" << eactivationOutput;
   //
   //      }
   //
   //      auto edisplayOutput = stateOutput.display();
   //
   //      auto edisplayWindow = stateWindow.display();
   //
   //      if (edisplayOutput != edisplayWindow)
   //      {
   //
   //         //information() << "Design.display != Window.display " << edisplayOutput << ", " << edisplayWindow;
   //
   //      }
   //      else
   //      {
   //
   //         stringstreamUnchanged << ".display:" << edisplayOutput;
   //
   //      }
   //
   //      auto pointOutput = stateOutput.origin();
   //
   //      auto pointWindow = stateWindow.origin();
   //
   //      if (pointOutput != pointWindow)
   //      {
   //
   //         //information() << "Design.point != Window.point " << pointOutput << ", " << pointWindow;
   //
   //      }
   //      else
   //      {
   //
   //         stringstreamUnchanged << ".origin:" << pointOutput;
   //
   //      }
   //
   //      auto sizeOutput = stateOutput.size();
   //
   //      auto sizeWindow = stateWindow.size();
   //
   //      if (sizeOutput != sizeWindow)
   //      {
   //
   //         //information() << "Design.size != Window.size " << sizeOutput << ", " << sizeWindow;
   //
   //      }
   //      else
   //      {
   //
   //         stringstreamUnchanged << ".size:" << sizeOutput;
   //
   //      }
   //
   //      auto zOutput = stateOutput.zorder();
   //
   //      auto zWindow = stateWindow.zorder();
   //
   //      if (zOutput != zWindow)
   //      {
   //
   //         //information() << "Design.zorder != Window.zorder " << zOutput << ", " << zWindow;
   //
   //      }
   //      else
   //      {
   //
   //         stringstreamUnchanged << ".zorder:" << zOutput;
   //
   //      }
   //
   //      if (stringstreamUnchanged.as_string().has_character())
   //      {
   //
   //         //information() << "==" << stringstreamUnchanged.as_string();
   //
   //      }
   //
   //      bool shouldGetVisible = ::is_screen_visible(edisplayOutput);
   //
   //      if (sizeOutput.is_empty())
   //      {
   //
   //         information() << "window_show rectangleUi isEmpty";
   //
   //         return;
   //
   //      }
   //
   //      bool bWindowVisible = is_window_visible();
   //
   //      __keep_flag_on(user_interaction()->layout().m_eflag, ::user::interaction_layout::flag_apply_visual);
   //
   //      //unsigned int uFlags = 0;
   //
   //      //bool bLayered = GetExStyle() & WS_EX_LAYERED;
   //
   //      //if (bLayered)
   //      {
   //
   //         //uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
   //
   //      }
   //      //else
   //      //{
   //
   //      //   uFlags |= SWP_ASYNCWINDOWPOS  | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
   //
   //      //}
   //
   //      //if (eactivationOutput & ::user::e_activation_no_activate)
   //      //{
   //
   //      //   uFlags |= SWP_NOACTIVATE;
   //
   //      //}
   //
   //      // if GNOME
   //      // if Xorg
   //      // if Wayland
   //
   //   //#if !defined(LINUX)
   //
   //         //if(m_sizeDrawn != sizeOutput)
   //         //{
   //
   //         //   informationf("blank borders (1), drawing extrapoation (1) or cut border (1)??\n");
   //
   //         //}
   //
   //         //sizeOutput = m_sizeDrawn;
   //
   //      bool bSize = true;
   //
   //      if (sizeWindow == sizeOutput)
   //      {
   //
   //         bSize = false;
   //
   //         //uFlags |= SWP_NOSIZE;
   //
   //      }
   //      else
   //      {
   //
   //         //uFlags |= SWP_ASYNCWINDOWPOS | SWP_FRAMECHANGED | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
   //         ////uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
   //         ////uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOCOPYBITS;
   //
   //      }
   //
   //      bool bMove = true;
   //
   //      if (pointWindow == pointOutput)
   //      {
   //
   //         bMove = false;
   //
   //         //uFlags |= SWP_NOMOVE;
   //
   //      }
   //
   //      //#endif
   //
   //      bool bVisibilityChange = is_different(bWindowVisible, shouldGetVisible);
   //
   //      bool bShow = false;
   //
   //      bool bHide = false;
   //
   //      if (bVisibilityChange)
   //      {
   //
   //         if (shouldGetVisible)
   //         {
   //
   //            bShow = true;
   //
   //         }
   //         else
   //         {
   //
   //            bHide = true;
   //
   //         }
   //
   //      }
   //      else
   //      {
   //
   //         if (shouldGetVisible)
   //         {
   //
   //            bShow = true;
   //
   //         }
   //
   //      }
   //
   //      //if (eactivationOutput & ::user::e_activation_no_activate)
   //      //{
   //
   //      //   uFlags |= SWP_NOACTIVATE;
   //
   //      //}
   //
   //      bool bZ = zOutput.is_change_request();
   //
   //
   //
   //      //if (!bZ)
   //      //{
   //
   //      //   uFlags |= SWP_NOZORDER;
   //
   //      //}
   //
   //      string strType = ::type(user_interaction()).name();
   //
   //      if (strType.contains("font_format"))
   //      {
   //
   //         information() << "font_format going to gather Z-Ordering information";
   //
   //      }
   //
   //      if (!user_interaction())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      ::zorder zorderNew = (bZ ? zOutput : ::zorder());
   //
   //      //      if (edisplayWindow == e_display_zoomed)
   //      //      {
   //      //
   //      //         if (edisplayOutput != e_display_zoomed)
   //      //         {
   //      //
   //      //            auto puserinteraction = user_interaction();
   //      //
   //      //            if (puserinteraction)
   //      //            {
   //      //
   //      //               puserinteraction->_001OnExitZoomed();
   //      //
   //      //            }
   //      //
   //      //         }
   //      //
   //      //      }
   //
   //            //int iVisibilityChageBefore = (is_ubunt() && edisplayOutput == e_display_zoomed);
   //
   //      int iVisibilityChageBefore = true;
   //
   //      if (iVisibilityChageBefore) {
   //         if (edisplayOutput != edisplayWindow)
   //            //&& !::conditional(bLayered, bHasSetWindowPosition)
   //            //)
   //         {
   //
   //            //#ifdef WINDOWS
   //            //
   //            //         bool bShowOutput = windows_show_window(edisplayOutput, eactivationOutput);
   //            //
   //            //         bool bShowWindow = windows_show_window(edisplayWindow, eactivationWindow);
   //            //
   //            //         if (is_different(bShowOutput, bShowWindow))
   //            //#endif
   //            //         {
   //
   //            user_interaction()->_window_show_change_visibility_unlocked();
   //
   //            //}
   //
   //         }
   //      }
   //
   //      //if(is_ubunt())
   //      {
   //
   //         if (edisplayOutput == e_display_zoomed)
   //         {
   //
   //            bMove = true;
   //            bSize = true;
   //
   //         }
   //
   //      }
   //
   //      //#endif
   //            //user_interaction()->_on_show_window();
   //      //
   //      //               if (is_different(user_interaction()->m_ewindowflag & e_window_flag_on_show_window_visible,
   //      //            user_interaction()->is_this_visible())
   //      //            || is_different(user_interaction()->m_ewindowflag & e_window_flag_on_show_window_screen_visible,
   //      //               user_interaction()->is_window_screen_visible()))
   //      //         {
   //      //
   //      //            user_interaction()->m_ewindowflag.set(e_window_flag_on_show_window_visible, user_interaction()->is_this_visible());
   //      //
   //      //            user_interaction()->m_ewindowflag.set(e_window_flag_on_show_window_screen_visible, user_interaction()->is_window_screen_visible());
   //      //
   //      //            user_interaction()->_on_show_window();
   //      //
   //      //         }
   //
   //
   //      //bool bHasSetWindowPosition = false;
   //
   //      if (shouldGetVisible
   //         //#ifdef WINDOWS_DESKTOP
   //           //    && !bLayered
   //         //#endif
   //         && (
   //            //#ifdef WINDOWS_DESKTOP
   //            //               !bLayered
   //            //#else
   //                           //(uFlags & (SWP_NOMOVE | SWP_NOSIZE)) != (SWP_NOMOVE | SWP_NOSIZE)
   //            //#endif
   //            bMove
   //            || bSize
   //            || bVisibilityChange
   //            || bZ
   //            )
   //         )
   //      {
   //
   //         string strType = ::type(user_interaction()).name();
   //
   //         if (strType.contains("font_format"))
   //         {
   //
   //            information() << "font_format going to SetWindowPos";
   //
   //         }
   //         else if (strType.contains("textformat"))
   //         {
   //
   //            information() << "text_format going to SetWindowPos";
   //
   //         }
   //
   //         // Commented on Windows
   //         //if(user_interaction()->m_ewindowflag & e_window_flag_postpone_visual_update)
   //         //{
   //
   //         //   m_bEatMoveEvent = !(uFlags & SWP_NOMOVE) || !(uFlags & SWP_NOSIZE);
   //
   //         //   m_bEatSizeEvent = !(uFlags & SWP_NOSIZE);
   //
   //         //}
   //
   //         //if(user_interaction()->m_ewindowflag & e_window_flag_postpone_visual_update)
   //         //{
   //
   //         //   m_bPendingRedraw = true;
   //
   //         //}
   //         // END Commented on Windows
   //
   //         ::int_point pointBottomRight = pointOutput + sizeOutput;
   //
   //         //informationf("SetWindowPos bottom_right " + as_string(pointBottomRight.x()) + ", " + as_string(pointBottomRight.y()) + "\n");
   //
   //   //#if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)
   //
   //            //if (sizeOutput.cx() > m_sizeDrawn.cx() || sizeOutput.cy() > m_sizeDrawn.cy())
   //            // if (sizeOutput != m_sizeDrawn)
   //            // {
   //
   //            //    user_interaction()->set_need_layout();
   //
   //            //    //user_interaction()->set_need_redraw();
   //
   //            //    user_interaction()->post_redraw();
   //
   //            // }
   //            // else
   //         {
   //               _set_window_position_unlocked(
   //               zorderNew,
   //               pointOutput.x(),
   //               pointOutput.y(),
   //               sizeOutput.cx(),
   //               sizeOutput.cy(),
   //               eactivationOutput, !bZ, !bMove, !bSize, edisplayOutput);
   //
   //            m_sizeSetWindowSizeRequest = sizeOutput;
   //
   //         }
   //
   //         //::SetWindowPos(get_handle(), oswindowInsertAfter,
   //         //   pointOutput.x(), pointOutput.y(),
   //         //   sizeOutput.cx(), sizeOutput.cy(),
   //         //   uFlags);
   //
   //   //#endif
   //
   //         if (g_pointLastBottomRight != pointBottomRight)
   //         {
   //
   //            //sinformation() << "::windowing::window::do_graphics Different Bottom Right design size" << user_interaction()->const_layout().design().size();
   //
   //            g_pointLastBottomRight = pointBottomRight;
   //
   //         }
   //
   //         zOutput.clear_request();
   //
   //         m_bOkToUpdateScreen = true;
   //
   //      }
   //
   //      if (!iVisibilityChageBefore) {
   //
   //         if (edisplayOutput != edisplayWindow)
   //            //&& !::conditional(bLayered, bHasSetWindowPosition)
   //            //)
   //         {
   //
   //            //#ifdef WINDOWS
   //            //
   //            //         bool bShowOutput = windows_show_window(edisplayOutput, eactivationOutput);
   //            //
   //            //         bool bShowWindow = windows_show_window(edisplayWindow, eactivationWindow);
   //            //
   //            //         if (is_different(bShowOutput, bShowWindow))
   //            //#endif
   //            //         {
   //
   //            user_interaction()->_window_show_change_visibility_unlocked();
   //
   //            //}
   //
   //         }
   //
   //      }
   //
   //      if (eactivationOutput & ::user::e_activation_set_foreground)
   //      {
   //
   //         //throw ::exception(todo);
   //         //user_interaction()->set();
   //
   //         _set_foreground_window_unlocked();
   //
   //      }
   //
   //      if (eactivationOutput & ::user::e_activation_set_active)
   //      {
   //
   //         //throw ::exception(todo);
   //         ///user_interaction()->XXXSetActiveWindow();
   //
   //         _set_active_window_unlocked();
   //
   //      }
   //
   //      if (!user_interaction())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      user_interaction()->set_display(user_interaction()->const_layout().design().display(), e_layout_window);
   //
   //      user_interaction()->reset_pending(e_layout_design);
   //
   //      user_interaction()->set_display(edisplayOutput, e_layout_design);
   //
   //      ::windowing::window * pwindowFocus = nullptr;
   //
   //      ::windowing::window * pwindowImpl = nullptr;
   //
   //      ::windowing::window * pimplFocus = nullptr;
   //
   //      if (has_pending_focus() && user_interaction() != nullptr && user_interaction()->is_window_visible())
   //      {
   //
   //         auto psession = session();
   //
   //         auto pimplFocus = psession->m_puserinteractionPendingFocus2;
   //
   //         psession->m_puserinteractionPendingFocus2 = nullptr;
   //
   //         auto pwindowing = windowing();
   //
   //         ::oswindow oswindow = pimplFocus->oswindow();
   //
   //         if (pimplFocus == this)
   //         {
   //
   //            informationf("optimized out a set_keyboard_focus");
   //
   //         }
   //         else
   //         {
   //
   //            user_interaction()->set_keyboard_focus();
   //
   //         }
   //
   //      }
   //
   //      user_interaction()->m_bVisualChanged = true;
   //
   //      user_interaction()->check_transparent_mouse_events();
   //
   //   }


   //   void window::on_visual_applied()
   //   {
   //
   //   }


   void window::ShowWindow(const ::e_display& edisplay)
   {

      //return false;


   }


   //void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{


   //}


   void window::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

      on_configuration_change(user_interaction());

   }


   void window::on_configuration_change(::user::interaction_base* pprimitiveSource)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (auto& puserinteraction : m_userinteractionaHideOnConfigurationChange.m_interactiona)
      {

         if (puserinteraction->is_window_screen_visible())
         {

            puserinteraction->hide();

            puserinteraction->set_need_redraw();

            puserinteraction->post_redraw();

         }

      }

   }


   //   void window::_window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation)
   //   {
   //
   //      //m_puserthread->post_procedure([this, edisplay, useractivation]()
   //        // {
   //
   //      if (!user_interaction())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      __keep_flag_on(user_interaction()->layout().m_eflag, ::user::interaction_layout::flag_show_window);
   //
   //      if (edisplay == e_display_iconic)
   //      {
   //
   //         if (useractivation == ::user::e_activation_no_activate)
   //         {
   //
   //            _show_window_unlocked(edisplay, useractivation);
   //
   //         }
   //         else
   //         {
   //
   //            _show_window_unlocked(edisplay, useractivation);
   //
   //         }
   //
   //      }
   //      else
   //      {
   //
   //         _show_window_unlocked(edisplay, useractivation);
   //
   //      }
   //
   //      if (user_interaction())
   //      {
   //
   //         user_interaction()->set_activation(::user::e_activation_default, e_layout_design);
   //
   //      }
   //
   //         //});
   //
   //   }


      //void window::_001OnRedraw(::message::message * pmessage)
      //{

      //   user_interaction()->prodevian_redraw(pmessage->m_wparam & 1);

      //}


   //   void window::_001OnDoShowWindow(::message::message * pmessage)
   //   {
   //
   //      user_interaction()->_window_show_change_visibility();
   //
   //   }


   //   void window::_001OnApplyVisual(::message::message * pmessage)
   //   {
   //
   //      if (!user_interaction())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      string strType = ::type(user_interaction()).name();
   //
   //      if (strType.case_insensitive_contains("filemanager"))
   //      {
   //
   //         information() << "filemanager apply visual";
   //
   //      }
   //
   //      if (user_interaction()->is_graphical())
   //      {
   //
   //         window_show();
   //
   //         //if (::is_set(m_puserthread))
   //         //{
   //
   //         //   m_puserthread->m_happeningApplyVisual.set_happening();
   //
   //         //}
   //
   //      }
   //
   //   }

   //                  auto pwindowing = windowing();
   //
   //                  if(pwindowing)
   //                  {
   //
   //                     auto pdisplay = pwindowing->display();
   //
   //                     if(pdisplay)
   //                     {
   //
   //                        auto pmonitor = pdisplay->get_best_monitor(rectangle);
   //
   //                        if(::is_set(pmonitor))
   //                        {
   //
   //                           auto rectangleBig = pmonitor->monitor_rectangle();
   //
   //                           auto rectangleSmall = rectangleBig;
   //
   //                           rectangleSmall.deflate(rectangleBig.width() / 10, rectangleBig.height() / 10);
   //
   //                           auto pointDesign = user_interaction()->const_layout().design().origin();
   //
   //                           if(rectangle.top() >= rectangleBig.top() && rectangle.top() <= rectangleSmall.top()
   //                           && rectangleRequest.top()>= rectangleBig.top() && rectangleRequest.top() <= rectangleSmall.top()
   //                           && rectangleRequest.top() < rectangle.top())
   //                           {
   //
   //                              pmonitor->set_workspace_rectangle_top(rectangle.top());
   //
   //                           }
   //
   //                           if(rectangle.left() >= rectangleBig.left() && rectangle.left() <= rectangleSmall.left()
   //                              && rectangleRequest.left()>= rectangleBig.left() && rectangleRequest.left() <= rectangleSmall.left()
   //                              && rectangleRequest.left() < rectangle.left())
   //                           {
   //
   //                              pmonitor->set_workspace_rectangle_left(rectangle.left());
   //
   //                           }
   //
   //                           if(rectangle.right() >= rectangleSmall.right() && rectangle.right() <= rectangleBig.right()
   //                              && rectangleRequest.right()>= rectangleSmall.right() && rectangleRequest.right() <= rectangleBig.right()
   //                              && rectangleRequest.right() > rectangle.right())
   //                           {
   //
   //                              pmonitor->set_workspace_rectangle_right(rectangle.right());
   //
   //                           }
   //
   //                           if(rectangle.bottom() >= rectangleSmall.bottom() && rectangle.bottom() <= rectangleBig.bottom()
   //                              && rectangleRequest.bottom()>= rectangleSmall.bottom() && rectangleRequest.bottom() <= rectangleBig.bottom()
   //                              && rectangleRequest.bottom() > rectangle.bottom())
   //                           {
   //
   //                              pmonitor->set_workspace_rectangle_bottom(rectangle.bottom());
   //
   //                           }
   //
   //                        }
   //
   //                     }
   //
   //                  }

      //         if(!user_interaction()->is_window_resizing()
   //             && !user_interaction()->is_window_repositioning()
   //             && !user_interaction()->is_window_docking())


   void window::on_configure(const ::int_rectangle& rectangle)
   {

      if (!user_interaction()->is_window_repositioning()
         && !user_interaction()->is_window_resizing()
         && !user_interaction()->is_window_docking())
      {

         user_interaction()->main_async()
            << [this, rectangle]()
            {

               _on_configure(rectangle);

            };

      }

   }


   void window::_on_configure(const ::int_rectangle& rectangle)
   {

      if (user_interaction()->const_layout().sketch().display() !=
         e_display_iconic)
      {

         auto rectangleRequest = user_interaction()->const_layout().design().parent_raw_rectangle();

         auto rectangleWindow = user_interaction()->const_layout().window().parent_raw_rectangle();

         if (rectangle != rectangleRequest)
         {

            information() << "on configure; setting to window rectangle : "
               << rectangle;

            auto point = rectangle.origin();

            auto size = rectangle.size();

            if (point != rectangleRequest.origin())
            {

               user_interaction()->set_position(point, ::user::e_layout_window);

               user_interaction()->set_position(point, ::user::e_layout_sketch);

               user_interaction()->set_reposition();

            }

            if (size != rectangleRequest.size())
            {

               user_interaction()->set_size(size, ::user::e_layout_window);

               user_interaction()->set_size(size, ::user::e_layout_sketch);

               user_interaction()->set_need_layout();

            }

            user_interaction()->set_need_redraw();

            user_interaction()->post_redraw();

         }
         else if (rectangle != rectangleWindow)
         {

            information()
               << "on configure; setting to window rectangle (2) : "
               << rectangle;

            if (rectangle.origin() != rectangleWindow.origin())
            {

               user_interaction()->set_position(rectangle.origin(),
                  ::user::e_layout_window);

            }

            if (rectangle.size() != rectangleWindow.size())
            {

               user_interaction()->set_size(rectangle.size(), ::user::e_layout_window);

            }

         }

      }

   }

   //   void window::on_resize(const ::int_size & size)
   //   {
   //
   //      if (user_interaction()->const_layout().sketch().display() != e_display_iconic)
   //      {
   //
   //         //if (!placement_log()->has_recent(size)
   //         if(!user_interaction()->is_window_resizing()
   //             && !user_interaction()->is_window_repositioning()
   //             && !user_interaction()->is_window_docking())
   //         {
   //
   //            user_interaction()->post_procedure([this, size]()
   //            {
   //
   //               if(size != user_interaction()->const_layout().design().size())
   //               {
   //
   //                  information() << "on resize; setting to window size : " << size;
   //
   //                  user_interaction()->set_size(size, e_layout_window);
   //
   //                  user_interaction()->set_size(size, e_layout_sketch);
   //
   //                  int cx = user_interaction()->const_layout().sketch().size().width();
   //
   //                  int cy = user_interaction()->const_layout().sketch().size().height();
   //                  //         user_interaction()->layout().design().size() = user_interaction()->layout().window().size();
   //
   //
   //                  user_interaction()->set_need_layout();
   //
   //                  user_interaction()->set_need_redraw();
   //
   //                  user_interaction()->post_redraw();
   //
   //               }
   //               else if(size != user_interaction()->const_layout().window().size())
   //               {
   //
   //                  information() << "on reposition; setting to window size (2) : " << size;
   //
   //                  user_interaction()->set_size(size, e_layout_window);
   //
   //               }
   //
   //
   //            });
   //
   //         }
   //
   //      }
   //
   //   }


   void window::on_message_reposition(::message::message* pmessage)
   {

      user_interaction()->m_pinteractionScaler->on_display_change(user_interaction());

      if (m_bEatMoveEvent)
      {

         m_bEatMoveEvent = false;

         return;

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

      //      if (user_interaction()->layout().m_eflag)
      //      {
      //
      //         return;
      //
      //      }

      ::pointer<::message::reposition> preposition(pmessage);

      m_pointWindow = preposition->m_point;

      //      if(user_interaction()->m_ewindowflag & e_window_flag_postpone_visual_update)
      //      {
      //
      //         return;
      //
      //      }

      //      bool bLayered = user_interaction()->GetExStyle() & WS_EX_LAYERED;
      //
      //#ifndef WINDOWS_DESKTOP
      //
      //      bLayered = false;
      //
      //#endif
      //
      //      if(!bLayered)
      //      {
      //
      //         user_interaction()->layout().sketch().origin() = preposition->m_point;
      //
      //         user_interaction()->screen_origin() = preposition->m_point;
      //
      //      }

      //m_point = preposition->m_point;

      auto& layout = user_interaction()->const_layout();

      auto sketch_origin = layout.sketch().origin();

      auto window_origin = layout.window().origin();

      //information() << "window::on_message_reposition preposition->m_point " << preposition->m_point;

      //information() << "window::on_message_reposition window_origin " << window_origin;

      //information() << "window::on_message_reposition sketch_origin " << sketch_origin;

      //if(preposition->m_point.x() == 0)
      //{

      //  information() << "window::on_message_reposition x is zero";

      //}
      //user_interaction()->set_position(preposition->m_point, e_layout_window);

      if (!is_iconic())
      {


         if (!placement_log()->has_recent(preposition->m_point)
            && !user_interaction()->is_window_resizing()
            && !user_interaction()->is_window_repositioning()
            && !user_interaction()->is_window_docking())
         {

            information() << "window::on_message_reposition " << preposition->m_point;

            user_interaction()->set_position(preposition->m_point, ::user::e_layout_sketch);

            user_interaction()->set_reposition();

            user_interaction()->set_need_redraw();

            user_interaction()->post_redraw();

         }

      }

      //if (user_interaction()->layout().is_moving())
      //{

      // information() << "\nWindow is Moving :: on_message_move";

      //}

      //user_interaction()->layout().sketch().origin() = preposition->m_point;

      //if (user_interaction()->layout().sketch().display() != e_display_normal)
      //{

      // user_interaction()->display(e_display_normal);

      //}

      //user_interaction()->set_reposition();

      //user_interaction()->set_need_redraw();

      //user_interaction()->post_redraw();

      //}

      //on_window_configuration_change();

      //user_interaction()->set_timer(e_timer_configure_unlocked, 200_ms);

   }


   void window::on_message_size(::message::message* pmessage)
   {

      if (m_bEatSizeEvent)
      {

         m_bEatSizeEvent = false;

         return;

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (user_interaction()->layout().m_eflag)
      {

         return;

      }

      ::pointer<::message::size> psize(pmessage);

      m_sizeWindow = psize->m_size;

      //      bool bLayered = user_interaction()->GetExStyle() & WS_EX_LAYERED;
      //
      //#ifndef WINDOWS_DESKTOP
      //
      //      bLayered = false;
      //
      //#endif
      //
      //      if(!bLayered)
      //      {
      //
      //         user_interaction()->layout().window() = psize->m_size;
      //
      //      }

      //      if (user_interaction()->layout().sketch().size() != psize->m_size)
      //      {
      //
      //         user_interaction()->layout().sketch() = psize->m_size;
      //
      //         if (user_interaction()->layout().sketch().display() != e_display_normal)
      //         {
      //
      //            user_interaction()->display(e_display_normal);
      //
      //         }
      //
      //         user_interaction()->set_need_layout();
      //
      //         user_interaction()->set_need_redraw();
      //
      //         user_interaction()->post_redraw();
      //
      //      }

      //m_size = psize->m_size;

      //user_interaction()->set_size(psize->m_size, e_layout_window);
      //user_interaction()->set_size(psize->m_size, e_layout_window);

      //m_sizeSetWindowSizeRequest = psize->m_size;

      if (!placement_log()->has_recent(psize->m_size)
         && user_interaction()->is_this_screen_visible()
         && !user_interaction()->is_window_resizing()
         && !user_interaction()->is_window_repositioning()
         && !user_interaction()->is_window_docking())
      {

         information() << "window::on_message_size " << psize->m_size;

         user_interaction()->set_size(psize->m_size, ::user::e_layout_sketch);

         int cx = user_interaction()->const_layout().sketch().size().width();

         int cy = user_interaction()->const_layout().sketch().size().height();

         user_interaction()->set_need_layout();

         user_interaction()->set_need_redraw();

         user_interaction()->post_redraw();

         //
         //         user_interaction()->post_redraw();


         //if (user_interaction()->layout().is_moving())
         //{

         // information() << "\nWindow is Moving :: on_message_move";

         //}

         //user_interaction()->layout().sketch().origin() = preposition->m_point;

         //if (user_interaction()->layout().sketch().display() != e_display_normal)
         //{

         // user_interaction()->display(e_display_normal);

         //}

         //         user_interaction()->set_reposition();
         //
         //         user_interaction()->set_need_redraw();
         //
         //         user_interaction()->post_redraw();

      }

      //on_window_configuration_change();

      ///user_interaction()->set_timer(e_timer_configure_unlocked, 200_ms);

   }


   void window::_001OnDestroyWindow(::message::message* pmessage)
   {

      if (user_interaction() && ::type(user_interaction()).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

      if (m_bDestroyImplOnly)
      {

         destroy_impl_only();

      }
      else if (user_interaction())
      {

         user_interaction()->destroy_window();

         informationf("destroy_window");

      }

   }


   void window::show_software_keyboard(::user::element* pelement)
   {

      throw ::interface_only();

   }


   void window::hide_software_keyboard(::user::element* pelement)
   {

      //throw ::interface_only();

   }


   void window::non_top_most_upper_window_rects(::int_rectangle_array& recta)
   {

      //non_top_most_upper_window_rects(recta);

   }


   bool window::is_occluded()
   {

      ::int_rectangle_array recta;

      non_top_most_upper_window_rects(recta);

      ::int_rectangle rectangle;

      user_interaction()->window_rectangle(rectangle);

      ::int_rectangle rTest;

      for (auto& rHigher : recta)
      {

         if (rTest.intersect(rHigher, rectangle))
         {

            return true;

         }

      }

      return false;

   }


   void window::approximate_occlusion_rects(int_rectangle_array& raTest)
   {

      raTest.erase_all();

      ::int_rectangle_array ra;

      non_top_most_upper_window_rects(ra);

      if (ra.is_empty())
      {

         return;

      }

      ::int_rectangle rectangle;

      user_interaction()->window_rectangle(rectangle);

      for (auto& rHigher : ra)
      {

         ::int_rectangle rTest;

         if (rTest.intersect(rHigher, rectangle))
         {

            raTest.add(rTest);

         }

      }

      // First Exclude Full Intersections

   restartFullIntersectionExclusion:

      for (::collection::index i = 0; i < raTest.get_count(); i++)
      {

         for (::collection::index j = i + 1; j < raTest.get_count(); j++)
         {

            int iArea = raTest[i].area();

            int jArea = raTest[j].area();

            int iMinArea = maximum(iArea, jArea);

            if (raTest[i].intersection(raTest[j]).area() == iMinArea)
            {

               if (iArea == iMinArea)
               {

                  raTest.erase_at(i);

               }
               else
               {

                  raTest.erase_at(j);

               }

               goto restartFullIntersectionExclusion;

            }

         }

      }

      // Second Remove Partial Intersections which:
      // Intersection area is less than third the area of the int_rectangle with bigger area.

   restartPartialIntersectionExclusionEx:

      for (::collection::index i = 0; i < raTest.get_count(); i++)
      {

         for (::collection::index j = i + 1; j < raTest.get_count(); j++)
         {

            int iArea = raTest[i].area();

            int jArea = raTest[j].area();

            int iMaxArea = maximum(iArea, jArea);

            if (raTest[i].intersection(raTest[j]).area() < iMaxArea / 3)
            {

               if (iArea == iMaxArea)
               {

                  raTest.erase_at(j);

               }
               else
               {

                  raTest.erase_at(i);

               }

               goto restartPartialIntersectionExclusionEx;

            }

         }

      }

   }


   long long window::approximate_occlusion_area()
   {

      int_rectangle_array ra;

      approximate_occlusion_rects(ra);

      return ra.total_area();

   }


   long long window::opaque_area(const ::int_rectangle& rect)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock synchronouslockScreen(pitem->m_pmutex);

      ::color::color colorTransparent(::color::transparent);

      ::int_rectangle rectangle(rect);

      user_interaction()->screen_to_client()(rectangle);

      return rectangle.area() - pitem->m_pimage2->get_rgba_area(colorTransparent, rectangle);

   }


   long long window::_001GetRectTopLeftWeightedArea(const ::int_rectangle& rect)
   {

      ::int_rectangle rectangle(rect);

      user_interaction()->screen_to_client()(rectangle);

      return m_pgraphicsgraphics->_001GetTopLeftWeightedOpaqueArea(rectangle);

   }


   long long window::opaque_area()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock synchronouslockScreen(pitem->m_pmutex);

      ::color::color colorTransparent(::color::transparent);

      ::int_rectangle rectangle;

      user_interaction()->window_rectangle(rectangle);

      return rectangle.area() - pitem->m_pimage2->get_rgba_area(colorTransparent);

   }


   long long window::_001GetTopLeftWeightedArea()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock synchronouslockScreen(pitem->m_pmutex);

      ::color::color colorTransparent(::color::transparent);

      ::int_rectangle rectangle;

      user_interaction()->window_rectangle(rectangle);

      if (::is_null(m_pgraphicsgraphics))
      {

         return 0;

      }

      auto pimage = pitem->m_pimage2;

      if (::is_null(pimage))
      {

         return 0;

      }

      return pimage->_001GetTopLeftWeightedOpaqueArea(colorTransparent.byte_opacity());

   }


   long long window::approximate_occlusion_area_except_self_transparent()
   {

      int_rectangle_array ra;

      approximate_occlusion_rects(ra);

      long long cApproxOpaqueArea = 0;

      for (auto& r : ra)
      {

         cApproxOpaqueArea += opaque_area(r);

      }

      return cApproxOpaqueArea;

   }


   double window::approximate_occlusion_rate_except_self_transparent()
   {

      return (double)approximate_occlusion_area_except_self_transparent() / (double)opaque_area();

   }


   long long window::_001GetTopLeftWeightedOccludedOpaqueArea()
   {

      int_rectangle_array ra;

      approximate_occlusion_rects(ra);

      long long cApproxOpaqueArea = 0;

      for (auto& r : ra)
      {

         cApproxOpaqueArea += _001GetRectTopLeftWeightedArea(r);

      }

      return cApproxOpaqueArea;

   }


   double window::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      auto iWeightedOccludedOpaqueArea = _001GetTopLeftWeightedOccludedOpaqueArea();

      auto iWeightedOpaqueArea = _001GetTopLeftWeightedArea();

      double dWeightedOccludedOpaqueArea = (double)iWeightedOccludedOpaqueArea;

      double dWeightedOpaqueArea = (double)iWeightedOpaqueArea;

      double dRate = dWeightedOccludedOpaqueArea / dWeightedOpaqueArea;

      return dRate;

   }


   double window::approximate_occlusion_rate()
   {

      return (double)approximate_occlusion_area() / (double)user_interaction()->layout().area();

   }


   //   bool window::is_there_graphics_output_interest() const
   //   {
   //
   //      return m_particleaAutoRefresh;
   //
   //   }


   ::graphics::enum_output_purpose window::most_demanding_graphical_output_purpose()
   {

      ::graphics::enum_output_purpose epurposeMostDemanding = ::graphics::e_output_purpose_none;

      for (auto& ppurpose : m_graphicaloutputpurposea)
      {

         if (ppurpose->m_egraphicsoutputpurpose > epurposeMostDemanding)
         {

            epurposeMostDemanding = ppurpose->m_egraphicsoutputpurpose;

         }

      }

      return epurposeMostDemanding;

   }


   bool window::has_screen_output_purpose()
   {

      //::graphics::enum_output_purpose epurposeMostDemanding = ::graphics::e_output_purpose_none;

      for (auto& ppurpose : m_graphicaloutputpurposea)
      {

         if (ppurpose->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
         {

            return true;

         }

      }

      //return epurposeMostDemanding;

      return false;

   }


   bool window::has_offscreen_output_purpose()
   {

      //::graphics::enum_output_purpose epurposeMostDemanding = ::graphics::e_output_purpose_none;

      for (auto& ppurpose : m_graphicaloutputpurposea)
      {

         if (ppurpose->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_offscreen)
         {

            return true;

         }

      }

      //return epurposeMostDemanding;

      return false;

   }


   bool window::has_graphical_output_purpose()
   {

      return m_graphicaloutputpurposea.has_element();

   }


   bool window::has_fps_output_purpose()
   {

      //::graphics::enum_output_purpose epurposeMostDemanding = ::graphics::e_output_purpose_none;

      for (auto& ppurpose : m_graphicaloutputpurposea)
      {

         if (ppurpose && ppurpose->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_fps)
         {

            return true;

         }

      }

      //return epurposeMostDemanding;

      return false;

   }


   //   bool window::is_this_visible(enum_layout elayout)
   //   {
   //
   //      if (!user_interaction())
   //      {
   //
   //         return false;
   //
   //      }
   //
   ////      if (m_bOfflineRender)
   ////      {
   ////
   ////         return true;
   ////
   ////      }
   //
   //      if (!(user_interaction()->m_ewindowflag & e_window_flag_is_window))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      if (user_interaction()->m_ewindowflag & e_window_flag_not_visible)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      if (!user_interaction()->const_layout().state(elayout).is_visible())
   //      {
   //
   //         return false;
   //
   //      }
   //
   ////      if(!user_interaction()->m_bVisible)
   ////      {
   ////
   ////         return false;
   ////
   ////      }
   //
   //      return true;
   //
   //   }


      //   character_count window::get_window_text(char* sz, character_count s)
      //   {
      //
      //      if (!m_pwindow)
      //      {
      //
      //         return -1;
      //
      //      }
      //
      //      auto iSize = get_window_text(sz, s);
      //
      //      return iSize;
      //
      //   }
      //
      //
      //
      //   void window::get_window_text(string& str)
      //   {
      //
      //      if (!m_pwindow)
      //      {
      //
      //         return;
      //
      //      }
      //
      //      get_window_text(str);
      //
      //   }
      //
      //
      //   character_count window::get_window_text_length()
      //   {
      //
      //      return -1;
      //
      //   }


   //void window::set_icon(::windowing::icon *)
   //{

   //   //return ::success;

   //}


   //::pointer<::windowing::icon> window::get_icon() const
   //{

   //   return nullptr;

   //}


   //    void window::set_tool_window(bool bSet)
       //{

       //   return set_tool_window(bSet);

       //}


   void window::android_fill_plasma(const void* pixels, int width, int height, int stride, long long time_ms)
   {

      ::particle * pparticleSynchronization = nullptr;

      ::graphics::buffer_item * pitem = nullptr;

      ::image::image * pimageSource = nullptr;

      if(m_pgraphicsgraphics) {

         pitem = m_pgraphicsgraphics->get_screen_item();

      }

      if(pitem)
      {

         pparticleSynchronization = pitem->m_pmutex;

      }

//      if(payload("android_fill_plasma").is_false())
//      {
//
//         payload("android_fill_plasma") = true;
//
//         auto puserinteraction = user_interaction();
//
//         __check_refdbg
//
//         puserinteraction->set_need_redraw();
//
//         __check_refdbg
//
//         puserinteraction->post_redraw();
//
//      }

      _synchronous_lock synchronouslock(pparticleSynchronization);

      //_synchronous_lock synchronouslock(pitem->m_pmutex);

      int wSource;

      int hSource;

      ::image32_t * pdataSource = nullptr;

      int scanSource;

      if(pitem)
      {

         pimageSource = pitem->m_pimage2;

         if(pimageSource)
         {

            pimageSource->map();

            wSource = pimageSource->width();

            hSource = pimageSource->height();

            pdataSource = pimageSource->get_data();

            scanSource = pimageSource->m_iScan;

         }

      }

      if(!pimageSource)
      {

         wSource = width;

         hSource = height;

         pdataSource = nullptr;

         scanSource = wSource * 4;

      }

      if(pdataSource) {

#if defined(__i386__) || defined(__x86_64__)

         ((image32_t*)pixels)->copy_swap_red_blue(minimum(width, wSource), minimum(height, hSource), stride, pdataSource, scanSource);

#else

         ((image32_t *) pixels)->copy(
            minimum(width, wSource), minimum(height, hSource), stride,
                                      pdataSource,
                                      scanSource);

#endif

      }
      else
      {

         int r = 50;

         int g = 100;

         int b = 150;

         int a = 180;

         auto color = argb(a, r, g, b);

         image32_t image32Color(color, ::color_indexes());

         for(int i = 0; i < height; i++)
         {

            auto pline = (image32_t *)((unsigned char*)pixels + stride * i);

            for(int j = 0; j < width; j++)
            {

               pline[j] = image32Color;

            }

         }


      }

   }


   //:/*:oswindow window::oswindow() const
   //{

   //   return oswindow();

   //}*/


   //::windowing::window * message_interaction_impl(::user::message * pusermessage)
   //{

   //   auto pwindow = pusermessage->window();

   //   return pwindow ? pwindow->m_pwindow : nullptr;

   //}


   //void window::set_opacity(double dOpacity)
   //{

   //   if (::is_null(m_pwindow))
   //   {

   //      return;

   //   }

   //   set_opacity(dOpacity);

   //}


   //} // namespace user


   //CLASS_DECL_AURA::user::interaction * __interaction(::windowing::window * pwindow)
   //{
   //
   //   if (::is_null(pwindow)) return nullptr;
   //
   //   auto pwindow = pwindow->m_pwindow;
   //
   //   if (!pwindow) return nullptr;
   //
   //   return pwindow->user_interaction();
   //
   //}


   //CLASS_DECL_AURA::windowing::window * __interaction_impl(::windowing::window * pwindow)
   //{
   //
   //   if (::is_null(pwindow)) return nullptr;
   //
   //   auto pimpl = pwindow->m_pwindow.m_p;
   //
   //   if (::is_null(pimpl)) return nullptr;
   //
   //   return pimpl;
   //
   //}

   void window::process_messages()
   {



   }




   iptr_map < string >* g_p = nullptr;


   //window::window()
   //{

   //   m_bUserImplCreated = false;
   //   m_pinteractionimpl = nullptr;
   //   m_pinteractionchild = nullptr;
   //   //m_bDestroying = false;
   //   m_bDestroyImplOnly = false;
   //   m_iPendingRectMatch = -1;
   //   m_bPendingRedraw = false;
   //   user_interaction() = nullptr;
   //   m_bIgnoreSizeEvent = false;
   //   m_bIgnoreMoveEvent = false;
   //   //m_bUserElementOk = true;

   //}


   //window::~window()
   //{

   //}


   //void window::create_message_queue(::user::interaction * pinteraction, const ::scoped_string & scopedstrName)
   //{

   //   throw ::interface_only();

   //   //return true;

   //}


   //void window::create_interaction(::user::interaction * pinteraction, ::user::interaction_base * pparent)
   //{

   //   throw ::interface_only();

   //   return true;

   //}


   //void window::create_interaction(::user::interaction * pinteraction, ::user::interaction_base * puiParent)

   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void window::create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pcs, ::user::interaction_base * puiParent, atom atom)
   //{

   //   throw ::interface_only();

   //   return true;

   //}


   //void window::create_interaction(::user::interaction * pinteraction, ::user::interaction_base * pparent)
   //{

   //   throw ::interface_only();

   //   return true;

   //}

   //::windowing::window * window::get_user_interaction_impl()
   //{

   //   return nullptr;

   //}


   //::user::interaction_child * window::get_user_interaction_child()
   //{

   //   return nullptr;

   //}


   //void window::defer_do_graphics(::draw2d::graphics_pointer & pgraphics)
   //{

   //   user_interaction()->_000CallOnDraw(pgraphics);

   //}


   //void window::top_down_prefix()
   //{

   //   user_interaction()->top_down_prefix();

   //}


   void window::set_need_layout()
   {

      user_interaction()->set_need_layout();

      if (user_interaction()->m_puserinteractionParent != nullptr)
      {

         user_interaction()->m_puserinteractionParent->set_need_layout();

      }

   }


   //void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //   //user_interaction()->message_call(e_message_size, 0, process_state().m_size.lparam());

   //   //user_interaction()->m_timeLastVisualChange.Now();

   //   //user_interaction()->m_bSizeMove = true;


   //}


   void window::on_reposition()
   {

   }


   void window::on_layout_reposition()
   {


   }

   void window::on_show_window()
   {

   }


   oswindow window::detach_window()
   {

      return nullptr;

   }


   //void window::destroy()
   //{

   //   ::channel::destroy();

   //   //::source::destroy();

   //   ::manager::destroy();

   //   //auto estatus = 
   //   user_interaction().release();

   //   //return estatus;

   //}


   //void window::finish()
   //{

   //   ::user::interaction_base::finish();

   //}


   //   void window::graphics_thread_update_screen()
   //   {
   //
   //      //return true;
   //
   //   }


      //void window::RepositionBars(unsigned int nIDFirst, unsigned int nIDLast, atom idLeft, unsigned int nFlags, ::int_rectangle * prectParam, const int_rectangle & rectangleX, bool bStretch)
      //{

      //   if (!_is_window())
      //   {

      //      return;

      //   }

      //   __UNREFERENCED_PARAMETER(nIDFirst);

      //   __UNREFERENCED_PARAMETER(nIDLast);

      //   ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery || (nFlags & ~reposNoPosLeftOver) == reposExtra);

      //   SIZEPARENTPARAMS sizeparentparams;

      //   ::pointer<::user::interaction>puiLeft;

      //   sizeparentparams.bStretch = bStretch;

      //   sizeparentparams.sizeTotal.cx() = sizeparentparams.sizeTotal.cy() = 0;

      //   if (rectangleX != nullptr)
      //   {

      //      sizeparentparams.rectangle = rectangleX;

      //   }
      //   else
      //   {

      //      user_interaction()->rectangle(&sizeparentparams.rectangle);

      //   }

      //   if (::is_empty(sizeparentparams.rectangle))
      //   {

      //      return;

      //   }

      //   ::pointer<::user::interaction>pinteraction;

      //   while (user_interaction()->get_child(pinteraction))
      //   {

      //      atom atom = pinteraction->GetDlgCtrlId();

      //      if (atom == idLeft)
      //      {

      //         puiLeft = pinteraction;

      //      }
      //      else
      //      {

      //         pinteraction->send_message(e_message_size_parent, 0, (lparam)& sizeparentparams);

      //      }

      //   }

      //   if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
      //   {

      //      ASSERT(prectParam != nullptr);

      //      if (bStretch)
      //      {

      //         ::copy(prectParam, &sizeparentparams.rectangle);

      //      }
      //      else
      //      {

      //         prectParam->left() = prectParam->top() = 0;

      //         prectParam->right() = sizeparentparams.sizeTotal.cx();

      //         prectParam->bottom() = sizeparentparams.sizeTotal.cy();


      //      }

      //      return;

      //   }


      //   if (!idLeft.is_empty() && puiLeft != nullptr)
      //   {

      //      if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
      //      {

      //         ASSERT(prectParam != nullptr);


      //         sizeparentparams.rectangle.left() += prectParam->left();

      //         sizeparentparams.rectangle.top() += prectParam->top();

      //         sizeparentparams.rectangle.right() -= prectParam->right();

      //         sizeparentparams.rectangle.bottom() -= prectParam->bottom();


      //      }

      //      if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
      //      {

      //         //puiLeft->CalcWindowRect(&sizeparentparams.rectangle);

      //         puiLeft->place(sizeparentparams.rectangle);

      //         puiLeft->display();

      //         puiLeft->set_need_layout();

      //      }

      //   }

      //}


   void window::window_move(int x, int y)
   {

      //return true;

   }


   //void window::on_configure(const ::int_rectangle & rectangle)
   //{


   //}


   //   void window::on_resize(const ::int_size & size)
   //   {
   //
   //
   //   }


      //void window::main_async(const promise::procedure & routine, enum_priority epriority)
      //{

      //   if (!user_interaction())
      //   {

      //      return ::error_failed;

      //   }

      //   auto puserinteraction = user_interaction()->get_wnd();

      //   if (!puserinteraction)
      //   {

      //       return ::error_failed;

      //   }

      //   return puserinteraction->post_procedure(routine, epriority);

      //}


   void window::_001OnNcClip(::draw2d::graphics_pointer& pgraphics)
   {

      user_interaction()->_001OnTopNcClip(pgraphics);

   }


   //   void window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //   }
   //
   //
   //   void window::_000CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //      if (!user_interaction())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      string strType = ::type(user_interaction()).name();
   //
   ////      if (strType.contains("list_box"))
   ////      {
   ////
   ////         informationf("list_box");
   ////
   ////      }
   //
   //      windowing_output_debug_string("\ninteraction_impl_base::_001Print");
   //
   //      user_interaction()->_000CallOnDraw(pgraphics);
   //
   //   }
   //
   //
   //   void window::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //      if (user_interaction())
   //      {
   //
   //         user_interaction()->_000CallOnDraw(pgraphics);
   //
   //      }
   //
   //   }
   //
   //
   //   void window::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //      if (user_interaction())
   //      {
   //
   //         user_interaction()->_001DrawThis(pgraphics);
   //
   //      }
   //
   //   }
   //
   //
   //   void window::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //      if (user_interaction())
   //      {
   //
   //         user_interaction()->_001DrawChildren(pgraphics);
   //
   //      }
   //
   //   }
   //
   //
   //   void window::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //      if (user_interaction())
   //      {
   //
   //         user_interaction()->draw_control_background(pgraphics);
   //
   //      }
   //
   //   }


   void window::set_origin(::draw2d::graphics_pointer& pgraphics)
   {

   }


   void window::viewport_client_to_screen(::sequence2_int& sequence)
   {

      if (user_interaction())
      {

         ::add(sequence, user_interaction()->const_layout().design().origin());

      }

   }


   void window::viewport_screen_to_client(::sequence2_int& sequence)
   {

      if (user_interaction())
      {

         ::subtract(sequence, user_interaction()->const_layout().design().origin());

      }

   }


   void window::viewport_client_to_screen(::int_rectangle& rectangle)
   {

      viewport_client_to_screen(rectangle.top_left());

      viewport_client_to_screen(rectangle.bottom_right());

   }


   void window::viewport_screen_to_client(::int_rectangle& rectangle)
   {

      viewport_screen_to_client((::int_point&)rectangle.top_left());
      viewport_screen_to_client((::int_point&)rectangle.bottom_right());

   }


   void window::post_message(::message::message* pmessage)
   {

      if (!user_interaction())
      {

         throw ::exception(error_wrong_state);

      }

      user_interaction()->post_message(pmessage);

   }


   //void window::set_bitmap_source(const ::scoped_string & scopedstrBitmapSource)
   //{


   //}


   //void window::clear_bitmap_source()
   //{


   //}


   //void window::set_tool_window(bool bSet)
   //{


   //}


   //void window::interaction_post(const ::procedure & procedure)
   //{


   //}


   //void window::_000OnMouseLeave(::message::message * pmessage)
   //{


   //}


   //void window::track_mouse_hover()
   //{


   //}


   //void window::track_mouse_leave()
   //{


   //}


   //   void window::add_fps_interest(::particle * pparticle)
   //   {
   //
   //
   //   }
   //
   //
   //   void window::erase_fps_interest(::particle * pparticle)
   //   {
   //
   //
   //   }
   //
   //
   //   bool window::is_fps_interest(const ::particle * pparticle) const
   //   {
   //
   //      return false;
   //
   //   }


   //   void window::fps_interest_stop()
   //   {
   //
   //
   //   }


   //::user::interaction_base * window::set_owner(::user::interaction_base * pprimitiveOwner)
   //{

   //   return nullptr;

   //}


   //bool window::has_pending_redraw_flags()
   //{

   //   return false;

   //}


   //void window::add(::graphics::output_purpose * poutputpurpose)
   //{



   //}


   //void window::erase(::graphics::output_purpose * poutputpurpose)
   //{



   //}



   //void window::add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose)
   //{


   //}



   //void window::erase_graphical_output_purpose(::particle * pparticle)
   //{


   //}


   //bool window::does_particle_has_fps_purpose(const ::particle * pparticle) const
   //{

   //   return false;

   //}


   //   ::graphics::enum_output_purpose window::most_demanding_graphical_output_purpose() const
   //   {
   //
   //      return ::graphics::e_output_purpose_none;
   //
   //   }


   //bool window::has_screen_output_purpose() const
   //{

   //   return false;

   //}


   //bool window::has_graphical_output_purpose() const
   //{

   //   return false;

   //}


   //   bool window::has_graphical_output_purpose() const
   //   {
   //
   //      return false;
   //
   //   }


   //bool window::has_fps_output_purpose() const
   //{

   //   return false;

   //}



   //   bool window::has_graphical_output_purpose() const
   //   {
   //
   //      return false;
   //
   //   }


   //void window::pre_subclass_window()
   //{


   //}


   //void window::destroy_impl_only()
   //{


   //}


   //void window::start_destroying_window()
   //{


   //}


   /*void window::destroy_window()
   {


   }*/


   //bool window::_is_window()
   //{

   //   return false;

   //}


   //lresult window::send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point & point)
   //{

   //   return message_call(emessage, wparam, lparam, point);

   //}


   //lresult window::send_message(::message::message * pmessage)
   //{

   //   return message_call(pmessage);

   //}


#define _NEW_MESSAGE(TYPE) \
   auto pmessage = __create_new<TYPE>(); \
   pmessage->m_pchannel = this; \
   pmessage->m_oswindow = oswindow; \
   pmessage->m_pwindow = pwindow; \
   pmessage->m_emessage = atom; \
   pmessage->m_wparam = wparam; \
   pmessage->m_lparam = lparam; \
   pmessageBase = pmessage


   //#define _NEW_MESSAGE(TYPE) \
   //   auto pmessage = __create_new<TYPE>(); \
   //   pmessage->m_pchannel = this; \
   //   pmessage->m_emessage = atom; \
   //   pmessage->m_wparam = wparam; \
   //   pmessage->m_lparam = lparam; \
   //   pmessageBase = pmessage


   ::pointer<::message::message>window::get_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, ::message::enum_prototype eprototype)
   {

      return user_interaction()->get_message(emessage, wparam, lparam);

   }

   //   {
   //
   //      ::pointer<::message::message>pmessageBase;
   //
   //      if (eprototype == ::message::e_prototype_none)
   //      {
   //
   //         eprototype = ::message::get_message_prototype(atom.as_emessage(), 0);
   //
   //      }
   //
   //      auto pwindow = this;
   //
   //      auto oswindow = pwindow ? pwindow->oswindow() : nullptr;
   //
   //      switch (eprototype)
   //      {
   //      case ::message::e_prototype_none:
   //      {
   //
   //         _NEW_MESSAGE(::user::message);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_create:
   //      {
   //         _NEW_MESSAGE(::message::create);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_enable:
   //      {
   //         _NEW_MESSAGE(::message::enable);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_non_client_activate:
   //      {
   //         _NEW_MESSAGE(::message::nc_activate);
   //         {
   //
   //            //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);
   //
   //            pmessage->m_bActive = wparam != false;
   //
   //         }
   //      }
   //      break;
   //      case ::message::e_prototype_key:
   //      {
   //         _NEW_MESSAGE(::message::key);
   //         //void key::set(oswindow oswindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
   //         {
   //
   //            // ::user::message::set(oswindow, pwindow, emessage, wparam, lparam);
   //
   //            pmessage->m_nChar = static_cast<unsigned int>(wparam);
   //
   //            pmessage->m_nRepCnt = lower_unsigned_short(lparam);
   //
   //            pmessage->m_nFlags = upper_unsigned_short(lparam);
   //
   //            pmessage->m_iVirtualKey = (int)wparam;
   //
   //            pmessage->m_nScanCode = ((lparam >> 16) & 0xff);
   //
   //            pmessage->m_bExt = (lparam & (1 << 24)) != 0;
   //
   //         }
   //
   //      }
   //      break;
   //      case ::message::e_prototype_timer:
   //      {
   //
   //         //throw ::exception(::exception("do not use e_message_timer or Windows set_timer/kill_timer"));
   //
   //         _NEW_MESSAGE(::message::timer);
   //
   //         pmessage->m_uTimer = static_cast<unsigned int>(wparam);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_show_window:
   //      {
   //         _NEW_MESSAGE(::message::show_window);
   //         pmessage->m_bShow = wparam != false;
   //
   //         pmessage->m_nStatus = static_cast<unsigned int>(lparam);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_set_cursor:
   //      {
   //         _NEW_MESSAGE(::message::set_cursor);
   //      }
   //      break;
   //      case ::message::e_prototype_non_client_hit_test:
   //      {
   //         _NEW_MESSAGE(::message::nc_hit_test);
   //         pmessage->m_point.x() = lparam_int_x(lparam);
   //
   //         pmessage->m_point.y() = lparam_int_y(lparam);
   //      }
   //      break;
   //      case ::message::e_prototype_move:
   //      {
   //         _NEW_MESSAGE(::message::reposition);
   //         pmessage->m_point = lparam.point();
   //      }
   //      break;
   //      case ::message::e_prototype_erase_background:
   //      {
   //         _NEW_MESSAGE(::message::erase_bkgnd);
   //      }
   //      break;
   //      case ::message::e_prototype_scroll:
   //      {
   //         _NEW_MESSAGE(::message::scroll);
   //
   //#ifdef WINDOWS_DESKTOP
   //         pmessage->m_oswindowScrollBar = (::oswindow)(::iptr)(lparam);
   //
   //#endif
   //
   //         //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);
   //
   //         pmessage->m_ecommand = (enum_scroll_command)(short)lower_unsigned_short(wparam);
   //
   //         pmessage->m_dPosition = (double)(short)upper_unsigned_short(wparam);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_set_focus:
   //      {
   //         _NEW_MESSAGE(::message::set_keyboard_focus);
   //      }
   //      break;
   //      case ::message::e_prototype_kill_focus:
   //      {
   //         _NEW_MESSAGE(::message::kill_keyboard_focus);
   //         pmessage->m_oswindowNew = (::oswindow)wparam.m_number;
   //      }
   //      break;
   //#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(__ANDROID__) && !defined(__BSD__)
   //      case ::message::e_prototype_window_pos:
   //
   //      {
   //         _NEW_MESSAGE(::message::window_pos);
   //         pmessage->m_pWINDOWPOS = reinterpret_cast<void *>(lparam.m_lparam);
   //      }
   //      break;
   //      case ::message::e_prototype_non_client_calc_size:
   //      {
   //         _NEW_MESSAGE(::message::nc_calc_size);
   //         pmessage->m_pNCCALCSIZE_PARAMS = reinterpret_cast<void *>(lparam.m_lparam);
   //      }
   //      break;
   //#endif
   //      case ::message::e_prototype_mouse:
   //      {
   //         _NEW_MESSAGE(::message::mouse);
   //         pmessage->m_ebuttonstate = (::user::enum_button_state)wparam.m_number;
   //
   //         //         if ((pmessage->m_ebuttonstate & I32_MINIMUM) == (I32_MINIMUM))
   //         //         {
   //         //
   //         //            informationf("(m_ebuttonstate & I32_MINIMUM) == (I32_MINIMUM)");
   //         //
   //         //         }
   //
   //         pmessage->m_pointHost = lparam.point();
   //
   //         pmessage->m_pointAbsolute = lparam.point();
   //
   //         _raw_client_to_screen(pmessage->m_pointAbsolute);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_object:
   //      {
   //         _NEW_MESSAGE(::message::particle);
   //         //void particle::set(oswindow oswindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
   //         {
   //
   //            //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);
   //
   //            ::particle_pointer pparticle(lparam);
   //
   //            pmessage->m_pparticle = pparticle;
   //
   //            pmessage->m_lparam = 0;
   //
   //         }
   //      }
   //      break;
   //      case ::message::e_prototype_mouse_wheel:
   //      {
   //         _NEW_MESSAGE(::message::mouse_wheel);
   //
   //         pmessage->m_ebuttonstate = (::user::enum_button_state)lower_unsigned_short(wparam);
   //
   //         pmessage->m_pointAbsolute = lparam.point();
   //
   //         pmessage->m_Δ = upper_short(wparam);
   //
   //         pmessage->m_pointHost = pmessage->m_pointAbsolute;
   //
   //         _raw_screen_to_client(pmessage->m_pointHost);
   //
   //      }
   //      break;
   //      case ::message::e_prototype_size:
   //      {
   //         _NEW_MESSAGE(::message::size);
   //
   //         pmessage->m_nType = static_cast <unsigned int> (wparam);
   //
   //         pmessage->m_size = ::int_size(lparam_int_x(lparam), lparam_int_y(lparam));
   //      }
   //      break;
   //      case ::message::e_prototype_activate:
   //      {
   //         _NEW_MESSAGE(::message::activate);
   //         //pmessage = p;
   //         //default_set(pmessage, emessage, wparam, lparam)
   //         //void activate::set(oswindow oswindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
   //         //{
   //
   //            //::user::message::set(oswindow, pwindow, emessage, wparam, lparam);
   //
   //         pmessage->m_eactivate = (enum_activate)(lower_unsigned_short(wparam));
   //
   //         if (lparam == 0)
   //         {
   //
   //            pmessage->m_pWndOther = nullptr;
   //
   //         }
   //         else
   //         {
   //
   //            auto paurasession = m_papplication->m_psession;
   //
   //            auto puser = paurasession->m_puser;
   //
   //            auto pwindowing = system()->windowing();
   //
   //            pmessage->m_pWndOther = pwindowing->window(lparam.raw_cast <::oswindow>())->user_interaction();
   //
   //         }
   //
   //         pmessage->m_bMinimized = upper_unsigned_short(wparam) != false;
   //
   //         //}
   //
   //      }
   //      break;
   //      case ::message::e_prototype_mouse_activate:
   //      {
   //         _NEW_MESSAGE(::message::mouse_activate);
   //      }
   //      break;
   //      default:
   //      {
   //
   //         auto pmessage = ::channel::get_message(emessage, wparam, lparam, eprototype);
   //
   //         pmessageBase = pmessage;
   //
   //      }
   //      break;
   //      }
   //
   //      if (pmessageBase.is_null())
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      //auto estatus =
   //
   //
   //
   //
   //      //if (!estatus)
   //      //{
   //
   //      //   return nullptr;
   //
   //      //}
   //
   //      return pmessageBase;

      //}



      //void window::post_message(const ::atom& atom, ::wparam wParam, ::lparam lParam)
      //{


      //}


      //   void window::set_window_text(const ::scoped_string & scopedstrString)
      //   {
      //
      //
      //   }


         //void window::on_set_window_text()
         //{


         //}

         //   character_count window::get_window_text(char* pszStringBuf, character_count nMaxCount)
         //   {
         //
         //      return 0;
         //
         //   }


         //   void window::get_window_text(string& rString)
         //   {
         //
         //
         //   }


         //   character_count window::get_window_text_length()
         //   {
         //
         //      return 0;
         //
         //   }


            //void window::UpdateWindow()
            //{


            //}


            //void window::SetRedraw(bool bRedraw)
            //{


            //}


         //   void window::graphics_thread_redraw(bool bUpdateBuffer)
         //   {
         //
         //
         //   }



         //void window::set_mouse_cursor(::windowing::cursor * pcursor)
         //{


         //}

         //::user::interaction * window::ChildWindowFromPoint(const ::int_point & point)
         //{

         //   return nullptr;

         //}


         //::user::interaction * window::ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags)
         //{

         //   return nullptr;

         //}


         //::user::interaction * window::GetLastActivePopup()
         //{

         //   return nullptr;

         //}


         //void window::update_data(bool bSaveAndValidate)
         //{


         //}


         //void window::CenterWindow(::user::interaction * pAlternateOwner)
         //{


         //}


         //bool window::OnChildNotify(::message::message * pusermessage)
         //{

         //   return false;

         //}


         //void window::ActivateTopParent()
         //{


         //}


         //void window::_001UpdateWindow()
         //{


         //}


         //void window::on_start_layout_experience(enum_layout_experience elayoutexperience)
         //{


         //}


   void window::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {


   }


   //void window::on_configuration_change(::user::interaction_base * pprimitiveSource)
   //{


   //}


   //::user::element* window::get_keyboard_focus()
   //{

   //   return nullptr;

   //}


   void window::_001OnAfterExitIconic()
   {

   }


   void window::_001OnAfterExitNormal()
   {

   }


   void window::_001OnAfterExitZoomed()
   {


   }


   void window::_001OnAfterExitFullScreen()
   {


   }


   //void window::default_message_handler(::message::message * pmessage)
   //{


   //}


   //   void window::_001OnTriggerMouseInside()
   //   {
   //
   //
   //   }


   //bool window::has_pending_graphical_update()
   //{

   //   return false;

   //}


   //void window::on_after_graphical_update()
   //{


   //}


   bool window::is_this_visible(::user::enum_layout elayout)
   {

      return false;

   }


   //void window::post_redraw(bool bAscendants)
   //{



   //}


   //double window::_001GetTopLeftWeightedOccludedOpaqueRate()
   //{

   //   return 0.;

   //}


   //   ::windowing::window* window::get_window() const
   //   {
   //
   //      return nullptr;
   //
   //   }


   //bool window::keyboard_focus_OnKillFocus(::oswindow oswindowNew)
   //{

   //   return false;

   //}


   //bool window::keyboard_focus_OnChildKillFocus()
   //{

   //   return false;

   //}


   void window::edit_on_set_focus(::user::interaction* pinteraction)
   {


   }


   void window::edit_on_kill_focus(::user::interaction* pinteraction)
   {


   }


   //void window::show_software_keyboard(::user::element * pelement)
   //{

   //   throw interface_only();

   //}


   //void window::hide_software_keyboard(::user::element * pelement)
   //{

   //   throw interface_only();

   //}


   ::user::interaction* window::get_child_by_id(const ::atom& atom, ::collection::index iItem, int iLevel)
   {

      return nullptr;

   }


   //void window::set_need_redraw(const ::int_rectangle_array & rectangleaNeedRedraw, function<void()> function, bool bAscendants)
   //{


   //}


   //bool window::RedrawWindow(const ::int_rectangle & rectangleUpdate, ::draw2d::region * prgnUpdate, unsigned int flags)
   //{

   //   if (!user_interaction())
   //   {

   //      //return false;

   //      return;

   //   }

   //   return user_interaction()->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

   //}


   //unsigned int window::GetStyle() const
   //{

   //   return get_window_long(GWL_STYLE);

   //}


   //unsigned int window::GetExStyle() const
   //{

   //   return get_window_long(GWL_EXSTYLE);

   //}


   //void window::ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   int l = GetStyle();

   //   l |= dwAdd;

   //   int lRemove = ~dwRemove;

   //   l &= lRemove;

   //   set_window_long(GWL_STYLE, l);

   //   return true;

   //}


   //void window::ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags)
   //{

   //   set_window_long(GWL_EXSTYLE, (GetExStyle() | dwAdd) & ~dwRemove);

   //   return true;

   //}


   //   int window::get_window_long(int nIndex) const
   //   {
   //
   //      return (int)get_window_long_ptr(nIndex);
   //
   //   }
   //
   //
   //   int window::set_window_long(int nIndex, int lValue)
   //   {
   //
   //      return (int)set_window_long_ptr(nIndex, lValue);
   //
   //   }
   //
   //
   //   iptr window::get_window_long_ptr(int nIndex) const
   //   {
   //
   ////      return 0;
   //////
   //////      if (nIndex == GWL_STYLE)
   //////      {
   //////
   //////         return  m_uStyle;
   //////
   //////      }
   //////      else if (nIndex == GWL_EXSTYLE)
   //////      {
   //////
   //////         return  m_uExStyle;
   //////
   //////      }
   //////
   //////      synchronous_lock synchronouslock(&((window *)this)->m_pmutexLongPtr);
   //////
   //////      return (LONG_PTR)m_longptr[nIndex];
   ////
   //      return m_iptrmap[nIndex];
   //
   //   }
   //
   //
   //   void window::set_window_long_ptr(int nIndex, iptr lValue)
   //   {
   //
   ////      if (nIndex == GWL_STYLE)
   ////      {
   ////
   ////         return m_uStyle = lValue;
   ////
   ////      }
   ////      else if (nIndex == GWL_EXSTYLE)
   ////      {
   ////
   ////         return m_uExStyle = lValue;
   ////
   ////      }
   ////
   ////      synchronous_lock synchronouslock(m_pmutexLongPtr);
   ////
   ////      m_longptr[nIndex] = lValue;
   ////
   ////      return lValue;
   //
   //      //return lValue;
   //
   //      return m_iptrmap[nIndex] = lValue;
   //
   //   }


   atom window::GetDlgCtrlId() const
   {

      if (!user_interaction())
      {

         return ::atom::e_type_null;

      }

      return user_interaction()->GetDlgCtrlId();

   }


   atom window::SetDlgCtrlId(const atom& atom)
   {

      if (!user_interaction())
      {

         return atom::e_type_null;

      }

      return user_interaction()->SetDlgCtrlId(atom);

   }



   ::user::interaction* window::first_child()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->first_child();

   }


   ::user::interaction* window::top_child()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->first_child();

   }


   ::user::interaction* window::under_sibling()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->under_sibling();

   }


   ::user::interaction* window::above_sibling()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->above_sibling();

   }


   ::user::interaction* window::above_sibling(::user::interaction* pinteraction)
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->above_sibling(pinteraction);

   }


   ::user::interaction* window::under_sibling(::user::interaction* pinteraction)
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->under_sibling(pinteraction);

   }


   //unsigned int window::ArrangeIconicWindows()
   //{

   //   //      return user_interaction()->ArrangeIconicWindows();
   //   return 0;

   //}


   bool window::is_ascendant(::user::element* puiIsAscendant, bool bIncludeSelf)
   {

      if (::is_null(puiIsAscendant))
      {

         return false;

      }

      return puiIsAscendant->is_descendant(user_interaction(), bIncludeSelf);

   }


   bool window::is_parent(::user::element* puiIsParent)
   {

      if (puiIsParent == nullptr)
      {

         return false;

      }

      return puiIsParent->is_child(user_interaction());

   }


   bool window::is_child(::user::element* puiIsChild)
   {

      if (puiIsChild == nullptr)
      {

         return false;

      }

      ::user::interaction* puiProbe = puiIsChild->get_parent();

      return puiProbe == user_interaction();

   }


   bool window::is_descendant(::user::element* puiIsDescendant, bool bIncludeSelf)
   {

      ::user::element* puiProbe;

      if (bIncludeSelf)
      {

         puiProbe = puiIsDescendant;

      }
      else
      {

         puiProbe = puiIsDescendant->get_parent();

      }

      if (::is_null(puiProbe))
      {

         return false;

      }

      auto puserinteraction = user_interaction();

      do
      {

         if (puiProbe == puserinteraction)
         {

            return true;

         }

         puiProbe = puiProbe->get_parent();

      } while (puiProbe != nullptr);

      return false;

   }


   ::user::interaction* window::get_wnd()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->get_wnd();

   }


   ::user::interaction* window::get_wnd(unsigned int nCmd)
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->get_wnd(nCmd);

   }


   //::user::interaction * window::GetTopWindow() const
   //{

   //   auto pinteraction = get_wnd();

   //   if (!pinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetTopWindow();

   //}


   //::user::interaction * window::get_parent()
   //{

   //   if (!user_interaction())
   //   {

   //      return nullptr;

   //   }

   //   return user_interaction()->get_parent();

   //}


   ::user::interaction* window::get_owner()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->owner_interaction();

   }


   ::user::frame_interaction* window::frame()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->frame();

   }


   //::user::frame_interaction * window::get_parent_frame() const
   //{

   //   if (!user_interaction())
   //   {

   //      return nullptr;

   //   }

   //   return user_interaction()->parent_frame();

   //}


   ::user::interaction* window::get_parent_owner()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->get_parent_owner();

   }


   ::user::interaction* window::get_parent_or_owner()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->get_parent_or_owner();

   }


   ::user::interaction* window::get_top_level_owner()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->get_top_level_owner();

   }


   ::user::frame_interaction* window::top_level_frame()
   {

      if (!user_interaction())
      {

         return nullptr;

      }

      return user_interaction()->top_level_frame();

   }


   //::user::interaction * window::get_top_level() const
   //{

   //   if (!user_interaction())
   //   {

   //      return nullptr;

   //   }

   //   return user_interaction()->top_level();

   //}


   lresult window::message_handler(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      // if (::is_null(user_interaction()))
      // {

      //    throw ::exception(error_wrong_state);

      // }

      // user_interaction()->interaction_post(__allocate call_message_handler_task(user_interaction(), emessage, wparam, lparam));

      //auto pmessage

      //get_message()

      ::pointer<::message::message>pmessage;

      if (user_interaction())
      {

         pmessage = user_interaction()->get_message(emessage, wparam, lparam);

      }
      else
      {

         pmessage = get_message(emessage, wparam, lparam);

      }

      pmessage->m_pchannel = this;

      //return message_call(pmessage);

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   lresult window::message_call(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point& point)
   {

      ::pointer<::message::message>pmessage;

      if (user_interaction())
      {

         pmessage = user_interaction()->get_message(emessage, wparam, lparam);

      }
      else
      {

         pmessage = get_message(emessage, wparam, lparam);

      }

      pmessage->m_pchannel = user_interaction();

      return message_call(pmessage);

   }


   lresult window::message_call(::message::message* pmessage)
   {

      if (user_interaction() == nullptr)
      {

         message_handler(pmessage);

         return pmessage->m_lresult;

      }

      if (user_interaction()->layout().is_moving())
      {

         informationf("moving: skip walk pre translate tree");

      }
      else if (user_interaction()->layout().is_sizing())
      {

         informationf("sizing: skip walk pre translate tree");

      }
      else
      {

         user_interaction()->walk_pre_translate_tree(pmessage);

         if (pmessage->m_bRet)
         {

            return pmessage->m_lresult;

         }

      }

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   void window::send_message_to_descendants(::enum_message emessage, ::wparam wparam, ::lparam lparam, bool bDeep, bool bOnlyPerm)
   {

      return user_interaction()->send_message_to_descendants(emessage, wparam, lparam, bDeep, bOnlyPerm);

   }


   //void window::pre_translate_message(::message::message * pmessage)
   //{

   //   user_interaction()->pre_translate_message(pmessage);

   //}


   //void window::set_mouse_capture(::user::interaction * pinteraction)
   //{

   //   return get_host_user_interaction()->set_mouse_capture(pinteraction);

   //}


   //::user::interaction * window::get_capture() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_capture();

   //}


   ////void window::set_keyboard_focus(::user::interaction * pinteraction)
   //{

   //   return get_host_user_interaction()->set_keyboard_focus(pinteraction);

   //}


   //::user::interaction * window::get_keyboard_focus() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_keyboard_focus();

   //}


   //bool window::get_rect_normal(::int_rectangle * prectangle)
   //{

   //   *prectangle = user_interaction()->screen_rectangle();

   //}


   //void window::set_timer(uptr uEvent, const class ::time & timeEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pdata)
   //{

   //   if (timeEllapse < 500_ms)
   //   {

   //      //         string str;
   //      //
   //      //         str.formatf("creating fast timer: %d\n", nEllapse);
   //      //
   //      //         ::information(str);

   //   }

   //   if (m_ptimerarray.is_null())
   //   {

   //      __construct_new(m_ptimerarray);

   //      m_ptimerarray->m_pcallback = user_interaction();

   //      //m_ptimerarray->set_context_thread(user_interaction()->m_pthreadUserInteraction);

   //   }

   //   m_ptimerarray->create_timer(this, uEvent, timeEllapse, pfnTimer, bPeriodic, pdata);

   //}


   //void window::kill_timer(uptr uEvent)
   //{

   //   if (m_ptimerarray.is_null())
   //   {

   //      return;

   //   }

   //   m_ptimerarray->delete_timer(uEvent);

   //}


   //void window::on_timer(::timer * ptimer)
   //{

   //   if (user_interaction() == nullptr)
   //   {

   //      return;

   //   }

   //   user_interaction()->on_timer(ptimer);

   //}


   //void window::defer_start_fps_interest()
   //{

   //   user_interaction()->post_simple_command(e_simple_command_defer_start_fps_interest);

   //}


   //void window::_defer_start_fps_interest()
   //{

   //}

   //void window::destroy_impl_only()
   //{

   //   auto pinteraction = user_interaction();

   //   m_bDestroyImplOnly = true;

   //   if (::is_set(user_interaction()))
   //   {

   //      //         user_interaction()->transfer_receiver(m_idroute, this);
   //      //
   //      auto puserinteraction = user_interaction()->get_wnd();

   //      if (::is_set(puserinteraction))
   //      {

   //         auto pwindow = puserinteraction->m_pinteractionimpl;

   //         if (pwindow)
   //         {

   //            synchronous_lock synchronouslock(pwindow->synchronization());

   //            pwindow->m_userinteractionaMouseHover.erase(user_interaction());

   //         }

   //      }

   //      user_interaction()->m_puserinteractionParent = nullptr;

   //   }

   //   user_interaction() = nullptr;

   //   start_destroying_window();

   //   //informationf("destroy_impl_only DestroyWindow %d", bOk != false);

   //   //return bOk;

   //}


   void window::start_destroying_window()
   {

      if (!m_bUserImplCreated)
      {

         return;

      }

      m_bUserImplCreated = false;

      if (user_interaction() == nullptr && !m_bDestroyImplOnly)
      {

         return;

      }

      destroy_window();

   }


   //void window::mouse_hover_add(::user::interaction * pinterface)
   //{

   //   auto puserinteraction = user_interaction();

   //   if (!puserinteraction)
   //   {

   //      return;

   //   }

   //   ::user::interaction * pinteraction = puserinteraction->get_host_user_interaction();

   //   if (!pinteraction)
   //   {

   //      //return false;

   //      return;

   //   }

   //   //auto bOk = 

   //   pinteraction->mouse_hover_add(pinterface);

   //   //if (!bOk)
   //   //{

   //   //   return false;

   //   //}

   //   //return true;

   //}


   //bool window::mouse_hover_erase(::user::interaction * pinterface)
   //{

   //   auto puserinteraction = user_interaction();

   //   if (!puserinteraction)
   //   {

   //      return false;

   //   }

   //   ::user::interaction * pinteraction = puserinteraction->get_host_user_interaction();

   //   if (pinteraction != nullptr)
   //   {

   //      return pinteraction->mouse_hover_erase(pinterface);

   //   }

   //   return false;

   //}


   void window::register_drop_target()
   {

   }


   //   ::windowing::window* window::window()
   //   {
   //
   //      auto puserinteraction = user_interaction();
   //
   //      if (!puserinteraction)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      auto pwindow = puserinteraction->window();
   //
   //      if (!pwindow)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return pwindow;
   //
   //   }


   /*::user::element * window::get_keyboard_focus()
   {

      return nullptr;

   }*/


   //void window::set_keyboard_focus(::user::interaction * puserinteraction)
   //{

   //   __UNREFERENCED_PARAMETER(puserinteraction);

   //   //return ::error_failed;

   //}


   //void window::erase_keyboard_focus(::windowing::window * pprimitiveimpl)
   //{

   //   __UNREFERENCED_PARAMETER(pprimitiveimpl);

   //}


   //void window::aaa_clear_keyboard_focus(::windowing::window * pprimitiveimplGainingFocusIfAny)
   //{


   //}


   //void window::impl_set_keyboard_focus(::windowing::window * pprimitiveimpl)
   //{


   //}


   //void window::impl_erase_keyboard_focus(::windowing::window * pprimitiveimpl)
   //{


   //}


   //void window::aaa_impl_clear_keyboard_focus()
   //{


   //}


   void window::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      // if (::is_null(user_interaction()))
      // {

      //    throw ::exception(error_wrong_state);

      // }

      // user_interaction()->interaction_post(__allocate call_message_handler_task(user_interaction(), emessage, wparam, lparam));

      //auto pmessage

      //get_message()

      ::pointer<::message::message>pmessage;

      if (user_interaction())
      {

         pmessage = user_interaction()->get_message(emessage, wparam, lparam);

      }
      else
      {

         pmessage = get_message(emessage, wparam, lparam);

      }

      pmessage->m_pchannel = user_interaction();

      //return message_call(pmessage);

      post_message(pmessage);

   }


   //void window::post_non_client_destroy()
   //{

   //   ::pointer<window>pimpl = this;

   //   {

   //      _synchronous_lock synchronouslock(this->synchronization());

   //      try
   //      {

   //         erase_all_routes();

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //   //::channel::on_finish();

   //   if (!m_bDestroyImplOnly && user_interaction())
   //   {

   //      user_interaction()->post_non_client_destroy();

   //   }

   //   //::windowing::window::post_non_client_destroy();



   //   //if (user_interaction()->m_pthreadUserInteraction)
   //   //{

   //   //   auto pthread = user_interaction()->m_pthreadUserInteraction.cast < thread >();
   //   //
   //   //   if (pthread)
   //   //   {

   //   //      if (pthread->m_pimpl == this)
   //   //      {

   //   //         pthread->m_pimpl.release();

   //   //         pthread->finish();

   //   //      }

   //   //   }

   //   //}

   //   if (!m_bDestroyImplOnly)
   //   {

   //      user_interaction().release();

   //   }

   //}


   //void window::on_message_show_window(::message::message * pmessage)
   //{

   //   ::pointer<::message::show_window>pshowwindow(pmessage);

   //   //if (user_interaction())
   //   //{

   //   //   user_interaction()->set_need_redraw();

   //   //}

   //}


   //void window::_001OnPrioCreate(::message::message * pmessage)
   //{

   //   if (!user_interaction())
   //   {

   //      return;

   //   }

   //   //      if(::is_null(user_interaction()->m_pwindow))
   //   //      {
   //   //
   //   //         printf("user_interaction()->m_pwindow is null!! (8) (0x%" PRI0xPTR ")\n", (uptr) user_interaction()->m_pwindow);
   //   //
   //   //      }
   //   //      else
   //   //      {
   //   //
   //   //         printf("user_interaction()->m_pwindow is set!! (8) (0x%" PRI0xPTR ")\n", (uptr) user_interaction()->m_pwindow);
   //   //
   //   //      }
   //   //
   //   //      fflush(stdout);

   //   user_interaction()->defer_run_property(id_create);

   //   //      if(::is_null(user_interaction()->m_pwindow))
   //   //      {
   //   //
   //   //         printf("user_interaction()->m_pwindow is null!! (9) (0x%" PRI0xPTR ")", (uptr) user_interaction()->m_pwindow);
   //   //
   //   //      }
   //   //      else
   //   //      {
   //   //
   //   //         printf("user_interaction()->m_pwindow is set!! (9) (0x%" PRI0xPTR ")", (uptr) user_interaction()->m_pwindow);
   //   //
   //   //      }
   //   //
   //   //      fflush(stdout);

   //         //user_interaction()->call_procedures(CREATE_ROUTINE);

   //   //      if(::is_null(user_interaction()->m_pwindow))
   //   //      {
   //   //
   //   //         printf("user_interaction()->m_pwindow is null!! (10) (0x%" PRI0xPTR ")", (uptr) user_interaction()->m_pwindow);
   //   //
   //   //      }
   //   //      else
   //   //      {
   //   //
   //   //         printf("user_interaction()->m_pwindow is set!! (10) (0x%" PRI0xPTR ")", (uptr) user_interaction()->m_pwindow);
   //   //
   //   //      }
   //   //
   //   //      fflush(stdout);


   //}


   //void window::on_message_destroy(::message::message * pmessage)
   //{

   //   //synchronous_lock synchronouslock(this->synchronization());

   //   //try
   //   //{

   //   //   if (m_ptimerarray)
   //   //   {

   //   //      m_ptimerarray->destroy();

   //   //      m_ptimerarray.release(REFERENCING_DEBUGGING_THIS_NOTE(""));

   //   //   }

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //}


   void window::on_message_non_client_destroy(::message::message* pmessage)
   {

      if (user_interaction() && ::type(user_interaction()).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

      //post_non_client_destroy();

      //destroy();

   }


   void window::set_user_interaction(::acme::user::interaction* pacmeuserinteraction)
   {

      ::windowing::window_base::set_user_interaction(pacmeuserinteraction);

      //user_interaction() = pacmeuserinteraction;

   }


   void window::set_user_thread(::user::thread* puserthread)
   {

      m_puserthread = puserthread;

      if (!m_puserthread)
      {

         throw ::exception(error_wrong_state);

      }

   }


   void window::set_user_graphics_thread(::user::graphics_thread* pusergraphicsthread)
   {

      m_pgraphicsthread = pusergraphicsthread;

      if (!m_pgraphicsthread)
      {

         throw ::exception(error_wrong_state);

      }

   }


   void window::prio_install_message_routing(::channel* pchannel)
   {

      //if (g_p == nullptr)
      //{

      //   g_p = aaa_memory_new iptr_map < string >;

      //}

      //g_p->set_at((iptr)this, ::type(user_interaction()).name()) + "xxx" + ::type(this).name();
      MESSAGE_LINK(e_message_show_window, pchannel, this, &window::on_message_show_window);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &window::on_message_destroy);
      MESSAGE_LINK(e_message_non_client_destroy, pchannel, this, &window::on_message_non_client_destroy);
      MESSAGE_LINK(e_message_create, pchannel, this, &window::_001OnPrioCreate);
      MESSAGE_LINK(e_message_after_create, pchannel, this, &window::_001OnPrioAfterCreate);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &window::on_prio_message_set_focus);

      if (user_interaction() && ::type(user_interaction()).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

   }


   //void window::last_install_message_routing(::channel * pchannel)
   //{


   //}


   //void window::show_task(bool bShow)
   //{

   //   __UNREFERENCED_PARAMETER(bShow);

   //}


   //void window::redraw_add(::particle * pparticle)
   //{

   //}


   //void window::redraw_erase(::particle * pparticle)
   //{

   //}


   //bool window::has_redraw()
   //{

   //   return false;

   //}


   //void window::queue_message_handler(::message::message * pmessage)
   //{

   //   user_interaction()->message_handler(pmessage);

   //   //if (pmessage->m_bRet)
   //   //{

   //   //   return true;

   //   //}

   //   //return false;

   //}


   //void window::has_keyboard_focus() const
   //{

   //   if (user_interaction() == nullptr)
   //   {

   //      return false;

   //   }

   //   ::pointer<::user::interaction>pinteraction = user_interaction()->get_host_user_interaction();

   //   if (pinteraction.is_null())
   //   {

   //      return false;

   //   }

   //   if (pinteraction == this)
   //   {

   //      return false;

   //   }

   //   if (!pinteraction->has_keyboard_focus())
   //   {

   //      return false;

   //   }

   //   ::pointer<::windowing::window>pimpl = pinteraction->m_pimpl;

   //   if (pimpl.is_null())
   //   {

   //      return false;

   //   }

   //   return pimpl->m_pprimitiveFocus == user_interaction();

   //}


   //void window::is_active()
   //{

   //   if (user_interaction() == nullptr)
   //   {

   //      return false;

   //   }

   //   return user_interaction() == user_interaction()->GetActiveWindow();

   //}


   ////void window::create_host(::user::interaction * puserinteraction, enum_parallelization eparallelization)
   //void window::create_host(::user::interaction * puserinteraction)
   //{

   //   //return false;

   //}


   void window::create_child(::user::interaction* puserinteraction, ::user::interaction_base* puserprimitiveParent)
   {

      //return false;

   }


   //void window::is_this_enabled() const
   //{

   //   if (!user_interaction())
   //   {

   //      return false;

   //   }

   //   return user_interaction()->m_ewindowflag & e_window_flag_enable;

   //}


   // void window::SetWindowDisplayChanged()
   // {

   // }


   //   void window::_window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation)
   //   {
   //
   //   }
   //
   //
   //   void window::_window_show_change_visibility_locked()
   //   {
   //
   //   }
   //
   //
   //   void window::_window_request_presentation_locked()
   //   {
   //
   //   }
   //
   //
   //   void window::_window_request_presentation_unlocked()
   //   {
   //
   //   }


      //void window::enable_window(bool bEnable)
      //{

      //   //bool bWasDisabled = !(user_interaction()->m_ewindowflag & e_window_flag_enable);

      //   user_interaction()->m_ewindowflag.set(e_window_flag_enable, bEnable);

      //   user_interaction()->set_need_redraw();

      //   user_interaction()->post_redraw();

      //   //return bWasDisabled;

      //}


      //void window::user_interaction_on_hide()
      //{


      //}


      //int window::GetUpdateRgn(class draw2d::region *,bool)
      //{

      //   return 0;

      //}


      //void window::Invalidate(bool)
      //{


      //}


      //void window::InvalidateRect(::int_rectangle const &,bool)
      //{


      //}


      //void window::InvalidateRgn(class draw2d::region *,bool)
      //{


      //}


      //void window::ValidateRect(::int_rectangle const &)
      //{


      //}


      //void window::ValidateRgn(class draw2d::region *)
      //{


      //}


      //void window::ShowOwnedPopups(bool)
      //{


      //}


      //::graphics::graphics * window::get_window_graphics(void)
      //{

      //   return nullptr;

      //}


      //bool window::is_composite()
      //{

      //   return false;

      //}


      //void window::_task_transparent_mouse_event()
      //{

      //}


      //bool window::IsTopParentActive()
      //{

      //   return false;

      //}


#ifdef LINUX


   lresult window::send_x11_event(void* phappening)
   {

      throw interface_only();

      return 0;

   }


#endif


   //::user::interaction * window::top_level()
   //{

   //   return user_interaction()->top_level();

   //}


   ::user::frame_interaction* window::parent_frame()
   {

      return user_interaction()->parent_frame();

   }


   //::windowing::window * window::window()
   //{

   //   if (::is_null(user_interaction()))
   //   {

   //      return nullptr;

   //   }

   //   return user_interaction()->m_pwindow;

   //}


   //::aura::application * window::get_app()
   //{

   //   return m_papplication ? m_papplication->m_papplication : nullptr;

   //}


   //::aura::session * window::session()
   //{

   //   return m_papplication ? m_papplication->m_psession : nullptr;

   //}


   //::aura::system * primitive_implacmesystem()
   //{

   //   return system() ? system() : nullptr;

   //}

   void window::_raw_client_to_screen(::int_point& point)
   {

      user_interaction()->client_to_screen(::user::e_layout_design)(point);

   }

   void window::_raw_screen_to_client(::int_point& point)
   {

      user_interaction()->screen_to_client(::user::e_layout_design)(point);

   }

   ::windowing::window* window::windowing_window()
   {

      return this;

   }
   //::trace_statement & window::trace_statement_prefix(::trace_statement & statement) const
   //{

   //   statement << "usrimpl ";

   //   if (user_interaction())
   //   {

   //      user_interaction()->raw_trace_statement_prefix(statement);

   //   }

   //   return statement;

   //}


   void window::_user_send(const ::procedure& procedure)
   {

      if (!user_interaction())
      {

         ::channel::_user_send(procedure);

         return;

      }

      user_interaction()->_user_send(procedure);

   }


   void window::_user_post(const ::procedure& procedure)
   {

      if (!user_interaction())
      {

         ::channel::_user_post(procedure);

         return;

      }

      user_interaction()->_user_post(procedure);

   }


   void window::_main_send(const ::procedure& procedure)
   {

      if (!user_interaction())
      {

         ::channel::_main_send(procedure);

         return;

      }

      user_interaction()->_main_send(procedure);

   }


   void window::_main_post(const ::procedure& procedure)
   {

      if (!user_interaction())
      {

         ::channel::_main_post(procedure);

         return;

      }

      user_interaction()->_main_post(procedure);

   }


   void window::on_set_focus_to_child()
   {

   }
   //void window::set_opacity(double dOpacity)
   //{


   //}


   bool window::on_window_configure_unlocked()
   {

      _017_on_window_get_configuration();

      return true;

   }


   bool window::_017_on_window_configure_unlocked_timer()
   {

      if (m_time017LastConfigureUnlocked.elapsed() > 600_ms)
      {

         return false;

      }

      information() << "window::on_window_configure_unlocked going to get configuration";

      _017_on_window_get_configuration();

      return true;


   }



   void window::_017_on_window_get_configuration()
   {

      auto r = ::int_rectangle(m_pointWindow, m_sizeWindow);

      _on_configure_notify_unlocked(r);

      // preempt(40_ms);
      //
      // main_send([this]()
      // {
      //
      //    auto r = get_window_rectangle();
      //
      //    information() << "window::_on_get_configuration";
      //
      //    _017_on_window_configure_delayed(r.left(), r.top(), r.width(), r.height());
      //
      // });

   }


   void window::_017_on_window_configure_delayed(int x, int y, int cx, int cy)
   {

      auto r = ::int_rectangle_dimension(x, y, cx, cy);

      _on_configure_notify_unlocked(r);

   }


   void window::_017_on_window_configure_immediate(int x, int y, int cx, int cy)
   {

      information() << "::windowing_gtk3::window::_on_configure_immediate " << ::int_rectangle_dimension(x, y, cx, cy);

      auto puserinteraction = user_interaction();

      ::int_size s(cx, cy);

      if (m_sizeWindow != s)
      {

         m_sizeWindow = s;

         puserinteraction->layout().m_statea[::user::e_layout_window].m_size = s;

         if (puserinteraction->layout().m_statea[::user::e_layout_sketch].m_size != s)
         {

            puserinteraction->layout().m_statea[::user::e_layout_sketch].m_size = s;

            puserinteraction->set_need_layout();

            puserinteraction->set_need_redraw();

            puserinteraction->post_redraw();

         }

      }

      ::int_point p(x, y);

      if (m_pointWindow != p)
      {

         m_pointWindow = p;

         puserinteraction->layout().m_statea[::user::e_layout_window].m_point2 = p;

         if (puserinteraction->layout().m_statea[::user::e_layout_sketch].m_point2 != p)
         {

            puserinteraction->layout().m_statea[::user::e_layout_sketch].m_point2 = p;

         }

      }

   }


   void window::_017_set_window_configure_unlocked_timer()
   {

      m_time017LastConfigureUnlocked.Now();

      ::cast<::user::interaction> puserinteraction = m_pacmeuserinteraction;

      puserinteraction->set_timer(e_timer_configure_unlocked, 100_ms);

   }



} // namespace windowing


//CLASS_DECL_AURA ::user::interaction * __user_interaction(::windowing::window * pwindow)
//{
//
//   if (::is_null(pwindow))
//   {
//
//      return nullptr;
//
//   }
//
//   auto pwindow = pwindow->m_pwindow;
//
//   if (::is_null(pwindow))
//   {
//
//      return nullptr;
//
//   }
//
//   auto puserinteraction = user_interaction();
//
//   if (::is_null(puserinteraction))
//   {
//
//      return nullptr;
//
//   }
//
//   return puserinteraction;
//
//}



