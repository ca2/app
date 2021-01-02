#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif


namespace experience
{



      move_manager::move_manager(::experience::frame_window * pframewindow) :
         object(pframewindow)
      {
         m_iConsiderMove = 0;
         ASSERT(pframewindow != nullptr);
         m_pframewindow = pframewindow;
         m_bMoving = false;
         SetSWPFlags(0);
         m_eborderMask = e_border_all;

      }


      move_manager::~move_manager()
      {

      }


      bool move_manager::_001OnLButtonDown(::message::mouse * pmouse)
      {

         if (!m_pframewindow->is_moving_enabled())
         {

            return false;

         }

         m_stateBefore = m_pframewindow->layout().sketch();

         auto pointCursor = pmouse->m_point;

         ::rect rectWindow;

         m_pframewindow->get_window_rect(rectWindow);

         //if(m_pframewindow->layout().design().display() != ::e_display_normal && m_pframewindow->layout().design().display() != ::e_display_minimal)
         //{

         //   auto pointRate = rectWindow.to_point_rate(pointCursor);

         //   auto pointRelative = m_pframewindow->m_windowrect.m_rectRestored.from_point_rate(pointRate);

         //   point pointMove = __point(pointCursor - __point(pointRelative -
         //      m_pframewindow->m_windowrect.m_rectRestored.origin()));

         //   m_pframewindow->move_to(pointMove);

         //   rectWindow.top_left() = pointMove;

         //   m_pframewindow->set_size(m_pframewindow->m_windowrect.m_rectRestored.size());

         //   m_pframewindow->display(::e_display_normal);

         //}

         m_pointCursorOrigin = pointCursor;

         m_pointWindowOrigin = rectWindow.top_left();

         m_pointMove = m_pointWindowOrigin;

         m_pframewindow->SetCapture();

         m_iConsiderMove = 0;

         m_bMoving = true;

         m_pframewindow->on_start_layout_experience(e_layout_experience_moving);

         pmouse->m_bRet = true;

         return true;

      }


      bool move_manager::_001OnMouseMove(::message::mouse * pmouse)
      {

         if (!m_pframewindow->is_moving_enabled())
         {

            return false;

         }

         ASSERT(pmouse->m_id == e_message_mouse_move || pmouse->m_id == e_message_non_client_mouse_move);

         if (!window_is_moving())
         {

            return false;

         }

         auto pframewindow = m_pframewindow;

         auto pointMove = m_pointWindowOrigin + (pmouse->m_point - m_pointCursorOrigin);

         if (pframewindow->GetParent() != nullptr)
         {

            pframewindow->_001ScreenToClient(&pointMove);

         }

         if (pframewindow->find_i32("ysnap") > 1)
         {

            pointMove.y -= pointMove.y % pframewindow->find_i32("ysnap");

         }

         m_pointMove = pointMove;

         m_iConsiderMove++;

         pframewindow->start_layout();

         if (::is_docking_appearance(pframewindow->layout().sketch().display()))
         {

            pframewindow->m_pframe->defer_frame_placement_snapping();

         }
         else
         {

            pframewindow->move_to(pointMove.x, pointMove.y);

         }

         pframewindow->set_layout_ready();

         pframewindow->set_need_redraw();

         pframewindow->post_redraw();

         pmouse->m_bRet = true;

         return true;

      }


      bool move_manager::_001OnLButtonUp(::message::mouse * pmouse)
      {

         if (!m_pframewindow->is_moving_enabled())
         {

            return false;

         }

         if (!window_is_moving())
         {

            return false;

         }

         bool bApply = !is_docking_appearance(m_pframewindow->layout().sketch().display());

         window_stop_moving(bApply, pmouse);

         return true;

      }



      bool move_manager::window_stop_moving(bool bApply, ::message::mouse * pmouse)
      {

         if (!m_bMoving)
         {

            return false;

         }

         m_bMoving = false;

         auto psession = Session;

         psession->ReleaseCapture();

         if (!consider_move())
         {

            m_pframewindow->layout().sketch() = m_stateBefore;

            m_pframewindow->set_layout_ready();

            m_pframewindow->set_need_redraw();

         }
         else if (bApply)
         {

            auto rectRequest = m_pframewindow->layout().sketch().screen_rect();

            index iMatchingMonitor = m_pframewindow->good_move(rectRequest, nullptr);

            if (iMatchingMonitor >= 0)
            {

               if (!pmouse)
               {

                  pmouse->m_point = -m_pointWindowOrigin + rectRequest.top_left() + m_pointCursorOrigin;

                  psession->set_cursor_pos(pmouse->m_point);

               }

            }

         }

         m_pframewindow->on_end_layout_experience(e_layout_experience_moving);

         return true;

      }


