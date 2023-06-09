#include "framework.h"
#include "tool_tip_window.h"
#include "tool_tip_tool.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/exception/interface_only.h"
#include "acme/primitive/geometry2d/_random.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"


namespace user
{


   tool_tip_window::tool_tip_window()
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
      
      ::pointer<::user::message>pusermessage(pmessage);

      switch(pusermessage->m_atom.as_i32())
      {
      case e_message_mouse_move:
      {

         auto puserinteraction = ::user::message_user_interaction(pusermessage);
         
         if(ptool->BaseToolTipGetWnd()->top_level() == puserinteraction)
         {
            
//            auto pwindow = window();
//
//            auto pointCursor = pwindow->get_cursor_position();

//            if(m_iEventTool != ptool->BaseToolTipGetIndex()
  //                || pointCursor != m_point)
            {
               
//               m_point = pointCursor;
               
               m_iEventTool = ptool->BaseToolTipGetIndex();
               
               //ptool->BaseToolTipGetWnd()->screen_to_client(&m_point);
               
               KillTimer(e_timer_show_delayed);
               
               HideTip();
               
               SetTimer(e_timer_show_delayed, 500_ms, nullptr);

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

//      if(!bForce)
//      {
//
//         auto pwindow = window();
//
//         auto pointCursor = pwindow->get_cursor_position();
//
//         if (pointCursor != m_point)
//         {
//
//            return;
//
//         }
//
//      }

      if(!GetToolText(iTool, m_strTip))
         return;

      SetTimer(1, 5_s, nullptr);

      ::rectangle_i32 rectangle;

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      GetToolRect(iTool, &rectangle);

      m_ealign = m_ealignDefault;

      ::pointer<::user::interaction>puserinteraction = m_puserinteraction;
      
      ::user::tool_tip_tool * ptool = GetTool(iTool);

      bool bVRetry = false;
      bool bHRetry = false;

      while(true)
      {
         
         m_sizeArrow.cx() = 12;
         
         m_sizeArrow.cy() = 12;

         if(((m_ealign & AlignLeft) == AlignLeft) &&
               ((m_ealign & AlignTop) == AlignTop))
         {
            m_pointOffset.x() = + (rectangle.width() == 0 ? 0 : rectangle.width() * 3 / 5);
            m_pointOffset.y() = + (rectangle.height() == 0 ? 0 : rectangle.height() * 3 / 5);
         }
         else if(((m_ealign & AlignRight) == AlignRight) &&
                 ((m_ealign & AlignTop) == AlignTop))
         {
            m_pointOffset.x() = - (rectangle.width() == 0 ? 0 : rectangle.width() * 3 / 5);
            m_pointOffset.y() = + (rectangle.height() == 0 ? 0 : rectangle.height() * 3 / 5);
         }
         else
         {
            m_pointOffset.x() = - (rectangle.width() == 0 ? 0 : rectangle.width() * 3 / 5);
            m_pointOffset.y() = - (rectangle.height() == 0 ? 0 : rectangle.height() * 3 / 5);
         }
         
         ::rectangle_i32 rectangleToolScreen;
         
         ptool->BaseToolTipGetRect(&rectangleToolScreen);
         
         ptool->BaseToolTipGetWnd()->client_to_screen()(rectangleToolScreen);
         
         CalcRect(pgraphics, &rectangle, rectangleToolScreen, m_strTip);

         ::rectangle_i32 rectangleScreen;

         auto pwindowing = windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectangle);

         ::size_i32 sizeScreen;

         sizeScreen = rectangleScreen.size();

         if(rectangle.right > sizeScreen.cx() && !bHRetry)
         {
            bHRetry = true;
            if(m_ealign & AlignRight)
            {
               m_ealign &= (EAlign) ~AlignRight;
               m_ealign |= AlignLeft;
               continue;
            }
         }
         if(rectangle.bottom > sizeScreen.cy() && !bVRetry)
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
   bool tool_tip_window::CalcRect(::draw2d::graphics_pointer & pgraphics, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleTool, const ::string & pcsz)
   {
      
      pgraphics->set(m_pfont);
      
      auto size = pgraphics->get_text_extent(pcsz);

      if(((m_ealign & AlignLeft) == AlignLeft) &&
            ((m_ealign & AlignTop) == AlignTop))
      {
         prectangle->right = m_point.x() - (m_point.x() - rectangleTool.left) / 2;

         prectangle->left = (::i32) (prectangle->right - size.cx() - m_sizeArrow.cx() - 4);

         prectangle->bottom = m_point.y() - (m_point.y() - rectangleTool.top) / 2;

         prectangle->top = (::i32) (prectangle->bottom - size.cy() - m_sizeArrow.cy() - 4);

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
              ((m_ealign & AlignTop) == AlignTop))
      {
         prectangle->left = m_point.x() + (rectangleTool.right - m_point.x()) / 2;

         prectangle->bottom = m_point.y() - (m_point.y() - rectangleTool.top) / 2;

         prectangle->right = (::i32) (prectangle->left + size.cx() + m_sizeArrow.cx() + 4);

         prectangle->top = (::i32) (prectangle->bottom - size.cy() - m_sizeArrow.cy() - 4);

      }
      else
      {
         prectangle->left = prectangle->right + m_pointOffset.x();

         prectangle->top = prectangle->bottom + m_pointOffset.y();

         prectangle->right = (::i32)(prectangle->left + size.cx() + m_sizeArrow.cx() + 4);

         prectangle->bottom = (::i32) (prectangle->top + size.cy() + m_sizeArrow.cy() + 4);

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
      throw ::interface_only();
      /*CPaintDC spgraphics(this);
      ::draw2d::graphics_pointer & pgraphics = &spgraphics;
      pgraphics->set(m_pfont);
      ::rectangle_i32 rectangleClient;
      client_rectangle(rectangleClient);
      ::rectangle_i32 rectangleText;
      pgraphics->SetBkMode(TRANSPARENT);
      if(((m_ealign & AlignLeft) == AlignLeft) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::rectangle_i32 rectangleArrow(rectangleClient.right - m_sizeArrow.cx() * 2, rectangleClient.bottom - m_sizeArrow.cy() * 2, rectangleClient.right, rectangleClient.bottom);
        rectangleClient.right -= m_sizeArrow.cx();
        rectangleClient.bottom -= m_sizeArrow.cy();
        pgraphics->fill_rectangle(rectangleArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectangleClient, rgb(220, 240, 250));
        pgraphics->draw_inset_3d_rectangle(rectangleClient, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectangleText = rectangleClient;
        rectangleText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectangleText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::rectangle_i32 rectangleArrow(0, rectangleClient.bottom - m_sizeArrow.cy() * 2, m_sizeArrow.cx() * 2, rectangleClient.bottom);
        rectangleClient.left = m_sizeArrow.cx();
        rectangleClient.bottom -= m_sizeArrow.cy();
        pgraphics->fill_rectangle(rectangleArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectangleClient, rgb(220, 240, 250));
        pgraphics->draw_inset_3d_rectangle(rectangleClient, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectangleText = rectangleClient;
        rectangleText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectangleText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else
      {
        ::rectangle_i32 rectangleArrow(0, 0, m_sizeArrow.cx() * 2, m_sizeArrow.cy() * 2);
        rectangleClient.left = m_sizeArrow.cx();
        rectangleClient.top = m_sizeArrow.cy();
        pgraphics->fill_rectangle(rectangleArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectangleClient, rgb(220, 240, 250));
        pgraphics->draw_inset_3d_rectangle(rectangleClient, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectangleText = rectangleClient;
        rectangleText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectangleText, e_align_bottom_left, e_draw_text_end_ellipsis);
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


   //bool tool_tip_window::create(::user::interaction * puserinteraction, const atom & atom)
   //{
   //   
   //   m_puserinteraction = puserinteraction;

   //   m_pfont->create_point_font(pnode->font_name(e_font_sans), 10.0);

   //   auto pusersystem = __new(::user::system);

   //   return create_window_ex(pusersystem, nullptr, atom) != 0;

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

      //return ::success;

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
      __construct(m_pfont);

      /*::draw2d::region rgn;
      ::rectangle_i32 rectangleClient;
      client_rectangle(rectangleClient);
      ::rectangle_i32 rectangleWindow;
      window_rectangle(rectangleWindow);
      screen_to_client(rectangleWindow);
      rectangleClient.offset(-rectangleWindow.top_left());
      const ::point_i32 & pointa[6];

      if(((m_ealign & AlignLeft) == AlignLeft) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pointa[0].x() = rectangleClient.left;
         pointa[0].y() = rectangleClient.top;
         pointa[1].x() = rectangleClient.right - m_sizeArrow.cx();
         pointa[1].y() = rectangleClient.top;
         pointa[2].x() = rectangleClient.right - m_sizeArrow.cx();
         pointa[2].y() = rectangleClient.bottom - m_sizeArrow.cy() * 2;
         pointa[3].x() = rectangleClient.right;
         pointa[3].y() = rectangleClient.bottom;
         pointa[4].x() = rectangleClient.right - m_sizeArrow.cx() * 2;
         pointa[4].y() = rectangleClient.bottom - m_sizeArrow.cy();
         pointa[5].x() = rectangleClient.left;
         pointa[5].y() = rectangleClient.bottom - m_sizeArrow.cy();

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pointa[0].x() = rectangleClient.left + m_sizeArrow.cx();
         pointa[0].y() = rectangleClient.top;
         pointa[1].x() = rectangleClient.right;
         pointa[1].y() = rectangleClient.top;
         pointa[2].x() = rectangleClient.right;
         pointa[2].y() = rectangleClient.bottom - m_sizeArrow.cy();
         pointa[3].x() = rectangleClient.left + m_sizeArrow.cx() * 2;
         pointa[3].y() = rectangleClient.bottom - m_sizeArrow.cy();
         pointa[4].x() = rectangleClient.left;
         pointa[4].y() = rectangleClient.bottom;
         pointa[5].x() = rectangleClient.left + m_sizeArrow.cx();
         pointa[5].y() = rectangleClient.bottom - m_sizeArrow.cy() * 2;

      }
      else
      {
         pointa[0].x() = rectangleClient.left;
         pointa[0].y() = rectangleClient.top;
         pointa[1].x() = rectangleClient.left + m_sizeArrow.cx() * 2;
         pointa[1].y() = rectangleClient.top + m_sizeArrow.cy();
         pointa[2].x() = rectangleClient.right;
         pointa[2].y() = pointa[1].y();
         pointa[3].x() = pointa[2].x();
         pointa[3].y() = rectangleClient.bottom;
         pointa[4].x() = rectangleClient.left + m_sizeArrow.cx();
         pointa[4].y() = pointa[3].y();
         pointa[5].x() = pointa[4].x();
         pointa[5].y() = rectangleClient.top + m_sizeArrow.cy() * 2;
      }*/

      // rgn.CreatePolygonRgn(pointa, 6, ALTERNATE);
      //   SetWindowRgn((HRGN) rgn.detach(), true);
   }



   bool tool_tip_window::GetToolRect(i32 iTool, ::rectangle_i32 * prectangle)

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
         throw ::interface_only();
         //  str.load_string(ptool->m_uiBaseToolTipText);
         return true;
      }

      str.empty();

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
      m_toolmap.erase_all();
   }


   void tool_tip_window::SetPositionHint(::user::interaction * puserinteraction, enum_position eposition)
   {

      ::rectangle_i32 rectangle;

      puserinteraction->window_rectangle(rectangle);

      ::point_i32 point;

      switch(eposition)
      {
      case PositionCenter:
         m_point.x() = (rectangle.left + rectangle.right) / 2;
         m_point.y() = (rectangle.top + rectangle.bottom) / 2;
         break;
      case PositionRandomTopRight:
         
         ::geometry::deflate(rectangle, 0.5, 0.0, 0.0, 0.5);

         point =  random_point(rectangle);

         break;
      default:
         ASSERT(false);
         break;
      }


      m_point = point;
   }

} // namespace user
