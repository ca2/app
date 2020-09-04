#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/message.h"
#include "interaction_thread.h"
#include "interaction_prodevian.h"
#include "aura/os/_os.h"
#include "aura/platform/mq.h"

point g_pointLastBottomRight;

#undef ALOG_CONTEXT
#define ALOG_CONTEXT (::trace_object(::trace_category_windowing))


#ifdef WINDOWS_DESKTOP
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#endif


#define REDRAW_HINTING
CLASS_DECL_AURA bool thread_set_name(const char *psz);

#define IMAGE_OK(pimpl) (::is_set(pimpl) && pimpl->area() > 0)
void windowing_output_debug_string(const char * pszDebugString);

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


//   ::user::style* interaction_impl::get_style() const
//   {
//
//      if (m_puserstyle)
//      {
//
//         return m_puserstyle;
//
//      }
//
//      auto& app = Application;
//
//      return app.get_user_style();
//
//   }


   void interaction_impl::user_common_construct()
   {

      m_pinteractionimpl = this;

      m_iState1 = 0;

//#if defined(WINDOWS_DESKTOP) && !defined(ENABLE_TEXT_SERVICES_FRAMEWORK)
//
//      m_himc = nullptr;
//
//#endif

      m_uiCodePage = 0;

      m_langid = 0;

      m_bPendingRedraw = false;

      m_bEatMoveEvent = false;

      m_bEatSizeEvent = false;

      m_bOkToUpdateScreen = true;
      m_bUpdatingBuffer = false;
      m_bFocus = false;
      m_bCursorRedraw = false;

      defer_create_mutex();

      m_bScreenRelativeMouseMessagePosition  = true;
      m_bTranslateMouseMessageCursor         = true;
      m_bComposite                           = true;
      m_bUpdateGraphics                      = false;
      m_oswindow                             = nullptr;
      m_pprimitiveFocus                      = nullptr;
      m_bPendingRedraw                       = false;
      m_bTransparentMouseEvents              = false;

#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)

      set_config_fps(20.0);

#else

      set_config_fps(60.0);

#endif

   }


   void interaction_impl::on_tsf_activate(bool bActivate)
   {

      if (bActivate)
      {

         //get_wnd()->pred([this]()
         //   {

         //      //ImmSetOpenStatus(m_puserthread->m_himc, TRUE);



         ////      if (m_puserthread->m_peditwnd == nullptr)
         ////      {

         ////         m_puserthread->m_peditwnd = new CTSFEditWnd(System.m_hinstance, m_puserinteraction->get_handle());

         ////         m_puserthread->m_peditwnd->_Initialize(m_puserthread->m_pthreadmgr, m_puserthread->m_tfClientID);

         ////      }

         ////      m_puserthread->m_peditwnd->on_edit_set_focus(dynamic_cast <::user::interaction * > (get_focus_primitive()));

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

      if (m_bCursorRedraw)
      {

         ::point pointCursor;

         Session.get_cursor_pos(pointCursor);

         if (m_pointCursor != pointCursor)
         {

            if (_001IsPointInside(pointCursor))
            {

               return true;

            }

         }

      }

      return ::user::primitive::has_pending_redraw_flags();

   }


   void interaction_impl::set_need_layout()
   {

      m_puserinteraction->set_need_layout();

   }


   //bool interaction_impl::window_move(i32 x, i32 y)
   //{

   //   auto & stateRequest = m_puserinteraction->request_state();

   //   stateRequest.m_point.x = x;

   //   stateRequest.m_point.y = y;

   //   m_puserinteraction->set_reposition();

   //   return true;

   //}


   bool interaction_impl::has_pending_focus()
   {

      auto psession = &Session;

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

      auto psession = &Session;

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


   void interaction_impl::set_destroying()
   {

      m_bDestroying = true;

   }


   bool interaction_impl::set_pending_focus()
   {

      auto psession = &Session;

      if (::is_null(psession))
      {

         return false;

      }

      psession->m_pimplPendingFocus2 = this;

      return true;

   }


   bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const char * lpszName)
   {

      if(_is_window())
      {

         set_window_text(lpszName);

      }
      else
      {

         ::user::create_struct createstruct(0, nullptr, lpszName, WS_CHILD, nullptr);

         createstruct.hwndParent = MESSAGE_WINDOW_PARENT;

         if(!native_create_window_ex(pinteraction, createstruct))
         {

            return false;

         }

      }

      return true;

   }



   //bool interaction_impl::create_native_window(::user::native_window_initialize* pinitialize)
   //{

   //   UNREFERENCED_PARAMETER(pinitialize);
   //   ::exception::throw_interface_only();

   //   return false;

   //}

#ifdef WINDOWS_DESKTOP


   bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
   {
      UNREFERENCED_PARAMETER(pwi);
      ::exception::throw_interface_only();
      return false;
   }

   bool interaction_impl::GetScrollBarInfo(LONG idObject,PSCROLLBARINFO psbi) const
   {
      UNREFERENCED_PARAMETER(idObject);
      UNREFERENCED_PARAMETER(psbi);
      ::exception::throw_interface_only();
      return false;
   }

   bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
   {
      UNREFERENCED_PARAMETER(pti);
      ::exception::throw_interface_only();
      return false;
   }

#endif

#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)


   ::user::interaction_impl * interaction_impl::GetAncestor(UINT gaFlags) const
   {

      UNREFERENCED_PARAMETER(gaFlags);

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool interaction_impl::AnimateWindow(tick tick,u32 dwFlags)
   {
      UNREFERENCED_PARAMETER(tick);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only();
      return false;
   }

   bool interaction_impl::FlashWindowEx(u32 dwFlags,UINT uCount,tick tickTimeout)
   {
      UNREFERENCED_PARAMETER(dwFlags);
      UNREFERENCED_PARAMETER(uCount);
      UNREFERENCED_PARAMETER(tickTimeout);
      ::exception::throw_interface_only();
      return false;
   }

   bool interaction_impl::SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,u32 dwFlags)
   {
      UNREFERENCED_PARAMETER(crKey);
      UNREFERENCED_PARAMETER(bAlpha);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only();
      return false;
   }

   bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT * pptDst,SIZE * psize,
         ::draw2d::graphics * pDCSrc,POINT * pptSrc,COLORREF crKey,BLENDFUNCTION * pblend,u32 dwFlags)
   {
      UNREFERENCED_PARAMETER(pDCDst);
      UNREFERENCED_PARAMETER(pptDst);
      UNREFERENCED_PARAMETER(psize);
      UNREFERENCED_PARAMETER(pDCSrc);
      UNREFERENCED_PARAMETER(pptSrc);
      UNREFERENCED_PARAMETER(crKey);
      UNREFERENCED_PARAMETER(pblend);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only();

      return false;
   }

   bool interaction_impl::GetLayeredWindowAttributes(COLORREF * pcrKey,BYTE * pbAlpha,u32 * pdwFlags) const
   {
      UNREFERENCED_PARAMETER(pcrKey);
      UNREFERENCED_PARAMETER(pbAlpha);
      UNREFERENCED_PARAMETER(pdwFlags);
      ::exception::throw_interface_only();

      return false;
   }

   bool interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics,UINT nFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only();

      return false;
   }

