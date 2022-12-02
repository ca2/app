#include "framework.h"
#include "size_manager.h"
#include "frame_window.h"
#include "frame.h"
#include "acme/constant/message.h"
#include "aura/windowing/windowing.h"
#include "aura/message/user.h"


namespace experience
{


   size_manager::size_manager() :
      m_sizeMinimumBorder(33, 33)
   {

      m_eframeSizing = e_frame_none;

      m_eframeCursor = e_frame_none;

      m_egripMask = e_grip_all;

   }


   size_manager::~size_manager()
   {

   }


   void size_manager::initialize_size_manager(::experience::frame_window* pframewindow)
   {

      //auto estatus = 
      
      ::object::initialize(pframewindow);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pframewindow = pframewindow;

      //return estatus;

   }


   bool size_manager::on_message_left_button_down(::message::mouse * pmouse)
   {

      ASSERT(pmouse->m_atom == e_message_left_button_down || pmouse->m_atom == e_message_non_client_left_button_down);

      if(!m_pframewindow->is_sizing_enabled())
      {

         return false;

      }

      auto pointCursor = pmouse->m_point;

      m_pointCursorOrigin = pointCursor;

      ::rectangle_i32 rectangleWindow;

      m_pframewindow->get_window_rect(rectangleWindow);

      m_rectangleWindowOrigin = rectangleWindow;

      ::rectangle_i32 rectangleEvent;

      m_pframewindow->get_window_rect(rectangleEvent);

      //enum_frame eframe = _001HitTest(pointCursor);

      ::experience::enum_frame eframe = m_eframeCursor;

      //auto pframewindow = m_pframewindow;

//      if(eframe != e_frame_none)
//      {
//
//#ifdef WINDOWS_DESKTOP
//
//         ::u32 nHitTest = HTCLIENT;
//
//         switch(eframe)
//         {
//         case e_frame_sizing_left:
//            nHitTest = HTLEFT;
//            break;
//         case e_frame_sizing_top_left:
//            nHitTest = HTTOPLEFT;
//            break;
//         case e_frame_sizing_top:
//            nHitTest = HTTOP;
//            break;
//         case e_frame_sizing_top_right:
//            nHitTest = HTTOPRIGHT;
//            break;
//         case e_frame_sizing_right:
//            nHitTest = HTRIGHT;
//            break;
//         case e_frame_sizing_bottom_right:
//            nHitTest = HTBOTTOMRIGHT;
//            break;
//         case e_frame_sizing_bottom:
//            nHitTest = HTBOTTOM;
//            break;
//         case e_frame_sizing_bottom_left:
//            nHitTest = HTBOTTOMLEFT;
//            break;
//         default:
//            break;
//         }
//
//#endif
//
//         //if(pframewindow->WfiOnBeginSizing(nHitTest, pointCursor))
//         //   return true;
//      }

      if (eframe == e_frame_none)
      {

         return false;

      }

      pmouse->m_bRet = true;

      m_pframewindow->set_mouse_capture();

      auto pwindowing = m_pframewindow->windowing();

      auto ecursor = experience_frame_to_cursor(eframe);

      auto pcursor = pwindowing->get_cursor(ecursor);

      pmouse->m_pcursor = pcursor;

      m_eframeSizing = eframe;

      m_pframewindow->on_start_layout_experience(e_layout_experience_sizing);

      m_iPaintCount = 0;

      return true;

   }


   bool size_manager::on_message_mouse_move(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_sizing_enabled())
      {

         return false;

      }

      ASSERT(pmouse->m_atom == e_message_mouse_move || pmouse->m_atom == e_message_non_client_mouse_move);

      if(m_eframeSizing != e_frame_none)
      {

         size_window(m_eframeSizing, m_pframewindow, pmouse->m_point, true);

         auto pwindowing = m_pframewindow->windowing();

         auto ecursor = experience_frame_to_cursor(m_eframeSizing);

         auto pcursor = pwindowing->get_cursor(ecursor);

         m_pframewindow->set_mouse_cursor(pcursor);

         pmouse->m_pcursor = pcursor;

         pmouse->m_lresult = 1;

         pmouse->m_bRet = true;

         return true;

      }

