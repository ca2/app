#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{


   menu_interaction::menu_interaction(menu_item * pitem) :
      m_pmenuitem(pitem),
      ::object(pitem)
   {

   }


   menu_interaction::~menu_interaction()
   {

   }


   void menu_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &menu_interaction::_001OnCreate);

   }


   void menu_interaction::_001OnDrawDefault(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if (m_id == "separator")
      {

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(2.0, ARGB(127, 80, 80, 80));

         pgraphics->set(pen);

         pgraphics->move_to(rectClient.left, (rectClient.top + rectClient.bottom) / 2);

         pgraphics->line_to(rectClient.right, (rectClient.top + rectClient.bottom) / 2);

         return;

      }

      interaction::_001OnDraw(pgraphics);

      if (m_pmenuitem.is_set() && m_pmenuitem->m_bPopup)
      {

         ::draw2d::brush_pointer br(e_create);

         br->create_solid(RGB(0, 0, 0));

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(1, RGB(0, 0, 0));
         pgraphics->set(pen);
         pgraphics->set(br);
         ::rect rectPopupArrow;
         rectPopupArrow.left = rectClient.right - 9;
         rectPopupArrow.right = rectClient.right - 4;
         rectPopupArrow.top = ((rectClient.top + rectClient.bottom) / 2) - 4;
         rectPopupArrow.bottom = ((rectClient.top + rectClient.bottom) / 2) + 4;
         point_array pointa;
         pointa.add(point(rectPopupArrow.left, rectPopupArrow.bottom));
         pointa.add(point(rectPopupArrow.right, (rectPopupArrow.bottom + rectPopupArrow.top) / 2));
         pointa.add(point(rectPopupArrow.left, rectPopupArrow.top));
         pointa.add(point(rectPopupArrow.left, rectPopupArrow.bottom));
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


   void menu_interaction::_001OnCreate(::message::message * pmessage)
   {

      descriptor().set_control_type(control_type_menu_button);

      pmessage->previous();

   }


   void menu_interaction::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->previous();

   }


   void menu_interaction::on_calc_size(calc_size * pcalcsize)
   {

      string strText;

      get_window_text(strText);

      pcalcsize->m_pgraphics->set_font(this);

      auto size = pcalcsize->m_pgraphics->GetTextExtent(strText);

      auto pstyle = get_style(pcalcsize->m_pgraphics);

      ::rect rectMargin = get_margin(pstyle);

      ::rect rectBorder = get_border(pstyle);

      ::rect rectPadding = get_padding(pstyle);

      size.cx += rectMargin.left + rectBorder.left + rectPadding.left;

      size.cx += m_pmenuitem->m_pmenu->m_iCheckBoxSize;

      size.cx += rectPadding.left;

      if (m_pmenuitem->IsPopup())
      {

         size.cx += rectPadding.left;

         size.cx += m_pmenuitem->m_pmenu->m_iCheckBoxSize;

      }

      size.cx += rectMargin.right + rectBorder.right + rectPadding.right;

      size.cy += rectMargin.top + rectBorder.top + rectPadding.top;

      size.cy += rectMargin.bottom + rectBorder.bottom + rectPadding.bottom;

      pcalcsize->m_size = size;

   }


} // namespace user
