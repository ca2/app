#include "framework.h"
#include "scroll.h"
#include "scroll_bar.h"
#include "acme/constant/user_message.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/tool.h"
#include "acme/user/user/mouse.h"
#include "aura/graphics/draw2d/graphics.h"
#include "acme/prototype/geometry2d/_text_stream.h"


namespace user
{


   scroll_base::scroll_base()
   {

      m_bUsesDraggingScrolling = false;

   }


   scroll_base::~scroll_base()
   {

   }


   void scroll_base::destroy()
   {


      ::user::scroll_base_x::destroy();
      ::user::scroll_base_y::destroy();

   }


   void scroll_base::on_initialize_particle()
   {

      ::user::interaction::on_initialize_particle();

      if (m_bUsesDraggingScrolling)
      {

         m_bDefaultMouseHoverHandling = true;

         m_bDefaultClickHandling = true;

      }

   }


   void scroll_base::install_message_routing(::channel * pchannel)
   {

      scroll_base_x::install_message_routing(pchannel);
      scroll_base_y::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &scroll_base::on_message_create);

   }


   void scroll_base::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      if (m_bUsesDraggingScrolling)
      {

         auto pitemDragScroll = tool().defer_item(e_element_drag_scroll);

         auto puseritem = user_item(pitemDragScroll);

         puseritem->m_ezorder = e_zorder_front;

         enable_drag(pitemDragScroll, e_zorder_front);

      }

   }


   bool scroll_base::on_drag_start(::int_point & pointDrag, ::user::mouse * pmouse, ::item * pitem)
   {

      if (pitem->m_item.m_eelement == ::e_element_drag_scroll)
      {

         pointDrag = get_context_offset();

         return true;

      }

      return ::user::interaction::on_drag_start(pointDrag, pmouse, pitem);

   }


   //::int_point scroll_base::drag_mouse_cursor_position(::item * pitem, const ::int_point & point)
   //{

   //   auto p = windowing()->try_absolute_mouse_position(this, point);

   //   return p;

   //}


   void scroll_base::set_context_offset(const ::double_point & pointOffset, ::user::enum_layout elayout)
   {

      set_context_offset_x(pointOffset.x(), elayout);

      set_context_offset_y(pointOffset.y(), elayout);

   }

   
   ::int_point scroll_base::drag_point(::item * pitem, ::user::mouse * pmouse)
   {

      if (pitem->m_item.m_eelement == ::e_element_drag_scroll)
      {

         auto pdrag = drag(pitem);

         //auto pointLButtonDown2 = drag_mouse_cursor_position(pitem, pdrag->m_pointLButtonDown2);

         auto Δ = pdrag->m_pointLButtonDown2 ;

         auto pointCursor = drag_mouse_cursor_position(pitem, pmouse->m_pointAbsolute);

         auto pointDrag = pointCursor - Δ;

         information() << "drag_client::drag_point";
         information() << "pointLButtonDown2 : " << pdrag->m_pointLButtonDown2;
         information() << "pointInitial : " << pdrag->m_pointInitial;
         information() << "pointAbsolute : " << pmouse->m_pointAbsolute;
         information() << "pointCursor : " << pointCursor;
         information() << "pointDrag : " << pointDrag;

         return pointDrag;

      }

      return ::user::interaction::drag_point(pitem, pmouse);

   }


   bool scroll_base::drag_shift(::item * pitem, ::user::mouse * pmouse)
   {

      if (pitem->m_item.m_eelement == ::e_element_drag_scroll)
      {

         auto pdrag = drag(pitem);

         pdrag->m_ecursor = e_cursor_move;

         auto point = drag_point(pitem, pmouse);

         set_context_offset(pdrag->m_pointInitial -point);

         on_change_context_offset();

         set_need_redraw();

         post_redraw();

         return true;

      }

      return ::user::interaction::drag_shift(pitem, pmouse);

   }


   void scroll_base::sketch_to_lading()
   {

      ::user::interaction::sketch_to_lading();

      scroll_base_x::sketch_to_lading_x();

      scroll_base_y::sketch_to_lading_y();

      //m_sizeaTotal[::user::e_layout_lading] = m_sizeaTotal[::user::e_layout_sketch];

   }


   void scroll_base::defer_setup_default_client_area_user_item()
   {

      //{

      //   _synchronous_lock synchronouslock(this->synchronization());

      //   auto pitemDragSrcoll = tool().item(e_element_drag_scroll);

      //   if (pitemDragSrcoll)
      //   {

      //      auto pdragScroll = drag(pitemDragSrcoll);

      //      if (pdragScroll)
      //      {

      //         auto rectangleX = this->raw_rectangle();

      //         auto puseritem = user_item(pitemDragSrcoll);

      //         puseritem->m_rectangle2 = rectangleX;

      //      }

      //   }

      //}

      ::user::interaction::defer_setup_default_client_area_user_item();

   }


   void scroll_base::lading_to_layout(bool & bUpdateBuffer, bool & bUpdateWindow)
   {

      ::user::interaction::lading_to_layout(bUpdateBuffer, bUpdateWindow);

      scroll_base_x::lading_to_layout_x(bUpdateBuffer, bUpdateWindow);

      scroll_base_y::lading_to_layout_y(bUpdateBuffer, bUpdateWindow);

      //m_sizeaTotal[::user::e_layout_layout] = m_sizeaTotal[::user::e_layout_lading];

   }


   void scroll_base::layout_to_design()
   {

      ::user::interaction::layout_to_design();

      scroll_base_x::layout_to_design_x();

      scroll_base_y::layout_to_design_y();

      //m_sizeaTotal[::user::e_layout_design] = m_sizeaTotal[::user::e_layout_layout];

   }




   //void scroll_base::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   //{

   //   scroll_base_x::on_change_context_offset(pgraphics);

   //   scroll_base_y::on_change_context_offset(pgraphics);

   //   ::user::interaction::on_change_context_offset(pgraphics);

   //}


   ::double_point scroll_base::get_context_offset(::user::enum_layout elayout)
   {

      auto x = get_context_offset_x(elayout);

      auto y = get_context_offset_y(elayout);

      return { x, y };

   }


   void scroll_base::constrain_context_offset(double_point & point, ::user::enum_layout elayout)
   {

      constrain_context_offset_x(point.x(), elayout);

      constrain_context_offset_y(point.y(), elayout);

      //auto scrollstatey = get_scroll_state_y(elayout);

      //point.x() = minimum_maximum(point.x(), scrollstatex.m_iMinimum, scrollstatex.m_iMaximum);

      //point.y() = minimum_maximum(point.y(), scrollstatey.m_iMinimum, scrollstatey.m_iMaximum);

   //   bool yValidated = scroll_base_y::validate_context_offset(point);

   //   bool iValidated = ::user::interaction::validate_context_offset(point);

   //   return (xValidated || yValidated) && iValidated;

   }


   //void scroll_base::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   void scroll_base::layout_scroll_bar(::user::enum_layout elayout)
   {

      layout_scroll_bar_x(elayout);

      layout_scroll_bar_y(elayout);

   }


   void scroll_base::on_change_scroll_state(::user::enum_layout elayout)
   {

      auto sizeTotal = get_total_size(elayout);

      auto rectangleX = this->rectangle(elayout);

      auto pstyle = get_style();

      auto scrollstatex = get_scroll_state_x(elayout);

      auto scrollstatey = get_scroll_state_y(elayout);

      scrollstatex.m_bHasScroll = false;

      scrollstatey.m_bHasScroll = false;

      scrollstatex.m_dThickness = (double)get_int(pstyle, e_int_scroll_bar_thickness);

      scrollstatey.m_dThickness = (double)get_int(pstyle, e_int_scroll_bar_thickness);

      if (rectangleX.area() <= 0)
      {

         return;

      }

      int iTotalCX = (int)sizeTotal.cx();

      int iTotalCY = (int)sizeTotal.cy();

      int iClientCX = rectangleX.width();

      int iClientCY = rectangleX.height();

      int iScrollCX = iClientCX - get_int(pstyle, e_int_scroll_bar_thickness);

      int iScrollCY = iClientCY - get_int(pstyle, e_int_scroll_bar_thickness);

      if (iTotalCX > iClientCX)
      {

         scrollstatex.m_bHasScroll = true;

         if (iTotalCY > iScrollCY)
         {

            scrollstatey.m_bHasScroll = true;

         }

      }
      else if (iTotalCY > iClientCY)
      {

         scrollstatey.m_bHasScroll = true;

         if (iTotalCX > iScrollCX)
         {

            scrollstatex.m_bHasScroll = true;

         }

      }

      //m_pscrollstateHorizontal->m_bShowScroll = m_pscrollstateHorizontal->m_bScrollEnable && m_pscrollstateHorizontal->m_bHasScroll;

      //m_pscrollstateVertical->m_bShowScroll = m_pscrollstateVertical->m_bScrollEnable && m_pscrollstateVertical->m_bHasScroll;

      //if (!m_pscrollstateHorizontal->m_bScroll)
      //{

      //   m_pointScroll.x() = 0;

      //}


      //if (!m_pscrollstateVertical->m_bScroll)
      //{

      //   m_pointScroll.y() = 0;

      //}


      auto rectangleScroll = this->rectangle();

      scrollstatex.m_dPage = rectangleScroll.width();

      scrollstatey.m_dPage = rectangleScroll.height();

      //if (validate_context_offset(m_pointScroll))
      //{

      //   layout_scroll_bar(pgraphics);

      //   on_change_context_offset(pgraphics);

      //}
      //else
      //{

      //   layout_scroll_bar(pgraphics);

      //}

      set_scroll_state_x(scrollstatex, elayout);

      set_scroll_state_y(scrollstatey, elayout);

      layout_scroll_bar(elayout);

   }


   ::int_rectangle scroll_base::client2_rectangle(enum_layout elayout)
   {

      auto rectangle = this->rectangle(elayout);

      //auto sizeTotal = get_total_size(elayout);

      //auto pointOffset = get_context_offset(elayout);
      rectangle.right() -= get_final_scroll_bar_x_thickness(elayout);

      rectangle.bottom() -= get_final_scroll_bar_y_thickness(elayout);

      //rectangle.right() -= (int)(rectangle.left() + minimum(::width(rectangle), sizeTotal.cx() - m_pscrolllayoutX->m_scrollstatea[elayout].m_dPage - pointOffset.x()));

      //rectangle.bottom() -= (int)(rectangle.top() + minimum(::height(rectangle), sizeTotal.cy() - m_pscrolllayoutY->m_scrollstatea[elayout].m_dPage - pointOffset.y()));

      return rectangle;

   }


   //bool scroll_base::this->rectangle(::int_rectangle * prectangle)
   //{

   //   ::user::interaction::this->rectangle(prectangle);

   //   prectangle->right() -= get_final_y_scroll_bar_width();

   //   prectangle->bottom() -= get_final_x_scroll_bar_width();

   //   return true;

   //}


   bool scroll_base::GetFocusRect(::int_rectangle & rectangle)
   {

      rectangle.left() = 0;
      rectangle.top() = 0;
      rectangle.right() = const_layout().sketch().size().cx();
      rectangle.bottom() = const_layout().sketch().size().cy();

      rectangle += get_accumulated_scroll();

      return true;

   }


   ::double_size scroll_base::get_total_size(::user::enum_layout elayout)
   {

      auto scrollstatex = get_scroll_state_x(elayout);

      auto scrollstatey = get_scroll_state_y(elayout);

      return ::double_size(scrollstatex.dimension(), scrollstatey.dimension());

   }


   void scroll_base::set_total_size(const ::double_size & size, ::user::enum_layout elayout)
   {

      set_scroll_dimension(size, elayout);

      on_change_scroll_state(elayout);

   }


   void scroll_base::set_scroll_dimension(const ::int_size & size, ::user::enum_layout elayout)
   {

      scroll_base_x::set_scroll_dimension(size, elayout);

      scroll_base_y::set_scroll_dimension(size, elayout);

      on_change_scroll_state(elayout);

   }


   void scroll_base::set_page_size(const ::double_size & size, ::user::enum_layout elayout)
   {

      on_change_scroll_state(elayout);

   }


   void scroll_base::defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pscrolllayoutX->m_scrollstatea[::user::e_layout_design].m_bScrollEnable
         && m_pscrolllayoutX->m_scrollstatea[::user::e_layout_design].m_bHasScroll
            && m_pscrollbarX.is_set() && m_pscrollbarX->is_ok()
            && m_pscrolllayoutY->m_scrollstatea[::user::e_layout_design].m_bScrollEnable
         && m_pscrolllayoutY->m_scrollstatea[::user::e_layout_design].m_bHasScroll
            && m_pscrollbarY.is_set() && m_pscrollbarY->is_ok())
      {

         auto rectangleX = this->rectangle();

         ::int_rectangle rectangle;

         rectangle.top() = rectangleX.bottom();
         rectangle.left() = rectangleX.right();
         rectangle.right() = (int)(rectangle.left() + m_pscrollbarY->const_layout().design().size().cx());
         rectangle.bottom() = (int)(rectangle.top() + m_pscrollbarX->const_layout().design().size().cy());

         pgraphics->fill_rectangle(rectangle, argb(127, 127, 127, 127));

      }

   }


   bool scroll_base::scroll_bar_x_visible(enum_layout elayout)
   {

      return m_pscrolllayoutX->m_scrollstatea[elayout].scroll_visible();

   }


   bool scroll_base::scroll_bar_y_visible(enum_layout elayout)
   {

      return m_pscrolllayoutY->m_scrollstatea[elayout].scroll_visible();

   }


   bool scroll_base::get_element_rectangle(::int_rectangle & rectangle, enum_element eelement)
   {
      
      if (eelement == e_element_drag_scroll)
      {

         auto sizeTotal = get_total_size();

         auto sizeWindow = raw_rectangle().size();

         //if (sizeTotal.cx() < sizeWindow.cx())
         {

            rectangle.left() = 0;

         }
         //else
         //{

         //   rectangle.left() = get_context_offset_x();

         //}

         //if (sizeTotal.cy() < sizeWindow.cy())
         {

            rectangle.top() = 0;

         }
         //else
         //{

         //   rectangle.top() = get_context_offset_y(::user::e_layout_design);

         //}

         //auto size = sizeTotal.maximum(sizeWindow);
         
         rectangle.set_size(sizeTotal);

         return true;

      }
      else if(eelement == e_element_client_hit_test)
      {

         //if (!m_bEmptyAreaIsClientArea)
         //{

         //   return false;

         //}

         rectangle = this->rectangle();

         if (scroll_bar_x_visible())
         {

            rectangle.bottom() -= (int)m_pscrollbarX->scroll_bar_thickness();

         }

         if (scroll_bar_y_visible())
         {

            rectangle.right() -= (int)m_pscrollbarY->scroll_bar_thickness();

         }

         return true;

      }

      return ::user::interaction::get_element_rectangle(rectangle, eelement);

   }


}  // namespace aura



