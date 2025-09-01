#include "framework.h"
#include "control_bar.h"
#include "frame_window.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"
#include "aura/user/user/size_parent_layout.h"
#include "aura/windowing/window.h"


namespace user
{


   void DrawGripperElement001(::draw2d::graphics_pointer & pgraphics, int ix, int iy);


   control_bar::control_bar()
   {

      m_bFullScreenBar = false;
      m_bDockTrack = false;

      // no elements contained in the control bar yet
      //   m_nCount = 0;
      //m_pData = nullptr;

      // set up some default border spacings
      m_rectangleBorder.set(6, 1, 6, 1);
      //m_rectangleBorder.left() = m_rectangleBorder.right() = 6;
      m_cxDefaultGap = 2;
      //m_rectangleBorder.top() = m_rectangleBorder.bottom() = 1;
      m_bAutoDelete = false;
      m_nStateFlags = 0;
      m_pDockBar = nullptr;
      m_pDockContext = nullptr;
      m_dwStyle = 0;
      m_dwDockStyle = 0;
      m_nMRUWidth = 32767;

   }


   void control_bar::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

//#ifdef WINDOWS
//      MESSAGE_LINK(WM_CTLCOLOR, pchannel, this, &control_bar::_001OnCtlColor);
//#endif
      MESSAGE_LINK(::user::e_message_size_parent, pchannel, this, &control_bar::_001OnSizeParent);
      MESSAGE_LINK(::user::e_message_window_position_changing, pchannel, this, &control_bar::_001OnWindowPosChanging);
      MESSAGE_LINK(::user::e_message_mouse_move, pchannel, this, &control_bar::on_message_mouse_move);
      MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &control_bar::on_message_left_button_down);
      MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &control_bar::on_message_left_button_up);
      MESSAGE_LINK(::user::e_message_mouse_activate, pchannel, this, &control_bar::_001OnMouseActivate);
      MESSAGE_LINK(::user::e_message_create, pchannel, this, &control_bar::on_message_create);
      MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &control_bar::on_message_destroy);
      MESSAGE_LINK(::user::e_message_help_hit_test, pchannel, this, &control_bar::_001OnHelpHitTest);
   }


   void control_bar::SetBorders(int cxLeft, int cyTop, int cxRight, int cyBottom)
   {
      ASSERT(cxLeft >= 0);
      ASSERT(cyTop >= 0);
      ASSERT(cxRight >= 0);
      ASSERT(cyBottom >= 0);

      m_rectangleBorder.left() = cxLeft;
      m_rectangleBorder.top() = cyTop;
      m_rectangleBorder.right() = cxRight;
      m_rectangleBorder.bottom() = cyBottom;
   }


   bool control_bar::pre_create_window(::user::system * pusersystem)
   {

      if (!::user::interaction::pre_create_window(pusersystem))
      {

         return false;

      }


//#ifdef WINDOWS_DESKTOP
//
//      // force clipsliblings (otherwise will cause repaint problems)
//      pusersystem->m_createstruct.style |= WS_CLIPSIBLINGS;
//
//#endif

      // default border style translation for Win4
      //  (you can turn off this translation by setting CBRS_BORDER_3D)
      //   if (::windows_definition::Data.bWin4 && (m_dwStyle & CBRS_BORDER_3D) == 0)
      if ((m_dwStyle & CBRS_BORDER_3D) == 0)
      {
         unsigned int dwNewStyle = 0;
         switch (m_dwStyle & (CBRS_BORDER_ANY|CBRS_ALIGN_ANY))
         {
         case CBRS_LEFT:
            dwNewStyle = CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM;
            break;
         case CBRS_TOP:
            dwNewStyle = CBRS_BORDER_TOP;
            break;
         case CBRS_RIGHT:
            dwNewStyle = CBRS_BORDER_TOP|CBRS_BORDER_BOTTOM;
            break;
         case CBRS_BOTTOM:
            dwNewStyle = CBRS_BORDER_BOTTOM;
            break;
         }

         // set ___new style if it matched one of the predefined border types
         if (dwNewStyle != 0)
         {
            m_dwStyle &= ~(CBRS_BORDER_ANY);
            m_dwStyle |= (dwNewStyle | CBRS_BORDER_3D);
         }
      }
      if(m_dwStyle & CBRS_LEAVEONFULLSCREEN)
      {
         m_bFullScreenBar = true;
      }

      return true;
   }

   void control_bar::SetBarStyle(unsigned int uStyle)
   {
      ASSERT((uStyle & CBRS_ALL) == uStyle);

      if (m_dwStyle != uStyle)
      {
         unsigned int dwOldStyle = m_dwStyle;
         m_dwStyle = uStyle;
         OnBarStyleChange(dwOldStyle, uStyle);
      }
   }

   void control_bar::OnBarStyleChange(unsigned int, unsigned int)
   {
      // can be overridden in derived classes
   }

   /*
   bool control_bar::AllocElements(int nElements, int cbElement)
   {
      ASSERT_OK(this);
      ASSERT(nElements >= 0 && cbElement >= 0);
      ASSERT(m_pData != nullptr || m_nCount == 0);

      // allocate ___new data if necessary
      void * pData = nullptr;
      if (nElements > 0)
      {
         ASSERT(cbElement > 0);
         if ((pData = calloc(nElements, cbElement)) == nullptr)
            return false;
      }
      free(m_pData);      // free old data

      // set ___new data and elements
      m_pData = pData;
      m_nCount = nElements;

      return true;
   }
   */


   control_bar::~control_bar()
   {

      ASSERT_OK(this);

      if (m_pframewindowDockSite)
      {

         m_pframewindowDockSite->erase_control_bar(this);

         m_pframewindowDockSite.release();

      }

      // free docking context
      /*   BaseDockContext* pDockContext = m_pDockContext;
         m_pDockContext = nullptr;
         delete pDockContext;*/

      // free array
      /*
         if (m_pData != nullptr)
         {
            ASSERT(m_nCount != 0);
            free(m_pData);
         }
      */

   }


   void control_bar::destroy()
   {

      ::user::interaction::destroy();
      //if (m_bAutoDelete)      // Automatic cleanup?
      // delete this;
   }

   /////////////////////////////////////////////////////////////////////////////
   

   int_size control_bar::CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz)
   {
      ::int_size size;
      size.cx() = (bStretch && bHorz ? 32767 : 0);
      size.cy() = (bStretch && !bHorz ? 32767 : 0);
      return size;
   }

   int_size control_bar::CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, int, unsigned int nMode)
   {
      return CalcFixedLayout(pgraphics, (nMode & LM_STRETCH) != 0, (nMode & LM_HORZ) != 0);
   }

   bool control_bar::IsDockBar()
   {
      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Fly-by status bar help

#define ID_TIMER_WAIT   0xE000  // timer while waiting to show status
#define ID_TIMER_CHECK  0xE001  // timer to check for removal of status

   void control_bar::ResetTimer(unsigned int nEvent, const class time & time)
   {
      kill_timer(ID_TIMER_WAIT);
      kill_timer(ID_TIMER_CHECK);
      set_timer(nEvent,time,nullptr);
   }

   void control_bar::on_timer(::timer * ptimer)
   {
      __UNREFERENCED_PARAMETER(ptimer);
//      unsigned int uEvent = ptimer->m_uTimer;
#ifdef WINDOWS_DESKTOP
      

      if (session()->is_key_pressed(::user::e_key_left_button))
         return;
#else
      throw ::exception(todo);
#endif

   }


   bool control_bar::SetStatusText(int nHit)
   {

      ::pointer<::user::interaction>pOwner = get_owner();

      //if (nHit == -1)
      //{
      //   if (m_nStateFlags & statusSet)
      //   {
      //      m_nStateFlags &= ~statusSet;
      //      return true;
      //   }
      //   kill_timer(ID_TIMER_WAIT);
      //}
      //else
      //{
      //   // handle setnew case
      //   if (!(m_nStateFlags & statusSet))
      //   {
      //      pOwner->send_message(WM_SETMESSAGESTRING, nHit);
      //      m_nStateFlags |= statusSet;
      //      ResetTimer(ID_TIMER_CHECK, 200);
      //      return true;
      //   }
      //}
      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Default control bar processing

   void control_bar::pre_translate_message(::message::message * pmessage)
   {
      ASSERT_OK(this);
      //trans   ASSERT(get_handle() != nullptr);

      // allow tooltip messages to be filtered
      ::user::interaction::pre_translate_message(pmessage);
      if(pmessage->m_bRet)
         return;

      ::pointer<::user::interaction>pOwner = get_owner();

#ifdef WINDOWS_DESKTOP

//      ::pointer<::user::message>pmessage(pmessage);
//
//      unsigned int message;
//
//      message = pmessage->m_emessage.umessage();
//
//      // handle CBRS_FLYBY style (status bar flyby help)
//      if (((m_dwStyle & CBRS_FLYBY) ||
//            message == ::user::e_message_left_button_down || message == ::user::e_message_left_button_up) &&
//            ((message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)))
////          (message >= WM_NCMOUSEFIRST && message <= WM_NCMOUSELAST)))
//      {
//      }
#else
//      throw ::exception(todo);
#endif

      // don't translate dialog messages when in Shift+F1 help mode
      ::pointer<::user::frame_window>pFrameWnd = top_level_frame();
      if (pFrameWnd != nullptr && pFrameWnd->m_bHelpMode)
         return;

      // since 'IsDialogMessage' will eat frame interaction_impl accelerators,
      //   we call all frame windows' pre_translate_message first
      while (pOwner != nullptr)
      {

         // allow owner & frames to translate before IsDialogMessage does
         pOwner->pre_translate_message(pmessage);

         if (pmessage->m_bRet)
         {

            return;

         }

         // try parent frames until there are no parent frames
         pOwner = pOwner->parent_frame();

      }

      // filter both messages to dialog and from children
      // pmessage->m_bRet = false;

   }


   void control_bar::message_handler(::message::message * pmessage)
   {

      ::user::interaction::message_handler(pmessage);

      if (pmessage->m_bRet)
      {

         return;

      }

#ifdef WINDOWS_DESKTOP

//      ASSERT_OK(this);
//
//      lresult lResult;
//
//      unsigned int message;
//
//      message = pmessage->m_emessage.umessage();
//
//      switch (message)
//      {
//      case WM_NOTIFY:
//      case ::user::e_message_command:
//      case WM_DRAWITEM:
//      case ::user::e_message_measure_item:
//      case WM_DELETEITEM:
//      case WM_COMPAREITEM:
//      case WM_VKEYTOITEM:
//      case WM_CHARTOITEM:
//         // send these messages to the owner if not handled
//         //      if (OnWndMsg(nMsg, wParam, lParam, &lResult))
//         //         return lResult;
//         //      else
//      {
//         // try owner next
//         lResult = get_owner()->send_message((enum_message) message, pmessage->m_wparam, pmessage->m_lparam);
//
//         // special case for TTN_NEEDTEXTA and TTN_NEEDTEXTW
////#ifdef WINDOWS_DESKTOP
////            if(pmessage->m_emessage == WM_NOTIFY)
////            {
////               NMHDR* pNMHDR = (NMHDR*)pmessage->m_lparam.m_lparam;
////               if (pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW)
////               {
////                  TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
////                  TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
////                  if ((pNMHDR->code == TTN_NEEDTEXTA && (!pTTTA->pszText || !*pTTTA->pszText)) ||
//
////                     (pNMHDR->code == TTN_NEEDTEXTW && (!pTTTW->pszText || !*pTTTW->pszText)))
//
////                  {
////                     // not handled by owner, so let bar itself handle it
////                     ::user::interaction::message handler(pmessage);
////                  }
////               }
////            }
////#else
////            throw ::exception(todo);
////#endif
//         return;
//      }
//      }

#endif

      // otherwise, just handle in default way
      ::user::interaction::message_handler(pmessage);

   }


   void control_bar::_001OnHelpHitTest(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::user::message>pmessage(pmessage);
      ASSERT_OK(this);

   }


   void control_bar::_001OnWindowPosChanging(::message::message * pmessage)
   {

      //__UNREFERENCED_PARAMETER(pmessage);

      //default_window_procedure(pmessage);

   }


   void control_bar::on_message_create(::message::message * pmessage)
   {

      if(pmessage->previous())
         return;

      ::pointer<::user::frame_window>pframe = get_parent();

      if (pframe)
      {

         m_pframewindowDockSite = pframe;

         m_pframewindowDockSite->add_control_bar(this);

      }

   }


   void control_bar::on_message_destroy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_pframewindowDockSite)
      {

         m_pframewindowDockSite->erase_control_bar(this);

         m_pframewindowDockSite.release();

      }

   }


   void control_bar::destroy_window()
   {

      //return 
      ::user::interaction::destroy_window();

   }


   void control_bar::_001OnMouseActivate(::message::message * pmessage)
   {
      ::pointer<::message::mouse_activate>pmouseactivate(pmessage);
      // call default when toolbar is not floating
      if (!IsFloating())
      {
         //trans pmouseactivate->set_lresult(::user::interaction::OnMouseActivate(pmouseactivate->get_desktop_window(), pmouseactivate->GetHitTest(), pmouseactivate->GetMessage()));
         pmessage->m_bRet = true;
         return;
      }

      // special behavior when floating
      ActivateTopParent();

      pmouseactivate->m_lresult = e_mouse_activate_no_activate;   // activation already done

      pmessage->m_bRet = true;

      return;
   }

   void control_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      // background is already filled in gray
      //CPaintDC spgraphics(this);

      // erase background now
      //if (IsVisible())
      //DoPaint(&spgraphics);       // delegate to paint helper
      if (IsVisible())
         DoPaint(pgraphics);       // delegate to paint helper
   }

   void control_bar::EraseNonClient()
   {
      // get interaction_impl DC that is clipped to the non-client area
      /* trans   CWindowDC spgraphics(this);
         auto rectangleX = this->rectangle();
         ::int_rectangle rectangleWindow;
         window_rectangle(rectangleWindow);
         screen_to_client(rectangleWindow);
         rectangleX.offset(-rectangleWindow.left(), -rectangleWindow.top());
         spgraphics->ExcludeClipRect(rectangleX);

         // draw borders in non-client area
         rectangleWindow.offset(-rectangleWindow.left(), -rectangleWindow.top());
         DrawBorders(&spgraphics, rectangleWindow);

         // erase parts not drawn
         spgraphics->IntersectClipRect(rectangleWindow);
         SendMessage(::user::e_message_erase_background, (WPARAM)spgraphics->get_handle1());

         // draw gripper in non-client area
         DrawGripper(&spgraphics, rectangleWindow);*/
   }

   void control_bar::EraseNonClient(::draw2d::graphics_pointer & pgraphics)
   {

      // get interaction_impl DC that is clipped to the non-client area
      ::int_rectangle rectangleX;
      rectangleX = this->rectangle();
      ::int_rectangle rectangleWindow;
      window_rectangle(rectangleWindow);
      screen_to_client()(rectangleWindow);
      rectangleX.offset(-rectangleWindow.left(), -rectangleWindow.top());
      
      //pgraphics->exclude_clip();
      
      //pgraphics->ExcludeClipRect(rectangleX);

      // draw borders in non-client area
      rectangleWindow.offset(-rectangleWindow.left(), -rectangleWindow.top());
      DrawBorders(pgraphics, rectangleWindow);

      // erase parts not drawn
      //pgraphics->IntersectClipRect(rectangleWindow);
      //SendMessage(::user::e_message_erase_background, (WPARAM)spgraphics->get_handle1());
      pgraphics->reset_clip();

      auto rectangle = ::double_rectangle_dimension(0, 0, rectangleWindow.width(), rectangleWindow.height());

      pgraphics->fill_rectangle(rectangle, argb(128, 192, 192, 187));

      // draw gripper in non-client area
      DrawGripper(pgraphics, rectangleWindow);

   }


   void control_bar::_001OnCtlColor(::message::message * pmessage)
   {
      
      ::pointer < ::message::ctl_color > pctlcolor(pmessage);

      auto pinteraction = pctlcolor->window()->user_interaction();
      
      if (::is_set(pinteraction) && pinteraction->OnChildNotify(pctlcolor))
      {
         
         pctlcolor->m_bRet = true;
         
         return;
         
      }

      // force black text on gray background all the time
      /*      if (!interaction_impl::GrayCtlColor((HDC)pctlcolor->m_pdc->get_os_data(), pctlcolor->m_puserinteraction->get_os_data(), pctlcolor->m_nCtlType,
               ::windows_definition::Data.hbrBtnFace, ::windows_definition::Data.clrBtnText))
            {
               pctlcolor->set_lresult(Default());
               pctlcolor->m_bRet = true;
               return;
            }*/
      //pctlcolor->set_lresult((LRESULT) ::windows_definition::Data.hbrBtnFace);
      pctlcolor->m_bRet = true;
   }

   void control_bar::on_message_left_button_down(::message::message * pmessage)
   {
      auto pmouse = pmessage->m_union.m_pmouse;
      // only start dragging if clicked in "void" space
      if (m_pDockBar != nullptr )
         //!m_pDockContext->m_bTracking  && OnToolHitTest(pmouse->m_point, nullptr) == -1)
      {
         // start the drag
         ASSERT(m_pDockContext != nullptr);
         //client_to_screen(&pmouse->m_point);
         //      m_pDockContext->StartDrag(pmouse->m_point);
      }
      else
      {
         pmouse->previous();
      }
   }

   void control_bar::on_message_left_button_up(::message::message * pmessage)
   {
      auto pmouse = pmessage->m_union.m_pmouse;
      if(m_bDockTrack)
      {
         //      m_pDockContext->OnBarLButtonUp(pmouse->m_nFlags, pmouse->m_point);
      }
      pmouse->previous();
   }

   void control_bar::on_message_mouse_move(::message::message * pmessage)
   {
      auto pmouse = pmessage->m_union.m_pmouse;
      if(m_bDockTrack)
      {
         //      m_pDockContext->OnBarMouseMove(pmouse->m_nFlags, pmouse->m_point);
      }
      pmouse->previous();
   }


   void control_bar::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      // // update the indicators before becoming visible
      // ::user::message base(this);
      // LRESULT lresult;
      // base.set(this, ::user::e_message_idle_update_command_user_interface, true, (LPARAM) 0, lresult);
      // _001OnIdleUpdateCmdUI(&base);

   }


   unsigned int control_bar::RecalcDelayShow(void * pvoidSIZEPARENTPARAMS)
   {

//      SIZEPARENTPARAMS * playout = (SIZEPARENTPARAMS * ) pvoidSIZEPARENTPARAMS;

      unsigned int uStyleVisible = 0;

      //if (GetStyle() & WS_VISIBLE)
      //{

      //   uStyleVisible |= WS_VISIBLE;

      //}

      unsigned int uStyle = (m_dwStyle & (CBRS_ALIGN_ANY|CBRS_BORDER_ANY)) | uStyleVisible;

      return uStyle;

//      ASSERT(playout != nullptr);
//
//
//      unsigned int dwStyleVisible = (GetStyle() & WS_VISIBLE);
//
//      if (is_this_visible())
//      {
//
//         dwStyleVisible |= WS_VISIBLE;
//
//      }
//
//      // resize and reposition this control bar based on styles
//      unsigned int uStyle = (m_dwStyle & (CBRS_ALIGN_ANY|CBRS_BORDER_ANY)) |
//                         dwStyleVisible;
//
//      // handle delay hide/show
////      if (m_nStateFlags & (delayHide|delayShow))
//      {
//         unsigned int swpFlags = 0;
//         //if (m_nStateFlags & delayHide)
//         //{
//         //   ASSERT((m_nStateFlags & delayShow) == 0);
//         //   if (uStyle & WS_VISIBLE)
//         //      swpFlags = SWP_HIDEWINDOW;
//         //}
//         //else
//         //{
//         //   ASSERT(m_nStateFlags & delayShow);
//         //   if ((uStyle & WS_VISIBLE) == 0)
//         //      swpFlags = SWP_SHOWWINDOW;
//         //}
//         if (swpFlags != 0)
//         {
//             make the interaction_impl seem visible/hidden
//            uStyle ^= WS_VISIBLE;
//             clear delay flags
//            m_nStateFlags &= ~(delayShow|delayHide);
//             hide/show the interaction_impl if actually doing on_layout
//
//            if (swpFlags & SWP_HIDEWINDOW)
//            {
//
//               hide();
//
//            }
//            else if (swpFlags & SWP_SHOWWINDOW)
//            {
//
//               display(e_display_normal, ::user::e_activation_no_activate);
//
//            }
//
//            set_window_position(zorder_none, 0, 0, 0, 0, swpFlags | SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOREDRAW);
//         }
//         else
//         {
//            // clear delay flags -- interaction_impl is already in correct state
//            m_nStateFlags &= ~(delayShow|delayHide);
//         }
//      }
//      return uStyle; // return ___new style
   }


   void control_bar::_001OnSizeParent(::message::message * pmessage)
   {

      size_parent_layout * playout = (size_parent_layout *) pmessage->m_lparam.m_lparam;

      unsigned int uStyle = RecalcDelayShow(playout);

      bool bIsThisVisible = is_this_visible(e_layout_sketch);

      if (bIsThisVisible && (uStyle & CBRS_ALIGN_ANY) != 0)
      {
         
         // align the control bar
         ::int_rectangle rectangle;

         rectangle = playout->m_rectangle;

         ::int_size sizeAvail = rectangle.size();  // maximum int_size available

         // get maximum requested int_size
         unsigned int dwMode = playout->m_bStretch ? LM_STRETCH : 0;

         if ((m_dwStyle & CBRS_SIZE_DYNAMIC) && m_dwStyle & CBRS_FLOATING)
         {

            dwMode |= LM_HORZ | LM_MRUWIDTH;

         }
         else if (uStyle & CBRS_ORIENT_HORZ)
         {

            dwMode |= LM_HORZ | LM_HORZDOCK;

         }
         else
         {

            dwMode |= LM_VERTDOCK;

         }

         auto psystem = system();

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(this);

         //pgraphics->m_puserinteraction = this;

         ::int_size size = CalcDynamicLayout(pgraphics, -1, dwMode);

         size.cx() = minimum(size.cx(), sizeAvail.cx());
         size.cy() = minimum(size.cy(), sizeAvail.cy());

         if (uStyle & CBRS_ORIENT_HORZ)
         {

            playout->m_sizeTotal.cy() += size.cy();

            playout->m_sizeTotal.cx() = maximum(playout->m_sizeTotal.cx(), size.cx());

            if (uStyle & CBRS_ALIGN_TOP)
            {

               playout->m_rectangle.top() += size.cy();

            }
            else if (uStyle & CBRS_ALIGN_BOTTOM)
            {

               rectangle.top() = rectangle.bottom() - size.cy();

               playout->m_rectangle.bottom() -= size.cy();

            }

         }
         else if (uStyle & CBRS_ORIENT_VERT)
         {

            playout->m_sizeTotal.cx() += size.cx();

            playout->m_sizeTotal.cy() = maximum(playout->m_sizeTotal.cy(), size.cy());

            if (uStyle & CBRS_ALIGN_LEFT)
            {

               playout->m_rectangle.left() += size.cx();

            }
            else if (uStyle & CBRS_ALIGN_RIGHT)
            {

               rectangle.left() = rectangle.right() - size.cx();

               playout->m_rectangle.right() -= size.cx();

            }

         }
         else
         {

            ASSERT(false);      // can never happen

         }

         rectangle.right() = rectangle.left() + size.cx();

         rectangle.bottom() = rectangle.top() + size.cy();

         // only resize the interaction_impl if doing on_layout and not just int_rectangle query
         //if (playout->hDWP != nullptr)

         //::user::__reposition_window(playout, this, &rectangle);

         ASSERT(::is_set(this));

         ::pointer<::user::interaction>puiParent = get_parent();

         ASSERT(puiParent != nullptr);

         ::int_rectangle rectangleOld;

         window_rectangle(rectangleOld);

         puiParent->screen_to_client()(rectangleOld);

         place(rectangle);

         display(e_display_normal, { ::user::e_activation_no_activate } );

      }

      pmessage->m_lresult = 0;

   }


