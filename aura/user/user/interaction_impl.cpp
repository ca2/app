#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/user/_user.h"
#endif
//#include "acme/operating_system/cross.h"
#include "aura/platform/message_queue.h"
#include "aura/message.h"
#include "interaction_thread.h"
#include "interaction_prodevian.h"
#include "aura/operating_system/_node.h"
#include "acme/operating_system/_user.h"
#include "aura/graphics/graphics/_.h"
#include "aura/graphics/graphics/_graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/windowing/text_editor_interface.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/lock.h"
//#ifdef _UWP
//#include "aura/operating_system/windows_common/draw2d_direct2d_global.h"
//#endif

point_i32 g_pointLastBottomRight;

#undef ALOG_CONTEXT
#define ALOG_CONTEXT (::trace_object(::trace_category_windowing))

//#include <mutex>


#ifdef WINDOWS_DESKTOP
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#endif

CLASS_DECL_ACME void monitor_pointer(void * p);

#define REDRAW_HINTING
//CLASS_DECL_AURA bool task_set_name(const ::string &psz);

#define IMAGE_OK(pimpl) (::is_set(pimpl) && pimpl->area() > 0)
//void windowing_output_debug_string(const ::string & pszDebugString);

#define REDRAW_PROFILE_NORMAL 5

#define REDRAW_PROFILE REDRAW_PROFILE_NORMAL


#define HARD_DEBUG 0
//#define REDRAW_HINTING
#undef REDRAW_HINTING
//

namespace user
{


   interaction_impl::interaction_impl()
   {

      user_common_construct();

   }


   interaction_impl::~interaction_impl()
   {

   }


   void interaction_impl::user_common_construct()
   {

      m_pImpl2 = nullptr;

      m_pinteractionimpl = this;

      m_bOfflineRender = false;

      m_iState1 = 0;

      m_uCodePage = 0;

      m_iLangId = 0;

      m_bPendingRedraw = false;

      m_bEatMoveEvent = false;

      m_bEatSizeEvent = false;

      m_bOkToUpdateScreen = true;
      m_bUpdatingBuffer = false;
      //m_bFocus = false;
      m_bCursorRedraw = false;

      defer_create_mutex();

      m_bScreenRelativeMouseMessagePosition  = true;
      m_bTranslateMouseMessageCursor         = true;
      m_bComposite                           = true;
      m_bUpdateGraphics                      = false;
      //m_pwindow                              = nullptr;
      //m_pprimitiveFocus                      = nullptr;
      m_bPendingRedraw                       = false;
      m_bTransparentMouseEvents              = false;

#if defined(APPLE_IOS) || defined(ANDROID)

      set_fps(12.0);

#elif defined(_UWP)

      set_fps(60.0);

#else

      set_fps(60.0);

#endif

   }


   void interaction_impl::on_tsf_activate(bool bActivate)
   {

      if (bActivate)
      {

         //get_wnd()->pred([this]()
         //   {

         //      //ImmSetOpenStatus(m_puserthread->m_himc, true);



         ////      if (m_puserthread->m_peditwnd == nullptr)
         ////      {

         ////         m_puserthread->m_peditwnd = new CTSFEditWnd(psystem->m_hinstance, m_puserinteraction->get_handle());

         ////         m_puserthread->m_peditwnd->_Initialize(m_puserthread->m_pthreadmgr, m_puserthread->m_tfClientID);

         ////      }

         ////      m_puserthread->m_peditwnd->on_edit_set_focus(dynamic_cast <::user::interaction * > (get_keyboard_focus()));

         //   });

      }

   }



   ::mutex * interaction_impl::draw_mutex()
   {

      if (m_pmutexDraw == nullptr)
      {

         m_pmutexDraw = __new(::mutex());

      }

      return m_pmutexDraw;

   }


   ::user::interaction_impl * interaction_impl::get_user_interaction_impl()
   {

      return this;

   }


   bool interaction_impl::has_pending_redraw_flags()
   {

      //if (m_bCursorRedraw)
      //{

      //   auto psession = get_session();

      //   auto puser = psession->user();

      //   auto pwindowing = puser->windowing();

      //   auto pointCursor = pwindowing->get_cursor_position();

      //   if (m_pointMouseMove != pointCursor)
      //   {

      //      if (_001IsPointInside(pointCursor))
      //      {

      //         return true;

      //      }

      //   }

      //}

      return ::user::primitive_impl::has_pending_redraw_flags();

   }


   void interaction_impl::set_need_layout()
   {

      m_puserinteraction->set_need_layout();

   }


   //void interaction_impl::window_move(i32 x, i32 y)
   //{

   //   auto & stateRequest = m_puserinteraction->request_state();

   //   stateRequest.m_point.x = x;

   //   stateRequest.m_point.y = y;

   //   m_puserinteraction->set_reposition();

   //   return true;

   //}


   bool interaction_impl::has_pending_focus()
   {

      auto psession = get_session();

      if (::is_null(psession))
      {

         return false;

      }

      if (::is_null(psession->m_pimplPendingFocus2))
      {

         return false;

      }

      if (psession->m_pimplPendingFocus2 != this)
      {

         return false;

      }

      return true;

   }


   bool interaction_impl::clear_pending_focus()
   {

      auto psession = get_session();

      if (::is_null(psession))
      {

         return false;

      }

      if (::is_null(psession->m_pimplPendingFocus2))
      {

         return false;

      }

      if (psession->m_pimplPendingFocus2 != this)
      {

         return false;

      }

      psession->m_pimplPendingFocus2 = nullptr;

      return true;

   }


   //void interaction_impl::set_destroying()
   //{

   //   m_bDestroying = true;

   //}


   bool interaction_impl::set_pending_focus()
   {

      auto psession = get_session();

      if (::is_null(psession))
      {

         return false;

      }

      psession->m_pimplPendingFocus2 = this;

      return true;

   }


   void interaction_impl::create_message_queue(::user::interaction * pinteraction, const ::string & lpszName)
   {

      if(_is_window())
      {

         set_window_text(lpszName);

      }
      else
      {

         //auto pusersystem=__new(::user::system(0, nullptr, lpszName, WS_CHILD, nullptr));

         //pusersystem->m_createstruct.hwndParent = MESSAGE_WINDOW_PARENT;

         pinteraction->m_bMessageWindow = true;

         create_host(pinteraction);
         //{

         //   return false;

         //}

      }

      //return true;

   }



   //void interaction_impl::create_native_window(::user::native_window_initialize* pinitialize)
   //{

   //   __UNREFERENCED_PARAMETER(pinitialize);
   //   throw ::interface_only();

   //   return false;

   //}

//#ifdef WINDOWS_DESKTOP
//
//
//   void interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
//   {
//      __UNREFERENCED_PARAMETER(pwi);
//      throw ::interface_only();
//      return false;
//   }
//
//   void interaction_impl::GetScrollBarInfo(::i32 idObject,PSCROLLBARINFO psbi) const
//   {
//      __UNREFERENCED_PARAMETER(idObject);
//      __UNREFERENCED_PARAMETER(psbi);
//      throw ::interface_only();
//      return false;
//   }
//
//   void interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
//   {
//      __UNREFERENCED_PARAMETER(pti);
//      throw ::interface_only();
//      return false;
//   }
//
//#endif

#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(FREEBSD)


   ::user::interaction_impl * interaction_impl::GetAncestor(::u32 gaFlags) const
   {

      __UNREFERENCED_PARAMETER(gaFlags);

      throw ::interface_only();

      return nullptr;

   }


   //void interaction_impl::AnimateWindow(::duration ::duration,u32 dwFlags)
   //{
   //   __UNREFERENCED_PARAMETER(::duration);
   //   __UNREFERENCED_PARAMETER(dwFlags);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::FlashWindowEx(u32 dwFlags,::u32 uCount,::duration tickTimeout)
   //{
   //   __UNREFERENCED_PARAMETER(dwFlags);
   //   __UNREFERENCED_PARAMETER(uCount);
   //   __UNREFERENCED_PARAMETER(tickTimeout);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::SetLayeredWindowAttributes(::color::color crKey,byte bAlpha,u32 dwFlags)
   //{
   //   __UNREFERENCED_PARAMETER(crKey);
   //   __UNREFERENCED_PARAMETER(bAlpha);
   //   __UNREFERENCED_PARAMETER(dwFlags);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT_I32 * pptDst,SIZE_I32 * psize,
   //      ::draw2d::graphics * pDCSrc,POINT_I32 * pptSrc,::color::color crKey,BLENDFUNCTION * pblend,u32 dwFlags)
   //{
   //   __UNREFERENCED_PARAMETER(pDCDst);
   //   __UNREFERENCED_PARAMETER(pptDst);
   //   __UNREFERENCED_PARAMETER(psize);
   //   __UNREFERENCED_PARAMETER(pDCSrc);
   //   __UNREFERENCED_PARAMETER(pptSrc);
   //   __UNREFERENCED_PARAMETER(crKey);
   //   __UNREFERENCED_PARAMETER(pblend);
   //   __UNREFERENCED_PARAMETER(dwFlags);
   //   throw ::interface_only();

   //   return false;
   //}

   //void interaction_impl::GetLayeredWindowAttributes(::color::color * pcrKey,byte * pbAlpha,u32 * pdwFlags) const
   //{
   //   __UNREFERENCED_PARAMETER(pcrKey);
   //   __UNREFERENCED_PARAMETER(pbAlpha);
   //   __UNREFERENCED_PARAMETER(pdwFlags);
   //   throw ::interface_only();

   //   return false;
   //}

   //void interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics,::u32 nFlags) const
   //{
   //   __UNREFERENCED_PARAMETER(pgraphics);
   //   __UNREFERENCED_PARAMETER(nFlags);
   //   throw ::interface_only();

   //   return false;
   //}

#endif


   //lresult interaction_impl::default_window_procedure()
   //{
   //
   //   return default_window_procedure(m_uiMessage, m_wparam, m_lparam);

   //}


   void interaction_impl::pre_subclass_window()
   {

      throw ::interface_only();

   }


   ::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
   {

      __UNREFERENCED_PARAMETER(pdata);

      throw ::interface_only();

      return nullptr;

   }


   void * interaction_impl::get_os_data() const
   {

      throw ::interface_only();

      return nullptr;

   }


   //void interaction_impl::create_host(::user::interaction * pinteraction, ::user::primitive * pprimitiveParent)
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
   bool interaction_impl::pre_create_window(::user::system * pusersystem)
   {

      __UNREFERENCED_PARAMETER(pusersystem);

      return true;

   }