      auto eframeCursor = experience_frame_hit_test(pmouse->m_point);

      if (eframeCursor == e_frame_none)
      {

         if (m_eframeCursor != e_frame_none)
         {

            m_eframeCursor = e_frame_none;

         }

         return false;

      }
         
      if (m_eframeCursor != eframeCursor)
      {

         m_eframeCursor = eframeCursor;

      }

      auto ecursor = experience_frame_to_cursor(m_eframeCursor);

      auto pwindowing = m_pframewindow->windowing();

      auto pcursor = pwindowing->get_cursor(ecursor);

      pmouse->m_pcursor = pcursor;

      m_pframewindow->set_mouse_cursor(pcursor);

      pmouse->m_lresult = 1;

      pmouse->m_bRet = true;

      return true;

   }


   //bool size_manager::on_message_set_cursor(::message::set_cursor * psetcursor)
   //{

   //   if (!m_pframewindow->is_sizing_enabled())
   //   {

   //      return false;

   //   }

   //   if (m_eframeSizing != e_frame_none)
   //   {

   //      auto psession = acmesession()->m_paurasession;

   //      auto puser = psession->user();

   //      auto pwindowing = puser->windowing();

   //      auto ecursor = translate(m_eframeSizing);

   //      auto pcursor = pwindowing->get_cursor(ecursor);

   //      psetcursor->m_pcursor = pcursor;

   //      psetcursor->m_lresult = 1;

   //      psetcursor->m_bRet = true;

   //      return true;

   //   }

   //   auto eframeCursor = _001HitTest(psetcursor->m_point);

   //   if (eframeCursor == e_frame_none)
   //   {

   //      if (m_eframeCursor != e_frame_none)
   //      {

   //         eframeCursor = e_frame_none;

   //      }

   //   }
   //   else
   //   {

   //      if (m_eframeCursor != eframeCursor)
   //      {

   //         eframeCursor = eframeCursor;

   //      }

   //      auto ecursor = translate(m_eframeCursor);

   //      auto psession = acmesession()->m_paurasession;

   //      auto puser = psession->user();

   //      auto pwindowing = puser->windowing();

   //      auto pcursor = pwindowing->get_cursor(ecursor);

   //      psetcursor->m_pcursor = pcursor;

   //      psetcursor->m_lresult = 1;

   //      psetcursor->m_bRet = true;

   //      return true;

   //   }

   //   return false;

   //}


   bool size_manager::on_message_left_button_up(::message::mouse * pmouse)
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

      if (m_eframeSizing == e_frame_none)
      {

         return false;

      }

      auto eframeSizing = m_eframeSizing;

      m_eframeSizing = e_frame_none;

      auto pwindowing = m_pframewindow->windowing();

      pwindowing->release_mouse_capture();

      if(pmouse)
      {

         pmouse->m_bRet = true;

         if(bApply)
         {

            size_window(eframeSizing, m_pframewindow, pmouse->m_point, true);

            pmouse->m_lresult = 1;

            pmouse->m_bRet = true;

         }

      }

      m_pframewindow->on_end_layout_experience(e_layout_experience_sizing);

      return true;

   }


   enum_cursor size_manager::experience_frame_to_cursor(::experience::enum_frame eframe)
   {

      switch(eframe)
      {
      case e_frame_none:
         return e_cursor_default;
      case e_frame_sizing_top_left:
         return e_cursor_size_top_left;
      case e_frame_sizing_top:
         return e_cursor_size_top;
      case e_frame_sizing_top_right:
         return e_cursor_size_top_right;
      case e_frame_sizing_right:
         return e_cursor_size_right;
      case e_frame_sizing_bottom_right:
         return e_cursor_size_bottom_right;
      case e_frame_sizing_bottom:
         return e_cursor_size_bottom;
      case e_frame_sizing_bottom_left:
         return e_cursor_size_bottom_left;
      case e_frame_sizing_left:
         return e_cursor_size_left;
         break;
      default:
         return e_cursor_default;
      }

   }


   ::size_i32 size_manager::GetMinSize()
   {

      return m_pframewindow->m_pframe->GetMinSize();

   }


   //void size_manager::SetSWPFlags(::u32 uFlags)
   //{

   //   m_uiSWPFlags = uFlags;
   //   m_uiSWPFlags &= ~SWP_NOSIZE & ~SWP_NOMOVE;

   //}


   void size_manager::size_window(::experience::enum_frame eframe, ::user::interaction * pframewindow, const ::point_i32 & point, bool bTracking)
   {

      bool bSize = true;

      ::rectangle_i32 rectangleWindow;

      ::rectangle_i32 rectangleMonitor;

      pframewindow->best_monitor(rectangleMonitor);

      ::size_i32 sizeMin = GetMinSize();

      if(eframe == e_frame_sizing_top_left)
      {
         rectangleWindow.top = point.y +1;
         rectangleWindow.left = point.x +1;
         rectangleWindow.bottom = m_rectangleWindowOrigin.bottom;
         rectangleWindow.right = m_rectangleWindowOrigin.right;
         bSize = !rectangleWindow.is_empty();
         if(rectangleWindow.width() < sizeMin.cx)
         {
            rectangleWindow.left = m_rectangleWindowOrigin.right - sizeMin.cx;
         }
         if(rectangleWindow.height() < sizeMin.cy)
         {
            rectangleWindow.top = m_rectangleWindowOrigin.bottom - sizeMin.cy;
         }
         rectangleWindow.left = minimum(rectangleWindow.left, rectangleMonitor.right - m_sizeMinimumBorder.cx);
         rectangleWindow.top = minimum(rectangleWindow.top, rectangleMonitor.bottom - m_sizeMinimumBorder.cy);
      }
      else if(eframe == e_frame_sizing_top)
      {
         rectangleWindow.top = point.y +1;
         rectangleWindow.left = m_rectangleWindowOrigin.left;
         rectangleWindow.bottom = m_rectangleWindowOrigin.bottom;
         rectangleWindow.right = m_rectangleWindowOrigin.right;
         if(rectangleWindow.height() < sizeMin.cy)
         {
            rectangleWindow.top = m_rectangleWindowOrigin.bottom - sizeMin.cy;
         }
         rectangleWindow.top = minimum(rectangleWindow.top, rectangleMonitor.bottom - m_sizeMinimumBorder.cy);
         auto pframewindow = m_pframewindow;
         if (pframewindow->find_i32("ysnap") > 1)
         {
            rectangleWindow.top -= rectangleWindow.top % pframewindow->find_i32("ysnap");
         }
      }
      else if(eframe == e_frame_sizing_top_right)
      {
         rectangleWindow.top = point.y +1;
         rectangleWindow.left = m_rectangleWindowOrigin.left;
         rectangleWindow.bottom = m_rectangleWindowOrigin.bottom;
         rectangleWindow.right = point.x;
         if(rectangleWindow.width() < sizeMin.cx)
         {
            rectangleWindow.right = m_rectangleWindowOrigin.left + sizeMin.cx;

         }
         if(rectangleWindow.height() < sizeMin.cy)
         {
            rectangleWindow.top = m_rectangleWindowOrigin.bottom - sizeMin.cy;
         }
         rectangleWindow.right = maximum(rectangleWindow.right, rectangleMonitor.left + m_sizeMinimumBorder.cx);
         rectangleWindow.top = minimum(rectangleWindow.top, rectangleMonitor.bottom - m_sizeMinimumBorder.cy);
      }
      else if(eframe == e_frame_sizing_right)
      {
         rectangleWindow.top = m_rectangleWindowOrigin.top;
         rectangleWindow.left = m_rectangleWindowOrigin.left;
         rectangleWindow.bottom = m_rectangleWindowOrigin.bottom;
         rectangleWindow.right = point.x;
         if(rectangleWindow.width() < sizeMin.cx)
         {
            rectangleWindow.right = m_rectangleWindowOrigin.left + sizeMin.cx;

         }
         rectangleWindow.right = maximum(rectangleWindow.right, rectangleMonitor.left + m_sizeMinimumBorder.cx);
      }
      else if(eframe == e_frame_sizing_bottom_right)
      {
         rectangleWindow.top = m_rectangleWindowOrigin.top;
         rectangleWindow.left = m_rectangleWindowOrigin.left;
         rectangleWindow.bottom = point.y;
         rectangleWindow.right = point.x;
         if (rectangleWindow.width() < sizeMin.cx)
         {
            rectangleWindow.right = m_rectangleWindowOrigin.left + sizeMin.cx;

         }
         if (m_pframewindow->m_bDerivedHeight)
         {
            
            int iWidth = rectangleWindow.width();
            
            int iDerivedHeight = m_pframewindow->get_derived_height(iWidth);
            
            int iHeight = m_pframewindow->m_pframe->adjust_client_height(iDerivedHeight);

            if (iHeight < sizeMin.cy)
            {
               
               rectangleWindow.bottom = m_rectangleWindowOrigin.top + sizeMin.cy;

               rectangleWindow.right = m_rectangleWindowOrigin.left + m_pframewindow->m_pframe->adjust_client_width(m_pframewindow->get_derived_width(sizeMin.cy));
               
            }
            else
            {
               
               rectangleWindow.bottom = m_rectangleWindowOrigin.top + iHeight;

            }
            
         }
         else
         {
            if (rectangleWindow.height() < sizeMin.cy)
            {
               rectangleWindow.bottom = m_rectangleWindowOrigin.top + sizeMin.cy;
            }
            rectangleWindow.right = maximum(rectangleWindow.right, rectangleMonitor.left + m_sizeMinimumBorder.cx);
            rectangleWindow.bottom = maximum(rectangleWindow.bottom, rectangleMonitor.top + m_sizeMinimumBorder.cy);
         }
      }
      else if(eframe == e_frame_sizing_bottom)
      {
         rectangleWindow.top = m_rectangleWindowOrigin.top;
         rectangleWindow.left = m_rectangleWindowOrigin.left;
         rectangleWindow.bottom = point.y;
         rectangleWindow.right = m_rectangleWindowOrigin.right;
         if(rectangleWindow.height() < sizeMin.cy)
         {
            rectangleWindow.bottom = m_rectangleWindowOrigin.top + sizeMin.cy;
         }
         rectangleWindow.bottom = maximum(rectangleWindow.bottom, rectangleMonitor.top + m_sizeMinimumBorder.cy);
         auto pframewindow = m_pframewindow;

         if (pframewindow->find_i32("ysnap") > 1)
         {
            int h = rectangleWindow.height();
            h -= rectangleWindow.height() % pframewindow->find_i32("ysnap");
            rectangleWindow.bottom = rectangleWindow.top + h;
         }
      }
      else if(eframe == e_frame_sizing_bottom_left)
      {
         rectangleWindow.top = m_rectangleWindowOrigin.top;
         rectangleWindow.left = point.x +1;
         rectangleWindow.bottom = point.y;
         rectangleWindow.right = m_rectangleWindowOrigin.right;
         if(rectangleWindow.width() < sizeMin.cx)
         {
            rectangleWindow.left = m_rectangleWindowOrigin.right - sizeMin.cx;

         }
         if(rectangleWindow.height() < sizeMin.cy)
         {
            rectangleWindow.bottom = m_rectangleWindowOrigin.top + sizeMin.cy;
         }
         rectangleWindow.left = minimum(rectangleWindow.left, rectangleMonitor.right - m_sizeMinimumBorder.cx);
         rectangleWindow.bottom = maximum(rectangleWindow.bottom, rectangleMonitor.top + m_sizeMinimumBorder.cy);
      }
      else if(eframe == e_frame_sizing_left)
      {
         rectangleWindow.top = m_rectangleWindowOrigin.top;
         rectangleWindow.left = point.x +1;
         rectangleWindow.bottom = m_rectangleWindowOrigin.bottom;
         rectangleWindow.right = m_rectangleWindowOrigin.right;
         if(rectangleWindow.width() < sizeMin.cx)
         {
            rectangleWindow.left = m_rectangleWindowOrigin.right - sizeMin.cx;

         }
         rectangleWindow.left = minimum(rectangleWindow.left, rectangleMonitor.right - m_sizeMinimumBorder.cx);
      }
      else
      {
         bSize = false;
      }

      move_window(m_pframewindow, rectangleWindow);

      NotifyFramework(eframe);

   }


   void size_manager::move_window(::user::interaction * pframewindow, const ::rectangle_i32 & rectangle)
   {

      auto rectangleWindow = rectangle;

      auto sizeMin = GetMinSize();

      if (rectangleWindow.width() < sizeMin.cx || rectangleWindow.height() < sizeMin.cy)
      {

         return;

      }

      ::rectangle_i32 rectangleWindowNow;

      m_pframewindow->get_window_rect(rectangleWindowNow);

      if (rectangleWindowNow == rectangleWindow)
      {

         return;

      }

      {

         //::user::lock_sketch_to_design lockSketchToDesign(m_pframewindow);

         if (m_pframewindow->layout().is_zoomed())
         {

            m_pframewindow->display(e_display_restore);

         }

         ::rectangle_i32 rectangleBefore;

         pframewindow->get_window_rect(rectangleBefore);

         ::rectangle_i32 rectangleAfter = rectangleWindow;

         ::rectangle_i32 rectangleParentClient = rectangleAfter;

         if (m_pframewindow->get_parent() != nullptr)
         {

            rectangleParentClient+=m_pframewindow->get_parent()->screen_to_client();

         }

         ::rectangle_i32 rectangleTotal;

         rectangleTotal.unite(rectangleBefore, rectangleAfter);

         m_pframewindow->m_rectanglePending.unite(rectangleBefore, rectangleAfter);

         pframewindow->place(rectangleParentClient);

         FORMATTED_TRACE("Size Manager Changed (%d, %d)", rectangleParentClient.right, rectangleParentClient.bottom);

         pframewindow->display();

         pframewindow->set_need_layout();

         pframewindow->set_need_redraw();

      }

      pframewindow->post_redraw();

   }


   bool size_manager::window_is_sizing()
   {

      return m_eframeSizing != e_frame_none;

   }


   void size_manager::cancel_sizing()
   {
      
      m_eframeSizing = e_frame_none;
      
      auto pwindowing = m_pframewindow->windowing();

      pwindowing->release_mouse_capture();

   }


   void size_manager::SetGripMask(enum_grip egrip)
   {

      m_egripMask = egrip;

   }


   enum_grip size_manager::GetGripMask()
   {

      return m_egripMask;

   }


   enum_grip size_manager::experience_frame_to_experience_grip(enum_frame eframe)
   {

      enum_grip egrip;

      if(eframe == e_frame_sizing_top)
         egrip = e_grip_top;
      else if(eframe == e_frame_sizing_top_left)
         egrip = e_grip_top_left;
      else if(eframe == e_frame_sizing_left)
         egrip = e_grip_left;
      else if(eframe == e_frame_sizing_bottom_left)
         egrip = e_grip_bottom_left;
      else if(eframe == e_frame_sizing_bottom)
         egrip = e_grip_bottom;
      else if(eframe == e_frame_sizing_bottom_right)
         egrip = e_grip_bottom_right;
      else if(eframe == e_frame_sizing_right)
         egrip = e_grip_right;
      else if(eframe == e_frame_sizing_top_right)
         egrip = e_grip_top_right;
      else
         egrip = e_grip_none;
      return egrip;

   }


   void size_manager::NotifyFramework(enum_frame eframe)
   {

      __UNREFERENCED_PARAMETER(eframe);

   }


   enum_frame size_manager::experience_frame_hit_test(const ::point_i32 & pointCursor)
   {

      enum_frame eframe = m_pframewindow->experience_frame_hit_test(pointCursor);

      switch(eframe)
      {
      case e_frame_sizing_left:
      case e_frame_sizing_top_left:
      case e_frame_sizing_top:
      case e_frame_sizing_top_right:
      case e_frame_sizing_right:
      case e_frame_sizing_bottom_right:
      case e_frame_sizing_bottom:
      case e_frame_sizing_bottom_left:
         return eframe;
      default:
         return e_frame_none;
      }

   }


   bool size_manager::set_frame_window(frame_window * pframewindow)
   {

      m_pframewindow = pframewindow;

      return true;

   }


} // namespace experience