//   void control_bar::DelayShow(bool bShow)
//   {
//      m_nStateFlags &= ~(delayHide|delayShow);
////      /*if (bShow && (GetStyle() & WS_VISIBLE) == 0)
//      //       m_nStateFlags |= delayShow;
//      //  else if (!bShow && (GetStyle() & WS_VISIBLE) != 0)
//      //   m_nStateFlags |= delayHide;*/
//      if (bShow && !is_this_visible())
//         m_nStateFlags |= delayShow;
//      else if (!bShow && is_this_visible())
//         m_nStateFlags |= delayHide;
//   }

   bool control_bar::IsVisible()
   {
      return is_this_visible();
      //if (m_nStateFlags & delayHide)
      //   return false;

      //if ((m_nStateFlags & delayShow) || ((GetStyle() & WS_VISIBLE) != 0))
      //   return true;

      //return false;
   }


   void control_bar::DoPaint(::draw2d::graphics_pointer & pgraphics)
   {

      ASSERT_OK(this);
      //ASSERT_OK(pgraphics);

      // paint inside client area
      ::int_rectangle rectangle;

      rectangle = this->rectangle();

      DrawBorders(pgraphics, rectangle);

      DrawGripper(pgraphics, rectangle);

   }


   void control_bar::DrawBorders(::draw2d::graphics_pointer & pgraphics, ::int_rectangle& rectangle)
   {

      ASSERT_OK(this);

      ASSERT_OK(pgraphics);

      unsigned int uStyle = m_dwStyle;
      if (!(uStyle & CBRS_BORDER_ANY))
         return;

      // prepare for dark lines
      ASSERT(rectangle.top() == 0 && rectangle.left() == 0);
      ::int_rectangle rect1, rect2;
      rect1 = rectangle;
      rect2 = rectangle;
      //   ::color::color clr = ::windows_definition::Data.bWin4 ? ::windows_definition::Data.clrBtnShadow : ::windows_definition::Data.clrWindowFrame;
//      ::color::color clr = ::windows_definition::Data.clrBtnShadow;
      ::color::color clr;
      clr = rgb(128, 128, 123);




#ifdef WINDOWS_DESKTOP
      int CX_BORDER = 2;
      int CY_BORDER = 2;
      // draw dark line one pixel back/up
      if (uStyle & CBRS_BORDER_3D)
      {
         rect1.right() -= CX_BORDER;
         rect1.bottom() -= CY_BORDER;
      }
      if (uStyle & CBRS_BORDER_TOP)
         rect2.top() += 2;
      //rect2.top() += ::windows_definition::Data.cyBorder2;
      if (uStyle & CBRS_BORDER_BOTTOM)
         rect2.bottom() -= 2;
      //rect2.bottom() -= ::windows_definition::Data.cyBorder2;

      // draw left and top
      if (uStyle & CBRS_BORDER_LEFT)
      {
         if(uStyle & CBRS_GRIPPER)
         {
            pgraphics->fill_rectangle(::double_rectangle_dimension(0, rectangle.top() + 7, CX_BORDER, rectangle.height() - 7), clr);
         }
         else
         {
            pgraphics->fill_rectangle(::double_rectangle_dimension(0, rect2.top(), CX_BORDER, rect2.height()), clr);
         }
      }
      if (uStyle & CBRS_BORDER_TOP)
      {
         if(uStyle & CBRS_GRIPPER)
         {
            pgraphics->fill_rectangle(
            ::double_rectangle(rectangle.left() + 7,
            rectangle.top(),
            rectangle.right() - 7,
            1),
            rgb(128, 128, 123));
         }
         else
         {
            pgraphics->fill_rectangle(
            ::double_rectangle(rectangle.left(),
            rectangle.top(),
            rectangle.right(),
            1),
            rgb(128, 128, 123));
         }
         //      pgraphics->fill_rectangle(0, 0, rectangle.right(), CY_BORDER, clr);
      }
      if (uStyle & (CBRS_BORDER_LEFT | CBRS_BORDER_TOP))
      {

         if(uStyle & CBRS_GRIPPER)
         {

            auto ppen = øcreate < ::draw2d::pen > ();

            ppen->create_solid(1, clr);

            pgraphics->set(ppen);
            pgraphics->line(
               0, 7,
            7, 0);

         }
      }

      // draw right and bottom
      if (uStyle & CBRS_BORDER_RIGHT)
         pgraphics->fill_rectangle(::double_rectangle(rect1.right(), rect2.top(), -CX_BORDER, rect2.height()), clr);
      if (uStyle & CBRS_BORDER_BOTTOM)
         pgraphics->fill_rectangle(::double_rectangle(0, rect1.bottom(), rectangle.right(), -CY_BORDER), clr);

      if (uStyle & CBRS_BORDER_3D)
      {
         // prepare for hilite lines
//         clr = ::windows_definition::Data.clrBtnHilite;
         clr = rgb(250, 250, 245);

         // draw left and top
         if (uStyle & CBRS_BORDER_LEFT)
            pgraphics->fill_rectangle(::double_rectangle(1, rect2.top(), CX_BORDER, rect2.height()), clr);
         if (uStyle & CBRS_BORDER_TOP)
         {
            if(uStyle & CBRS_GRIPPER)
               pgraphics->fill_rectangle(::double_rectangle(rectangle.left() + 7, rectangle.top() + 1, rectangle.width() - 7, 1), clr);
            else
               pgraphics->fill_rectangle(::double_rectangle(rectangle.left(), rectangle.top() + 1, rectangle.width(), 1), clr);
            //pgraphics->fill_rectangle(0, 1, rectangle.right(), CY_BORDER, clr);
         }

         // draw right and bottom
         if (uStyle & CBRS_BORDER_RIGHT)
            pgraphics->fill_rectangle(::double_rectangle(rectangle.right(), rect2.top(), -CX_BORDER, rect2.height()), clr);
         if (uStyle & CBRS_BORDER_BOTTOM)
            pgraphics->fill_rectangle(::double_rectangle(0, rectangle.bottom(), rectangle.right(), -CY_BORDER), clr);
      }

      if (uStyle & CBRS_BORDER_LEFT)
         //rectangle.left() += ::windows_definition::Data.cxBorder2;
         rectangle.left() += 2;
      if (uStyle & CBRS_BORDER_TOP)
         //rectangle.top() += ::windows_definition::Data.cyBorder2;
         rectangle.top() += 2;
      if (uStyle & CBRS_BORDER_RIGHT)
         //rectangle.right() -= ::windows_definition::Data.cxBorder2;
         rectangle.right() -= 2;
      if (uStyle & CBRS_BORDER_BOTTOM)
         //rectangle.bottom() -= ::windows_definition::Data.cyBorder2;
         rectangle.bottom() -= 2;

#else

      throw ::exception(todo);

#endif

   }

