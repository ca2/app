#include "framework.h"
#include "aura/user/_user.h"
//#include "acme/os/cross.h"
#include "aura/platform/message_queue.h"
#include "aura/message.h"
#include "interaction_thread.h"
#include "interaction_prodevian.h"
#include "aura/node/_node.h"
#include "acme/os/_user.h"
#ifdef _UWP
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#endif

point_i32 g_pointLastBottomRight;

#undef ALOG_CONTEXT
#define ALOG_CONTEXT (::trace_object(::trace_category_windowing))


#ifdef WINDOWS_DESKTOP
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#endif


#define REDRAW_HINTING
//CLASS_DECL_AURA bool task_set_name(const char *psz);

#define IMAGE_OK(pimpl) (::is_set(pimpl) && pimpl->area() > 0)
//void windowing_output_debug_string(const char * pszDebugString);

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

#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)

      set_config_fps(20.0);

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

      if (m_bCursorRedraw)
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pointCursor = pwindowing->get_cursor_position();

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


   void interaction_impl::set_destroying()
   {

      m_bDestroying = true;

   }


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


   bool interaction_impl::create_message_queue(::user::interaction * pinteraction, const char * lpszName)
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

         if(!create_host(pinteraction))
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

//#ifdef WINDOWS_DESKTOP
//
//
//   bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
//   {
//      UNREFERENCED_PARAMETER(pwi);
//      ::exception::throw_interface_only();
//      return false;
//   }
//
//   bool interaction_impl::GetScrollBarInfo(::i32 idObject,PSCROLLBARINFO psbi) const
//   {
//      UNREFERENCED_PARAMETER(idObject);
//      UNREFERENCED_PARAMETER(psbi);
//      ::exception::throw_interface_only();
//      return false;
//   }
//
//   bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
//   {
//      UNREFERENCED_PARAMETER(pti);
//      ::exception::throw_interface_only();
//      return false;
//   }
//
//#endif

#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)


   ::user::interaction_impl * interaction_impl::GetAncestor(::u32 gaFlags) const
   {

      UNREFERENCED_PARAMETER(gaFlags);

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool interaction_impl::AnimateWindow(millis millis,u32 dwFlags)
   {
      UNREFERENCED_PARAMETER(millis);
      UNREFERENCED_PARAMETER(dwFlags);
      ::exception::throw_interface_only();
      return false;
   }

   bool interaction_impl::FlashWindowEx(u32 dwFlags,::u32 uCount,millis tickTimeout)
   {
      UNREFERENCED_PARAMETER(dwFlags);
      UNREFERENCED_PARAMETER(uCount);
      UNREFERENCED_PARAMETER(tickTimeout);
      ::exception::throw_interface_only();
      return false;
   }

   //bool interaction_impl::SetLayeredWindowAttributes(::color::color crKey,byte bAlpha,u32 dwFlags)
   //{
   //   UNREFERENCED_PARAMETER(crKey);
   //   UNREFERENCED_PARAMETER(bAlpha);
   //   UNREFERENCED_PARAMETER(dwFlags);
   //   ::exception::throw_interface_only();
   //   return false;
   //}

   //bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT_I32 * pptDst,SIZE_I32 * psize,
   //      ::draw2d::graphics * pDCSrc,POINT_I32 * pptSrc,::color::color crKey,BLENDFUNCTION * pblend,u32 dwFlags)
   //{
   //   UNREFERENCED_PARAMETER(pDCDst);
   //   UNREFERENCED_PARAMETER(pptDst);
   //   UNREFERENCED_PARAMETER(psize);
   //   UNREFERENCED_PARAMETER(pDCSrc);
   //   UNREFERENCED_PARAMETER(pptSrc);
   //   UNREFERENCED_PARAMETER(crKey);
   //   UNREFERENCED_PARAMETER(pblend);
   //   UNREFERENCED_PARAMETER(dwFlags);
   //   ::exception::throw_interface_only();

   //   return false;
   //}

   bool interaction_impl::GetLayeredWindowAttributes(::color::color * pcrKey,byte * pbAlpha,u32 * pdwFlags) const
   {
      UNREFERENCED_PARAMETER(pcrKey);
      UNREFERENCED_PARAMETER(pbAlpha);
      UNREFERENCED_PARAMETER(pdwFlags);
      ::exception::throw_interface_only();

      return false;
   }

   bool interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics,::u32 nFlags) const
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nFlags);
      ::exception::throw_interface_only();

      return false;
   }