#endif


   //LRESULT interaction_impl::default_window_procedure()
   //{
   //
   //   return default_window_procedure(m_uiMessage, m_wparam, m_lparam);

   //}


   void interaction_impl::pre_subclass_window()
   {
      ::exception::throw_interface_only();
   }


   ::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

      ::exception::throw_interface_only();

      return nullptr;

   }


   void * interaction_impl::get_os_data() const
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool interaction_impl::create_window_ex(::user::interaction * pinteraction, ::user::create_struct & createstruct, ::user::interaction * puiParent, id id)
   {

      if (puiParent == nullptr)
      {

         if (!native_create_window_ex(pinteraction, createstruct, nullptr, id))
         {

            return false;

         }

      }
      else
      {

         if (!native_create_window_ex(pinteraction, createstruct, puiParent->get_safe_handle(), id))
         {

            return false;

         }

      }

      return true;

   }


   // for child windows
   bool interaction_impl::pre_create_window(::user::create_struct & createstruct)
   {

      UNREFERENCED_PARAMETER(createstruct);

      return true;

   }


   bool interaction_impl::native_create_window_ex(::user::interaction * pinteraction, ::user::create_struct & createstruct, oswindow oswindowParent, id id)
   {

      m_puserinteraction = pinteraction;

      m_puserinteraction->m_pimpl = this;

      m_puserinteraction->m_pimpl2 = this;

      //#ifdef __APPLE__

            m_puserinteraction->m_ewindowflag |= window_flag_postpone_visual_update;

      //#endif



      bool bNewOwnThread = true;

      bool bProdevianThread = true;

      //if (createstruct.hwndParent != nullptr || (createstruct.style & WS_CHILD))
      if (createstruct.style & WS_CHILD)
      {

         // if child, uses parent window thread,

         bNewOwnThread = false;

         bProdevianThread = false;

      }

      if (createstruct.hwndParent == (oswindow) HWND_MESSAGE)
      {

         // except if "message"-only-window, in which casen it will have own thread

         bNewOwnThread = true;

         bProdevianThread = false;

      }

      if (m_puserinteraction->m_ewindowflag & window_flag_satellite_window)
      {

         // all except if satellite window it will use calling thread/parent window thread

         bNewOwnThread = false;

      }

      if (!m_puserinteraction->is_graphical())
      {

         bProdevianThread = false;

      }

      m_puserinteraction->create_layout(true);

      m_puserinteraction->place(rect_dim(
                            createstruct.x,
                            createstruct.y,
                            createstruct.cx,
                            createstruct.cy));

      sync_array synca;

      __pointer(manual_reset_event) peventStartedUser;

      __pointer(manual_reset_event) peventStartedProdevian;

      if (bNewOwnThread)
      {

         __raw_compose_new(m_puserthread);

         m_puserthread->initialize_user_thread(this, createstruct);

         __refer(m_puserinteraction->m_pthreadUserInteraction, m_puserthread);

         peventStartedUser = __new(manual_reset_event());

         m_puserthread->m_pevStarted = peventStartedUser;

      }

      if (bProdevianThread)
      {

         __raw_compose_new(m_pprodevian);

         m_pprodevian->initialize_prodevian(this);

         if (m_puserinteraction->is_graphical())
         {

            m_pprodevian->m_puserthread = m_puserthread;

         }

         if (!(m_puserinteraction->m_ewindowflag & window_flag_embedded_prodevian))
         {

            peventStartedProdevian = __new(manual_reset_event());

            m_pprodevian->m_pevStarted = peventStartedProdevian;

            if (!m_pprodevian->begin())
            {

               __release(m_pprodevian);

               __release(m_puserthread);

               m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

               return false;

            }

            synca.add(peventStartedProdevian);

         }
         else
         {

            m_pprodevian->init_thread();

         }

      }

      if (bNewOwnThread)
      {

         if (!m_puserthread->begin())
         {

            __release(m_pprodevian);

            __release(m_puserthread);

            m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

            return false;

         }

         synca.add(peventStartedUser);

         synca.wait();

         if (!m_puserinteraction || !m_puserinteraction->is_window())
         {

            return false;

         }

         if(m_puserthread->m_result.failed())
         {

            if(m_puserinteraction)
            {

               m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

            }

            __release(m_pprodevian);

            __release(m_puserthread);

            return false;

         }

         peventStartedUser.release();

         if (::is_set(m_pprodevian))
         {

            if(m_pprodevian->m_result.failed())
            {

               if(m_puserinteraction)
               {

                  m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

               }

               __release(m_pprodevian);

               __release(m_puserthread);

               return false;

            }

            peventStartedProdevian.release();

            if (m_pprodevian->thread_active())
            {

               m_pprodevian->release();

            }

         }

      }
      else
      {

         synca.wait(true, one_minute());

         if (::is_set(m_pprodevian))
         {

            peventStartedProdevian.release();

            if (m_pprodevian->thread_active())
            {

               m_pprodevian->release();

            }

         }

         if (!_native_create_window_ex(createstruct))
         {

            return false;

         }

      }

      return true;

   }


   bool interaction_impl::_native_create_window_ex(::user::create_struct & createstruct)
   {

      return false;

   }




   bool interaction_impl::create_window(::user::interaction * pinteraction, const char * pszClassName, const char * pszWindowName, u32 uStyle, const ::rect & rect, ::user::interaction * puiParent, id id, ::create * pcreate)

   {

      // can't use for desktop or pop-up windows (use create_window_ex instead)
      ASSERT(puiParent != nullptr);
      ASSERT((uStyle & WS_POPUP) == 0);

      ::user::create_struct createstruct;

      createstruct.dwExStyle = 0;

#ifdef WINDOWS

      wstring wstrClassName(pszClassName);
      createstruct.lpszClass = wstrClassName;
      wstring wstrWindowName(pszWindowName);
      createstruct.lpszName = wstrWindowName;

#else

      createstruct.lpszClass = pszClassName;
      createstruct.lpszName = pszWindowName;

#endif

      createstruct.style = uStyle | WS_CHILD;
      createstruct.x = rect.left;
      createstruct.y = rect.top;
      createstruct.cx = rect.width();
      createstruct.cy = rect.height();
      createstruct.hwndParent = puiParent->get_safe_handle();
#ifdef _UWP
      createstruct.pCreateParams = (LPVOID)pcreate;
#else
      createstruct.lpCreateParams = (LPVOID)pcreate;
#endif


      return create_window_ex(pinteraction, createstruct, puiParent, id);

   }



   void interaction_impl::prio_install_message_routing(::channel * pchannel)
   {

      ::user::primitive_impl::prio_install_message_routing(pchannel);

   }


   void interaction_impl::last_install_message_routing(::channel * pchannel)
   {

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &interaction_impl::_001OnCreate);

      ::user::primitive_impl::last_install_message_routing(pchannel);

      if (!m_puserinteraction->m_bMessageWindow)
      {

         IGUI_MSG_LINK(message_redraw, pchannel, this, &interaction_impl::_001OnRedraw);
         IGUI_MSG_LINK(message_apply_visual, pchannel, this, &interaction_impl::_001OnApplyVisual);


//#ifndef LINUX
         IGUI_MSG_LINK(WM_MOVE, pchannel, this, &interaction_impl::_001OnMove);
         IGUI_MSG_LINK(WM_SIZE, pchannel, this, &interaction_impl::_001OnSize);
//#endif


         IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &interaction_impl::_001OnShowWindow);
         IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &interaction_impl::_001OnKillFocus);
         IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &interaction_impl::_001OnSetFocus);

      }

      IGUI_MSG_LINK(message_destroy_window, pchannel, this, &interaction_impl::_001OnDestroyWindow);

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

         __pointer(::user::interaction) pinteraction;

         ::rect rectUi;

         ::point pointCursor;

         Session.get_cursor_pos(pointCursor);

         ::user::interaction_pointer_array uia;

         {

            sync_lock sl(mutex());

            uia = m_guieptraMouseHover;

            m_guieptraMouseHover.remove_all();

         }

         for(auto & pinteraction : uia.ptra())
         {

            try
            {

               pinteraction->send_message(WM_MOUSELEAVE);

            }
            catch (...)
            {

            }

         }

      }

   }


   void interaction_impl::_001OnTriggerMouseInside()
   {

      m_puserinteraction->m_bMouseHover = true;

   }


   void interaction_impl::_008OnMouse(::message::mouse * pmouse)
   {

      if(!m_puserinteraction)
      {

         return;

      }

      bool bPointInside;

      bPointInside = m_puserinteraction->_001IsPointInside(pmouse->m_point);

      if (!bPointInside)
      {

         if (pmouse->m_puserinteraction == m_puserinteraction)
         {

            bPointInside = true;

         }

      }

      if (pmouse->m_id == WM_LBUTTONUP)
      {

         ::output_debug_string("lbutton_up");

      }

      {

         ::user::interaction_pointer_array uia;

         {

            sync_lock sl(mutex());

            for(auto & pinteraction : m_guieptraMouseHover)
            {

               try
               {

                  if (!pinteraction->_001IsPointInside(pmouse->m_point))
                  {

                     uia.add(pinteraction);

                  }

               }
               catch(...)
               {

               }

            }

            ::papaya::array::remove_array(m_guieptraMouseHover, uia.ptra());

         }

         for(auto & pinteraction : uia.ptra())
         {

            pinteraction->send_message(WM_MOUSELEAVE);

         }

      }

      oswindow oswindow = Session.get_capture();

      if (oswindow == nullptr || oswindow == get_handle())
      {

         if (!m_puserinteraction->m_bMouseHover && bPointInside)
         {

            m_puserinteraction->_001OnTriggerMouseInside();

         }

      }

      if(oswindow != nullptr)
      {


         if (pmouse->m_id == WM_LBUTTONUP)
         {

            ::output_debug_string("lbutton_up");

         }
         ::user::interaction * puiCapture = Session.m_puiCapture;

         if (puiCapture == nullptr)
         {

            puiCapture = System.ui_from_handle(oswindow);

            if (puiCapture == nullptr)
            {

               puiCapture = m_puserinteraction;

            }

         }

         if (m_puserinteraction == Session.m_puiHost.get())
         {
            try
            {

               //(puiCapture->m_pimpl->*puiCapture->m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <::message::message *> (pmouse->);

               puiCapture->message_handler(pmouse);

            }
            catch (...)
            {

            }
         }
         else
         {

            try
            {

               //(puiCapture->m_pimpl->*puiCapture->m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <::message::message *> (pmouse->);

               puiCapture->_000OnMouse(pmouse);

            }
            catch (...)
            {

            }

         }

         return;

      }

      if (m_puserinteraction != nullptr)
      {


         if (pmouse->m_id == WM_LBUTTONUP)
         {

            ::output_debug_string("lbutton_up");

         }
         m_puserinteraction->_000OnMouse(pmouse);

      }

      if (pmouse->m_bRet)
      {

         return;

      }

   }


   bool interaction_impl::add_prodevian(::context_object * pobject)
   {

      sync_lock sl(m_puserthread->mutex());

      if(m_ptraProdevian.add_unique(pobject))
      {

         m_puserinteraction->post_message(message_redraw, 1);

         return true;

      }

      return false;

   }


   bool interaction_impl::remove_prodevian(::context_object * pobject)
   {

      if (!m_puserthread)
      {

         return false;

      }

      sync_lock sl(m_puserthread->mutex());

      bool bRemove = m_ptraProdevian.remove(pobject) > 0;

      if (bRemove)
      {

         m_puserinteraction->post_message(message_redraw, 1);

      }

      return bRemove;

   }





   void interaction_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      if (pinterface == nullptr)
      {

         return;

      }

      if (pinterface->m_pimpl->m_bDestroyImplOnly)
      {

         return;

      }

      sync_lock sl(mutex());

      m_guieptraMouseHover.add_unique(pinterface);

