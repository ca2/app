#include "framework.h"
#include "base/user/experience/_experience.h"


namespace experience
{

   
   move_manager::move_manager()
   {

      m_iConsiderMove = 0;
      m_bMoving = false;
      //SetSWPFlags(0);
      m_eborderMask = e_border_all;

   }


   move_manager::~move_manager()
   {

   }


   ::e_status move_manager::initialize_move_manager(::experience::frame_window* pframewindow)
   {

      auto estatus = ::object::initialize(pframewindow);

      if (!estatus)
      {

         return estatus;

      }

      m_pframewindow = pframewindow;

      return estatus;

   }


   bool move_manager::on_message_left_button_down(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      m_stateBefore = m_pframewindow->layout().sketch();

      auto pointCursor = pmouse->m_point;

      ::rectangle_i32 rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      //if(m_pframewindow->layout().design().display() != ::e_display_normal && m_pframewindow->layout().design().display() != ::e_display_minimal)
      //{

      //   auto pointRate = rectWindow.to_point_rate(pointCursor);

      //   auto pointRelative = m_pframewindow->m_windowrect.m_rectRestored.from_point_rate(pointRate);

      //   point_i32 pointMove = __point(pointCursor - __point(pointRelative -
      //      m_pframewindow->m_windowrect.m_rectRestored.origin()));

      //   m_pframewindow->move_to(pointMove);

      //   rectWindow.top_left() = pointMove;

      //   m_pframewindow->set_size(m_pframewindow->m_windowrect.m_rectRestored.size());

      //   m_pframewindow->display(::e_display_normal);

      //}

      m_pointCursorOrigin = pointCursor;

      m_pointWindowOrigin = rectWindow.top_left();

      m_pointMove = m_pointWindowOrigin;

      m_pframewindow->set_mouse_capture();

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

      if (pframewindow->get_parent() != nullptr)
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


   bool move_manager::on_message_left_button_up(::message::mouse * pmouse)
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

      __pointer(::base::session) psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

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

               //auto psession = get_session();

               //auto puser = psession->user();

               //auto pwindowing = puser->windowing();

               //pwindowing->set_cursor_pos(pmouse->m_point);

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


   //void move_manager::SetSWPFlags(::u32 uFlags)
   //{
   //   m_uiSWPFlags = uFlags;
   //   m_uiSWPFlags |= SWP_NOSIZE;
   //   m_uiSWPFlags |= SWP_FRAMECHANGED;
   //   m_uiSWPFlags &= ~SWP_NOMOVE;

   //}



//#ifdef WINDOWS_DESKTOP
//
//      bool CALLBACK UpdateCurrentAreaEnumWindowsProc(
//      oswindow oswindow,
//      LPARAM lParam)
//      {
//         UNREFERENCED_PARAMETER(lParam);
//         //      oswindow oswindowParam= lParam;
//         //u32 dwThreadId;
//         //u32 dwProcessId;
//         //HICON hicon16;
//         //HICON hicon48;
//         ::rectangle_i32 rectWindow;
//         ::GetWindowRect(oswindow, &rectWindow);
//         HRGN hrgn = ::CreateRectRgnIndirect(&rectWindow);
//         ::GetWindowRgn(oswindow, hrgn);
//         //      HRGN hrgnNew = ::CreateRectRgn(0, 0, 0, 0);;
//         /*      ::CombineRgn(hrgnNew, (HRGN)g_rgnTotal->get_os_data(), hrgn, RGN_AND);
//         ::set_need_redraw(oswindow, nullptr, nullptr, RDW_INVALIDATE);
//         ::CombineRgn((HRGN)g_rgnTotal->get_os_data(),( HRGN)g_rgnTotal->get_os_data(), hrgnNew, ::draw2d::region::combine_exclude);
//         ::DeleteObject(hrgn);
//         ::DeleteObject(hrgnNew);*/
//
//         ::rectangle_i32 rectangle;
//         /*      if(g_rgnTotal->GetRgnBox(rectangle) == NULLREGION)
//         return false;
//         else
//         return true;*/
//         /*__pointer(::user::interaction) pframewindow = ::user::interaction::from_handle_dup;
//         if(pframewindow == nullptr)
//         return true;
//         //HICON hicon = pframewindow->GetIcon(false);
//         //if(hicon == nullptr)
//         //{
//         //hicon = pframewindow->GetIcon(true);
//         //}
//         /*i32 iStyle = pframewindow->GetStyle();
//         i32 iStyleEx = pframewindow->GetExStyle();
//         if(pframewindow->GetSafeoswindow_() != pview->get_parent_frame()->GetSafeoswindow_()
//         && (iStyle & WS_VISIBLE)
//         && !(iStyleEx & WS_EX_TOOLWINDOW)
//         &&((iStyleEx & WS_EX_APPWINDOW)
//         || (!(iStyle & WS_CHILD)
//         && pframewindow->get_owner() == nullptr)))
//         {
//         if(!pview->m_areaa.Contains(pframewindow->GetSafeoswindow_(), pview->m_iArea))
//         pview->m_areaa[pview->m_iArea].m_oswindowa.add(pframewindow->GetSafeoswindow_());
//         }*/
//         return true;
//      }
//
//#endif

//      void move_manager::MoveWindow(void * oswindow, const ::point_i32 & point)
//      {
//
//         __pointer(::user::interaction) pframewindow = psystem->ui_from_handle(oswindow);
//
//
//         ::rectangle_i32 rectWindow;
//         pframewindow->get_window_rect(rectWindow);
//
//
//#ifdef WINDOWS_DESKTOP
//
//         critical_section_lock synchronizationlock(m_pframewindow->m_pimpl->cs_display());
//         //m_pframewindow->m_rectParentClient.move_to(point_i64(point));
//         m_pframewindow->m_pimpl->_001UpdateWindow();
//
//#else
//
//         pframewindow->order_top();
//
//         pframewindow->move_to(point);
//
//         pframewindow->set_size(rectWindow.size());
//
//         pframewindow->display();
//
//#endif
//
//
//         m_pframewindow->m_pframe->OnMove(m_pframewindow);
//
//      }


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