      bool move_manager::set_frame_window(frame_window * pframewindow)
      {

         m_pframewindow = pframewindow;

         return true;

      }


      void move_manager::SetSWPFlags(::u32 uFlags)
      {
         m_uiSWPFlags = uFlags;
         m_uiSWPFlags |= SWP_NOSIZE;
         m_uiSWPFlags |= SWP_FRAMECHANGED;
         m_uiSWPFlags &= ~SWP_NOMOVE;

      }



#ifdef WINDOWS_DESKTOP

      bool CALLBACK UpdateCurrentAreaEnumWindowsProc(
      oswindow oswindow,
      LPARAM lParam)
      {
         UNREFERENCED_PARAMETER(lParam);
         //      oswindow oswindowParam= lParam;
         //u32 dwThreadId;
         //u32 dwProcessId;
         //HICON hicon16;
         //HICON hicon48;
         ::rect rectWindow;
         ::GetWindowRect(oswindow, &rectWindow);
         HRGN hrgn = ::CreateRectRgnIndirect(&rectWindow);
         ::GetWindowRgn(oswindow, hrgn);
         //      HRGN hrgnNew = ::CreateRectRgn(0, 0, 0, 0);;
         /*      ::CombineRgn(hrgnNew, (HRGN)g_rgnTotal->get_os_data(), hrgn, RGN_AND);
         ::set_need_redraw(oswindow, nullptr, nullptr, RDW_INVALIDATE);
         ::CombineRgn((HRGN)g_rgnTotal->get_os_data(),( HRGN)g_rgnTotal->get_os_data(), hrgnNew, ::draw2d::region::combine_exclude);
         ::DeleteObject(hrgn);
         ::DeleteObject(hrgnNew);*/

         ::rect rect;
         /*      if(g_rgnTotal->GetRgnBox(rect) == NULLREGION)
         return FALSE;
         else
         return TRUE;*/
         /*__pointer(::user::interaction) pframewindow = ::user::interaction::from_handle_dup;
         if(pframewindow == nullptr)
         return TRUE;
         //HICON hicon = pframewindow->GetIcon(FALSE);
         //if(hicon == nullptr)
         //{
         //hicon = pframewindow->GetIcon(TRUE);
         //}
         /*i32 iStyle = pframewindow->GetStyle();
         i32 iStyleEx = pframewindow->GetExStyle();
         if(pframewindow->GetSafeoswindow_() != pview->GetParentFrame()->GetSafeoswindow_()
         && (iStyle & WS_VISIBLE)
         && !(iStyleEx & WS_EX_TOOLWINDOW)
         &&((iStyleEx & WS_EX_APPWINDOW)
         || (!(iStyle & WS_CHILD)
         && pframewindow->GetOwner() == nullptr)))
         {
         if(!pview->m_areaa.Contains(pframewindow->GetSafeoswindow_(), pview->m_iArea))
         pview->m_areaa[pview->m_iArea].m_oswindowa.add(pframewindow->GetSafeoswindow_());
         }*/
         return TRUE;
      }

#endif

      void move_manager::MoveWindow(void * oswindow, const ::point & point)
      {

         __pointer(::user::interaction) pframewindow = System.ui_from_handle(oswindow);


         ::rect rectWindow;
         pframewindow->get_window_rect(rectWindow);


#ifdef WINDOWS_DESKTOP

         cslock sl(m_pframewindow->m_pimpl->cs_display());
         //m_pframewindow->m_rectParentClient.move_to(point64(point));
         m_pframewindow->m_pimpl->_001UpdateWindow();

#else

         pframewindow->order_top();

         pframewindow->move_to(point);

         pframewindow->set_size(rectWindow.size());

         pframewindow->display();

#endif


         m_pframewindow->m_pframe->OnMove(m_pframewindow);

      }


      bool move_manager::window_is_moving()
      {

         return m_bMoving;

      }


      bool move_manager::consider_move()
      {

         return m_iConsiderMove > 10;

      }


      e_border move_manager::GetBorderMask()
      {

         return m_eborderMask;

      }


      void move_manager::SetBorderMask(const e_border & emask)
      {

         m_eborderMask = emask;

      }


      bool move_manager::_001OnTimer(::u32 uEvent)
      {

         return false;

      }


} // namespace experience



