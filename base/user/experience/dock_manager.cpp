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


   bool dock_manager::dock_window(::message::mouse* pmouse)
   {

      ::point_i32 pointCursor = pmouse->m_point;

      ::point_i32 point;

      ::rectangle_i32 rectDockButtonWindow;

      auto pbutton = dock_button();

      pbutton->get_window_rect(rectDockButtonWindow);

      ::point_i32 pointDock = rectDockButtonWindow.center();

      auto pointMove = m_pointWindowOrigin + (pmouse->m_point - (m_pointWindowOrigin + dock_origin() + m_pointCursorDockOrigin));

      m_pframewindow->screen_to_client(pointDock);

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

      pdisplay->get_workspace_rectangle(iMonitor, rectWork);

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

      }
      else
      {

         rectCenter.left -= cxCenterArea / 8;

      }

      ::rectangle_i32 rectDock;

      enum_display edisplayDock = e_display_none;

      enum_display edisplayOld = m_pframewindow->layout().sketch().display();

      ::rectangle_i32 rectScreenOld = m_pframewindow->screen_rect();

      if (rectCenter.contains_x(pointCursor.x))
      {

         if (rectCenter.contains_y(pointCursor.y))
         {

            edisplayDock = ::e_display_normal;

         }
         else if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::e_display_full_top;

            rectDock = rectangle_i32_dimension(rectWork.left, rectWork.top, rectWork.width(), rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::e_display_full_bottom;

            rectDock = rectangle_i32_dimension(rectWork.left, rectWork.top + rectWork.height() / 2, rectWork.width(), rectWork.height() / 2);

         }

      }
      else if (rectCenter.contains_y(pointCursor.y))
      {

         if (pointCursor.x < rectCenter.left)
         {

            edisplayDock = ::e_display_full_left;

            rectDock = rectangle_i32_dimension(rectWork.left, rectWork.top, rectWork.width() / 2, rectWork.height());

         }
         else if (pointCursor.x > rectCenter.right)
         {

            edisplayDock = ::e_display_full_right;

            rectDock = rectangle_i32_dimension(rectWork.left + rectWork.width() / 2, rectWork.top, rectWork.width() / 2, rectWork.height());

         }

      }
      else if (pointCursor.x < rectCenter.left)
      {

         if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::e_display_top_left;

            rectDock = rectangle_i32_dimension(rectWork.left, rectWork.top, rectWork.width() / 2, rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::e_display_bottom_left;

            rectDock = rectangle_i32_dimension(rectWork.left, rectWork.top + rectWork.height() / 2, rectWork.width() / 2, rectWork.height() / 2);

         }

      }
      else if (pointCursor.x > rectCenter.right)
      {

         if (pointCursor.y < rectCenter.top)
         {

            edisplayDock = ::e_display_top_right;

            rectDock = rectangle_i32_dimension(rectWork.left + rectWork.width() / 2, rectWork.top, rectWork.width() / 2, rectWork.height() / 2);

         }
         else if (pointCursor.y > rectCenter.bottom)
         {

            edisplayDock = ::e_display_bottom_right;

            rectDock = rectangle_i32_dimension(rectWork.left + rectWork.width() / 2, rectWork.top + rectWork.height() / 2, rectWork.width() / 2, rectWork.height() / 2);

         }

      }

      if (edisplayDock == ::e_display_normal)
      {

         bool bChange = false;

         if (edisplayOld != e_display_normal)
         {

            m_pframewindow->set_size(m_pframewindow->m_windowrectangle.m_rectangleRestored.size());

            bChange = true;

         }
         else
         {

            ::rectangle_i32 rectNew(pointMove, m_pframewindow->m_windowrectangle.m_rectangleRestored.size());

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

            m_pframewindow->set_need_layout();

            m_pframewindow->set_need_redraw();

            m_pframewindow->post_redraw();

         }

      }
      else if (is_docking_appearance(edisplayDock))
      {

         if (edisplayDock == edisplayOld || rectDock != rectWindow)
         {

            m_pframewindow->order(e_zorder_top);

            m_pframewindow->place(rectDock);

            m_pframewindow->display(edisplayDock);

            m_pframewindow->set_need_layout();

            m_pframewindow->set_need_redraw();

            m_pframewindow->post_redraw();

            m_bPendingCursorPos = true;

         }

      }

      return true;

   }


   void dock_manager::dock_button_on_message_left_button_down(::message::message *pmessage)
   {

      if (!m_pframewindow->WfiOnStartDock())
      {

         return;

      }

      if (!m_pframewindow->is_docking_enabled())
      {

         return;

      }

      auto pmouse = pmessage->m_pmouse;

      auto pbutton = dock_button();

      pbutton->set_mouse_capture();

      auto pointCursor = pmouse->m_point;

      auto rectWindow = m_pframewindow->screen_rect();

      auto pointDockOrigin = pointCursor;

      pbutton->screen_to_client(pointDockOrigin);

      m_pointCursorDockOrigin = pointDockOrigin;

      m_pointWindowOrigin = rectWindow.top_left();

      m_pointMove = m_pointWindowOrigin;

      m_sizeOrigin = rectWindow.size();

      m_edisplayOrigin = m_pframewindow->layout().design().display();

      m_mapWorkspaceRect.erase_all();

      m_bDocking = true;

      m_pframewindow->on_start_layout_experience(e_layout_experience_docking);

      m_iDockMove = 0;

      dock_window(pmouse);

      pmouse->m_bRet = true;

   }


   void dock_manager::dock_button_on_message_mouse_move(::message::message *pmessage)
   {

      if (!m_pframewindow->is_docking_enabled())
      {

         return;

      }

      if (!window_is_docking())
      {

         return;

      }

      auto pmouse = pmessage->m_pmouse;

      if (pmouse->m_eflagMessage & ::message::flag_synthesized)
      {

         return;

      }

      m_iDockMove++;

      dock_window(pmouse);

      pmouse->m_bRet = true;

   }


   void dock_manager::dock_button_on_message_left_button_up(::message::message *pmessage)
   {

      if (!window_is_docking())
      {

         return;

      }

      m_bDocking = false;

      auto pmouse = pmessage->m_pmouse;

      auto pbutton = dock_button();

      pbutton->windowing()->release_mouse_capture();

      dock_window(pmouse);

      m_pframewindow->on_end_layout_experience(e_layout_experience_docking);

      pmouse->m_bRet = true;

   }


   bool dock_manager::set_frame_window(frame_window * pframewindow)
   {

      m_pframewindow = pframewindow;

      return true;

   }


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



