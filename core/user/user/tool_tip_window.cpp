#include "framework.h"
#include "tool_tip_window.h"
#include "tool_tip_tool.h"
#include "acme/constant/user_message.h"
#include "acme/constant/timer.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/geometry2d/geometry.h"
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
      
      if (is_window())
      {

         return;

      }
      
      ::pointer<::user::message>pusermessage(pmessage);

      switch(pusermessage->m_eusermessage)
      {
      case ::user::e_message_mouse_move:
      {

         auto puserinteraction = pusermessage->user_interaction();
         
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
               
               kill_timer(e_timer_show_delayed);
               
               HideTip();
               
               set_timer(e_timer_show_delayed, 500_ms, nullptr);

            }

         }

      }
      break;
      default:
         break;
      }
   }


   void tool_tip_window::ShowTip(
   int iTool,    // [in] item selected
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

      set_timer(1, 5_s, nullptr);

      ::int_rectangle rectangle;

      auto psystem = system();

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
         
         ::int_rectangle rectangleToolScreen;
         
         ptool->BaseToolTipGetRect(&rectangleToolScreen);
         
         ptool->BaseToolTipGetWnd()->client_to_screen()(rectangleToolScreen);
         
         CalcRect(pgraphics, &rectangle, rectangleToolScreen, m_strTip);

         ::int_rectangle rectangleScreen;

         auto pwindowing = windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectangle);

         ::int_size sizeScreen;

         sizeScreen = rectangleScreen.size();

         if(rectangle.right() > sizeScreen.cx() && !bHRetry)
         {
            bHRetry = true;
            if(m_ealign & AlignRight)
            {
               m_ealign &= (EAlign) ~AlignRight;
               m_ealign |= AlignLeft;
               continue;
            }
         }
         if(rectangle.bottom() > sizeScreen.cy() && !bVRetry)
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
      
      activation({ ::user::e_activation_no_activate });

      update_drawing_objects();

      display(e_display_normal, { ::user::e_activation_no_activate });
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: CalcRect
   //
   // Purpose:
   // Calculate the int_rectangle of the tip string.
   //
   // Output:
   // True if successfull.
   //
   //
   ///////////////////////////////////////////////////////////
   bool tool_tip_window::CalcRect(::draw2d::graphics_pointer & pgraphics, ::int_rectangle * prectangle, const ::int_rectangle & rectangleTool, const ::scoped_string & scopedstr)
   {
      
      pgraphics->set(m_pfont);
      
      auto size = pgraphics->get_text_extent(scopedstr);

      if(((m_ealign & AlignLeft) == AlignLeft) &&
            ((m_ealign & AlignTop) == AlignTop))
      {
         prectangle->right() = m_point.x() - (m_point.x() - rectangleTool.left()) / 2;

         prectangle->left() = (int) (prectangle->right() - size.cx() - m_sizeArrow.cx() - 4);

         prectangle->bottom() = m_point.y() - (m_point.y() - rectangleTool.top()) / 2;

         prectangle->top() = (int) (prectangle->bottom() - size.cy() - m_sizeArrow.cy() - 4);

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
              ((m_ealign & AlignTop) == AlignTop))
      {
         prectangle->left() = m_point.x() + (rectangleTool.right() - m_point.x()) / 2;

         prectangle->bottom() = m_point.y() - (m_point.y() - rectangleTool.top()) / 2;

         prectangle->right() = (int) (prectangle->left() + size.cx() + m_sizeArrow.cx() + 4);

         prectangle->top() = (int) (prectangle->bottom() - size.cy() - m_sizeArrow.cy() - 4);

      }
      else
      {
         prectangle->left() = prectangle->right() + m_pointOffset.x();

         prectangle->top() = prectangle->bottom() + m_pointOffset.y();

         prectangle->right() = (int)(prectangle->left() + size.cx() + m_sizeArrow.cx() + 4);

         prectangle->bottom() = (int) (prectangle->top() + size.cy() + m_sizeArrow.cy() + 4);

      }
      return true;
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnPaint
   //
   // Purpose:
   // ::user::e_message_paint message handler.
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
      auto rectangleX = this->rectangle();
      ::int_rectangle rectangleText;
      pgraphics->SetBkMode(TRANSPARENT);
      if(((m_ealign & AlignLeft) == AlignLeft) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::int_rectangle rectangleArrow(rectangleX.right() - m_sizeArrow.cx() * 2, rectangleX.bottom() - m_sizeArrow.cy() * 2, rectangleX.right(), rectangleX.bottom());
        rectangleX.right() -= m_sizeArrow.cx();
        rectangleX.bottom() -= m_sizeArrow.cy();
        pgraphics->fill_rectangle(rectangleArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectangleX, rgb(220, 240, 250));
        pgraphics->draw_inset_3d_rectangle(rectangleX, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectangleText = rectangleX;
        rectangleText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectangleText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
        ((m_ealign & AlignTop) == AlignTop))
      {
        ::int_rectangle rectangleArrow(0, rectangleX.bottom() - m_sizeArrow.cy() * 2, m_sizeArrow.cx() * 2, rectangleX.bottom());
        rectangleX.left() = m_sizeArrow.cx();
        rectangleX.bottom() -= m_sizeArrow.cy();
        pgraphics->fill_rectangle(rectangleArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectangleX, rgb(220, 240, 250));
        pgraphics->draw_inset_3d_rectangle(rectangleX, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectangleText = rectangleX;
        rectangleText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectangleText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }
      else
      {
        ::int_rectangle rectangleArrow(0, 0, m_sizeArrow.cx() * 2, m_sizeArrow.cy() * 2);
        rectangleX.left() = m_sizeArrow.cx();
        rectangleX.top() = m_sizeArrow.cy();
        pgraphics->fill_rectangle(rectangleArrow, rgb(0, 120, 180));
        pgraphics->fill_rectangle(rectangleX, rgb(220, 240, 250));
        pgraphics->draw_inset_3d_rectangle(rectangleX, rgb(0, 120, 180), rgb(0, 120, 180));
        pgraphics->set_text_color(rgb(0, 60, 90));
        rectangleText = rectangleX;
        rectangleText.deflate(2, 2, 2, 2);
        pgraphics->draw_text(m_strTip, rectangleText, e_align_bottom_left, e_draw_text_end_ellipsis);
      }*/
   }

   ///////////////////////////////////////////////////////////
   //
   // Function Name: OnTimer()
   //
   // Purpose:
   // Handler for ::user::e_message_timer message
   //
   // Output:
   // none
   //
   //
   ///////////////////////////////////////////////////////////
   void tool_tip_window::OnTimer(unsigned int uEvent)
   {
      switch(uEvent)
      {
      case e_timer_hide_window:
      {
         display(e_display_none);
         kill_timer(uEvent);
      }
      break;
      case e_timer_show_delayed:
      {
         m_iTool = m_iEventTool;
         ShowTip();
         kill_timer(uEvent);
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

   //   auto pusersystem = øallocate ::user::system();

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
   void tool_tip_window::OnSize(unsigned int nType, int cx, int cy)
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
      øconstruct(m_pfont);

      /*::draw2d::region rgn;
      auto rectangleX = this->rectangle();
      ::int_rectangle rectangleWindow;
      window_rectangle(rectangleWindow);
      screen_to_client(rectangleWindow);
      rectangleX.offset(-rectangleWindow.top_left());
      const ::int_point & pointa[6];

      if(((m_ealign & AlignLeft) == AlignLeft) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pointa[0].x() = rectangleX.left();
         pointa[0].y() = rectangleX.top();
         pointa[1].x() = rectangleX.right() - m_sizeArrow.cx();
         pointa[1].y() = rectangleX.top();
         pointa[2].x() = rectangleX.right() - m_sizeArrow.cx();
         pointa[2].y() = rectangleX.bottom() - m_sizeArrow.cy() * 2;
         pointa[3].x() = rectangleX.right();
         pointa[3].y() = rectangleX.bottom();
         pointa[4].x() = rectangleX.right() - m_sizeArrow.cx() * 2;
         pointa[4].y() = rectangleX.bottom() - m_sizeArrow.cy();
         pointa[5].x() = rectangleX.left();
         pointa[5].y() = rectangleX.bottom() - m_sizeArrow.cy();

      }
      else if(((m_ealign & AlignRight) == AlignRight) &&
         ((m_ealign & AlignTop) == AlignTop))
      {
         pointa[0].x() = rectangleX.left() + m_sizeArrow.cx();
         pointa[0].y() = rectangleX.top();
         pointa[1].x() = rectangleX.right();
         pointa[1].y() = rectangleX.top();
         pointa[2].x() = rectangleX.right();
         pointa[2].y() = rectangleX.bottom() - m_sizeArrow.cy();
         pointa[3].x() = rectangleX.left() + m_sizeArrow.cx() * 2;
         pointa[3].y() = rectangleX.bottom() - m_sizeArrow.cy();
         pointa[4].x() = rectangleX.left();
         pointa[4].y() = rectangleX.bottom();
         pointa[5].x() = rectangleX.left() + m_sizeArrow.cx();
         pointa[5].y() = rectangleX.bottom() - m_sizeArrow.cy() * 2;

      }
      else
      {
         pointa[0].x() = rectangleX.left();
         pointa[0].y() = rectangleX.top();
         pointa[1].x() = rectangleX.left() + m_sizeArrow.cx() * 2;
         pointa[1].y() = rectangleX.top() + m_sizeArrow.cy();
         pointa[2].x() = rectangleX.right();
         pointa[2].y() = pointa[1].y();
         pointa[3].x() = pointa[2].x();
         pointa[3].y() = rectangleX.bottom();
         pointa[4].x() = rectangleX.left() + m_sizeArrow.cx();
         pointa[4].y() = pointa[3].y();
         pointa[5].x() = pointa[4].x();
         pointa[5].y() = rectangleX.top() + m_sizeArrow.cy() * 2;
      }*/

      // rgn.CreatePolygonRgn(pointa, 6, ALTERNATE);
      //   SetWindowRgn((HRGN) rgn.detach(), true);
   }



   bool tool_tip_window::GetToolRect(int iTool, ::int_rectangle * prectangle)

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

   bool tool_tip_window::GetToolText(int iTool, string &str)
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
      
      if (!m_puserinteraction->send_message(::user::e_message_tool_tip_text, iTool, (lparam)&text))
      {

         return false;

      }

      str = text.m_str;

      return true;
   }

   ::user::tool_tip_tool * tool_tip_window::GetTool(int iTool)
   {
      return m_toolmap[iTool];
   }


   void tool_tip_window::RemoveAllTools()
   {
      m_toolmap.erase_all();
   }


   void tool_tip_window::SetPositionHint(::user::interaction * puserinteraction, enum_position eposition)
   {

      ::int_rectangle rectangle;

      puserinteraction->window_rectangle(rectangle);

      ::int_point point;

      switch(eposition)
      {
      case PositionCenter:
         m_point.x() = (rectangle.left() + rectangle.right()) / 2;
         m_point.y() = (rectangle.top() + rectangle.bottom()) / 2;
         break;
      case PositionRandomTopRight:
         
         ::geometry::deflate(rectangle, 0.5, 0.0, 0.0, 0.5);

         point = system()->geometry()->random_point(rectangle);

         break;
      default:
         ASSERT(false);
         break;
      }


      m_point = point;
   }

} // namespace user
