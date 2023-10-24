#include "framework.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/draw2d/graphics.h"
//#include "scroll_state.h"
#include "scroll.h"
#include "scroll_bar.h"


namespace user
{


   scroll_base::scroll_base()
   {

   }


   scroll_base::~scroll_base()
   {

   }


   void scroll_base::sketch_to_lading()
   {

      ::user::interaction::sketch_to_lading();

      scroll_base_x::sketch_to_lading_x();

      scroll_base_y::sketch_to_lading_y();

      //m_sizeaTotal[::user::e_layout_lading] = m_sizeaTotal[::user::e_layout_sketch];

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


   void scroll_base::install_message_routing(::channel * pchannel)
   {

      scroll_base_x::install_message_routing(pchannel);
      scroll_base_y::install_message_routing(pchannel);

   }


   //void scroll_base::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   //{

   //   scroll_base_x::on_change_context_offset(pgraphics);

   //   scroll_base_y::on_change_context_offset(pgraphics);

   //   ::user::interaction::on_change_context_offset(pgraphics);

   //}


   ::point_f64 scroll_base::get_context_offset(::user::enum_layout elayout)
   {

      auto x = get_context_offset_x(elayout);

      auto y = get_context_offset_y(elayout);

      return { x, y };

   }


   void scroll_base::constrain_context_offset(point_f64 & point, ::user::enum_layout elayout)
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

      scrollstatex.m_dThickness = (::f64) get_int(pstyle, e_int_scroll_bar_thickness);

      scrollstatey.m_dThickness = (::f64) get_int(pstyle, e_int_scroll_bar_thickness);

      if (rectangleX.area() <= 0)
      {

         return;

      }

      ::i32 iTotalCX = (::i32)sizeTotal.cx();

      ::i32 iTotalCY = (::i32)sizeTotal.cy();

      ::i32 iClientCX = rectangleX.width();

      ::i32 iClientCY = rectangleX.height();

      ::i32 iScrollCX = iClientCX - get_int(pstyle, e_int_scroll_bar_thickness);

      ::i32 iScrollCY = iClientCY - get_int(pstyle, e_int_scroll_bar_thickness);

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


   ::rectangle_i32 scroll_base::client2_rectangle(enum_layout elayout)
   {

      auto rectangle = this->rectangle(elayout);

      auto sizeTotal = get_total_size(elayout);

      auto pointOffset = get_context_offset(elayout);

      rectangle.right() = (::i32)(rectangle.left() + minimum(::width(rectangle), sizeTotal.cx() - m_pscrolllayoutX->m_scrollstatea[elayout].m_dPage - pointOffset.x()));

      rectangle.bottom() = (::i32)(rectangle.top() + minimum(::height(rectangle), sizeTotal.cy() - m_pscrolllayoutY->m_scrollstatea[elayout].m_dPage - pointOffset.y()));

      return true;

   }


   //bool scroll_base::this->rectangle(::rectangle_i32 * prectangle)
   //{

   //   ::user::interaction::this->rectangle(prectangle);

   //   prectangle->right() -= get_final_y_scroll_bar_width();

   //   prectangle->bottom() -= get_final_x_scroll_bar_width();

   //   return true;

   //}


   bool scroll_base::GetFocusRect(::rectangle_i32 & rectangle)
   {

      rectangle.left() = 0;
      rectangle.top() = 0;
      rectangle.right() = const_layout().sketch().size().cx();
      rectangle.bottom() = const_layout().sketch().size().cy();

      return true;

   }


   ::size_f64 scroll_base::get_total_size(::user::enum_layout elayout)
   {

      auto scrollstatex = get_scroll_state_x(elayout);

      auto scrollstatey = get_scroll_state_y(elayout);

      return ::size_f64(scrollstatex.dimension(), scrollstatey.dimension());

   }


   void scroll_base::set_total_size(const ::size_f64 & size, ::user::enum_layout elayout)
   {

      auto scrollstatex = get_scroll_state_x(elayout);

      auto scrollstatey = get_scroll_state_y(elayout);

      scrollstatex.set_dimension((::i32) size.cx());

      scrollstatey.set_dimension((::i32) size.cy());

      set_scroll_state_x(scrollstatex, elayout);

      set_scroll_state_y(scrollstatey, elayout);

      on_change_scroll_state(elayout);

   }


   void scroll_base::set_page_size(const ::size_f64 & size, ::user::enum_layout elayout)
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

         ::rectangle_i32 rectangle;

         rectangle.top() = rectangleX.bottom();
         rectangle.left() = rectangleX.right();
         rectangle.right() = (::i32)(rectangle.left() + m_pscrollbarY->const_layout().design().size().cx());
         rectangle.bottom() = (::i32)(rectangle.top() + m_pscrollbarX->const_layout().design().size().cy());

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


   bool scroll_base::get_element_rectangle(::rectangle_i32 & rectangle, enum_element eelement)
   {

      if (eelement == e_element_client_hit_test)
      {

         //if (!m_bEmptyAreaIsClientArea)
         //{

         //   return false;

         //}

         rectangle = this->rectangle();

         if (scroll_bar_x_visible())
         {

            rectangle.bottom() -= (::i32) m_pscrollbarX->scroll_bar_thickness();

         }

         if (scroll_bar_y_visible())
         {

            rectangle.right() -= (::i32) m_pscrollbarY->scroll_bar_thickness();

         }

         return true;

      }

      return ::user::interaction::get_element_rectangle(rectangle, eelement);

   }


}  // namespace aura



