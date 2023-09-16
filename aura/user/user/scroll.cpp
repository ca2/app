#include "framework.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/draw2d/graphics.h"
#include "scroll_data.h"
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


   void scroll_base::install_message_routing(::channel * pchannel)
   {

      horizontal_scroll_base::install_message_routing(pchannel);
      vertical_scroll_base::install_message_routing(pchannel);

   }


   void scroll_base::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

      horizontal_scroll_base::on_change_context_offset(pgraphics);

      vertical_scroll_base::on_change_context_offset(pgraphics);

      ::user::interaction::on_change_context_offset(pgraphics);

   }


   bool scroll_base::validate_context_offset(point_i32 & point)
   {

      bool xValidated = horizontal_scroll_base::validate_context_offset(point);

      bool yValidated = vertical_scroll_base::validate_context_offset(point);

      bool iValidated = ::user::interaction::validate_context_offset(point);

      return (xValidated || yValidated) && iValidated;

   }


   void scroll_base::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   {

      horizontal_scroll_base::layout_scroll_bar(pgraphics);

      vertical_scroll_base::layout_scroll_bar(pgraphics);

   }


   void scroll_base::on_change_impact_size(::draw2d::graphics_pointer & pgraphics)
   {

      m_pscrolldataHorizontal->m_bHasScroll = false;

      m_pscrolldataVertical->m_bHasScroll = false;

      auto sizeTotal = get_total_size();

      auto rectangleX = this->rectangle();

      if(rectangleX.area() <= 0)
      {

         return;

      }

      auto pstyle = get_style(pgraphics);

      ::i32 iTotalHeight = (::i32) sizeTotal.cy();

      ::i32 iTotalWidth = (::i32) sizeTotal.cx();

      ::i32 iClientHeight = rectangleX.height();

      ::i32 iClientWidth = rectangleX.width();

      ::i32 iScrollHeight = iClientHeight - get_int(pstyle, e_int_scroll_bar_width);;

      ::i32 iscrollWidth = iClientWidth - get_int(pstyle, e_int_scroll_bar_width);;

      if (iTotalWidth > iClientWidth)
      {

         m_pscrolldataHorizontal->m_bHasScroll = true;

         if (iTotalHeight > iScrollHeight)
         {

            m_pscrolldataVertical->m_bHasScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_pscrolldataVertical->m_bHasScroll = true;

         if (iTotalWidth > iscrollWidth)
         {

            m_pscrolldataHorizontal->m_bHasScroll = true;

         }

      }

      //m_pscrolldataHorizontal->m_bShowScroll = m_pscrolldataHorizontal->m_bScrollEnable && m_pscrolldataHorizontal->m_bHasScroll;

      //m_pscrolldataVertical->m_bShowScroll = m_pscrolldataVertical->m_bScrollEnable && m_pscrolldataVertical->m_bHasScroll;

      //if (!m_pscrolldataHorizontal->m_bScroll)
      //{

      //   m_pointScroll.x() = 0;

      //}


      //if (!m_pscrolldataVertical->m_bScroll)
      //{

      //   m_pointScroll.y() = 0;

      //}


      auto rectangleScroll = this->rectangle();

      m_pscrolldataHorizontal->m_iPage = rectangleScroll.width();

      m_pscrolldataVertical->m_iPage = rectangleScroll.height();

      if (validate_context_offset(m_pointScroll))
      {

         layout_scroll_bar(pgraphics);

         on_change_context_offset(pgraphics);

      }
      else
      {

         layout_scroll_bar(pgraphics);

      }

   }



   bool scroll_base::GetActiveClientRect(::rectangle_i32 & rectangle)
   {

      rectangle = this->rectangle();

      auto sizeTotal = get_total_size();

      auto pointOffset = get_context_offset();

      rectangle.right() = (::i32) (rectangle.left() + minimum(::width(rectangle), sizeTotal.cx() - m_pscrolldataHorizontal->m_iPage - pointOffset.x()));

      rectangle.bottom() = (::i32) (rectangle.top() + minimum(::height(rectangle), sizeTotal.cy() - m_pscrolldataVertical->m_iPage - pointOffset.y()));

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


   ::size_f64 scroll_base::get_total_size()
   {

      return m_sizeTotal;

   }


   void scroll_base::set_total_size(const ::size_f64& size)
   {

      m_sizeTotal.cx() = size.cx();

      m_sizeTotal.cy() = size.cy();

      //return ::success;

   }


   void scroll_base::set_page_size(const ::size_f64& size)
   {

      throw ::interface_only();

   }


   void scroll_base::defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pscrolldataHorizontal->m_bScrollEnable && m_pscrolldataHorizontal->m_bHasScroll
            && m_pscrollbarHorizontal.is_set() && m_pscrollbarHorizontal->is_ok()
            && m_pscrolldataVertical->m_bScrollEnable && m_pscrolldataVertical->m_bHasScroll
            && m_pscrollbarVertical.is_set() && m_pscrollbarVertical->is_ok())
      {

         auto rectangleX = this->rectangle();

         ::rectangle_i32 rectangle;

         rectangle.top() = rectangleX.bottom();
         rectangle.left() = rectangleX.right();
         rectangle.right() = (::i32) (rectangle.left() + m_pscrollbarVertical->const_layout().design().size().cx());
         rectangle.bottom() = (::i32) (rectangle.top() + m_pscrollbarHorizontal->const_layout().design().size().cy());

         pgraphics->fill_rectangle(rectangle, argb(127, 127, 127, 127));

      }

   }


   bool scroll_base::horizontal_scrollbar_visible()
   {

      return m_pscrolldataHorizontal->scroll_visible();

   }


   bool scroll_base::vertical_scrollbar_visible()
   {

      return m_pscrolldataVertical->scroll_visible();

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

         if (horizontal_scrollbar_visible())
         {

            rectangle.bottom() -= m_pscrollbarHorizontal->scrollbar_width();

         }

         if (vertical_scrollbar_visible())
         {

            rectangle.right() -= m_pscrollbarVertical->scrollbar_width();

         }

         return true;

      }

      return ::user::interaction::get_element_rectangle(rectangle, eelement);

   }


}  // namespace aura



