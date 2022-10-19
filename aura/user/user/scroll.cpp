#include "framework.h"
//#include "acme/operating_system.h"
#if !BROAD_PRECOMPILED_HEADER
////#include "aura/user/user/_component.h"
#endif
//#include "acme/operating_system/_user.h"
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

      m_pscrolldataHorizontal->m_bScroll = false;

      m_pscrolldataVertical->m_bScroll = false;

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

         m_pscrolldataHorizontal->m_bScroll = true;

         if (iTotalHeight > iScrollHeight)
         {

            m_pscrolldataVertical->m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_pscrolldataVertical->m_bScroll = true;

         if (iTotalWidth > iscrollWidth)
         {

            m_pscrolldataHorizontal->m_bScroll = true;

         }

      }

      m_pscrolldataHorizontal->m_bScroll = m_pscrolldataHorizontal->m_bScrollEnable && m_pscrolldataHorizontal->m_bScroll;

      m_pscrolldataVertical->m_bScroll = m_pscrolldataVertical->m_bScrollEnable && m_pscrolldataVertical->m_bScroll;

      //if (!m_pscrolldataHorizontal->m_bScroll)
      //{

      //   m_pointScroll.x = 0;

      //}


      //if (!m_pscrolldataVertical->m_bScroll)
      //{

      //   m_pointScroll.y = 0;

      //}


      ::rectangle_i32 rectangleScroll;

      get_client_rect(rectangleScroll);

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



   bool scroll_base::GetActiveClientRect(RECTANGLE_I32 & rectangle)
   {

      ::user::interaction::get_client_rect(rectangle);

      auto sizeTotal = get_total_size();

      auto pointOffset = get_context_offset();

      rectangle.right = (::i32) (rectangle.left + minimum(::width(rectangle), sizeTotal.cx - m_pscrolldataHorizontal->m_iPage - pointOffset.x));

      rectangle.bottom = (::i32) (rectangle.top + minimum(::height(rectangle), sizeTotal.cy - m_pscrolldataVertical->m_iPage - pointOffset.y));

      return true;

   }


   //bool scroll_base::get_client_rect(RECTANGLE_I32 * prectangle)
   //{

   //   ::user::interaction::get_client_rect(prectangle);

   //   prectangle->right -= get_final_y_scroll_bar_width();

   //   prectangle->bottom -= get_final_x_scroll_bar_width();

   //   return true;

   //}


   bool scroll_base::GetFocusRect(RECTANGLE_I32 & rectangle)
   {

      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.right = const_layout().sketch().size().cx;
      rectangle.bottom = const_layout().sketch().size().cy;

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

      if (m_pscrolldataHorizontal->m_bScrollEnable && m_pscrolldataHorizontal->m_bScroll
            && m_pscrollbarHorizontal.is_set() && m_pscrollbarHorizontal->is_ok()
            && m_pscrolldataVertical->m_bScrollEnable && m_pscrolldataVertical->m_bScroll
            && m_pscrollbarVertical.is_set() && m_pscrollbarVertical->is_ok())
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         ::rectangle_i32 rectangle;

         rectangle.top = rectangleClient.bottom;
         rectangle.left = rectangleClient.right;
         rectangle.right = (::i32) (rectangle.left + m_pscrollbarVertical->const_layout().design().size().cx);
         rectangle.bottom = (::i32) (rectangle.top + m_pscrollbarHorizontal->const_layout().design().size().cy);

         pgraphics->fill_rectangle(rectangle, argb(127, 127, 127, 127));

      }

   }


}  // namespace aura



