#include "framework.h"
#include "core/user/user/_user.h"
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
      set_tool_window();

   }

   tool_tip_window::~tool_tip_window()
   {
   }

   void tool_tip_window::relay_event(::user::tool_tip_tool * ptool, ::message::message * pmessage)
   {
      if(is_window())
         return;
      __pointer(::user::message) pusermessage(pmessage);
      switch(pusermessage->m_id)
      {
      case e_message_mouse_move:
      {
         
         if(ptool->BaseToolTipGetWnd()->get_top_level() == pusermessage->userinteraction())
         {
            
            auto psession = Session;

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            auto pointCursor = pwindowing->get_cursor_position();

            if(m_iEventTool != ptool->BaseToolTipGetIndex()
                  || pointCursor != m_point)
            {
               m_point = pointCursor;
               m_iEventTool = ptool->BaseToolTipGetIndex();
               //ptool->BaseToolTipGetWnd()->_001ScreenToClient(&m_point);
               KillTimer(e_timer_show_delayed);
               HideTip();
               SetTimer(e_timer_show_delayed, 500, nullptr);
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

         auto psession = Session;

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pointCursor = pwindowing->get_cursor_position();

         if (pointCursor != m_point)
         {

            return;

         }

      }

      if(!GetToolText(iTool, m_strTip))
         return;

      SetTimer(1, 5000, nullptr);

      ::rectangle_i32 rectangle;

      auto pgraphics = ::draw2d::create_memory_graphics();

      GetToolRect(iTool, rectangle);


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
            m_pointOffset.x = + (rectangle.width() == 0 ? 0 : rectangle.width() * 3 / 5);
            m_pointOffset.y = + (rectangle.height() == 0 ? 0 : rectangle.height() * 3 / 5);
         }
         else if(((m_ealign & AlignRight) == AlignRight) &&
                 ((m_ealign & AlignTop) == AlignTop))
         {
            m_pointOffset.x = - (rectangle.width() == 0 ? 0 : rectangle.width() * 3 / 5);
            m_pointOffset.y = + (rectangle.height() == 0 ? 0 : rectangle.height() * 3 / 5);
         }
         else
         {
            m_pointOffset.x = - (rectangle.width() == 0 ? 0 : rectangle.width() * 3 / 5);
            m_pointOffset.y = - (rectangle.height() == 0 ? 0 : rectangle.height() * 3 / 5);
         }
         ::rectangle_i32 rectToolScreen;
         ptool->BaseToolTipGetRect(rectToolScreen);
         ptool->BaseToolTipGetWnd()->_001ClientToScreen(rectToolScreen);
         CalcRect(pgraphics, rectangle, rectToolScreen, m_strTip);

         ::rectangle_i32 rectScreen;

         auto psession = Session;

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectangle);

         ::size_i32 sizeScreen;
         sizeScreen = rectScreen.size();

         if(rectangle.right > sizeScreen.cx && !bHRetry)
         {
            bHRetry = true;
            if(m_ealign & AlignRight)
            {
               m_ealign &= (EAlign) ~AlignRight;
               m_ealign |= AlignLeft;
               continue;
            }
         }
         if(rectangle.bottom > sizeScreen.cy && !bVRetry)
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


      order(e_zorder_top_most);
      
      place(rectangle);
      
      activation(e_activation_no_activate);

      update_drawing_objects();

      display(e_display_normal, e_activation_no_activate);
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: CalcRect
   //
   // Purpose:
   // Calculate the rectangle_i32 of the tip string.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::CalcRect(::draw2d::graphics_pointer & pgraphics, RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectTool, const char * pcsz)
   {
      
      pgraphics->set(m_font);
      
      auto size = pgraphics->GetTextExtent(pcsz);

      if(((m_ealign & AlignLeft) == AlignLeft) &&
            ((m_ealign & AlignTop) == AlignTop))
      {
         prectangle->right = m_point.x - (m_point.x - rectTool.left) / 2;

         prectangle->left = (::i32) (prectangle->right - size.cx - m_sizeArrow.cx - 4);

         prectangle->bottom = m_point.y - (m_point.y - rectTool.top) / 2;

         prectangle->top = (::i32) (prectangle->bottom - size.cy - m_sizeArrow.cy - 4);

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
              ((m_ealign & AlignTop) == AlignTop))
      {
         prectangle->left = m_point.x + (rectTool.right - m_point.x) / 2;

         prectangle->bottom = m_point.y - (m_point.y - rectTool.top) / 2;

         prectangle->right = (::i32) (prectangle->left + size.cx + m_sizeArrow.cx + 4);

         prectangle->top = (::i32) (prectangle->bottom - size.cy - m_sizeArrow.cy - 4);

      }
      else
      {
         prectangle->left = prectangle->right + m_pointOffset.x;

         prectangle->top = prectangle->bottom + m_pointOffset.y;

         prectangle->right = (::i32)(prectangle->left + size.cx + m_sizeArrow.cx + 4);

         prectangle->bottom = (::i32) (prectangle->top + size.cy + m_sizeArrow.cy + 4);

      }
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnPaint
   //
   // Purpose:
   // e_message_paint message handler.
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
      ::rectangle_i32 rectClient;
      get_client_rect(rectClient);
      ::rectangle_i32 rectText;
      pgraphics->SetBkMode(TRANSPARENT);
      if(((m_ealign & AlignLeft) == AlignLeft) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::rectangle_i32 rectArrow(rectClient.right - m_sizeArrow.cx * 2, rectClient.bottom - m_sizeArrow.cy * 2, rectClient.right, rectClient.bottom);
        rectClient.right -= m_sizeArrow.cx;
        rectClient.bottom -= m_sizeArrow.cy;
        pgraphics->fill_rectangle(rectArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectClient, rgb(220, 240, 250));
        pgraphics->draw3d_rect(rectClient, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectText = rectClient;
        rectText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::rectangle_i32 rectArrow(0, rectClient.bottom - m_sizeArrow.cy * 2, m_sizeArrow.cx * 2, rectClient.bottom);
        rectClient.left = m_sizeArrow.cx;
        rectClient.bottom -= m_sizeArrow.cy;
        pgraphics->fill_rectangle(rectArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectClient, rgb(220, 240, 250));
        pgraphics->draw3d_rect(rectClient, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectText = rectClient;
        rectText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else
      {
        ::rectangle_i32 rectArrow(0, 0, m_sizeArrow.cx * 2, m_sizeArrow.cy * 2);
        rectClient.left = m_sizeArrow.cx;
        rectClient.top = m_sizeArrow.cy;
        pgraphics->fill_rectangle(rectArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectClient, rgb(220, 240, 250));
        pgraphics->draw3d_rect(rectClient, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
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
   // Handler for e_message_timer message
   //
   // Output:
   // none
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnTimer(::u32 uEvent)
   {
      switch(uEvent)
      {
      case e_timer_hide_window:
      {
         display(e_display_none);
         KillTimer(uEvent);
      }
      break;
      case e_timer_show_delayed:
      {
         m_iTool = m_iEventTool;
         ShowTip();
         KillTimer(uEvent);
      }
      default:
         break;
      }


   }


   //bool tool_tip_window::create(::user::interaction * puserinteraction, const id & id)
   //{
   //   
   //   m_puserinteraction = puserinteraction;

   //   m_font->create_point_font(os_font_name(e_font_sans), 10.0);

   //   auto pusersystem = __new(::user::system);

   //   return create_window_ex(pusersystem, nullptr, id) != 0;

   //}

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
   void tool_tip_window::OnSize(::u32 nType, i32 cx, i32 cy)
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
         display(e_display_none);
      }
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: EnableTip()
   //
   // Purpose:
   // enable the tip.
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
   // Function Name: on_destroy()
   //
   // Purpose:
   // Destroy the tip.
   //
   // Output:
   // None.
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::on_destroy()
   {
      //    window::on_destroy();
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
      ::rectangle_i32 rectClient;
      get_client_rect(rectClient);
      ::rectangle_i32 rectWindow;
      get_window_rect(rectWindow);
      _001ScreenToClient(rectWindow);
      rectClient.offset(-rectWindow.top_left());
      const ::point_i32 & pointa[6];

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
      //   SetWindowRgn((HRGN) rgn.detach(), true);
   }



   bool tool_tip_window::GetToolRect(i32 iTool, RECTANGLE_I32 * prectangle)

   {
      GetTool(iTool)->BaseToolTipGetRect(prectangle);

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
      
      if (!m_puserinteraction->send_message(MessageBaseToolTipText, iTool, (lparam)&text))
      {

         return false;

      }

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


   void tool_tip_window::SetPositionHint(::user::interaction * puserinteraction, enum_position eposition)
   {

      ::rectangle_i32 rectangle;

      puserinteraction->get_window_rect(rectangle);

      ::point_i32 point;

      switch(eposition)
      {
      case PositionCenter:
         m_point.x = (rectangle.left + rectangle.right) / 2;
         m_point.y = (rectangle.top + rectangle.bottom) / 2;
         break;
      case PositionRandomTopRight:
         System->geometry().deflate(rectangle, 0.5, 0.0, 0.0, 0.5);
         point =  rectangle.random_point();
         break;
      default:
         ASSERT(false);
         break;
      }


      m_point = point;
   }

} // namespace user
