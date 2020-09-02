#include "framework.h"
#include "control_box.h"


namespace experience
{


   dock_manager::dock_manager(::experience::frame_window * pframewindow) :
      object(pframewindow)
   {

      m_iConsiderDockMove = 49;
      m_bPendingCursorPos = false;
      ASSERT(pframewindow != nullptr);
      m_pframewindow = pframewindow;
      m_bDocking = false;
      m_eborder = border_all;

   }


   dock_manager::~dock_manager()
   {

   }


   bool dock_manager::_001OnLButtonDown(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_docking_enabled())
      {

         return false;

      }

      auto pointCursor = pmouse->m_point;

      auto rectWindow = m_pframewindow->layout().sketch().screen_rect();

      auto pointDockOrigin = pointCursor;

      dock_button()->ScreenToClient(pointDockOrigin);

      m_pointCursorDockOrigin = pointDockOrigin;

      m_pointWindowOrigin = rectWindow.top_left();

      m_pointMove = m_pointWindowOrigin;

      m_sizeOrigin = rectWindow.size();

      m_pframewindow->SetCapture();

      m_edisplayOrigin = m_pframewindow->layout().design().display();

      m_mapWorkspaceRect.remove_all();

      m_bDocking = true;

      m_pframewindow->on_start_layout_experience(layout_experience_docking);

      pmouse->m_bRet = true;

      m_iDockMove = 0;

      dock_window(pmouse);