   void interaction_impl::operating_system_create_host()
   {

      //      auto pwindowMain = m_psystem->m_paurasystem->m_pwindowMain;
      //
      //      if (pwindowMain && !pwindowMain->m_puserinteractionimpl)
      //      {
      //
      //         m_pwindow = m_psystem->m_paurasystem->m_pwindowMain;
      //
      //         m_pwindow->m_puserinteractionimpl = this;
      //
      //         m_puserinteraction->m_pinteractionimpl = this;
      //
      //      }
      //      else
      //      {
      //
      //         //auto estatus =
      //
      //         __construct(m_pwindow);
      //
      //         //if (!estatus)
      //         //{
      //
      //         //   return estatus;
      //
      //         //}
      //
      //         if (!m_psystem->m_paurasystem->m_pwindowMain)
      //         {
      //
      //            m_psystem->m_paurasystem->m_pwindowMain = m_pwindow;
      //
      //         }
      //
      //      }
      //
      //      //auto estatus =
      //
      //      m_pwindow->create_window(this);
      //
      //      //if (!estatus)
      //      //{
      //
      //      //   return estatus;
      //
      //      //}
      //
      //      //return true;

      __pointer(::user::system) pusersystem;

      if (m_puserinteraction->m_pusersystem)
      {

         pusersystem = m_puserinteraction->m_pusersystem;

      }
      else
      {

         pusersystem = __new(::user::system);

      }

      //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));
      //
      if (!m_puserinteraction->pre_create_window(pusersystem))
      {

         //return false;

         throw ::exception(error_failed);

      }

      __refer(m_puserinteraction->m_pthreadUserInteraction, ::get_task());

      //m_pthreadUserImpl = m_puserinteraction->m_pthreadUserInteraction;

      install_message_routing(m_puserinteraction);

      bool bOk = true;

      //      if(pusersystem->m_createstruct.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
      //      {
      //
      //         auto pwindowing = m_pwindowwindowing();
      //
      //         m_oswindow = pwindowing->new_message_window(this);
      //
      //         m_puserinteraction->m_bMessageWindow = true;
      //
      //         //send_message(e_message_create, 0, (LPARAM) &cs);
      //
      //      }
      //      else
      {

         m_puserinteraction->m_bMessageWindow = false;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         //pwindowing->windowing_send([&]()
         //   {

         //      auto psession = get_session();

         //      auto puser = psession->user();

         //      auto pwindowing = puser->windowing();

         m_pwindow = pwindowing->new_window(this);

         if (m_pwindow)
         {

            output_debug_string("window created");

         }
         else
         {

            output_debug_string("window not created");

         }

         //});

      }

      //      if(bOk)
      //      {
      //
      //         m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);
      //
      //         m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;
      //
      //      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }


   }


   
   void interaction_impl::native_create_host_alternate()
   {

//      auto pwindowMain = m_psystem->m_paurasystem->m_pwindowMain;
//
//      if (pwindowMain && !pwindowMain->m_puserinteractionimpl)
//      {
//
//         m_pwindow = m_psystem->m_paurasystem->m_pwindowMain;
//
//         m_pwindow->m_puserinteractionimpl = this;
//
//         m_puserinteraction->m_pinteractionimpl = this;
//
//      }
//      else
//      {
//
//         //auto estatus =
//
//         __construct(m_pwindow);
//
//         //if (!estatus)
//         //{
//
//         //   return estatus;
//
//         //}
//
//         if (!m_psystem->m_paurasystem->m_pwindowMain)
//         {
//
//            m_psystem->m_paurasystem->m_pwindowMain = m_pwindow;
//
//         }
//
//      }
//
//      //auto estatus =
//
//      m_pwindow->create_window(this);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //return true;

      __pointer(::user::system) pusersystem;

      if(m_puserinteraction->m_pusersystem)
      {

         pusersystem = m_puserinteraction->m_pusersystem;

      }
      else
      {

         pusersystem = __new(::user::system);

      }

//      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));
//
      if (!m_puserinteraction->pre_create_window(pusersystem))
      {

         //return false;

         throw ::exception(error_failed);

      }

      __refer(m_puserinteraction->m_pthreadUserInteraction, ::get_task());

      //m_pthreadUserImpl = m_puserinteraction->m_pthreadUserInteraction;

      install_message_routing(m_puserinteraction);

      bool bOk = true;

//      if(pusersystem->m_createstruct.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
//      {
//
//         auto pwindowing = m_pwindowwindowing();
//
//         m_oswindow = pwindowing->new_message_window(this);
//
//         m_puserinteraction->m_bMessageWindow = true;
//
//         //send_message(e_message_create, 0, (LPARAM) &cs);
//
//      }
//      else
      {

         m_puserinteraction->m_bMessageWindow = false;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->windowing_send([&]()
                                    {

                                       auto psession = get_session();

                                       auto puser = psession->user();

                                       auto pwindowing = puser->windowing();

                                       m_pwindow = pwindowing->new_window(this);

                                       if(m_pwindow)
                                       {

                                          output_debug_string("window created");

                                       }
                                       else
                                       {

                                          output_debug_string("window not created");

                                       }

                                    });

      }

//      if(bOk)
//      {
//
//         m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);
//
//         m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;
//
//      }

      if(!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   void interaction_impl::create_host(::user::interaction * puserinteraction)
   {

      m_puserinteraction = puserinteraction;

      m_puserinteraction->m_pprimitiveimpl = this;

      m_puserinteraction->m_pinteractionimpl = this;

      #if !defined(_UWP)

            m_puserinteraction->m_ewindowflag |= e_window_flag_postpone_visual_update;

      #endif

      bool bNewOwnThread = true;

      bool bProdevianThread = true;

      //if (m_puserinteraction->GetStyle() & WS_CHILD)
      //{

      //   // if child, uses parent window thread,

      //   bNewOwnThread = false;

      //   bProdevianThread = false;

      //}

      if (m_puserinteraction->m_bMessageWindow)
      {

         // except if "message"-only-window, in which casen it will have own thread

         bNewOwnThread = true;

         bProdevianThread = false;

      }

      if (m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window)
      {

         if (m_puserinteraction->m_puserinteractionOwner)
         {

            auto pthread = m_puserinteraction->m_puserinteractionOwner->m_pthreadUserInteraction;

            m_puserinteraction->m_pthreadUserInteraction = pthread;
            
            __refer(m_puserthread, pthread.get());

         }

         // all except if satellite window it will use calling thread/parent window thread

         bNewOwnThread = false;

      }

      if (!m_puserinteraction->is_graphical())
      {

         bProdevianThread = false;

      }

      //m_puserinteraction->place(rectangle_i32_dimension(
      //                      pusersystem->m_createstruct.x,
      //                      pusersystem->m_createstruct.y,
      //                      pusersystem->m_createstruct.cx,
      //                      pusersystem->m_createstruct.cy));

      //auto psynca = __new(synchronization_array);

      //__pointer(manual_reset_event) peventStartedUser;

      //__pointer(manual_reset_event) peventStartedProdevian;

      __pointer(::user::thread) puserthread;

      if (bNewOwnThread)
      {

         puserthread = __create_new<::user::thread>();

         __refer(m_puserthread, puserthread);

         auto papp = get_app();

         if (::is_set(papp))
         {

            papp->add_task(m_puserthread);

         }

         m_puserthread->initialize_user_thread(this);

         m_puserinteraction->__refer(m_puserinteraction->m_pthreadUserInteraction, m_puserthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE(__FUNCTION__));

         //peventStartedUser = __new(manual_reset_event());

         //m_puserthread->m_peventStarted = peventStartedUser;

      }

      m_puserthread->add_task(m_puserinteraction);

      __pointer(::user::prodevian) pprodevian;

      if (bProdevianThread && m_puserinteraction->is_graphical())
      {

         pprodevian = __create_new < ::user::prodevian >();

         __refer(m_pprodevian, pprodevian);

         m_pprodevian->initialize_prodevian(this);

         m_puserinteraction->add_task(m_pprodevian);

         m_pprodevian->__refer(m_pprodevian->m_puserthread, m_puserthread);

      }

      if (bNewOwnThread)
      {

         //if (!m_puserthread->begin_synch())
         m_puserthread->branch_synchronously();
         //{

         //   __release(m_pprodevian);

         //   __release(m_puserthread);

         //   m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

         //   return false;

         //}

//         psynca->add(peventStartedUser);
//
//         auto proutine = __routine([this, psynca]()
//            {
//
//               if (!m_puserinteraction ||
//                  //(m_puserthread->m_bCreateNativeWindowOnInteractionThread
//                     //&&
//                  !m_puserinteraction->is_window())
//                  //)
//               {
//
//                  return;
//
//               }
//
//               if (m_puserthread->m_result.failed())
//               {
//
//                  if (m_puserinteraction)
//                  {
//
//                     m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);
//
//                  }
//
//                  __release(m_pprodevian);
//
//                  __release(m_puserthread);
//
//                  return;
//
//               }
//
//               //peventStartedUser.release();
//
//               if (::is_set(m_pprodevian))
//               {
//
//                  if (m_pprodevian->m_result.failed())
//                  {
//
//                     if (m_puserinteraction)
//                     {
//
//                        m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);
//
//                     }
//
//                     __release(m_pprodevian);
//
//                     __release(m_puserthread);
//
//                     return;
//
//                  }
//
//                 // peventStartedProdevian.release();
//
//               }
//
//            });

         //if (pusersystem->m_procedureSuccess)
         //{

         //   fork([psynca, proutine, pusersystem]()
         //   {

         //      psynca->wait();

         //      (*proutine)();

         //      pusersystem->m_procedureSuccess();

         //   });

         //}
         //else
         //{

            ///psynca->wait();

         //   (*proutine)();

         //}

      }
      else
      {

         //psynca->wait(true, one_minute());

         //if (::is_set(m_pprodevian))
         //{

           // peventStartedProdevian.release();

         //}

         operating_system_create_host();

         ////if (!native_create_host())
         //{

         //   return false;

         //}

      }

      //if (m_puserthread && !m_puserthread->m_bCreateNativeWindowOnInteractionThread)
      //{

      //   send_message(e_message_create, 0, (lparam)&pusersystem);

      //   //m_puserinteraction->set_dim(pusersystem->m_createstruct.x, pusersystem->m_createstruct.cy, pusersystem->m_createstruct.cx, pusersystem->m_createstruct.cy);

      //   send_message(e_message_size, 0, MAKELPARAM(pusersystem->m_createstruct.cx, pusersystem->m_createstruct.cy));

      //   m_puserinteraction->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);

      //   m_puserinteraction->m_ewindowflag |= ::e_window_flag_is_window;

      //   m_puserinteraction->m_ewindowflag |= ::e_window_flag_window_created;

      //}

      //return true;

   }


   ::color::color interaction_impl::screen_pixel(int x, int y) const
   {

      auto origin = m_puserinteraction->const_layout().window().origin();

      if(::is_null(m_pgraphics))
      {

         return 0;

      }

      return m_pgraphics->get_screen_image()->pixel(x - origin.x, y - origin.y);

   }


   //void interaction_impl::native_create_window()
   //{
   //   return false;
   //}


//   void interaction_impl::create_host(::user::interaction * puserinteraction)
//   {
//
//      m_puserinteraction = puserinteraction;
//      // can't use for desktop or pop-up windows (use create_window_ex instead)
//      //ASSERT(puiParent != nullptr);
//      //ASSERT((uStyle & WS_POPUP) == 0);
//
//      //auto pusersystem = __new(::user::system);
//
//      //pusersystem->m_createstruct.dwExStyle = 0;
//
////#ifdef WINDOWS
////
////      wstring wstrClassName(pszClassName);
////      pusersystem->m_createstruct.lpszClass = wstrClassName;
////      wstring wstrWindowName(pszWindowName);
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
//      //pusersystem->m_createstruct.x = rectangle.left;
//      //pusersystem->m_createstruct.y = rectangle.top;
//      //pusersystem->m_createstruct.cx = rectangle.width();
//      //pusersystem->m_createstruct.cy = rectangle.height();
//      //pusersystem->m_createstruct.hwndParent = puiParent->get_safe_handle();
//      //pusersystem->m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (LPVOID)pcreate;
//
//      return native_create_window();
//
//   }


   void interaction_impl::prio_install_message_routing(::channel * pchannel)
   {

      ::user::primitive_impl::prio_install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &interaction_impl::_001OnPrioCreate);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::on_prio_message_set_focus);

   }


