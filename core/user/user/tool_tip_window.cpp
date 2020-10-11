#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif
#include "acme/const/timer.h"
#include "tool_tip_window.h"
#include "tool_tip_tool.h"


namespace user
{


   tool_tip_window::tool_tip_window():
      m_font(e_create)
   {

      m_ealignDefault = (EAlign) (AlignRight | AlignTop);
      m_iTool = -1;
      m_iEventTool = -1;
      m_bTipEnable = true;

   }

   tool_tip_window::~tool_tip_window()
   {
   }

   void tool_tip_window::relay_event(::user::tool_tip_tool * ptool, ::message::message * pmessage)
   {
      if(is_window())
         return;
      SCAST_PTR(::message::base, pbase, pmessage);
      switch(pbase->m_id)
      {
      case WM_MOUSEMOVE:
      {
         
         if(ptool->BaseToolTipGetWnd()->GetTopLevel() == pbase->userinteraction())
         {
            
            auto point = Session.get_cursor_pos();
            
            if(m_iEventTool != ptool->BaseToolTipGetIndex()
                  || point != m_point)
            {
               m_point = point;
               m_iEventTool = ptool->BaseToolTipGetIndex();
               //ptool->BaseToolTipGetWnd()->_001ScreenToClient(&m_point);
               KillTimer(timer_show_delayed);
               HideTip();
               SetTimer(timer_show_delayed, 500, nullptr);
            }
         }
      }
      break;
      default:
         break;
      }
   }


