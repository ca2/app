// From scroll.cpp by camilo on 2022-08-27 12:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "aura/operating_system.h"
#if !BROAD_PRECOMPILED_HEADER
////#include "aura/user/user/_component.h"
#endif
//#include "acme/operating_system/_user.h"
#include "aura/graphics/draw2d/graphics.h"
#include "scroll_data.h"
#include "vertical_scroll_base.h"
#include "scroll_bar.h"
#include "aura/message/user.h"


namespace user
{


   vertical_scroll_base::vertical_scroll_base()
   {

      m_iWheelDeltaScroll = 3;

      m_pscrolldataVertical = __new(scroll_data);

      m_pscrolldataVertical->m_bScroll = false;
      m_pscrolldataVertical->m_iPage = 0;
      m_pscrolldataVertical->m_iLine = 0;
      m_pscrolldataVertical->m_bScrollEnable = true;

   }


   vertical_scroll_base::~vertical_scroll_base()
   {

   }


   scroll_bar * vertical_scroll_base::get_vertical_scroll_bar()
   {

      return m_pscrollbarVertical;

   }


   scroll_data * vertical_scroll_base::get_vertical_scroll_data()
   {

      return m_pscrolldataVertical;

   }


   void vertical_scroll_base::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient = get_client_rect();

      //scroll_bar_get_client_rect(rectangleClient);

//      i32 ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      defer_create_vertical_scroll_bar();