//      defer_fork("track_mouse_leave", [this]()
//      {
//
//         while(thread_get_run())
//         {
//
//            {
//
//               sync_lock sl(mutex());
//
//               if(m_guieptraMouseHover.is_empty())
//               {
//
//                  break;
//
//               }
//
//            }
//
//            if(!m_puserinteraction)
//            {
//
//               break;
//
//            }
//
//            m_puserinteraction->defer_notify_mouse_move();
//
//            Sleep(100);
//
//         }
//
//      });

   }


   bool interaction_impl::mouse_hover_remove(::user::interaction * pinterface)
   {

      sync_lock sl(mutex());

      return m_guieptraMouseHover.remove(pinterface) > 0;

   }


   void interaction_impl::_001OnCaptureChanged(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      Session.m_puiCapture = nullptr;

   }


   bool interaction_impl::__windows_message_bypass(oswindow oswindow, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {

      return false;

   }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {

      ::user::primitive::install_message_routing(pchannel);

      if (!m_puserinteraction->m_bMessageWindow)
      {

         IGUI_MSG_LINK(WM_CAPTURECHANGED, pchannel, this, &interaction_impl::_001OnCaptureChanged);

      }

      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &interaction_impl::_001OnDestroy);

   }


   void interaction_impl::_001OnDestroy(::message::message * pmessage)
   {

      if (m_puserinteraction && ::str::demangle(m_puserinteraction->type_name()).contains("notify_icon"))
      {

         INFO("notify_icon");

      }

      __release(m_pgraphics);

      UNREFERENCED_PARAMETER(pmessage);

      {

         auto psync = mutex();

         sync_lock sl(mutex());

         m_guieptraMouseHover.remove_all();

      }

   }



   void interaction_impl::PostNcDestroy()
   {

      string strType = m_puserinteraction->type_name();

      if (strType.contains("main_frame"))
      {

         output_debug_string("main_frame");

      }

      ::user::primitive::PostNcDestroy();

      detach();

      m_puserinteraction.release();

      //release_parents();

      auto pwindowthread = m_puserthread;

      if (::is_set(pwindowthread))
      {

         pwindowthread->m_pimpl.release();

      }

   }


   void interaction_impl::on_final_release()
   {

   }



   void interaction_impl::assert_valid() const
   {

      ::user::primitive::assert_valid();

   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {

      ::user::primitive::dump(dumpcontext);

   }


   bool interaction_impl::destroy_impl_only()
   {

      if (!m_bDestroyImplOnly)
      {

         m_bDestroyImplOnly = true;

         ::multithreading::set_finish(m_pprodevian);

         if (::is_set(m_puserinteraction))
         {

            INFO(::str::demangle(m_puserinteraction->type_name()) + "::destroy_impl_only");

            m_puserinteraction->transfer_receiver(m_idroute, this);

         }

         m_puserinteraction->m_pimpl.release();

         m_puserinteraction->m_pimpl2.release();

         m_puserinteraction = nullptr;

         oswindow oswindow = get_handle();

         mq_post_message(oswindow, message_destroy_window, 0, 0);

         return true;

      }
      else if(m_bUserPrimitiveOk)
      {

         if (m_puserinteraction)
         {

            INFO(::str::demangle(m_puserinteraction->type_name()) + "::destroy_impl_only ( 2)");

         }

         m_bUserPrimitiveOk = false;

         return ::destroy_window(m_oswindow);

      }
      else
      {

         return false;

      }

   }


   bool interaction_impl::DestroyWindow()
   {

      if (m_bDestroying)
      {

         return true;

      }

      if (!m_bDestroying)
      {

         m_bDestroying = true;

         m_puserinteraction->post_message(message_destroy_window);

         return true;

      }

      bool bResult = ::user::primitive::DestroyWindow();

      return bResult;

   }


   void interaction_impl::destroy_window()
   {

      auto strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("main_frame"))
      {

         output_debug_string("main_frame user::interaction_impl::destroy_window");

      }

      ::destroy_window(m_oswindow);

   }


   //void interaction_impl::default_window_procedure(::message::message * pmessage)
   //{

   //   UNREFERENCED_PARAMETER(pmessage);

   //}


   void interaction_impl::pre_translate_message(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::exception::throw_interface_only();

   }


   void interaction_impl::GetWindowText(string & rectString)
   {

      UNREFERENCED_PARAMETER(rectString);

      ::exception::throw_interface_only();

   }


   i32 interaction_impl::GetChildByIdText(i32 nID,string & rectString) const
   {

      UNREFERENCED_PARAMETER(nID);

      UNREFERENCED_PARAMETER(rectString);

      ::exception::throw_interface_only();

      return 0;

   }


#ifdef WINDOWS_DESKTOP


   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* pwndpl)

   {

      UNREFERENCED_PARAMETER(pwndpl);


      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* pwndpl)
   {

      UNREFERENCED_PARAMETER(pwndpl);

      ::exception::throw_interface_only();

      return false;

   }


#endif


   void interaction_impl::PrepareForHelp()
   {

      ::exception::throw_interface_only();

   }


   void interaction_impl::route_command_message(::user::command * pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

      ::exception::throw_interface_only();

   }


   void interaction_impl::_002OnDraw(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::exception::throw_interface_only();

   }


   void interaction_impl::message_handler(::message::base * pbase)
   {

      if (m_puserinteraction)
      {

         m_bDestroyImplOnly ? route_message(pbase) : m_puserinteraction.m_p->route_message(pbase);

      }

   }


   void interaction_impl::default_window_procedure(::message::message * pmessage)
   {

   }


   //bool interaction_impl::OnNotify(::message::base * pbase)
   //{

   //   UNREFERENCED_PARAMETER(pbase);

   //   ::exception::throw_interface_only();

   //}


   bool interaction_impl::IsTopParentActive()
   {
      ::exception::throw_interface_only();

      return false;
   }

   void interaction_impl::ActivateTopParent()
   {
      ::exception::throw_interface_only();
   }


   //i32 interaction_impl::message_box(const char * pszText,const char * pszCaption,UINT nType)

   //{
   //   UNREFERENCED_PARAMETER(pszText);

   //   UNREFERENCED_PARAMETER(pszCaption);

   //   UNREFERENCED_PARAMETER(nType);
   //   ::exception::throw_interface_only();

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
   ::exception::throw_interface_only();
   }*/

   i32 interaction_impl::SetScrollPos(i32 nBar,i32 nPos,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nPos);
      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only();

      return 0;
   }

   i32 interaction_impl::GetScrollPos(i32 nBar) const
   {
      UNREFERENCED_PARAMETER(nBar);
      ::exception::throw_interface_only();

      return 0;
   }

   void interaction_impl::SetScrollRange(i32 nBar,i32 nMinPos,i32 nMaxPos,bool bRedraw)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(nMinPos);
      UNREFERENCED_PARAMETER(nMaxPos);
      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only();


   }


   void interaction_impl::GetScrollRange(i32 nBar,LPINT pMinPos,LPINT pMaxPos) const

   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(pMinPos);
      UNREFERENCED_PARAMETER(pMaxPos);

      ::exception::throw_interface_only();

   }


   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(i32 nBar,bool bEnable)
   {
      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bEnable);
      ::exception::throw_interface_only();
   }


#ifdef WINDOWS_DESKTOP


   bool interaction_impl::SetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,bool bRedraw)

   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(pScrollInfo);

      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::GetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,UINT nMask)

   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(pScrollInfo);

      UNREFERENCED_PARAMETER(nMask);
      ::exception::throw_interface_only();

      return false;

   }

