#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif


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
      m_eborder = e_border_all;

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

      m_pframewindow->on_start_layout_experience(e_layout_experience_docking);

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

      m_pframewindow->m_pframe->get_control_box()->get_button(e_button_dock)->get_window_rect(rectDockButtonWindow);

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

      auto psession = Session;

      int iMonitor = (int)psession->get_best_monitor(screen, rectCursor);

      if (!m_mapWorkspaceRect.lookup(iMonitor, rectWork))
      {

         psession->get_wkspace_rect(iMonitor, rectWork);

         m_mapWorkspaceRect.set_at(iMonitor, rectWork);

      }

      if (rectWork.is_empty())
      {

         __throw(::exception::exception(error_failed));

      }

      int cxCenterArea = rectWork.width() / 2;

      int cyCenterArea = rectWork.height() / 2;

      ::rect rectCenter;

      auto pointScreenCenter = rectWork.center();

      rectCenter.left = pointScreenCenter.x - cxCenterArea / 2;

      rectCenter.top = pointScreenCenter.y - cyCenterArea / 2;

      rectCenter.right = pointScreenCenter.x + cxCenterArea / 2;

      rectCenter.bottom = pointScreenCenter.y + cyCenterArea / 2;

      if (m_pframewindow->layout().design().display() & e_display_bottom)
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

      if (m_pframewindow->layout().design().display() & e_display_top)
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

      if (m_pframewindow->layout().design().display() & e_display_right)
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

      if (m_pframewindow->layout().design().display() & e_display_left)
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

      enum_display edisplayDock = e_display_none;

      enum_display edisplayOld = m_pframewindow->layout().sketch().display();

      ::rect rectScreenOld = m_pframewindow->layout().sketch().screen_rect();

      if (rectCenter.contains_x(pointCursor.x))
      {

         if (rectCenter.contains_y(pointCursor.y))
         {

            edisplayDock = ::e_display_normal;

         }
         else if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::e_display_full_top;

            rectDock = rect_dim(rectWork.left, rectWork.top, rectWork.width(), rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::e_display_full_bottom;

            rectDock = rect_dim(rectWork.left, rectWork.top + rectWork.height() / 2, rectWork.width(), rectWork.height() / 2);

         }

      }
      else if (rectCenter.contains_y(pointCursor.y))
      {

         if (pointCursor.x < rectCenter.left)
         {

            edisplayDock = ::e_display_full_left;

            rectDock = rect_dim(rectWork.left, rectWork.top, rectWork.width() / 2, rectWork.height());

         }
         else if (pointCursor.x > rectCenter.right)
         {

            edisplayDock = ::e_display_full_right;

            rectDock = rect_dim(rectWork.left + rectWork.width() / 2, rectWork.top, rectWork.width() / 2, rectWork.height());

         }

      }
      else if (pointCursor.x < rectCenter.left)
      {

         if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::e_display_top_left;

            rectDock = rect_dim(rectWork.left, rectWork.top, rectWork.width() / 2, rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::e_display_bottom_left;

            rectDock = rect_dim(rectWork.left, rectWork.top + rectWork.height() / 2, rectWork.width() / 2, rectWork.height() / 2);

         }

      }
      else if (pointCursor.x > rectCenter.right)
      {

         if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::e_display_top_right;

            rectDock = rect_dim(rectWork.left + rectWork.width() / 2, rectWork.top, rectWork.width() / 2, rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::e_display_bottom_right;

            rectDock = rect_dim(rectWork.left + rectWork.width() / 2, rectWork.top + rectWork.height() / 2, rectWork.width() / 2, rectWork.height() / 2);

         }

      }

      if (edisplayDock == ::e_display_normal)
      {

         bool bChange = false;

         if (edisplayOld != e_display_normal)
         {

            m_pframewindow->set_size(m_pframewindow->m_windowrect.m_rectRestored.size());

            bChange = true;

         }
         else
         {

            ::rect rectNew(pointMove, m_pframewindow->m_windowrect.m_rectRestored.size());

            rectNew._001Constraint(rectWork);

            if(rectNew != rectScreenOld)
            {

               m_pframewindow->move_to(pointMove);

               bChange = true;

            }

         }

         if(bChange)
         {

            m_pframewindow->display(e_display_normal);

            m_pframewindow->set_need_redraw();

            m_pframewindow->post_redraw();

         }

      }
      else if (is_docking_appearance(edisplayDock))
      {

         //if (m_iDockMove <= 0 || m_iDockMove >= m_iConsiderDockMove)
         {

            if (edisplayDock == edisplayOld || rectDock != rectWindow)
            {

               m_pframewindow->order(zorder_top);

               m_pframewindow->place(rectDock);

               m_pframewindow->display(edisplayDock);

               m_pframewindow->set_need_redraw();

               m_pframewindow->post_redraw();

               //if (m_iDockMove <= 0)
               {

                  m_bPendingCursorPos = true;

               }

            }

         }

      }

      return true;

   }


   //void dock_manager::defer_cursor_pos()
   //{

   //   if (m_bPendingCursorPos)
   //   {

   //      m_bPendingCursorPos = false;

   //      //if (window_is_docking())
   //      //{

   //      //   auto pointCursor = m_pframewindow->layout().sketch().origin() + (dock_button()->layout().parent_client_rect().origin() + m_pointCursorDockOrigin);

   //      //   auto psession = Session;

   //      //   psession->set_cursor_pos(pointCursor);

   //      //}

   //   }

   //}


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

      auto psession = Session;

      __pointer(::user::interaction) puieCapture = psession->GetCapture();

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

            TRACE("dock_manager::message_handler oswindow ReleaseCapture %x\n", psession->GetCapture().m_p);

            auto psession = Session;

            psession->ReleaseCapture();

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

      auto psession = Session;

      TRACE("dock_manager::message_handler oswindow ReleaseCapture 2 %x\n", psession->GetCapture().m_p);

      m_bDocking = false;

      dock_window(pmouse);

      psession->ReleaseCapture();

      m_pframewindow->on_end_layout_experience(e_layout_experience_docking);

      return true;

   }


   bool dock_manager::set_frame_window(frame_window * pframewindow)
   {

      m_pframewindow = pframewindow;

      return true;

   }


   //void dock_manager::SetSWPFlags(::u32 uFlags)
   //{

   //   m_uiSWPFlags = uFlags;
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

      return m_pframewindow->m_pframe->m_pcontrolbox->get_button(e_button_dock);

   }


   ::point dock_manager::dock_origin()
   {

      ::point pointOrigin;

      ::user::interaction * pinteraction = dock_button();

      while (pinteraction != m_pframewindow && pinteraction != nullptr)
      {

         pointOrigin += pinteraction->layout().origin();

         pinteraction = pinteraction->get_parent();

      }

      return pointOrigin;

   }


   e_border dock_manager::get_border_mask()
   {

      return m_eborder;

   }


   void dock_manager::set_border_mask(const ::e_border & eborder)
   {

      m_eborder = eborder;

   }


   e_dock dock_manager::get_dock_mask()
   {

      return m_edock;

   }


   void dock_manager::set_dock_mask(e_dock edock)
   {

      m_edock = edock;

   }


   bool dock_manager::_001OnTimer(::u32 uEvent)
   {

      return false;

   }


} // namespace experience