      if (m_pscrollbarVertical != nullptr)
      {

         if (m_pscrolldataVertical->m_bScroll)
         {

            get_vertical_scroll_info(m_pscrollbarVertical->m_scrollinfo);

            ::rectangle_i32 rectangleNewPos;

            auto pstyle = get_style(pgraphics);

            int iScrollBarWidth = get_int(pstyle, e_int_scroll_bar_width);

            rectangleNewPos.left = rectangleClient.right - iScrollBarWidth;
            rectangleNewPos.top = rectangleClient.top;
            rectangleNewPos.right = rectangleClient.right;
            rectangleNewPos.bottom = rectangleNewPos.top + rectangleClient.height() - get_final_x_scroll_bar_width();

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

   //   if (m_pscrolldataVertical->m_bScrollEnable)
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

      if (m_pscrolldataVertical->m_bScrollEnable)
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


   void vertical_scroll_base::on_message_vertical_scroll(::message::message * pmessage)
   {

      __pointer(::message::scroll) pscroll(pmessage);

      queue_graphics_call([this, pscroll](::draw2d::graphics_pointer & pgraphics)
         {

            if (pscroll->m_ecommand == e_scroll_command_line_up)
            {

               set_context_offset_y(pgraphics, (::i32)(get_context_offset().y - m_pscrolldataVertical->m_iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_up)
            {

               set_context_offset_y(pgraphics, (::i32)(get_context_offset().y - m_pscrolldataVertical->m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_page_down)
            {

               set_context_offset_y(pgraphics, (::i32)(get_context_offset().y + m_pscrolldataVertical->m_iPage));

            }
            else if (pscroll->m_ecommand == e_scroll_command_line_down)
            {

               auto iLine = m_pscrolldataVertical->m_iLine;

               set_context_offset_y(pgraphics, (::i32)(get_context_offset().y + iLine));

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_track)
            {

               set_context_offset_y(pgraphics, pscroll->m_nPos);

            }
            else if (pscroll->m_ecommand == e_scroll_command_thumb_position)
            {

               set_context_offset_y(pgraphics, pscroll->m_nPos);

            }

         });

      set_need_redraw();

      post_redraw();

   }



   i32 vertical_scroll_base::get_wheel_scroll_delta()
   {

      return m_iWheelDeltaScroll;

   }


   void vertical_scroll_base::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pscrollbarVertical.is_set())
      {

         m_pscrollbarVertical->m_scrollinfo.nPos = m_pointScroll.y;

      }

   }


   void vertical_scroll_base::on_message_mouse_wheel(::message::message * pmessage)
   {

      if (!m_pscrolldataVertical->m_bScroll || !m_pscrolldataVertical->m_bScrollEnable)
      {

         return;

      }

      __pointer(::message::mouse_wheel) pmousewheel(pmessage);

      int iDelta = pmousewheel->GetDelta();

      if (iDelta > 0)
      {

         for (; iDelta > 0; iDelta -= 120)
         {

            m_pscrollbarVertical->post_scroll_message(e_scroll_command_line_up);

         }

      }
      else
      {

         for (; iDelta < 0; iDelta += 120)
         {

            m_pscrollbarVertical->post_scroll_message(e_scroll_command_line_down);

         }

      }

      pmousewheel->m_lresult = 0;

      pmousewheel->m_bRet = true;

   }


   void vertical_scroll_base::on_message_key_down(::message::message * pmessage)
   {

      if (!m_pscrolldataVertical->m_bScroll || !m_pscrolldataVertical->m_bScrollEnable)
      {

         return;

      }

      __pointer(::message::key) pkey(pmessage);

      //      if (pmousewheel->GetDelta() > 0)
      //      {
      //
      //         if (m_iWheelDelta > 0)
      //         {
      //
      //            m_iWheelDelta += pmousewheel->GetDelta();
      //
      //         }
      //         else
      //         {
      //
      //            m_iWheelDelta = pmousewheel->GetDelta();
      //
      //         }
      //
      //      }
      //      else if (pmousewheel->GetDelta() < 0)
      //      {
      //
      //         if (m_iWheelDelta < 0)
      //         {
      //
      //            m_iWheelDelta += pmousewheel->GetDelta();
      //
      //         }
      //         else
      //         {
      //
      //            m_iWheelDelta = pmousewheel->GetDelta();
      //
      //         }
      //
      //      }

      //      index iDelta = m_iWheelDelta / WHEEL_DELTA;
      //
      //      m_iWheelDelta -= (i16)(WHEEL_DELTA * iDelta);
      //
      //      index nPos = m_pscrollbarVertical->m_scrollinfo.nPos - iDelta * get_wheel_scroll_delta();
      //
      //      if (nPos < m_pscrollbarVertical->m_scrollinfo.nMin)
      //         nPos = m_pscrollbarVertical->m_scrollinfo.nMin;
      //      else if (nPos > m_pscrollbarVertical->m_scrollinfo.nMax - m_pscrollbarVertical->m_scrollinfo.nPage)
      //         nPos = m_pscrollbarVertical->m_scrollinfo.nMax - m_pscrollbarVertical->m_scrollinfo.nPage;
      //
      //      m_pscrollbarVertical->m_scrollinfo.nPos =  (i32) nPos;


      auto ekey = pkey->m_ekey;

      if (ekey == ::user::e_key_prior)
      {

         m_pscrollbarVertical->post_scroll_message(e_scroll_command_page_up);

         pkey->m_lresult = 0;

         pkey->m_bRet = true;

      }
      else if (ekey == ::user::e_key_next)
      {

         m_pscrollbarVertical->post_scroll_message(e_scroll_command_page_down);

         pkey->m_lresult = 0;

         pkey->m_bRet = true;

      }

   }


   bool vertical_scroll_base::validate_context_offset(point_i32 & point)
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

            point.y = (::i32)maximum(0, sizeTotal.cy - sizePage.cy);

         }

      }

      return true;

   }




   void vertical_scroll_base::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_vscroll, pchannel, this, &vertical_scroll_base::on_message_vertical_scroll);
      MESSAGE_LINK(e_message_mouse_wheel, pchannel, this, &vertical_scroll_base::on_message_mouse_wheel);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &vertical_scroll_base::on_message_key_down);

   }


   void vertical_scroll_base::on_change_impact_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto sizeTotal = get_total_size();

      auto pstyle = get_style(pgraphics);

      m_pscrolldataVertical->m_iWidth = get_int(pstyle, e_int_scroll_bar_width);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::i32 iTotalHeight = (::i32)sizeTotal.cy;

      ::i32 iTotalWidth = (::i32)sizeTotal.cx;

      ::i32 iClientHeight = rectangleClient.height();

      ::i32 iClientWidth = rectangleClient.width();

      ::i32 iScrollHeight = iClientHeight - get_int(pstyle, e_int_scroll_bar_width);

      //::i32 iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_pscrolldataVertical->m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         if (iTotalHeight > iScrollHeight)
         {

            m_pscrolldataVertical->m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_pscrolldataVertical->m_bScroll = true;

      }

      m_pscrolldataVertical->m_bScroll = m_pscrolldataVertical->m_bScrollEnable && m_pscrolldataVertical->m_bScroll;

      ::rectangle_i32 rectangleScroll;

      get_client_rect(rectangleScroll);

      m_pscrolldataVertical->m_iPage = rectangleScroll.height();

      if (validate_context_offset(m_pointScroll))
      {

         layout_scroll_bar(pgraphics);

         on_change_context_offset(pgraphics);

      }

   }


   int vertical_scroll_base::get_final_y_scroll_bar_width()
   {

      return m_pscrolldataVertical->m_bScroll && m_pscrolldataVertical->m_bScrollEnable ? m_pscrolldataVertical->m_iWidth : 0;

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

         pscroll->m_nPos = (i32)get_context_offset().y;

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

      auto pbar = __create < scroll_bar >();

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

            set_context_offset_y(pgraphics, nPos);

         });

   }


} // namespace user



