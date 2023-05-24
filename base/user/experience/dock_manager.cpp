#include "framework.h"
#include "dock_manager.h"
#include "frame_window.h"
#include "frame.h"
#include "control_box.h"
#include "button.h"
////#include "acme/exception/exception.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"
#include "aura/user/user/button.h"


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


   void dock_manager::initialize_dock_manager(::experience::frame_window* pframewindow)
   {

      //auto estatus = 
      
      channel::initialize(pframewindow);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pframewindow = pframewindow;

//      return estatus;

   }


   bool dock_manager::dock_window(::message::mouse* pmouse)
   {

      ::point_i32 pointCursor = pmouse->m_point;

      ::point_i32 point;

      ::rectangle_i32 rectangleDockButtonWindow;

      auto pbutton = dock_button();

      pbutton->window_rectangle(rectangleDockButtonWindow);

      ::point_i32 pointDock = rectangleDockButtonWindow.center();

      auto pointMove = m_pointWindowOrigin + (pmouse->m_point - (m_pointWindowOrigin + dock_origin() + m_pointCursorDockOrigin));

      pointDock+=m_pframewindow->screen_to_client();

      point = ::point_i32(pointCursor - pointDock);

      ::rectangle_i32 rectangleWindow;

      m_pframewindow->window_rectangle(rectangleWindow);

      ::rectangle_i32 rectangleEvent = rectangleWindow;

      rectangleEvent.move_to(point);

      ::rectangle_i32 rectangleCursor(pointCursor.x() - 1, pointCursor.y() - 1, pointCursor.x() + 1, pointCursor.y() + 1);

      ::rectangle_i32 screen;

      ::rectangle_i32 rectangleWork;

      auto pwindow = m_pframewindow->window();

      auto pwindowing = pwindow->windowing();

      auto pdisplay = pwindowing->display();

      int iMonitor = (int)pdisplay->get_best_monitor(screen, rectangleCursor);

      pdisplay->get_workspace_rectangle(iMonitor, rectangleWork);

      if (rectangleWork.is_empty())
      {

         throw ::exception(error_failed);

      }

      int cxCenterArea = rectangleWork.width() / 2;

      int cyCenterArea = rectangleWork.height() / 2;

      ::rectangle_i32 rectangleCenter;

      auto pointScreenCenter = rectangleWork.center();

      rectangleCenter.left = pointScreenCenter.x() - cxCenterArea / 2;

      rectangleCenter.top = pointScreenCenter.y() - cyCenterArea / 2;

      rectangleCenter.right = pointScreenCenter.x() + cxCenterArea / 2;

      rectangleCenter.bottom = pointScreenCenter.y() + cyCenterArea / 2;

      if (m_pframewindow->const_layout().design().display() & e_display_bottom)
      {

         rectangleCenter.bottom -= cyCenterArea / 4;
         rectangleCenter.left -= cxCenterArea / 16;
         rectangleCenter.right += cxCenterArea / 16;

      }
      else
      {

         rectangleCenter.bottom += cyCenterArea / 8;

      }

      if (m_pframewindow->const_layout().design().display() & e_display_top)
      {

         rectangleCenter.top += cyCenterArea / 4;
         rectangleCenter.left -= cxCenterArea / 16;
         rectangleCenter.right += cxCenterArea / 16;

      }
      else
      {

         rectangleCenter.top -= cyCenterArea / 8;

      }

      if (m_pframewindow->const_layout().design().display() & e_display_right)
      {

         rectangleCenter.right -= cxCenterArea / 4;
         rectangleCenter.top -= cyCenterArea / 8;
         rectangleCenter.bottom += cyCenterArea / 8;

      }
      else
      {

         rectangleCenter.right += cxCenterArea / 8;

      }

      if (m_pframewindow->const_layout().design().display() & e_display_left)
      {

         rectangleCenter.left += cxCenterArea / 4;
         rectangleCenter.top -= cyCenterArea / 16;
         rectangleCenter.bottom += cyCenterArea / 16;

      }
      else
      {

         rectangleCenter.left -= cxCenterArea / 8;

      }

      ::rectangle_i32 rectangleDock;

      enum_display edisplayDock = e_display_none;

      enum_display edisplayOld = m_pframewindow->const_layout().sketch().display();

      ::rectangle_i32 rectangleScreenOld = m_pframewindow->screen_rect();

      if (rectangleCenter.contains_x(pointCursor.x()))
      {

         if (rectangleCenter.contains_y(pointCursor.y()))
         {

            edisplayDock = ::e_display_restored;

         }
         else if (pointCursor.y() < rectangleCenter.top)
         {

            edisplayDock = ::e_display_full_top;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left, rectangleWork.top, rectangleWork.width(), rectangleWork.height() / 2);

         }
         else if (pointCursor.y() > rectangleCenter.bottom)
         {

            edisplayDock = ::e_display_full_bottom;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left, rectangleWork.top + rectangleWork.height() / 2, rectangleWork.width(), rectangleWork.height() / 2);

         }

      }
      else if (rectangleCenter.contains_y(pointCursor.y()))
      {

         if (pointCursor.x() < rectangleCenter.left)
         {

            edisplayDock = ::e_display_full_left;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left, rectangleWork.top, rectangleWork.width() / 2, rectangleWork.height());

         }
         else if (pointCursor.x() > rectangleCenter.right)
         {

            edisplayDock = ::e_display_full_right;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left + rectangleWork.width() / 2, rectangleWork.top, rectangleWork.width() / 2, rectangleWork.height());

         }

      }
      else if (pointCursor.x() < rectangleCenter.left)
      {

         if (pointCursor.y() < rectangleCenter.top)
         {

            edisplayDock = ::e_display_top_left;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left, rectangleWork.top, rectangleWork.width() / 2, rectangleWork.height() / 2);

         }
         else if (pointCursor.y() > rectangleCenter.bottom)
         {

            edisplayDock = ::e_display_bottom_left;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left, rectangleWork.top + rectangleWork.height() / 2, rectangleWork.width() / 2, rectangleWork.height() / 2);

         }

      }
      else if (pointCursor.x() > rectangleCenter.right)
      {

         if (pointCursor.y() < rectangleCenter.top)
         {

            edisplayDock = ::e_display_top_right;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left + rectangleWork.width() / 2, rectangleWork.top, rectangleWork.width() / 2, rectangleWork.height() / 2);

         }
         else if (pointCursor.y() > rectangleCenter.bottom)
         {

            edisplayDock = ::e_display_bottom_right;

            rectangleDock = rectangle_i32_dimension(rectangleWork.left + rectangleWork.width() / 2, rectangleWork.top + rectangleWork.height() / 2, rectangleWork.width() / 2, rectangleWork.height() / 2);

         }

      }

      if (edisplayDock == ::e_display_restored)
      {

         bool bChange = false;

         if (edisplayOld != e_display_restored)
         {

            m_pframewindow->set_size(m_pframewindow->m_windowrectangle.m_rectangleRestored.size());

            bChange = true;

         }
         else
         {

            ::rectangle_i32 rectangleNew(pointMove, m_pframewindow->m_windowrectangle.m_rectangleRestored.size());

            rectangleNew._001Constrain(rectangleWork);

            if(rectangleNew != rectangleScreenOld)
            {

               m_pframewindow->set_position(pointMove);

               bChange = true;

            }

         }

         if(bChange)
         {

            m_pframewindow->display(e_display_restored);

            m_pframewindow->set_need_layout();

            m_pframewindow->set_need_redraw();

            m_pframewindow->post_redraw();

         }

      }
      else if (is_docking_appearance(edisplayDock))
      {

         if (edisplayDock == edisplayOld || rectangleDock != rectangleWindow)
         {

            m_pframewindow->order(e_zorder_top);

            m_pframewindow->place(rectangleDock);

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

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pbutton = dock_button();

      pbutton->set_mouse_capture();

      auto pointCursor = pmouse->m_point;

      auto rectangleWindow = m_pframewindow->screen_rect();

      auto pointDockOrigin = pointCursor;

      pointDockOrigin+=pbutton->screen_to_client();

      m_pointCursorDockOrigin = pointDockOrigin;

      m_pointWindowOrigin = rectangleWindow.top_left();

      m_pointMove = m_pointWindowOrigin;

      m_sizeOrigin = rectangleWindow.size();

      m_edisplayOrigin = m_pframewindow->const_layout().design().display();

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

      auto pmouse = pmessage->m_union.m_pmouse;

      if (pmouse->m_eflagMessage & ::message::e_flag_synthesized)
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

      auto pmouse = pmessage->m_union.m_pmouse;

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


   void dock_manager::cancel_docking()
   {
      
      m_bDocking = false;

      auto pwindowing = m_pframewindow->windowing();

      pwindowing->release_mouse_capture();
      
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