#endif


   //lresult interaction_impl::default_window_procedure()
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


   //bool interaction_impl::create_host(::user::interaction * pinteraction, ::user::primitive * pprimitiveParent)
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

   //   //   if (!native_create_window_ex(pinteraction, pusersystem, puiParent->get_safe_handle(), id))
   //   //   {

   //   //      return false;

   //   //   }

   //   //}

   //   return true;

   //}


   // for child windows
   bool interaction_impl::pre_create_window(::user::system * pusersystem)
   {

      UNREFERENCED_PARAMETER(pusersystem);

      return true;

   }

   
   ::e_status interaction_impl::native_create_host()
   {

      auto estatus = __construct(m_pwindow);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pwindow->create_window(this);

      if (!estatus)
      {

         return estatus;

      }

      return true;

   }


   bool interaction_impl::create_host(::user::interaction * puserinteraction)
   {

      m_puserinteraction = puserinteraction;

      m_puserinteraction->m_pimpl = this;

      m_puserinteraction->m_pimpl2 = this;

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

      auto psynca = __new(synchronization_array);

      __pointer(manual_reset_event) peventStartedUser;

      __pointer(manual_reset_event) peventStartedProdevian;

      if (bNewOwnThread)
      {

         __raw_compose_new(m_puserthread);

         m_puserthread->initialize_user_thread(this);

         m_puserthread->add_child_task(m_puserinteraction);

         m_puserinteraction->__refer(m_puserinteraction->m_pthreadUserInteraction, m_puserthread OBJ_REF_DBG_COMMA_THIS_NOTE(__FUNCTION__));

         peventStartedUser = __new(manual_reset_event());

         m_puserthread->m_peventStarted = peventStartedUser;

      }

      if (bProdevianThread)
      {

         __raw_compose_new(m_pprodevian);

         m_pprodevian->initialize_prodevian(this);

         if (m_puserinteraction->is_graphical())
         {

            m_pprodevian->m_puserthread = m_puserthread;

         }

         if (!(m_puserinteraction->m_ewindowflag & e_window_flag_embedded_prodevian))
         {

            peventStartedProdevian = __new(manual_reset_event());

            m_pprodevian->m_peventStarted = peventStartedProdevian;

            if (!m_pprodevian->branch())
            {

               __release(m_pprodevian);

               __release(m_puserthread);

               m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

               return false;

            }

            psynca->add(peventStartedProdevian);

         }
         else
         {

            m_pprodevian->init_thread();

         }

      }

      if (bNewOwnThread)
      {

         if (!m_puserthread->branch())
         {

            __release(m_pprodevian);

            __release(m_puserthread);

            m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

            return false;

         }

         psynca->add(peventStartedUser);

         auto proutine = __routine([this, psynca]()
            {

               if (!m_puserinteraction ||
                  //(m_puserthread->m_bCreateNativeWindowOnInteractionThread
                     //&&
                  !m_puserinteraction->is_window())
                  //)
               {

                  return;

               }

               if (m_puserthread->m_result.failed())
               {

                  if (m_puserinteraction)
                  {

                     m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

                  }

                  __release(m_pprodevian);

                  __release(m_puserthread);

                  return;

               }

               //peventStartedUser.release();

               if (::is_set(m_pprodevian))
               {

                  if (m_pprodevian->m_result.failed())
                  {

                     if (m_puserinteraction)
                     {

                        m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

                     }

                     __release(m_pprodevian);

                     __release(m_puserthread);

                     return;

                  }

                 // peventStartedProdevian.release();

               }

            });

         //if (pusersystem->m_routineSuccess)
         //{

         //   fork([psynca, proutine, pusersystem]()
         //   {

         //      psynca->wait();

         //      (*proutine)();

         //      pusersystem->m_routineSuccess();

         //   });

         //}
         //else
         //{

            psynca->wait();

         //   (*proutine)();

         //}

      }
      else
      {

         psynca->wait(true, one_minute());

         if (::is_set(m_pprodevian))
         {

            peventStartedProdevian.release();

         }

         if (!native_create_host())
         {

            return false;

         }

      }

      //if (m_puserthread && !m_puserthread->m_bCreateNativeWindowOnInteractionThread)
      //{

      //   send_message(e_message_create, 0, (lparam)&pusersystem);

      //   //m_puserinteraction->set_dim(pusersystem->m_createstruct.x, pusersystem->m_createstruct.cy, pusersystem->m_createstruct.cx, pusersystem->m_createstruct.cy);

      //   send_message(e_message_size, 0, MAKELPARAM(pusersystem->m_createstruct.cx, pusersystem->m_createstruct.cy));

      //   m_puserinteraction->add_ref(OBJ_REF_DBG_THIS_FUNCTION_LINE);

      //   m_puserinteraction->m_ewindowflag |= ::e_window_flag_is_window;

      //   m_puserinteraction->m_ewindowflag |= ::e_window_flag_window_created;

      //}

      return true;

   }


   ::color::color interaction_impl::screen_pixel(int x, int y) const
   {

      auto origin = m_puserinteraction->layout().window().origin();

      return m_pgraphics->get_screen_image()->pixel(x - origin.x, y - origin.y);

   }


   //bool interaction_impl::native_create_window()
   //{
   //   return false;
   //}


