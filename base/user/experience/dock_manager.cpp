#include "framework.h"
#include "dock_manager.h"
#include "frame_window.h"
#include "frame.h"
#include "control_box.h"
#include "button.h"
#include "acme/constant/message.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "apex/parallelization/thread.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"
#include "aura/user/user/button.h"
#include "aura/user/user/interaction_impl.h"


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

      auto pointDock = ::point_i32(pmouse->m_pointAbsolute - m_pointCursorDockOrigin + m_sizeDockRightOrigin);

      pointDock.x() -= m_pframewindow->width();

      ::rectangle_i32 rectangleWindow;

      m_pframewindow->window_rectangle(rectangleWindow);

      ::rectangle_i32 rectangleEvent = rectangleWindow;

      rectangleEvent.move_to(pointDock);

      auto pointCursor = pmouse->m_pointAbsolute;

      ::rectangle_i32 rectangleCursor(pointCursor.x() - 1, pointCursor.y() - 1, pointCursor.x() + 1, pointCursor.y() + 1);

      ::rectangle_i32 screen;

      ::rectangle_i32 rectangleWorkspace;

      auto pwindow = m_pframewindow->window();

      auto pwindowing = pwindow->windowing();

      auto pdisplay = pwindowing->display();

      int iMonitor = (int)pdisplay->get_best_monitor(&screen, rectangleCursor);

      pdisplay->get_workspace_rectangle(iMonitor, rectangleWorkspace);

      //information() << "dock_manager::dock_window rectangleWorkspace : " << rectangleWorkspace;

      if (rectangleWorkspace.is_empty())
      {

         throw ::exception(error_failed);

      }

      auto edisplayNormal = m_pframewindow->m_windowdisplayandlayout.m_edisplayLastNormal;

      int cxQuarterWorkspace = rectangleWorkspace.width() / 4;

      int cyQuarterWorkspace = rectangleWorkspace.height() / 4;

      ::rectangle_i32 rectangleWorkspaceCenter;

      auto pointWorkspaceCenter = rectangleWorkspace.center();

      rectangleWorkspaceCenter.left() = pointWorkspaceCenter.x() - cxQuarterWorkspace;

      rectangleWorkspaceCenter.top() = pointWorkspaceCenter.y() - cyQuarterWorkspace;

      rectangleWorkspaceCenter.right() = pointWorkspaceCenter.x() + cxQuarterWorkspace;

      rectangleWorkspaceCenter.bottom() = pointWorkspaceCenter.y() + cyQuarterWorkspace;

      if (m_pframewindow->const_layout().design().display() & e_display_bottom)
      {

         rectangleWorkspaceCenter.bottom() -= cyQuarterWorkspace / 2;
         rectangleWorkspaceCenter.left() -= cxQuarterWorkspace / 8;
         rectangleWorkspaceCenter.right() += cxQuarterWorkspace / 8;

      }
      else
      {

         rectangleWorkspaceCenter.bottom() += cyQuarterWorkspace / 4;

      }

      if (m_pframewindow->const_layout().design().display() & e_display_top)
      {

         rectangleWorkspaceCenter.top() += cyQuarterWorkspace / 2;
         rectangleWorkspaceCenter.left() -= cxQuarterWorkspace / 8;
         rectangleWorkspaceCenter.right() += cxQuarterWorkspace / 8;

      }
      else
      {

         rectangleWorkspaceCenter.top() -= cyQuarterWorkspace / 4;

      }

      if (m_pframewindow->const_layout().design().display() & e_display_right)
      {

         rectangleWorkspaceCenter.right() -= cxQuarterWorkspace / 2;
         rectangleWorkspaceCenter.top() -= cyQuarterWorkspace / 8;
         rectangleWorkspaceCenter.bottom() += cyQuarterWorkspace / 8;

      }
      else
      {

         rectangleWorkspaceCenter.right() += cxQuarterWorkspace / 4;

      }

      if (m_pframewindow->const_layout().design().display() & e_display_left)
      {

         rectangleWorkspaceCenter.left() += cxQuarterWorkspace / 2;
         rectangleWorkspaceCenter.top() -= cyQuarterWorkspace / 8;
         rectangleWorkspaceCenter.bottom() += cyQuarterWorkspace / 8;

      }
      else
      {

         rectangleWorkspaceCenter.left() -= cxQuarterWorkspace / 4;

      }

      ::rectangle_i32 rectangleDock;

      enum_display edisplayDock = e_display_none;

      enum_display edisplayOld = m_pframewindow->const_layout().sketch().display();

