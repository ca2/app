// From scroll.cpp by camilo on 2022-08-27 12:46 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "horizontal_scroll_base.h"
#include "scroll_data.h"
#include "scroll_bar.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"


namespace user
{


   horizontal_scroll_base::horizontal_scroll_base()
   {

      m_pscrolldataHorizontal = __new(scroll_data);

      m_pscrolldataHorizontal->m_bScroll = false;
      m_pscrolldataHorizontal->m_iPage = 0;
      m_pscrolldataHorizontal->m_iLine = 0;
      m_pscrolldataHorizontal->m_bScrollEnable = true;

   }


   horizontal_scroll_base::~horizontal_scroll_base()
   {


   }


   scroll_bar * horizontal_scroll_base::get_horizontal_scroll_bar()
   {

      return m_pscrollbarHorizontal;

   }


   scroll_data * horizontal_scroll_base::get_horizontal_scroll_data()
   {

      return m_pscrolldataHorizontal;

   }


   void horizontal_scroll_base::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      ::user::interaction::client_rectangle(rectangleClient);

      defer_create_horizontal_scroll_bar();

      if (m_pscrollbarHorizontal)
      {

         if (m_pscrolldataHorizontal->m_bScroll)
         {

            get_horizontal_scroll_info(m_pscrollbarHorizontal->m_scrollinfo);

            ::rectangle_i32 rectangleNewPos;

            auto pstyle = get_style(pgraphics);

            int iScrollBarWidth = get_int(pstyle, e_int_scroll_bar_width);

            rectangleNewPos.left = rectangleClient.left;
            rectangleNewPos.top = rectangleClient.bottom - iScrollBarWidth;
            //rectangleNewPos.right = rectangleNewPos.left + rectangleClient.width() - get_final_y_scroll_bar_width();
            rectangleNewPos.right = rectangleNewPos.left + rectangleClient.width() - iScrollBarWidth;
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


   void horizontal_scroll_base::defer_create_horizontal_scroll_bar()
   {

      bool bCreate = false;

      if (m_pscrolldataHorizontal->m_bScrollEnable)
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

      ::pointer<::message::scroll>pscroll(pmessage);

      queue_graphics_call([this, pscroll](::draw2d::graphics_pointer & pgraphics)
         {

            if (pscroll->m_ecommand == e_scroll_command_line_left)
            {

               set_context_offset_x(pgraphics, (::i32)(get_context_offset().x() - m_pscrolldataHorizontal->m_iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_left)
            {

               set_context_offset_x(pgraphics, (::i32)(get_context_offset().x() - m_pscrolldataHorizontal->m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_right)
            {

               set_context_offset_x(pgraphics, (::i32)(get_context_offset().x() + m_pscrolldataHorizontal->m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_line_right)
            {

               set_context_offset_x(pgraphics, (::i32)(get_context_offset().x() + m_pscrolldataHorizontal->m_iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_track)
            {

               set_context_offset_x(pgraphics, pscroll->m_nPos);

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_position)
            {

               set_context_offset_x(pgraphics, pscroll->m_nPos);

            }

         });

   }


   void horizontal_scroll_base::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pscrollbarHorizontal.is_set())
      {

         m_pscrollbarHorizontal->m_scrollinfo.nPos = m_pointScroll.x();

      }

   }


   bool horizontal_scroll_base::validate_context_offset(point_i32 & point)
   {

      if (point.x() < 0)
      {

         point.x() = 0;

      }
      else
      {

         auto sizeTotal = get_total_size();

         auto sizePage = get_page_size();

         if (point.x() > maximum(0, sizeTotal.cx - sizePage.cx))
         {

            point.x() = (::i32)maximum(0, sizeTotal.cx - sizePage.cx);

         }

      }

      return true;

   }


   void horizontal_scroll_base::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_hscroll, pchannel, this, &horizontal_scroll_base::_001OnHScroll);

   }


   void horizontal_scroll_base::on_change_impact_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto sizeTotal = get_total_size();

      auto pstyle = get_style(pgraphics);

      m_pscrolldataHorizontal->m_iWidth = get_int(pstyle, e_int_scroll_bar_width);

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      ::i32 iTotalHeight = (::i32)sizeTotal.cy;

      ::i32 iTotalWidth = (::i32)sizeTotal.cx;

      ::i32 iClientHeight = rectangleClient.height();

      ::i32 iClientWidth = rectangleClient.width();

      //::i32 iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      ::i32 iScrollWidth = iClientWidth - get_int(pstyle, e_int_scroll_bar_width);;

      m_pscrolldataHorizontal->m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         m_pscrolldataHorizontal->m_bScroll = true;

      }
      else if (iTotalHeight > iClientHeight)
      {

         if (iTotalWidth > iScrollWidth)
         {

            m_pscrolldataHorizontal->m_bScroll = true;

         }

      }

      m_pscrolldataHorizontal->m_bScroll = m_pscrolldataHorizontal->m_bScrollEnable && m_pscrolldataHorizontal->m_bScroll;

      ::rectangle_i32 rectangleScroll;

      client_rectangle(rectangleScroll);

      m_pscrolldataHorizontal->m_iPage = rectangleScroll.width();

      if (validate_context_offset(m_pointScroll))
      {

         layout_scroll_bar(pgraphics);

         on_change_context_offset(pgraphics);

      }

   }


   int horizontal_scroll_base::get_final_x_scroll_bar_width()
   {

      //return m_pscrolldataHorizontal->m_bScroll && m_pscrolldataHorizontal->m_bScrollEnable ? m_pscrolldataHorizontal->m_iWidth : 0;

      return m_pscrolldataHorizontal->m_iWidth;

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

         pscroll->m_nPos = (i32)get_context_offset().x();

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

      auto pbar = __create < scroll_bar >();

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

            set_context_offset_x(pgraphics, nPos);

         });

   }



} // namespace user



