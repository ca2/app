#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif


namespace experience
{


   size_manager::size_manager(::experience::frame_window * pframewindow) :
      object(pframewindow),
      m_sizeMinimumBorder(33, 33)
   {

      ASSERT(pframewindow != nullptr);

      m_pframewindow = pframewindow;

      m_ehittestSizing = hittest_none;

      m_ehittestCursor = hittest_none;

      SetSWPFlags(0);

      m_egripMask = e_grip_all;

   }


   size_manager::~size_manager()
   {

   }


   bool size_manager::_001OnLButtonDown(::message::mouse * pmouse)
   {

      ASSERT(pmouse->m_id == e_message_left_button_down || pmouse->m_id == e_message_non_client_left_button_down);

      if(!m_pframewindow->is_sizing_enabled())
      {

         return false;

      }

      auto pointCursor = pmouse->m_point;

      m_pointCursorOrigin = pointCursor;

      ::rect rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      m_rectWindowOrigin = rectWindow;

      ::rect rectEvent;

      m_pframewindow->get_window_rect(rectEvent);

      //e_hittest ehittest = _001HitTest(pointCursor);

      e_hittest ehittest = m_ehittestCursor;

      //auto pframewindow = m_pframewindow;

      if(ehittest != hittest_none)
      {

#ifdef WINDOWS_DESKTOP

         ::u32 nHitTest = HTCLIENT;

         switch(ehittest)
         {
         case hittest_sizing_left:
            nHitTest = HTLEFT;
            break;
         case hittest_sizing_top_left:
            nHitTest = HTTOPLEFT;
            break;
         case hittest_sizing_top:
            nHitTest = HTTOP;
            break;
         case hittest_sizing_top_right:
            nHitTest = HTTOPRIGHT;
            break;
         case hittest_sizing_right:
            nHitTest = HTRIGHT;
            break;
         case hittest_sizing_bottom_right:
            nHitTest = HTBOTTOMRIGHT;
            break;
         case hittest_sizing_bottom:
            nHitTest = HTBOTTOM;
            break;
         case hittest_sizing_bottom_left:
            nHitTest = HTBOTTOMLEFT;
            break;
         default:
            break;
         }

#endif

         //if(pframewindow->WfiOnBeginSizing(nHitTest, pointCursor))
         //   return true;
      }

      auto psession = Session;

      if(ehittest != hittest_none)
      {

         m_pframewindow->SetCapture();

         pmouse->m_bRet = true;

      }
      else
      {

         psession->ReleaseCapture();

      }

      pmouse->m_ecursor = translate(ehittest);

      m_ehittestCursor = hittest_none;

      m_ehittestSizing = ehittest;

      if(m_ehittestSizing == hittest_none)
      {

         return false;

      }
      else
      {

         m_pframewindow->on_start_layout_experience(e_layout_experience_sizing);

         m_iPaintCount = 0;

         return true;

      }

   }


   bool size_manager::_001OnMouseMove(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_sizing_enabled())
      {

         return false;

      }

      ASSERT(pmouse->m_id == e_message_mouse_move || pmouse->m_id == e_message_non_client_mouse_move);

      if(m_ehittestSizing != hittest_none)
      {

         size_window(m_ehittestSizing, m_pframewindow, pmouse->m_point, true);

         pmouse->m_ecursor = translate(m_ehittestSizing);

         pmouse->m_lresult = 1;

         pmouse->m_bRet = true;

         return true;

      }

      m_ehittestCursor = _001HitTest(pmouse->m_point);

      if(m_ehittestCursor != hittest_none)
      {
         
         auto ecursor = translate(m_ehittestCursor);

         pmouse->m_ecursor = ecursor;

         pmouse->m_lresult = 1;

         pmouse->m_bRet = true;

         return true;

      }

