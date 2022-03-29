#include "framework.h"
#include "aura/operating_system.h"
//#include "aura/user/_user.h"
#include "acme/operating_system/_user.h"
#include "aura/graphics/draw2d/graphics.h"


namespace user
{


   horizontal_scroll_base::horizontal_scroll_base()
   {

      m_scrolldataHorizontal.m_bScroll = false;
      m_scrolldataHorizontal.m_iPage = 0;
      m_scrolldataHorizontal.m_iLine = 0;
      m_scrolldataHorizontal.m_bScrollEnable = true;
      //m_scrolldataHorizontal.m_iWidth = GetSystemMetrics(SM_CXHSCROLL);

   }


   horizontal_scroll_base::~horizontal_scroll_base()
   {


   }


   scroll_bar* horizontal_scroll_base::get_horizontal_scroll_bar()
   {

      return m_pscrollbarHorizontal;

   }


   scroll_data* horizontal_scroll_base::get_horizontal_scroll_data()
   {

      return &m_scrolldataHorizontal;

   }


   void horizontal_scroll_base::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      ::user::interaction::get_client_rect(rectangleClient);

      defer_create_horizontal_scroll_bar();

      if (m_pscrollbarHorizontal)
      {

         if (m_scrolldataHorizontal.m_bScroll)
         {

            get_horizontal_scroll_info(m_pscrollbarHorizontal->m_scrollinfo);

            ::rectangle_i32 rectangleNewPos;

            auto pstyle = get_style(pgraphics);

            rectangleNewPos.left = rectangleClient.left;
            rectangleNewPos.top = rectangleClient.bottom - get_int(pstyle,e_int_scroll_bar_width);
            rectangleNewPos.right = rectangleNewPos.left + rectangleClient.width() - get_final_y_scroll_bar_width();
            rectangleNewPos.bottom = rectangleClient.bottom;

            m_pscrollbarHorizontal->order(e_zorder_top);

            m_pscrollbarHorizontal->place(rectangleNewPos);

            m_pscrollbarHorizontal->display();

            //m_pscrollbarHorizontal->set_need_redraw();

            //m_pscrollbarHorizontal->set_need_layout();

         }
         else
         {

            m_pscrollbarHorizontal->display(e_display_none);

         }

         set_need_redraw();

      }

   }


   //bool horizontal_scroll_base::create_horizontal_scroll_bar()
   //{

   //   if (m_scrolldataHorizontal.m_bScrollEnable)
   //   {

   //      if (!m_pscrollbarHorizontal)
   //      {

   //         create_horizontal_scroll_bar();

   //      }

   //   }

   //}


   void horizontal_scroll_base::defer_create_horizontal_scroll_bar()
   {

      bool bCreate = false;

      if (m_scrolldataHorizontal.m_bScrollEnable)
      {

         if (m_pscrollbarHorizontal == nullptr)
         {

            bCreate = true;

         }

      }

      if (bCreate)
      {

         create_horizontal_scroll_bar();

      }

   }


   void horizontal_scroll_base::_001OnHScroll(::message::message * pmessage)
   {

      __pointer(::message::scroll) pscroll(pmessage);

      queue_graphics_call([this, pscroll](::draw2d::graphics_pointer & pgraphics)
         {

            if (pscroll->m_ecommand == e_scroll_command_line_left)
            {

               set_viewport_offset_x(pgraphics, (::i32)(get_viewport_offset().x - m_scrolldataHorizontal.m_iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_left)
            {

               set_viewport_offset_x(pgraphics, (::i32)(get_viewport_offset().x - m_scrolldataHorizontal.m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_right)
            {

               set_viewport_offset_x(pgraphics, (::i32)(get_viewport_offset().x + m_scrolldataHorizontal.m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_line_right)
            {

               set_viewport_offset_x(pgraphics, (::i32)(get_viewport_offset().x + m_scrolldataHorizontal.m_iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_track)
            {

               set_viewport_offset_x(pgraphics, pscroll->m_nPos);

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_position)
            {

               set_viewport_offset_x(pgraphics, pscroll->m_nPos);

            }

         });

   }


   void horizontal_scroll_base::on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pscrollbarHorizontal.is_set())
      {

         m_pscrollbarHorizontal->m_scrollinfo.nPos = m_pointScroll.x;

      }

   }


   bool horizontal_scroll_base::validate_viewport_offset(point_i32 & point)
   {

      if (point.x < 0)
      {

         point.x = 0;

      }
      else
      {

         auto sizeTotal = get_total_size();

         auto sizePage = get_page_size();

         if (point.x > maximum(0, sizeTotal.cx - sizePage.cx))
         {

            point.x = (::i32) maximum(0, sizeTotal.cx - sizePage.cx);

         }

      }

      return true;

   }


   void horizontal_scroll_base::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_hscroll, pchannel, this, &horizontal_scroll_base::_001OnHScroll);

   }


   void horizontal_scroll_base::on_change_view_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto sizeTotal = get_total_size();

      auto pstyle = get_style(pgraphics);

      m_scrolldataHorizontal.m_iWidth = get_int(pstyle, e_int_scroll_bar_width);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::i32 iTotalHeight = (::i32) sizeTotal.cy;

      ::i32 iTotalWidth = (::i32) sizeTotal.cx;

      ::i32 iClientHeight = rectangleClient.height();

      ::i32 iClientWidth = rectangleClient.width();

      //::i32 iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      ::i32 iScrollWidth = iClientWidth - get_int(pstyle, e_int_scroll_bar_width);;

      m_scrolldataHorizontal.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorizontal.m_bScroll = true;

      }
      else if (iTotalHeight > iClientHeight)
      {

         if (iTotalWidth > iScrollWidth)
         {

            m_scrolldataHorizontal.m_bScroll = true;

         }

      }

      m_scrolldataHorizontal.m_bScroll = m_scrolldataHorizontal.m_bScrollEnable && m_scrolldataHorizontal.m_bScroll;

      ::rectangle_i32 rectangleScroll;

      get_client_rect(rectangleScroll);

      m_scrolldataHorizontal.m_iPage = rectangleScroll.width();

      if (validate_viewport_offset(m_pointScroll))
      {

         layout_scroll_bar(pgraphics);

         on_change_viewport_offset(pgraphics);

      }

   }


   int horizontal_scroll_base::get_final_x_scroll_bar_width()
   {

      return m_scrolldataHorizontal.m_bScroll && m_scrolldataHorizontal.m_bScrollEnable ? m_scrolldataHorizontal.m_iWidth : 0;

   }











   vertical_scroll_base::vertical_scroll_base()
   {

      m_iWheelDeltaScroll = 3;
      m_scrolldataVertical.m_bScroll = false;
      m_scrolldataVertical.m_iPage = 0;
      m_scrolldataVertical.m_iLine = 0;
      m_scrolldataVertical.m_bScrollEnable = true;
//      m_scrolldataVertical.m_iWidth = GetSystemMetrics(SM_CYVSCROLL);

   }

   vertical_scroll_base::~vertical_scroll_base()
   {

   }


   scroll_bar* vertical_scroll_base::get_vertical_scroll_bar()
   {

      return m_pscrollbarVertical;

   }


   scroll_data* vertical_scroll_base::get_vertical_scroll_data()
   {

      return &m_scrolldataVertical;

   }


   void vertical_scroll_base::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient = get_client_rect();

      //scroll_bar_get_client_rect(rectangleClient);

//      i32 ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      defer_create_vertical_scroll_bar();

      if (m_pscrollbarVertical != nullptr)
      {

         if (m_scrolldataVertical.m_bScroll)
         {

            get_vertical_scroll_info(m_pscrollbarVertical->m_scrollinfo);

            ::rectangle_i32 rectangleNewPos;

            auto pstyle = get_style(pgraphics);

            int iScrollBarWidth = get_int(pstyle,e_int_scroll_bar_width);

            rectangleNewPos.left = rectangleClient.right - iScrollBarWidth;
            rectangleNewPos.top = rectangleClient.top;
            rectangleNewPos.right = rectangleClient.right;
            rectangleNewPos.bottom = rectangleNewPos.top+ rectangleClient.height() - get_final_x_scroll_bar_width();

            m_pscrollbarVertical->order(e_zorder_top);

            m_pscrollbarVertical->place(rectangleNewPos);

            m_pscrollbarVertical->display();

         }
         else
         {

            m_pscrollbarVertical->display(e_display_none);

         }

         set_need_redraw();

      }

   }


   //void vertical_scroll_base::_001OnDeferCreateYScrollBar()
   //{

   //   if (m_scrolldataVertical.m_bScrollEnable)
   //   {

   //      if (m_pscrollbarVertical == nullptr)
   //      {

   //         create_y_scroll_bar(nullptr);

   //      }

   //   }

   //}


   void vertical_scroll_base::defer_create_vertical_scroll_bar()
   {

      bool bCreate = false;

      if (m_scrolldataVertical.m_bScrollEnable)
      {

         if (m_pscrollbarVertical == nullptr)
         {

            bCreate = true;

         }

      }

      if (bCreate)
      {

         create_vertical_scroll_bar();

      }

   }


   void vertical_scroll_base::_001OnVScroll(::message::message * pmessage)
   {

      __pointer(::message::scroll) pscroll(pmessage);

      queue_graphics_call([this, pscroll](::draw2d::graphics_pointer & pgraphics)
         {

            if (pscroll->m_ecommand == e_scroll_command_line_up)
            {

               set_viewport_offset_y(pgraphics, (::i32)(get_viewport_offset().y - m_scrolldataVertical.m_iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_up)
            {

               set_viewport_offset_y(pgraphics, (::i32)(get_viewport_offset().y - m_scrolldataVertical.m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_down)
            {

               set_viewport_offset_y(pgraphics, (::i32)(get_viewport_offset().y + m_scrolldataVertical.m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_line_down)
            {

               set_viewport_offset_y(pgraphics, (::i32)(get_viewport_offset().y + m_scrolldataVertical.m_iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_track)
            {

               set_viewport_offset_y(pgraphics, pscroll->m_nPos);

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_position)
            {

               set_viewport_offset_y(pgraphics, pscroll->m_nPos);

            }

         });

   }



   i32 vertical_scroll_base::get_wheel_scroll_delta()
   {

      return m_iWheelDeltaScroll;

   }


   void vertical_scroll_base::on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pscrollbarVertical.is_set())
      {

         m_pscrollbarVertical->m_scrollinfo.nPos = m_pointScroll.y;

      }

   }


   void vertical_scroll_base::_001OnMouseWheel(::message::message * pmessage)
   {

      if (!m_scrolldataVertical.m_bScroll || !m_scrolldataVertical.m_bScrollEnable)
      {

         return;

      }

      __pointer(::message::mouse_wheel) pmousewheel(pmessage);

      if (pmousewheel->GetDelta() > 0)
      {
         if (m_iWheelDelta > 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }
      else if (pmousewheel->GetDelta() < 0)
      {
         if (m_iWheelDelta < 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (i16)(WHEEL_DELTA * iDelta);

      index nPos = m_pscrollbarVertical->m_scrollinfo.nPos - iDelta * get_wheel_scroll_delta();

      if (nPos < m_pscrollbarVertical->m_scrollinfo.nMin)
         nPos = m_pscrollbarVertical->m_scrollinfo.nMin;
      else if (nPos > m_pscrollbarVertical->m_scrollinfo.nMax - m_pscrollbarVertical->m_scrollinfo.nPage)
         nPos = m_pscrollbarVertical->m_scrollinfo.nMax - m_pscrollbarVertical->m_scrollinfo.nPage;

      m_pscrollbarVertical->m_scrollinfo.nPos =  (i32) nPos;

      m_pscrollbarVertical->post_scroll_message(e_scroll_command_thumb_position);

      pmousewheel->m_lresult = 0;

      pmousewheel->m_bRet = true;

   }


   bool vertical_scroll_base::validate_viewport_offset(point_i32 & point)
   {

      if (point.y < 0)
      {

         point.y = 0;

      }
      else
      {

         auto sizeTotal = get_total_size();

         auto sizePage = get_page_size();

         if (point.y > maximum(0, sizeTotal.cy - sizePage.cy))
         {

            point.y = (::i32) maximum(0, sizeTotal.cy - sizePage.cy);

         }

      }

      return true;

   }




   void vertical_scroll_base::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_vscroll, pchannel, this, &vertical_scroll_base::_001OnVScroll);
      MESSAGE_LINK(e_message_mouse_wheel, pchannel, this, &vertical_scroll_base::_001OnMouseWheel);

   }


   void vertical_scroll_base::on_change_view_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto sizeTotal = get_total_size();

      auto pstyle = get_style(pgraphics);

      m_scrolldataVertical.m_iWidth = get_int(pstyle, e_int_scroll_bar_width);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::i32 iTotalHeight = (::i32) sizeTotal.cy;

      ::i32 iTotalWidth = (::i32) sizeTotal.cx;

      ::i32 iClientHeight = rectangleClient.height();

      ::i32 iClientWidth = rectangleClient.width();

      ::i32 iScrollHeight = iClientHeight - get_int(pstyle, e_int_scroll_bar_width);

      //::i32 iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataVertical.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVertical.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVertical.m_bScroll = true;

      }

      m_scrolldataVertical.m_bScroll = m_scrolldataVertical.m_bScrollEnable && m_scrolldataVertical.m_bScroll;

      ::rectangle_i32 rectangleScroll;

      get_client_rect(rectangleScroll);

      m_scrolldataVertical.m_iPage = rectangleScroll.height();

      if (validate_viewport_offset(m_pointScroll))
      {

         layout_scroll_bar(pgraphics);

         on_change_viewport_offset(pgraphics);

      }

   }



   int vertical_scroll_base::get_final_y_scroll_bar_width()
   {

      return m_scrolldataVertical.m_bScroll && m_scrolldataVertical.m_bScrollEnable ? m_scrolldataVertical.m_iWidth : 0;

   }

   //
   //void vertical_scroll_base::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //   BASE::on_layout(pgraphics);

   //   on_change_view_size();

   //}


   scroll_base::scroll_base()
   {

   }


   scroll_base::~scroll_base()
   {

   }


   void scroll_base::install_message_routing(::channel * pchannel)
   {
      horizontal_scroll_base::install_message_routing(pchannel);
      vertical_scroll_base::install_message_routing(pchannel);
   }


   void scroll_base::on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      horizontal_scroll_base::on_change_viewport_offset(pgraphics);

      vertical_scroll_base::on_change_viewport_offset(pgraphics);

      ::user::interaction::on_change_viewport_offset(pgraphics);

   }


   bool scroll_base::validate_viewport_offset(point_i32 & point)
   {

      bool xValidated = horizontal_scroll_base::validate_viewport_offset(point);

      bool yValidated = vertical_scroll_base::validate_viewport_offset(point);

      bool iValidated = ::user::interaction::validate_viewport_offset(point);

      return (xValidated || yValidated) && iValidated;

   }


   void scroll_base::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   {

      horizontal_scroll_base::layout_scroll_bar(pgraphics);

      vertical_scroll_base::layout_scroll_bar(pgraphics);

   }


   void scroll_base::on_change_view_size(::draw2d::graphics_pointer & pgraphics)
   {

      m_scrolldataHorizontal.m_bScroll = false;

      m_scrolldataVertical.m_bScroll = false;

      auto sizeTotal = get_total_size();

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if(rectangleClient.area() <= 0)
      {

         return;

      }

      auto pstyle = get_style(pgraphics);

      ::i32 iTotalHeight = (::i32) sizeTotal.cy;

      ::i32 iTotalWidth = (::i32) sizeTotal.cx;

      ::i32 iClientHeight = rectangleClient.height();

      ::i32 iClientWidth = rectangleClient.width();

      ::i32 iScrollHeight = iClientHeight - get_int(pstyle, e_int_scroll_bar_width);;

      ::i32 iscrollWidth = iClientWidth - get_int(pstyle, e_int_scroll_bar_width);;

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorizontal.m_bScroll = true;

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVertical.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVertical.m_bScroll = true;

         if (iTotalWidth > iscrollWidth)
         {

            m_scrolldataHorizontal.m_bScroll = true;

         }

      }

      m_scrolldataHorizontal.m_bScroll = m_scrolldataHorizontal.m_bScrollEnable && m_scrolldataHorizontal.m_bScroll;

      m_scrolldataVertical.m_bScroll = m_scrolldataVertical.m_bScrollEnable && m_scrolldataVertical.m_bScroll;

      if (!m_scrolldataHorizontal.m_bScroll)
      {

         m_pointScroll.x = 0;

      }


      if (!m_scrolldataVertical.m_bScroll)
      {

         m_pointScroll.y = 0;

      }


      ::rectangle_i32 rectangleScroll;

      get_client_rect(rectangleScroll);

      m_scrolldataHorizontal.m_iPage = rectangleScroll.width();

      m_scrolldataVertical.m_iPage = rectangleScroll.height();

      if (validate_viewport_offset(m_pointScroll))
      {

         layout_scroll_bar(pgraphics);

         on_change_viewport_offset(pgraphics);

      }
      else
      {

         layout_scroll_bar(pgraphics);

      }

   }


   void horizontal_scroll_base::send_xscroll_message(enum_scroll_command ecommand)
   {

      auto pscroll = __new(::message::scroll);

      pscroll->m_ecommand = ecommand;

      if (m_pscrollbarHorizontal.is_set())
      {

         pscroll->m_nPos = m_pscrollbarHorizontal->m_scrollinfo.nPos;

      }
      else
      {

         pscroll->m_nPos = (i32) get_viewport_offset().x;

      }

      pscroll->m_atom = e_message_hscroll;

      send(pscroll);

   }


   bool horizontal_scroll_base::create_horizontal_scroll_bar()
   {

      if (m_pscrollbarHorizontal)
      {

         return true;

      }

      auto pbar = __create < scroll_bar > ();

      pbar->m_eorientation = ::e_orientation_horizontal;

      pbar->create_child(this);

      //if (!)
      //{

      //   return false;

      //}

      m_pscrollbarHorizontal = pbar;

      return true;

   }


   void horizontal_scroll_base::scroll_left_line()
   {

      send_xscroll_message(e_scroll_command_line_left);

   }


   void horizontal_scroll_base::scroll_right_line()
   {

      send_xscroll_message(e_scroll_command_line_right);

   }


   void horizontal_scroll_base::scroll_left_page()
   {

      send_xscroll_message(e_scroll_command_page_left);

   }


   void horizontal_scroll_base::scroll_right_page()
   {

      send_xscroll_message(e_scroll_command_page_right);

   }


   void horizontal_scroll_base::scroll_horz(int nPos)
   {

      queue_graphics_call([this, nPos](::draw2d::graphics_pointer & pgraphics)
         {

            set_viewport_offset_x(pgraphics, nPos);

         });

   }


   void vertical_scroll_base::send_yscroll_message(enum_scroll_command ecommand)
   {

      auto pscroll = __new(::message::scroll);

      pscroll->m_ecommand = ecommand;

      if (m_pscrollbarVertical.is_set())
      {

         pscroll->m_nPos = m_pscrollbarVertical->m_scrollinfo.nPos;

      }
      else
      {

         pscroll->m_nPos = (i32) get_viewport_offset().y;

      }

      pscroll->m_atom = e_message_vscroll;

      send(pscroll);

   }


   bool vertical_scroll_base::create_vertical_scroll_bar()
   {

      if (m_pscrollbarVertical != nullptr)
      {

         return false;

      }

      auto pbar = __create < scroll_bar > ();

      pbar->m_eorientation = ::e_orientation_vertical;

      pbar->create_child(this);

      ////if (!pbar->create_child(this))
      //{
      //   
      //   return false;

      //}

      m_pscrollbarVertical = pbar;

      return true;

   }


   void vertical_scroll_base::scroll_down_line()
   {

      send_yscroll_message(e_scroll_command_line_down);

   }


   void vertical_scroll_base::scroll_up_line()
   {

      send_yscroll_message(e_scroll_command_line_up);

   }


   void vertical_scroll_base::scroll_up_page()
   {

      send_yscroll_message(e_scroll_command_page_up);

   }


   void vertical_scroll_base::scroll_down_page()
   {

      send_yscroll_message(e_scroll_command_page_down);

   }


   void vertical_scroll_base::scroll_vert(int nPos)
   {

      queue_graphics_call([this, nPos](::draw2d::graphics_pointer & pgraphics)
         {

            set_viewport_offset_y(pgraphics, nPos);

         });

   }


   bool scroll_base::GetActiveClientRect(RECTANGLE_I32 * prectangle)
   {

      ::user::interaction::get_client_rect(prectangle);

      auto sizeTotal = get_total_size();

      auto pointOffset = get_viewport_offset();

      prectangle->right = (::i32) (prectangle->left + minimum(::width(prectangle), sizeTotal.cx - m_scrolldataHorizontal.m_iPage - pointOffset.x));

      prectangle->bottom = (::i32) (prectangle->top + minimum(::height(prectangle), sizeTotal.cy - m_scrolldataVertical.m_iPage - pointOffset.y));

      return true;

   }


   //bool scroll_base::get_client_rect(RECTANGLE_I32 * prectangle)
   //{

   //   ::user::interaction::get_client_rect(prectangle);

   //   prectangle->right -= get_final_y_scroll_bar_width();

   //   prectangle->bottom -= get_final_x_scroll_bar_width();

   //   return true;

   //}


   bool scroll_base::GetFocusRect(RECTANGLE_I32 * prectangle)
   {

      prectangle->left = 0;
      prectangle->top = 0;
      prectangle->right = layout().sketch().size().cx;
      prectangle->bottom = layout().sketch().size().cy;

      return true;

   }


   ::size_f64 scroll_base::get_total_size()
   {

      return m_sizeTotal;

   }


   void scroll_base::set_total_size(const ::size_f64& size)
   {

      m_sizeTotal.cx = size.cx;

      m_sizeTotal.cy = size.cy;

      //return ::success;

   }


   void scroll_base::set_page_size(const ::size_f64& size)
   {

      throw ::interface_only();

   }



   void scroll_base::defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_scrolldataHorizontal.m_bScrollEnable && m_scrolldataHorizontal.m_bScroll
            && m_pscrollbarHorizontal.is_set() && m_pscrollbarHorizontal->is_ok()
            && m_scrolldataVertical.m_bScrollEnable && m_scrolldataVertical.m_bScroll
            && m_pscrollbarVertical.is_set() && m_pscrollbarVertical->is_ok())
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         ::rectangle_i32 rectangle;

         rectangle.top = rectangleClient.bottom;
         rectangle.left = rectangleClient.right;
         rectangle.right = (::i32) (rectangle.left + m_pscrollbarVertical->layout().design().size().cx);
         rectangle.bottom = (::i32) (rectangle.top + m_pscrollbarHorizontal->layout().design().size().cy);

         pgraphics->fill_rectangle(rectangle, argb(127, 127, 127, 127));

      }

   }


}  // namespace aura