      return true;

   }


   bool dock_manager::dock_window(::message::mouse* pmouse)
   {

      ::point pointCursor = pmouse->m_point;

      ::point point;
      
      ::rect rectDockButtonWindow;

      m_pframewindow->m_pframe->get_control_box()->get_button(::experience::button_dock)->get_window_rect(rectDockButtonWindow);

      ::point pointDock = rectDockButtonWindow.center();

      auto pointMove = m_pointWindowOrigin + (pmouse->m_point - (m_pointWindowOrigin + dock_origin() + m_pointCursorDockOrigin));

      m_pframewindow->_001ScreenToClient(pointDock);

      point = __point(pointCursor - pointDock);

      ::rect rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      ::rect rectEvent = rectWindow;

      rectEvent.move_to(point);

      ::rect rectCursor(pointCursor.x - 1, pointCursor.y - 1, pointCursor.x + 1, pointCursor.y + 1);

      ::rect screen;

      ::rect rectWork;

      int iMonitor = (int)Session.get_best_monitor(screen, rectCursor);

      if (!m_mapWorkspaceRect.lookup(iMonitor, rectWork))
      {

         System.get_wkspace_rect(iMonitor, rectWork);

         m_mapWorkspaceRect.set_at(iMonitor, rectWork);

      }

      int cxCenterArea = rectWork.width() / 2;

      int cyCenterArea = rectWork.height() / 2;

      ::rect rectCenter;

      auto pointScreenCenter = rectWork.center();

      rectCenter.left = pointScreenCenter.x - cxCenterArea / 2;

      rectCenter.top = pointScreenCenter.y - cyCenterArea / 2;

      rectCenter.right = pointScreenCenter.x + cxCenterArea / 2;

      rectCenter.bottom = pointScreenCenter.y + cyCenterArea / 2;

      if (m_pframewindow->layout().design().display() & display_bottom)
      {

         rectCenter.bottom -= cyCenterArea / 4;
         rectCenter.left -= cxCenterArea / 16;
         rectCenter.right += cxCenterArea / 16;

         //output_debug_string("biggerbottomarea\n");

      }
      else
      {

         rectCenter.bottom += cyCenterArea / 8;

      }

      if (m_pframewindow->layout().design().display() & display_top)
      {

         rectCenter.top += cyCenterArea / 4;
         rectCenter.left -= cxCenterArea / 16;
         rectCenter.right += cxCenterArea / 16;

         //output_debug_string("biggertoparea\n");

      }
      else
      {

         rectCenter.top -= cyCenterArea / 8;

      }

      if (m_pframewindow->layout().design().display() & display_right)
      {

         rectCenter.right -= cxCenterArea / 4;
         rectCenter.top -= cyCenterArea / 8;
         rectCenter.bottom += cyCenterArea / 8;

         //output_debug_string("biggerrightarea\n");

      }
      else
      {

         rectCenter.right += cxCenterArea / 8;

      }

      if (m_pframewindow->layout().design().display() & display_left)
      {

         rectCenter.left += cxCenterArea / 4;
         rectCenter.top -= cyCenterArea / 16;
         rectCenter.bottom += cyCenterArea / 16;

         //output_debug_string("biggerleftarea\n");

      }
      else
      {

         rectCenter.left -= cxCenterArea / 8;

      }

      ::rect rectDock;

      e_display edisplayDock = display_none;

      if (rectCenter.contains_x(pointCursor.x))
      {

         if (rectCenter.contains_y(pointCursor.y))
         {

            edisplayDock = ::display_normal;

         }
         else if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::display_full_top;

            rectDock = rect_dim(rectWork.left, rectWork.top, rectWork.width(), rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::display_full_bottom;

            rectDock = rect_dim(rectWork.left, rectWork.top + rectWork.height() / 2, rectWork.width(), rectWork.height() / 2);

         }

      }
      else if (rectCenter.contains_y(pointCursor.y))
      {

         if (pointCursor.x < rectCenter.left)
         {

            edisplayDock = ::display_full_left;

            rectDock = rect_dim(rectWork.left, rectWork.top, rectWork.width() / 2, rectWork.height());

         }
         else if (pointCursor.x > rectCenter.right)
         {

            edisplayDock = ::display_full_right;

            rectDock = rect_dim(rectWork.left + rectWork.width() / 2, rectWork.top, rectWork.width() / 2, rectWork.height());

         }

      }
      else if (pointCursor.x < rectCenter.left)
      {

         if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::display_top_left;

            rectDock = rect_dim(rectWork.left, rectWork.top, rectWork.width() / 2, rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::display_bottom_left;

            rectDock = rect_dim(rectWork.left, rectWork.top + rectWork.height() / 2, rectWork.width() / 2, rectWork.height() / 2);

         }

      }
      else if (pointCursor.x > rectCenter.right)
      {

         if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::display_top_right;

            rectDock = rect_dim(rectWork.left + rectWork.width() / 2, rectWork.top, rectWork.width() / 2, rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::display_bottom_right;

            rectDock = rect_dim(rectWork.left + rectWork.width() / 2, rectWork.top + rectWork.height() / 2, rectWork.width() / 2, rectWork.height() / 2);

         }

      }

      if (edisplayDock == ::display_normal)
      {

         if (m_pframewindow->layout().sketch().display() != display_normal)
         {

            m_pframewindow->set_size(m_pframewindow->m_windowrect.m_rectRestored.size());

         }

         m_pframewindow->move_to(pointMove);

         m_pframewindow->display(display_normal);

         m_pframewindow->set_need_redraw();

         //auto pointMove = point;

         //if (m_pframewindow->GetParent() != nullptr)
         //{

         //   m_pframewindow->GetParent()->_001ScreenToClient(pointMove);

         //}

         //m_pframewindow->order(zorder_top);

         //m_pframewindow->move_to(pointMove);

         //m_pframewindow->set_size(m_pframewindow->m_windowrect.m_rectRestored.size());

         //m_pframewindow->display(display_normal);

         //m_pframewindow->set_need_redraw();

      }
      else if (is_docking_appearance(edisplayDock))
      {

         if (m_iDockMove <= 0 || m_iDockMove >= m_iConsiderDockMove)
         {

            if (m_pframewindow->layout().sketch().display() != edisplayDock || rectDock != rectWindow)
            {

               m_pframewindow->order(zorder_top);

               m_pframewindow->place(rectDock);

               m_pframewindow->display(edisplayDock);

               m_pframewindow->set_need_redraw();

               if (m_iDockMove <= 0)
               {

                  m_bPendingCursorPos = true;

               }

            }

         }

      }

      return true;

   }

   void dock_manager::defer_cursor_pos()
   {

      if (m_bPendingCursorPos)
      {

         m_bPendingCursorPos = false;

         if (window_is_docking())
         {

            auto pointCursor = m_pframewindow->layout().sketch().origin() + (dock_button()->layout().parent_client_rect().origin() + m_pointCursorDockOrigin);

            Session.set_cursor_pos(pointCursor);

         }

      }

   }


   bool dock_manager::_001OnMouseMove(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_docking_enabled())
      {

         return false;

      }

      if (!window_is_docking())
      {

         return false;

      }

      if (pmouse->m_eflagMessage & ::message::flag_synthesized)
      {

         return true;

      }

      pmouse->m_bRet = true;

      __pointer(::user::interaction) puieCapture = Session.GetCapture();

      if (puieCapture == nullptr)
      {

#ifdef LINUX

         // for safety in Linux
         ::release_capture();

#endif

         m_bDocking = false;

         return false;

      }

      __pointer(::user::interaction) puieEventWindow = m_pframewindow;

      if (puieCapture != puieEventWindow)
      {

         if (puieCapture != nullptr && puieCapture == m_pframewindow)
         {

            TRACE("dock_manager::message_handler oswindow ReleaseCapture %x\n", Session.GetCapture().m_p);

            Session.ReleaseCapture();

         }

         return false;

      }

      m_iDockMove++;

      dock_window(pmouse);

      return true;

   }


   bool dock_manager::_001OnLButtonUp(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_docking_enabled())
      {

         return false;

      }

      if (!window_is_docking())
      {

         return false;

      }

      TRACE("dock_manager::message_handler oswindow ReleaseCapture 2 %x\n", Session.GetCapture().m_p);

      m_bDocking = false;

      dock_window(pmouse);



      Session.ReleaseCapture();

      m_pframewindow->on_end_layout_experience(layout_experience_docking);

      return true;

   }


   bool dock_manager::set_frame_window(frame_window * pframewindow)
   {

      m_pframewindow = pframewindow;

      return true;

   }


   //void dock_manager::SetSWPFlags(UINT uiFlags)
   //{

   //   m_uiSWPFlags = uiFlags;
   //   m_uiSWPFlags |= SWP_NOSIZE;
   //   m_uiSWPFlags |= SWP_FRAMECHANGED;
   //   m_uiSWPFlags &= ~SWP_NOMOVE;

   //}


   bool dock_manager::window_is_docking()
   {

      return m_bDocking;

   }


   ::user::button * dock_manager::dock_button()
   {

      return m_pframewindow->m_pframe->m_pcontrolbox->get_button(button_dock);

   }


   ::point dock_manager::dock_origin()
   {

      ::point pointOrigin;

      ::user::interaction * pinteraction = dock_button();

      while (pinteraction != m_pframewindow && pinteraction != nullptr)
      {

         pointOrigin += pinteraction->layout().origin();

         pinteraction = pinteraction->GetParent();

      }

      return pointOrigin;

   }


   eborder dock_manager::get_border_mask()
   {

      return m_eborder;

   }


   void dock_manager::set_border_mask(eborder eborder)
   {

      m_eborder = eborder;

   }


   edock dock_manager::get_dock_mask()
   {

      return m_edock;

   }


   void dock_manager::set_dock_mask(edock edock)
   {

      m_edock = edock;

   }


   bool dock_manager::_001OnTimer(UINT nIDEvent)
   {

      return false;

   }


} // namespace experience