//      ::rectangle_i32 rectangleScreenOld = m_pframewindow->screen_rect();

      if (rectangleWorkspaceCenter.contains_x(pointCursor.x()))
      {

         if (rectangleWorkspaceCenter.contains_y(pointCursor.y()))
         {

            edisplayDock = edisplayNormal;

         }
         else if (pointCursor.y() < rectangleWorkspaceCenter.top())
         {

            edisplayDock = ::e_display_full_top;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left(), rectangleWorkspace.top(), rectangleWorkspace.width(), rectangleWorkspace.height() / 2);

         }
         else if (pointCursor.y() > rectangleWorkspaceCenter.bottom())
         {

            edisplayDock = ::e_display_full_bottom;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left(), rectangleWorkspace.top() + rectangleWorkspace.height() / 2, rectangleWorkspace.width(), rectangleWorkspace.height() / 2);

         }

      }
      else if (rectangleWorkspaceCenter.contains_y(pointCursor.y()))
      {

         if (pointCursor.x() < rectangleWorkspaceCenter.left())
         {

            edisplayDock = ::e_display_full_left;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left(), rectangleWorkspace.top(), rectangleWorkspace.width() / 2, rectangleWorkspace.height());

         }
         else if (pointCursor.x() > rectangleWorkspaceCenter.right())
         {

            edisplayDock = ::e_display_full_right;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left() + rectangleWorkspace.width() / 2, rectangleWorkspace.top(), rectangleWorkspace.width() / 2, rectangleWorkspace.height());

         }

      }
      else if (pointCursor.x() < rectangleWorkspaceCenter.left())
      {

         if (pointCursor.y() < rectangleWorkspaceCenter.top())
         {

            edisplayDock = ::e_display_top_left;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left(), rectangleWorkspace.top(), rectangleWorkspace.width() / 2, rectangleWorkspace.height() / 2);

         }
         else if (pointCursor.y() > rectangleWorkspaceCenter.bottom())
         {

            edisplayDock = ::e_display_bottom_left;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left(), rectangleWorkspace.top() + rectangleWorkspace.height() / 2, rectangleWorkspace.width() / 2, rectangleWorkspace.height() / 2);

         }

      }
      else if (pointCursor.x() > rectangleWorkspaceCenter.right())
      {

         if (pointCursor.y() < rectangleWorkspaceCenter.top())
         {

            edisplayDock = ::e_display_top_right;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left() + rectangleWorkspace.width() / 2, rectangleWorkspace.top(), rectangleWorkspace.width() / 2, rectangleWorkspace.height() / 2);

         }
         else if (pointCursor.y() > rectangleWorkspaceCenter.bottom())
         {

            edisplayDock = ::e_display_bottom_right;

            rectangleDock = rectangle_i32_dimension(rectangleWorkspace.left() + rectangleWorkspace.width() / 2, rectangleWorkspace.top() + rectangleWorkspace.height() / 2, rectangleWorkspace.width() / 2, rectangleWorkspace.height() / 2);

         }

      }

      if (equivalence_sink(edisplayDock) == ::e_display_normal)
      {

         bool bChanged = false;

         edisplayDock = m_edisplayOrigin;

         if (edisplayOld != edisplayDock)
         {

            bChanged = true;

         }

         ::rectangle_i32 rectangleWindow = m_rectangleOnDockStart;

         auto pointReposition =
            pmouse->m_pointAbsolute
            - m_pointCursorDockOrigin
            + m_sizeDockRightOrigin;

         pointReposition.cx() -= rectangleWindow.width();

         rectangleWindow.move_to(pointReposition);

         information() << "rectangleNew " << pointReposition;

         ///m_pframewindow->good_restore(nullptr, rectangleNew, true, e_activation_default, e_zorder_top, edisplayDock);

         m_pframewindow->place(rectangleWindow);

         if (bChanged)
         {

            m_pframewindow->set_display(edisplayDock);

            m_pframewindow->set_need_layout();

         }

         m_pframewindow->set_need_redraw();

         m_pframewindow->post_redraw();

      }
      else if (is_docking_appearance(edisplayDock))
      {

         if (edisplayDock != edisplayOld || rectangleDock != rectangleWindow)
         {

            m_pframewindow->order(e_zorder_top);

            m_pframewindow->place(rectangleDock);

            m_pframewindow->display_docked(edisplayDock, e_activation_default);

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

      auto pwindowimpl = m_pframewindow->get_window_impl();

      pwindowimpl->m_puiLastLButtonDown = pbutton;

      pbutton->set_mouse_capture();

      auto rectangleWindow = m_pframewindow->screen_rectangle();

      auto pointCursor = pmouse->m_pointAbsolute;

      m_rectangleOnDockStart = rectangleWindow;

      auto pointCursorDockOrigin = pointCursor;

      pbutton->screen_to_client()(pointCursorDockOrigin);

      m_pointCursorDockOrigin = pointCursorDockOrigin;

      m_sizeDockRightOrigin = dock_button_right_origin();

      m_pointWindowOrigin = rectangleWindow.top_left();

      m_pointMove = m_pointWindowOrigin;

      m_sizeOrigin = rectangleWindow.size();

      auto edisplayOrigin = m_pframewindow->const_layout().design().display();

      if (::is_docking_appearance(edisplayOrigin))
      {

         m_edisplayOrigin = e_display_normal;

      }
      else
      {

         m_edisplayOrigin = edisplayOrigin;

      }

      m_pointLastRepositionCursorOrigin = pmouse->m_pointAbsolute;

      m_pointLastRepositionWindowOrigin = m_pframewindow->const_layout().window().origin();

      m_mapWorkspaceRect.erase_all();

      m_bDocking = true;

      m_pframewindow->m_pthreadUserInteraction->m_emessageaGetLast.add(e_message_mouse_move);

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

      m_pframewindow->m_pthreadUserInteraction->m_emessageaGetLast.erase(e_message_mouse_move);

      m_bDocking = false;

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pbutton = dock_button();

      pbutton->defer_release_mouse_capture();

      //dock_window(pmouse);

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

      auto pbutton = dock_button();

      pbutton->defer_release_mouse_capture();

   }


   ::user::button * dock_manager::dock_button()
   {

      return m_pframewindow->m_pframe->m_pcontrolbox->get_button(e_button_dock);

   }

   /// Screen coordinates of center of dock button
   ::size_i32 dock_manager::dock_button_right_origin()
   {

      ::point_i32 pointOrigin;

      auto pbutton = dock_button();

      auto rectangle = pbutton->raw_rectangle();

      pbutton->raw_to_host()(rectangle);

      return { m_pframewindow->width() - rectangle.origin().x(), -rectangle.origin().y()};

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

      return m_edockMask;

   }


   void dock_manager::set_dock_mask(e_dock edockMask)
   {

      m_edockMask = edockMask;

   }


   bool dock_manager::_001OnTimer(::u32 uEvent)
   {

      return false;

   }


} // namespace experience