#define CX_GRIPPER  6
#define CY_GRIPPER  6
#define CX_BORDER_GRIPPER 2
#define CY_BORDER_GRIPPER 2

   void DrawGripperElement001(::draw2d::graphics_pointer & pgraphics, int ix, int iy)
   {
      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(ix);
      __UNREFERENCED_PARAMETER(iy);
      /*      pgraphics->SetPixel(ix    , iy + 1, ::windows_definition::Data.clrBtnHilite);
            pgraphics->SetPixel(ix + 1, iy + 1, ::windows_definition::Data.clrBtnHilite);
            pgraphics->SetPixel(ix + 1, iy    , ::windows_definition::Data.clrBtnHilite);
            pgraphics->SetPixel(ix + 2, iy    , ::windows_definition::Data.clrBtnShadow);
            pgraphics->SetPixel(ix + 3, iy + 1, ::windows_definition::Data.clrBtnShadow);
            pgraphics->SetPixel(ix + 3, iy + 2, ::windows_definition::Data.clrBtnShadow);
            pgraphics->SetPixel(ix + 2, iy + 3, ::windows_definition::Data.clrBtnShadow);*/
   }


   void control_bar::DrawGripper(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle& rectangle)
   {

      // only draw the gripper if not floating and gripper is specified
      if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
      {
         // draw the gripper in the border
         if (m_dwStyle & CBRS_ORIENT_HORZ)
         {
            //pgraphics->draw_inset_3d_rectangle(rectangle.left()+CX_BORDER_GRIPPER,
            //   rectangle.top()+m_rectangleBorder.top(),
            //   CX_GRIPPER, rectangle.height()-m_rectangleBorder.top()-m_rectangleBorder.bottom(),
            //   ::windows_definition::Data.clrBtnHilite, ::windows_definition::Data.clrBtnShadow);
            int Δx = CX_GRIPPER / 2;
            int Δy = CY_GRIPPER / 2;
            int ix = rectangle.left() + CX_BORDER_GRIPPER;
            int iy = rectangle.top() + m_rectangleBorder.top() + Δy / 2;
            int cy = rectangle.bottom() - m_rectangleBorder.top() - m_rectangleBorder.bottom() - Δy * 3;

            for(; iy < cy; iy += Δy)
            {
               DrawGripperElement001(pgraphics, ix + Δx, iy);
               iy += Δy;
               DrawGripperElement001(pgraphics, ix,      iy);
            }
            DrawGripperElement001(pgraphics, ix + Δx, iy);
         }
         else
         {
            //         pgraphics->draw_inset_3d_rectangle(rectangle.left()+m_rectangleBorder.top(),
            //            rectangle.top()+CY_BORDER_GRIPPER,
            //            rectangle.width()-m_rectangleBorder.top()-m_rectangleBorder.bottom(), CY_GRIPPER,
            //            ::windows_definition::Data.clrBtnHilite, ::windows_definition::Data.clrBtnShadow);
            int Δx = CX_GRIPPER / 2;
            int Δy = CY_GRIPPER / 2;
            int ix = rectangle.left() + m_rectangleBorder.top() + Δx / 2;
            int iy = rectangle.top() + CY_BORDER_GRIPPER;
            int cx = rectangle.right() - m_rectangleBorder.top() - m_rectangleBorder.bottom() - Δx * 3;

            for(; ix < cx; ix += Δx)
            {
               DrawGripperElement001(pgraphics, ix, iy + Δy);
               ix += Δx;
               DrawGripperElement001(pgraphics, ix, iy);
            }
            DrawGripperElement001(pgraphics, ix, iy + Δy);
         }
      }
   }

   // input int_rectangle should be client int_rectangle int_size
   void control_bar::CalcInsideRect(::draw2d::graphics_pointer& pgraphics, ::int_rectangle& rectangle, bool bHorz) const
   {
      ASSERT_OK(this);
      unsigned int uStyle = m_dwStyle;

      if (uStyle & CBRS_BORDER_LEFT)
//         rectangle.left() += ::windows_definition::Data.cxBorder2;
         rectangle.left() += 2;
      if (uStyle & CBRS_BORDER_TOP)
//         rectangle.top() += ::windows_definition::Data.cyBorder2;
         rectangle.top() += 2;
      if (uStyle & CBRS_BORDER_RIGHT)
//         rectangle.right() -= ::windows_definition::Data.cxBorder2;
         rectangle.right() -= 2;
      if (uStyle & CBRS_BORDER_BOTTOM)
//         rectangle.bottom() -= ::windows_definition::Data.cyBorder2;
         rectangle.bottom() -= 2;

      // insert_at the top and bottom.
      if (bHorz)
      {
         rectangle.left() += m_rectangleBorder.left();
         rectangle.top() += m_rectangleBorder.top();
         rectangle.right() -= m_rectangleBorder.right();
         rectangle.bottom() -= m_rectangleBorder.bottom();
         if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
            rectangle.left() += CX_BORDER_GRIPPER+CX_GRIPPER+CX_BORDER_GRIPPER;
      }
      else
      {
         rectangle.left() += m_rectangleBorder.top();
         rectangle.top() += m_rectangleBorder.left();
         rectangle.right() -= m_rectangleBorder.bottom();
         rectangle.bottom() -= m_rectangleBorder.right();
         if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
            rectangle.top() += CY_BORDER_GRIPPER+CY_GRIPPER+CY_BORDER_GRIPPER;
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   // control_bar diagnostics


//   void control_bar::assert_ok() const
//   {
//      ::user::interaction::assert_ok();
//
//      ASSERT((m_dwStyle & CBRS_ALL) == m_dwStyle);
//   }
//
//   void control_bar::dump(dump_context & dumpcontext) const
//   {
//      ::user::interaction::dump(dumpcontext);
//
//      //dumpcontext << "\nm_cxLeftBorder = " << m_rectangleBorder.left();
//      //dumpcontext << "\nm_cxRightBorder = " << m_rectangleBorder.right();
//      //dumpcontext << "\nm_cyTopBorder = " << m_rectangleBorder.top();
//      //dumpcontext << "\nm_cyBottomBorder = " << m_rectangleBorder.bottom();
//      //dumpcontext << "\nm_cxDefaultGap = " << m_cxDefaultGap;
//      //dumpcontext << "\nm_bAutoDelete = " << m_bAutoDelete;
//
//      //dumpcontext << "\n";
//   }



   ::pointer<::user::frame_window>control_bar::GetDockingFrame()
   {

      auto pframewindow = parent_frame();

      if (!pframewindow)
      {

         pframewindow = m_pframewindowDockSite;

      }

      ASSERT(pframewindow);

      return pframewindow;

   }

   bool control_bar::IsFloating()
   {
      return false;
   }


   unsigned int control_bar::GetBarStyle()
   {

      return m_dwStyle;

   }


   void control_bar::SetBorders(const ::int_rectangle & rectangle)
   {

      SetBorders(rectangle.left(), rectangle.top(), rectangle.right(), rectangle.bottom());

   }


   ::int_rectangle control_bar::GetBorders()
   {

      return m_rectangleBorder;

   }


} // namespace user