//   bool interaction_impl::create_host(::user::interaction * puserinteraction)
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
         MESSAGE_LINK(e_message_kill_focus, pchannel, this, &interaction_impl::_001OnKillFocus);
         MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::_001OnSetFocus);

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

         //::rectangle_i32 rectUi;

         //auto psession = get_session();

         //auto puser = psession->user();

         //auto pwindowing = puser->windowing();

         //auto pointCursor = pwindowing->get_cursor_position();

         //::user::interaction_array uia;

         //{

         //   synchronous_lock synchronouslock(mutex());

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

   //   if (pmouse->m_id == e_message_left_button_up)
   //   {

   //      ::output_debug_string("lbutton_up");

   //   }

   //   if(pmouse->m_id == ::e_message_left_button_down)
   //   {

   //      on_configuration_change(m_puserinteraction);

   //   }

   //   {

   //      ::user::interaction_array uia;

   //      {

   //         synchronous_lock synchronouslock(mutex());

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

   //      if (pmouse->m_id == e_message_left_button_up)
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


   //      if (pmouse->m_id == e_message_left_button_up)
   //      {

   //         ::output_debug_string("lbutton_up");

   //      }

   //      //synchronous_lock synchronouslock(mutex_children());

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


   bool interaction_impl::add_prodevian(::matter * pmatter)
   {

      synchronous_lock synchronouslock(m_puserthread->mutex());

      if(!m_matteraProdevian.add_unique(pmatter))
      {

         return false;

      }

      m_puserinteraction->post_message(e_message_redraw, 1);

      return true;

   }


   bool interaction_impl::erase_prodevian(::matter * pmatter)
   {

      if (!m_puserthread)
      {

         return false;

      }

      synchronous_lock synchronouslock(m_puserthread->mutex());

      bool bRemove = m_matteraProdevian.erase(pmatter) > 0;

      if (bRemove)
      {

         m_puserinteraction->post_message(e_message_redraw, 1);

      }

      return bRemove;

   }


   bool interaction_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      if (pinterface == nullptr)
      {

         return false;

      }

      if (pinterface->m_pimpl->m_bDestroyImplOnly)
      {

         return false;

      }

      bool bWasEmpty = false;
      
      {

         synchronous_lock synchronouslock(mutex());

         bWasEmpty = m_userinteractionaMouseHover.is_empty();

         m_userinteractionaMouseHover.add_unique(pinterface);

      }

      if (bWasEmpty)
      {

         track_mouse_hover();

      }

      return true;

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

      synchronous_lock synchronouslock(mutex());

      for(::index i = 0; i < m_userinteractionaMouseHover.get_count(); )
      {

         auto pinteraction = m_userinteractionaMouseHover[i];

         if(pinteraction == m_puserinteractionCapture)
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
//         synchronous_lock synchronouslock(mutex());
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

      synchronous_lock synchronouslock(mutex());

      return m_userinteractionaMouseHover.erase(pinterface) > 0;

   }


   void interaction_impl::_task_transparent_mouse_event()
   {

      m_pwindow->_task_transparent_mouse_event();

   }


   void interaction_impl::_001OnCaptureChanged(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      m_puserinteractionCapture.release();
      
   }


   bool interaction_impl::__windows_message_bypass(::windowing::window * pwindow, ::u32 message, wparam wparam, lparam lparam, lresult & lresult)
   {

      return false;

   }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {

      last_install_message_routing(pchannel);

      ::user::primitive::install_message_routing(pchannel);

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


   bool interaction_impl::pre_message_handler(::message::key * & pkey, bool & bKeyMessage, ::message::message* pmessage)
   {

      ::u32 message = pmessage->m_id.umessage();

      bKeyMessage = message == e_message_key_down ||
         message == e_message_key_up ||
         message == e_message_char ||
      message == e_message_text_composition
#ifdef WINDOWS_DESKTOP
         || message == e_message_sys_key_down
         || message == e_message_sys_key_up
         || message == e_message_sys_char
         || message == e_message_ime_key_down
         || message == e_message_ime_key_up
         || message == e_message_ime_char
         || message == e_message_ime_select
         || message == e_message_ime_set_context
         || message == e_message_ime_start_composition
         || message == e_message_ime_composition
         || message == e_message_ime_composition_full
         || message == e_message_ime_notify
         || message == e_message_ime_end_composition
         || message == e_message_input_language
#endif
         ;

      if (bKeyMessage)
      {

         pkey = dynamic_cast <::message::key*> (pmessage);

         if (pkey)
         {

            m_pwindowing->set(pkey, pkey->m_oswindow, pkey->m_pwindow, pkey->m_id, pkey->m_wparam, pkey->m_lparam);

         }

         if (message == e_message_key_down || message == e_message_sys_key_down)
         {

            auto psession = get_session();

            try
            {

               psession->set_key_pressed(pkey->m_ekey, true);

            }
            catch (...)
            {
            }
         }
         else if (message == e_message_key_up || message == e_message_sys_key_up)
         {

            auto psession = get_session();

            try
            {

               psession->set_key_pressed(pkey->m_ekey, false);

            }
            catch (...)
            {

            }

         }

      }


      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->pre_translate_message(pmessage);

      }

      if (pmessage->m_bRet)
      {

         return true;

      }

      return false;

   }


   void interaction_impl::default_message_handler(::message::message * pmessage)
   {

      m_pwindow->default_message_handler(pmessage);

   }


   void interaction_impl::on_message_destroy(::message::message * pmessage)
   {

      if (m_puserinteraction && ::str::demangle(m_puserinteraction->type_name()).contains("notify_icon"))
      {

         INFO("notify_icon");

      }

      if (m_pgraphics)
      {

         m_pgraphics->destroy_buffer();

         m_pgraphics->finalize();

      }

      __release(m_pgraphics);

      UNREFERENCED_PARAMETER(pmessage);

      {

         auto psync = mutex();

         synchronous_lock synchronouslock(mutex());

         m_userinteractionaMouseHover.erase_all();

      }

   }



   void interaction_impl::PostNcDestroy()
   {

      string strType = m_puserinteraction->type_name();

//      if (strType.contains("main_frame"))
//      {
//
//         output_debug_string("main_frame");
//
//      }

      ::user::primitive_impl::PostNcDestroy();

      detach();

      m_puserinteraction.release();

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

         m_pprodevian->set_finish();

         if (::is_set(m_puserinteraction))
         {

            INFO(::str::demangle(m_puserinteraction->type_name()) + "::destroy_impl_only");

            m_puserinteraction->transfer_receiver(m_handlermap, this);

         }

         m_puserinteraction->m_pimpl.release();

         m_puserinteraction->m_pimpl2.release();

         m_puserinteraction = nullptr;

         auto pwindow = get_window();

         message_queue_post(pwindow, e_message_destroy_window, 0, 0);

         return true;

      }
      else if(m_bUserPrimitiveOk)
      {

         if (m_puserinteraction)
         {

            INFO(::str::demangle(m_puserinteraction->type_name()) + "::destroy_impl_only ( 2)");

         }

         m_bUserPrimitiveOk = false;

         //return ::DestroyWindow((HWND)get_handle());
         return false;

      }
      else
      {

         return false;

      }

   }


   bool interaction_impl::start_destroying_window()
   {

      if (m_bDestroying)
      {

         return true;

      }

      if (!m_bDestroying)
      {

         if (m_pprodevian && m_pprodevian->task_active())
         {

            m_pprodevian->finish();

         }
         else
         {

            m_bDestroying = true;

            m_puserinteraction->post_message(e_message_destroy_window);

         }

         return true;

      }

      bool bResult = ::user::primitive::start_destroying_window();

      return bResult;

   }


   void interaction_impl::destroy_window()
   {

      auto strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("main_frame"))
      {

         output_debug_string("main_frame user::interaction_impl::destroy_window");

      }

      //::destroy_window(get_handle());

      m_pwindow->destroy_window();

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


   //void interaction_impl::GetWindowText(string & rectString)
   //{

   //   UNREFERENCED_PARAMETER(rectString);

   //   ::exception::throw_interface_only();

   //}


   //i32 interaction_impl::GetChildByIdText(i32 nID,string & rectString) const
   //{

   //   UNREFERENCED_PARAMETER(nID);

   //   UNREFERENCED_PARAMETER(rectString);

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
//
//   {
//
//      UNREFERENCED_PARAMETER(puserinteractionpl);
//
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }
//
//
//   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
//   {
//
//      UNREFERENCED_PARAMETER(puserinteractionpl);
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }
//
//
//#endif


   //void interaction_impl::PrepareForHelp()
   //{

   //   ::exception::throw_interface_only();

   //}


   void interaction_impl::route_command_message(::message::command * pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

      ::exception::throw_interface_only();

   }


   void interaction_impl::_002OnDraw(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::exception::throw_interface_only();

   }


   void interaction_impl::message_handler(::message::message * pmessage)
   {

      if (m_puserinteraction)
      {

         m_bDestroyImplOnly ? route_message(pmessage) : m_puserinteraction.m_p->route_message(pmessage);

      }

   }


   void interaction_impl::default_window_procedure(::message::message * pmessage)
   {

   }


   //bool interaction_impl::OnNotify(::message::message * pmessage)
   //{

   //   UNREFERENCED_PARAMETER(pmessage);

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


   //i32 interaction_impl::message_box(const char * pszText,const char * pszCaption,::u32 nType)

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

   //i32 interaction_impl::SetScrollPos(i32 nBar,i32 nPos,bool bRedraw)
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(nPos);
   //   UNREFERENCED_PARAMETER(bRedraw);
   //   ::exception::throw_interface_only();

   //   return 0;
   //}

   //i32 interaction_impl::GetScrollPos(i32 nBar) const
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   ::exception::throw_interface_only();

   //   return 0;
   //}

   //void interaction_impl::SetScrollRange(i32 nBar,i32 nMinPos,i32 nMaxPos,bool bRedraw)
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(nMinPos);
   //   UNREFERENCED_PARAMETER(nMaxPos);
   //   UNREFERENCED_PARAMETER(bRedraw);
   //   ::exception::throw_interface_only();


   //}


   //void interaction_impl::GetScrollRange(i32 nBar,LPINT pMinPos,LPINT pMaxPos) const

   //{

   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(pMinPos);
   //   UNREFERENCED_PARAMETER(pMaxPos);

   //   ::exception::throw_interface_only();

   //}


   //// Turn on/off non-control scrollbars
   ////   for WS_?SCROLL scrollbars - show/hide them
   ////   for control scrollbar - enable/disable them
   //void interaction_impl::EnableScrollBarCtrl(i32 nBar,bool bEnable)
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(bEnable);
   //   ::exception::throw_interface_only();
   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   bool interaction_impl::SetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,bool bRedraw)