      return false;

   }


   bool size_manager::_001OnLButtonUp(::message::mouse * pmouse)
   {

      if(!m_pframewindow->is_sizing_enabled())
      {

         return false;

      }

      if(!window_is_sizing())
      {

         return false;

      }

      //bool bApply = !is_docking_appearance(m_pframewindow->layout().sketch().display());

      bool bApply = true;

      return window_stop_sizing(bApply, pmouse);

   }


   bool size_manager::window_stop_sizing(bool bApply, ::message::mouse * pmouse)
   {

      if (m_ehittestSizing == hittest_none)
      {

         return false;

      }

      auto ehittestSizing = m_ehittestSizing;

      m_ehittestSizing = hittest_none;

      auto psession = Session;

      psession->ReleaseCapture();

      if(pmouse)
      {

         pmouse->m_bRet = true;

         if(bApply)
         {

            size_window(ehittestSizing, m_pframewindow, pmouse->m_point, true);

            pmouse->m_lresult = 1;

            pmouse->m_bRet = true;

         }

      }

      m_pframewindow->on_end_layout_experience(e_layout_experience_sizing);

      return true;

   }


   e_cursor size_manager::translate(e_hittest emode)
   {

      switch(emode)
      {
      case hittest_none:
         return cursor_default;
      case hittest_sizing_top_left:
         return cursor_size_top_left;
      case hittest_sizing_top:
         return cursor_size_top;
      case hittest_sizing_top_right:
         return cursor_size_top_right;
      case hittest_sizing_right:
         return cursor_size_right;
      case hittest_sizing_bottom_right:
         return cursor_size_bottom_right;
      case hittest_sizing_bottom:
         return cursor_size_bottom;
      case hittest_sizing_bottom_left:
         return cursor_size_bottom_left;
      case hittest_sizing_left:
         return cursor_size_left;
         break;
      default:
         return cursor_default;
      }

   }


   ::size size_manager::GetMinSize()
   {

      return m_pframewindow->m_pframe->GetMinSize();

   }


   void size_manager::SetSWPFlags(::u32 uFlags)
   {

      m_uiSWPFlags = uFlags;
      m_uiSWPFlags &= ~SWP_NOSIZE & ~SWP_NOMOVE;

   }


   void size_manager::size_window(e_hittest ehittest, ::user::interaction * pframewindow, const ::point & point, bool bTracking)
   {

      bool bSize = true;

      ::rect rectWindow;

      ::rect rectMonitor;

      pframewindow->best_monitor(rectMonitor);

      ::size sizeMin = GetMinSize();

      if(ehittest == hittest_sizing_top_left)
      {
         rectWindow.top = point.y +1;
         rectWindow.left = point.x +1;
         rectWindow.bottom = m_rectWindowOrigin.bottom;
         rectWindow.right = m_rectWindowOrigin.right;
         bSize = !rectWindow.is_empty();
         if(rectWindow.width() < sizeMin.cx)
         {
            rectWindow.left = m_rectWindowOrigin.right - sizeMin.cx;
         }
         if(rectWindow.height() < sizeMin.cy)
         {
            rectWindow.top = m_rectWindowOrigin.bottom - sizeMin.cy;
         }
         rectWindow.left = min(rectWindow.left, rectMonitor.right - m_sizeMinimumBorder.cx);
         rectWindow.top = min(rectWindow.top, rectMonitor.bottom - m_sizeMinimumBorder.cy);
      }
      else if(ehittest == hittest_sizing_top)
      {
         rectWindow.top = point.y +1;
         rectWindow.left = m_rectWindowOrigin.left;
         rectWindow.bottom = m_rectWindowOrigin.bottom;
         rectWindow.right = m_rectWindowOrigin.right;
         if(rectWindow.height() < sizeMin.cy)
         {
            rectWindow.top = m_rectWindowOrigin.bottom - sizeMin.cy;
         }
         rectWindow.top = min(rectWindow.top, rectMonitor.bottom - m_sizeMinimumBorder.cy);
         auto pframewindow = m_pframewindow;
         if (pframewindow->find_i32("ysnap") > 1)
         {
            rectWindow.top -= rectWindow.top % pframewindow->find_i32("ysnap");
         }
      }
      else if(ehittest == hittest_sizing_top_right)
      {
         rectWindow.top = point.y +1;
         rectWindow.left = m_rectWindowOrigin.left;
         rectWindow.bottom = m_rectWindowOrigin.bottom;
         rectWindow.right = point.x;
         if(rectWindow.width() < sizeMin.cx)
         {
            rectWindow.right = m_rectWindowOrigin.left + sizeMin.cx;

         }
         if(rectWindow.height() < sizeMin.cy)
         {
            rectWindow.top = m_rectWindowOrigin.bottom - sizeMin.cy;
         }
         rectWindow.right = max(rectWindow.right, rectMonitor.left + m_sizeMinimumBorder.cx);
         rectWindow.top = min(rectWindow.top, rectMonitor.bottom - m_sizeMinimumBorder.cy);
      }
      else if(ehittest == hittest_sizing_right)
      {
         rectWindow.top = m_rectWindowOrigin.top;
         rectWindow.left = m_rectWindowOrigin.left;
         rectWindow.bottom = m_rectWindowOrigin.bottom;
         rectWindow.right = point.x;
         if(rectWindow.width() < sizeMin.cx)
         {
            rectWindow.right = m_rectWindowOrigin.left + sizeMin.cx;

         }
         rectWindow.right = max(rectWindow.right, rectMonitor.left + m_sizeMinimumBorder.cx);
      }
      else if(ehittest == hittest_sizing_bottom_right)
      {
         rectWindow.top = m_rectWindowOrigin.top;
         rectWindow.left = m_rectWindowOrigin.left;
         rectWindow.bottom = point.y;
         rectWindow.right = point.x;
         if (rectWindow.width() < sizeMin.cx)
         {
            rectWindow.right = m_rectWindowOrigin.left + sizeMin.cx;

         }
         if (m_pframewindow->m_bDerivedHeight)
         {
            
            int iWidth = rectWindow.width();
            
            int iDerivedHeight = m_pframewindow->get_derived_height(iWidth);
            
            int iHeight = m_pframewindow->m_pframe->adjust_client_height(iDerivedHeight);

            if (iHeight < sizeMin.cy)
            {
               
               rectWindow.bottom = m_rectWindowOrigin.top + sizeMin.cy;

               rectWindow.right = m_rectWindowOrigin.left + m_pframewindow->m_pframe->adjust_client_width(m_pframewindow->get_derived_width(sizeMin.cy));
               
            }
            else
            {
               
               rectWindow.bottom = m_rectWindowOrigin.top + iHeight;

            }
            
         }
         else
         {
            if (rectWindow.height() < sizeMin.cy)
            {
               rectWindow.bottom = m_rectWindowOrigin.top + sizeMin.cy;
            }
            rectWindow.right = max(rectWindow.right, rectMonitor.left + m_sizeMinimumBorder.cx);
            rectWindow.bottom = max(rectWindow.bottom, rectMonitor.top + m_sizeMinimumBorder.cy);
         }
      }
      else if(ehittest == hittest_sizing_bottom)
      {
         rectWindow.top = m_rectWindowOrigin.top;
         rectWindow.left = m_rectWindowOrigin.left;
         rectWindow.bottom = point.y;
         rectWindow.right = m_rectWindowOrigin.right;
         if(rectWindow.height() < sizeMin.cy)
         {
            rectWindow.bottom = m_rectWindowOrigin.top + sizeMin.cy;
         }
         rectWindow.bottom = max(rectWindow.bottom, rectMonitor.top + m_sizeMinimumBorder.cy);
         auto pframewindow = m_pframewindow;

         if (pframewindow->find_i32("ysnap") > 1)
         {
            int h = rectWindow.height();
            h -= rectWindow.height() % pframewindow->find_i32("ysnap");
            rectWindow.bottom = rectWindow.top + h;
         }
      }
      else if(ehittest == hittest_sizing_bottom_left)
      {
         rectWindow.top = m_rectWindowOrigin.top;
         rectWindow.left = point.x +1;
         rectWindow.bottom = point.y;
         rectWindow.right = m_rectWindowOrigin.right;
         if(rectWindow.width() < sizeMin.cx)
         {
            rectWindow.left = m_rectWindowOrigin.right - sizeMin.cx;

         }
         if(rectWindow.height() < sizeMin.cy)
         {
            rectWindow.bottom = m_rectWindowOrigin.top + sizeMin.cy;
         }
         rectWindow.left = min(rectWindow.left, rectMonitor.right - m_sizeMinimumBorder.cx);
         rectWindow.bottom = max(rectWindow.bottom, rectMonitor.top + m_sizeMinimumBorder.cy);
      }
      else if(ehittest == hittest_sizing_left)
      {
         rectWindow.top = m_rectWindowOrigin.top;
         rectWindow.left = point.x +1;
         rectWindow.bottom = m_rectWindowOrigin.bottom;
         rectWindow.right = m_rectWindowOrigin.right;
         if(rectWindow.width() < sizeMin.cx)
         {
            rectWindow.left = m_rectWindowOrigin.right - sizeMin.cx;

         }
         rectWindow.left = min(rectWindow.left, rectMonitor.right - m_sizeMinimumBorder.cx);
      }
      else
      {
         bSize = false;
      }

      move_window(m_pframewindow, rectWindow);

      NotifyFramework((e_hittest)ehittest);

   }


   void size_manager::move_window(::user::interaction * pframewindow, const ::rect & rect)
   {

      auto rectWindow = rect;

      auto sizeMin = GetMinSize();

      if (rectWindow.width() < sizeMin.cx || rectWindow.height() < sizeMin.cy)
      {

         return;

      }

      ::rect rectWindowNow;

      m_pframewindow->get_window_rect(rectWindowNow);

      if (rectWindowNow == rectWindow)
      {

         return;

      }

      m_pframewindow->start_layout();

      if(m_pframewindow->layout().is_zoomed())
      {

         m_pframewindow->display(e_display_restore);

      }

      ::rect rectBefore;

      pframewindow->get_window_rect(rectBefore);

      ::rect rectAfter = rectWindow;

      ::rect rectParentClient = rectAfter;

      if(m_pframewindow->get_parent() != nullptr)
      {

         m_pframewindow->get_parent()->_001ScreenToClient(rectParentClient);

      }

      ::rect rectTotal;

      rectTotal.unite(rectBefore, rectAfter);

      m_pframewindow->m_rectPending.unite(rectBefore, rectAfter);

      {

         sync_lock sl(pframewindow->mutex());

         pframewindow->place(rectParentClient);

         TRACE("Size Manager Changed (%d, %d)", rectParentClient.right, rectParentClient.bottom);

         pframewindow->display();

         pframewindow->set_need_layout();

         pframewindow->set_need_redraw();

         pframewindow->post_redraw();

      }

   }


   bool size_manager::window_is_sizing()
   {

      return m_ehittestSizing != hittest_none;

   }


   void size_manager::SetGripMask(enum_grip egrip)
   {

      m_egripMask = egrip;

   }


   enum_grip size_manager::GetGripMask()
   {

      return m_egripMask;

   }


   enum_grip size_manager::hittest_mode_grip(e_hittest emode)
   {

      enum_grip egrip;

      if(emode == hittest_sizing_top)
         egrip = e_grip_top;
      else if(emode == hittest_sizing_top_left)
         egrip = e_grip_top_left;
      else if(emode == hittest_sizing_left)
         egrip = e_grip_left;
      else if(emode == hittest_sizing_bottom_left)
         egrip = e_grip_bottom_left;
      else if(emode == hittest_sizing_bottom)
         egrip = e_grip_bottom;
      else if(emode == hittest_sizing_bottom_right)
         egrip = e_grip_bottom_right;
      else if(emode == hittest_sizing_right)
         egrip = e_grip_right;
      else if(emode == hittest_sizing_top_right)
         egrip = e_grip_top_right;
      else
         egrip = e_grip_none;
      return egrip;

   }


   void size_manager::NotifyFramework(e_hittest emode)
   {

      UNREFERENCED_PARAMETER(emode);

   }


   e_hittest size_manager::_001HitTest(const ::point & pointCursor)
   {
      e_hittest ehittest = m_pframewindow->_001HitTest(pointCursor);
      switch(ehittest)
      {
      case hittest_sizing_left:
      case hittest_sizing_top_left:
      case hittest_sizing_top:
      case hittest_sizing_top_right:
      case hittest_sizing_right:
      case hittest_sizing_bottom_right:
      case hittest_sizing_bottom:
      case hittest_sizing_bottom_left:
         return ehittest;
      default:
         return hittest_none;
      }

   }


   bool size_manager::set_frame_window(frame_window * pframewindow)
   {

      m_pframewindow = pframewindow;

      return true;

   }


} // namespace experience