   void interaction_impl::last_install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_create, pchannel, this, &interaction_impl::on_message_create);

      ::user::primitive_impl::last_install_message_routing(pchannel);

      if (!m_puserinteraction->m_bMessageWindow)
      {

         MESSAGE_LINK(e_message_redraw, pchannel, this, &interaction_impl::_001OnRedraw);
         MESSAGE_LINK(e_message_apply_visual, pchannel, this, &interaction_impl::_001OnApplyVisual);


//#ifndef LINUX
         MESSAGE_LINK(e_message_move, pchannel, this, &interaction_impl::on_message_move);
         MESSAGE_LINK(e_message_size, pchannel, this, &interaction_impl::on_message_size);
//#endif


         MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_impl::on_message_show_window);
         MESSAGE_LINK(e_message_kill_focus, pchannel, this, &interaction_impl::on_message_kill_focus);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::on_message_set_focus);

      }

      MESSAGE_LINK(e_message_destroy_window, pchannel, this, &interaction_impl::_001OnDestroyWindow);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &interaction_impl::on_message_destroy);

   }


   void interaction_impl::_000OnMouseLeave(::message::message * pmessage)
   {

      if (m_bDestroyImplOnly)
      {

         return;

      }

      m_puserinteraction->m_bMouseHover = false;

#ifdef WINDOWS_DESKTOP
      if (!m_bTransparentMouseEvents)
#endif
      {

         ::point_i32 pointInvalid; // For long future hope still : Invalid

         minimum(pointInvalid.x);
         minimum(pointInvalid.y);

         _on_mouse_move_step(pointInvalid);

         //__pointer(::user::interaction) pinteraction;

         //::rectangle_i32 rectangleUi;

         //auto psession = get_session();

         //auto puser = psession->user();

         //auto pwindowing = puser->windowing();

         //auto pointCursor = pwindowing->get_cursor_position();

         //::user::interaction_array uia;

         //{

         //   _synchronous_lock synchronouslock(mutex());

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


   void interaction_impl::_001OnTriggerMouseInside()
   {

      m_puserinteraction->m_bMouseHover = true;

   }


   //void interaction_impl::_008OnMouse(::message::mouse * pmouse)
   //{

   //   if(!m_puserinteraction)
   //   {

   //      return;

   //   }

   //   bool bPointInside;

   //   bPointInside = m_puserinteraction->_001IsPointInside(pmouse->m_point);

   //   if (!bPointInside)
   //   {

   //      if (pmouse->userinteraction() == m_puserinteraction)
   //      {

   //         bPointInside = true;

   //      }

   //   }

   //   if (pmouse->m_atom == e_message_left_button_up)
   //   {

   //      ::output_debug_string("lbutton_up");

   //   }

   //   if(pmouse->m_atom == ::e_message_left_button_down)
   //   {

   //      on_configuration_change(m_puserinteraction);

   //   }

   //   {

   //      ::user::interaction_array uia;

   //      {

   //         _synchronous_lock synchronouslock(mutex());

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

   //   auto psession = get_session();

   //   if (!m_puserinteraction->m_bMouseHover && bPointInside)
   //   {

   //      m_puserinteraction->_001OnTriggerMouseInside();

   //   }

   //   if(m_pwindow->has_capture())
   //   {

   //      if (pmouse->m_atom == e_message_left_button_up)
   //      {

   //         ::output_debug_string("lbutton_up");

   //      }

   //      ::user::interaction * puiCapture = m_puserinteractionCapture;

   //      if (puiCapture == nullptr)
   //      {

   //         puiCapture = m_puserinteraction;

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

   //   if (m_puserinteraction != nullptr)
   //   {


   //      if (pmouse->m_atom == e_message_left_button_up)
   //      {

   //         ::output_debug_string("lbutton_up");

   //      }

   //      //_synchronous_lock synchronouslock(mutex_children());

   //      auto puserinteraction = m_puserinteraction->child_from_point(pmouse->m_point);

   //      if (!puserinteraction)
   //      {

   //         puserinteraction = m_puserinteraction;

   //      }

   //      puserinteraction->message_handler(pmouse);



   //   }

   //   if (pmouse->m_bRet)
   //   {

   //      return;

   //   }

   //}


   void interaction_impl::add_prodevian(::matter * pmatter)
   {

      _synchronous_lock synchronouslock(mutex());

      auto bAdded = m_matteraProdevian.add_unique(pmatter);

      if (bAdded)
      {

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

      //return true;

   }


   void interaction_impl::erase_prodevian(::matter * pmatter)
   {

      _synchronous_lock synchronouslock(mutex());

      bool bRemoved = m_matteraProdevian.erase(pmatter) > 0;

      if (bRemoved)
      {

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

      //return true;

   }


   bool interaction_impl::is_prodevian(const ::matter * pmatter) const
   {

      _synchronous_lock synchronouslock(mutex());

      return m_matteraProdevian.contains(pmatter);

   }

   void interaction_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      if (pinterface == nullptr)
      {

         return;

      }

      bool bWasEmpty = false;
      
      {

         _synchronous_lock synchronouslock(mutex());

         bWasEmpty = m_userinteractionaMouseHover.is_empty();

         m_userinteractionaMouseHover.add_unique(pinterface);

      }

      if (bWasEmpty)
      {

         track_mouse_hover();

      }

      //return true;

   }


   void interaction_impl::track_mouse_hover()
   {

      m_pwindow->track_mouse_hover();

   }

   
   void interaction_impl::track_mouse_leave()
   {

      //__defer_fork(MouseLeave);

   }
   
   
   void interaction_impl::_on_mouse_move_step(const ::point_i32 & pointCursor, bool bMouseLeave)
   {

      _synchronous_lock synchronouslock(mutex());

      for(::index i = 0; i < m_userinteractionaMouseHover.get_count(); )
      {

         auto pinteraction = m_userinteractionaMouseHover[i];

         if(pinteraction == m_puserinteractionMouseCapture)
         {

            i++;

         }
         else if(!bMouseLeave && pinteraction->_001IsPointInsideInline(pointCursor))
         {

            i++;

         }
         else
         {

            

            m_userinteractionaMouseHover.erase_at(i);

            ///pinteraction->m_bTrackMouseLeave = false;

            synchronouslock.unlock();

            pinteraction->post_message(e_message_mouse_leave);

            synchronouslock.lock();

         }

      }

   }

   
//   void interaction_impl::mouse_hover_step(const __status < ::point_i32 > & statusPointCursor)
//   {
//
//      decltype(m_uiptraMouseHover) uia;
//
//      {
//
//         _synchronous_lock synchronouslock(mutex());
//
//         if (statusPointCursor.m_estatus != success)
//         {
//
//            uia = ::move(m_uiptraMouseHover);
//
//         }
//         else
//         {
//
//            for (::index i = 0; i < m_uiptraMouseHover.get_count();)
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


   bool interaction_impl::mouse_hover_erase(::user::interaction * pinterface)
   {

      _synchronous_lock synchronouslock(mutex());

      return m_userinteractionaMouseHover.erase(pinterface) >= 0;

   }


   void interaction_impl::_task_transparent_mouse_event()
   {

      m_pwindow->_task_transparent_mouse_event();

   }


   void interaction_impl::_001OnCaptureChanged(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      m_puserinteractionMouseCapture.release();
      
   }


   bool interaction_impl::__windows_message_bypass(::windowing::window * pwindow, ::u32 message, wparam wparam, lparam lparam, lresult & lresult)
   {

      return false;

   }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {

      last_install_message_routing(pchannel);

      ::user::primitive_impl::install_message_routing(pchannel);

      m_puserinteraction->install_message_routing(pchannel);

//#ifdef WINDOWS

      if (!m_puserinteraction->m_bMessageWindow)
      {

         MESSAGE_LINK(e_message_capture_changed, pchannel, this, &interaction_impl::_001OnCaptureChanged);

      }

//#endif

      MESSAGE_LINK(e_message_destroy, pchannel, this, &interaction_impl::on_message_destroy);

      prio_install_message_routing(pchannel);

   }




   void interaction_impl::default_message_handler(::message::message * pmessage)
   {

      m_pwindow->default_message_handler(pmessage);

   }


   void interaction_impl::on_message_destroy(::message::message * pmessage)
   {

      if (m_puserinteraction && __type_name(m_puserinteraction).contains("notify_icon"))
      {

         INFORMATION("notify_icon");

      }

      if (m_pgraphics)
      {

         m_pgraphics->destroy_buffer();

         m_pgraphics->destroy();

      }

      __release(m_pgraphics);

      __UNREFERENCED_PARAMETER(pmessage);

      {

         auto psync = mutex();

         _synchronous_lock synchronouslock(mutex());

         m_userinteractionaMouseHover.erase_all();

      }

   }



   void interaction_impl::post_non_client_destroy()
   {

      string strType = __type_name(m_puserinteraction);

//      if (strType.contains("main_frame"))
//      {
//
//         output_debug_string("main_frame");
//
//      }

      auto pwindowthread = m_puserthread;

      ::user::primitive_impl::post_non_client_destroy();

      detach_window();

      m_puserinteraction.release();

      if (::is_set(pwindowthread))
      {

         pwindowthread->m_pimpl.release();

      }

   }


   void interaction_impl::on_final_release()
   {

   }



   void interaction_impl::assert_ok() const
   {

      ::user::primitive_impl::assert_ok();

   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {

      ::user::primitive_impl::dump(dumpcontext);

   }


   void interaction_impl::destroy_impl_only()
   {

      if (!m_bDestroyImplOnly)
      {

         m_bDestroyImplOnly = true;

         m_pprodevian->set_finish();

         if (::is_set(m_puserinteraction))
         {

            INFORMATION(__type_name(m_puserinteraction) << "::destroy_impl_only");

            m_puserinteraction->transfer_handler(m_dispatchermap, this);

         }

         m_puserinteraction->m_pprimitiveimpl.release();

         m_puserinteraction->m_pinteractionimpl.release();

         m_puserinteraction.release();

         auto pwindow = get_window();

         message_queue_post(pwindow, e_message_destroy_window, 0, 0);

         //return true;

      }
      else if(m_bUserImplCreated)
      {

         if (m_puserinteraction)
         {

            INFORMATION(__type_name(m_puserinteraction) << "::destroy_impl_only ( 2)");

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


   void interaction_impl::start_destroying_window()
   {

      if (is_destroying())
      {

         //return true;

         return;

      }

      if (!is_destroying())
      {

         if (m_pprodevian && m_pprodevian->task_active())
         {

            m_pprodevian->set_finish();

         }
         else
         {

            set_destroying();

            m_puserinteraction->post_message(e_message_destroy_window);

         }

         return;

      }

      //bool bResult = 
      ::user::primitive_impl::start_destroying_window();

      //return bResult;

   }


   void interaction_impl::destroy_window()
   {

      auto strType = __type_name(m_puserinteraction);

      if (strType.contains("main_frame"))
      {

         output_debug_string("main_frame user::interaction_impl::destroy_window");

      }

      if(!m_puserinteraction->is_destroying())
      {

         m_puserinteraction->set(e_flag_destroying);

      }
      
      //m_puserinteraction->m_ewindowflag -= e_window_flag_window_created;

      //::destroy_window(get_handle());

      m_pwindow->destroy_window();

   }


   //void interaction_impl::default_window_procedure(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


   void interaction_impl::pre_translate_message(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

   }


   //void interaction_impl::GetWindowText(string & rectangleString)
   //{

   //   __UNREFERENCED_PARAMETER(rectangleString);

   //   throw ::interface_only();

   //}


   //i32 interaction_impl::GetChildByIdText(i32 nID,string & rectangleString) const
   //{

   //   __UNREFERENCED_PARAMETER(nID);

   //   __UNREFERENCED_PARAMETER(rectangleString);

   //   throw ::interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   void interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
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
//   void interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
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


   //void interaction_impl::PrepareForHelp()
   //{

   //   throw ::interface_only();

   //}


   void interaction_impl::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      __UNREFERENCED_PARAMETER(pcommand);

      throw ::interface_only();

   }


   void interaction_impl::_002OnDraw(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

   }


   void interaction_impl::message_handler(::message::message* pmessage)
   {

      bool bKeyMessage = false;

      ::message::key* pkey = nullptr;

      if (m_puserinteraction->pre_message_handler(pkey, bKeyMessage, pmessage))
      {

         return;

      }

      if (pmessage->m_atom == e_message_timer)
      {

         //m_pthread->step_timer();

      }
      else if (pmessage->m_atom == e_message_left_button_down)
      {

         output_debug_string("linux::interaction_impl::e_message_left_button_down\n");

      }
      else if (pmessage->m_atom == e_message_left_button_up)
      {

         output_debug_string("linux::interaction_impl::e_message_left_button_up\n");

      }
      else if (pmessage->m_atom == e_message_mouse_move)
      {

         //g_iMouseMove++;

         //TRACE("linux::interaction_impl::message_handler e_message_mouse_move");
         //printf("g_iMouseMove = %d\n", g_iMouseMove);

      }
      else if (pmessage->m_atom == e_message_paint)
      {

      }
      else if (pmessage->m_atom == e_message_left_button_up)
      {

         TRACE("e_message_left_button_up (0)");

      }

      //      if(::is_set(m_puserinteraction))
      //      {
      //
      //         m_puserinteraction->pre_translate_message(pmessage);
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
      //            ::output_debug_string("interaction_impl::message handler flooded?\n");
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

      if (m_puserinteraction != nullptr)
      {

         if (m_puserinteraction->layout().is_moving())
         {
            //TRACE("moving: skip pre translate message");
         }
         else if (m_puserinteraction->layout().is_sizing())
         {
            //TRACE("sizing: skip pre translate message");
         }
         else
         {

            //m_puserinteraction->pre_translate_message(pmessage);

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
      //         auto psession = get_session();
      //
      //         auto puser = psession->user();
      //
      //         auto pwindowing = puser->windowing();
      //
      //         __pointer(::message::key) pkey = pmessage;
      //
      //         //pwindowing->set(pkey, get_oswindow(), m_pwindow, pkey->m_atom, pkey->m_wparam, pkey->m_lparam);
      //
      ////         if(pmessage->m_atom == e_message_key_down)
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
      ////         else if(pmessage->m_atom == e_message_key_up)
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

      if (pmessage->m_atom == e_message_mouse_leave)
      {

         _000OnMouseLeave(pmessage);

         return;

      }

      if (pmessage->m_atom == e_message_left_button_down ||
         pmessage->m_atom == e_message_left_button_up ||
         pmessage->m_atom == e_message_middle_button_down ||
         pmessage->m_atom == e_message_middle_button_up ||
         pmessage->m_atom == e_message_right_button_down ||
         pmessage->m_atom == e_message_right_button_up ||
         pmessage->m_atom == e_message_left_button_double_click ||
         pmessage->m_atom == e_message_mouse_move ||
         pmessage->m_atom == e_message_mouse_move ||
         pmessage->m_atom == e_message_mouse_wheel)
      {

         if (::is_set(m_puserinteraction) && !m_puserinteraction->m_bUserElementOk)
         {

            return;

         }

         __pointer(::message::mouse) pmouse = pmessage;

         auto psession = get_session();

         if (pmouse)
         {

            if (psession != nullptr)
            {

               psession->on_ui_mouse_message(pmouse);

               psession->m_pointCursor = pmouse->m_point;

            }

            //         if(m_puserinteraction != nullptr && m_puserinteraction->get_session()  != nullptr && m_puserinteraction->get_session() != get_session())
            //         {
            //
            //            auto psystem = m_psystem;
            //
            //            auto psession = psystem->node();
            //
            //            psession->m_pointCursor = pmouse->m_point;
            //
            //         }

            if (m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
            {
               pmouse->m_bTranslated = true;
               ::rectangle_i32 rectWindow;
               //            if(m_bScreenRelativeMouseMessagePosition)
               //            {
               //
               //               INFO("Screen Relative Mouse Message Position");
               //
               //               ::rectangle_i32 rectWindow32;
               //
               //               ::get_window_rect((oswindow) get_handle(), &rectWindow32);
               //
               //               ::copy(rectWindow, rectWindow32);
               //
               //            }
               //            else
               {
                  m_puserinteraction->get_window_rect(rectWindow);
               }

               auto puser = psession->user();

               auto pwindowing = puser->windowing();

               auto pdisplay = pwindowing->display();

               if (pdisplay->get_monitor_count() > 0)
               {

                  ::rectangle_i32 rcMonitor;

                  pdisplay->get_monitor_rectangle(0, &rcMonitor);

                  if (rectWindow.left >= rcMonitor.left)
                  {

                     pmouse->m_point.x += (::i32)rectWindow.left;

                  }

                  if (rectWindow.top >= rcMonitor.top)
                  {

                     pmouse->m_point.y += (::i32)rectWindow.top;

                  }

               }
               else
               {

                  if (rectWindow.left >= 0)
                  {

                     pmouse->m_point.x += (::i32)rectWindow.left;

                  }

                  if (rectWindow.top >= 0)
                  {

                     pmouse->m_point.y += (::i32)rectWindow.top;

                  }

               }

            }

         }

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->set(pmouse, get_oswindow(), m_pwindow, pmouse->m_atom, pmouse->m_wparam, pmouse->m_lparam);

         if (pmessage->m_atom == e_message_mouse_move)
         {

            // We are at the message handler routine.
            // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
            // So the routine starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.

            m_puserinteraction->m_pinteractionimpl->_on_mouse_move_step(pmouse->m_point);

         }

         //_008OnMouse(pmouse);

         ::user::interaction* puserinteractionMouse = nullptr;

         if (m_puserinteractionMouseCapture)
         {

            //            if(g_puserinteractionMouseCapture123 == nullptr)
            //            {
            //
            //               g_puserinteractionMouseCapture123 = m_puserinteractionCapture;
            //
            //            }
            //            else if(g_puserinteractionMouseCapture123 != m_puserinteractionCapture)
            //            {
            //
            //               output_debug_string("different capture (1)");
            //
            //            }

            puserinteractionMouse = m_puserinteractionMouseCapture;

         }

         //         if(g_puserinteractionMouseCapture123 != nullptr)
         //         {
         //
         //            if(g_puserinteractionMouseCapture123 != puserinteractionMouse)
         //            {
         //
         //               output_debug_string("different capture (2)");
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

         if (pmouse->m_atom == e_message_left_button_down)
         {


            ::output_debug_string("left_button_down (A)");

         }

         if (!puserinteractionMouse)
         {

            puserinteractionMouse = m_puserinteraction->child_from_point(pmouse->m_point);

         }

         if (pmouse->m_atom == e_message_left_button_down)
         {


            ::output_debug_string("left_button_down");

         }
         else if (pmouse->m_atom == e_message_left_button_up)
         {


            ::output_debug_string("left_button_up");

         }

         //         string strUserInteractionType(::is_null(puserinteractionMouse) ? "(null)" : __type_name(puserinteractionMouse));
         //
         //         if(pmouse->m_atom == e_message_mouse_move)
         //         {
         //
         //            static int s_iMotionNotify = 0;
         //
         //            s_iMotionNotify++;
         //
         //            if (strUserInteractionType.contains_ci("button"))
         //            {
         //
         //               output_debug_string("mouse_move::userinteraction=button");
         //
         //            }
         //            else
         //            {
         //
         //
         //               puserinteractionMouse = m_puserinteraction->child_from_point(pmouse->m_point);
         //
         //
         //
         //            }
         //
         //         }

         if (puserinteractionMouse)
         {

            do
            {

               puserinteractionMouse->route_message(pmouse);

               if (pmouse->m_bRet)
               {

                  break;

               }

               puserinteractionMouse = puserinteractionMouse->get_parent();

            } while (puserinteractionMouse != nullptr);

         }

         return;

      }
      /*      else if(pmessage->m_atom == e_message_key_down ||
                    pmessage->m_atom == e_message_key_up ||
                    pmessage->m_atom == e_message_char)*/
      else if (bKeyMessage)
      {

         if (::is_set(pkey))
         {

            __pointer(::user::interaction) puiKeyboardFocus = m_puserinteractionKeyboardFocus;

            if (puiKeyboardFocus)
            {

               puiKeyboardFocus->route_message(pkey);

            }
            else
            {

               m_puserinteraction->route_message(pkey);

            }

         }

         if (pmessage->m_bRet)
         {

            return;

         }

         default_window_procedure(pmessage);

         return;

      }

      if (pmessage->m_atom == e_message_subject)
      {

         if (m_puserinteraction != nullptr)
         {

            m_puserinteraction->handle((::topic*)pmessage->m_lparam.m_lparam, nullptr);

         }
         //         else
         //         {
         //
         //            on_control_event((::user::control_event *) pmessage->m_lparam.m_lparam);
         //
         //         }

         return;

      }

      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->route_message(pmessage);

      }
      else
      {

         route_message(pmessage);

      }

      if (pmessage->m_bRet)
      {

         return;

      }

      default_window_procedure(pmessage);

   }


   void interaction_impl::_message_handler(::message::message * pmessage)
   {

      if (m_puserinteraction)
      {

         m_bDestroyImplOnly ? route_message(pmessage) : m_puserinteraction.m_p->route_message(pmessage);

      }

   }


   void interaction_impl::default_window_procedure(::message::message * pmessage)
   {

   }


   bool interaction_impl::on_mouse_message(::message::mouse * pmouse)
   {

      if (pmouse->m_atom == e_message_left_button_down)
      {

         TRACE("e_message_left_button_down");

         string strType = __type_name(m_puserinteraction);

         if (strType.contains_ci("list_box"))
         {

            ::output_debug_string("list_box e_message_left_button_down");

         }

      }
      else if (pmouse->m_atom == e_message_left_button_up)
      {

         TRACE("e_message_left_button_up");

      }
      else if (pmouse->m_atom == e_message_non_client_left_button_up)
      {

         TRACE("e_message_non_client_left_button_up");

      }
      else if (pmouse->m_atom == e_message_non_client_left_button_down)
      {

         TRACE("e_message_non_client_left_button_down");

         string strType;

         if (strType.contains_ci("list_box"))
         {

            ::output_debug_string("list_box e_message_non_client_left_button_down");

         }

      }

      auto psession = get_session();

      if (psession)
      {

         psession->on_ui_mouse_message(pmouse);

      }

      if (pmouse->m_atom == e_message_mouse_move)
      {
         // We are at the message handler procedure.
         // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
         // So the procedure starts by setting to the default cursor,
         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
         // handler has set it to another one.
         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pcursor = pwindowing->get_cursor(e_cursor_default);

         pmouse->m_pcursor = pcursor;

         //FORMATTED_INFORMATION("windows::e_message_mouse_move(%d,%d)", pmouse->m_point.x, pmouse->m_point.y);

         string strType;

         if (m_puserinteraction)
         {

            strType = __type_name(m_puserinteraction);

            if (strType.contains_ci("list_box"))
            {

               //::output_debug_string("list_box e_message_mouse_move");

            }

         }

      }
      else if (pmouse->m_atom == e_message_non_client_mouse_move)
      {
         // We are at the message handler procedure.
         // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
         // So the procedure starts by setting to the default cursor,
         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
         // handler has set it to another one.
         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pcursor = pwindowing->get_cursor(e_cursor_default);

         pmouse->m_pcursor = pcursor;

      }

      _on_mouse_move_step(pmouse->m_point);

      auto puserinteractionMouseCapture = m_puserinteractionMouseCapture;

      if (::is_set(puserinteractionMouseCapture))
      {

         puserinteractionMouseCapture->route_message(pmouse);

         return true;

      }

      auto pchild = m_puserinteraction->child_from_point(pmouse->m_point);

      if (pchild)
      {

         string strType = __type_name(pchild);

         if (strType.contains_ci("button"))
         {

            output_debug_string("mouse move on button");

         }
         else if (strType.contains_ci("tab"))
         {

            output_debug_string("mouse move on tab");

         }

         auto puserinteraction = pchild;

         ::user::interaction_array interactionaHandled;

         while (::is_set(puserinteraction))
         {

            puserinteraction->route_message(pmouse);

            interactionaHandled.add_interaction(puserinteraction);

            if (pmouse->m_bRet)
            {

               break;

            }

            puserinteraction = puserinteraction->get_parent();

            if (is_set(puserinteraction))
            {

               auto pchild = puserinteraction->child_from_point(pmouse->m_point, interactionaHandled);

               if (::is_set(pchild))
               {

                  pchild->route_message(pmouse);

                  if (pmouse->m_bRet)
                  {

                     break;

                  }

               }

            }

         }

      }
      else
      {

         m_puserinteraction->route_message(pmouse);

      }

      return true;

   }


   bool interaction_impl::IsTopParentActive()
   {

      return m_puserinteraction->window()->is_active_window();

      //return false;

   }


   void interaction_impl::ActivateTopParent()
   {

      throw ::interface_only();

   }


   //i32 interaction_impl::message_box(const ::string & pszText, const ::string & pszCaption,::u32 nType)

   //{
   //   __UNREFERENCED_PARAMETER(pszText);

   //   __UNREFERENCED_PARAMETER(pszCaption);

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

   /*   CScrollBar* interaction_impl::GetScrollBarCtrl(i32) const
   {
   throw ::interface_only();
   }*/

   //i32 interaction_impl::SetScrollPos(i32 nBar,i32 nPos,bool bRedraw)
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(nPos);
   //   __UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();

   //   return 0;
   //}

   //i32 interaction_impl::GetScrollPos(i32 nBar) const
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   throw ::interface_only();

   //   return 0;
   //}

   //void interaction_impl::SetScrollRange(i32 nBar,i32 nMinPos,i32 nMaxPos,bool bRedraw)
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(nMinPos);
   //   __UNREFERENCED_PARAMETER(nMaxPos);
   //   __UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();


   //}


   //void interaction_impl::GetScrollRange(i32 nBar,LPINT pMinPos,LPINT pMaxPos) const

   //{

   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(pMinPos);
   //   __UNREFERENCED_PARAMETER(pMaxPos);

   //   throw ::interface_only();

   //}


   //// Turn on/off non-control scrollbars
   ////   for WS_?SCROLL scrollbars - show/hide them
   ////   for control scrollbar - enable/disable them
   //void interaction_impl::EnableScrollBarCtrl(i32 nBar,bool bEnable)
   //{
   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(bEnable);
   //   throw ::interface_only();
   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   void interaction_impl::SetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,bool bRedraw)
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
//   void interaction_impl::GetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,::u32 nMask)
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


   //i32 interaction_impl::GetScrollLimit(i32 nBar)
   //{
   //   
   //   __UNREFERENCED_PARAMETER(nBar);
   //   
   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::ScrollWindow(i32 xAmount,i32 yAmount, const RECTANGLE_I32 * pcrect, const RECTANGLE_I32 * pcrectClip)
   //{

   //   __UNREFERENCED_PARAMETER(xAmount);
   //   __UNREFERENCED_PARAMETER(yAmount);
   //   __UNREFERENCED_PARAMETER(pcrect);
   //   __UNREFERENCED_PARAMETER(pcrectClip);

   //   throw ::interface_only();

   //}


   //void interaction_impl::CalcWindowRect(RECTANGLE_I32 * pClientRect,::u32 nAdjustType)
   //{

   //   __UNREFERENCED_PARAMETER(pClientRect);
   //   __UNREFERENCED_PARAMETER(nAdjustType);

   //   throw ::interface_only();

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(::u32 nID,lparam lParam)
   {

      __UNREFERENCED_PARAMETER(nID);
      __UNREFERENCED_PARAMETER(lParam);

      throw ::interface_only();

      return false;

   }


   bool interaction_impl::OnChildNotify(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

      return false;

   }


   bool interaction_impl::ReflectChildNotify(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

      return false;

   }


//   void interaction_impl::OnParentNotify(const ::atom & atom,lparam lParam)
//   {
//      __UNREFERENCED_PARAMETER(message);
//      __UNREFERENCED_PARAMETER(lParam);
//      throw ::interface_only();
//   }
//
//   void interaction_impl::OnSetFocus(::user::interaction_impl *)
//   {
//      throw ::interface_only();
//   }
//
//   lresult interaction_impl::OnActivateTopLevel(wparam wParam,lparam)
//   {
//      __UNREFERENCED_PARAMETER(wParam);
//      throw ::interface_only();
//   }
//
//   void interaction_impl::OnSysColorChange()
//   {
//      throw ::interface_only();
//   }
//
//   void interaction_impl::OnSettingChange(::u32 uFlags, const ::string & pszSection)

//   {
//      __UNREFERENCED_PARAMETER(uFlags);
//      __UNREFERENCED_PARAMETER(pszSection);

//      throw ::interface_only();
//   }
//
//#ifdef WINDOWS
//   void interaction_impl::OnDevModeChange(__in char * pDeviceName)

//   {
//      __UNREFERENCED_PARAMETER(pDeviceName);

//      throw ::interface_only();
//   }
//
//#ifdef WINDOWS_DESKTOP
//   void interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
//   {
//      throw ::interface_only();
//   }
//#endif
//#endif
//
//   lresult interaction_impl::OnDisplayChange(wparam,lparam)
//   {
//      //   throw ::interface_only();
//
//      return 0;
//
//   }
//
//   lresult interaction_impl::OnDragList(wparam,lparam lParam)
//   {
//      __UNREFERENCED_PARAMETER(lParam);
//      throw ::interface_only();
//   }

   /*   void interaction_impl::OnHScroll(::u32, ::u32, CScrollBar* pScrollBar)
   {
   __UNREFERENCED_PARAMETER(pScrollBar);
   throw ::interface_only();
   }

   void interaction_impl::OnVScroll(::u32, ::u32, CScrollBar* pScrollBar)
   {
   __UNREFERENCED_PARAMETER(pScrollBar);
   throw ::interface_only();
   }
   */

   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image * pimage)
   {
      __UNREFERENCED_PARAMETER(pimage);
      throw ::interface_only();
   }

   void interaction_impl::_001DeferPaintLayeredWindowBackground(::image * pimage)
   {
      __UNREFERENCED_PARAMETER(pimage);
      throw ::interface_only();
   }

   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      throw ::interface_only();
   }

   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      throw ::interface_only();
   }

   //void interaction_impl::OnEnterIdle(::u32 /*nWhy*/,::user::interaction_impl * /*pWho*/)
   //{
   //   throw ::interface_only();
   //}

   //void * interaction_impl::OnCtlColor(::draw2d::graphics *,::user::interaction_impl * pwindow,::u32)
   //{
   //   __UNREFERENCED_PARAMETER(pwindow);
   //   throw ::interface_only();
   //}


   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support

   void interaction_impl::update_data(bool bSaveAndValidate)
   {

      __UNREFERENCED_PARAMETER(bSaveAndValidate);

      throw ::interface_only();

      //return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child interaction_impl)

   void interaction_impl::CenterWindow(::user::interaction * pAlternateOwner)
   {

      __UNREFERENCED_PARAMETER(pAlternateOwner);

      throw ::interface_only();

   }


   //void interaction_impl::CheckAutoCenter()
   //{
   //   throw ::interface_only();

   //   return false;

   //}

//   /////////////////////////////////////////////////////////////////////////////
//   // Dialog initialization support
//
//   void interaction_impl::ExecuteDlgInit(const ::string & pszResourceName)
//
//   {
//      __UNREFERENCED_PARAMETER(pszResourceName);
//
//      throw ::interface_only();
//
//      return false;
//
//   }

//   void interaction_impl::ExecuteDlgInit(LPVOID pResource)
//
//   {
//      __UNREFERENCED_PARAMETER(pResource);
//
//      throw ::interface_only();
//
//      return false;
//
//   }

   void interaction_impl::UpdateDialogControls(channel * pTarget,bool bDisableIfNoHndler)
   {
      __UNREFERENCED_PARAMETER(pTarget);
      __UNREFERENCED_PARAMETER(bDisableIfNoHndler);

      throw ::interface_only();

   }



   //void interaction_impl::subclass_window(::windowing::window * pwindow)
   //{
   //   __UNREFERENCED_PARAMETER(oswindow);
   //   throw ::interface_only();

   //   return false;

   //}

   //void interaction_impl::SubclassDlgItem(::u32 nID,::user::interaction_impl * pParent)
   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pParent);
   //   throw ::interface_only();

   //   return false;

   //}

   //oswindow interaction_impl::unsubclass_window()
   //{
   //   throw ::interface_only();
   //   return nullptr;
   //}

   //void interaction_impl::IsChild(::user::interaction * pinteraction) const
   //{
   //   __UNREFERENCED_PARAMETER(pinteraction);
   //   throw ::interface_only();

   //   return false;

   //}


   bool interaction_impl::_is_window() const
   {

      throw ::interface_only();

      return false;

   }


   //atom interaction_impl::SetDlgCtrlId(atom atom)
   //{

   //   __UNREFERENCED_PARAMETER(atom);

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom interaction_impl::GetDlgCtrlId() const
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   // void interaction_impl::SetWindowDisplayChanged()
   // {

   //    if (m_puserinteraction->is_this_visible() && m_puserinteraction->window_state3().m_edisplay3 != ::e_display_iconic)
   //    {

   //       if (m_puserinteraction->get_parent() == nullptr)
   //       {

   //          m_puserinteraction->check_transparent_mouse_events();

   //       }

   //    }
   //    else
   //    {

   //       //stop_prodevian();
   //       //child_post_quit("prodevian");

   //    }

   // }


   //void interaction_impl::layout().is_iconic()
   //{

   //   //throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::IsZoomed()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::interaction * interaction_impl::get_parent() const
   //{

   //   return nullptr;

   //}


//   ::i32 interaction_impl::get_window_long(i32 nIndex) const
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return (::i32) ::GetWindowLongPtr(get_handle(), nIndex);
//
//#else
//
//      return (::i32) get_window_long_ptr(nIndex);
//
//#endif
//
//   }


//   ::i32 interaction_impl::set_window_long(i32 nIndex,::i32 lValue)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return (::i32) ::SetWindowLongPtr(get_handle(), nIndex, lValue);
//
//#else
//
//      return (::i32) set_window_long_ptr(nIndex, lValue);
//
//#endif
//
//   }


//   iptr interaction_impl::get_window_long_ptr(i32 nIndex) const
//   {
//
//      return m_pwindow->get_window_long_ptr(nIndex);
//
//   }
//
//
//   iptr interaction_impl::set_window_long_ptr(i32 nIndex, iptr lValue)
//   {
//
//      return m_pwindow->set_window_long_ptr(nIndex, lValue);
//
//   }


   //void interaction_impl::ReleaseCapture()
   //{

   //   auto psession = get_session();

   //   auto pwindowing = psession->windowing();

   //   pwindowing->release_capture();

   //   psession->m_puiCapture = nullptr;

   //   return true;

   //}


   //::user::interaction * interaction_impl::get_capture()
   //{

   //   if (!m_pwindow->has_capture())
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteractionCapture;

   //}


   //void interaction_impl::SetCapture(::user::interaction * pinteraction)
   //{

   //   if (pinteraction == nullptr)
   //   {

   //      pinteraction = m_puserinteraction;

   //   }

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   oswindow w = ::set_capture(get_handle());

   //   output_debug_string("\nSet Capture: oswindow=0x" + ::hex::lower_from((iptr) w));

   //   auto psession = get_session();

   //   psession->m_puiCapture = pinteraction;

   //   return true;

   //}


   //// interaction_impl
   ///* interaction_impl::operator oswindow() const
   //{ return this == nullptr ? nullptr : get_handle(); }*/
   //void interaction_impl::operator==(const interaction_impl& wnd) const
   //{
   //   __UNREFERENCED_PARAMETER(wnd);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::operator!=(const interaction_impl& wnd) const
   //{
   //   __UNREFERENCED_PARAMETER(wnd);
   //   throw ::interface_only();
   //   return false;
   //}


   //u32 interaction_impl::GetStyle() const
   //{

   //   return ::user::primitive_impl::GetStyle();

   //}


   //u32 interaction_impl::GetExStyle() const
   //{

   //   return ::user::primitive_impl::GetExStyle();

   //}


   //void interaction_impl::ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   //{

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   ::u32 dw = get_window_long(GWL_STYLE);

   //   dw &= ~dwRemove;

   //   dw |= dwAdd;

   //   set_window_long(GWL_STYLE, dw);

   //   return false;

   //}


   //void interaction_impl::ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   ::u32 dw = get_window_long(GWL_EXSTYLE);

   //   dw &= ~dwRemove;

   //   dw |= dwAdd;

   //   set_window_long(GWL_EXSTYLE, dw);

   //   return false;

   //}


   ::user::primitive * interaction_impl::set_owner(::user::primitive * pprimitiveOwner)
   {

      __UNREFERENCED_PARAMETER(pprimitiveOwner);

      //throw ::interface_only();

      return nullptr;

   }


   lresult interaction_impl::send_message(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      auto pmessage = m_puserinteraction->get_message(atom, wparam, lparam);

      if(m_puserinteraction->layout().is_moving())
      {

         TRACE("moving: skip walk pre translate tree");

      }
      else if(m_puserinteraction->layout().is_sizing())
      {

         TRACE("sizing: skip walk pre translate tree");

      }
      else
      {

         m_puserinteraction->walk_pre_translate_tree(pmessage);

         if(pmessage->m_bRet)
         {

            return pmessage->m_lresult;

         }

      }

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


//#ifdef LINUX
//
//
//   lresult interaction_impl::send_x11_event(void * pevent)
//   {
//
//      __UNREFERENCED_PARAMETER(pevent);
//
//      throw ::interface_only();
//
//      return 0;
//
//   }
//
//
//#endif


   void interaction_impl::post_message(const ::atom & atom,wparam wParam,lparam lParam)
   {

      if(!m_puserinteraction)
      {

         //return false;

         throw ::exception(error_wrong_state);

      }

      if(!m_puserinteraction->m_pthreadUserInteraction)
      {

         throw ::exception(error_wrong_state);

      }

      auto pwindow = m_pwindow;

      if(!pwindow)
      {

         throw ::exception(error_wrong_state);

      }

      auto oswindow = pwindow->get_oswindow();

      if(!oswindow)
      {

         throw ::exception(error_wrong_state);

      }
      
      auto puserinteraction = m_puserinteraction;

      auto pthread = puserinteraction->m_pthreadUserInteraction;
      
      if(atom == e_message_redraw)
      {
         
         if(m_pprodevian)
         {
            
            puserinteraction->prodevian_redraw(wParam & 1);
            
            return;
            
         }
         
      }

      MESSAGE message = {};

      message.oswindow = oswindow;

      message.m_atom = atom;

      message.wParam = wParam;

      message.lParam = lParam;

      auto pmessagequeue = pthread->get_message_queue();
      
      if(::is_null(pmessagequeue))
      {
         
         throw ::exception(error_wrong_state);
         
      }

      //auto estatus = 
      pmessagequeue->post_message(message);

      //return estatus;

   }


   //void interaction_impl::DragDetect(const ::point_i32 & point) const
   //{
   //   __UNREFERENCED_PARAMETER(point);
   //   throw ::interface_only();
   //   return false;
   //}


   void interaction_impl::set_window_text(const ::string & pszString)

   {

      __UNREFERENCED_PARAMETER(pszString);


      throw ::interface_only();

   }

   
   //strsize interaction_impl::GetWindowText(char * pszString,i32 nMaxCount)
   //{

   //   __UNREFERENCED_PARAMETER(pszString);
   //   __UNREFERENCED_PARAMETER(nMaxCount);
   //   throw ::interface_only();

   //   return 0;
   //}


   //strsize interaction_impl::GetWindowTextLength()
   //{

   //   throw ::interface_only();
   //   return 0;

   //}


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      __UNREFERENCED_PARAMETER(bAccept);

      throw ::interface_only();

   }


   bool interaction_impl::window_is_iconic()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->const_layout().sketch().display() == ::e_display_iconic;

   }


   bool interaction_impl::window_is_zoomed()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->const_layout().sketch().display() == ::e_display_zoomed;

   }


   ::u32 interaction_impl::ArrangeIconicWindows()
   {

      throw ::interface_only();

      return 0;

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * puserinteractionTo,POINT_I32 * pPoint,::u32 nCount)
   {

      __UNREFERENCED_PARAMETER(puserinteractionTo);
      __UNREFERENCED_PARAMETER(pPoint);
      __UNREFERENCED_PARAMETER(nCount);

      throw ::interface_only();

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * puserinteractionTo,RECTANGLE_I32 * prectangle)
   {
      __UNREFERENCED_PARAMETER(puserinteractionTo);
      __UNREFERENCED_PARAMETER(prectangle);

      throw ::interface_only();
   }

   void interaction_impl::UpdateWindow()
   {
      throw ::interface_only();
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {
      __UNREFERENCED_PARAMETER(bRedraw);
      throw ::interface_only();
   }

   //void interaction_impl::GetUpdateRect(RECTANGLE_I32 * prectangle,bool bErase)

   //{
   //   __UNREFERENCED_PARAMETER(prectangle);

   //   __UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();

   //   return false;
   //}

   //i32 interaction_impl::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{
   //   __UNREFERENCED_PARAMETER(pRgn);
   //   __UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();

   //   return 0;
   //}


   void interaction_impl::Invalidate(bool bErase)
   {

      __UNREFERENCED_PARAMETER(bErase);

      throw ::interface_only();

   }


   void interaction_impl::InvalidateRect(const ::rectangle_i32 & rectangle,bool bErase)
   {

      __UNREFERENCED_PARAMETER(rectangle);
      __UNREFERENCED_PARAMETER(bErase);

      throw ::interface_only();

   }


   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {
      __UNREFERENCED_PARAMETER(pRgn);
      __UNREFERENCED_PARAMETER(bErase);
      throw ::interface_only();
   }


   void interaction_impl::ValidateRect(const ::rectangle_i32 & rectangle)
   {

      __UNREFERENCED_PARAMETER(rectangle);

      throw ::interface_only();

   }


   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {

      __UNREFERENCED_PARAMETER(pRgn);

      throw ::interface_only();

   }


   //void interaction_impl::_is_window_visible()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {
      __UNREFERENCED_PARAMETER(bShow);
      throw ::interface_only();
   }


   /*::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip,u32 flags)
   {
      __UNREFERENCED_PARAMETER(prgnClip);
      __UNREFERENCED_PARAMETER(flags);
      throw ::interface_only();


      return nullptr;
   }*/

   void interaction_impl::LockWindowUpdate()
   {

      throw ::interface_only();

      //return false;

   }


   void interaction_impl::UnlockWindowUpdate()
   {

      throw ::interface_only();

   }


   //void interaction_impl::set_need_redraw(bool bAscendants)
   //{

   //}


   void interaction_impl::post_redraw(bool bAscendants)
   {

      if (!m_puserinteraction)
      {

         return;

      }

      m_puserinteraction->post_message(::e_message_redraw, 1);

   }


   void interaction_impl::RedrawWindow(const ::rectangle_i32 & rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      m_puserinteraction->set_need_redraw();

      //return true;

   }


   //void interaction_impl::EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags)
   //{

   //   __UNREFERENCED_PARAMETER(nSBFlags);

   //   __UNREFERENCED_PARAMETER(nArrowFlags);

   //   throw ::interface_only();

   //   return false;

   //}


   //::point_i32 interaction_impl::get_cursor_position() const
   //{

   //   auto psession = get_session();

   //   if (!psession)
   //   {

   //      return ::point_i32();

   //   }

   //   return psession->get_cursor_position();

   //}


   void interaction_impl::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      if (::is_null(m_pwindow))
      {

         //return ::error_failed;

         return;

      }

      //auto estatus = 
      
      m_pwindow->set_mouse_cursor(pcursor);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   ::windowing::window * interaction_impl::get_window() const
   {

      return m_pwindow;

   }


   //void interaction_impl::set_mouse_cursor(enum_cursor ecursor)
   //{

   //   auto psession = get_session();

   //   auto puser = psession->user();

   //   auto pwindowing = puser->windowing();

   //   auto pcursor = pwindowing->get_cursor(ecursor);

   //   auto pwindow = get_window();

   //   auto estatus = pwindow->set_cursor(pcursor);

   //   return estatus;

   //}


   //void interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics,const rectangle_i32 & prc,::u32 uFlags)
   //{

   //   __UNREFERENCED_PARAMETER(pgraphics);
   //   __UNREFERENCED_PARAMETER(prc);
   //   __UNREFERENCED_PARAMETER(uFlags);

   //   throw ::interface_only();

   //   //return false;

   //}


   //void interaction_impl::is_window_enabled() const
   //{

   //   return m_puserinteraction->m_ewindowflag & e_window_flag_enable;

   //}


   void interaction_impl::enable_window(bool bEnable)
   {

      m_puserinteraction->m_ewindowflag.set(e_window_flag_enable, bEnable);

      //return true;

   }


   //::user::interaction * interaction_impl::GetActiveWindow()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_impl::SetActiveWindow()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void interaction_impl::SetFocus()
   //{

   //   return false;

   //}


   //void interaction_impl::CheckDlgButton(i32 nIDButton,::u32 nCheck)
   //{
   //   __UNREFERENCED_PARAMETER(nIDButton);
   //   __UNREFERENCED_PARAMETER(nCheck);
   //   throw ::interface_only();
   //}

   //void interaction_impl::CheckRadioButton(i32 nIDFirstButton,i32 nIDLastButton,i32 nIDCheckButton)
   //{
   //   __UNREFERENCED_PARAMETER(nIDFirstButton);
   //   __UNREFERENCED_PARAMETER(nIDLastButton);
   //   __UNREFERENCED_PARAMETER(nIDCheckButton);
   //   throw ::interface_only();
   //}

   //i32 interaction_impl::DlgDirList(char * pPathSpec,i32 nIDListBox,i32 nIDStaticPath,::u32 nFileType)

   //{
   //   __UNREFERENCED_PARAMETER(pPathSpec);

   //   __UNREFERENCED_PARAMETER(nIDListBox);
   //   __UNREFERENCED_PARAMETER(nIDStaticPath);
   //   __UNREFERENCED_PARAMETER(nFileType);
   //   throw ::interface_only();
   //   return 0;
   //}

   //i32 interaction_impl::DlgDirListComboBox(char * pPathSpec,i32 nIDComboBox,i32 nIDStaticPath,::u32 nFileType)

   //{
   //   __UNREFERENCED_PARAMETER(pPathSpec);

   //   __UNREFERENCED_PARAMETER(nIDComboBox);
   //   __UNREFERENCED_PARAMETER(nIDStaticPath);
   //   __UNREFERENCED_PARAMETER(nFileType);
   //   throw ::interface_only();

   //   return 0;
   //}

   //void interaction_impl::DlgDirSelect(char * pString,i32 nSize,i32 nIDListBox)

   //{
   //   __UNREFERENCED_PARAMETER(pString);

   //   __UNREFERENCED_PARAMETER(nSize);
   //   __UNREFERENCED_PARAMETER(nIDListBox);
   //   throw ::interface_only();

   //   return false;
   //}

   //void interaction_impl::DlgDirSelectComboBox(char * pString,i32 nSize,i32 nIDComboBox)

   //{
   //   __UNREFERENCED_PARAMETER(pString);

   //   __UNREFERENCED_PARAMETER(nSize);
   //   __UNREFERENCED_PARAMETER(nIDComboBox);
   //   throw ::interface_only();

   //   return false;
   //}

   //::u32 interaction_impl::GetChildByIdInt(i32 nID,bool* pTrans,bool bSigned) const

   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pTrans);

   //   __UNREFERENCED_PARAMETER(bSigned);
   //   throw ::interface_only();

   //   return 0;
   //}

   //i32 interaction_impl::GetChildByIdText(i32 nID,char * pStr,i32 nMaxCount) const

   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pStr);

   //   __UNREFERENCED_PARAMETER(nMaxCount);
   //   throw ::interface_only();

   //   return 0;
   //}


   //::user::interaction_impl * interaction_impl::GetNextDlgGroupItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   //{

   //   __UNREFERENCED_PARAMETER(pWndCtl);
   //   __UNREFERENCED_PARAMETER(bPrevious);

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction_impl * interaction_impl::GetNextDlgTabItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   //{

   //   __UNREFERENCED_PARAMETER(pWndCtl);
   //   __UNREFERENCED_PARAMETER(bPrevious);

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::u32 interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   //{
   //   __UNREFERENCED_PARAMETER(nIDButton);
   //   throw ::interface_only();

   //   return 0;
   //}


   //lparam interaction_impl::SendDlgItemMessage(i32 nID, ::u32 message, wparam wParam,lparam lParam)
   //{

   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(message);
   //   __UNREFERENCED_PARAMETER(wParam);
   //   __UNREFERENCED_PARAMETER(lParam);
   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::SetDlgItemInt(i32 nID,::u32 nValue,bool bSigned)
   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(nValue);
   //   __UNREFERENCED_PARAMETER(bSigned);
   //   throw ::interface_only();
   //}

   //void interaction_impl::SetDlgItemText(i32 nID, const ::string & pszString)

   //{
   //   __UNREFERENCED_PARAMETER(nID);
   //   __UNREFERENCED_PARAMETER(pszString);

   //   throw ::interface_only();
   //}


   //i32 interaction_impl::ScrollWindowEx(i32 dx,i32 dy,
   //                                     const RECTANGLE_I32 * prectScroll,
   //                                       const RECTANGLE_I32 * prectClip,
   //                                     ::draw2d::region* prgnUpdate,RECTANGLE_I32 * pRectUpdate,::u32 flags)
   //{

   //   __UNREFERENCED_PARAMETER(dx);
   //   __UNREFERENCED_PARAMETER(dy);
   //   __UNREFERENCED_PARAMETER(prectScroll);
   //   __UNREFERENCED_PARAMETER(prectClip);
   //   __UNREFERENCED_PARAMETER(prgnUpdate);
   //   __UNREFERENCED_PARAMETER(pRectUpdate);
   //   __UNREFERENCED_PARAMETER(flags);

   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::ShowScrollBar(::u32 nBar,bool bShow)
   //{

   //   __UNREFERENCED_PARAMETER(nBar);
   //   __UNREFERENCED_PARAMETER(bShow);

   //   throw ::interface_only();

   //}


   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point_i32 & point)
   {
      
      __UNREFERENCED_PARAMETER(point);

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags)
   {

      __UNREFERENCED_PARAMETER(point);

      __UNREFERENCED_PARAMETER(nFlags);

      throw ::interface_only();

      return nullptr;

   }