#endif

   i32 interaction_impl::GetScrollLimit(i32 nBar)
   {
      UNREFERENCED_PARAMETER(nBar);
      ::exception::throw_interface_only();

      return 0;
   }


   void interaction_impl::ScrollWindow(i32 xAmount,i32 yAmount, LPCRECT pcrect, LPCRECT pcrectClip)
   {

      UNREFERENCED_PARAMETER(xAmount);
      UNREFERENCED_PARAMETER(yAmount);
      UNREFERENCED_PARAMETER(pcrect);
      UNREFERENCED_PARAMETER(pcrectClip);

      ::exception::throw_interface_only();

   }


   void interaction_impl::CalcWindowRect(RECT * pClientRect,UINT nAdjustType)
   {

      UNREFERENCED_PARAMETER(pClientRect);
      UNREFERENCED_PARAMETER(nAdjustType);

      ::exception::throw_interface_only();

   }


   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(UINT nID,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lParam);
      ::exception::throw_interface_only();

      return false;

   }

   bool interaction_impl::OnChildNotify(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::ReflectChildNotify(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

      ::exception::throw_interface_only();

      return false;

   }


//   void interaction_impl::OnParentNotify(UINT message,LPARAM lParam)
//   {
//      UNREFERENCED_PARAMETER(message);
//      UNREFERENCED_PARAMETER(lParam);
//      ::exception::throw_interface_only();
//   }
//
//   void interaction_impl::OnSetFocus(::user::interaction_impl *)
//   {
//      ::exception::throw_interface_only();
//   }
//
//   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wParam,LPARAM)
//   {
//      UNREFERENCED_PARAMETER(wParam);
//      ::exception::throw_interface_only();
//   }
//
//   void interaction_impl::OnSysColorChange()
//   {
//      ::exception::throw_interface_only();
//   }
//
//   void interaction_impl::OnSettingChange(UINT uFlags,const char * pszSection)

//   {
//      UNREFERENCED_PARAMETER(uFlags);
//      UNREFERENCED_PARAMETER(pszSection);

//      ::exception::throw_interface_only();
//   }
//
//#ifdef WINDOWS
//   void interaction_impl::OnDevModeChange(__in LPTSTR pDeviceName)

//   {
//      UNREFERENCED_PARAMETER(pDeviceName);

//      ::exception::throw_interface_only();
//   }
//
//#ifdef WINDOWS_DESKTOP
//   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
//   {
//      ::exception::throw_interface_only();
//   }
//#endif
//#endif
//
//   LRESULT interaction_impl::OnDisplayChange(WPARAM,LPARAM)
//   {
//      //   ::exception::throw_interface_only();
//
//      return 0;
//
//   }
//
//   LRESULT interaction_impl::OnDragList(WPARAM,LPARAM lParam)
//   {
//      UNREFERENCED_PARAMETER(lParam);
//      ::exception::throw_interface_only();
//   }

   /*   void interaction_impl::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   ::exception::throw_interface_only();
   }

   void interaction_impl::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   ::exception::throw_interface_only();
   }
   */

   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image * pimage)
   {
      UNREFERENCED_PARAMETER(pimage);
      ::exception::throw_interface_only();
   }

   void interaction_impl::_001DeferPaintLayeredWindowBackground(::image * pimage)
   {
      UNREFERENCED_PARAMETER(pimage);
      ::exception::throw_interface_only();
   }

   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      ::exception::throw_interface_only();
   }

   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      ::exception::throw_interface_only();
   }

   //void interaction_impl::OnEnterIdle(UINT /*nWhy*/,::user::interaction_impl * /*pWho*/)
   //{
   //   ::exception::throw_interface_only();
   //}

   //void * interaction_impl::OnCtlColor(::draw2d::graphics *,::user::interaction_impl * pwindow,UINT)
   //{
   //   UNREFERENCED_PARAMETER(pwindow);
   //   ::exception::throw_interface_only();
   //}


   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support

   bool interaction_impl::update_data(bool bSaveAndValidate)
   {

      UNREFERENCED_PARAMETER(bSaveAndValidate);

      ::exception::throw_interface_only();

      return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child interaction_impl)

   void interaction_impl::CenterWindow(::user::interaction * pAlternateOwner)
   {

      UNREFERENCED_PARAMETER(pAlternateOwner);

      ::exception::throw_interface_only();

   }


   bool interaction_impl::CheckAutoCenter()
   {
      ::exception::throw_interface_only();

      return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const char * pszResourceName)

   {
      UNREFERENCED_PARAMETER(pszResourceName);

      ::exception::throw_interface_only();

      return false;

   }

   bool interaction_impl::ExecuteDlgInit(LPVOID pResource)

   {
      UNREFERENCED_PARAMETER(pResource);

      ::exception::throw_interface_only();

      return false;

   }

   void interaction_impl::UpdateDialogControls(channel * pTarget,bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);

      ::exception::throw_interface_only();

   }



   bool interaction_impl::subclass_window(oswindow oswindow)
   {
      UNREFERENCED_PARAMETER(oswindow);
      ::exception::throw_interface_only();

      return false;

   }

   bool interaction_impl::SubclassDlgItem(UINT nID,::user::interaction_impl * pParent)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pParent);
      ::exception::throw_interface_only();

      return false;

   }

   oswindow interaction_impl::unsubclass_window()
   {
      ::exception::throw_interface_only();
      return nullptr;
   }

   //bool interaction_impl::IsChild(::user::interaction * pinteraction) const
   //{
   //   UNREFERENCED_PARAMETER(pinteraction);
   //   ::exception::throw_interface_only();

   //   return false;

   //}


   bool interaction_impl::_is_window() const
   {

      ::exception::throw_interface_only();

      return false;

   }


   id interaction_impl::SetDlgCtrlId(id id)
   {

      UNREFERENCED_PARAMETER(id);

      ::exception::throw_interface_only();

      return ::id();

   }


   id interaction_impl::GetDlgCtrlId() const
   {

      ::exception::throw_interface_only();

      return ::id();

   }


   // void interaction_impl::SetWindowDisplayChanged()
   // {

   //    if (m_puserinteraction->is_this_visible() && m_puserinteraction->window_state3().m_edisplay3 != ::display_iconic)
   //    {

   //       if (m_puserinteraction->GetParent() == nullptr)
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


   //bool interaction_impl::layout().is_iconic()
   //{

   //   //::exception::throw_interface_only();

   //   return false;

   //}


   //bool interaction_impl::IsZoomed()
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //::user::interaction * interaction_impl::get_parent() const
   //{

   //   return nullptr;

   //}


   LONG interaction_impl::get_window_long(i32 nIndex) const
   {

      return (LONG)get_window_long_ptr(nIndex);

   }


   LONG interaction_impl::set_window_long(i32 nIndex,LONG lValue)
   {

      return (LONG)set_window_long_ptr(nIndex, lValue);

   }


   LONG_PTR interaction_impl::get_window_long_ptr(i32 nIndex) const
   {

      return ::user::primitive_impl::get_window_long_ptr(nIndex);

   }


   LONG_PTR interaction_impl::set_window_long_ptr(i32 nIndex,LONG_PTR lValue)
   {

      return ::user::primitive_impl::set_window_long_ptr(nIndex, lValue);

   }


   bool interaction_impl::ReleaseCapture()
   {

      ::release_capture();

      Session.m_puiCapture = nullptr;

      return true;

   }


   ::user::interaction * interaction_impl::GetCapture()
   {

      oswindow oswindow = ::get_capture();

      if (oswindow == nullptr)
      {

         return nullptr;

      }

      ::user::interaction * pinteraction = System.ui_from_handle(oswindow);

      if (pinteraction != nullptr)
      {

         if (Session.m_puiCapture != nullptr)
         {

            return Session.m_puiCapture;

         }
         else
         {

            return pinteraction;

         }

      }

      return nullptr;

   }


   bool interaction_impl::SetCapture(::user::interaction * pinteraction)
   {

      if (pinteraction == nullptr)
      {

         pinteraction = m_puserinteraction;

      }

      if (!_is_window())
      {

         return false;

      }

      oswindow w = ::set_capture(get_handle());

      output_debug_string("\nSet Capture: oswindow=0x" + ::hex::lower_from((iptr) w));

      Session.m_puiCapture = pinteraction;

      return true;

   }


   // interaction_impl
   /* interaction_impl::operator oswindow() const
   { return this == nullptr ? nullptr : get_handle(); }*/
   bool interaction_impl::operator==(const interaction_impl& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      ::exception::throw_interface_only();
      return false;
   }

   bool interaction_impl::operator!=(const interaction_impl& wnd) const
   {
      UNREFERENCED_PARAMETER(wnd);
      ::exception::throw_interface_only();
      return false;
   }


   u32 interaction_impl::GetStyle() const
   {

      return ::user::primitive_impl::GetStyle();

   }


   u32 interaction_impl::GetExStyle() const
   {

      return ::user::primitive_impl::GetExStyle();

   }


   bool interaction_impl::ModifyStyle(u32 dwRemove, u32 dwAdd, UINT nFlags)
   {

      if (!_is_window())
      {

         return false;

      }

      DWORD dw = get_window_long(GWL_STYLE);

      dw &= ~dwRemove;

      dw |= dwAdd;

      set_window_long(GWL_STYLE, dw);

      return false;

   }


   bool interaction_impl::ModifyStyleEx(u32 dwRemove,u32 dwAdd,UINT nFlags)
   {

      if (!_is_window())
      {

         return false;

      }

      DWORD dw = get_window_long(GWL_EXSTYLE);

      dw &= ~dwRemove;

      dw |= dwAdd;

      set_window_long(GWL_EXSTYLE, dw);

      return false;

   }

   void interaction_impl::set_owner(::user::interaction * pOwnerWnd)
   {
      UNREFERENCED_PARAMETER(pOwnerWnd);
      ::exception::throw_interface_only();
   }


   LRESULT interaction_impl::send_message(UINT message, WPARAM wparam, lparam lparam)
   {

      ::pointer < ::message::base > spbase;

      spbase = m_puserinteraction->get_message_base(message, wparam, lparam);

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

         m_puserinteraction->walk_pre_translate_tree(spbase);

         if(spbase->m_bRet)
         {

            return spbase->m_lresult;

         }

      }

      message_handler(spbase);

      return spbase->m_lresult;

   }


#ifdef LINUX

   LRESULT interaction_impl::send_x11_event(void * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
      ::exception::throw_interface_only();

      return 0;

   }

