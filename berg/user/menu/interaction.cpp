#include "platform.h"
#include "interaction.h"
#include "menu.h"
#include "acme/constant/user_message.h"
#include "acme/platform/application.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/message/user.h"
#include "berg/platform/session.h"
#include "aura/user/user/calc_size.h"
#include "berg/user/menu/item.h"
#include "berg/user/user/style.h"


namespace user
{


   menu_interaction::menu_interaction()
   {

      m_econtroltype = e_control_type_menu_button;

   }


   menu_interaction::~menu_interaction()
   {

   }


   void menu_interaction::destroy()
   {

      m_pmenuitem.release();

      ::user::interaction::destroy();

   }


   void menu_interaction::initialize_menu_interaction(::menu::item* pmenuitem)
   {

      //auto estatus = 
      
      ::user::interaction::initialize(pmenuitem);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pmenuitem = pmenuitem;
         
      //return estatus;

   }


   void menu_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &menu_interaction::on_message_create);

   }


   void menu_interaction::_001OnDrawDefault(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      if (id() == "separator")
      {

         auto pdraw2dpen = createø < ::draw2d::pen > ();

         pdraw2dpen->create_solid(2.0, argb(127, 80, 80, 80));

         pdraw2dgraphics->set(pdraw2dpen);

         pdraw2dgraphics->line(
            rectangleX.left, (rectangleX.top + rectangleX.bottom) / 2,
            rectangleX.right, (rectangleX.top + rectangleX.bottom) / 2);

         return;

      }

      interaction::_001OnDraw(pdraw2dgraphics);

      if (m_pmenuitem.is_set() && m_pmenuitem->m_bPopup)
      {

         auto pdraw2dbrush = createø < ::draw2d::brush > ();

         pdraw2dbrush->create_solid(rgb(0, 0, 0));

         auto pdraw2dpen = createø < ::draw2d::pen > ();

         pdraw2dpen->create_solid(1, rgb(0, 0, 0));
         pdraw2dgraphics->set(pdraw2dpen);
         pdraw2dgraphics->set(pdraw2dbrush);
         ::i32_rectangle rectanglePopupArrow;
         rectanglePopupArrow.left = rectangleX.right - 9;
         rectanglePopupArrow.right = rectangleX.right - 4;
         rectanglePopupArrow.top = ((rectangleX.top + rectangleX.bottom) / 2) - 4;
         rectanglePopupArrow.bottom = ((rectangleX.top + rectangleX.bottom) / 2) + 4;
         f64_point_array pointa;

         pointa.add(i32_point(rectanglePopupArrow.left, rectanglePopupArrow.bottom));

         pointa.add(i32_point(rectanglePopupArrow.right, (rectanglePopupArrow.bottom + rectanglePopupArrow.top) / 2));

         pointa.add(i32_point(rectanglePopupArrow.left, rectanglePopupArrow.top));



         pointa.add(i32_point(rectanglePopupArrow.left, rectanglePopupArrow.bottom));
         pdraw2dgraphics->polygon(pointa);

      }

      _001DrawCheck(pdraw2dgraphics);

   }


   void menu_interaction::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::pointer<::berg::style>pstyle = get_style(pdraw2dgraphics);

      if (pstyle)
      {

         pstyle->_001OnDrawMenuInteraction(pdraw2dgraphics, this);

      }

      _001OnDrawDefault(pdraw2dgraphics);

   }


   void menu_interaction::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

   }


   void menu_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      if (id() != "separator")
      {

         ::user::interaction::_001OnNcDraw(pdraw2dgraphics);

      }

   }


   void menu_interaction::_001DrawCheck(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

   }


   void menu_interaction::on_message_create(::message::message * pmessage)
   {

      //descriptor().set_control_type(e_control_type_menu_button);

      pmessage->previous();

   }


   void menu_interaction::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

   }


   ::f64_size menu_interaction::get_preferred_size(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto strWindowText = get_window_text();

      //get_window_text(strText);

      pdraw2dgraphics->set_font(this, ::e_element_none);

      auto size = pdraw2dgraphics->get_text_extent(strWindowText);

      auto pstyle = get_style(pdraw2dgraphics);

      auto rectangleMargin = get_margin(pstyle);

      auto rectangleBorder = get_border(pstyle);

      auto rectanglePadding = get_padding(pstyle);

      size.cx += rectangleMargin.left + rectangleBorder.left + rectanglePadding.left;

      size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      size.cx += rectanglePadding.left;

      if (m_pmenuitem->is_popup())
      {

         size.cx += rectanglePadding.left;

         size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      }

      size.cx += rectangleMargin.right + rectangleBorder.right + rectanglePadding.right;

      size.cy += rectangleMargin.top + rectangleBorder.top + rectanglePadding.top;

      size.cy += rectangleMargin.bottom + rectangleBorder.bottom + rectanglePadding.bottom;

      //pcalcsize->m_size = size;

      return size;

   }


   // ::berg::application* menu_interaction::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::berg::session* menu_interaction::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::berg::system* menu_interaction::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::berg::user* menu_interaction::user()
   // {
   //
   //
   //
   //    return ::is_set(psession) ? user() : nullptr;
   //
   // }

} // namespace user