//   ::user::interaction * interaction_impl::get_next_window(::u32 nFlag)
//   {
//
//      __UNREFERENCED_PARAMETER(nFlag);
//
//      throw ::interface_only();
//
//      return nullptr;
//
//   }


   ::user::interaction * interaction_impl::GetTopWindow()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::GetLastActivePopup()
   {

      throw ::interface_only();

      return nullptr;

   }


   //void interaction_impl::FlashWindow(bool bInvert)
   //{

   //   __UNREFERENCED_PARAMETER(bInvert);

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::ChangeClipboardChain(::windowing::window * pwindow_Next)
   //{

   //   __UNREFERENCED_PARAMETER(oswindow_Next);

   //   throw ::interface_only();

   //   return false;

   //}


   //oswindow interaction_impl::SetClipboardImpacter()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void interaction_impl::OpenClipboard()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void interaction_impl::user_interaction_on_hide()
   {

      decltype(m_userinteractionaMouseHover) userinteractiona;

      {

         auto psync = mutex();

         _synchronous_lock synchronouslock(mutex());

         userinteractiona = m_userinteractionaMouseHover;

         m_userinteractionaMouseHover.erase_all();

      }

      for(auto & pinteraction : userinteractiona)
      {

         pinteraction->post_message(e_message_mouse_leave);

      }

   }


   void interaction_impl::HideCaret()
   {

      throw ::interface_only();

   }


   void interaction_impl::ShowCaret()
   {

      throw ::interface_only();

   }


   //void interaction_impl::SetForegroundWindow()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::SendNotifyMessage(::u32 message,wparam wParam,lparam lParam)
   //{

   //   __UNREFERENCED_PARAMETER(message);
   //   __UNREFERENCED_PARAMETER(wParam);
   //   __UNREFERENCED_PARAMETER(lParam);

   //   throw ::interface_only();

   //   return false;

   //}


   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const
   {

      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(dwFlags);

      throw ::interface_only();

   }


   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const
   {

      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(dwFlags);

      throw ::interface_only();

   }


   //void interaction_impl::SetWindowContextHelpId(u32 dwContextHelpId)
   //{

   //   __UNREFERENCED_PARAMETER(dwContextHelpId);

   //   throw ::interface_only();

   //   return false;

   //}


   //u32 interaction_impl::GetWindowContextHelpId() const
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   void interaction_impl::on_message_create(::message::message * pmessage)
   {

      auto psession = get_session();

      auto puser = psession->user();

      m_pwindowing = puser->windowing();

      if (m_puserinteraction->m_ewindowflag & e_window_flag_graphical)
      {

         if (::is_set(m_pprodevian))
         {

            m_pprodevian->set_prodevian_fps(get_prodevian_fps());

            m_pprodevian->set_nominal_fps(get_nominal_fps());

            pmessage->previous();

            m_pprodevian->prodevian_reset(m_puserinteraction);

         }

         if (m_puserinteraction)
         {

            if (!m_puserinteraction->m_bMessageWindow)
            {

               m_pcsDisplay = new(critical_section);

               output_debug_string("interaction_impl m_pgraphics alloc");

               update_graphics_resources();

               output_debug_string("interaction_impl on _create_window");

            }

            if (m_pprodevian && m_puserinteraction->is_graphical())
            {

               m_pprodevian->prodevian_reset(m_puserinteraction);

            }

         }

         if(m_pprodevian)
         {

            m_pprodevian->defer_create_prodevian();

         }

      }

   }


   void interaction_impl::_001OnPrioCreate(::message::message * pmessage)
   {

      if(::is_null(m_puserinteraction->m_pinteractionScaler))
      {

         m_puserinteraction->m_pinteractionScaler = __new(::user::interaction_scaler());

      }

      m_puserinteraction->m_pinteractionScaler->on_display_change(m_puserinteraction);

   }


   void interaction_impl::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         INFORMATION("user::interaction_impl::on_message_show_window bShow = true");

         if (m_puserinteraction->const_layout().design().display() != ::e_display_iconic)
         {

            if (m_puserinteraction->get_parent() == nullptr)
            {

               m_puserinteraction->check_transparent_mouse_events();

            }

         }
         else
         {

            //stop_prodevian();
            //child_post_quit("prodevian");

         }

      }
      else
      {
         
         INFORMATION("user::interaction_impl::on_message_show_window bShow = false");

         {

            decltype(m_userinteractionaMouseHover) userinteractiona;

            {

               _synchronous_lock synchronouslock(mutex());

               userinteractiona = m_userinteractionaMouseHover;

               m_userinteractionaMouseHover.erase_all();

            }

            for (auto & pinteraction : userinteractiona)
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

            auto puserinteractionpointeraChild = m_puserinteraction->m_puserinteractionpointeraChild;

            if(puserinteractionpointeraChild)
            {

            //{

            //   _synchronous_lock synchronouslock(mutex());

            //   if(!m_puserinteraction)
            //   {

            //      return;

            //   }

            //   uia = m_puserinteraction->m_puserinteractionpointeraChild;

            //}

               for (auto & pinteraction : puserinteractionpointeraChild->interactiona())
               {

                  try
                  {

                     pinteraction->send_message(e_message_show_window, 0, SW_PARENTCLOSING);

                  }
                  catch (...)
                  {

                  }

               }

            }

         }

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if(m_puserinteraction)
      {

         m_puserinteraction->check_transparent_mouse_events();

         set_need_redraw();

      }

   }