   void tool_tip_window::ShowTip(
   i32 iTool,    // [in] item selected
   bool bForce)
   {
      if(!IsTipEnabled())
      {
         return;
      }

      if(!bForce)
      {
         auto point = Session.get_cursor_pos();
         if(point != m_point)
            return;
      }

      if(!GetToolText(iTool, m_strTip))
         return;

      SetTimer(1, 5000, nullptr);

      ::rect rect;

      auto pgraphics = ::draw2d::create_memory_graphics();

      GetToolRect(iTool, rect);


      m_ealign = m_ealignDefault;


      __pointer(::user::interaction) pwnd = m_puserinteraction;
      ::user::tool_tip_tool * ptool = GetTool(iTool);

      bool bVRetry = false;
      bool bHRetry = false;

      while(true)
      {
         m_sizeArrow.cx = 12;
         m_sizeArrow.cy = 12;
         if(((m_ealign & AlignLeft) == AlignLeft) &&
               ((m_ealign & AlignTop) == AlignTop))
         {
            m_pointOffset.x = + (rect.width() == 0 ? 0 : rect.width() * 3 / 5);
            m_pointOffset.y = + (rect.height() == 0 ? 0 : rect.height() * 3 / 5);
         }
         else if(((m_ealign & AlignRight) == AlignRight) &&
                 ((m_ealign & AlignTop) == AlignTop))
         {
            m_pointOffset.x = - (rect.width() == 0 ? 0 : rect.width() * 3 / 5);
            m_pointOffset.y = + (rect.height() == 0 ? 0 : rect.height() * 3 / 5);
         }
         else
         {
            m_pointOffset.x = - (rect.width() == 0 ? 0 : rect.width() * 3 / 5);
            m_pointOffset.y = - (rect.height() == 0 ? 0 : rect.height() * 3 / 5);
         }
         ::rect rectToolScreen;
         ptool->BaseToolTipGetRect(rectToolScreen);
         ptool->BaseToolTipGetWnd()->_001ClientToScreen(rectToolScreen);
         CalcRect(pgraphics, rect, rectToolScreen, m_strTip);


         ::size sizeScreen;
         sizeScreen.cx = ::GetSystemMetrics(SM_CXSCREEN);
         sizeScreen.cy = ::GetSystemMetrics(SM_CYSCREEN);

         if(rect.right > sizeScreen.cx && !bHRetry)
         {
            bHRetry = true;
            if(m_ealign & AlignRight)
            {
               m_ealign &= (EAlign) ~AlignRight;
               m_ealign |= AlignLeft;
               continue;
            }
         }
         if(rect.bottom > sizeScreen.cy && !bVRetry)
         {
            bVRetry = true;
            if(m_ealign & AlignBottom)
            {
               m_ealign &= (EAlign) ~AlignBottom;
               m_ealign |= AlignTop;
               continue;
            }
         }
         break;
      }


      order(zorder_top_most);
      
      place(rect);
      
      activation(activation_no_activate);

      update_drawing_objects();

      display(SW_SHOWNOACTIVATE);
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: CalcRect
   //
   // Purpose:
   // Calculate the rectangle of the tip string.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::CalcRect(::draw2d::graphics_pointer & pgraphics, RECT * prect, const ::rect & rectTool, const char * pcsz)
   {
      
      pgraphics->set(m_font);
      
      auto size = pgraphics->GetTextExtent(pcsz);

      if(((m_ealign & AlignLeft) == AlignLeft) &&
            ((m_ealign & AlignTop) == AlignTop))
      {
         prect->right = m_point.x - (m_point.x - rectTool.left) / 2;

         prect->left = (LONG) (prect->right - size.cx - m_sizeArrow.cx - 4);

         prect->bottom = m_point.y - (m_point.y - rectTool.top) / 2;

         prect->top = (LONG) (prect->bottom - size.cy - m_sizeArrow.cy - 4);

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
              ((m_ealign & AlignTop) == AlignTop))
      {
         prect->left = m_point.x + (rectTool.right - m_point.x) / 2;

         prect->bottom = m_point.y - (m_point.y - rectTool.top) / 2;

         prect->right = (LONG) (prect->left + size.cx + m_sizeArrow.cx + 4);

         prect->top = (LONG) (prect->bottom - size.cy - m_sizeArrow.cy - 4);

      }
      else
      {
         prect->left = prect->right + m_pointOffset.x;

         prect->top = prect->bottom + m_pointOffset.y;

         prect->right = (LONG)(prect->left + size.cx + m_sizeArrow.cx + 4);

         prect->bottom = (LONG) (prect->top + size.cy + m_sizeArrow.cy + 4);

      }
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnPaint
   //
   // Purpose:
   // WM_PAINT message handler.
   //
   // Output:
   // See aura API documentation.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnPaint()
   {
      ::exception::throw_not_implemented();
      /*CPaintDC spgraphics(this);
      ::draw2d::graphics_pointer & pgraphics = &spgraphics;
      pgraphics->set(m_font);
      ::rect rectClient;
      get_client_rect(rectClient);
      ::rect rectText;
      pgraphics->SetBkMode(TRANSPARENT);
      if(((m_ealign & AlignLeft) == AlignLeft) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::rect rectArrow(rectClient.right - m_sizeArrow.cx * 2, rectClient.bottom - m_sizeArrow.cy * 2, rectClient.right, rectClient.bottom);
        rectClient.right -= m_sizeArrow.cx;
        rectClient.bottom -= m_sizeArrow.cy;
        pgraphics->fill_rect(rectArrow, RGB(0, 120, 180));
        pgraphics->fill_rect(rectClient, RGB(220, 240, 250));
        pgraphics->draw3d_rect(rectClient, RGB(0, 120, 180), RGB(0, 120, 180));
        pgraphics->set_text_color(RGB(0, 60, 90));
        rectText = rectClient;
        rectText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::rect rectArrow(0, rectClient.bottom - m_sizeArrow.cy * 2, m_sizeArrow.cx * 2, rectClient.bottom);
        rectClient.left = m_sizeArrow.cx;
        rectClient.bottom -= m_sizeArrow.cy;
        pgraphics->fill_rect(rectArrow, RGB(0, 120, 180));
        pgraphics->fill_rect(rectClient, RGB(220, 240, 250));
        pgraphics->draw3d_rect(rectClient, RGB(0, 120, 180), RGB(0, 120, 180));
        pgraphics->set_text_color(RGB(0, 60, 90));
        rectText = rectClient;
        rectText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else
      {
        ::rect rectArrow(0, 0, m_sizeArrow.cx * 2, m_sizeArrow.cy * 2);
        rectClient.left = m_sizeArrow.cx;
        rectClient.top = m_sizeArrow.cy;
        pgraphics->fill_rect(rectArrow, RGB(0, 120, 180));
        pgraphics->fill_rect(rectClient, RGB(220, 240, 250));
        pgraphics->draw3d_rect(rectClient, RGB(0, 120, 180), RGB(0, 120, 180));
        pgraphics->set_text_color(RGB(0, 60, 90));
        rectText = rectClient;
        rectText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }*/
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnTimer()
   //
   // Purpose:
   // Handler for WM_TIMER message
   //
   // Output:
   // none
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnTimer(UINT nIDEvent)
   {
      switch(nIDEvent)
      {
      case timer_hide_window:
      {
         display(display_none);
         KillTimer(nIDEvent);
      }
      break;
      case timer_show_delayed:
      {
         m_iTool = m_iEventTool;
         ShowTip();
         KillTimer(nIDEvent);
      }
      default:
         break;
      }


   }


   bool tool_tip_window::create(::user::interaction * puserinteraction, const id & id)
   {
      
      m_puserinteraction = puserinteraction;

      m_font->create_point_font(FONT_SANS, 10.0);
      
      ::user::create_struct createstruct(WS_EX_TOOLWINDOW, nullptr, nullptr, WS_POPUP, nullptr);
      
      return create_window_ex(createstruct, nullptr, id) != 0;

   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnSize()
   //
   // Purpose:
   // Resize the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnSize(UINT nType, i32 cx, i32 cy)
   {
      update_drawing_objects();
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: HideTip()
   //
   // Purpose:
   // Hide the tip.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::HideTip()
   {
      if(is_window_visible())
      {
         display(display_none);
      }
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: EnableTip()
   //
   // Purpose:
   // Enable the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::EnableTip(
   bool bEnable)  // [in] define if the tip will be enabled
   {
      m_bTipEnable = bEnable;
      if(!bEnable)
      {
         HideTip();
      }
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: IsTipEnabled()
   //
   // Purpose:
   // Define if the tip is enabled.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::IsTipEnabled()
   {
      return m_bTipEnable;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnDestroy()
   //
   // Purpose:
   // Destroy the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnDestroy()
   {
      //    window::OnDestroy();
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: ShowTip()
   //
   // Purpose:
   // Show the tip.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::ShowTip()
   {
      ShowTip(m_iTool);
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: update_drawing_objects()
   //
   // Purpose:
   // Update the drawing of the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::update_drawing_objects()
   {
      /*::draw2d::region rgn;
      ::rect rectClient;
      get_client_rect(rectClient);
      ::rect rectWindow;
      get_window_rect(rectWindow);
      _001ScreenToClient(rectWindow);
      rectClient.offset(-rectWindow.top_left());
      const ::point & pointa[6];

      if(((m_ealign & AlignLeft) == AlignLeft) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pointa[0].x = rectClient.left;
         pointa[0].y = rectClient.top;
         pointa[1].x = rectClient.right - m_sizeArrow.cx;
         pointa[1].y = rectClient.top;
         pointa[2].x = rectClient.right - m_sizeArrow.cx;
         pointa[2].y = rectClient.bottom - m_sizeArrow.cy * 2;
         pointa[3].x = rectClient.right;
         pointa[3].y = rectClient.bottom;
         pointa[4].x = rectClient.right - m_sizeArrow.cx * 2;
         pointa[4].y = rectClient.bottom - m_sizeArrow.cy;
         pointa[5].x = rectClient.left;
         pointa[5].y = rectClient.bottom - m_sizeArrow.cy;

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pointa[0].x = rectClient.left + m_sizeArrow.cx;
         pointa[0].y = rectClient.top;
         pointa[1].x = rectClient.right;
         pointa[1].y = rectClient.top;
         pointa[2].x = rectClient.right;
         pointa[2].y = rectClient.bottom - m_sizeArrow.cy;
         pointa[3].x = rectClient.left + m_sizeArrow.cx * 2;
         pointa[3].y = rectClient.bottom - m_sizeArrow.cy;
         pointa[4].x = rectClient.left;
         pointa[4].y = rectClient.bottom;
         pointa[5].x = rectClient.left + m_sizeArrow.cx;
         pointa[5].y = rectClient.bottom - m_sizeArrow.cy * 2;

      }
      else
      {
         pointa[0].x = rectClient.left;
         pointa[0].y = rectClient.top;
         pointa[1].x = rectClient.left + m_sizeArrow.cx * 2;
         pointa[1].y = rectClient.top + m_sizeArrow.cy;
         pointa[2].x = rectClient.right;
         pointa[2].y = pointa[1].y;
         pointa[3].x = pointa[2].x;
         pointa[3].y = rectClient.bottom;
         pointa[4].x = rectClient.left + m_sizeArrow.cx;
         pointa[4].y = pointa[3].y;
         pointa[5].x = pointa[4].x;
         pointa[5].y = rectClient.top + m_sizeArrow.cy * 2;
      }*/

      // rgn.CreatePolygonRgn(pointa, 6, ALTERNATE);
      //   SetWindowRgn((HRGN) rgn.detach(), TRUE);
   }



   bool tool_tip_window::GetToolRect(i32 iTool, RECT * prect)

   {
      GetTool(iTool)->BaseToolTipGetRect(prect);

      return true;
   }

   void tool_tip_window::AddTool(::user::tool_tip_tool * ptool)
   {
      ptool->BaseToolTipSetHandler(this);
      m_toolmap.AddTool(ptool);
   }


   void tool_tip_window::CToolMap::AddTool(::user::tool_tip_tool * ptool)
   {
      ASSERT(ptool != nullptr);
      set_at(ptool->BaseToolTipGetIndex(), ptool);
   }

   bool tool_tip_window::GetToolText(i32 iTool, string &str)
   {
      ::user::tool_tip_tool * ptool = GetTool(iTool);

      if(ptool->m_uiBaseToolTipText != 0xffffffff)
      {
         ::exception::throw_not_implemented();
         //  str.load_string(ptool->m_uiBaseToolTipText);
         return true;
      }

      str.Empty();

      if(ptool->BaseToolTipGetText(str))
      {
         return true;
      }

      CText text;
      if(!m_puserinteraction->send_message(MessageBaseToolTipText, iTool, (LPARAM) &text))
         return false;
      str = text.m_str;

      return true;
   }

   ::user::tool_tip_tool * tool_tip_window::GetTool(i32 iTool)
   {
      return m_toolmap[iTool];
   }


   void tool_tip_window::RemoveAllTools()
   {
      m_toolmap.remove_all();
   }


   void tool_tip_window::SetPositionHint(::user::interaction * puserinteraction, e_position eposition)
   {

      ::rect rect;

      puserinteraction->get_window_rect(rect);

      ::point point;

      switch(eposition)
      {
      case PositionCenter:
         m_point.x = (rect.left + rect.right) / 2;
         m_point.y = (rect.top + rect.bottom) / 2;
         break;
      case PositionRandomTopRight:
         System.geometry().deflate(rect, 0.5, 0.0, 0.0, 0.5);
         point =  rect.random_point();
         break;
      default:
         ASSERT(FALSE);
         break;
      }


      m_point = point;
   }

} // namespace user