//
//   {
//
//      UNREFERENCED_PARAMETER(nBar);
//      UNREFERENCED_PARAMETER(pScrollInfo);
//
//      UNREFERENCED_PARAMETER(bRedraw);
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }
//
//
//   bool interaction_impl::GetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,::u32 nMask)
//
//   {
//
//      UNREFERENCED_PARAMETER(nBar);
//      UNREFERENCED_PARAMETER(pScrollInfo);
//
//      UNREFERENCED_PARAMETER(nMask);
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }
//
//#endif

   i32 interaction_impl::GetScrollLimit(i32 nBar)
   {
      UNREFERENCED_PARAMETER(nBar);
      ::exception::throw_interface_only();

      return 0;
   }


   //void interaction_impl::ScrollWindow(i32 xAmount,i32 yAmount, const RECTANGLE_I32 * pcrect, const RECTANGLE_I32 * pcrectClip)
   //{

   //   UNREFERENCED_PARAMETER(xAmount);
   //   UNREFERENCED_PARAMETER(yAmount);
   //   UNREFERENCED_PARAMETER(pcrect);
   //   UNREFERENCED_PARAMETER(pcrectClip);

   //   ::exception::throw_interface_only();

   //}


   //void interaction_impl::CalcWindowRect(RECTANGLE_I32 * pClientRect,::u32 nAdjustType)
   //{

   //   UNREFERENCED_PARAMETER(pClientRect);
   //   UNREFERENCED_PARAMETER(nAdjustType);

   //   ::exception::throw_interface_only();

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(::u32 nID,lparam lParam)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lParam);
      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::OnChildNotify(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::exception::throw_interface_only();

      return false;

   }


   bool interaction_impl::ReflectChildNotify(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::exception::throw_interface_only();

      return false;

   }


//   void interaction_impl::OnParentNotify(const ::id & id,lparam lParam)
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
//   lresult interaction_impl::OnActivateTopLevel(wparam wParam,lparam)
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
//   void interaction_impl::OnSettingChange(::u32 uFlags,const char * pszSection)

//   {
//      UNREFERENCED_PARAMETER(uFlags);
//      UNREFERENCED_PARAMETER(pszSection);

//      ::exception::throw_interface_only();
//   }
//
//#ifdef WINDOWS
//   void interaction_impl::OnDevModeChange(__in char * pDeviceName)

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
//   lresult interaction_impl::OnDisplayChange(wparam,lparam)
//   {
//      //   ::exception::throw_interface_only();
//
//      return 0;
//
//   }
//
//   lresult interaction_impl::OnDragList(wparam,lparam lParam)
//   {
//      UNREFERENCED_PARAMETER(lParam);
//      ::exception::throw_interface_only();
//   }

   /*   void interaction_impl::OnHScroll(::u32, ::u32, CScrollBar* pScrollBar)
   {
   UNREFERENCED_PARAMETER(pScrollBar);
   ::exception::throw_interface_only();
   }

   void interaction_impl::OnVScroll(::u32, ::u32, CScrollBar* pScrollBar)
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

   //void interaction_impl::OnEnterIdle(::u32 /*nWhy*/,::user::interaction_impl * /*pWho*/)
   //{
   //   ::exception::throw_interface_only();
   //}

   //void * interaction_impl::OnCtlColor(::draw2d::graphics *,::user::interaction_impl * pwindow,::u32)
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

//   /////////////////////////////////////////////////////////////////////////////
//   // Dialog initialization support
//
//   bool interaction_impl::ExecuteDlgInit(const char * pszResourceName)
//
//   {
//      UNREFERENCED_PARAMETER(pszResourceName);
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }

//   bool interaction_impl::ExecuteDlgInit(LPVOID pResource)
//
//   {
//      UNREFERENCED_PARAMETER(pResource);
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }

   void interaction_impl::UpdateDialogControls(channel * pTarget,bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);

      ::exception::throw_interface_only();

   }



   //bool interaction_impl::subclass_window(::windowing::window * pwindow)
   //{
   //   UNREFERENCED_PARAMETER(oswindow);
   //   ::exception::throw_interface_only();

   //   return false;

   //}

   //bool interaction_impl::SubclassDlgItem(::u32 nID,::user::interaction_impl * pParent)
   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pParent);
   //   ::exception::throw_interface_only();

   //   return false;

   //}

   //oswindow interaction_impl::unsubclass_window()
   //{
   //   ::exception::throw_interface_only();
   //   return nullptr;
   //}

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


   //id interaction_impl::SetDlgCtrlId(id id)
   //{

   //   UNREFERENCED_PARAMETER(id);

   //   ::exception::throw_interface_only();

   //   return ::id();

   //}


   //id interaction_impl::GetDlgCtrlId() const
   //{

   //   ::exception::throw_interface_only();

   //   return ::id();

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


   //bool interaction_impl::ReleaseCapture()
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


   //bool interaction_impl::SetCapture(::user::interaction * pinteraction)
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


   //u32 interaction_impl::GetStyle() const
   //{

   //   return ::user::primitive_impl::GetStyle();

   //}


   //u32 interaction_impl::GetExStyle() const
   //{

   //   return ::user::primitive_impl::GetExStyle();

   //}


   //bool interaction_impl::ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
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


   //bool interaction_impl::ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags)
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

      UNREFERENCED_PARAMETER(pprimitiveOwner);

      //::exception::throw_interface_only();

      return nullptr;

   }


   lresult interaction_impl::send_message(const ::id & id, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      auto pmessage = m_puserinteraction->get_message(id, wparam, lparam, point);

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
//      UNREFERENCED_PARAMETER(pevent);
//
//      ::exception::throw_interface_only();
//
//      return 0;
//
//   }
//
//
//#endif


   bool interaction_impl::post_message(const ::id & id,wparam wParam,lparam lParam)
   {

      if(!m_puserinteraction)
      {

         return false;

      }

      if(!m_puserinteraction->m_pthreadUserInteraction)
      {

         return false;

      }

      auto pwindow = m_pwindow;

      if(!pwindow)
      {

         return false;

      }

      auto oswindow = pwindow->get_oswindow();

      if(!oswindow)
      {

         return false;

      }

      MESSAGE message = {};

      message.oswindow = oswindow;

      message.m_id = id;

      message.wParam = wParam;

      message.lParam = lParam;

      auto puserinteraction = m_puserinteraction;

      auto pthread = puserinteraction->m_pthreadUserInteraction;

      auto pmessagequeue = pthread->get_message_queue();

      auto estatus = pmessagequeue->post_message(message);

      return estatus;

   }


   bool interaction_impl::DragDetect(const ::point_i32 & point) const
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

   
   //strsize interaction_impl::GetWindowText(char * pszString,i32 nMaxCount)
   //{

   //   UNREFERENCED_PARAMETER(pszString);
   //   UNREFERENCED_PARAMETER(nMaxCount);
   //   ::exception::throw_interface_only();

   //   return 0;
   //}


   //strsize interaction_impl::GetWindowTextLength()
   //{

   //   ::exception::throw_interface_only();
   //   return 0;

   //}


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      UNREFERENCED_PARAMETER(bAccept);

      ::exception::throw_interface_only();

   }


   bool interaction_impl::window_is_iconic()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->layout().sketch().display() == ::e_display_iconic;

   }


   bool interaction_impl::window_is_zoomed()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->layout().sketch().display() == ::e_display_zoomed;

   }


   ::u32 interaction_impl::ArrangeIconicWindows()
   {

      ::exception::throw_interface_only();

      return 0;

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * puserinteractionTo,POINT_I32 * pPoint,::u32 nCount)
   {

      UNREFERENCED_PARAMETER(puserinteractionTo);
      UNREFERENCED_PARAMETER(pPoint);
      UNREFERENCED_PARAMETER(nCount);

      ::exception::throw_interface_only();

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * puserinteractionTo,RECTANGLE_I32 * prectangle)
   {
      UNREFERENCED_PARAMETER(puserinteractionTo);
      UNREFERENCED_PARAMETER(prectangle);

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

   bool interaction_impl::GetUpdateRect(RECTANGLE_I32 * prectangle,bool bErase)

   {
      UNREFERENCED_PARAMETER(prectangle);

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


   void interaction_impl::InvalidateRect(const ::rectangle_i32 & rectangle,bool bErase)
   {

      UNREFERENCED_PARAMETER(rectangle);
      UNREFERENCED_PARAMETER(bErase);

      ::exception::throw_interface_only();

   }


   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(bErase);
      ::exception::throw_interface_only();
   }


   void interaction_impl::ValidateRect(const ::rectangle_i32 & rectangle)
   {

      UNREFERENCED_PARAMETER(rectangle);

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

      m_puserinteraction->post_message(::e_message_redraw, 1);

   }


   bool interaction_impl::RedrawWindow(const ::rectangle_i32 & rectUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      m_puserinteraction->set_need_redraw();

      return true;

   }


   bool interaction_impl::EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags)
   {

      UNREFERENCED_PARAMETER(nSBFlags);

      UNREFERENCED_PARAMETER(nArrowFlags);

      ::exception::throw_interface_only();

      return false;

   }


   //::point_i32 interaction_impl::get_cursor_position() const
   //{

   //   auto psession = get_session();

   //   if (!psession)
   //   {

   //      return ::point_i32();

   //   }

   //   return psession->get_cursor_position();

   //}


   ::e_status interaction_impl::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      if (::is_null(m_pwindow))
      {

         return ::error_failed;

      }

      auto estatus = m_pwindow->set_mouse_cursor(pcursor);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::windowing::window * interaction_impl::get_window() const
   {

      return m_pwindow;

   }


   //::e_status interaction_impl::set_mouse_cursor(enum_cursor ecursor)
   //{

   //   auto psession = get_session();

   //   auto puser = psession->user();

   //   auto pwindowing = puser->windowing();

   //   auto pcursor = pwindowing->get_cursor(ecursor);

   //   auto pwindow = get_window();

   //   auto estatus = pwindow->set_cursor(pcursor);

   //   return estatus;

   //}


   bool interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics,const rectangle_i32 & prc,::u32 uFlags)
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(prc);
      UNREFERENCED_PARAMETER(uFlags);

      ::exception::throw_interface_only();

      return false;

   }


   //bool interaction_impl::is_window_enabled() const
   //{

   //   return m_puserinteraction->m_ewindowflag & e_window_flag_enable;

   //}


   bool interaction_impl::enable_window(bool bEnable)
   {

      m_puserinteraction->m_ewindowflag.set(e_window_flag_enable, bEnable);

      return true;

   }


   //::user::interaction * interaction_impl::GetActiveWindow()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_impl::SetActiveWindow()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //bool interaction_impl::SetFocus()
   //{

   //   return false;

   //}


   //void interaction_impl::CheckDlgButton(i32 nIDButton,::u32 nCheck)
   //{
   //   UNREFERENCED_PARAMETER(nIDButton);
   //   UNREFERENCED_PARAMETER(nCheck);
   //   ::exception::throw_interface_only();
   //}

   //void interaction_impl::CheckRadioButton(i32 nIDFirstButton,i32 nIDLastButton,i32 nIDCheckButton)
   //{
   //   UNREFERENCED_PARAMETER(nIDFirstButton);
   //   UNREFERENCED_PARAMETER(nIDLastButton);
   //   UNREFERENCED_PARAMETER(nIDCheckButton);
   //   ::exception::throw_interface_only();
   //}

   //i32 interaction_impl::DlgDirList(char * pPathSpec,i32 nIDListBox,i32 nIDStaticPath,::u32 nFileType)

   //{
   //   UNREFERENCED_PARAMETER(pPathSpec);

   //   UNREFERENCED_PARAMETER(nIDListBox);
   //   UNREFERENCED_PARAMETER(nIDStaticPath);
   //   UNREFERENCED_PARAMETER(nFileType);
   //   ::exception::throw_interface_only();
   //   return 0;
   //}

   //i32 interaction_impl::DlgDirListComboBox(char * pPathSpec,i32 nIDComboBox,i32 nIDStaticPath,::u32 nFileType)

   //{
   //   UNREFERENCED_PARAMETER(pPathSpec);

   //   UNREFERENCED_PARAMETER(nIDComboBox);
   //   UNREFERENCED_PARAMETER(nIDStaticPath);
   //   UNREFERENCED_PARAMETER(nFileType);
   //   ::exception::throw_interface_only();

   //   return 0;
   //}

   //bool interaction_impl::DlgDirSelect(char * pString,i32 nSize,i32 nIDListBox)

   //{
   //   UNREFERENCED_PARAMETER(pString);

   //   UNREFERENCED_PARAMETER(nSize);
   //   UNREFERENCED_PARAMETER(nIDListBox);
   //   ::exception::throw_interface_only();

   //   return false;
   //}

   //bool interaction_impl::DlgDirSelectComboBox(char * pString,i32 nSize,i32 nIDComboBox)

   //{
   //   UNREFERENCED_PARAMETER(pString);

   //   UNREFERENCED_PARAMETER(nSize);
   //   UNREFERENCED_PARAMETER(nIDComboBox);
   //   ::exception::throw_interface_only();

   //   return false;
   //}

   //::u32 interaction_impl::GetChildByIdInt(i32 nID,bool* pTrans,bool bSigned) const

   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pTrans);

   //   UNREFERENCED_PARAMETER(bSigned);
   //   ::exception::throw_interface_only();

   //   return 0;
   //}

   //i32 interaction_impl::GetChildByIdText(i32 nID,char * pStr,i32 nMaxCount) const

   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pStr);

   //   UNREFERENCED_PARAMETER(nMaxCount);
   //   ::exception::throw_interface_only();

   //   return 0;
   //}


   //::user::interaction_impl * interaction_impl::GetNextDlgGroupItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   //{

   //   UNREFERENCED_PARAMETER(pWndCtl);
   //   UNREFERENCED_PARAMETER(bPrevious);

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::user::interaction_impl * interaction_impl::GetNextDlgTabItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   //{

   //   UNREFERENCED_PARAMETER(pWndCtl);
   //   UNREFERENCED_PARAMETER(bPrevious);

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //::u32 interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   //{
   //   UNREFERENCED_PARAMETER(nIDButton);
   //   ::exception::throw_interface_only();

   //   return 0;
   //}


   //lparam interaction_impl::SendDlgItemMessage(i32 nID, ::u32 message, wparam wParam,lparam lParam)
   //{

   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(message);
   //   UNREFERENCED_PARAMETER(wParam);
   //   UNREFERENCED_PARAMETER(lParam);
   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //void interaction_impl::SetDlgItemInt(i32 nID,::u32 nValue,bool bSigned)
   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(nValue);
   //   UNREFERENCED_PARAMETER(bSigned);
   //   ::exception::throw_interface_only();
   //}

   //void interaction_impl::SetDlgItemText(i32 nID,const char * pszString)

   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pszString);

   //   ::exception::throw_interface_only();
   //}


   //i32 interaction_impl::ScrollWindowEx(i32 dx,i32 dy,
   //                                     const RECTANGLE_I32 * prectScroll,
   //                                       const RECTANGLE_I32 * prectClip,
   //                                     ::draw2d::region* prgnUpdate,RECTANGLE_I32 * pRectUpdate,::u32 flags)
   //{

   //   UNREFERENCED_PARAMETER(dx);
   //   UNREFERENCED_PARAMETER(dy);
   //   UNREFERENCED_PARAMETER(prectScroll);
   //   UNREFERENCED_PARAMETER(prectClip);
   //   UNREFERENCED_PARAMETER(prgnUpdate);
   //   UNREFERENCED_PARAMETER(pRectUpdate);
   //   UNREFERENCED_PARAMETER(flags);

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //void interaction_impl::ShowScrollBar(::u32 nBar,bool bShow)
   //{

   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(bShow);

   //   ::exception::throw_interface_only();

   //}


   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point_i32 & point)
   {
      
      UNREFERENCED_PARAMETER(point);

      ::exception::throw_interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags)
   {

      UNREFERENCED_PARAMETER(point);

      UNREFERENCED_PARAMETER(nFlags);

      ::exception::throw_interface_only();

      return nullptr;

   }