#ifdef WINDOWS_DESKTOP


   void interaction_impl::_001OnWindowPosChanged(::message::message * pmessage)
   {

      throw ::interface_only();

   }


#endif


   void interaction_impl::BeginModalState()
   {

      throw ::interface_only();

   }


   void interaction_impl::EndModalState()
   {

      throw ::interface_only();

   }


   //void interaction_impl::CloseWindow()
   //{

   //   throw ::interface_only();

   //}


   //void interaction_impl::OpenIcon()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //i32 interaction_impl::GetCheckedRadioButton(i32 nIDFirstButton,i32 nIDLastButton)
   //{

   //   __UNREFERENCED_PARAMETER(nIDFirstButton);
   //   __UNREFERENCED_PARAMETER(nIDLastButton);

   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::_EnableToolTips(bool bEnable,::u32 nFlag)
   //{

   //   __UNREFERENCED_PARAMETER(bEnable);
   //   __UNREFERENCED_PARAMETER(nFlag);

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::_001BaseWndInterfaceMap()
   //{

   //   psystem->window_map().set(get_handle(), this);

   //}


   interaction_impl * interaction_impl::get_impl() const
   {

      return (::user::interaction_impl *) this;

   }


   void interaction_impl::_001UpdateBuffer()
   {

      if (!m_puserinteraction || is_destroying())
      {

         return;

      }

      ::rectangle_i32 rectangleWindow;

      m_puserinteraction->get_window_rect(rectangleWindow);

      windowing_output_debug_string("\n_001UpdateBuffer : after get_window_rect");

      string strType = __type_name(m_puserinteraction);

      if (strType.contains("list_box"))
      {

         output_debug_string("list_box");

      }

      {

         ::draw2d::lock draw2dlock(this);

         ::size_i32 sizeDrawn;

         //single_lock synchronouslockObjects(m_psystem->m_paurasystem->draw2d()->get_object_list_mutex());

         //if (!synchronouslockObjects.lock(0_s))
         //{

         //   return;

         //}
         //single_lock synchronouslockImages(m_psystem->m_paurasystem->draw2d()->get_image_list_mutex());

         //if (!synchronouslockImages.lock(0_s))
         //{

         //   return;

         //}
         //single_lock synchronouslockGraphicsContext(m_psystem->m_paurasystem->draw2d()->get_graphics_context_list_mutex());

         //if (!synchronouslockGraphicsContext.lock(0_s))
         //{

         //   return;

         //}
         _synchronous_lock slGraphics(m_pgraphics->mutex());

         ::synchronization_object * psync = m_pgraphics->get_buffer_sync();

         _synchronous_lock synchronouslock(psync);

         //windowing::graphics_lock graphicslock(m_pwindow);

         ::draw2d::graphics_pointer pgraphics = m_pgraphics->on_begin_draw();

         slGraphics.unlock();

         windowing_output_debug_string("\n_001UpdateBuffer : after on_begin_draw");

         if (is_destroying())
         {

            return;

         }

//#ifdef _UWP
         if (pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
         {

//#define SEVERITY_HIGH 5

            //int iSeverity = SEVERITY_HIGH;

            //for(index i = 0; i < iSeverity * 20; i++)
            //{

            output_debug_string("m_pgraphics->on_begin_draw FAILED (1)\n");

            //}

            return;

         }

//#endif

         pgraphics->on_begin_draw();

         pgraphics->m_phost = m_puserinteraction;

         pgraphics->m_puserstyle.release();

         if (pgraphics->m_pimage)
         {

            pgraphics->m_pimage->m_rectangleTag.Null();

            sizeDrawn = pgraphics->m_pimage->m_size;

         }

         string strBitmapSource = payload("bitmap-source");

         if (strBitmapSource.has_char())
         {

            auto pbitmapsourcebuffer = pgraphics->cast < ::graphics::bitmap_source_buffer >();

            if(pbitmapsourcebuffer)
            {




            }

         }

         if(m_puserinteraction)
         {

            auto r = m_puserinteraction->screen_rect();

            if (m_puserinteraction->is_finishing())
            {

               output_debug_string("::user::interaction_impl set_finish");

            }
            else
            {

               m_puserinteraction->_001PrintBuffer(pgraphics);

            }

            m_rectangleUpdateBuffer = r;

            //FORMATTED_TRACE("PrintBuffer (%d, %d)",  r.right, r.bottom);

            if(!m_pgraphics)
            {

               return;

            }

            m_pgraphics->m_bNewBuffer = true;

         }

         if (pgraphics->m_pimage)
         {

            pgraphics->m_pimage->m_rectangleTag = m_rectangleUpdateBuffer;

            m_sizeDrawn = sizeDrawn;

         }

         if (m_pgraphics)
         {

            m_pgraphics->on_end_draw();

         }

      }

   }


//void interaction_impl::_defer_start_prodevian()
//{

//   defer_fork("prodevian", [&]() { _thread_prodevian(); });

//}


   void interaction_impl::set_prodevian_fps(double dProdevianFps)
   {

      m_dProdevianFps = dProdevianFps;

      if (::is_set(m_pprodevian))
      {

         if (::is_set(m_puserinteraction) && m_puserinteraction->is_graphical())
         {

            m_pprodevian->set_prodevian_fps(m_dProdevianFps);

         }

      }

   }


   void interaction_impl::set_nominal_fps(double dNominalFps)
   {

      m_dNominalFps = dNominalFps;

      if (::is_set(m_pprodevian))
      {

         if (::is_set(m_puserinteraction) && m_puserinteraction->is_graphical())
         {

            m_pprodevian->set_nominal_fps(m_dNominalFps);

         }

      }

   }


   void interaction_impl::set_fps(double dFps)
   {

      m_dNominalFps = dFps;

      m_dProdevianFps = dFps;

      if (::is_set(m_pprodevian))
      {

         if (::is_set(m_puserinteraction) && m_puserinteraction->is_graphical())
         {

            m_pprodevian->set_fps(dFps);

         }

      }

   }


   double interaction_impl::get_prodevian_fps()
   {

      return m_dProdevianFps;

   }


   double interaction_impl::get_nominal_fps()
   {

      return m_dNominalFps;

   }


   double interaction_impl::get_output_fps()
   {

      return m_dOutputFps;

   }


   void interaction_impl::start_window_visual()
   {

      if (m_puserthread)
      {

         m_puserthread->start_window_visual();

      }
      else
      {

         m_puserinteraction->post_message(e_message_apply_visual);

      }

      //return true;

   }


   void interaction_impl::_001UpdateWindow()
   {

   }


   void interaction_impl::_001UpdateScreen()
   {

      _synchronous_lock synchronouslock(mutex());

      if (!m_puserinteraction)
      {

         return;

      }

      if (m_bOfflineRender)
      {

         return;

      }

      string strType = __type_name(m_puserinteraction);

      if(strType.contains_ci("list_box"))
      {

         auto edisplay = m_puserinteraction->const_layout().state(e_layout_design).display();

         bool bGraphicsSet = m_pgraphics.is_set();

         output_debug_string("_001UpdateScreen list_box");

      }

      if (m_pgraphics.is_set())
      {

         if (m_puserinteraction->layout().is_this_screen_visible())
         {

            //CINFO(prodevian)("going to update_window (1)");

            auto puserinteraction = m_puserinteraction.m_p;

            int * pi= (int*) puserinteraction;

            auto & i = *pi;

            //monitor_pointer(puserinteraction);

            auto & iStateCount = m_puserinteraction->layout().m_iStateCount;

            monitor_pointer(&iStateCount);

            m_pgraphics->update_screen();
            
            m_puserinteraction->set_layout_state(m_puserinteraction->const_layout().design());

         }

      }

   }


   void interaction_impl::process_message()
   {

      while (true)
      {

         __pointer(::message::message) pmessage;

         {

            synchronous_lock synchronouslock(mutex());

            if (m_messagelist.is_empty())
            {

               return;

            }

            pmessage = m_messagelist.pick_head();

         }

         message_handler(pmessage);

      }

   }


   void interaction_impl::queue_message_handler(::message::message * pmessage)
   {

      synchronous_lock synchronouslock(mutex());

      bool bWasEmpty = m_messagelist.is_empty();

      m_messagelist.add_tail(pmessage);

      if (bWasEmpty)
      {

         m_puserinteraction->m_pthreadUserInteraction->kick_idle();

      }

   }


   void interaction_impl::set_bitmap_source(const string& strBitmapSource)
   {

      m_strBitmapSource = strBitmapSource;

      if (m_pgraphics)
      {

         m_pgraphics->set_bitmap_source(strBitmapSource);

      }

      //return ::success;

   }


   void interaction_impl::clear_bitmap_source()
   {

      m_strBitmapSource.Empty();

      if (m_pgraphics)
      {

         m_pgraphics->clear_bitmap_source();

      }

      //return ::success;

   }


   void interaction_impl::update_graphics_resources()
   {

      single_lock synchronouslock(mutex());

      if (m_pgraphics.is_null())
      {

         //auto estatus =
         
         __raw_compose(m_pgraphics);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         if (m_pgraphics)
         {

            m_pgraphics->initialize_graphics_graphics(this);

         }

      }

      //m_pgraphics.is_set() ? ::success : ::error_failed;

   }


   void interaction_impl::interaction_post(const ::procedure & procedure)
   {

      auto puserinteraction = m_puserinteraction;

      if (::is_null(puserinteraction))
      {

         //return error_failed;

         throw ::exception(error_wrong_state);

      }

      auto puserthread = puserinteraction->m_pthreadUserInteraction;

      if (::is_null(puserthread))
      {

         throw ::exception(error_wrong_state);

      }

      puserthread->post_procedure(procedure);

   }

   
   guie_message_wnd::guie_message_wnd(::property_object * pobject)
   {

      m_puiForward = nullptr;

   }


   void guie_message_wnd::message_handler(::message::message * pmessage)
   {

      if(m_puiForward != nullptr)
      {

         return m_puiForward->message_handler(pmessage);

      }

   }


   CLASS_DECL_AURA void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction,const ::rectangle_i32 & rectangle)
   {

      ASSERT(::is_set(pinteraction));

      __pointer(::user::interaction) puiParent = pinteraction->get_parent();

      ASSERT(puiParent != nullptr);

      ::rectangle_i32 rectangleOld;

      pinteraction->get_window_rect(rectangleOld);

      puiParent->screen_to_client(rectangleOld);

      pinteraction->place(rectangle);

      pinteraction->display(e_display_normal, e_activation_no_activate);

   }


   void interaction_impl::prodevian_redraw(bool bUpdateBuffer)
   {

      if(!m_pprodevian)
      {

         return;

      }

      if (m_puserinteraction->m_ewindowflag & e_window_flag_embedded_prodevian)
      {

         m_pprodevian->m_message.wParam |= 1;

         m_pprodevian->prodevian_iteration();

      }
      else
      {

         m_pprodevian->post_message(e_message_redraw, bUpdateBuffer ? 1 : 0);

      }

   }


   void interaction_impl::set_finish(::object * pcontextobjectFinish)
   {

      if(!is_destroying())
      {

         if (m_pgraphics)
         {

            _synchronous_lock slGraphics(m_pgraphics->mutex());

            ::synchronization_object * psync = m_pgraphics->get_draw_lock();

            _synchronous_lock synchronouslock(psync);

            slGraphics.unlock();

            set_destroying();

         }

      }

      //return 
      
      ::user::primitive_impl::set_finish();

   }


   void interaction_impl::prodevian_stop()
   {

      auto pprodevian = m_pprodevian;

      if (::is_set(pprodevian) && ::is_set(m_pgraphics))
      {

         {

            _synchronous_lock slGraphics(m_pgraphics->mutex());

            ::synchronization_object * psyncDraw = m_pgraphics->get_draw_lock();

            _synchronous_lock slDraw(psyncDraw);

            slGraphics.unlock();

            //pprodevian->m_puserinteraction = nullptr;

            //pprodevian->m_pimpl = nullptr;

            pprodevian->set_finish();

         }

         //{

         //   _synchronous_lock synchronouslock(mutex());

         //   _synchronous_lock slGraphics(m_pgraphics->mutex());

         //   m_pprodevian);

         //}

      }

   }


   void interaction_impl::prodevian_update_screen()
   {

      _001UpdateScreen();

      //return true;

   }


   //void interaction_impl::set_handle(::windowing::window * pwindow)
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


   //void interaction_impl::attach(::windowing::window * pwindowNew)
   //{

   //   ASSERT(get_handle() == nullptr);

   //   ASSERT(oswindow_interaction(oswindowNew) == nullptr);

   //   if(oswindowNew == nullptr)
   //   {

   //      return false;

   //   }

   //   //set_handle(oswindowNew);

   //   ASSERT(psystem->ui_from_handle(get_handle()) == m_puserinteraction);

   //   return true;

   //}


   void interaction_impl::destroy()
   {

      return ::user::primitive_impl::destroy();

   }


   //oswindow interaction_impl::detach()
   //{

   //   ::windowing::window * pwindow = get_handle();

   //   if(oswindow != nullptr)
   //   {

   //      set_handle(nullptr);

   //   }

   //   return oswindow;

   //}


   oswindow interaction_impl::get_oswindow() const
   {
       
      if(!m_pwindow)
      {
         
         return nullptr;
         
      }

      return (oswindow) m_pwindow->get_oswindow();

   }


   bool interaction_impl::is_composite()
   {

      return m_puserinteraction->m_ewindowflag & e_window_flag_composite;

   }


   ::graphics::graphics * interaction_impl::get_window_graphics()
   {

      return m_pgraphics;

   }


   ::user::element * interaction_impl::get_keyboard_focus()
   {

      return m_puserinteractionKeyboardFocus;

   }


   void interaction_impl::on_prio_message_set_focus(::message::message * pmessage)
   {

      __pointer(::message::set_keyboard_focus) psetkeyboardfocus(pmessage);

//      on_final_set_keyboard_focus();
//
//      if (m_puserinteraction->m_ewindowflag & e_window_flag_focus)
//      {
//
//         return;
//
//      }
//
//      m_puserinteraction->m_ewindowflag |= e_window_flag_focus;

   }
   

   bool interaction_impl::on_keyboard_focus(::user::primitive* pfocus)
   {

      auto pwindowing = m_puserinteraction->windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         strsize iBeg = 0;

         strsize iEnd = 0;

         pfocus->_001GetSel(iBeg, iEnd);

         string strText;

         pfocus->_001GetText(strText);

         auto pwindowing = m_puserinteraction->windowing();

         auto ptexteditorinterface = pwindowing->get_text_editor_interface();

         ptexteditorinterface->set_editor_selection(iBeg, iEnd);

         ptexteditorinterface->set_editor_text(strText);

         ptexteditorinterface->show_software_keyboard();

      }

      return true;

   }


   
