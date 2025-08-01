#include "framework.h"
#include "interaction.h"
#include "menu.h"
#include "acme/constant/message.h"
#include "acme/platform/application.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/message/user.h"
#include "base/platform/session.h"
#include "aura/user/user/calc_size.h"
#include "base/user/menu/item.h"
#include "base/user/user/style.h"


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

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_interaction::on_message_create);

   }


   void menu_interaction::_001OnDrawDefault(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (id() == "separator")
      {

         auto ppen = __øcreate < ::draw2d::pen > ();

         ppen->create_solid(2.0, argb(127, 80, 80, 80));

         pgraphics->set(ppen);

         pgraphics->line(
            rectangleX.left(), (rectangleX.top() + rectangleX.bottom()) / 2,
            rectangleX.right(), (rectangleX.top() + rectangleX.bottom()) / 2);

         return;

      }

      interaction::_001OnDraw(pgraphics);

      if (m_pmenuitem.is_set() && m_pmenuitem->m_bPopup)
      {

         auto pbrush = __øcreate < ::draw2d::brush > ();

         pbrush->create_solid(rgb(0, 0, 0));

         auto ppen = __øcreate < ::draw2d::pen > ();

         ppen->create_solid(1, rgb(0, 0, 0));
         pgraphics->set(ppen);
         pgraphics->set(pbrush);
         ::int_rectangle rectanglePopupArrow;
         rectanglePopupArrow.left() = rectangleX.right() - 9;
         rectanglePopupArrow.right() = rectangleX.right() - 4;
         rectanglePopupArrow.top() = ((rectangleX.top() + rectangleX.bottom()) / 2) - 4;
         rectanglePopupArrow.bottom() = ((rectangleX.top() + rectangleX.bottom()) / 2) + 4;
         double_point_array pointa;

         pointa.add(int_point(rectanglePopupArrow.left(), rectanglePopupArrow.bottom()));

         pointa.add(int_point(rectanglePopupArrow.right(), (rectanglePopupArrow.bottom() + rectanglePopupArrow.top()) / 2));

         pointa.add(int_point(rectanglePopupArrow.left(), rectanglePopupArrow.top()));



         pointa.add(int_point(rectanglePopupArrow.left(), rectanglePopupArrow.bottom()));
         pgraphics->polygon(pointa);

      }

      _001DrawCheck(pgraphics);

   }


   void menu_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::pointer<::base::style>pstyle = get_style(pgraphics);

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

      if (id() != "separator")
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

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

   }


   ::double_size menu_interaction::get_preferred_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto strWindowText = get_window_text();

      //get_window_text(strText);

      pgraphics->set_font(this, ::e_element_none);

      auto size = pgraphics->get_text_extent(strWindowText);

      auto pstyle = get_style(pgraphics);

      auto rectangleMargin = get_margin(pstyle);

      auto rectangleBorder = get_border(pstyle);

      auto rectanglePadding = get_padding(pstyle);

      size.cx() += rectangleMargin.left() + rectangleBorder.left() + rectanglePadding.left();

      size.cx() += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      size.cx() += rectanglePadding.left();

      if (m_pmenuitem->is_popup())
      {

         size.cx() += rectanglePadding.left();

         size.cx() += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      }

      size.cx() += rectangleMargin.right() + rectangleBorder.right() + rectanglePadding.right();

      size.cy() += rectangleMargin.top() + rectangleBorder.top() + rectanglePadding.top();

      size.cy() += rectangleMargin.bottom() + rectangleBorder.bottom() + rectanglePadding.bottom();

      //pcalcsize->m_size = size;

      return size;

   }


   // ::base::application* menu_interaction::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::base::session* menu_interaction::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::base::system* menu_interaction::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::base::user* menu_interaction::user()
   // {
   //
   //
   //
   //    return ::is_set(psession) ? user() : nullptr;
   //
   // }

} // namespace user



