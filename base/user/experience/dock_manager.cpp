#include "framework.h"
#include "base/user/experience/_experience.h"


namespace experience
{


   dock_manager::dock_manager()
   {

      m_iConsiderDockMove = 49;
      m_bPendingCursorPos = false;
      m_bDocking = false;
      m_eborder = e_border_all;

   }


   dock_manager::~dock_manager()
   {

   }


   ::e_status dock_manager::initialize_dock_manager(::experience::frame_window* pframewindow)
   {

      auto estatus = channel::initialize(pframewindow);

      if (!estatus)
      {

         return estatus;

      }

      m_pframewindow = pframewindow;

      return estatus;

   }


   void dock_manager::dock_button_on_message_left_button_down(::message::message *pmessage)
   {

      if (!m_pframewindow->WfiOnStartDock())
      {

         return;

      }

      __pointer(::message::mouse) pmouse(pmessage);

      if (!m_pframewindow->is_docking_enabled())
      {

         return;

      }

      pmouse->previous();

      auto pointCursor = pmouse->m_point;

      auto rectWindow = m_pframewindow->layout().sketch().screen_rect();

      auto pointDockOrigin = pointCursor;

      dock_button()->ScreenToClient(pointDockOrigin);

      m_pointCursorDockOrigin = pointDockOrigin;

      m_pointWindowOrigin = rectWindow.top_left();

      m_pointMove = m_pointWindowOrigin;

      m_sizeOrigin = rectWindow.size();

      dock_button()->set_mouse_capture();

      auto pwindow = m_pframewindow->window();

      if(!pwindow->has_mouse_capture())
      {

         m_pframewindow->set_mouse_capture();

      }

      m_edisplayOrigin = m_pframewindow->layout().design().display();

      m_mapWorkspaceRect.erase_all();

      m_bDocking = true;

      m_pframewindow->on_start_layout_experience(e_layout_experience_docking);

      pmouse->m_bRet = true;

      m_iDockMove = 0;

      dock_window(pmouse);

   }


   bool dock_manager::dock_window(::message::mouse* pmouse)
   {

      ::point_i32 pointCursor = pmouse->m_point;

      ::point_i32 point;

      ::rectangle_i32 rectDockButtonWindow;

      m_pframewindow->m_pframe->get_control_box()->get_button(e_button_dock)->get_window_rect(rectDockButtonWindow);

      ::point_i32 pointDock = rectDockButtonWindow.center();

      auto pointMove = m_pointWindowOrigin + (pmouse->m_point - (m_pointWindowOrigin + dock_origin() + m_pointCursorDockOrigin));

      m_pframewindow->_001ScreenToClient(pointDock);

      point = __point(pointCursor - pointDock);

      ::rectangle_i32 rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      ::rectangle_i32 rectEvent = rectWindow;

      rectEvent.move_to(point);

      ::rectangle_i32 rectCursor(pointCursor.x - 1, pointCursor.y - 1, pointCursor.x + 1, pointCursor.y + 1);

      ::rectangle_i32 screen;

      ::rectangle_i32 rectWork;

      __pointer(::base::session) psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      int iMonitor = (int)pdisplay->get_best_monitor(screen, rectCursor);

      if (!m_mapWorkspaceRect.lookup(iMonitor, rectWork))
      {

         pdisplay->get_workspace_rectangle(iMonitor, rectWork);

         m_mapWorkspaceRect.set_at(iMonitor, rectWork);

      }

      if (rectWork.is_empty())
      {

         __throw(error_failed);

      }

      int cxCenterArea = rectWork.width() / 2;

      int cyCenterArea = rectWork.height() / 2;

      ::rectangle_i32 rectCenter;

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

      ::rectangle_i32 rectDock;

      enum_display edisplayDock = e_display_none;

      enum_display edisplayOld = m_pframewindow->layout().sketch().display();

      ::rectangle_i32 rectScreenOld = m_pframewindow->layout().sketch().screen_rect();

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

            ::rectangle_i32 rectNew(pointMove, m_pframewindow->m_windowrect.m_rectRestored.size());

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

               m_pframewindow->order(e_zorder_top);

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

   //      //   auto psession = get_session();

   //      //   psession->set_cursor_pos(pointCursor);

   //      //}

   //   }

   //}


   void dock_manager::dock_button_on_message_mouse_move(::message::message *pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (!m_pframewindow->is_docking_enabled())
      {

         return;

      }

      if (!window_is_docking())
      {

         return;

      }

      if (pmouse->m_eflagMessage & ::message::flag_synthesized)
      {

         pmessage->m_bRet = false;

         return;

      }

      auto pwindow = m_pframewindow->window();

      if (!pwindow || !pwindow->has_mouse_capture())
      {

         return;

      }

      m_iDockMove++;

      dock_window(pmouse);

      pmessage->m_bRet = true;

   }


   void dock_manager::dock_button_on_message_left_button_up(::message::message *pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (!m_pframewindow->is_docking_enabled())
      {

         return;

      }

      if (!window_is_docking())
      {

         return;

      }

      __pointer(::base::session) psession = get_session();

      auto puser = psession->user();

      auto puserinteractionCapture = puser->get_mouse_capture(m_pframewindow->m_pthreadUserInteraction);

      TRACE("dock_manager::message_handler oswindow ReleaseCapture 2 %x\n", puserinteractionCapture);

      m_bDocking = false;

      dock_window(pmouse);

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      m_pframewindow->on_end_layout_experience(e_layout_experience_docking);

      pmessage->m_bRet = true;

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


   ::point_i32 dock_manager::dock_origin()
   {

      ::point_i32 pointOrigin;

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



