// From scroll.cpp by camilo on 2022-08-27 12:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "scroll_bar.h"
#include "scroll_base_x.h"
#include "acme/constant/user_message.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"


namespace user
{


   scroll_base_x::scroll_base_x()
   {

      //m_pscrollstateHorizontal = øallocate scroll_state();

      //m_pscrollstateHorizontal->m_bShowScroll = false;

      m_pscrolllayoutX = øallocate scroll_layout();

      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch].m_bHasScroll = false;
      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch].m_dPage = 0;
      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch].m_dLine = 0;
      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch].m_bScrollEnable = true;

   }


   scroll_base_x::~scroll_base_x()
   {


   }

   
   void scroll_base_x::destroy()
   {

      m_pscrollbarX.defer_destroy();
      m_pscrolllayoutX.defer_destroy();
      ::user::interaction::destroy();

   }



   void scroll_base_x::sketch_to_lading_x()
   {

      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_lading] = m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch];

   }


   void scroll_base_x::lading_to_layout_x(bool & bUpdateBuffer, bool & bUpdateWindow)
   {

      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_layout] = m_pscrolllayoutX->m_scrollstatea[::user::e_layout_lading];

   }


   void scroll_base_x::layout_to_design_x()
   {

      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_design] = m_pscrolllayoutX->m_scrollstatea[::user::e_layout_layout];

   }


   scroll_bar * scroll_base_x::get_scroll_bar_x()
   {

      return m_pscrollbarX;

   }


   scroll_state scroll_base_x::get_scroll_state_x(::user::enum_layout elayout)
   {

      return m_pscrolllayoutX->m_scrollstatea[elayout];

   }


   void scroll_base_x::set_scroll_state_x(const scroll_state & scrollstate, ::user::enum_layout elayout)
   {

      auto iLayout = (int)elayout;

      while(iLayout >= 0)
      {

         m_pscrolllayoutX->m_scrollstatea[iLayout] = scrollstate;

         iLayout--;

      }

   }


   void scroll_base_x::set_scroll_dimension(const ::int_size & size, ::user::enum_layout elayout)
   {

      auto iLayout = (int)elayout;

      while (iLayout >= 0)
      {

         m_pscrolllayoutX->m_scrollstatea[iLayout].set_dimension(size.cx());

         iLayout--;

      }

   }


   void scroll_base_x::layout_scroll_bar_x(::user::enum_layout elayout)
   {

      auto rectangleX = ::user::interaction::rectangle(elayout);

      //::user::interaction::this->rectangle(rectangleX);

      defer_create_scroll_bar_x();

      if (m_pscrollbarX)
      {

         if (scroll_bar_x_visible())
         {

            synthesize_scroll_state_x(m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch], ::user::e_layout_sketch);

            ::int_rectangle rectangleNewPos;

            auto pstyle = get_style();

            int iScrollBarWidth = get_int(pstyle, e_int_scroll_bar_thickness);

            rectangleNewPos.left() = rectangleX.left();
            rectangleNewPos.top() = rectangleX.bottom() - iScrollBarWidth;
            //rectangleNewPos.right() = rectangleNewPos.left() + rectangleX.width() - get_final_y_scroll_bar_width();
            rectangleNewPos.right() = rectangleNewPos.left() + rectangleX.width() - iScrollBarWidth;
            rectangleNewPos.bottom() = rectangleX.bottom();

            m_pscrollbarX->place(rectangleNewPos, elayout);

            if (!m_pscrollbarX->is_this_visible())
            {

               m_pscrollbarX->order(e_zorder_top);

               m_pscrollbarX->display();

               m_pscrollbarX->set_need_redraw();

               m_pscrollbarX->set_need_layout();

            }

         }
         else
         {

            m_pscrollbarX->display(e_display_none);

         }

         m_pscrollbarX->set_need_redraw();

         m_pscrollbarX->post_redraw();

      }

   }


   void scroll_base_x::defer_create_scroll_bar_x(::user::enum_layout elayout)
   {

      bool bCreate = false;

      if (m_pscrolllayoutX->m_scrollstatea[elayout].m_bScrollEnable)
      {

         if (m_pscrollbarX == nullptr)
         {

            bCreate = true;

         }

      }

      if (bCreate)
      {

         create_scroll_bar_x();

      }

   }


   void scroll_base_x::on_message_scroll_x(::message::message * pmessage)
   {

      //::pointer<::message::scroll>pscroll(pmessage);

      //queue_graphics_call([this, pscroll](::draw2d::graphics_pointer & pgraphics)
      //   {

      //      if (pscroll->m_ecommand == e_scroll_command_line_left)
      //      {

      //         set_context_offset_x(pgraphics, (int)(get_context_offset().x() - m_pscrollstateHorizontal->m_iLine));

      //      }
      //      else if (pscroll->m_ecommand == e_scroll_command_page_left)
      //      {

      //         set_context_offset_x(pgraphics, (int)(get_context_offset().x() - m_pscrollstateHorizontal->m_iPage));

      //      }
      //      else if (pscroll->m_ecommand == e_scroll_command_page_right)
      //      {

      //         set_context_offset_x(pgraphics, (int)(get_context_offset().x() + m_pscrollstateHorizontal->m_iPage));

      //      }
      //      else if (pscroll->m_ecommand == e_scroll_command_line_right)
      //      {

      //         set_context_offset_x(pgraphics, (int)(get_context_offset().x() + m_pscrollstateHorizontal->m_iLine));

      //      }
      //      else if (pscroll->m_ecommand == e_scroll_command_thumb_track)
      //      {

      //         set_context_offset_x(pgraphics, pscroll->m_nPos);

      //      }
      //      else if (pscroll->m_ecommand == e_scroll_command_thumb_position)
      //      {

      //         set_context_offset_x(pgraphics, pscroll->m_nPos);

      //      }

      //   });

      set_need_redraw();

      set_need_layout();

   }


   //void scroll_base_x::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   //if (m_pscrollbarX.is_set())
   //   //{

   //   //   m_pscrollbarX->m_scrollstate.nPos = m_pointScroll.x();

   //   //}

   //}


   void scroll_base_x::set_scroll_tracking_x(double x, ::user::enum_layout elayout)
   {

      auto iLayout = (::collection::index)elayout;

      while (iLayout >= 0)
      {

         m_pscrolllayoutX->m_scrollstatea[iLayout].m_dTrackingPosition = x;

         iLayout--;

      }

   }


   double scroll_base_x::get_context_offset_x(::user::enum_layout elayout)
   {

      return m_pscrolllayoutX->m_scrollstatea[elayout].m_dPosition;

   }


   void scroll_base_x::set_context_offset_x(double x, ::user::enum_layout elayout)
   {

      auto iLayout = (::collection::index)elayout;

      while (iLayout >= 0)
      {

         m_pscrolllayoutX->m_scrollstatea[iLayout].m_dPosition = x;

         iLayout--;

      }

   }


   void scroll_base_x::constrain_context_offset_x(double & x, ::user::enum_layout elayout)
   {

      auto scrollstatex = get_scroll_state_x(elayout);

      x = minimum_maximum(x, scrollstatex.m_dMinimum, scrollstatex.m_dMaximum - scrollstatex.m_dPage);

//point.y() = minimum_maximum(point.y(), scrollstatey.m_iMinimum, scrollstatey.m_iMaximum);

      //if (point.x() < 0)
      //{

      //   point.x() = 0;

      //}
      //else
      //{

      //   auto sizeTotal = get_total_size();

      //   auto sizePage = get_page_size();

      //   if (point.x() > maximum(0, sizeTotal.cx() - sizePage.cx()))
      //   {

      //      point.x() = (int)maximum(0, sizeTotal.cx() - sizePage.cx());

      //   }

      //}

      //return true;

   }


   void scroll_base_x::install_message_routing(::channel * pchannel)
   {

      USER_MESSAGE_LINK(::user::e_message_scroll_x, pchannel, this, &scroll_base_x::on_message_scroll_x);

   }


   void scroll_base_x::on_change_scroll_state(::user::enum_layout elayout)
   {

      auto sizeTotal = get_total_size(elayout);

      auto pstyle = get_style();

      auto scrollstatex = get_scroll_state_x(elayout);

      scrollstatex.m_dThickness = (double) get_int(pstyle, e_int_scroll_bar_thickness);

      auto rectangleX = this->rectangle();

      int iTotalHeight = (int)sizeTotal.cy();

      int iTotalWidth = (int)sizeTotal.cx();

      int iClientHeight = rectangleX.height();

      int iClientWidth = rectangleX.width();

      int iScrollWidth = iClientWidth - get_int(pstyle, e_int_scroll_bar_thickness);;

      scrollstatex.m_bHasScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         scrollstatex.m_bHasScroll = true;

      }
      else if (iTotalHeight > iClientHeight)
      {

         if (iTotalWidth > iScrollWidth)
         {

            scrollstatex.m_bHasScroll = true;

         }

      }

      //m_pscrollstateHorizontal->m_bHasScroll = m_pscrollstateHorizontal->m_bScrollEnable && m_pscrollstateHorizontal->m_bScroll;

      auto rectangleScroll = this->rectangle();

      m_pscrolllayoutX->m_scrollstatea[elayout].m_dPage = rectangleScroll.width();

      //if (validate_context_offset(m_pointScroll))
      //{

      //   layout_scroll_bar(pgraphics);

      //   on_change_context_offset(pgraphics);

      //}

   }


   int scroll_base_x::get_final_scroll_bar_x_thickness(enum_layout elayout)
   {

      //return m_pscrollstateHorizontal->m_bScroll && m_pscrollstateHorizontal->m_bScrollEnable ? m_pscrollstateHorizontal->m_iWidth : 0;

      return (int) m_pscrolllayoutX->m_scrollstatea[elayout].m_dThickness;

   }



   void scroll_base_x::send_scroll_x_message(enum_scroll_command ecommand, double dPosition)
   {

      auto pscroll = øallocate ::message::scroll();

      pscroll->m_ecommand = ecommand;

      if (dPosition != DOUBLE_MOST_NEGATIVE)
      {

         pscroll->m_dPosition = dPosition;

      }
      //else
      //{

      //   pscroll->m_nPos = (int)get_context_offset().x();

      //}

      pscroll->m_eusermessage = ::user::e_message_scroll_x;

      send_message(pscroll);

   }


   bool scroll_base_x::create_scroll_bar_x()
   {

      if (m_pscrollbarX)
      {

         return true;

      }

      auto pbar = øcreate < scroll_bar >();

      pbar->m_eorientation = ::e_orientation_horizontal;

      pbar->create_child(this);

      //if (!)
      //{

      //   return false;

      //}

      m_pscrollbarX = pbar;

      m_pscrollbarX->m_pscrolllayout = m_pscrolllayoutX;

      m_pscrollbarX->m_puserinteractionScrollBase = this;

      return true;

   }


   void scroll_base_x::scroll_left_line()
   {

      send_scroll_x_message(e_scroll_command_line_left);

   }


   void scroll_base_x::scroll_right_line()
   {

      send_scroll_x_message(e_scroll_command_line_right);

   }


   void scroll_base_x::scroll_left_page()
   {

      send_scroll_x_message(e_scroll_command_page_left);

   }


   void scroll_base_x::scroll_right_page()
   {

      send_scroll_x_message(e_scroll_command_page_right);

   }


   void scroll_base_x::scroll_x(int nPos)
   {

      send_scroll_x_message(e_scroll_command_thumb_position, nPos);
      //queue_graphics_call([this, nPos](::draw2d::graphics_pointer & pgraphics)
      //   {

      //      set_context_offset_x(pgraphics, nPos);

      //   });

   }



} // namespace user