//   void interaction_impl::on_final_set_keyboard_focus(::message::set_keyboard_focus * psetkeyboardfocus)
   void interaction_impl::on_final_set_keyboard_focus()
   {

      _synchronous_lock synchronouslock(mutex());

      if (m_puserinteractionKeyboardFocusRequest)
      {
         
         if(m_puserinteractionKeyboardFocusRequest != m_puserinteractionKeyboardFocus)
         {

            m_puserinteractionKeyboardFocus = m_puserinteractionKeyboardFocusRequest;

            m_puserinteractionKeyboardFocusRequest = nullptr;

            auto puserinteractionKeyboardFocus = m_puserinteractionKeyboardFocus;

            if (puserinteractionKeyboardFocus)
            {

               synchronouslock.unlock();

               puserinteractionKeyboardFocus->on_set_keyboard_focus();

            }
            
         }

      }
//      else
//      {
//
//         m_puserinteractionToKillKeyboardFocus = m_puserinteractionKeyboardFocus;
//
//         synchronouslock.unlock();
//
//         on_final_kill_keyboard_focus();
//
//      }

   }


   bool interaction_impl::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      output_debug_string("::android::interaction_impl::keyboard_focus_OnKillFocus() (1) \n");

//      auto pwindowing = m_puserinteraction->windowing();
//
//      auto ptexteditorinterface = pwindowing->get_text_editor_interface();
//
//      if (::is_set(ptexteditorinterface))
//      {
//
//         ptexteditorinterface->hide_software_keyboard();
//
//      }


