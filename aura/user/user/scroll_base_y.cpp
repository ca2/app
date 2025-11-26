// From scroll.cpp by camilo on 2022-08-27 12:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "scroll_bar.h"
#include "scroll_base_y.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


namespace user
{


   scroll_base_y::scroll_base_y()
   {

      //m_iWheelDeltaScroll = 3;

      //m_pscrollstateVertical = øallocate scroll_state();

      m_pscrolllayoutY = øallocate scroll_layout();

      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bHasScroll = false;
      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_dPage = 0.;
      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_dLine = 60.;
      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_dWheel = 120.;
      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bScrollEnable = true;

   }


   scroll_base_y::~scroll_base_y()
   {

   }


   void scroll_base_y::destroy()
   {

      m_pscrollbarY.defer_destroy();
      m_pscrolllayoutY.defer_destroy();
      ::user::interaction::destroy();

   }


   void scroll_base_y::sketch_to_lading_y()
   {

      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_lading] = m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch];

   }


   void scroll_base_y::lading_to_layout_y(bool & bUpdateBuffer, bool & bUpdateWindow)
   {

      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_layout] = m_pscrolllayoutY->m_scrollstatea[::user::e_layout_lading];

   }


   void scroll_base_y::layout_to_design_y()
   {

      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_design] = m_pscrolllayoutY->m_scrollstatea[::user::e_layout_layout];

   }


   scroll_bar * scroll_base_y::get_scroll_bar_y()
   {

      return m_pscrollbarY;

   }


   scroll_state scroll_base_y::get_scroll_state_y(::user::enum_layout elayout)
   {

      return m_pscrolllayoutY->m_scrollstatea[elayout];

   }


   void scroll_base_y::set_scroll_state_y(const scroll_state & scrollstate, ::user::enum_layout elayout)
   {

      auto iLayout = (int)elayout;

      while (iLayout >= 0)
      {

         m_pscrolllayoutY->m_scrollstatea[iLayout] = scrollstate;

         iLayout--;

      }

   }


   void scroll_base_y::set_scroll_dimension(const ::int_size & size, ::user::enum_layout elayout)
   {

      auto iLayout = (int)elayout;

      while (iLayout >= 0)
      {

         m_pscrolllayoutY->m_scrollstatea[iLayout].set_dimension(size.cy);

         iLayout--;

      }

   }


   //void scroll_base_y::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   void scroll_base_y::layout_scroll_bar_y(::user::enum_layout elayout)
   {

      ::int_rectangle rectangleX = raw_rectangle(elayout);

      //scroll_bar_get_client_rect(rectangleX);

//      int ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      defer_create_scroll_bar_y(elayout);

      if (m_pscrollbarY != nullptr)
      {

         if (scroll_bar_y_visible(elayout))
         {

            synthesize_scroll_state_y(m_pscrolllayoutY->m_scrollstatea[elayout], elayout);

            ::int_rectangle rectangleNewPos;

            auto pstyle = get_style();

            int iScrollBarWidth = get_int(pstyle, e_int_scroll_bar_thickness);

            rectangleNewPos.left = rectangleX.right - iScrollBarWidth;
            rectangleNewPos.top = rectangleX.top;
            rectangleNewPos.right = rectangleX.right;
            //rectangleNewPos.bottom = rectangleNewPos.top + rectangleX.height() - get_final_x_scroll_bar_width();
            rectangleNewPos.bottom = rectangleNewPos.top + rectangleX.height() - iScrollBarWidth;

            m_pscrollbarY->place(rectangleNewPos, elayout);

            if (!m_pscrollbarY->is_this_visible())
            {

               m_pscrollbarY->order(e_zorder_top);

               m_pscrollbarY->display();

               m_pscrollbarY->set_need_layout();

            }

         }
         else
         {

            m_pscrollbarY->display(e_display_none);

         }

         set_need_redraw();

         post_redraw();

      }

   }


   //void scroll_base_y::_001OnDeferCreateYScrollBar()
   //{

   //   if (m_pscrollstateVertical->m_bScrollEnable)
   //   {

   //      if (m_pscrollbarY == nullptr)
   //      {

   //         create_y_scroll_bar(nullptr);

   //      }

   //   }

   //}


   void scroll_base_y::defer_create_scroll_bar_y(::user::enum_layout elayout)
   {

      bool bCreate = false;

      if (m_pscrolllayoutY->m_scrollstatea[elayout].m_bScrollEnable)
      {

         if (m_pscrollbarY == nullptr)
         {

            bCreate = true;

         }

      }

      if (bCreate)
      {

         create_scroll_bar_y();

      }

   }


   void scroll_base_y::on_message_scroll_y(::message::message * pmessage)
   {

      ::pointer<::message::scroll>pscroll(pmessage);

      ::user::enum_layout elayout = ::user::e_layout_sketch;

      double Δ = 0.0;

      auto y = get_context_offset_y(elayout);

      if (pscroll->m_ecommand == e_scroll_command_line_up)
      {

         Δ = -m_pscrolllayoutY->m_scrollstatea[elayout].m_dLine;

      }
      else if (pscroll->m_ecommand == e_scroll_command_wheel_up)
      {

         Δ = -m_pscrolllayoutY->m_scrollstatea[elayout].m_dWheel;

      }
      else if (pscroll->m_ecommand == e_scroll_command_page_up)
      {

         Δ = -m_pscrolllayoutY->m_scrollstatea[elayout].m_dPage;

      }
      else if (pscroll->m_ecommand == e_scroll_command_page_down)
      {

         Δ = m_pscrolllayoutY->m_scrollstatea[elayout].m_dPage;

      }
      else if (pscroll->m_ecommand == e_scroll_command_wheel_down)
      {

         Δ = m_pscrolllayoutY->m_scrollstatea[elayout].m_dWheel;

      }
      else if (pscroll->m_ecommand == e_scroll_command_line_down)
      {

         Δ = m_pscrolllayoutY->m_scrollstatea[elayout].m_dLine;

      }
      else if (pscroll->m_ecommand == e_scroll_command_thumb_track)
      {

         Δ = pscroll->m_dPosition - y;

      }
      else if (pscroll->m_ecommand == e_scroll_command_thumb_position)
      {

         Δ = pscroll->m_dPosition - y;

      }
      else if (pscroll->m_ecommand == e_scroll_command_home)
      {

         Δ = -y;

      }
      else if (pscroll->m_ecommand == e_scroll_command_end)
      {

         Δ = m_pscrolllayoutY->m_scrollstatea[elayout].m_dMaximum - y;

      }

      if (fabs(Δ) > 0.001)
      {

         y += Δ;

         constrain_context_offset_y(y, elayout);

         set_context_offset_y(y, elayout);

         on_change_context_offset(elayout);

         set_need_redraw();

         post_redraw();

      }

   }



   int scroll_base_y::get_wheel_scroll_delta()
   {

      return (int)m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_dWheel;

   }


   //void scroll_base_y::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   //{

   //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //   //if (m_pscrollbarY.is_set())
   //   //{

   //   //   m_pscrollbarY->m_scrollinfo.nPos = m_pointScroll.y;

   //   //}

   //}


   void scroll_base_y::on_message_mouse_wheel(::message::message * pmessage)
   {

      if (!m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].scroll_visible())
      {

         return;

      }

      ::pointer<::message::mouse_wheel>pmousewheel(pmessage);

      auto Δ = pmousewheel->m_Δ;
      
      informationf("on_message_mouse_wheel Δ=%d", Δ);

      if (Δ > 0)
      {

         for (; Δ > 0; Δ -= 120)
         {

            m_pscrollbarY->post_scroll_message(e_scroll_command_wheel_up);

         }

      }
      else
      {

         for (; Δ < 0; Δ += 120)
         {

            m_pscrollbarY->post_scroll_message(e_scroll_command_wheel_down);

         }

      }

      pmousewheel->m_lresult = 0;

      pmousewheel->m_bRet = true;

   }


   void scroll_base_y::on_message_key_down(::message::message * pmessage)
   {

      if (!m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].scroll_visible())
      {

         return;

      }

      ::pointer<::message::key>pkey(pmessage);

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
      //      m_iWheelDelta -= (short)(WHEEL_DELTA * iDelta);
      //
      //      index nPos = m_pscrollbarY->m_scrollinfo.nPos - iDelta * get_wheel_scroll_delta();
      //
      //      if (nPos < m_pscrollbarY->m_scrollinfo.nMin)
      //         nPos = m_pscrollbarY->m_scrollinfo.nMin;
      //      else if (nPos > m_pscrollbarY->m_scrollinfo.nMax - m_pscrollbarY->m_scrollinfo.nPage)
      //         nPos = m_pscrollbarY->m_scrollinfo.nMax - m_pscrollbarY->m_scrollinfo.nPage;
      //
      //      m_pscrollbarY->m_scrollinfo.nPos =  (int) nPos;


      auto ekey = pkey->m_ekey;

      if (ekey == ::user::e_key_page_up)
      {

         m_pscrollbarY->post_scroll_message(e_scroll_command_page_up);

         pkey->m_lresult = 0;

         pkey->m_bRet = true;

      }
      else if (ekey == ::user::e_key_page_down)
      {

         m_pscrollbarY->post_scroll_message(e_scroll_command_page_down);

         pkey->m_lresult = 0;

         pkey->m_bRet = true;

      }

   }


   //bool scroll_base_y::validate_context_offset(int_point & point)
   //{

   //   if (point.y < 0)
   //   {

   //      point.y = 0;

   //   }
   //   else
   //   {

   //      auto sizeTotal = get_total_size();

   //      auto sizePage = get_page_size();

   //      if (point.y > maximum(0, sizeTotal.cy - sizePage.cy))
   //      {

   //         point.y = (int)maximum(0, sizeTotal.cy - sizePage.cy);

   //      }

   //   }

   //   return true;

   //}


   void scroll_base_y::set_scroll_tracking_y(double y, ::user::enum_layout elayout)
   {

      auto iLayout = (::collection::index)elayout;

      while (iLayout >= 0)
      {

         m_pscrolllayoutY->m_scrollstatea[iLayout].m_dTrackingPosition = y;

         iLayout--;

      }

   }


   double scroll_base_y::get_context_offset_y(::user::enum_layout elayout)
   {

      return m_pscrolllayoutY->m_scrollstatea[elayout].m_dPosition;

   }


   void scroll_base_y::set_context_offset_y(double y, ::user::enum_layout elayout)
   {

      auto iLayout = (::collection::index)elayout;

      while (iLayout >= 0)
      {

         m_pscrolllayoutY->m_scrollstatea[iLayout].m_dPosition = y;

         iLayout--;

      }

   }


   void scroll_base_y::constrain_context_offset_y(double & y, ::user::enum_layout elayout)
   {

      auto scrollstatey = get_scroll_state_y(elayout);

      y = minimum_maximum(y, scrollstatey.m_dMinimum, scrollstatey.m_dMaximum - scrollstatey.m_dPage);

      //point.y = minimum_maximum(point.y, scrollstatey.m_iMinimum, scrollstatey.m_iMaximum);

            //if (point.x < 0)
            //{

            //   point.x = 0;

            //}
            //else
            //{

            //   auto sizeTotal = get_total_size();

            //   auto sizePage = get_page_size();

            //   if (point.x > maximum(0, sizeTotal.cx - sizePage.cx))
            //   {

            //      point.x = (int)maximum(0, sizeTotal.cx - sizePage.cx);

            //   }

            //}

            //return true;

   }


   void scroll_base_y::install_message_routing(::channel * pchannel)
   {

      USER_MESSAGE_LINK(::user::e_message_scroll_y, pchannel, this, &scroll_base_y::on_message_scroll_y);
      USER_MESSAGE_LINK(::user::e_message_mouse_wheel, pchannel, this, &scroll_base_y::on_message_mouse_wheel);
      USER_MESSAGE_LINK(::user::e_message_key_down, pchannel, this, &scroll_base_y::on_message_key_down);

   }


   void scroll_base_y::on_change_scroll_state(::user::enum_layout elayout)
   {

      auto sizeTotal = get_total_size(elayout);

      auto pstyle = get_style();

      auto scrollstatey = get_scroll_state_y(elayout);

      scrollstatey.m_dThickness = (double)get_int(pstyle, e_int_scroll_bar_thickness);

      auto rectangleX = this->rectangle();

      int iTotalHeight = (int)sizeTotal.cy;

      int iTotalWidth = (int)sizeTotal.cx;

      int iClientHeight = rectangleX.height();

      int iClientWidth = rectangleX.width();

      int iScrollHeight = iClientHeight - get_int(pstyle, e_int_scroll_bar_thickness);

      //int iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bHasScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         if (iTotalHeight > iScrollHeight)
         {

            m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bHasScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bHasScroll = true;

      }

      //m_pscrollstateVertical->m_bScroll = m_pscrollstateVertical->m_bScrollEnable && m_pscrollstateVertical->m_bScroll;

      auto rectangleScroll = this->rectangle();

      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_dPage = rectangleScroll.height();

      //if (validate_context_offset(m_pointScroll))
      //{

      //   layout_scroll_bar(pgraphics);

      //   on_change_context_offset(pgraphics);

      //}

      set_scroll_state_y(scrollstatey, elayout);

   }


   int scroll_base_y::get_final_scroll_bar_y_thickness(::user::enum_layout elayout)
   {

      //return m_pscrollstateVertical->m_bScroll && m_pscrollstateVertical->m_bScrollEnable ? m_pscrollstateVertical->m_iWidth : 0;

      return (int)m_pscrolllayoutY->m_scrollstatea[elayout].m_dThickness;

   }



   void scroll_base_y::send_scroll_y_message(enum_scroll_command ecommand, double dPosition)
   {

      auto pscroll = øallocate ::message::scroll();

      pscroll->m_ecommand = ecommand;

      if (dPosition != DOUBLE_MOST_NEGATIVE)
      {

         pscroll->m_dPosition = dPosition;

      }
      //else
      //{

      //   pscroll->m_nPos = (int)get_context_offset().y;

      //}

      pscroll->m_eusermessage = ::user::e_message_scroll_y;

      send_message(pscroll);

   }


   bool scroll_base_y::create_scroll_bar_y()
   {

      if (m_pscrollbarY != nullptr)
      {

         return false;

      }

      auto pbar = øcreate < scroll_bar >();

      pbar->m_eorientation = ::e_orientation_vertical;

      pbar->create_child(this);

      ////if (!pbar->create_child(this))
      //{
      //   
      //   return false;

      //}

      m_pscrollbarY = pbar;

      m_pscrollbarY->m_pscrolllayout = m_pscrolllayoutY;

      m_pscrollbarY->m_puserinteractionScrollBase = this;

      return true;

   }


   void scroll_base_y::scroll_down_line()
   {

      send_scroll_y_message(e_scroll_command_line_down);

   }


   void scroll_base_y::scroll_up_line()
   {

      send_scroll_y_message(e_scroll_command_line_up);

   }


   void scroll_base_y::scroll_up_page()
   {

      send_scroll_y_message(e_scroll_command_page_up);

   }


   void scroll_base_y::scroll_down_page()
   {

      send_scroll_y_message(e_scroll_command_page_down);

   }


   void scroll_base_y::scroll_y(int iPosition)
   {

      send_scroll_y_message(e_scroll_command_thumb_position, iPosition);

      /*    queue_graphics_call([this, nPos](::draw2d::graphics_pointer & pgraphics)
             {

                set_context_offset_y(pgraphics, nPos);

             });*/

   }


} // namespace user