//   ::user::interaction * interaction_impl::get_next_window(::u32 nFlag)
//   {
//
//      UNREFERENCED_PARAMETER(nFlag);
//
//      ::exception::throw_interface_only();
//
//      return nullptr;
//
//   }


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


   //bool interaction_impl::ChangeClipboardChain(::windowing::window * pwindow_Next)
   //{

   //   UNREFERENCED_PARAMETER(oswindow_Next);

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //oswindow interaction_impl::SetClipboardViewer()
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   //bool interaction_impl::OpenClipboard()
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   void interaction_impl::user_interaction_on_hide()
   {

      decltype(m_userinteractionaMouseHover) userinteractiona;

      {

         auto psync = mutex();

         synchronous_lock synchronouslock(mutex());

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

      ::exception::throw_interface_only();

   }


   void interaction_impl::ShowCaret()
   {

      ::exception::throw_interface_only();

   }


   //bool interaction_impl::SetForegroundWindow()
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //bool interaction_impl::SendNotifyMessage(::u32 message,wparam wParam,lparam lParam)
   //{

   //   UNREFERENCED_PARAMETER(message);
   //   UNREFERENCED_PARAMETER(wParam);
   //   UNREFERENCED_PARAMETER(lParam);

   //   ::exception::throw_interface_only();

   //   return false;

   //}


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

      }

      m_puiThis = m_puserinteraction;

   }


   void interaction_impl::_001OnPrioCreate(::message::message * pmessage)
   {

      //m_puserinteraction->on_create_user_interaction();

   }


   void interaction_impl::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         INFO("user::interaction_impl::on_message_show_window bShow = true");

         if (m_puserinteraction->layout().design().display() != ::e_display_iconic)
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

         {

            decltype(m_userinteractionaMouseHover) userinteractiona;

            {

               synchronous_lock synchronouslock(mutex());

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

            //   synchronous_lock synchronouslock(mutex());

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


   //void interaction_impl::CloseWindow()
   //{

   //   ::exception::throw_interface_only();

   //}


   //bool interaction_impl::OpenIcon()
   //{

   //   ::exception::throw_interface_only();

   //   return false;

   //}


   //i32 interaction_impl::GetCheckedRadioButton(i32 nIDFirstButton,i32 nIDLastButton)
   //{

   //   UNREFERENCED_PARAMETER(nIDFirstButton);
   //   UNREFERENCED_PARAMETER(nIDLastButton);

   //   ::exception::throw_interface_only();

   //   return 0;

   //}


   //bool interaction_impl::_EnableToolTips(bool bEnable,::u32 nFlag)
   //{

   //   UNREFERENCED_PARAMETER(bEnable);
   //   UNREFERENCED_PARAMETER(nFlag);

   //   ::exception::throw_interface_only();

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

      if (!m_puserinteraction || m_bFinishing)
      {

         return;

      }

      ::rectangle_i32 rectWindow;

      m_puserinteraction->get_window_rect(rectWindow);

      windowing_output_debug_string("\n_001UpdateBuffer : after get_window_rect");

      string strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("list_box"))
      {

         output_debug_string("list_box");

      }

      {

         ::size_i32 sizeDrawn;

         synchronous_lock slGraphics(m_pgraphics->mutex());

         ::synchronization_object * psync = m_pgraphics->get_buffer_sync();

         synchronous_lock synchronouslock(psync);

         ::draw2d::device_lock devicelock(m_puserinteraction);

         ::draw2d::graphics_pointer pgraphics = m_pgraphics->on_begin_draw();

         slGraphics.unlock();

         windowing_output_debug_string("\n_001UpdateBuffer : after on_begin_draw");

         if (m_bFinishing)
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

         pgraphics->m_puserstyle.release();

         if (pgraphics->m_pimage)
         {

            pgraphics->m_pimage->m_rectTag.Null();

            sizeDrawn = pgraphics->m_pimage->m_size;

         }

         if(m_puserinteraction)
         {

            auto r = m_puserinteraction->screen_rect();

            if (m_puserinteraction->m_bSetFinish)
            {

               output_debug_string("::user::interaction_impl set_finish");

            }
            else
            {

               m_puserinteraction->_001PrintBuffer(pgraphics);

            }

            m_rectUpdateBuffer = r;

            //TRACE("PrintBuffer (%d, %d)",  r.right, r.bottom);

            if(!m_pgraphics)
            {

               return;

            }

            m_pgraphics->m_bNewBuffer = true;

         }

         if (pgraphics->m_pimage)
         {

            pgraphics->m_pimage->m_rectTag = m_rectUpdateBuffer;

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

         m_puserinteraction->post_message(e_message_apply_visual);

      }

      return true;

   }


   void interaction_impl::_001UpdateWindow()
   {

   }


   void interaction_impl::_001UpdateScreen()
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_puserinteraction)
      {

         return;

      }

      string strType = m_puserinteraction->type_c_str();

      if(strType.contains_ci("list_box"))
      {

         auto edisplay = m_puserinteraction->layout().state(e_layout_design).display();

         bool bGraphicsSet = m_pgraphics.is_set();

         output_debug_string("_001UpdateScreen list_box");

      }

      if (m_pgraphics.is_set() && m_puserinteraction->layout().is_this_screen_visible())
      {

         CINFO(prodevian)("going to update_window (1)");

         m_pgraphics->update_window();

         m_puserinteraction->layout().output() = m_puserinteraction->layout().design();

      }

   }


   //bool interaction_impl::create_host(::user::interaction * pinteraction)
   //{

   //   return ;

   //}


   ::e_status interaction_impl::update_graphics_resources()
   {

      single_lock synchronouslock(mutex());

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


   ::e_status interaction_impl::interaction_branch(const ::routine & routine)
   {

      return ::error_interface_only;

   }

   
//   bool interaction_impl::pre_message_handler(bool & bKeyMessage, ::message::message * pmessage)
//   {
//
//      ::u32 message = pmessage->m_id.umessage();
//
//      ::message::key* pkey = nullptr;
//
//      bKeyMessage = message == e_message_key_down ||
//         message == e_message_key_up ||
//         message == e_message_char ||
//         message == e_message_sys_key_down ||
//         message == e_message_sys_key_up ||
//         message == e_message_sys_char ||
//         message == e_message_ime_key_down ||
//         message == e_message_ime_key_up ||
//         message == e_message_ime_char ||
//         message == e_message_ime_select ||
//         message == e_message_ime_set_context ||
//         message == e_message_ime_start_composition ||
//         message == e_message_ime_composition ||
//         message == e_message_ime_composition_full ||
//         message == e_message_ime_notify ||
//         message == e_message_ime_end_composition ||
//         message == e_message_input_language;
//
//      if (bKeyMessage)
//      {
//
//         pkey = dynamic_cast <::message::key*> (pmessage);
//
//         if (pkey)
//         {
//
//            m_pwindowing->set(pkey, pkey->m_oswindow, pkey->m_pwindow, pkey->m_id, pkey->m_wparam, pkey->m_lparam);
//
//         }
//
//         if (message == e_message_key_down || message == e_message_sys_key_down)
//         {
//
//            auto psession = get_session();
//
//            try
//            {
//
//               psession->set_key_pressed(pkey->m_ekey, true);
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }
//         else if (message == e_message_key_up || message == e_message_sys_key_up)
//         {
//
//            auto psession = get_session();
//
//            try
//            {
//
//               psession->set_key_pressed(pkey->m_ekey, false);
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }
//
//      }
//
//      if (::is_set(m_puserinteraction))
//      {
//
//         m_puserinteraction->pre_translate_message(pmessage);
//
//      }
//
//      if (pmessage->m_bRet)
//      {
//
//         return true;
//
//      }
//
//      return false;
//
//   }

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


   void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction,const ::rectangle_i32 & rectangle)
   {

      ASSERT(::is_set(pinteraction));

      __pointer(::user::interaction) puiParent = pinteraction->get_parent();

      ASSERT(puiParent != nullptr);

      ::rectangle_i32 rectOld;

      pinteraction->get_window_rect(rectOld);

      puiParent->screen_to_client(rectOld);

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


   ::e_status interaction_impl::set_finish(::object * pcontextobjectFinish)
   {

      if(!m_bFinishing)
      {

         if (m_pgraphics)
         {

            synchronous_lock slGraphics(m_pgraphics->mutex());

            ::synchronization_object * psync = m_pgraphics->get_draw_lock();

            synchronous_lock synchronouslock(psync);

            slGraphics.unlock();

            m_bFinishing = true;

         }

      }

      return ::user::primitive_impl::set_finish();

   }


   void interaction_impl::prodevian_stop()
   {

      auto pprodevian = m_pprodevian;

      if (::is_set(pprodevian) && ::is_set(m_pgraphics))
      {

         {

            synchronous_lock slGraphics(m_pgraphics->mutex());

            ::synchronization_object * psyncDraw = m_pgraphics->get_draw_lock();

            synchronous_lock slDraw(psyncDraw);

            slGraphics.unlock();

            //pprodevian->m_puserinteraction = nullptr;

            //pprodevian->m_pimpl = nullptr;

            pprodevian->set_finish();

         }

         //{

         //   synchronous_lock synchronouslock(mutex());

         //   synchronous_lock slGraphics(m_pgraphics->mutex());

         //   m_pprodevian);

         //}

      }

   }


   bool interaction_impl::prodevian_update_screen()
   {

      _001UpdateScreen();

      return true;

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


   //bool interaction_impl::attach(::windowing::window * pwindowNew)
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


   ::e_status interaction_impl::finalize()
   {

      return ::user::primitive::finalize();

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


   ::user::primitive * interaction_impl::get_keyboard_focus()
   {

      return m_puserinteractionFocus1;

   }


   void interaction_impl::_001OnSetFocus(::message::message * pmessage)
   {

      __pointer(::message::set_keyboard_focus) psetkeyboardfocus(pmessage);

      on_final_set_keyboard_focus(psetkeyboardfocus);

      if (m_puserinteraction->m_ewindowflag & e_window_flag_focus)
      {

         return;

      }

      m_puserinteraction->m_ewindowflag |= e_window_flag_focus;

   }
   
   
   void interaction_impl::on_final_set_keyboard_focus(::message::set_keyboard_focus * psetkeyboardfocus)
   {

      on_final_kill_keyboard_focus(nullptr);

      synchronous_lock synchronouslock(mutex());

      if (m_puserinteractionFocusRequest && m_puserinteractionFocusRequest != m_puserinteractionFocus1)
      {

         m_puserinteractionFocus1 = m_puserinteractionFocusRequest;

         m_puserinteractionToKillFocus = m_puserinteractionFocus1;

         m_puserinteractionFocusRequest = nullptr;

         auto puserinteraction = m_puserinteractionFocus1;

         synchronouslock.unlock();

         puserinteraction->on_set_keyboard_focus();

      }

   }


   void interaction_impl::_001OnKillFocus(::message::message * pmessage)
   {

      __pointer(::message::kill_keyboard_focus) pkillkeyboardfocus(pmessage);

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_focus))
      {

         return;

      }

      m_puserinteraction->m_ewindowflag -= e_window_flag_focus;

      on_final_kill_keyboard_focus(pkillkeyboardfocus);

   }

   
   void interaction_impl::on_final_kill_keyboard_focus(::message::kill_keyboard_focus * pkillkeyboardfocus)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_puserinteractionToKillFocus && m_puserinteractionToKillFocus != m_puserinteractionFocusRequest)
      {

         auto pinteraction = m_puserinteractionToKillFocus;

         m_puserinteractionToKillFocus = nullptr;

         synchronouslock.unlock();

         pinteraction->on_kill_keyboard_focus();

      }

   }


   //::e_status interaction_impl::impl_set_keyboard_focus(::user::primitive * pprimitiveFocusNew)
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


   //::e_status interaction_impl::impl_erase_keyboard_focus(::user::primitive * pprimitiveFocusRemove)
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


   //::e_status interaction_impl::impl_clear_keyboard_focus()
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


   //::e_status interaction_impl::set_keyboard_focus(::user::primitive * pprimitive)
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


   //::e_status interaction_impl::erase_keyboard_focus(::user::primitive * pprimitive)
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


   //::e_status interaction_impl::clear_keyboard_focus()
   //{

   //   auto puserinteraction = m_puserinteraction;

   //   if (::is_null(puserinteraction))
   //   {

   //      return false;

   //   }

   //   ::user::interaction * pinteractionHost = puserinteraction->get_host_window();

   //   if (::is_null(pinteractionHost))
   //   {

   //      return false;

   //   }

   //   auto pimplHost = pinteractionHost->m_pimpl;

   //   if (::is_null(pimplHost))
   //   {

   //      return false;

   //   }

   //   pimplHost->impl_clear_keyboard_focus();

   //   return false;

   //}


   bool interaction_impl::post(::message::message * pmessage)
   {

      if (m_puserthread)
      {

         synchronous_lock synchronouslock(m_puserthread->mutex());

         m_puserthread->m_messagebasea.add(pmessage);

         m_puserthread->kick_idle();

         return true;

      }

      m_puserinteraction->post_routine(__routine([this, pmessage]()
      {

         return m_puserinteraction->message_handler(pmessage);

      }));

      return true;

   }



   void interaction_impl::redraw_add(::object * p)
   {

      synchronous_lock synchronouslock(mutex_redraw());

      m_ptraRedraw.add(p);

   }


   void interaction_impl::redraw_erase(::object * p)
   {

      synchronous_lock synchronouslock(mutex_redraw());

      m_ptraRedraw.erase(p);

   }


   bool interaction_impl::has_redraw()
   {

      synchronous_lock synchronouslock(mutex_redraw());

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

         synchronous_lock synchronouslock(mutex());

         if (m_ptraRedraw.has_elements())
         {

            return true;

         }

      }

      return false;

   }


   void interaction_impl::on_after_graphical_update()
   {


#ifdef ANDROID

      oslocal()->m_bRedraw = true;

#endif


   }




   void interaction_impl::window_show()
   {

      if(::is_null(m_puserinteraction))
      {

         return;

      }

      // Request / Incoming changes / Prepare Internal Buffer
      auto & stateOutput = m_puserinteraction->layout().design();

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

      string strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("font_format"))
      {

         INFO("font_format going to gather Z-Ordering information");

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

            _001OnExitZoomed();

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

         //output_debug_string("SetWindowPos bottom_right " + __str(pointBottomRight.x) + ", " + __str(pointBottomRight.y) + "\n");

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

         //__throw(todo);
         //m_puserinteraction->set();

         m_pwindow->set_foreground_window();

      }

      if (eactivationOutput & e_activation_set_active)
      {

         //__throw(todo);
         ///m_puserinteraction->SetActiveWindow();

         m_pwindow->set_active_window();

      }

      if(!m_puserinteraction)
      {

         return;

      }

      m_puserinteraction->layout().window() = m_puserinteraction->layout().design();

      m_puserinteraction->layout().design().clear_activation();

      m_puserinteraction->layout().design().display() = edisplayOutput;

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


   bool interaction_impl::ShowWindow(const ::e_display & edisplay)
   {

      return false;


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

      synchronous_lock synchronouslock(mutex());

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

      m_puserinteraction->m_pthreadUserInteraction->post_predicate([this, edisplay, eactivation]()
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

               m_puserinteraction->layout().design() = e_activation_default;

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


   void interaction_impl::on_message_move(::message::message * pmessage)
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

         auto & layout = m_puserinteraction->layout();

         auto & sketch_origin = layout.sketch().origin();

         auto & window_origin = layout.window().origin();

         window_origin = pmove->m_point;

         if(window_origin != sketch_origin)
         {

            sketch_origin = window_origin;

            m_puserinteraction->set_reposition();

            m_puserinteraction->set_need_redraw();

            m_puserinteraction->post_redraw();

         }

         //if (m_puserinteraction->layout().is_moving())
         //{

           // INFO("\nWindow is Moving :: on_message_move");

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

      m_puserinteraction->layout().window().size() = psize->m_size;

      if ((m_puserinteraction->layout().sketch().size()
           != m_puserinteraction->layout().window().size()))
      {

         m_puserinteraction->layout().sketch().size() = m_puserinteraction->layout().window().size();
         m_puserinteraction->layout().design().size() = m_puserinteraction->layout().window().size();

         //if (m_puserinteraction->layout().is_moving())
         //{

         // INFO("\nWindow is Moving :: on_message_move");

         //}

         //m_puserinteraction->layout().sketch().origin() = pmove->m_point;

         //if (m_puserinteraction->layout().sketch().display() != e_display_normal)
         //{

         // m_puserinteraction->display(e_display_normal);

         //}

         //m_puserinteraction->set_reposition();

         //m_puserinteraction->set_need_redraw();

         //m_puserinteraction->post_redraw();

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


   ::e_status interaction_impl::show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd)
   {

      return error_interface_only;

   }


   ::e_status interaction_impl::hide_software_keyboard(::user::primitive * pprimitive)
   {

      return error_interface_only;

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

      synchronous_lock synchronouslock(m_pgraphics->get_screen_sync());

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

      return m_pgraphics->get_screen_image()->_001GetTopLeftWeightedOpaqueArea(colorTransparent);

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

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_is_window))
      {

         return false;

      }

      if (m_puserinteraction->m_ewindowflag & e_window_flag_not_visible)
      {

         return false;

      }

      if (!m_puserinteraction->layout().state(elayout).is_visible())
      {

         return false;

      }

      return true;

   }


   strsize interaction_impl::get_window_text(char * sz, int s)
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

   
   ::e_status interaction_impl::set_icon(::windowing::icon*)
   {

      return ::success;

   }


   __pointer(::windowing::icon) interaction_impl::get_icon() const
   {

      return nullptr;

   }


   ::e_status interaction_impl::set_tool_window(bool bSet)
   {

      return m_pwindow->set_tool_window(bSet);

   }

} // namespace user



