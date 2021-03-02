#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   menu_interaction::menu_interaction(menu_item * pitem) :
      m_pmenuitem(pitem),
      ::object(pitem)
   {

      m_econtroltype = e_control_type_menu_button;

   }


   menu_interaction::~menu_interaction()
   {

   }


   void menu_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_interaction::on_message_create);

   }


   void menu_interaction::_001OnDrawDefault(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      if (m_id == "separator")
      {

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(2.0, argb(127, 80, 80, 80));

         pgraphics->set(pen);

         pgraphics->move_to(rectClient.left, (rectClient.top + rectClient.bottom) / 2);

         pgraphics->line_to(rectClient.right, (rectClient.top + rectClient.bottom) / 2);

         return;

      }

      interaction::_001OnDraw(pgraphics);

      if (m_pmenuitem.is_set() && m_pmenuitem->m_bPopup)
      {

         ::draw2d::brush_pointer br(e_create);

         br->create_solid(rgb(0, 0, 0));

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(1, rgb(0, 0, 0));
         pgraphics->set(pen);
         pgraphics->set(br);
         ::rectangle_i32 rectPopupArrow;
         rectPopupArrow.left = rectClient.right - 9;
         rectPopupArrow.right = rectClient.right - 4;
         rectPopupArrow.top = ((rectClient.top + rectClient.bottom) / 2) - 4;
         rectPopupArrow.bottom = ((rectClient.top + rectClient.bottom) / 2) + 4;
         point_f64_array pointa;

         pointa.add(point_i32(rectPopupArrow.left, rectPopupArrow.bottom));

         pointa.add(point_i32(rectPopupArrow.right, (rectPopupArrow.bottom + rectPopupArrow.top) / 2));

         pointa.add(point_i32(rectPopupArrow.left, rectPopupArrow.top));



         pointa.add(point_i32(rectPopupArrow.left, rectPopupArrow.bottom));
         pgraphics->polygon(pointa);

      }

      _001DrawCheck(pgraphics);

   }


   void menu_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::base::style) pstyle = get_style(pgraphics);

      if (pstyle)
      {

         pstyle->_001OnDrawMenuInteraction(pgraphics, this);

      }

      _001OnDrawDefault(pgraphics);

   }


   void menu_interaction::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void menu_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_id != "separator")
      {

         ::user::interaction::_001OnNcDraw(pgraphics);

      }

   }


   void menu_interaction::_001DrawCheck(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void menu_interaction::on_message_create(::message::message * pmessage)
   {

      //descriptor().set_control_type(e_control_type_menu_button);

      pmessage->previous();

   }


   void menu_interaction::_001OnMouseMove(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->previous();

   }


   void menu_interaction::on_calc_size(calc_size * pcalcsize)
   {

      string strText;

      get_window_text(strText);

      pcalcsize->m_pgraphics->set_font(this, ::user::e_element_none);

      auto size = pcalcsize->m_pgraphics->GetTextExtent(strText);

      auto pstyle = get_style(pcalcsize->m_pgraphics);

      auto rectMargin = get_margin(pstyle);

      auto rectBorder = get_border(pstyle);

      auto rectPadding = get_padding(pstyle);

      size.cx += rectMargin.m_result.left + rectBorder.m_result.left + rectPadding.m_result.left;

      size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      size.cx += rectPadding.m_result.left;

      if (m_pmenuitem->IsPopup())
      {

         size.cx += rectPadding.m_result.left;

         size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      }

      size.cx += rectMargin.m_result.right + rectBorder.m_result.right + rectPadding.m_result.right;

      size.cy += rectMargin.m_result.top + rectBorder.m_result.top + rectPadding.m_result.top;

      size.cy += rectMargin.m_result.bottom + rectBorder.m_result.bottom + rectPadding.m_result.bottom;

      pcalcsize->m_size = size;

   }


} // namespace user