//      _synchronous_lock synchronouslock(mutex());
//
//      auto puserinteractionKeyboardFocus = m_puserinteractionKeyboardFocus;
//
//      if (puserinteractionKeyboardFocus)
//      {
//
//         m_puserinteractionKeyboardFocus.release();
//
//         synchronouslock.unlock();
//
//         puserinteractionKeyboardFocus->on_kill_keyboard_focus();
//
//      }

      return true;

   }

   bool interaction_impl::keyboard_focus_OnChildKillFocus()
   {

      output_debug_string("::android::interaction_impl::keyboard_focus_OnChildKillFocus() (2) \n");

      auto pwindowing = m_puserinteraction->windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         ptexteditorinterface->hide_software_keyboard();

      }

      return true;

   }



   void interaction_impl::on_message_kill_focus(::message::message * pmessage)
   {

      __pointer(::message::kill_keyboard_focus) pkillkeyboardfocus(pmessage);

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_focus))
      {

         return;

      }

      m_puserinteraction->m_ewindowflag -= e_window_flag_focus;

      on_final_kill_keyboard_focus();

   }

//void interaction_impl::on_final_kill_keyboard_focus(::message::kill_keyboard_focus * pkillkeyboardfocus)

   void interaction_impl::on_final_kill_keyboard_focus()
   {

      _synchronous_lock synchronouslock(mutex());

      if (m_puserinteractionToKillKeyboardFocus && m_puserinteractionToKillKeyboardFocus != m_puserinteractionKeyboardFocusRequest)
      {
         
         auto pinteraction = m_puserinteractionToKillKeyboardFocus;

         if(m_puserinteractionKeyboardFocus == pinteraction)
         {
            
            m_puserinteractionKeyboardFocus.release();
            
         }

         m_puserinteractionToKillKeyboardFocus = nullptr;

         synchronouslock.unlock();

         pinteraction->on_kill_keyboard_focus();

      }

   }


   //void interaction_impl::impl_set_keyboard_focus(::user::primitive * pprimitiveFocusNew)
   //{

   //   ::user::primitive * pprimitiveFocusOld = m_pprimitiveFocus;

   //   if(pprimitiveFocusOld == pprimitiveFocusNew)
   //   {

   //      return true;

   //   }

   //   auto oswindow = get_handle();

   //   auto oswindowPrevious = ::set_keyboard_focus(oswindow);

   //   m_pprimitiveFocus = pprimitiveFocusNew;

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusOld))
   //      {

   //         if(pprimitiveFocusOld->m_bFocus)
   //         {

   //            pprimitiveFocusOld->send_message(e_message_kill_focus);

   //         }

   //         pprimitiveFocusOld->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusNew))
   //      {

   //         if (!pprimitiveFocusNew->m_bFocus)
   //         {

   //            pprimitiveFocusNew->send_message(e_message_set_focus);

   //         }

   //         pprimitiveFocusNew->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


   //void interaction_impl::impl_erase_keyboard_focus(::user::primitive * pprimitiveFocusRemove)
   //{

   //   if (::is_null(pprimitiveFocusRemove))
   //   {

   //      return false;

   //   }

   //   ::user::primitive * pprimitiveFocusKillFocus = m_pprimitiveFocus;

   //   if (pprimitiveFocusKillFocus != pprimitiveFocusRemove)
   //   {

   //      return false;

   //   }

   //   m_pprimitiveFocus = nullptr;

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusKillFocus))
   //      {

   //         if (pprimitiveFocusKillFocus->m_bFocus)
   //         {

   //            pprimitiveFocusKillFocus->send_message(e_message_kill_focus);

   //         }

   //         pprimitiveFocusKillFocus->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


   //void interaction_impl::impl_clear_keyboard_focus()
   //{

   //   ::user::primitive * pprimitiveFocusKillFocus = m_pprimitiveFocus;

   //   m_pprimitiveFocus = nullptr;

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusKillFocus))
   //      {

   //         if (pprimitiveFocusKillFocus->m_bFocus)
   //         {

   //            pprimitiveFocusKillFocus->send_message(e_message_kill_focus);

   //         }

   //         pprimitiveFocusKillFocus->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


   //void interaction_impl::set_keyboard_focus(::user::primitive * pprimitive)
   //{

   //   if(::is_null(pprimitive))
   //   {

   //      impl_clear_keyboard_focus();

   //      return true;

   //   }

   //   auto pinteraction = m_puserinteraction;

   //   if (::is_null(pinteraction))
   //   {

   //      return false;

   //   }

   //   if (!pinteraction->is_ascendant_of(pprimitive, true))
   //   {

   //      return false;

   //   }

   //   impl_set_keyboard_focus(pprimitive);

   //   return true;

   //}


   //void interaction_impl::erase_keyboard_focus(::user::primitive * pprimitive)
   //{

   //   if (pprimitive == nullptr)
   //   {

   //      impl_erase_keyboard_focus(pprimitive);

   //      return true;

   //   }

   //   if (pprimitive == m_puserinteraction || pprimitive == this)
   //   {

   //      impl_erase_keyboard_focus(pprimitive);

   //      return true;

   //   }

   //   ::user::interaction * pinteraction = pprimitive->get_host_window();

   //   if (pinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   if (!m_puserinteraction->is_ascendant_of(pinteraction, true))
   //   {

   //      return false;

   //   }

   //   impl_erase_keyboard_focus(pprimitive);

   //   return true;

   //}


   void interaction_impl::clear_keyboard_focus(::user::primitive_impl * pprimitiveimplGainingFocusIfAny)
   {

      auto puserinteraction = m_puserinteraction;

      if (!puserinteraction)
      {

         throw ::exception(error_failed);

      }

      auto pwindow = puserinteraction->window();

      if (!pwindow)
      {

         throw ::exception(error_failed);

      }

      auto pwindowing = pwindow->windowing();

      if (!pwindowing)
      {

         throw ::exception(error_failed);

      }

      ::windowing::window* pwindowGainingFocusIfAny = nullptr;
      
      if (pprimitiveimplGainingFocusIfAny)
      {

         pwindowGainingFocusIfAny = pprimitiveimplGainingFocusIfAny->window();

      }
      
      m_puserinteractionToKillKeyboardFocus = m_puserinteractionKeyboardFocus;
      
      on_final_kill_keyboard_focus();

      //pwindowing->clear_keyboard_focus(pwindowGainingFocusIfAny);

      //auto puserinteraction = m_puserinteraction;

      //if (::is_null(puserinteraction))
      //{

      //   return false;

      //}

      //::user::interaction * pinteractionHost = puserinteraction->get_host_window();

      //if (::is_null(pinteractionHost))
      //{

      //   return false;

      //}

      //auto pimplHost = pinteractionHost->m_pimpl;

      //if (::is_null(pimplHost))
      //{

      //   return false;

      //}

      //pimplHost->impl_clear_keyboard_focus();

      //return false;

   }


   void interaction_impl::post(::message::message * pmessage)
   {

      //if (m_puserthread)
      //{

      //   _synchronous_lock synchronouslock(m_puserthread->mutex());

      //   m_puserthread->m_messagebasea.add(pmessage);

      //   m_puserthread->kick_idle();

      //   return true;

      //}

      //m_puserinteraction->post_procedure(__routine([this, pmessage]()
      //{

        // return m_puserinteraction->message_handler(pmessage);

      //}));


      //return 
      
      m_puserinteraction->post(pmessage);

      //return true;

   }



   void interaction_impl::redraw_add(::object * p)
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      m_ptraRedraw.add(p);

   }


   void interaction_impl::redraw_erase(::object * p)
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      m_ptraRedraw.erase(p);

   }


   bool interaction_impl::has_redraw()
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      return m_ptraRedraw.has_elements();

   }


   ::mutex * interaction_impl::mutex_redraw()
   {

      if (m_pmutexRedraw == nullptr)
      {

         m_pmutexRedraw = __new(::mutex());

      }

      return m_pmutexRedraw;

   }


   bool interaction_impl::has_pending_graphical_update()
   {

      {

         _synchronous_lock synchronouslock(mutex());

         if (m_ptraRedraw.has_elements())
         {

            return true;

         }

      }

      return false;

   }


   void interaction_impl::on_after_graphical_update()
   {


//#ifdef ANDROID
//
//      operating_system_driver::get()->m_bRedraw = true;
//
//#endif


   }




   void interaction_impl::window_show()
   {

      if(::is_null(m_puserinteraction))
      {

         return;

      }

      // Request / Incoming changes / Prepare Internal Buffer
      auto & stateOutput = m_puserinteraction->const_layout().design();

      // Current/Previous Window State
      auto & stateWindow = m_puserinteraction->const_layout().window();

      if (stateOutput == stateWindow)
      {

         return;

      }

      auto eactivationOutput = stateOutput.activation();

      auto eactivationWindow = stateWindow.activation();

      auto edisplayOutput = stateOutput.display();

      auto edisplayWindow = stateWindow.display();

      auto pointOutput = stateOutput.origin();

      auto pointWindow = stateWindow.origin();

      auto sizeOutput = stateOutput.size();

      auto sizeWindow = stateWindow.size();

      auto zOutput = stateOutput.zorder();

      auto zWindow = stateWindow.zorder();

      bool shouldGetVisible = ::is_screen_visible(edisplayOutput);

      if(sizeOutput.is_empty())
      {

         INFORMATION("window_show rectangleUi isEmpty");

         return;

      }

      bool bWasVisible = ::is_screen_visible(edisplayWindow);

      __keep_flag_on(m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_apply_visual);

      ::u32 uFlags = 0;

      //bool bLayered = GetExStyle() & WS_EX_LAYERED;

      //if (bLayered)
      {

         uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;

      }
      //else
      //{

      //   uFlags |= SWP_ASYNCWINDOWPOS  | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;

      //}

      if (eactivationOutput & e_activation_no_activate)
      {

         uFlags |= SWP_NOACTIVATE;

      }

      // if GNOME
      // if Xorg
      // if Wayland

//#if !defined(LINUX)

      //if(m_sizeDrawn != sizeOutput)
      //{

      //   output_debug_string("blank borders (1), drawing extrapoation (1) or cut border (1)??\n");

      //}

      //sizeOutput = m_sizeDrawn;

      bool bSize = true;

      if (sizeWindow == sizeOutput)
      {

         bSize = false;

         uFlags |= SWP_NOSIZE;

      }
      else
      {

         uFlags |= SWP_ASYNCWINDOWPOS | SWP_FRAMECHANGED | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
         //uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
         //uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOCOPYBITS;

      }

      bool bMove = true;

      if (pointWindow == pointOutput)
      {

         bMove = false;

         uFlags |= SWP_NOMOVE;

      }

//#endif

      bool bVisibilityChange = is_different(bWasVisible, shouldGetVisible);

      if (bVisibilityChange)
      {

         if (shouldGetVisible)
         {

            uFlags |= SWP_SHOWWINDOW;

         }
         else
         {

            uFlags |= SWP_HIDEWINDOW;

         }

      }

      if (eactivationOutput & e_activation_no_activate)
      {

         uFlags |= SWP_NOACTIVATE;

      }

      bool bZ = zOutput.is_change_request();

      if (!bZ)
      {

         uFlags |= SWP_NOZORDER;

      }

      string strType = __type_name(m_puserinteraction);

      if (strType.contains("font_format"))
      {

         INFORMATION("font_format going to gather Z-Ordering information");

      }

      if(!m_puserinteraction)
      {

         return;

      }

      ::zorder zorderNew = (bZ ? zOutput : ::zorder());

      if (edisplayWindow == e_display_zoomed)
      {

         if (edisplayOutput != e_display_zoomed)
         {

            auto puserinteraction = m_puserinteraction;

            if (puserinteraction)
            {

               puserinteraction->_001OnExitZoomed();

            }

         }

      }

      bool bHasSetWindowPosition = false;

      if (shouldGetVisible
//#ifdef WINDOWS_DESKTOP
  //    && !bLayered
//#endif
         && (
            //#ifdef WINDOWS_DESKTOP
            //               !bLayered
            //#else
                           //(uFlags & (SWP_NOMOVE | SWP_NOSIZE)) != (SWP_NOMOVE | SWP_NOSIZE)
            //#endif
            bMove
            || bSize
            || bVisibilityChange
            || bZ
            )
         )
      {

         string strType = __type_name(m_puserinteraction);

         if (strType.contains("font_format"))
         {

            INFORMATION("font_format going to SetWindowPos");

         }
         else if (strType.contains("textformat"))
         {

            INFORMATION("text_format going to SetWindowPos");

         }

         // Commented on Windows
         //if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
         //{

         //   m_bEatMoveEvent = !(uFlags & SWP_NOMOVE) || !(uFlags & SWP_NOSIZE);

         //   m_bEatSizeEvent = !(uFlags & SWP_NOSIZE);

         //}

         //if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
         //{

         //   m_bPendingRedraw = true;

         //}
         // END Commented on Windows

         ::point_i32 pointBottomRight = pointOutput + sizeOutput;

         //output_debug_string("SetWindowPos bottom_right " + __string(pointBottomRight.x) + ", " + __string(pointBottomRight.y) + "\n");

//#if !defined(_UWP) && !defined(ANDROID)

         bHasSetWindowPosition = m_pwindow->on_set_window_position(
             zorderNew, 
             pointOutput.x, 
             pointOutput.y,
             sizeOutput.cx, 
             sizeOutput.cy,
             uFlags);

         //::SetWindowPos(get_handle(), oswindowInsertAfter,
         //   pointOutput.x, pointOutput.y,
         //   sizeOutput.cx, sizeOutput.cy,
         //   uFlags);

//#endif

         if (g_pointLastBottomRight != pointBottomRight)
         {

            TRACE("Different Bottom Right");

            g_pointLastBottomRight = pointBottomRight;

         }

         zOutput.clear_request();

         m_bOkToUpdateScreen = true;

      }

      if (edisplayOutput != edisplayWindow)
        //&& !::conditional(bLayered, bHasSetWindowPosition)
        //)
      {

//#ifdef WINDOWS
//
//         bool bShowOutput = windows_show_window(edisplayOutput, eactivationOutput);
//
//         bool bShowWindow = windows_show_window(edisplayWindow, eactivationWindow);
//
//         if (is_different(bShowOutput, bShowWindow))
//#endif
//         {

            m_puserinteraction->window_show_change_visibility();

         //}

      }

      if (eactivationOutput & e_activation_set_foreground)
      {

         //throw ::exception(todo);
         //m_puserinteraction->set();

         m_pwindow->set_foreground_window();

      }

      if (eactivationOutput & e_activation_set_active)
      {

         //throw ::exception(todo);
         ///m_puserinteraction->SetActiveWindow();

         m_pwindow->set_active_window();

      }

      if(!m_puserinteraction)
      {

         return;

      }

      m_puserinteraction->set_layout_state(m_puserinteraction->const_layout().design(), e_layout_window);

      m_puserinteraction->clear_activation(e_layout_design);

      m_puserinteraction->set_display(edisplayOutput, e_layout_design);

      ::windowing::window * pwindowFocus = nullptr;

      ::windowing::window * pwindowImpl = nullptr;

      ::user::interaction_impl* pimplFocus = nullptr;

      if (has_pending_focus() && m_puserinteraction != nullptr && m_puserinteraction->is_window_visible())
      {

         auto psession = get_session();

         auto pimplFocus = psession->m_pimplPendingFocus2;

         psession->m_pimplPendingFocus2 = nullptr;

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         oswindow oswindow = pimplFocus->get_oswindow();

         if (pimplFocus == this)
         {

            output_debug_string("optimized out a SetFocus");

         }
         else
         {

            m_puserinteraction->set_keyboard_focus();

         }

      }

      m_puserinteraction->visual_changed();

      m_puserinteraction->check_transparent_mouse_events();

      //m_puserinteraction->m_bReposition = false;

   }


   void interaction_impl::on_visual_applied()
   {

   }


   void interaction_impl::ShowWindow(const ::e_display & edisplay)
   {

      //return false;


   }


   void interaction_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void interaction_impl::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

      on_configuration_change(m_puserinteraction);

   }


   void interaction_impl::on_configuration_change(::user::primitive * pprimitiveSource)
   {

      _synchronous_lock synchronouslock(mutex());

      for(auto & puserinteraction : m_userinteractionaHideOnConfigurationChange.m_interactiona)
      {

         if(puserinteraction->is_window_screen_visible())
         {

            puserinteraction->hide();

            puserinteraction->set_need_redraw();

            puserinteraction->post_redraw();

         }

      }

   }


   void interaction_impl::window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

      m_puserinteraction->m_pthreadUserInteraction->post_procedure([this, edisplay, eactivation]()
      {

         if (!m_puserinteraction)
         {

            return;

         }

         __keep_flag_on(m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_show_window);

         if (edisplay == e_display_iconic)
         {

            if (eactivation == e_activation_no_activate)
            {

               m_pwindow->show_window(edisplay, eactivation);

            }
            else
            {

               m_pwindow->show_window(edisplay, eactivation);

            }

         }
         else 
         {

            m_pwindow->show_window(edisplay, eactivation);

         }

         if (m_puserinteraction)
         {

            m_puserinteraction->set_activation(e_activation_default, e_layout_design);

         }

      });

   }


   void interaction_impl::_001OnRedraw(::message::message* pmessage)
   {

      m_puserinteraction->prodevian_redraw(pmessage->m_wparam & 1);

   }


   void interaction_impl::_001OnDoShowWindow(::message::message * pmessage)
   {

      m_puserinteraction->window_show_change_visibility();

   }


   void interaction_impl::_001OnApplyVisual(::message::message* pmessage)
   {

      if (!m_puserinteraction)
      {

         return;

      }

      string strType = __type_name(m_puserinteraction);

      if (strType.contains_ci("filemanager"))
      {

         INFORMATION("filemanager apply visual");

      }

      if (m_puserinteraction->is_graphical())
      {

         window_show();

         if (::is_set(m_puserthread))
         {

            m_puserthread->m_evApplyVisual.set_event();

         }

      }

   }


   void interaction_impl::on_message_move(::message::message * pmessage)
   {

      m_puserinteraction->m_pinteractionScaler->on_display_change(m_puserinteraction);

      if(m_bEatMoveEvent)
      {

         m_bEatMoveEvent = false;

         return;

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

//      if (m_puserinteraction->layout().m_eflag)
//      {
//
//         return;
//
//      }

      __pointer(::message::move) pmove(pmessage);

//      if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
//      {
//
//         return;
//
//      }

//      bool bLayered = m_puserinteraction->GetExStyle() & WS_EX_LAYERED;
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
//         m_puserinteraction->layout().sketch().origin() = pmove->m_point;
//
//         m_puserinteraction->screen_origin() = pmove->m_point;
//
//      }

         //m_pwindow->m_point = pmove->m_point;

         auto & layout = m_puserinteraction->const_layout();

         auto sketch_origin = layout.sketch().origin();

         auto window_origin = layout.window().origin();

         m_puserinteraction->set_position(pmove->m_point, e_layout_window);

         if(window_origin != sketch_origin)
         {

            m_puserinteraction->set_position(pmove->m_point, e_layout_sketch);

            m_puserinteraction->set_reposition();

            m_puserinteraction->set_need_redraw();

            m_puserinteraction->post_redraw();

         }

         //if (m_puserinteraction->layout().is_moving())
         //{

           // INFORMATION("\nWindow is Moving :: on_message_move");

         //}

         //m_puserinteraction->layout().sketch().origin() = pmove->m_point;

         //if (m_puserinteraction->layout().sketch().display() != e_display_normal)
         //{

           // m_puserinteraction->display(e_display_normal);

         //}

         //m_puserinteraction->set_reposition();

         //m_puserinteraction->set_need_redraw();

         //m_puserinteraction->post_redraw();

      //}

   }


   void interaction_impl::on_message_size(::message::message * pmessage)
   {

      if(m_bEatSizeEvent)
      {

         m_bEatSizeEvent = false;

         return;

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->layout().m_eflag)
      {

         return;

      }

      __pointer(::message::size) psize(pmessage);

//      bool bLayered = m_puserinteraction->GetExStyle() & WS_EX_LAYERED;
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
//         m_puserinteraction->layout().window() = psize->m_size;
//
//      }

//      if (m_puserinteraction->layout().sketch().size() != psize->m_size)
//      {
//
//         m_puserinteraction->layout().sketch() = psize->m_size;
//
//         if (m_puserinteraction->layout().sketch().display() != e_display_normal)
//         {
//
//            m_puserinteraction->display(e_display_normal);
//
//         }
//
//         m_puserinteraction->set_need_layout();
//
//         m_puserinteraction->set_need_redraw();
//
//         m_puserinteraction->post_redraw();
//
//      }

      //m_pwindow->m_size = psize->m_size;

      m_puserinteraction->set_size(psize->m_size, e_layout_window);

      if ((m_puserinteraction->const_layout().sketch().size()
           != m_puserinteraction->const_layout().window().size()))
      {

         m_puserinteraction->set_size(m_puserinteraction->const_layout().window().size(), e_layout_sketch);
         
         int cx = m_puserinteraction->const_layout().sketch().size().width();
         
         int cy = m_puserinteraction->const_layout().sketch().size().height();
//         m_puserinteraction->layout().design().size() = m_puserinteraction->layout().window().size();
         
         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();
         
         m_puserinteraction->post_redraw();

         //
         //         m_puserinteraction->post_redraw();


         //if (m_puserinteraction->layout().is_moving())
         //{

         // INFORMATION("\nWindow is Moving :: on_message_move");

         //}

         //m_puserinteraction->layout().sketch().origin() = pmove->m_point;

         //if (m_puserinteraction->layout().sketch().display() != e_display_normal)
         //{

         // m_puserinteraction->display(e_display_normal);

         //}

//         m_puserinteraction->set_reposition();
//
//         m_puserinteraction->set_need_redraw();
//
//         m_puserinteraction->post_redraw();

      }

   }


   void interaction_impl::_001OnDestroyWindow(::message::message* pmessage)
   {

      if (m_puserinteraction && __type_name(m_puserinteraction).contains("notify_icon"))
      {

         INFORMATION("notify_icon");

      }

      if (m_bDestroyImplOnly)
      {

         destroy_impl_only();

      }
      else if(m_puserinteraction)
      {

         m_puserinteraction->destroy_window();

         output_debug_string("destroy_window");

      }

   }


   void interaction_impl::show_software_keyboard(::user::element * pelement)
   {

      throw ::interface_only();

   }


   void interaction_impl::hide_software_keyboard(::user::element * pelement)
   {

      throw ::interface_only();

   }


   void interaction_impl::non_top_most_upper_window_rects(::rectangle_i32_array& recta)
   {

      m_pwindow->non_top_most_upper_window_rects(recta);

   }


   bool interaction_impl::is_occluded()
   {

      ::rectangle_i32_array recta;

      non_top_most_upper_window_rects(recta);

      ::rectangle_i32 rectangle;

      m_puserinteraction->get_window_rect(rectangle);

      ::rectangle_i32 rTest;

      for (auto & rHigher : recta)
      {

         if (rTest.intersect(rHigher, rectangle))
         {

            return true;

         }

      }

      return false;

   }


   void interaction_impl::approximate_occlusion_rects(rectangle_i32_array& raTest)
   {

      raTest.erase_all();

      ::rectangle_i32_array ra;

      non_top_most_upper_window_rects(ra);

      if (ra.is_empty())
      {

         return;

      }

      ::rectangle_i32 rectangle;

      m_puserinteraction->get_window_rect(rectangle);

      for (auto & rHigher : ra)
      {

         ::rectangle_i32 rTest;

         if (rTest.intersect(rHigher, rectangle))
         {

            raTest.add(rTest);

         }

      }

      // First Exclude Full Intersections

   restartFullIntersectionExclusion:

      for (index i = 0; i < raTest.get_count(); i++)
      {

         for (index j = i + 1; j < raTest.get_count(); j++)
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
      // Intersection area is less than third the area of the rectangle_i32 with bigger area.

   restartPartialIntersectionExclusionEx:

      for (index i = 0; i < raTest.get_count(); i++)
      {

         for (index j = i + 1; j < raTest.get_count(); j++)
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


   i64 interaction_impl::approximate_occlusion_area()
   {

      rectangle_i32_array ra;

      approximate_occlusion_rects(ra);

      return ra.total_area();

   }


   i64 interaction_impl::opaque_area(const RECTANGLE_I32 * lpcrect)
   {

      _synchronous_lock synchronouslock(m_pgraphics->get_screen_sync());

      ::color::color colorTransparent(0);

      ::rectangle_i32 rectangle(lpcrect);

      m_puserinteraction->screen_to_client(rectangle);

      return rectangle.area() - m_pgraphics->get_screen_image()->get_rgba_area(colorTransparent, rectangle);

   }


   i64 interaction_impl::_001GetRectTopLeftWeightedArea(const RECTANGLE_I32 * lpcrect)
   {

      ::rectangle_i32 rectangle(lpcrect);

      m_puserinteraction->screen_to_client(rectangle);

      return m_pgraphics->_001GetTopLeftWeightedOpaqueArea(rectangle);

   }


   i64 interaction_impl::opaque_area()
   {

      ::color::color colorTransparent(0);

      ::rectangle_i32 rectangle;

      m_puserinteraction->get_window_rect(rectangle);

      return rectangle.area() - m_pgraphics->get_screen_image()->get_rgba_area(colorTransparent);

   }


   i64 interaction_impl::_001GetTopLeftWeightedArea()
   {

      ::color::color colorTransparent(0);

      ::rectangle_i32 rectangle;

      m_puserinteraction->get_window_rect(rectangle);
       
      if(::is_null(m_pgraphics))
      {
         
         return 0;
         
      }
      
      auto pimage = m_pgraphics->get_screen_image();
      
      if(::is_null(pimage))
      {
         
         return 0;
         
      }

      return pimage->_001GetTopLeftWeightedOpaqueArea(colorTransparent);

   }


   i64 interaction_impl::approximate_occlusion_area_except_self_transparent()
   {

      rectangle_i32_array ra;

      approximate_occlusion_rects(ra);

      ::i64 cApproxOpaqueArea = 0;

      for (auto& r : ra)
      {

         cApproxOpaqueArea += opaque_area(r);

      }

      return cApproxOpaqueArea;

   }


   double interaction_impl::approximate_occlusion_rate_except_self_transparent()
   {

      return (double)approximate_occlusion_area_except_self_transparent() / (double)opaque_area();

   }


   i64 interaction_impl::_001GetTopLeftWeightedOccludedOpaqueArea()
   {

      rectangle_i32_array ra;

      approximate_occlusion_rects(ra);

      ::i64 cApproxOpaqueArea = 0;

      for (auto& r : ra)
      {

         cApproxOpaqueArea += _001GetRectTopLeftWeightedArea(r);

      }

      return cApproxOpaqueArea;

   }


   double interaction_impl::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      auto iWeightedOccludedOpaqueArea = _001GetTopLeftWeightedOccludedOpaqueArea();

      auto iWeightedOpaqueArea = _001GetTopLeftWeightedArea();

      double dWeightedOccludedOpaqueArea = (double) iWeightedOccludedOpaqueArea;

      double dWeightedOpaqueArea = (double) iWeightedOpaqueArea;

      double dRate = dWeightedOccludedOpaqueArea / dWeightedOpaqueArea;

      return dRate;

   }


   double interaction_impl::approximate_occlusion_rate()
   {

      return (double)approximate_occlusion_area() / (double)m_puserinteraction->layout().area();

   }


   bool interaction_impl::is_this_visible(enum_layout elayout)
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      if (m_bOfflineRender)
      {

         return true;

      }

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_is_window))
      {

         return false;

      }

      if (m_puserinteraction->m_ewindowflag & e_window_flag_not_visible)
      {

         return false;

      }

      if (!m_puserinteraction->const_layout().state(elayout).is_visible())
      {

         return false;

      }

      return true;

   }


   strsize interaction_impl::get_window_text(char * sz, strsize s)
   {

      if (!m_pwindow)
      {

         return -1;

      }
      
      auto iSize = m_pwindow->get_window_text(sz, s);

      return iSize;

   }



   void interaction_impl::get_window_text(string & str)
   {

      if (!m_pwindow)
      {

         return ;

      }

      m_pwindow->get_window_text(str);

   }


   strsize interaction_impl::get_window_text_length()
   {

      return -1;

   }

   
   void interaction_impl::set_icon(::windowing::icon*)
   {

      //return ::success;

   }


   __pointer(::windowing::icon) interaction_impl::get_icon() const
   {

      return nullptr;

   }


   void interaction_impl::set_tool_window(bool bSet)
   {

      return m_pwindow->set_tool_window(bSet);

   }

   
   void interaction_impl::android_fill_plasma(const void* pixels, int width, int height, int stride, ::i64 time_ms)
   {

      synchronous_lock synchronouslock(m_pgraphics->get_screen_sync());

      auto pimageSource = m_pgraphics->get_screen_image();

      pimageSource->map();

      auto wSource = pimageSource->width();

      auto hSource = pimageSource->height();

      auto pdataSource = pimageSource->get_data();

      auto scanSource = pimageSource->m_iScan;


#ifdef __i386__

      ::copy_colorref_swap_red_blue((color32_t *) pixels, minimum(width, wSource), minimum(height, hSource), stride, pdataSource, scanSource);

#else

      ::copy_colorref((color32_t*)pixels, minimum(width, wSource), minimum(height, hSource), stride, pdataSource, scanSource);

#endif

   }


} // namespace user



