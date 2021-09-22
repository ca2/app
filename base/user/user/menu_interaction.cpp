#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   menu_interaction::menu_interaction()
   {

      m_econtroltype = e_control_type_menu_button;

   }


   menu_interaction::~menu_interaction()
   {

   }


   ::e_status menu_interaction::initialize_menu_interaction(menu_item* pmenuitem)
   {

      auto estatus = ::user::interaction::initialize(pmenuitem);

      if (!estatus)
      {

         return estatus;

      }

      m_pmenuitem = pmenuitem;
         
      return estatus;

   }


   void menu_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_interaction::on_message_create);

   }


   void menu_interaction::_001OnDrawDefault(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (m_id == "separator")
      {

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(2.0, argb(127, 80, 80, 80));

         pgraphics->set(ppen);

         pgraphics->move_to(rectangleClient.left, (rectangleClient.top + rectangleClient.bottom) / 2);

         pgraphics->line_to(rectangleClient.right, (rectangleClient.top + rectangleClient.bottom) / 2);

         return;

      }

      interaction::_001OnDraw(pgraphics);

      if (m_pmenuitem.is_set() && m_pmenuitem->m_bPopup)
      {

         auto pbrush = __create < ::draw2d::brush > ();

         pbrush->create_solid(rgb(0, 0, 0));

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1, rgb(0, 0, 0));
         pgraphics->set(ppen);
         pgraphics->set(pbrush);
         ::rectangle_i32 rectanglePopupArrow;
         rectanglePopupArrow.left = rectangleClient.right - 9;
         rectanglePopupArrow.right = rectangleClient.right - 4;
         rectanglePopupArrow.top = ((rectangleClient.top + rectangleClient.bottom) / 2) - 4;
         rectanglePopupArrow.bottom = ((rectangleClient.top + rectangleClient.bottom) / 2) + 4;
         point_f64_array pointa;

         pointa.add(point_i32(rectanglePopupArrow.left, rectanglePopupArrow.bottom));

         pointa.add(point_i32(rectanglePopupArrow.right, (rectanglePopupArrow.bottom + rectanglePopupArrow.top) / 2));

         pointa.add(point_i32(rectanglePopupArrow.left, rectanglePopupArrow.top));



         pointa.add(point_i32(rectanglePopupArrow.left, rectanglePopupArrow.bottom));
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


   void menu_interaction::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      pmouse->previous();

   }


   void menu_interaction::on_calc_size(calc_size * pcalcsize)
   {

      string strText;

      get_window_text(strText);

      pcalcsize->m_pgraphics->set_font(this, ::e_element_none);

      auto size = pcalcsize->m_pgraphics->get_text_extent(strText);

      auto pstyle = get_style(pcalcsize->m_pgraphics);

      auto rectangleMargin = get_margin(pstyle);

      auto rectangleBorder = get_border(pstyle);

      auto rectanglePadding = get_padding(pstyle);

      size.cx += rectangleMargin.left + rectangleBorder.left + rectanglePadding.left;

      size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      size.cx += rectanglePadding.left;

      if (m_pmenuitem->IsPopup())
      {

         size.cx += rectanglePadding.left;

         size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      }

      size.cx += rectangleMargin.right + rectangleBorder.right + rectanglePadding.right;

      size.cy += rectangleMargin.top + rectangleBorder.top + rectanglePadding.top;

      size.cy += rectangleMargin.bottom + rectangleBorder.bottom + rectanglePadding.bottom;

      pcalcsize->m_size = size;

   }


} // namespace user