#endif


   bool interaction_impl::post_message(UINT message,WPARAM wParam,lparam lParam)
   {

      if(!m_puserinteraction)
      {

         return false;

      }

      if(!m_puserinteraction->m_pthreadUserInteraction)
      {

         return false;

      }

      return m_puserinteraction->m_pthreadUserInteraction->post_message(m_oswindow,
                                                                        message, wParam, lParam);

   }


   bool interaction_impl::DragDetect(const ::point & point) const
   {
      UNREFERENCED_PARAMETER(point);
      ::exception::throw_interface_only();
      return false;
   }


   void interaction_impl::set_window_text(const char * pszString)

   {

      UNREFERENCED_PARAMETER(pszString);


      ::exception::throw_interface_only();

   }

   strsize interaction_impl::GetWindowText(char * pszString,i32 nMaxCount)

   {
      UNREFERENCED_PARAMETER(pszString);

      UNREFERENCED_PARAMETER(nMaxCount);
      ::exception::throw_interface_only();

      return 0;
   }


   strsize interaction_impl::GetWindowTextLength()
   {

      ::exception::throw_interface_only();
      return 0;

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      UNREFERENCED_PARAMETER(bAccept);

      ::exception::throw_interface_only();

   }


   bool interaction_impl::node_is_iconic()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->layout().sketch().display() == ::display_iconic;

   }


   bool interaction_impl::node_is_zoomed()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->layout().sketch().display() == ::display_zoomed;

   }


   UINT interaction_impl::ArrangeIconicWindows()
   {

      ::exception::throw_interface_only();

      return 0;

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * pwndTo,LPPOINT pPoint,UINT nCount)
   {

      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(pPoint);
      UNREFERENCED_PARAMETER(nCount);

      ::exception::throw_interface_only();

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * pwndTo,RECT * prect)
   {
      UNREFERENCED_PARAMETER(pwndTo);
      UNREFERENCED_PARAMETER(prect);

      ::exception::throw_interface_only();
   }

   void interaction_impl::UpdateWindow()
   {
      ::exception::throw_interface_only();
   }

   void interaction_impl::SetRedraw(bool bRedraw)
   {
      UNREFERENCED_PARAMETER(bRedraw);
      ::exception::throw_interface_only();
   }

   bool interaction_impl::GetUpdateRect(RECT * prect,bool bErase)

   {
      UNREFERENCED_PARAMETER(prect);

      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only();

      return false;
   }

   i32 interaction_impl::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only();

      return 0;
   }


   void interaction_impl::Invalidate(bool bErase)
   {

      UNREFERENCED_PARAMETER(bErase);

      ::exception::throw_interface_only();

   }


   void interaction_impl::InvalidateRect(const ::rect & rect,bool bErase)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(bErase);

      ::exception::throw_interface_only();

   }


   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only();
   }


   void interaction_impl::ValidateRect(const ::rect & rect)
   {

      UNREFERENCED_PARAMETER(rect);

      ::exception::throw_interface_only();

   }


   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {

      UNREFERENCED_PARAMETER(pRgn);

      ::exception::throw_interface_only();

   }


   //bool interaction_impl::_is_window_visible()
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {
      UNREFERENCED_PARAMETER(bShow);
      ::exception::throw_interface_only();
   }


   /*::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip,u32 flags)
   {
      UNREFERENCED_PARAMETER(prgnClip);
      UNREFERENCED_PARAMETER(flags);
      ::exception::throw_interface_only();


      return nullptr;
   }*/

   bool interaction_impl::LockWindowUpdate()
   {

      ::exception::throw_interface_only();

      return false;

   }


   void interaction_impl::UnlockWindowUpdate()
   {

      ::exception::throw_interface_only();

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

      m_puserinteraction->post_message(::message_redraw, 1);

   }


   bool interaction_impl::RedrawWindow(const ::rect & rectUpdate, ::draw2d::region * prgnUpdate, UINT flags)
   {

      m_puserinteraction->set_need_redraw();

      return true;

   }


   bool interaction_impl::EnableScrollBar(i32 nSBFlags,UINT nArrowFlags)
   {

      UNREFERENCED_PARAMETER(nSBFlags);

      UNREFERENCED_PARAMETER(nArrowFlags);

      ::exception::throw_interface_only();

      return false;

   }


   //bool interaction_impl::DrawAnimatedRects(i32 idAni, const LPRECT prcFrom, const ::rect & prcTo)
   //{

   //   UNREFERENCED_PARAMETER(idAni);
   //   UNREFERENCED_PARAMETER(prcFrom);
   //   UNREFERENCED_PARAMETER(prcTo);

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics,const rect & prc,UINT uFlags)
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(prc);
      UNREFERENCED_PARAMETER(uFlags);

      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::is_window_enabled() const
   {

      return m_puserinteraction->m_ewindowflag & window_flag_enable;

   }


   bool interaction_impl::enable_window(bool bEnable)
   {

      m_puserinteraction->m_ewindowflag.set(window_flag_enable, bEnable);

      return true;

   }


   ::user::interaction * interaction_impl::GetActiveWindow()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::SetActiveWindow()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool interaction_impl::SetFocus()
   {

      return false;

   }


   void interaction_impl::CheckDlgButton(i32 nIDButton,UINT nCheck)
   {
      UNREFERENCED_PARAMETER(nIDButton);
      UNREFERENCED_PARAMETER(nCheck);
      ::exception::throw_interface_only();
   }

   void interaction_impl::CheckRadioButton(i32 nIDFirstButton,i32 nIDLastButton,i32 nIDCheckButton)
   {
      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);
      UNREFERENCED_PARAMETER(nIDCheckButton);
      ::exception::throw_interface_only();
   }

   i32 interaction_impl::DlgDirList(LPTSTR pPathSpec,i32 nIDListBox,i32 nIDStaticPath,UINT nFileType)

   {
      UNREFERENCED_PARAMETER(pPathSpec);

      UNREFERENCED_PARAMETER(nIDListBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      ::exception::throw_interface_only();
      return 0;
   }

   i32 interaction_impl::DlgDirListComboBox(LPTSTR pPathSpec,i32 nIDComboBox,i32 nIDStaticPath,UINT nFileType)

   {
      UNREFERENCED_PARAMETER(pPathSpec);

      UNREFERENCED_PARAMETER(nIDComboBox);
      UNREFERENCED_PARAMETER(nIDStaticPath);
      UNREFERENCED_PARAMETER(nFileType);
      ::exception::throw_interface_only();

      return 0;
   }

   bool interaction_impl::DlgDirSelect(LPTSTR pString,i32 nSize,i32 nIDListBox)

   {
      UNREFERENCED_PARAMETER(pString);

      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDListBox);
      ::exception::throw_interface_only();

      return false;
   }

   bool interaction_impl::DlgDirSelectComboBox(LPTSTR pString,i32 nSize,i32 nIDComboBox)

   {
      UNREFERENCED_PARAMETER(pString);

      UNREFERENCED_PARAMETER(nSize);
      UNREFERENCED_PARAMETER(nIDComboBox);
      ::exception::throw_interface_only();

      return false;
   }

   UINT interaction_impl::GetChildByIdInt(i32 nID,bool* pTrans,bool bSigned) const

   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pTrans);

      UNREFERENCED_PARAMETER(bSigned);
      ::exception::throw_interface_only();

      return 0;
   }

   i32 interaction_impl::GetChildByIdText(i32 nID,LPTSTR pStr,i32 nMaxCount) const

   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pStr);

      UNREFERENCED_PARAMETER(nMaxCount);
      ::exception::throw_interface_only();

      return 0;
   }


   ::user::interaction_impl * interaction_impl::GetNextDlgGroupItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   {

      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction_impl * interaction_impl::GetNextDlgTabItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   {

      UNREFERENCED_PARAMETER(pWndCtl);
      UNREFERENCED_PARAMETER(bPrevious);

      ::exception::throw_interface_only();

      return nullptr;

   }


   UINT interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   {
      UNREFERENCED_PARAMETER(nIDButton);
      ::exception::throw_interface_only();

      return 0;
   }

   LPARAM interaction_impl::SendDlgItemMessage(i32 nID,UINT message,WPARAM wParam,LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      ::exception::throw_interface_only();

      return 0;
   }

   void interaction_impl::SetDlgItemInt(i32 nID,UINT nValue,bool bSigned)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(nValue);
      UNREFERENCED_PARAMETER(bSigned);
      ::exception::throw_interface_only();
   }

   void interaction_impl::SetDlgItemText(i32 nID,const char * pszString)

   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pszString);

      ::exception::throw_interface_only();
   }


   i32 interaction_impl::ScrollWindowEx(i32 dx,i32 dy,
                                        LPCRECT prectScroll,
                                          LPCRECT prectClip,
                                        ::draw2d::region* prgnUpdate,RECT * pRectUpdate,UINT flags)
   {

      UNREFERENCED_PARAMETER(dx);
      UNREFERENCED_PARAMETER(dy);
      UNREFERENCED_PARAMETER(prectScroll);
      UNREFERENCED_PARAMETER(prectClip);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(pRectUpdate);
      UNREFERENCED_PARAMETER(flags);

      ::exception::throw_interface_only();

      return 0;

   }


   void interaction_impl::ShowScrollBar(UINT nBar,bool bShow)
   {

      UNREFERENCED_PARAMETER(nBar);
      UNREFERENCED_PARAMETER(bShow);

      ::exception::throw_interface_only();

   }


   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point & point)
   {
      UNREFERENCED_PARAMETER(point);
      ::exception::throw_interface_only();

      return nullptr;

   }

   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point & point,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::get_next_window(UINT nFlag)
   {

      UNREFERENCED_PARAMETER(nFlag);

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::GetTopWindow()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::GetLastActivePopup()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool interaction_impl::FlashWindow(bool bInvert)
   {

      UNREFERENCED_PARAMETER(bInvert);

      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::ChangeClipboardChain(oswindow oswindow_Next)
   {

      UNREFERENCED_PARAMETER(oswindow_Next);

      ::exception::throw_interface_only();

      return false;

   }


   oswindow interaction_impl::SetClipboardViewer()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool interaction_impl::OpenClipboard()
   {

      ::exception::throw_interface_only();

      return false;

   }


   void interaction_impl::user_interaction_on_hide()
   {

      decltype(m_guieptraMouseHover) uiptra;

      {

         auto psync = mutex();

         sync_lock sl(mutex());

         uiptra = m_guieptraMouseHover;

         m_guieptraMouseHover.remove_all();

      }

      for(auto & pinteraction : uiptra)
      {

         pinteraction->send_message(WM_MOUSELEAVE);

      }

   }


   void interaction_impl::HideCaret()
   {

      ::exception::throw_interface_only();

   }


   void interaction_impl::ShowCaret()
   {

      ::exception::throw_interface_only();

   }


   bool interaction_impl::SetForegroundWindow()
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::SendNotifyMessage(UINT message,WPARAM wParam,lparam lParam)

   {

      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);

      ::exception::throw_interface_only();

      return false;

   }


   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);

      ::exception::throw_interface_only();

   }


   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);

      ::exception::throw_interface_only();

   }


   bool interaction_impl::SetWindowContextHelpId(u32 dwContextHelpId)
   {

      UNREFERENCED_PARAMETER(dwContextHelpId);

      ::exception::throw_interface_only();

      return false;

   }


   u32 interaction_impl::GetWindowContextHelpId() const
   {

      ::exception::throw_interface_only();

      return -1;

   }


   void interaction_impl::_001OnCreate(::message::message * pmessage)
   {

      if (::is_set(m_pprodevian))
      {

         m_pprodevian->set_config_fps(get_config_fps());

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

      m_puiThis = m_puserinteraction;


   }


   void interaction_impl::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if (pshowwindow->m_bShow)
      {

         INFO("user::interaction_impl::_001OnShowWindow bShow = true");

         if (m_puserinteraction->layout().design().display() != ::display_iconic)
         {

            if (m_puserinteraction->GetParent() == nullptr)
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

         {

            decltype(m_guieptraMouseHover) uiptra;

            {

               sync_lock sl(mutex());

               uiptra = m_guieptraMouseHover;

               m_guieptraMouseHover.remove_all();

            }

            for (auto & pinteraction : uiptra)
            {

               try
               {

                  pinteraction->send_message(WM_MOUSELEAVE);

               }
               catch (...)
               {

               }


            }

         }

         {

            ::user::interaction_pointer_array uia;

            {

               sync_lock sl(mutex());

               if(!m_puserinteraction)
               {

                  return;

               }

               uia = m_puserinteraction->m_uiptraChild;

            }

            for (auto & pinteraction : uia.ptra())
            {

               try
               {

                  pinteraction->send_message(WM_SHOWWINDOW, 0, SW_PARENTCLOSING);

               }
               catch (...)
               {

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

      ::exception::throw_interface_only();

   }


#endif


   void interaction_impl::BeginModalState()
   {

      ::exception::throw_interface_only();

   }


   void interaction_impl::EndModalState()
   {

      ::exception::throw_interface_only();

   }


   void interaction_impl::CloseWindow()
   {

      ::exception::throw_interface_only();

   }


   bool interaction_impl::OpenIcon()
   {

      ::exception::throw_interface_only();

      return false;

   }


   i32 interaction_impl::GetCheckedRadioButton(i32 nIDFirstButton,i32 nIDLastButton)
   {

      UNREFERENCED_PARAMETER(nIDFirstButton);
      UNREFERENCED_PARAMETER(nIDLastButton);

      ::exception::throw_interface_only();

      return 0;

   }


   bool interaction_impl::_EnableToolTips(bool bEnable,UINT nFlag)
   {

      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);

      ::exception::throw_interface_only();

      return false;

   }


   void interaction_impl::_001BaseWndInterfaceMap()
   {

      System.window_map().set(get_handle(), this);

   }


   interaction_impl * interaction_impl::get_impl() const
   {

      return (::user::interaction_impl *) this;

   }





   void interaction_impl::_001UpdateBuffer()
   {

      if (!m_puserinteraction)
      {

         return;

      }

      ::rect rectWindow;

      m_puserinteraction->get_window_rect(rectWindow);

      windowing_output_debug_string("\n_001UpdateBuffer : after get_window_rect");

      string strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("combo_list"))
      {

         output_debug_string("combo_list");

      }

      {

         ::size sizeDrawn;

         sync_lock slGraphics(m_pgraphics->mutex());

         ::sync * psync = m_pgraphics->get_draw_lock();

         sync_lock sl(psync);

         ::draw2d::graphics_pointer pgraphics = m_pgraphics->on_begin_draw();

         slGraphics.unlock();

         windowing_output_debug_string("\n_001UpdateBuffer : after on_begin_draw");

         if (pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
         {

#define SEVERITY_HIGH 5

            int iSeverity = SEVERITY_HIGH;

            for(index i = 0; i < iSeverity * 20; i++)
            {

               output_debug_string("m_pgraphics->on_begin_draw FAILED (1)");

            }

            return;

         }

         pgraphics->m_pimageimplDraw2dGraphics->m_rectTag.Null();

         pgraphics->m_puserstyle.release();

         if (pgraphics->m_pimageimplDraw2dGraphics)
         {

            sizeDrawn = pgraphics->m_pimageimplDraw2dGraphics->m_size;

         }

         if(m_puserinteraction)
         {

            auto r = m_puserinteraction->layout().design().screen_rect();

            m_puserinteraction->_001PrintBuffer(pgraphics);

            m_rectUpdateBuffer = r;

            TRACE("PrintBuffer (%d, %d)",  r.right, r.bottom);

            m_pgraphics->m_bNewBuffer = true;

            pgraphics->m_pimageimplDraw2dGraphics->m_rectTag = r;

         }

         if (pgraphics->m_pimageimplDraw2dGraphics)
         {

            m_sizeDrawn = sizeDrawn;

         }

      }

      if(m_pgraphics && m_pprodevian)
      {

         m_pgraphics->on_end_draw();

      }

   }


//void interaction_impl::_defer_start_prodevian()
//{

//   defer_fork("prodevian", [&]() { _thread_prodevian(); });

//}


   void interaction_impl::set_config_fps(double dConfigFps)
   {

      m_dConfigFps = dConfigFps;

      if (::is_set(m_pprodevian))
      {

         if (::is_set(m_puserinteraction) && m_puserinteraction->is_graphical())
         {

            m_pprodevian->set_config_fps(dConfigFps);

         }

      }

   }


   double interaction_impl::get_config_fps()
   {

      return m_dConfigFps;

   }


   double interaction_impl::get_output_fps()
   {

      return m_dOutputFps;

   }


   //void interaction_impl::prodevian_update_visual(bool & bUpdateBuffer, bool & bUpdateWindow)
   //{

   //}


   bool interaction_impl::start_window_visual()
   {

      if (m_puserthread)
      {

         m_puserthread->start_window_visual();

      }
      else
      {

         m_puserinteraction->post_message(message_apply_visual);

      }

      return true;

   }


   void interaction_impl::_001UpdateWindow()
   {

   }


   void interaction_impl::_001UpdateScreen()
   {

      sync_lock sl(mutex());

      if (!m_puserinteraction)
      {

         return;

      }

      if (m_pgraphics.is_set() && m_puserinteraction->layout().is_this_screen_visible())
      {

         CINFO(prodevian)("going to update_window (1)");

         m_pgraphics->update_window();

         m_puserinteraction->layout().output() = m_puserinteraction->layout().design();

      }

   }


   ::estatus interaction_impl::update_graphics_resources()
   {

      single_lock sl(mutex());

      if (m_pgraphics.is_null())
      {

         auto estatus = __raw_compose(m_pgraphics);

         if (!estatus)
         {

            return estatus;

         }

         if (m_pgraphics)
         {

            m_pgraphics->initialize_graphics_graphics(this);

         }

      }

      return m_pgraphics.is_set() ? ::success : ::error_failed;

   }


   guie_message_wnd::guie_message_wnd(::object * pobject):
      ::object(pobject)
   {

      m_puiForward = nullptr;

   }


   void guie_message_wnd::message_handler(::message::base * pbase)
   {

      if(m_puiForward != nullptr)
      {

         return m_puiForward->message_handler(pbase);

      }

   }


   void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction,const ::rect & rect)
   {

      ASSERT(::is_set(pinteraction));

      __pointer(::user::interaction) puiParent = pinteraction->GetParent();

      ASSERT(puiParent != nullptr);

      ::rect rectOld;

      pinteraction->get_window_rect(rectOld);

      puiParent->_001ScreenToClient(rectOld);

      pinteraction->place(rect);

      pinteraction->display(display_normal, activation_no_activate);

   }


   void interaction_impl::prodevian_redraw(bool bUpdateBuffer)
   {

      if(!m_pprodevian)
      {

         return;

      }

      if (m_puserinteraction->m_ewindowflag & window_flag_embedded_prodevian)
      {

         m_pprodevian->m_message.wParam |= 1;

         m_pprodevian->prodevian_iteration();

      }
      else
      {

         m_pprodevian->post_message(message_redraw, bUpdateBuffer ? 1 : 0);

      }

   }


   void interaction_impl::prodevian_stop()
   {

      auto pprodevian = m_pprodevian;

      if (::is_set(pprodevian))
      {

         {

            sync_lock slGraphics(m_pgraphics->mutex());

            ::sync * psyncDraw = m_pgraphics->get_draw_lock();

            sync_lock slDraw(psyncDraw);

            slGraphics.unlock();

            pprodevian->m_puserinteraction = nullptr;

            pprodevian->m_pimpl = nullptr;

            pprodevian->set_finish();

         }

         {

            sync_lock sl(mutex());

            sync_lock slGraphics(m_pgraphics->mutex());

            __release(m_pprodevian);

         }

      }

   }


   bool interaction_impl::prodevian_update_screen()
   {

      //if (m_bUpdateBufferScreen || m_puserinteraction->layout().is_moving())
      {

         _001UpdateScreen();

      }

      return true;

   }


   void interaction_impl::set_handle(oswindow oswindow)
   {

      if (m_oswindow != nullptr)
      {

         oswindow_remove(m_oswindow);

         oswindow_remove_impl(this);

      }

      m_oswindow = oswindow;

      if (oswindow != nullptr)
      {

         oswindow_assign(oswindow, this);

         _001BaseWndInterfaceMap();

      }

   }


   bool interaction_impl::attach(oswindow oswindowNew)
   {

      ASSERT(get_handle() == nullptr);

      ASSERT(oswindow_interaction(oswindowNew) == nullptr);

      if(oswindowNew == nullptr)
      {

         return false;

      }

      set_handle(oswindowNew);

      ASSERT(System.ui_from_handle(get_handle()) == m_puserinteraction);

      return true;

   }


   void interaction_impl::finalize()
   {

      return ::user::primitive::finalize();

   }


   oswindow interaction_impl::detach()
   {

      oswindow oswindow = get_handle();

      if(oswindow != nullptr)
      {

         set_handle(nullptr);

      }

      return oswindow;

   }


   oswindow interaction_impl::get_handle() const
   {

      return m_oswindow;

   }


   bool interaction_impl::is_composite()
   {

      return (GetExStyle() & WS_EX_LAYERED) != 0;

   }


   ::graphics::graphics * interaction_impl::get_window_graphics()
   {

      return m_pgraphics;

   }


   ::user::primitive * interaction_impl::get_focus_primitive()
   {

      return m_pprimitiveFocus;

   }


   void interaction_impl::_001OnSetFocus(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if (m_bFocus)
      {

         return;

      }

      m_bFocus = true;

      if (m_pprimitiveFocus != nullptr && m_pprimitiveFocus->m_puiThis != m_puserinteraction)
      {

         if(!m_pprimitiveFocus->m_puiThis->m_bFocus)
         {

            m_pprimitiveFocus->m_puiThis->send_message(WM_SETFOCUS);

         }

         m_pprimitiveFocus->set_need_redraw();

      }



      //   if (pprimitiveFocus.is_set())
      //   {

      //      __pointer(::user::interaction) puiFocus = pprimitiveFocus;

      //      if (puiFocus.is_set())
      //      {

      //         puiFocus->keyboard_focus_OnSetFocus();

      //      }

      //      on_keyboard_focus(pprimitiveFocus);

      //   }

      //}


   }


   void interaction_impl::_001OnKillFocus(::message::message * pmessage)
   {

      SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);


      if (!m_bFocus)
      {

         return;

      }

      m_bFocus = false;

      if (pkillfocus->m_oswindowNew != m_oswindow)
      {

         if (m_pprimitiveFocus != nullptr && m_pprimitiveFocus->m_puiThis != m_puserinteraction)
         {

            auto pprimitiveFocus = m_pprimitiveFocus;

            try
            {

               if(pprimitiveFocus->m_puiThis->m_bFocus)
               {

                  pprimitiveFocus->m_puiThis->send_message(WM_KILLFOCUS, pkillfocus->m_wparam, pkillfocus->m_lparam);

               }

            }
            catch (...)
            {

            }

            try
            {

               pprimitiveFocus->set_need_redraw();

            }
            catch (...)
            {

            }


         }

      }


      //if (m_pprimitiveFocus != nullptr)
      //{

      //   ::user::primitive * pprimitiveFocusPrev = m_pprimitiveFocus;

      //   m_pprimitiveFocus = nullptr;

      //   pprimitiveFocusPrev->send_message(WM_KILLFOCUS);

      //   pprimitiveFocusPrev->set_need_redraw();

      //}

   }


   bool interaction_impl::impl_set_focus_primitive(::user::primitive * pprimitiveFocusNew, bool bNotify)
   {

      ::user::primitive * pprimitiveFocusOld = m_pprimitiveFocus;

      if(pprimitiveFocusOld == pprimitiveFocusNew
         && (pprimitiveFocusNew == nullptr
            || pprimitiveFocusNew->m_bFocus))
      {

         return true;

      }

      m_pprimitiveFocus = pprimitiveFocusNew;

      if (bNotify)
      {

         try
         {

            if (::is_set(pprimitiveFocusOld))
            {

               if(pprimitiveFocusOld->m_bFocus)
               {

                  pprimitiveFocusOld->send_message(WM_KILLFOCUS);

               }

               pprimitiveFocusOld->set_need_redraw();

            }

         }
         catch (...)
         {

         }

         try
         {

            if (::is_set(pprimitiveFocusNew))
            {

               pprimitiveFocusNew->send_message(WM_SETFOCUS);

               pprimitiveFocusNew->set_need_redraw();

            }

         }
         catch (...)
         {

         }

      }

      return true;

   }


   bool interaction_impl::set_focus_primitive(::user::primitive * pprimitive)
   {

      if(pprimitive == nullptr)
      {

         bool bXXXNotify = has_focus();

         impl_set_focus_primitive(pprimitive, bXXXNotify);

         return true;

      }

      if(pprimitive == m_puserinteraction || pprimitive == this)
      {

         bool bXXXNotify = has_focus();

         impl_set_focus_primitive(pprimitive, bXXXNotify);

         return true;

      }

      ::user::interaction * pinteraction = pprimitive->get_wnd();

      if (pinteraction == nullptr)
      {

         ASSERT(FALSE);

         return false;

      }

      if(m_puserinteraction->is_ascendant_of(pinteraction, true))
      {

         bool bXXXNotify = has_focus();

         impl_set_focus_primitive(pprimitive, bXXXNotify);

         return true;

      }

      //__throw(invalid_argument_exception("Focus of a window implementation should be set nullptr, to itself or to a descendant window"));

      ASSERT(FALSE);

      return false;

   }


   bool interaction_impl::post(::message::base * pbase)
   {

      if (m_puserthread)
      {

         sync_lock sl(m_puserthread->mutex());

         m_puserthread->m_messagebasea.add(pbase);

         m_puserthread->kick_idle();

         return true;

      }

      m_puserinteraction->post_pred([this, pbase]()
      {

         return m_puserinteraction->message_handler(pbase);

      });

      return true;

   }



   void interaction_impl::redraw_add(::context_object * p)
   {

      sync_lock sl(mutex_redraw());

      m_ptraRedraw.add(p);

   }


   void interaction_impl::redraw_remove(::context_object * p)
   {

      sync_lock sl(mutex_redraw());

      m_ptraRedraw.remove(p);

   }


   bool interaction_impl::has_redraw()
   {

      sync_lock sl(mutex_redraw());

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

         sync_lock sl(mutex());

         if (m_ptraRedraw.has_elements())
         {

            return true;

         }

      }

      return false;

   }


   void interaction_impl::on_after_graphical_update()
   {

      windowing_output_debug_string("\non_after_graphical_update before Session.get_cursor_pos");

      // if(is_set(m_puserinteraction))
      // {

      //    update_session_cursor(this);

      // }

      windowing_output_debug_string("\non_after_graphical_update after Session.get_cursor_pos");

   }




   void interaction_impl::window_show()
   {

      // Request / Incoming changes / Prepare Internal Buffer
      auto & stateOutput = m_puserinteraction->layout().design();

      if (!stateOutput.is_modified())
      {

         return;

      }

      // Current/Previous Window State
      auto & stateWindow = m_puserinteraction->layout().window();

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

         INFO("window_show rectUi isEmpty");

         return;

      }

      bool bWasVisible = ::is_screen_visible(edisplayWindow);

      __keep_flag_on(m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_apply_visual);

      UINT uiFlags = 0;

      bool bLayered = GetExStyle() & WS_EX_LAYERED;

      //if (bLayered)
      {

         uiFlags |= SWP_ASYNCWINDOWPOS | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;

      }
      //else
      //{

      //   uiFlags |= SWP_ASYNCWINDOWPOS  | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;

      //}

      if (eactivationOutput & activation_no_activate)
      {

         uiFlags |= SWP_NOACTIVATE;

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

         uiFlags |= SWP_NOSIZE;

      }
      else
      {

         uiFlags |= SWP_ASYNCWINDOWPOS | SWP_FRAMECHANGED | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;

      }

      bool bMove = true;

      if (pointWindow == pointOutput)
      {

         bMove = false;

         uiFlags |= SWP_NOMOVE;

      }

//#endif

      bool bVisibilityChange = is_different(bWasVisible, shouldGetVisible);

      if (bVisibilityChange)
      {

         if (shouldGetVisible)
         {

            uiFlags |= SWP_SHOWWINDOW;

         }
         else
         {

            uiFlags |= SWP_HIDEWINDOW;

         }

      }

      bool bZ = zOutput.is_change_request();

      if (!bZ)
      {

         uiFlags |= SWP_NOZORDER;

      }

      string strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("font_format"))
      {

         INFO("font_format going to gather Z-Ordering information");

      }

      if(!m_puserinteraction)
      {

         return;

      }

      oswindow oswindowInsertAfter = (bZ ? zOutput.get_os_data() : 0);

      if (edisplayWindow == display_zoomed)
      {

         if (edisplayOutput != display_zoomed)
         {

            _001OnExitZoomed();

         }

      }

      if (shouldGetVisible
#ifdef WINDOWS_DESKTOP
      && !bLayered
#endif
         && (
            //#ifdef WINDOWS_DESKTOP
            //               !bLayered
            //#else
                           //(uiFlags & (SWP_NOMOVE | SWP_NOSIZE)) != (SWP_NOMOVE | SWP_NOSIZE)
            //#endif
            bMove
            || bSize
            || bVisibilityChange
            || bZ
            )
         )
      {

         string strType = ::str::demangle(m_puserinteraction->type_name());

         if (strType.contains("font_format"))
         {

            INFO("font_format going to SetWindowPos");

         }
         else if (strType.contains("textformat"))
         {

            INFO("text_format going to SetWindowPos");

         }

         // Commented on Windows
         //if(m_puserinteraction->m_ewindowflag & window_flag_postpone_visual_update)
         //{

         //   m_bEatMoveEvent = !(uiFlags & SWP_NOMOVE) || !(uiFlags & SWP_NOSIZE);

         //   m_bEatSizeEvent = !(uiFlags & SWP_NOSIZE);

         //}

         //if(m_puserinteraction->m_ewindowflag & window_flag_postpone_visual_update)
         //{

         //   m_bPendingRedraw = true;

         //}
         // END Commented on Windows

         ::point pointBottomRight = pointOutput + sizeOutput;

         output_debug_string("SetWindowPos bottom_right " + __str(pointBottomRight.x) + ", " + __str(pointBottomRight.y) + "\n");

         ::SetWindowPos(m_oswindow, oswindowInsertAfter,
            pointOutput.x, pointOutput.y,
            sizeOutput.cx, sizeOutput.cy,
            uiFlags);

         if (g_pointLastBottomRight != pointBottomRight)
         {

            TRACE("Different Bottom Right");

            g_pointLastBottomRight = pointBottomRight;

         }

         zOutput.clear_request();

         m_bOkToUpdateScreen = true;

      }

      if (edisplayOutput != edisplayWindow)
      {

#ifdef WINDOWS

         bool bShowOutput = windows_show_window(edisplayOutput, eactivationOutput);

         bool bShowWindow = windows_show_window(edisplayWindow, eactivationWindow);

         if (is_different(bShowOutput, bShowWindow))
#endif
         {

            m_puserinteraction->window_show_change_visibility();

         }

      }

      if (eactivationOutput & activation_set_foreground)
      {

         m_puserinteraction->SetForegroundWindow();

      }

      if (eactivationOutput & activation_set_active)
      {

         m_puserinteraction->SetActiveWindow();

      }

      if(!m_puserinteraction)
      {

         return;

      }

      m_puserinteraction->layout().window() = m_puserinteraction->layout().output();

      m_puserinteraction->layout().output().clear_ephemeral();

      oswindow oswindowFocus = nullptr;

      oswindow oswindowImpl = nullptr;

      ::user::interaction_impl* pimplFocus = nullptr;

      if (has_pending_focus() && m_puserinteraction != nullptr && m_puserinteraction->is_window_visible())
      {

         Session.m_pimplPendingFocus2 = nullptr;

         oswindowFocus = ::get_focus();

         oswindowImpl = m_oswindow;

         pimplFocus = oswindow_interaction_impl(oswindowFocus);

         if (oswindowFocus == oswindowImpl)
         {

            output_debug_string("optimized out a SetFocus");

         }
         else
         {

            ::set_focus(m_oswindow);

         }

      }

      m_puserinteraction->visual_changed();

      m_puserinteraction->check_transparent_mouse_events();

      //m_puserinteraction->m_bReposition = false;

   }


   void interaction_impl::on_visual_applied()
   {

   }


   bool interaction_impl::ShowWindow(int iShow)
   {

      return false;


   }


   void interaction_impl::window_show_change_visibility(::edisplay edisplay, ::eactivation eactivation)
   {

      __keep_flag_on(m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_show_window);

      if (edisplay == display_iconic)
      {

         if (eactivation == activation_no_activate)
         {

            ::show_window(m_oswindow, SW_SHOWMINNOACTIVE);

         }
         else
         {

            ::show_window(m_oswindow, SW_MINIMIZE);

         }

      }
      else if (is_visible(edisplay))
      {

         auto iShow = windows_show_window(edisplay, eactivation);

         if (iShow == SW_MAXIMIZE)
         {

            if (GetExStyle() & WS_EX_LAYERED)
            {

               iShow = SW_NORMAL;

            }

         }

         ::show_window(m_oswindow, iShow);

      }
      else
      {

         ::show_window(m_oswindow, SW_HIDE);

      }

      if(m_puserinteraction)
      {

         m_puserinteraction->layout().design() = activation_none;

      }

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

      string strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains_ci("filemanager"))
      {

         INFO("filemanager apply visual");

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


   void interaction_impl::_001OnMove(::message::message * pmessage)
   {

      if(m_bEatMoveEvent)
      {

         m_bEatMoveEvent = false;

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

      SCAST_PTR(::message::move, pmove, pmessage);

      if(m_puserinteraction->m_ewindowflag & window_flag_postpone_visual_update)
      {

         return;

      }

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
//         m_puserinteraction->layout().sketch().screen_origin() = pmove->m_point;
//
//      }

      if (m_puserinteraction->layout().sketch().origin() != pmove->m_point)
      {

         if (m_puserinteraction->layout().is_moving())
         {

            INFO("\nWindow is Moving :: _001OnMove");

         }

         m_puserinteraction->layout().sketch().origin() = pmove->m_point;

         if (m_puserinteraction->layout().sketch().display() != display_normal)
         {

            m_puserinteraction->display(display_normal);

         }

         m_puserinteraction->set_reposition();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

   }


   void interaction_impl::_001OnSize(::message::message * pmessage)
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

      SCAST_PTR(::message::size, psize, pmessage);

      bool bLayered = m_puserinteraction->GetExStyle() & WS_EX_LAYERED;

#ifndef WINDOWS_DESKTOP

      bLayered = false;

#endif

      if(!bLayered)
      {

         m_puserinteraction->layout().window() = psize->m_size;

      }

      if (m_puserinteraction->layout().sketch().size() != psize->m_size)
      {

         m_puserinteraction->layout().sketch() = psize->m_size;

         if (m_puserinteraction->layout().sketch().display() != display_normal)
         {

            m_puserinteraction->display(display_normal);

         }

         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

   }


   void interaction_impl::_001OnDestroyWindow(::message::message* pmessage)
   {

      if (m_puserinteraction && ::str::demangle(m_puserinteraction->type_name()).contains("notify_icon"))
      {

         INFO("notify_icon");

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

   bool interaction_impl::setWMClass(const char * psz)
   {

    return true;

   }


   void interaction_impl::show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd)
   {

   }


   void interaction_impl::non_top_most_upper_window_rects(::rect_array& recta)
   {

      __throw(interface_only_exception);

      return;

   }


   bool interaction_impl::is_occluded()
   {

      ::rect_array recta;

      non_top_most_upper_window_rects(recta);

      ::rect rect;

      m_puserinteraction->get_window_rect(rect);

      ::rect rTest;

      for (auto & rHigher : recta)
      {

         if (rTest.intersect(rHigher, rect))
         {

            return true;

         }

      }

      return false;

   }


   void interaction_impl::approximate_occlusion_rects(rect_array& raTest)
   {

      raTest.remove_all();

      ::rect_array ra;

      non_top_most_upper_window_rects(ra);

      if (ra.isEmpty())
      {

         return;

      }

      ::rect rect;

      m_puserinteraction->get_window_rect(rect);

      for (auto & rHigher : ra)
      {

         ::rect rTest;

         if (rTest.intersect(rHigher, rect))
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

            int iMinArea = MAX(iArea, jArea);

            if (raTest[i].intersection(raTest[j]).area() == iMinArea)
            {

               if (iArea == iMinArea)
               {

                  raTest.remove_at(i);

               }
               else
               {

                  raTest.remove_at(j);

               }

               goto restartFullIntersectionExclusion;

            }

         }

      }

      // Second Remove Partial Intersections which:
      // Intersection area is less than third the area of the rectangle with bigger area.

   restartPartialIntersectionExclusionEx:

      for (index i = 0; i < raTest.get_count(); i++)
      {

         for (index j = i + 1; j < raTest.get_count(); j++)
         {

            int iArea = raTest[i].area();

            int jArea = raTest[j].area();

            int iMaxArea = MAX(iArea, jArea);

            if (raTest[i].intersection(raTest[j]).area() < iMaxArea / 3)
            {

               if (iArea == iMaxArea)
               {

                  raTest.remove_at(j);

               }
               else
               {

                  raTest.remove_at(i);

               }

               goto restartPartialIntersectionExclusionEx;

            }

         }

      }

   }


   i64 interaction_impl::approximate_occlusion_area()
   {

      rect_array ra;

      approximate_occlusion_rects(ra);

      return ra.total_area();

   }


   i64 interaction_impl::opaque_area(LPCRECT lpcrect)
   {

      sync_lock sl(m_pgraphics->get_screen_sync());

      color colorTransparent(0);

      ::rect rect(lpcrect);

      m_puserinteraction->ScreenToClient(rect);

      return rect.area() - m_pgraphics->get_screen_image()->get_rgba_area(colorTransparent, rect);

   }


   i64 interaction_impl::_001GetRectTopLeftWeightedArea(LPCRECT lpcrect)
   {

      ::rect rect(lpcrect);

      m_puserinteraction->ScreenToClient(rect);

      return m_pgraphics->_001GetTopLeftWeightedOpaqueArea(rect);

   }


   i64 interaction_impl::opaque_area()
   {

      color colorTransparent(0);

      ::rect rect;

      m_puserinteraction->get_window_rect(rect);

      return rect.area() - m_pgraphics->get_screen_image()->get_rgba_area(colorTransparent);

   }


   i64 interaction_impl::_001GetTopLeftWeightedArea()
   {

      color colorTransparent(0);

      ::rect rect;

      m_puserinteraction->get_window_rect(rect);

      return m_pgraphics->get_screen_image()->_001GetTopLeftWeightedOpaqueArea(colorTransparent);

   }


   i64 interaction_impl::approximate_occlusion_area_except_self_transparent()
   {

      rect_array ra;

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

      rect_array ra;

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


   bool interaction_impl::is_this_visible(e_layout elayout)
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      if (!(m_puserinteraction->m_ewindowflag & window_flag_is_window))
      {

         return false;

      }

      if (!m_puserinteraction->layout().state(elayout).is_visible())
      {

         return false;

      }

      return true;

   }


} // namespace user



